/**
 * @file GateAnd.cpp
 * @author Rachel Jansen
 */

#include "pch.h"
#include "GateAnd.h"

#include "VisitorBase.h"

/// Size of the AND gate in pixels
/// @return and gate size
const wxSize AndGateSize(75, 50);

/// How far the Bezier control points are for the AND
/// gate to the right of ends of the curve as a percentage
/// of the gate height.
const double AndGateControlPointOffset = 0.75;

/// Factor by which to divide the height to get the space between the pins
const double PinSpaceFactor = 4;

/**
 * Constructor
 * @param game the game this gate is in
 */
GateAnd::GateAnd(Game* game) : Gate(game)
{
	SetSize(AndGateSize);

	// Create input and output pins
	mInputPin1 = std::make_shared<Pin>(GetX() - GetWidth() / 2 - DefaultLineLength * 2, GetY() + GetHeight() / PinSpaceFactor, true, this);
	mInputPin2 = std::make_shared<Pin>(GetX() - GetWidth() / 2 - DefaultLineLength * 2, GetY() - GetHeight() / PinSpaceFactor, true, this);
	mOutputPin = std::make_shared<Pin>(GetX() + GetWidth() / 2 + DefaultLineLength / 2, GetY(), false, this);
}

/**
 * Draws the And gate
 * @param graphics the graphics context used to draw the gate
 */
void GateAnd::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Create a path to draw the gate shape
    auto path = graphics->CreatePath();

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

	// The four corner points of an AND gate
	wxPoint2DDouble p1(x- (w * AndGateControlPointOffset), y-h/2);   // Top left
	wxPoint2DDouble p2(x, y-h/2);  // Top right
	wxPoint2DDouble p3(x , y+h/2); // Bottom right
	wxPoint2DDouble p4(x- (w * AndGateControlPointOffset), y+h/2);   // Bottom left

	// Control points
	wxPoint2DDouble controlPointOffset(h * AndGateControlPointOffset, 0);

	// Draw input pins
	mInputPin1->Draw(graphics);
	mInputPin2->Draw(graphics);
	mOutputPin->Draw(graphics);

	// Create the path for the gate shape
	path.MoveToPoint(p1);
	path.AddLineToPoint(p2);
	path.AddCurveToPoint(p2 + controlPointOffset, p3 + controlPointOffset ,p3);
	path.AddLineToPoint(p4);
	path.CloseSubpath();

	// Draw the path
	graphics->SetPen(*wxBLACK_PEN);
	graphics->SetBrush(*wxWHITE_BRUSH);
	graphics->DrawPath(path);

}

/**
 * Updates the state of the output pin
 */
void GateAnd::UpdateOutputPin()
{
	if (mInputPin2->IsUnknown() || mInputPin1->IsUnknown())
	{
		mOutputPin->SetUnknown();
	}
	else if (mInputPin1->IsOne() && mInputPin2->IsOne())
	{
		mOutputPin->SetOne();
	}
	else
	{
		mOutputPin->SetZero();
	}
	mOutputPin->SetLine(mOutputPin.get());
}

/**
 * Update the position of the pins relative to the gate (for dragging gate)
 */
void GateAnd::UpdatePinPositions()
{
	mInputPin1->SetPosition(GetX() - GetWidth() / 2 - DefaultLineLength * 2, GetY() + GetHeight() / PinSpaceFactor);
	mInputPin2->SetPosition(GetX() - GetWidth() / 2 - DefaultLineLength * 2, GetY() - GetHeight() / PinSpaceFactor);
	mOutputPin->SetPosition(GetX() + GetWidth() / 2 + DefaultLineLength / 2, GetY());
}

/**
 * Accept a visitor
 * @param visitor the visitor we are accepting
 */
void GateAnd::Accept(VisitorBase* visitor)
{
	visitor->VisitGateAnd(this);
}

/**
 * Check if we clicked on the Output pin
 * @param x x coordinate of click
 * @param y y coordinate of click
 * @return Pointer to output pin if we clicked it, nullptr otherwise
 */
std::shared_ptr<IDraggable> GateAnd::HitDraggable(int x, int y)
{
	if (mOutputPin->HitTest(x,y))
	{
		return mOutputPin;
	}
	return nullptr;
}

/**
 * Try to connect the pin we are dragging from to each of the input pins on the gate
 * @param pin The pin we are dragging from
 * @param lineEnd The end of the line we are dragging
 * @return True if a connection occurs, false otherwise
 */
bool GateAnd::Connect(Pin* pin, wxPoint lineEnd)
{
	return pin->Connect(mInputPin1.get(), lineEnd) || pin->Connect(mInputPin2.get(), lineEnd);
}

/**
 * Get the output pin of the gate
 * @return Pointer to the output pin
 */
std::pair<std::shared_ptr<Pin>, std::shared_ptr<Pin>> GateAnd::GetOutputPins()
{
	return std::make_pair(mOutputPin,nullptr);
}