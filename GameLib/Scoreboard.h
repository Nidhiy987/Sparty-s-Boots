/**
 * @file Scoreboard.h
 * @author Emily Nguyen
 *
 * Class for the scoreboard
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Item.h"
#include <string>
class Level;

/**
 * Class for the scoreboard
 */
class Scoreboard : public Item
{
private:
    /// Points awarded for kicking an object you are supposed to kick
    int mGood = 10;
    /// Points awarded for kicking an object you aren't supposed to kick
    int mBad = 0;
    /// Instructions given for the level
    std::wstring mInstructions;
    /// The score for the current level
    int mLevelScore = 0;
    /// The score for the game
    int mGameScore = 0;
	/// Perfect score for level 7
	int mPerfectScore7 = 60;
	/// Perfect score for level 8
	int mPerfectScore8 = 80;
	/// Whether the level was perfectly scored
	bool mPerfectScore = false;
	/// Whether the level score has been added to game score
	bool mScoreAdded = false;

public:
    /// Default constructor (disabled)
    Scoreboard() = delete;

    /// Copy constructor (disabled)
    Scoreboard(const Scoreboard&) = delete;

    /// Assignment operator
    Scoreboard& operator=(const Scoreboard&) = delete;

    /// Constructor for Scoreboard
    Scoreboard(Level* level);

	/**
	 * Get Good scoring
	 * @return integer for good scoring
	 */
	int GetGood() {return mGood;}

	/**
	 * Get Bad scoring
	 * @return integer for bad scoring
	 */
	int GetBad() {return mBad;}

    /**
     * Get Level Score
     * @return integer for level score
     */
    int GetLevelScore() {return mLevelScore;}

    /**
     * Get Game Score
     * @return integer for game score
     */
    int GetGameScore() {return mGameScore;}

	/**
	 * Get Perfect Score
	 * @return bool whether level was scored perfectly
	 */
	bool GetPerfectScore() {return mPerfectScore;}

	/**
	 * Set Perfect Score
	 * @param perfect whether level was scored perfectly
	 */
	void SetPerfectScore(bool perfect) {mPerfectScore = perfect;}

    /**
     * Set Level Score
     * @param score score we want to set to
     */
    void SetLevelScore(int score) {mLevelScore = score;}

	/**
	 * Set Game Score
	 * @param score score we want to set to
	 */
	void SetGameScore(int score) {mGameScore = score;}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed) override;

    void XmlLoad(wxXmlNode* node) override;

    void Accept(VisitorBase* visitor) override;
    void AddLevelScoreToGame();

    /**
     * Getter for instructions
     * @return wstring
     * */
    std::wstring GetInstructions() {return mInstructions;}
};


#endif //SCOREBOARD_H
