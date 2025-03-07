/**
 * @file GateOr.cpp
 * @author Rachel Jansen
 */

#include "pch.h"
#include "GateOr.h"
#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>

#include "VisitorBase.h"

/**
 * Or gate size
 * @return wxSize
 */
const wxSize OrGateSize(75, 50);

/// Input pin offset in pixels
const double orGatePinOffset = 10;

/**
 * Constructor
 * @param game the game this gate is in
 */
GateOr::GateOr(Game* game) : Gate(game)
{
    SetSize(OrGateSize);

    // Create input and output pins
    mInputPin1 = std::make_shared<Pin>(GetX() - GetWidth() / 2 - DefaultLineLength + orGatePinOffset, GetY() + PinSize, true, this);
    mInputPin2 = std::make_shared<Pin>(GetX() - GetWidth() / 2 - DefaultLineLength + orGatePinOffset, GetY() - PinSize, true, this);
    mOutputPin = std::make_shared<Pin>(GetX() + GetWidth() / 2 + DefaultLineLength, GetY(), false, this);
}

/**
 * Draws the Or gate
 * @param graphics the graphics context used to draw the gate
 */
void GateOr::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Create a path to draw the gate shape
    auto path = graphics->CreatePath();

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    // The three corner points of an OR gate
    wxPoint2DDouble p1(x - w / 2, y + h / 2); // Bottom left
    wxPoint2DDouble p2(x + w / 2, y); // Center right
    wxPoint2DDouble p3(x - w / 2, y - h / 2); // Top left

    // Control points used to create the Bezier curves
    auto controlPointOffset1 = wxPoint2DDouble(w * 0.5, 0);
    auto controlPointOffset2 = wxPoint2DDouble(w * 0.75, 0);
    auto controlPointOffset3 = wxPoint2DDouble(w * 0.2, 0);

    // Create the path for the gate
    path.MoveToPoint(p1);
    path.AddCurveToPoint(p1 + controlPointOffset1, p1 + controlPointOffset2, p2);
    path.AddCurveToPoint(p3 + controlPointOffset2, p3 + controlPointOffset1, p3);
    path.AddCurveToPoint(p3 + controlPointOffset3, p1 + controlPointOffset3, p1);
    path.CloseSubpath();

   // Draw the path
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

    // Draw the pins
    mInputPin1->Draw(graphics);
    mInputPin2->Draw(graphics);
    mOutputPin->Draw(graphics);
}

/**
 * Update the position of the pins relative to the gate (for dragging gate)
 */
void GateOr::UpdatePinPositions()
{
	mInputPin1->SetPosition(GetX() - GetWidth() / 2 - DefaultLineLength + orGatePinOffset, GetY() + PinSize);
	mInputPin2->SetPosition(GetX() - GetWidth() / 2 - DefaultLineLength + orGatePinOffset, GetY() - PinSize);
	mOutputPin->SetPosition(GetX() + GetWidth() / 2 + DefaultLineLength, GetY());
}

/**
 * Updates the state of the output pin
 */
void GateOr::UpdateOutputPin()
{
	if ((mInputPin2->IsUnknown()) || (mInputPin1->IsUnknown()))
	{
		mOutputPin->SetUnknown();
	}
	else if ((mInputPin1->IsOne()) || (mInputPin2->IsOne()))
	{
		mOutputPin->SetOne();
	}
	else
	{
		mOutputPin->SetZero();
	}
}

/**
 * Get the output pin of the gate
 * @return Pointer to the output pin
 */
std::pair<std::shared_ptr<Pin>, std::shared_ptr<Pin>> GateOr::GetOutputPins()
{
	return std::make_pair(mOutputPin,nullptr);
}

/**
 * Accept a visitor
 * @param visitor the visitor we are accepting
 */
void GateOr::Accept(VisitorBase* visitor)
{
	visitor->VisitGateOr(this);
}

/**
 * Check if we clicked on the Output pin
 * @param x x coordinate of click
 * @param y y coordinate of click
 * @return Pointer to output pin if we clicked it, nullptr otherwise
 */
std::shared_ptr<IDraggable> GateOr::HitDraggable(int x, int y)
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
bool GateOr::Connect(Pin* pin, wxPoint lineEnd)
{
	return pin->Connect(mInputPin1.get(), lineEnd) || pin->Connect(mInputPin2.get(), lineEnd);
}