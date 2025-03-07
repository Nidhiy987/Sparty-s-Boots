/**
 * @file PinVisitor.cpp
 * @author Rachel Jansen
 */

#include "pch.h"
#include "PinVisitor.h"

/**
 * Get a list of the input pins connected to an output pin
 * @param pin The output pin we are visiting
 */
void PinVisitor::VisitPin(Pin* pin)
{
	// Skip the first pin (the one that calls Accept)
	if (mFirst)
	{
		mFirst = false;
		return; // Don't add the first pin to the set
	}

	// Add the subsequent connected pins to the set
	mCollectedPins.insert(pin);
}