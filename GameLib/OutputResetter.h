/**
 * @file OutputResetter.h
 * @author Flower Akaliza
 *
 *
 */

#ifndef PROJECT1_GAMELIB_OUTPUTRESETTER_H
#define PROJECT1_GAMELIB_OUTPUTRESETTER_H

#include "VisitorBase.h"
#include "SensorOutput.h"

/**
 * Visitor to reset sensor outputs
 * */
class OutputResetter : public VisitorBase
{
private:

public:
    /** Default constructor */
    OutputResetter() = default;

    /**
     * @brief Visit SensorOutput object
     * @param sensorOutput Pointer to SensorOutput object
     *
     */
    void VisitSensorOutput(SensorOutput* sensorOutput) override { sensorOutput->ResetOutput(); }

};

#endif //PROJECT1_GAMELIB_OUTPUTRESETTER_H
