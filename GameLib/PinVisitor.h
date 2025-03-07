/**
 * @file PinVisitor.h
 * @author Rachel Jansen
 *
 *
 */
 
#ifndef PINVISITOR_H
#define PINVISITOR_H

#include <set>
#include "VisitorBase.h"

/**
 * Class to visit pins and get the set of pins they are connected to
 */
class PinVisitor : public VisitorBase {
private:
	/// List of pins attached to this output
	std::set<Pin*> mCollectedPins;
	/// Flag to track the first pin visit
	bool mFirst = true;

public:
	void VisitPin(Pin* pin) override;

	/**
	 * Getter for the list of collected pins
	 * @return A set containing the list of collected pins
	 */
	const std::set<Pin*>& GetCollectedPins() const { return mCollectedPins; }

};



#endif //PINVISITOR_H
