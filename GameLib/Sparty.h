/**
* @file Sparty.h
 * @author Rachel Jansen
 *
 * Class to represent Sparty
 */

#ifndef SPARTY_H
#define SPARTY_H

#include "Item.h"
#include "Level.h"
#include "SpartyPin.h"

class VisitorBase;
/**
 * Class to represent Sparty item
 */
class Sparty : public Item
{
    private:
     /// Duration of the kick
     double mKickDuration = 0.25;

     /// Speed of the kick (pixel per second)
     double mKickSpeed = 0;

     /// Current boot rotation
     double mBootRotation = 0;

     /// Time elapsed since kick started
     double mKickTime = 0;

     /// Whether Sparty is currently kicking
     bool mIsKicking = false;

     /// Previous input pin state
     bool mPreviousPinState = false;

     /// Input pin for Sparty
     std::shared_ptr<SpartyPin> mInputPin;

     /// Image for Sparty background
     std::unique_ptr<wxImage> mSpartyBackImage;

     /// Image for Sparty boot
     std::unique_ptr<wxImage> mSpartyBootImage;

     /// Image for Sparty foreground
     std::unique_ptr<wxImage> mSpartyForegroundImage;

     /// Bitmap for Sparty background
     std::unique_ptr<wxBitmap> mSpartyBackBitmap;

     /// Bitmap for Sparty boot
     std::unique_ptr<wxBitmap> mSpartyBootBitmap;

     /// Bitmap for Sparty foreground
     std::unique_ptr<wxBitmap> mSpartyForegroundBitmap;

     // Private helper methods
     double GetBootPivotX() const;   // X-coordinate of the boot's pivot
     double GetBootPivotY() const;   // Y-coordinate of the boot's pivot

     void LoadImages();

public:
     Sparty(Level* level);

     void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

     void Update(double elapsed) override;

     void XmlLoad(wxXmlNode* node) override;

     /**
      * Get the input pin for Sparty
      * @return Pointer to the input pin
      */
     std::shared_ptr<Pin> GetInputPin() { return mInputPin; }


     /**
      * Check if Sparty should kick the product
      * @param productY The Y coordinate of the product
      * @return True if the product should be kicked, false otherwise
      */
     bool ShouldKickProduct(double productY);

     void SetPin(double x, double y);
     void SetKickDuration(double duration);
     void SetKickSpeed(double speed);
     void Kicking(double elapsed);

     /**
      * Function to check if sparty is kicking
      * @return True if sparty is kicking, false otherwise
      * */
     bool IsKicking() const { return mIsKicking; }

    /**
     * Function to get kick duration
     * @return double kick duration
     * */
     double GetKickDuration() const { return mKickDuration; }

    /**
    * Function to get kick speed
    * @return double kick speed
    * */
     double GetKickSpeed() const { return mKickSpeed; }


     void Accept(VisitorBase *visitor) override;

	 bool Connect(Pin *pin, wxPoint lineEnd) override;

     bool DetectProduct(std::tuple<double, double> range);

     /**
      * Function to check if Sparty has anything connected to it
      * @return if the input pin has a connection or not
      * */
     bool IsConnected() { return !mInputPin->IsUnknown(); }
};

#endif //SPARTY_H
