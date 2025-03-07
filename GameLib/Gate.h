/**
 * @file Gate.h
 * @author Rachel Jansen
 *
 * Base class for gates
 */

#ifndef GATE_H
#define GATE_H

#include "Item.h"
#include "Game.h"
#include "VisitorBase.h"

/**
 * Base class for gates
 */
class Gate : public Item, public std::enable_shared_from_this<Gate>
{
private:
    /// The size of the gate (maybe this should be in each class instead so I can
    /// set the value instead of needing a default here? Some feedback would be
    /// helpful!)
    wxSize mSize = wxSize(0,0);

    /// Position of gate on the screen
    wxPoint mPosition = wxPoint(550,350);

public:

    /// Destructor
    virtual ~Gate() = default;

  /**
   * Sets the size of the gate
   * @param size of the gate
   */
    void SetSize(wxSize size) { mSize = size; }

    /**
     * The X location of the center of the gate
     * @return X location in pixels
     */
    double GetX() const override { return mPosition.x + GetWidth() / 2; }

    /**
     * The Y location of the center of the gate
     * @return Y location in pixels
     */
    double GetY() const override { return mPosition.y + GetHeight() / 2; }

	/**
	 * Set location of the gate
	 * @param x x coordinate in pixels
	 * @param y y coordinate in pixels
	 */
	void SetLocation(double x, double y) override { mPosition = wxPoint(x - GetWidth() / 2,y - GetHeight() / 2); }

    /**
     * The width of the gate
     * @return width in pixels
     */
    double GetWidth() const override { return mSize.GetWidth(); }

  /**
   * The height of the gate
   * @return height in pixels
   */
    double GetHeight() const override { return mSize.GetHeight(); }


	void Update(double elapsed) override;
	bool HitTest(int x, int y) override;

	/**
	 * Constructor
	 * @param game this gate is a part of
	 */
    Gate(Game* game) : Item(game) {}

	/**
	 * Updates the positions of the pins (used for dragging gate)
	 */
	virtual void UpdatePinPositions() {}

	/**
	 * Updates the output pin
	 */
	virtual void UpdateOutputPin() {}

    /**
     * Gate Draw function
     *  @param graphics The graphics context used for drawing.
     * */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}

	/**
	 * Accept a visitor
	 * @param visitor The visitor we accept
	 */
	void Accept(VisitorBase *visitor) override { visitor->VisitGate(this); }

	/**
	 * Get the output pin(s) from a gate
	 * @return a pair containing pointers to the pins. If a gate has only one pin, will return nullptr as second
	 */
	virtual std::pair<std::shared_ptr<Pin>, std::shared_ptr<Pin>> GetOutputPins() = 0;

	/**
	 * Get the input pins for this gate
	 * @return Vector of input pins
	 */
	virtual std::vector<std::shared_ptr<Pin>> GetInputPins() = 0;

};


#endif //GATE_H
