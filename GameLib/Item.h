/**
 * @file Item.h
 * @author Flower Akalzia
 *
 *
 */

#ifndef GAME_GAMELIB_ITEM_H
#define GAME_GAMELIB_ITEM_H

class Game;
class Level;
class Pin;
#include "VisitorBase.h"
#include "IDraggable.h"


/**
 * Class representing an item in the game
 */
class Item : public IDraggable
{
private:
    /// The game this item is contained in
    Game* mGame;
    /// The level this item is contained in
    Level* mLevel;

    // Item location in the game
    double mX = 0; ///< X location for the center of the item
    double mY = 0; ///< Y location for the center of the item
    double mWidth = 0; ///< Width of the item
    double mHeight = 0; ///< Height of the item
    double mAspectRatio = 1.00; ///< default aspect ratio

public:
    virtual ~Item();

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item&) = delete;

    /// Assignment operator
    void operator=(const Item&) = delete;
    /**
     * The X location of the item
     * @return X location in pixels
     */
    virtual double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    virtual double GetY() const { return mY; }
    /**
	   * The width of the item
	   * @return width in pixels
	   */
    virtual double GetWidth() const { return mWidth; }

    /**
     * The height of the item
     * @return height in pixels
     */
    virtual double GetHeight() const { return mHeight; }

    /**
     * The game the item belongs to
     * @return pointer to game
     */
    Game* GetGame() { return mGame; }
    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
	void SetLocation(double x, double y) override { mX = x; mY = y; }


    /**
     * Set the width of the item
     * @param width Width in pixels
     */
    void SetWidth(double width) { mWidth = width; }

    /**
    * Set the height of the item
    * @param height Height in pixels
    */
    void SetHeight(double height) { mHeight = height; }

    /**
    * Pure virtual function to draw Item
    * @param graphics The graphics context used for drawing
    */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
    * Function to check if an item has been clicked on
    * @param x The x-coordinate of hit spot
     * @param y The y-coordinate of hit spot
     * @return false
    */
    virtual bool HitTest(int x, int y) { return false; }

    virtual void XmlLoad(wxXmlNode* node);

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    /**
     * Get the level this item is contained in
     * @return Pointer to the Level object
     */
    Level* GetLevel() const { return mLevel; }

    /**
     * Set the level for this item
     * @param level Pointer to the Level object
     */
    void SetLevel(Level* level) { mLevel = level; }

	/**
	 * Sets the aspect ratio of the item
	 * @param aspectRatio the aspect ratio of the item
	 */
	void SetAspectRatio(double aspectRatio) { mAspectRatio = aspectRatio; }

	/**
	 * Accept a visitor
	 * @param visitor the visitor we are accepting
	 */
    virtual void Accept(VisitorBase* visitor) = 0;

	/**
	 * Hit test for pins on gates
	 * @param x x coordinate of click
	 * @param y y coordinate of click
	 * @return Pointer to pin if clicked, nullptr otherwise
	 */
	virtual std::shared_ptr<IDraggable> HitDraggable(int x, int y) { return nullptr; }

	/**
	 * Used to release a dragged line
	 */
	void Release() override {}

	/**
	 * Function for connecting pins on items that contain pins
	 * @param pin The pin we are dragging from
	 * @param lineEnd The end of the line we are dragging
	 * @return True if a connection is made between two pins
	 */
	bool Connect(Pin* pin, wxPoint lineEnd) override { return false; }

    /**
     * Setter for control points
     * @param show whether or not we should show control points
     * */
    virtual void SetShowControlPoints(bool show) {}


protected:
    Item(Game* game);
};

#endif //GAME_GAMELIB_ITEM_H
