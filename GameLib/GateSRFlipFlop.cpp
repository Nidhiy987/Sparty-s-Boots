/**
 * @file GateSRFlipFlop.cpp
 * @author Rachel Jansen
 */

#include "pch.h"
#include "GateSRFlipFlop.h"

#include "VisitorBase.h"

/// Size of the SR Flip Flop in pixels
/// @return size of SR flip flop in pixels
const wxSize SRFlipFlopSize(50, 75);

/// Gap between the edge of the flip flop and the labels
const int SRFlipFlopLabelMargin = 3;

/// Pin margin from top and bottom of flip flop
const int SRFlipFlopPinMargin = 4;

/**
 * Constructor
 * @param game the game this gate is in
 */
GateSRFlipFlop::GateSRFlipFlop(Game *game) : Gate(game)
{
	SetSize(SRFlipFlopSize);

	// Create input and output pins
	mInputPinS = std::make_shared<Pin>(GetX() - GetWidth() / 2 - DefaultLineLength, GetY() - GetHeight() / SRFlipFlopPinMargin, true, this);
	mInputPinR = std::make_shared<Pin>(GetX() - GetWidth() / 2 - DefaultLineLength, GetY() + GetHeight() / SRFlipFlopPinMargin, true, this);
	mOutputPinQ = std::make_shared<Pin>(GetX() + GetWidth() / 2 + DefaultLineLength, GetY() - GetHeight() / SRFlipFlopPinMargin, false, this);
	mOutputPinQNot = std::make_shared<Pin>(GetX() + GetWidth() / 2 + DefaultLineLength, GetY() + GetHeight() / SRFlipFlopPinMargin, false, this);
	// Initialize states of Q and Q'
	mOutputPinQ->SetZero();
	mOutputPinQNot->SetOne();
}

/**
 * Draws the SR Flip Flop gate
 * @param graphics the graphics context used to draw the gate
 */
void GateSRFlipFlop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	// Draw the pins
	mInputPinS->Draw(graphics);
	mInputPinR->Draw(graphics);
	mOutputPinQ->Draw(graphics);
	mOutputPinQNot->Draw(graphics);

    // Create a path to draw the gate shape
    auto path = graphics->CreatePath();

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

	// The four corner points of an SR Flip Flop gate
	wxPoint2DDouble p1(x-w/2, y+h/2);   // Bottom left
	wxPoint2DDouble p2(x-w/2, y-h/2);   // Top left
	wxPoint2DDouble p3(x+w/2, y-h/2);   // Top right
	wxPoint2DDouble p4(x+w/2, y+h/2);   // Bottom right

	path.MoveToPoint(p1);
	path.AddLineToPoint(p2);
	path.AddLineToPoint(p3);
	path.AddLineToPoint(p4);
	path.CloseSubpath();

	// Draw the path
	graphics->SetPen(*wxBLACK_PEN);
	graphics->SetBrush(*wxWHITE_BRUSH);
	graphics->DrawPath(path);

	// Set font
	auto font = graphics->CreateFont(15, L"Arial",
								 wxFONTFLAG_BOLD, *wxBLACK);

	graphics->SetFont(font);

	double textWidth, textHeight;
	// Use text width and height to position each letter
	graphics->GetTextExtent(L"S", &textWidth, &textHeight);
	graphics->DrawText(L"S",GetX() - GetWidth() / 2 + SRFlipFlopLabelMargin, mInputPinS->GetY() - textHeight / 2);

	graphics->GetTextExtent(L"R", &textWidth, &textHeight);
	graphics->DrawText(L"R",GetX() - GetWidth() / 2 + SRFlipFlopLabelMargin, mInputPinR->GetY() - textHeight / 2);

	graphics->GetTextExtent(L"Q", &textWidth, &textHeight);
	graphics->DrawText(L"Q",GetX() + GetWidth() / 2 - textWidth - SRFlipFlopLabelMargin, mOutputPinQ->GetY() - textHeight / 2);

	graphics->GetTextExtent(L"Q'", &textWidth, &textHeight);
	graphics->DrawText(L"Q'",GetX() + GetWidth() / 2 - textWidth - SRFlipFlopLabelMargin, mOutputPinQNot->GetY() - textHeight / 2);
}

/**
 * Updates the state of the output pin
 */
void GateSRFlipFlop::UpdateOutputPin()
{
	if (mInputPinR->IsOne() && mInputPinS->IsOne())
	{
		mOutputPinQ->SetUnknown();
		mOutputPinQNot->SetUnknown();
	}
	else if (mInputPinS->IsOne())
	{
		mOutputPinQ->SetOne();
		mOutputPinQNot->SetZero();
	}
	else if (mInputPinR->IsOne())
	{
		mOutputPinQ->SetZero();
		mOutputPinQNot->SetOne();
	}
}

/**
 * Update the position of the pins relative to the gate (for dragging gate)
 */
void GateSRFlipFlop::UpdatePinPositions()
{
	mInputPinS->SetPosition(GetX() - GetWidth() / 2 - DefaultLineLength, GetY() - GetHeight() / SRFlipFlopPinMargin);
	mInputPinR->SetPosition(GetX() - GetWidth() / 2 - DefaultLineLength, GetY() + GetHeight() / SRFlipFlopPinMargin);
	mOutputPinQ->SetPosition(GetX() + GetWidth() / 2 + DefaultLineLength, GetY() - GetHeight() / SRFlipFlopPinMargin);
	mOutputPinQNot->SetPosition(GetX() + GetWidth() / 2 + DefaultLineLength, GetY() + GetHeight() / SRFlipFlopPinMargin);
}

/**
 * Accept a visitor
 * @param visitor the visitor we are accepting
 */
void GateSRFlipFlop::Accept(VisitorBase* visitor)
{
	visitor->VisitGateSRFlipFlop(this);
}

/**
 * Check if we clicked on the Output pin
 * @param x x coordinate of click
 * @param y y coordinate of click
 * @return Pointer to output pin if we clicked it, nullptr otherwise
 */
std::shared_ptr<IDraggable> GateSRFlipFlop::HitDraggable(int x, int y)
{
	if (mOutputPinQ->HitTest(x,y))
	{
		return mOutputPinQ;
	}
	if (mOutputPinQNot->HitTest(x,y))
	{
		return mOutputPinQNot;
	}
	return nullptr;
}

/**
 * Try to connect the pin we are dragging from to each of the input pins on the gate
 * @param pin The pin we are dragging from
 * @param lineEnd The end of the line we are dragging
 * @return True if a connection occurs, false otherwise
 */
bool GateSRFlipFlop::Connect(Pin* pin, wxPoint lineEnd)
{
	return pin->Connect(mInputPinS.get(), lineEnd) || pin->Connect(mInputPinR.get(), lineEnd);
}

/**
 * Get the output pins of the gate
 * @return Pointers to the output pins
 */
std::pair<std::shared_ptr<Pin>, std::shared_ptr<Pin>> GateSRFlipFlop::GetOutputPins()
{
	return std::make_pair(mOutputPinQ,mOutputPinQNot);
}

/**
 * Setter for control points
 * @param show whether or not we should show control points
 * */
void GateSRFlipFlop::SetShowControlPoints(bool show)
{
    mOutputPinQ->SetShowControlPoints(show);
    mOutputPinQNot->SetShowControlPoints(show);
}