/**
* @file Game.h
 * @author Attulya Pratap Gupta
 *
 * Class to represent the game
 */

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <queue>

#include "Level.h"
#include "IDraggable.h"
#include "Pin.h"

class Level;
class Item;
class Gate;
class Sparty;
class Conveyor;
class ItemFinder;

/// Total delay from end of level to beginning of next level
const double DelayTime = 5.0;

/**
 * Class to represent the game
 */
class Game
{
private:
    int mVirtualWidth = 1150; ///< The width of the virtual window in virtual pixels
    int mVirtualHeight = 800; ///< The height of the virtual window in virtual pixels

    double mScale = 1.0; ///< Amount to scale drawing
    double mXOffset = 0; ///< X offset for drawing
    double mYOffset = 0; ///< Y offset for drawing

    std::vector<std::shared_ptr<Item>> mItems; ///< The items in the game
    std::vector<std::shared_ptr<Item>> mProducts; ///< Temporary list for products in the game
    std::unique_ptr<Level> mLevel; ///< The level loader
    std::shared_ptr<IDraggable> mGrabbedItem; ///< Grabbed item in the game

    /// Whether or not the game should display the control points
    double mShowControlPoints = false;

    /// Max level number for the game
    int mMaxLevelNumber = 1;

	/// Timing for the end of the level and the Level Completed display message in seconds
	double mEndLevelTimer = DelayTime;

	/// Message duration in seconds
	double mMessageDuration = 2.0;

	/// Game score
	int mGameScore = 0;

    /// Counter for number of gates in the game
    int mGateCount = 0;

public:
    Game();
    virtual ~Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void OnLeftDown(int x, int y);
    void OnMouseMove(wxMouseEvent &event);
    void Load(const wxString &filename);
    void AddItem(std::shared_ptr<Item> item);
    void Update(double elapsed);
    void Clear();

    /**
     * Setter for control points
     * @param show whether or not we should show control points
     * */
    void SetShowControlPoints(bool show) { mShowControlPoints = show; }

    /**
     * Get the virtual width of the window
     * @return Virtual width in pixels
     */
    int GetVirtualWidth() const { return mVirtualWidth; }

    /**
     * Get the virtual height of the window
     * @return Virtual height in pixels
     */
    int GetVirtualHeight() const { return mVirtualHeight; }

    void Accept(class VisitorBase* visitor);

    void LoadLevel(int level);
    void MoveItemToEnd(std::shared_ptr<Item> item);
    std::shared_ptr<IDraggable> HitTest(int x, int y);
    void TryToConnect(Pin *pin, wxPoint lineEnd);

    /**
     * Getter for level in the game
     * @return pointer to the level
     * */
    Level* GetLevel() { return mLevel.get();}

	/**
	 * Getter for game score
	 * @return int game score
	 */
	int GetGameScore() { return mGameScore; }

	/**
	 * Sets game score
	 * @param score sets game score to this score
	 */
	void SetGameScore(int score) {mGameScore = score;}

	/**
	 * Getter for end timer
	 * @return double timer
	 */
	double GetEndTimer() { return mEndLevelTimer; }

    /**
     * Getter for gate count
     * @return gate count
     * */
    int GetGateCount() { return mGateCount; }

    /**
     * Helper function to update gate count
     * */
    void UpdateGateCount() { ++mGateCount; }


    bool IsItemVisible(const Item* item) const; ///< Checks if the current item is in frame without modifying it

    std::vector<std::shared_ptr<Gate>> TopologicalSort(std::shared_ptr<Pin> beamPin, std::vector<std::shared_ptr<Pin>> sensorPins);


    bool IsLastProductReached();
    void DetermineMaxLevelNumber();
	int CalculateBonusPoints();
    void AddProduct(std::shared_ptr<Item> item);
    void ProductClear();


};

#endif //GAME_H
