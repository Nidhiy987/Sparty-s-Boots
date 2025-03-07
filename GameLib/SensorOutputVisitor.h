/**
 * @file SensorOutputVisitor.h
 * @author Rachel Jansen
 *
 *
 */
 
#ifndef SENSOROUTPUTVISITOR_H
#define SENSOROUTPUTVISITOR_H

#include "VisitorBase.h"
#include "SensorOutput.h"

/**
 * Class to visit sensor output and retrieve the output pin
 */
class SensorOutputVisitor : public VisitorBase {
private:
	/// The output pin of the sensor output object
	std::vector<std::shared_ptr<Pin>> mOutput;

public:
	/**
	 * Visits the sensorOutput and saves the pointer to the output pin
	 * @param sensorOutput The sensor output object we are visiting
	 */
	void VisitSensorOutput(SensorOutput* sensorOutput) { mOutput.push_back(sensorOutput->GetOutputPin()); }

	/**
	 * Gets the output pin of the sensor output object we visited
	 * @return Pointer to the output pin
	 */
	std::vector<std::shared_ptr<Pin>> GetOutput() { return mOutput; }
};



#endif //SENSOROUTPUTVISITOR_H
