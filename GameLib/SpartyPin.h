/**
 * @file SpartyPin.h
 * @brief class to represent a pin for Sparty in the game.
 *
 * @author Navanidhiy Achuthan Kumaraguru
 */
#ifndef SPARTYPIN_H
#define SPARTYPIN_H

#include "Pin.h"
#include <wx/graphics.h>
#include <memory>


/// Space between the top of the screen and the SpartyPin line
const int SpartyPinBuffer = 10;

/// Factor of width of sparty image bitmap to the visible portion of sparty
const int SpartyWidthFactor = 8;


/**
 * Class representing input pin for Sparty
 * */
class SpartyPin : public Pin{
private:
    /// x-coordinate for start of connection
    double mStartX = 0;
    /// y- coordinate for start of connection
    double mStartY = 0;

    /// x-coordinate for end of connection
    double mEndX = 0;

    /// y-coordinate for end of connection
    double mEndY = 0;



public:
	SpartyPin(double dotX, double dotY, bool input, Item* owner);
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif // SPARTYPIN_H
