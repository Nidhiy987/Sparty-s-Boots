/**
 * @file SensorOutput.cpp
 * @author Flower Akaliza
 */
#include "pch.h"
#include "SensorOutput.h"
#include "Game.h"
#include "VisitorBase.h"

using namespace std;

/// Color to use for red
/// @return Ohio State Red color
const wxColour OhioStateRed(187, 0, 0);

/// Color to use for green
/// @return MSU green color
const wxColour MSUGreen(24, 69, 59);

/// Color to use for blue
/// @return UofM blue color
const wxColor UofMBlue(0, 39, 76);

/**
 * The background color to draw the sensor panel
 * @return wxColor
 */
const wxColour PanelBackgroundColor(128, 128, 128);

/**
 * How much space for each property
 * @return wxSize
 */
const wxSize PropertySize(100, 40);

/// Size of a shape as a property in virtual pixels
const double PropertyShapeSize = 32;

/// map of properties with their images
const std::map<SensorOutput::Properties, std::wstring> SensorOutput::PropertiesToContentImages = {
    {SensorOutput::Properties::Izzo, L"images/izzo.png"},
    {SensorOutput::Properties::Smith, L"images/smith.png"},
    {SensorOutput::Properties::Football, L"images/football.png"},
    {SensorOutput::Properties::Basketball, L"images/basketball.png"}
};

/// map of possible properties of products
const std::map<std::wstring, SensorOutput::Properties> SensorOutput::NamesToProperties = {
    {L"red", SensorOutput::Properties::Red},
    {L"green", SensorOutput::Properties::Green},
    {L"blue", SensorOutput::Properties::Blue},
    {L"white", SensorOutput::Properties::White},
    {L"square", SensorOutput::Properties::Square},
    {L"circle", SensorOutput::Properties::Circle},
    {L"diamond", SensorOutput::Properties::Diamond},
    {L"izzo", SensorOutput::Properties::Izzo},
    {L"smith", SensorOutput::Properties::Smith},
    {L"basketball", SensorOutput::Properties::Basketball},
    {L"football", SensorOutput::Properties::Football},
    {L"none", SensorOutput::Properties::None},
};
/**
 * Sensor constructor
 * @param game pointer to the game the sensor belongs to
 * */
SensorOutput::SensorOutput(Game *game) : Item(game)
{
    mOutputPin = make_shared<Pin>(PinSize, PinSize, false, this);
    mOutputPin->SetZero();
}

/**
 * Sensor Draw function
 * @param graphics The graphics context used for drawing
 * */
void SensorOutput::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxBrush brush;

    switch(mProperty)
    {
        case Properties::Red:
            brush.SetColour(OhioStateRed);
            break;

        case Properties::Green:
            brush.SetColour(MSUGreen);
            break;

        case Properties::Blue:
            brush.SetColour(UofMBlue);
            break;
        case Properties::White:
            brush.SetColour(*wxWHITE);
            break;
        default:
            brush.SetColour(PanelBackgroundColor);
            break;
    }

    graphics->SetBrush(brush);
    graphics->SetPen(*wxBLACK_PEN);

    graphics->DrawRectangle(GetX(), GetY(), PropertySize.GetWidth(), PropertySize.GetHeight());

    brush.SetColour(*wxWHITE);
    graphics->SetBrush(brush);

    double propertyX = GetX() + PropertySize.GetWidth()/2 - PropertyShapeSize/2;
    double propertyY = GetY() + PropertySize.GetHeight()/2 - PropertyShapeSize/2;

    switch(mProperty)
    {
        case Properties::Square:
            graphics->DrawRectangle(propertyX, propertyY, PropertyShapeSize, PropertyShapeSize);
            break;

        case Properties::Circle:
            graphics->DrawEllipse(propertyX, propertyY, PropertyShapeSize, PropertyShapeSize);
            break;

        case Properties::Diamond:
        {
            double centerX = GetX() + PropertySize.GetWidth()/2;
            double centerY = GetY() + PropertySize.GetHeight()/2;
            const wxPoint2DDouble points[4] = {
                wxPoint(centerX, centerY + PropertyShapeSize/2),
                wxPoint(centerX + PropertyShapeSize/2, centerY),
                wxPoint(centerX, centerY - PropertyShapeSize/2),
                wxPoint(centerX - PropertyShapeSize/2, centerY)
            };
            graphics->DrawLines(4, points);
            break;
        }
        case Properties::Izzo:
        case Properties::Smith:
        case Properties::Basketball:
        case Properties::Football:
        {
            graphics->DrawBitmap(*mContentBitmap, propertyX, propertyY, PropertyShapeSize, PropertyShapeSize);
            break;
        }
        default:
            break;
    }

    mOutputPin->SetPosition(GetX() + PropertySize.GetWidth() + DefaultLineLength, GetY() + PropertySize.GetHeight()/2);
    mOutputPin->Draw(graphics);

}

/**
 * Loads the attributes of the sensor output
 *
 * @param node the Xml node we are loading the sensor output from
 */
void SensorOutput::XmlLoad(wxXmlNode *node)
{
    wxString name = node->GetName();

    if(Product::NamesToProperties.find(name.ToStdWstring()) != Product::NamesToProperties.end())
    {
        mProperty = SensorOutput::NamesToProperties.at(name.ToStdWstring());

        switch(mProperty)
        {
            case Properties::Izzo:
            case Properties::Smith:
            case Properties::Basketball:
            case Properties::Football:
            {
                mContentImage = make_unique<wxImage>(SensorOutput::PropertiesToContentImages.at(mProperty), wxBITMAP_TYPE_PNG);
                mContentBitmap = make_unique<wxBitmap>(*mContentImage);
                break;
            }
            default:
                break;
        }
    }
}

/**
 * Function to set output
 * @param property integer representing a product property
 * */
void SensorOutput::SetOutput(int property)
{
    int outputProperty = static_cast<int>(mProperty);

    if(property == outputProperty)
    {
        mOutputPin->SetOne();
    }

}
/**
 * Accepts a visitor
 * @param visitor The visitor we accept
 */
void SensorOutput::Accept(VisitorBase* visitor)
{
    visitor->VisitSensorOutput(this);
}

/**
 * Check if we clicked on the Output pin
 * @param x x coordinate of click
 * @param y y coordinate of click
 * @return Pointer to output pin if we clicked it, nullptr otherwise
 */
std::shared_ptr<IDraggable> SensorOutput::HitDraggable(int x, int y)
{
	if (mOutputPin->HitTest(x,y))
	{
		return mOutputPin;
	}
	return nullptr;
}