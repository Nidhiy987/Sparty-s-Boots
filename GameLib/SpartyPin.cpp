/**
 * @file SpartyPin.cpp
 * @author Navanidhiy  Achuthan Kumaraguru
 */

#include "pch.h"
#include "SpartyPin.h"

/**
* Constructor for the Pin class.
*
* @param dotX The X-coordinate for the pin's dot position.
* @param dotY The Y-coordinate for the pin's dot position.
* @param input bool (True if input pin, False if Output pin)
* @param owner The item that owns this pin
*/
SpartyPin::SpartyPin(double dotX, double dotY, bool input, Item* owner) : Pin(dotX, dotY, input, owner)
{

}

/**
 * Draw the pin and the line extending from it.
 *
 * @param graphics The graphics context used for drawing.
 */
void SpartyPin::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	Pin::Draw(graphics);
	wxBrush brush;
	wxColour color;
	if (IsZero())
	{
		color = *wxBLACK;
	}
	else if (IsOne())
	{
		color = *wxRED;
	}
	else // States::Unknown
	{
		color = GreyColor;
	}

		mStartX = GetX();
		mStartY = GetY();
        mEndX = GetOwner()->GetX() + GetOwner()->GetWidth() / SpartyWidthFactor;
        mEndY = GetOwner()->GetY();

		// Set the correct color and line width
		graphics->SetPen(wxPen(color, LineWidth));

        double firstLineX = mStartX + DefaultLineLength;
        double firstLineY = SpartyPinBuffer;
		// Draw a line between the two points
		graphics->StrokeLine(firstLineX, mStartY, firstLineX, firstLineY);

        double secondLineX = GetOwner()->GetX() + GetOwner()->GetWidth() / 2 + SpartyPinBuffer;
        double thirdLineY = GetOwner()->GetY();

		// Draw a line between the two points
		graphics->StrokeLine(firstLineX, firstLineY, secondLineX, firstLineY);
		graphics->StrokeLine(secondLineX, firstLineY, secondLineX, thirdLineY);
		graphics->StrokeLine( mEndX, thirdLineY, secondLineX, thirdLineY);

}