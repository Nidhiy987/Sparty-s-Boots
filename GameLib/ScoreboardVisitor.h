/**
 * @file ScoreboardVisitor.h
 * @author Emily Nguyen
 *
 *
 */
 
#ifndef SCOREBOARDVISITOR_H
#define SCOREBOARDVISITOR_H

#include "Scoreboard.h"
#include "VisitorBase.h"

/**
 * Class to find Scoreboard as well as keep track of Game Score
 */
class ScoreboardVisitor : public VisitorBase{
private:

    /// Pointer to the scoreboard
	Scoreboard* mScoreboard = nullptr;
public:
	/**
	 * @brief Visit Scorboard object
	 * @param scoreboard Pointer to Scoreboard object
	 */
	void VisitScoreboard(Scoreboard* scoreboard) override { mScoreboard = scoreboard; }

	/**
	 * Get Game Score from Scoreboard
	 * @return the game score
	 */
	int GetGameScore() {return mScoreboard->GetGameScore();}

	/**
	 * End of Level Scoring Sequence
	 */
	void EndLevelScoring() {mScoreboard->AddLevelScoreToGame();}
};



#endif //SCOREBOARDVISITOR_H
