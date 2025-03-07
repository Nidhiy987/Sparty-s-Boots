/**
 * @file GateNot.cpp
 * @author Rachel Jansen
 */

#include "pch.h"
#include "GateNot.h"

#include "VisitorBase.h"

/// Size of the Not gate in pixels
/// @return size of the Not gate in pixels
const wxSize NotGateSize(50, 50);

/// circle radius
double circleRadius = 4.0;


/**
 * Constructor
 * @param game the game this gate is in
 */
GateNot::GateNot(Game *game) : Gate(game)
{
	SetSize(NotGateSize);

	// Create input and output pins
	mInputPin = std::make_shared<Pin>(GetX() - GetWidth() / 2 - DefaultLineLength, GetY(), true, this);
	mOutputPin = std::make_shared<Pin>(GetX() + GetWidth() / 2 + DefaultLineLength, GetY(), false, this);
}

/**
 * Draws the Not gate
 * @param graphics the graphics context used to draw the gate
 */
void GateNot::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	// Draw the pins
	mInputPin->Draw(graphics);
	mOutputPin->Draw(graphics);

    // Create a path to draw the gate shape
    auto path = graphics->CreatePath();

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

	// The three corner points of a NOT gate
	wxPoint2DDouble p1(x-w/2, y+h/2);   // Bottom left
	wxPoint2DDouble p2(x+w/2, y);  // Center right
	wxPoint2DDouble p3(x-w/2, y-h/2);   // Top left

	// Create the path for the gate
	path.MoveToPoint(p1);
	path.AddLineToPoint(p2);
	path.AddLineToPoint(p3);
	path.CloseSubpath();

	// Draw the path
	graphics->SetPen(*wxBLACK_PEN);
	graphics->SetBrush(*wxWHITE_BRUSH);
	graphics->DrawPath(path);

	// Draw the circle on the end of the gate
	graphics->DrawEllipse(p2.m_x, p2.m_y - circleRadius, circleRadius * 2, circleRadius * 2);
}

/**
 * Update the position of the pins relative to the gate (for dragging gate)
 */
void GateNot::UpdatePinPositions()
{
	mInputPin->SetPosition(GetX() - GetWidth() / 2 - DefaultLineLength, GetY());
	mOutputPin->SetPosition(GetX() + GetWidth() / 2 + DefaultLineLength, GetY());
}

/**
 * Updates the state of the output pin
 */
void GateNot::UpdateOutputPin()
{
	if (mInputPin->IsUnknown())
	{
		mOutputPin->SetUnknown();
	}
	else if (mInputPin->IsOne())
	{
		mOutputPin->SetZero();
	}
	else
	{
		mOutputPin->SetOne();
	}
}

/**
 * Accept a visitor
 * @param visitor the visitor we are accepting
 */
void GateNot::Accept(VisitorBase* visitor)
{
	visitor->VisitGateNot(this);
}

/**
 * Check if we clicked on the Output pin
 * @param x x coordinate of click
 * @param y y coordinate of click
 * @return Pointer to output pin if we clicked it, nullptr otherwise
 */
std::shared_ptr<IDraggable> GateNot::HitDraggable(int x, int y)
{
	if (mOutputPin->HitTest(x,y))
	{
		return mOutputPin;
	}
	return nullptr;
}

/**
 * Try to connect the pin we are dragging from to the input pin on the gate
 * @param pin The pin we are dragging from
 * @param lineEnd The end of the line we are dragging
 * @return True if a connection occurs, false otherwise
 */
bool GateNot::Connect(Pin* pin, wxPoint lineEnd)
{
	return pin->Connect(mInputPin.get(), lineEnd);
}

/**
 * Get the output pin of the gate
 * @return Pointer to the output pin
 */
std::pair<std::shared_ptr<Pin>, std::shared_ptr<Pin>> GateNot::GetOutputPins()
{
	return std::make_pair(mOutputPin,nullptr);
}