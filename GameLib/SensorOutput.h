/**
 * @file SensorOutput.h
 * @author Flower Akaliza
 *
 * Class to represent the sensor output
 */

#ifndef PROJECT1_GAMELIB_SENSOROUTPUT_H
#define PROJECT1_GAMELIB_SENSOROUTPUT_H

#include "Item.h"
#include "Pin.h"
#include "Game.h"
#include "Product.h"
#include "VisitorBase.h"

/**
 * Class to represent the sensor output
 */
class SensorOutput : public Item
{

private:

    /// The possible product properties
    enum class Properties
    {
        None, Red, Green, Blue, White, Square, Circle, Diamond,
        Izzo, Smith, Football, Basketball
    };

    /// The type of the output
    Properties mProperty = Properties::None;

    /// A list of the output pins
    std::shared_ptr<Pin> mOutputPin;

    /// Content image for the outputs Izzo, Smith, Football, and Basketball
    std::unique_ptr<wxImage> mContentImage;

    /// Content bitmap for outputs Izzo, Smith, Football, and Basketball
    std::unique_ptr<wxBitmap> mContentBitmap;

public:

    SensorOutput(Game* game);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode* node) override;
    void SetOutput(int property);

    /** Function to reset the output*/
    void ResetOutput() { mOutputPin->SetZero(); }

    /**
     * Getter for property of the sensor output
     * @return property of the sensor output
     * */
    Properties GetProperty() {return mProperty;}

    void Accept(VisitorBase *visitor) override;
	std::shared_ptr<IDraggable> HitDraggable(int x, int y) override;
	/**
	 * Getter for the output pin
	 * @return Pointer to the output pin
	 */
	std::shared_ptr<Pin> GetOutputPin() { return mOutputPin; }

	/// Mapping from content properties to their associated image
    static const std::map<Properties, std::wstring> PropertiesToContentImages;

    /// Mapping from the XML strings for properties to the Properties enum
    static const std::map<std::wstring, Properties> NamesToProperties;

    /**
     * Setter for control points
     * @param show whether or not we should show control points
     * */
    void SetShowControlPoints(bool show) override { mOutputPin->SetShowControlPoints(show);}

};

#endif //PROJECT1_GAMELIB_SENSOROUTPUT_H
