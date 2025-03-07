/**
 * @file Sensor.cpp
 * @author Flower Akaliza
 */

#include "pch.h"
#include "Sensor.h"
#include "SensorOutput.h"
#include "Game.h"
#include "ItemFinder.h"
#include "OutputSetter.h"
#include "OutputResetter.h"
#include "ProductDetector.h"
#include <string>

using namespace std;

/// The image file for the sensor cable
const std::wstring SensorCableImage = L"images/sensor-cable.png";

/// The image file for the sensor camera
const std::wstring SensorCameraImage = L"images/sensor-camera.png";

/// How far below Y location of the sensor system is the panel top?
const int PanelOffsetY = 87;

/**
 * How much space for each property
 * @return wxSize
 */
const wxSize PropertySize(100, 40);

/// Range where a product is viewed by the sensor relative
/// to the Y coordinate of the sensor.
const int SensorRange[] = {-40, 15};



/**
 * Sensor Constructor
 * @param level level the sensor is a part of
 */
Sensor::Sensor(Level* level) : Item(level->GetGame())
{
    mCameraImage = make_unique<wxImage>(SensorCameraImage, wxBITMAP_TYPE_ANY);
    mCameraBitmap = make_unique<wxBitmap>(*mCameraImage);
    mCableImage = make_unique<wxImage>(SensorCableImage, wxBITMAP_TYPE_ANY);
    mCableBitmap = make_unique<wxBitmap>(*mCableImage);

    SetWidth(mCableBitmap->GetWidth());
    SetHeight(mCableBitmap->GetHeight());
}

/**
 * Sensor Draw function
 *  @param graphics The graphics context used for drawing.
 * */
void Sensor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    graphics->DrawBitmap(*mCableBitmap,
                         GetX() - GetWidth()/2,
                         GetY() - GetHeight() / 2,
                         GetWidth(),
                         GetHeight());

    graphics->DrawBitmap(*mCameraBitmap,
                         GetX() - GetWidth()/2,
                         GetY() - GetHeight() / 2,
                         GetWidth(),
                         GetHeight());


}

/**
 * Sensor Xml loading function
 * @param node the Xml node to load from
 * */
void Sensor::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

    auto outputs = node->GetChildren();

    double wid = mCableBitmap->GetWidth();
    double x = GetX() + wid/2;
    double offsetY = GetY() + PanelOffsetY;

    // Counter so we know how much to offset our X values by
    mNumOutputs = 0;

    for(auto output = outputs; output; output = output->GetNext())
    {
        auto newOutput = make_shared<SensorOutput>(GetGame());
        double y = offsetY + mNumOutputs * PropertySize.GetHeight();
        newOutput->XmlLoad(output);
        newOutput->SetLocation(x, y);
        GetGame()->AddItem(newOutput);
        ++mNumOutputs;
    }

}

/**
 * Accepts a visitor
 * @param visitor The visitor we accept
 */
void Sensor::Accept(VisitorBase* visitor)
{
    visitor->VisitSensor(this);
}

/**
 * Function to set output when a product is detected
 * @param range y coordinates of the product
 * @param y coordinates of the product
 * @return true if product is detected, false otherwise
 * */
bool Sensor::DetectProduct(tuple<double, double> range, double y)
{
    double topY = GetY() + SensorRange[0];
    double bottomY = GetY() + SensorRange[1];

    bool topInRange = (topY <= get<0>(range) && get<0>(range) <= bottomY);
    bool bottomInRange = (topY <= get<1>(range) && get<1>(range) <= bottomY);
    bool yInRange = (topY <= y && y <= bottomY);

    if(topInRange || bottomInRange || yInRange)
    {
        return true;
    }
    return false;
}

/**
 * Update the sensor
 * @param elapsed The elapsed time since the last update
 */
void Sensor::Update(double elapsed)
{
    OutputResetter resetter;
    GetGame()->Accept(&resetter);

    ProductDetector detector;
    GetGame()->Accept(&detector);

    detector.UpdateSensor();
}