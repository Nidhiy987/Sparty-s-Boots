/**
 * @file Level.cpp
 * @author Attulya Pratap Gupta
 */
#include "pch.h"
#include "Level.h"
#include "Product.h"
#include "Game.h"
#include "ItemFactory.h"
#include <wx/tokenzr.h>

/**
 * Level Constructor
 * @param game The game this is a member of
 */
Level::Level(Game* game) : mGame(game) {}

/**
 * Load the level from an XML node
 * @param node The XML node to load from
 * @return True if loading was successful, false otherwise
 */
bool Level::Load(wxXmlNode* node)
{
    // Load level size
    wxString size;
    if (node->GetAttribute(L"size", &size))
    {
        wxStringTokenizer tokenizer(size, L",");
        tokenizer.GetNextToken().ToLong(&mWidth);
        tokenizer.GetNextToken().ToLong(&mHeight);
    }

    // Load items
    auto itemsNode = node->GetChildren();
    while (itemsNode)
    {
        if (itemsNode->GetName() == L"items")
        {
            auto itemNode = itemsNode->GetChildren();
            while (itemNode)
            {
                if (itemNode->GetName() == L"conveyor")
                {
                    LoadItem(itemNode);
                    LoadProducts(itemNode);
                }
                else
                {
                    LoadItem(itemNode);
                }
                itemNode = itemNode->GetNext();
            }
        }
        itemsNode = itemsNode->GetNext();
    }
	mGame->ProductClear();
	// Reset member variables for each load
	mLevelTime = 0;
	mCompletionBonus = MaxCompletionBonus;
	mBonusDecrement = BonusDecrementStart;
	mLastBonusDecrement = 0;
    return true;
}


void Level::LoadItem(wxXmlNode* node)
{
    auto item = ItemFactory::CreateItem(node->GetName().ToStdWstring(), mGame);
    if (item != nullptr)
    {
        item->XmlLoad(node);
        mGame->AddItem(item);
    }
}

void Level::LoadProducts(wxXmlNode* conveyorNode)
{
    double conveyorX, conveyorY, conveyorHeight;
    conveyorNode->GetAttribute("x", "0").ToDouble(&conveyorX);
    conveyorNode->GetAttribute("y", "0").ToDouble(&conveyorY);
    conveyorNode->GetAttribute("height", "0").ToDouble(&conveyorHeight);

    double currentPlacement = 0;
    for (auto productNode = conveyorNode->GetChildren(); productNode; productNode = productNode->GetNext())
    {
        if (productNode->GetName() == L"product")
        {
            auto product = std::make_shared<Product>(this);
            product->XmlLoad(productNode);

            wxString placementStr = productNode->GetAttribute(L"placement", L"0");
            double placement;

            if (placementStr.StartsWith(L"+"))
            {
                placementStr = placementStr.Mid(1);
                placementStr.ToDouble(&placement);
                currentPlacement += placement;
            }
            else
            {
                placementStr.ToDouble(&currentPlacement);
            }

            double productX = conveyorX;
            double productY = conveyorY - currentPlacement;

            product->SetLocation(productX, productY);
            product->SetInitialPosition(productX, productY, conveyorHeight);
            mGame->AddProduct(product);
        }
    }
}

/**
 * Draw the level notices
 * @param gc The graphics context used to draw the level notices
 * @param levelEnd boolean flag tells if we are at the end of the level or not
 */
