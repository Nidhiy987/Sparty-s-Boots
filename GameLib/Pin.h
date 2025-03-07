/**
 * @file Pin.h
 * @brief Base class to represent a pin in the game.
 *
 * This class represents a pin that can be either an input or an output in the game.
 * It can be drawn, connected to other pins, and has various properties like position,
 * direction, and associated images.
 *
 * @author Navanidhiy Achuthan Kumaraguru
 * @author Rachel Jansen
 */

#ifndef PIN_H
#define PIN_H

#include <set>
#include <wx/colour.h>
#include "IDraggable.h"
#include "Item.h"

/// The diameter to draw the pin in pixels.
static const int PinSize = 10;

/// Maximum offset for Bézier control points when drawing connections.
static constexpr double BezierMaxOffset = 200.0;

/// The width of the line connecting pins, in pixels.
static const int LineWidth = 3;

/// Default length of the line extending from the pin, in pixels.
static const int DefaultLineLength = 20;

/// Default lenght of the cross for control points
static const double CrossSize = 20;

/// Grey color for lines
const wxColour GreyColor = wxColour(128, 128, 128);

/**
 * Class for the pin
 */
class Pin : public IDraggable {
private:

	double mDotX = 0;  ///< X-coordinate of the pin's dot.
	double mDotY = 0;  ///< Y-coordinate of the pin's dot.
	double mLineLength = 0; ///< Length of the pin's length

	/**
	* Direction of the pin.
	* Pins can either be inputs or outputs in the game.
	*/
	enum class Direction {
		Input, ///< The pin is an input.
		Output ///< The pin is an output.
	};

	Direction mLineDirection;  ///< Direction of the pin (input or output).

	/// The possible pin states
	enum class States {One, Zero, Unknown};

	/// The current state of the pin
	States mState = States::Unknown;

	/// List of pins connected to this pin
	std::set<Pin *> mPins;

	/// function for the Bezier Curve
	void DrawBezierCurve(std::shared_ptr<wxGraphicsContext> graphics, wxPoint2DDouble p1, wxPoint2DDouble p4);

    /// function to draw control points
    void DrawCross(std::shared_ptr<wxGraphicsContext> graphics, wxPoint2DDouble point, wxString name);

	/// Owner of the pin
	Item* mOwner = nullptr;

	/// Location of the line end when dragging
	wxPoint mLineEnd = wxPoint(0,0);

	/// Are we dragging the line?
	bool mDragging = false;

    /// Do we show the control point for the connections from the pin?
    bool mShowControlPoints = false;

	/// Are we connected to another pin? Only changes for input pins
	Pin* mConnected = nullptr;

public:
    Pin(double dotX, double dotY, bool input, Item* owner);

	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Get the direction of the pin (input or output).
     * @return The direction of the pin.
     */
    Direction GetDirection() const { return mLineDirection; }

	/**
	 * Sets the position of the pin
	 * @param x X position in pixels
	 * @param y Y position in pixels
	 */
	void SetPosition(double x, double y) { mDotX = x; mDotY = y; }

	/**
	 * Check if the current state pin is One
	 * @return True if state is One, False otherwise
	 */
	bool IsOne() {return mState == States::One;}

	/**
	 * Check if the current state pin is Zero
	 * @return True if state is One, False otherwise
	 */
	bool IsZero() {return mState == States::Zero;}

	/**
	* Check if the current state pin is Unknown
	* @return True if state is One, False otherwise
	*/
	bool IsUnknown() {return mState == States::Unknown; }

	/**
	 * Set state of pin to One
	 */
	void SetOne() {mState = States::One; }

	/**
	 * Set state of pin to Zero
	 */
	void SetZero() {mState = States::Zero; }

	/**
	 * Set state of pin to Unknown
	 */
	void SetUnknown() {mState = States::Unknown;}

    /**
     * Set Length of the pin
     * @param length the length to set for the pin
     * */
    void SetLineLength(double length) { mLineLength = length; }

    /**
     * Setter for control points
     * @param show whether or not we should show control points
     * */
    void SetShowControlPoints(bool show) { mShowControlPoints = show; }

	bool HitTest(double x, double y);
	void SetLocation(double x, double y);
	void Release();
	bool Connect(Pin *pin, wxPoint lineEnd);
	void SetConnected(Pin *connected);
	void SetLine(Pin *line);
	void SetDisconnected(Pin *inputPin);
	void AddPin(Pin *pin);
	void Accept(VisitorBase *visitor);

	/**
	 * The getX constant
	 * @return the X position in pixels
	 */
	double GetX() const { return mDotX; }

	/**
	 * The getY constant
	 * @return the Y position
	 */
	double GetY() const { return mDotY; }

	/**
	 * Tells if pin is an input pin
	 * @return True if input pin, false otherwise
	 */
	bool IsInput() const { return mLineDirection == Direction::Input; }

	/**
	 * Get the output pin this input pin is connected to
	 * @return pointer to the output pin we are connected to
	 */
	Pin* GetConnected() const { return mConnected; }

    /**
	 * Get the owner this pin belongs to
	 * @return pointer to the owner it belongs to
	 */
    Item* GetOwner() const { return mOwner; }


};

#endif // PIN_H
