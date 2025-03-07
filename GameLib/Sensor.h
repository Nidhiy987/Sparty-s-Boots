/**
 * @file Sensor.h
 * @author Flower Akaliza
 *
 * Class for the sensor
 */

#ifndef PROJECT1_GAMELIB_SENSOR_H
#define PROJECT1_GAMELIB_SENSOR_H

#include "Item.h"
#include "SensorOutput.h"
#include "Level.h"

/**
 * Class for the sensor
 */
class Sensor : public Item
{
private:

    /// The camera image
    std::unique_ptr<wxImage> mCameraImage;

    /// The bitmap we can display for this camera
    std::unique_ptr<wxBitmap> mCameraBitmap;

    /// The cable image
    std::unique_ptr<wxImage> mCableImage;

    /// The bitmap we can display for this cable
    std::unique_ptr<wxBitmap> mCableBitmap;

    /// Number of outputs the sensor has
    int mNumOutputs = 0;

public:
    /// Default constructor (disabled)
    Sensor() = delete;

    /// Copy constructor (disabled)
    Sensor(const Sensor&) = delete;

    /// Assignment operator
    void operator=(const Sensor&) = delete;

    Sensor(Level* level);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode* node) override;

    void Update(double elapsed) override;

    /**
     * Getter for number of outputs for testing
     * @return number of outputs
     * */
    int GetOutputCount() { return mNumOutputs; }

    void Accept(VisitorBase* visitor) override;

    bool DetectProduct(std::tuple<double, double> range, double y);
};

#endif //PROJECT1_GAMELIB_SENSOR_H