void Level::DrawLevel(std::shared_ptr<wxGraphicsContext> gc, bool levelEnd)
{
	// Set the brush for semi-transparent white rectangle and a transparent pen
	gc->SetBrush(wxBrush(mLevelNoticeBackground));  // Adjusted transparency
	gc->SetPen(*wxTRANSPARENT_PEN);  // Transparent pen to remove the outline

	// Draw the level notice at the start of the level
	if (mLevelTime < mMessageDuration)
	{

		// Adjust the font size and style
		gc->SetFont(wxFont(NoticeSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD),
			LevelNoticeColor);

		// Format the message
		wxString message = wxString::Format(L"Level %d Begin", mLevelNumber);
		double textWidth, textHeight;
		gc->GetTextExtent(message, &textWidth, &textHeight);
		// Draw the rectangle
		gc->DrawRectangle((mWidth - textWidth) / 2 - LevelNoticePadding ,
			(mHeight - textHeight) / 2 - LevelNoticePadding,
			textWidth + LevelNoticePadding * 2,
			textHeight + LevelNoticePadding * 2);
		// Draw the message
		gc->DrawText(message, (mWidth - textWidth) / 2, (mHeight - textHeight) / 2);
		if (mLevelNumber == 7 || mLevelNumber == 8)
		{
			// Halve font size
			gc->SetFont(wxFont(NoticeSize / 2, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD),
		LevelNoticeColor);
			wxString messageBonus = wxString::Format(L"Work quickly to earn bonus points!");
			double textBonusWidth, textBonusHeight;
			gc->GetTextExtent(messageBonus, &textBonusWidth, &textBonusHeight);

			// Draw rectangle below the Level _ Begin! message
			gc->DrawRectangle((mWidth - textBonusWidth) / 2 - LevelNoticePadding,
				(mHeight + textBonusHeight) / 2 - LevelNoticePadding + textHeight + LevelNoticePadding * 2,
				textBonusWidth + LevelNoticePadding * 2,
				textBonusHeight + LevelNoticePadding * 2);
			gc->DrawText(messageBonus, (mWidth - textBonusWidth) / 2, (mHeight + textBonusHeight) / 2  + textHeight + LevelNoticePadding * 2);
		}
	}

	// Draw the timer and Completion bonus
	else
	{
		if (mLevelNumber == 7  || mLevelNumber == 8)
		{
			// Adjust the font size and style
			auto font = gc->CreateFont(25, L"Arial",
								 wxFONTFLAG_BOLD, LevelNoticeColor);
			gc->SetFont(font);

			// Update the displayed time and bonus points if the level has not ended
			if (!levelEnd)
			{
				mDisplayTime = mLevelTime - mMessageDuration;
				UpdateCompletionBonus();
			}

			// Convert to minutes and seconds
			int displayMinutes = mDisplayTime / SecondsInMinute;
			int displaySeconds = mDisplayTime % SecondsInMinute;

			// Format the current completion bonus
			wxString bonusPoints = wxString::Format(L"Completion Bonus:    %02d", mCompletionBonus);
			double bonusPointsWidth, bonusPointsHeight;
			gc->GetTextExtent(bonusPoints, &bonusPointsWidth, &bonusPointsHeight);

			double bonusX = bonusPointsWidth + LevelNoticePadding;
			double bonusY = bonusPointsHeight + LevelNoticePadding;


			// Format the time spent in the level
			wxString timerMessage = wxString::Format(L"Level Time: %d:%02d", displayMinutes, displaySeconds);
			double textTimerWidth, textTimerHeight;
			gc->GetTextExtent(timerMessage, &textTimerWidth, &textTimerHeight);

			double timerX = mWidth - textTimerWidth - LevelNoticePadding / 2;
			double timerY = mHeight - textTimerHeight - LevelNoticePadding - bonusY;

			// Compute the rectangle size and position
			gc->SetPen(*wxBLACK_PEN);
			gc->DrawRectangle(mWidth - bonusX - LevelNoticePadding / 2, timerY - LevelNoticePadding / 2,
				bonusPointsWidth + TeamFeatureNoticePaddingWidth / 2,
				textTimerHeight +  bonusPointsHeight + TeamFeatureNoticePaddingHeight / 2);

			// Draw the timer, bonus, and rectangle
			gc->DrawText(timerMessage, timerX, timerY);
			gc->DrawText(bonusPoints, mWidth - bonusX, mHeight - bonusY);
		}
	}

	// Message to display if the level has ended
	if (levelEnd)
	{

		// Adjust the font size and style
		gc->SetFont(wxFont(NoticeSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD),
			LevelNoticeColor);

		wxString message = wxString::Format(L"Level Completed!");
		double textWidth, textHeight;
		gc->GetTextExtent(message, &textWidth, &textHeight);
		// Draw the rectangle
		gc->SetPen(*wxTRANSPARENT_PEN);  // Transparent pen to remove the outline
		gc->DrawRectangle((mWidth - textWidth) / 2 - LevelNoticePadding ,
			(mHeight - textHeight) / 2 - LevelNoticePadding,
			textWidth + LevelNoticePadding * 2,
			textHeight + LevelNoticePadding * 2);
		// Draw the message
		gc->DrawText(message, (mWidth - textWidth) / 2, (mHeight - textHeight) / 2);
	}
}

/**
 * Update the amount of time the level has been running
 * @param elapsed The amount of time since the last updated
 */
void Level::Update(double elapsed)
{
	mLevelTime += elapsed;
}

/**
 * Updates the completion bonus
 */
void Level::UpdateCompletionBonus()
{
	// Check if it's time to decrement the bonus
	if (mDisplayTime - mLastBonusDecrement >= BonusDecrementInterval)
	{
		// Decrement the bonus and update the last decrement time
		mCompletionBonus = std::max(0, mCompletionBonus - mBonusDecrement); // Ensure it doesn't go below zero
		mLastBonusDecrement = mDisplayTime;
		mBonusDecrement *= 2;
	}
}