/**
 * @file OutputSetter.cpp
 * @author Flower Akaliza
 */

#include "pch.h"
#include "OutputSetter.h"

/**
 * @brief Visit SensorOutput object
 * @param sensorOutput Pointer to SensorOutput object
 *
 */
void OutputSetter::VisitSensorOutput(SensorOutput *sensorOutput)
{
    sensorOutput->SetOutput(mColor);
    sensorOutput->SetOutput(mShape);
    sensorOutput->SetOutput(mContent);
}
/**
 * Set the integer values for a product's properties
 * @param color integer representing a color
 * @param shape integer representing a shape
 * @param content integer representing some content
 * */
void OutputSetter::SetProductProperties(int color, int shape, int content)
{
    mColor = color;
    mShape = shape;
    mContent = content;
}