/**
 * @file BeamVisitor.h
 * @author Rachel Jansen
 *
 *
 */
 
#ifndef BEAMVISITOR_H
#define BEAMVISITOR_H

#include "Beam.h"
#include "VisitorBase.h"

/**
 * Class to visit beam and get the output pin
 */
class BeamVisitor : public VisitorBase {
private:
	/// Output pin of beam
	std::shared_ptr<Pin> mOutput;

public:
	/**
	* Visits the beam and saves the pointer to the output pin
	* @param beam The beam object we are visiting
	*/
	void VisitBeam(Beam* beam) { mOutput = beam->GetOutputPin(); }

	/**
	* Gets the output pin of the beam object we visited
	* @return Pointer to the output pin
	*/
	std::shared_ptr<Pin> GetOutputPin() { return mOutput; }

};



#endif //BEAMVISITOR_H
