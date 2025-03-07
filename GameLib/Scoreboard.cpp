/**
 * @file Scoreboard.cpp
 * @author Emily Nguyen
 */

#include "pch.h"
#include <sstream>
#include "Scoreboard.h"

#include "LastProductVisitor.h"
#include "Level.h"
#include "VisitorBase.h"
#include "ProductDetector.h"

/**
 * Size of the scoreboard in virtual pixels
 * @return wxSize
 */
const wxSize ScoreboardSize(380, 100);

/// x coordinate of Top-left corner of the scoreboard
const int xCoordinate = 700;
/// y coordinate of top-left corner of the scoreboard
const int yCoordinate = 40;

/// The spacing from the level score and game score
/// in virtual pixels
const int SpacingLevelToGameScores = 150;

/// The spacing from the scores to the instructions presentation
/// in virtual pixels
const int SpacingScoresToInstructions = 40;

/// The spacing between the instruction lines in virtual pixels.
const int SpacingInstructionLines = 17;

/**
 * Constructor
 * @param level Level this scoreboard is a member of
 */
Scoreboard::Scoreboard(Level* level) : Item(level->GetGame())
{
	// Grab the game score stored in game
	mGameScore = GetGame()->GetGameScore();
}

/**
 * Draws the scoreboard
 * @param graphics The graphics context used for making the scoreboard
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	// Offset for text position
	double offsetX = xCoordinate + 10;
	double offsetY = yCoordinate + 10;

	// Set pen to black (outline)
	graphics->SetPen(wxPen(wxColor(0, 0, 0), 1));

	// Set brush to white (background)
	graphics->SetBrush(wxBrush(wxColor(255, 255, 255)));

	// Draw rectangular box
	graphics->DrawRectangle(xCoordinate, yCoordinate, ScoreboardSize.GetWidth(), ScoreboardSize.GetHeight());

    // Font for the scores
    auto font = graphics->CreateFont(25, L"Arial",
                                     wxFONTFLAG_BOLD, wxColour(24, 69, 59));
    graphics->SetFont(font);

    // Draw the current level score and game score
    std::wstring levelScoreText = L"Level: " + std::to_wstring(mLevelScore);
    std::wstring gameScoreText = L"Game: " + std::to_wstring(mGameScore);
    graphics->DrawText(levelScoreText, offsetX, offsetY);
    graphics->DrawText(gameScoreText, offsetX + SpacingLevelToGameScores, offsetY);

    // Font for the instructions
    font = graphics->CreateFont(15, L"Arial",
                                wxFONTFLAG_BOLD, *wxBLACK);
    graphics->SetFont(font);

    // Draw the instructions below scores
	// Split the instructions by newline characters and draw each line (solves newline problem on mac)
	std::wstringstream instructionsStream(mInstructions);
	std::wstring line;

	double currentOffsetY = offsetY + SpacingScoresToInstructions;  // Start below scores

	// Use loop to print each line
	while (std::getline(instructionsStream, line))
	{
		graphics->DrawText(line, offsetX, currentOffsetY);
		currentOffsetY += SpacingInstructionLines;  // Adjust spacing for the next line
	}
}

/**
 * Update Scoreboard
 * @param elapsed Time elapsed since the last update
 */
void Scoreboard::Update(double elapsed)
{
	// Updates level score
	ProductDetector detector;
	GetGame()->Accept(&detector);
	detector.UpdateScoreboard();

	// Level end scoring
	LastProductVisitor visitor;
	GetGame()->Accept(&visitor);
	if(visitor.HasLastProductReached())
	{
		// Delay adding score until Level Complete banner appears
		double timer = GetGame()->GetEndTimer() - elapsed;
		if(timer <= 2 && !mScoreAdded)
		{
			AddLevelScoreToGame();

			// Adds score once
			mScoreAdded = true;
		}
	}
}

/**
 * Load the information for a scoreboard node
 * @param node The Xml node we are loading the scoreboard from
 */
void Scoreboard::XmlLoad(wxXmlNode* node)
{
	Item::XmlLoad(node);
	node->GetAttribute(L"good" , L"10").ToInt(&mGood);
	node->GetAttribute(L"bad" , L"0").ToInt(&mBad);
	auto child = node->GetChildren();
	for(; child; child = child->GetNext())
	{
		if(child->GetType() == wxXML_TEXT_NODE)
		{
			mInstructions += child->GetContent().ToStdWstring();
			mInstructions += L"\r\n";
		}
	}
}

/**
 * Accepts a visitor
 * @param visitor The visitor we accept
 */
void Scoreboard::Accept(VisitorBase* visitor)
{
	visitor->VisitScoreboard(this);
}

/**
 * Adds the Level score to Game Score at the end of level
 */
void Scoreboard::AddLevelScoreToGame()
{
	// Add level score to game score
	mGameScore += mLevelScore;

	// Add bonus score if applicable
	if(mLevelScore == mPerfectScore7 || mLevelScore == mPerfectScore8)
	{
		mPerfectScore = true;
		mGameScore += GetGame()->CalculateBonusPoints();
	}
}