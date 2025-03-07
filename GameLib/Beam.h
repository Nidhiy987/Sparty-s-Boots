/**
 * @file Beam.h
 * @author Flower Akaliza
 *
 *  The class for the beam
 */

#ifndef PROJECT1_GAMELIB_BEAM_H
#define PROJECT1_GAMELIB_BEAM_H

#include "Item.h"
#include "Level.h"
#include "Pin.h"

/**
 * The class for the beam
 */
class Beam : public Item
{
private:
    /// The underlying item image
    std::unique_ptr<wxImage> mBeamGreenImage;

    /// The image we can display for this item
    std::unique_ptr<wxBitmap> mBeamGreenBitmap;

    /// Mirrored green beam image bitmap
    std::unique_ptr<wxBitmap> mGreenMirroredBitmap;

    /// Mirrored red beam image bitmap
    std::unique_ptr<wxBitmap> mRedMirroredBitmap;

    /// The underlying item image
    std::unique_ptr<wxImage> mBeamRedImage;

    /// The image we can display for this item
    std::unique_ptr<wxBitmap> mBeamRedBitmap;

    double mSender = 0;     ///< how much to the left to place the beam sender image
    bool mOutput = false;   ///< return True if beam is broke, false otherwise

    /// Output pin for the beam
    std::shared_ptr<Pin> mOutputPin;

public:
    /// Default constructor (disabled)
    Beam() = delete;

    /// Copy constructor (disabled)
    Beam(const Beam&) = delete;

    /// Assignment operator
    void operator=(const Beam&) = delete;

    Beam(Level* level);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode* node) override;

    void Update(double elapsed) override;

    /**
     * Gets the value of output
     * @return mOuput
     */
    bool GetOutput() { return mOutput; }

    void SetOutput(bool output);
    /**
     * Set the sender value
     * @return sender The sender value of the beam
     * */
    double GetSender() { return mSender; }

    bool DetectProduct(std::tuple<double, double> range);

    void Accept(VisitorBase *visitor) override;

	std::shared_ptr<IDraggable> HitDraggable(int x, int y) override;

	/**
	* Getter for the output pin
	* @return Pointer to the output pin
	*/
	std::shared_ptr<Pin> GetOutputPin() { return mOutputPin; }

    /**
     * Setter for control points
     * @param show whether or not we should show control points
     * */
    void SetShowControlPoints(bool show) override { mOutputPin->SetShowControlPoints(show);}
};

#endif //PROJECT1_GAMELIB_BEAM_H
