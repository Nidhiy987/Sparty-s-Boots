/**
* @file Level.h
 * @author Attulya Pratap Gupta
 *
 * Class to represent a game level
 */

#ifndef LEVEL_H
#define LEVEL_H

#include <memory>

#include "Item.h"

class Item;
class Game;

/// Size of notices displayed on screen in virtual pixels
const int NoticeSize = 100;

/// Color to draw the level notices
const wxColour LevelNoticeColor = wxColour(24, 69, 59);

/// Padding to add to the left and right side of the level
/// notice background rectangle in virtual pixels
const double LevelNoticePadding = 20;

/// seconds in a minute
const int SecondsInMinute = 60;

/// Time between point bonus decrements
const int BonusDecrementInterval = 30;

/// Team feature notice padding width in virtual pixels
const double TeamFeatureNoticePaddingWidth = LevelNoticePadding * 3;

/// Team feature notice padding height in virtual pixels
const double TeamFeatureNoticePaddingHeight = LevelNoticePadding * 5;

/// Max completion bonus
const int MaxCompletionBonus = 75;

/// Starting decrement amount
const int BonusDecrementStart = 5;

/**
 * Class to represent a level in the game
 */
class Level: public wxEvtHandler
{
private:
     /// The width of the level
     long mWidth = 0;

     /// The height of the level
     long mHeight = 0;

     /// The game this level is a part of
     Game* mGame;

	/// level number
	int mLevelNumber = 1;

	/// Duration of message pop up
	const double mMessageDuration = 2;

	/// The amount of time the level has been running
	double mLevelTime = 0;

	/// Color to draw a rectangle enclosing the level notice text
	wxColour mLevelNoticeBackground = wxColour(255, 255, 255, 200);

	/// Time to display on timer
	int mDisplayTime = 0;

	/// Completion bonus points
	int mCompletionBonus = 80;

	/// The list time a bonus was decremented
	int mLastBonusDecrement = 0;

	/// The decrement amount
	int mBonusDecrement = 5;




 public:
     Level(Game* game);

     bool Load(wxXmlNode* node);

	 /**
	  * Get the width of the level
	  * @return Level width in pixels
	  */
     int GetWidth() const { return mWidth; }

     /**
      * Get the height of the level
      * @return Level height in pixels
      */
     int GetHeight() const { return mHeight; }

     /**
      * Get the game this level is a part of
      * @return Pointer to the Game object
      */
     Game* GetGame() { return mGame; }

     /**
      * Load an item from the XML file
      * @param node
      *
      */
     void LoadItem(wxXmlNode* node);
     /**
      * Load Products from the XML file
      * @param conveyornode
      *
      */
     void LoadProducts(wxXmlNode* conveyornode);

     void DrawLevel(std::shared_ptr<wxGraphicsContext> gc, bool levelEnd);
	 void Update(double elapsed);
	 void UpdateCompletionBonus();

	 /**
	  * Getter for the level number
	  * @return The number of the current level
	  */
	 int GetLevelNumber() const { return mLevelNumber; }

	 /**
	  * Setter for the level  number
	  * @param number The number of the current level
	  */
	 void SetLevelNumber(int number) { mLevelNumber = number; }

	 /**
	  * Getter for the time spent in this level
	  * @return The time spent in this level in seconds
	  */
	double GetLevelTime() const { return mLevelTime; }

	/**
	 * Get the completion bonus for the level
	 * @return The completion bonus in points
	 */
	int GetCompletionBonus() const { return mCompletionBonus; }

};

#endif // LEVEL_H