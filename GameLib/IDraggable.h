/**
 * @file IDraggable.h
 * @author Navanidhiy  Achuthan Kumaraguru
 *
 *
 */
 
#ifndef IDRAGGABLE_H
#define IDRAGGABLE_H

class Pin;

/**
 * Class representing IDraggable
 * */
class IDraggable
{
private:

public:
	/**
	 * Sets the location of the object
	 * @param x X position
	 * @param y Y position
	 */
	virtual void SetLocation(double x, double y) = 0;

	/**
	 * virtual function for release
	 */
	virtual void Release() = 0;

	/**
	 * Virtual function for connecting one pin to another
	 * @param pin The pin we are dragging from
	 * @param mLineEnd the position of the end of the line we are dragging
	 * @return True if connection can be made, False otherwise
	 */
	virtual bool Connect(Pin* pin, wxPoint mLineEnd) = 0;
};


#endif //IDRAGGABLE_H
