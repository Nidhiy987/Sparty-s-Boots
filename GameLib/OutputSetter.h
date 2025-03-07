/**
 * @file OutputSetter.h
 * @author Flower Akaliz
 *
 *
 */

#ifndef PROJECT1_GAMELIB_OUTPUTSETTER_H
#define PROJECT1_GAMELIB_OUTPUTSETTER_H

#include "VisitorBase.h"
#include "SensorOutput.h"

/**
 * A visitor class for setting outputs in sensor
 * */
class OutputSetter : public VisitorBase
{
private:
    /// Integer representing color of product detected
    int mColor = 0;

    /// Integer representing shape of product detected
    int mShape = 0;

    /// Integer representing content of product detected
    int mContent = 0;

public:

    /** Default constructor */
    OutputSetter() = default;

    void VisitSensorOutput(SensorOutput* sensorOutput) override;

    void SetProductProperties(int color, int shape, int content);

};

#endif //PROJECT1_GAMELIB_OUTPUTSETTER_H
