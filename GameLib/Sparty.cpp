/**
* @file Sparty.cpp
 * @author Rachel Jansen
 */

#include "pch.h"
#include "Sparty.h"
#include "Beam.h"
#include "ProductDetector.h"
#include "VisitorBase.h"

/// Image for the sparty background, what is behind the boot
const std::wstring SpartyBackImage = L"images/sparty-back.png";

/// Image for the Sparty boot
const std::wstring SpartyBootImage = L"images/sparty-boot.png";

/// Image for the Sparty front, what is in front of the boot
const std::wstring SpartyFrontImage = L"images/sparty-front.png";

/// Pivot point for the Sparty boot image as a fraction of
/// the width and height.
wxPoint2DDouble SpartyBootPivot = wxPoint2DDouble(0.5, 0.55);

/// The maximum rotation for Sparty's boot in radians
const double SpartyBootMaxRotation = 0.8;

/// The point in the kick animation when the product
/// actually is kicked. If the kick duration is 0.25,
/// we kick when 0.25 * 0.35 seconds have elapsed.
const double SpartyKickPoint = 0.35;

/// What percentage of the way down Sparty do we find the tip of his boot?
/// This means the location of the boot when kicking is 80% of the
/// way from the top of the Sparty image.
const double SpartyBootPercentage = 0.80;

/**
 * Sparty Constructor
 * @param level The level this is a member of
 */
Sparty::Sparty(Level* level) : Item(level->GetGame())
{
    LoadImages();
    mInputPin = std::make_shared<SpartyPin>(PinSize, PinSize, true, this);
}

/**
 * Load the images for Sparty
 */
void Sparty::LoadImages()
{
    mSpartyBackImage = std::make_unique<wxImage>(SpartyBackImage, wxBITMAP_TYPE_PNG);
    mSpartyBootImage = std::make_unique<wxImage>(SpartyBootImage, wxBITMAP_TYPE_PNG);
    mSpartyForegroundImage = std::make_unique<wxImage>(SpartyFrontImage, wxBITMAP_TYPE_PNG);

    mSpartyBackBitmap = std::make_unique<wxBitmap>(*mSpartyBackImage);
    mSpartyBootBitmap = std::make_unique<wxBitmap>(*mSpartyBootImage);
    mSpartyForegroundBitmap = std::make_unique<wxBitmap>(*mSpartyForegroundImage);
}

/**
 * Draws Sparty
 * @param graphics The graphics context used for making Sparty
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Check if width is not set (or is zero)
    if (GetWidth() <= 0 && mSpartyBackImage && mSpartyBackImage->IsOk())
    {
        // Calculate and set width based on the current height and image aspect ratio
        double aspectRatio = (double)mSpartyBackImage->GetWidth() / mSpartyBackImage->GetHeight();
        SetWidth(GetHeight() * aspectRatio);
    }

    double wid = GetWidth();
    double hit = GetHeight();

    // Draw background
    graphics->DrawBitmap(*mSpartyBackBitmap,
        GetX() - wid/2, GetY() - hit/2,
        wid, hit);


	// Draw boot
	graphics->PushState();
	// Makes the boot draw at the right location
	graphics->Translate(GetX() - wid/2, GetY() - hit/2);

	// Kicking motion for boot
	graphics->Translate(GetBootPivotX(), GetBootPivotY());
	graphics->Rotate(mBootRotation);
	graphics->Translate(-GetBootPivotX(), -GetBootPivotY());
	graphics->DrawBitmap(*mSpartyBootBitmap,
		0, 0,
		wid, hit);
	graphics->PopState();

    // Draw foreground
    graphics->DrawBitmap(*mSpartyForegroundBitmap,
        GetX() - wid/2, GetY() - hit/2,
        wid, hit);


	// Draw input pin
	mInputPin->Draw(graphics);
}



/**
 * Update Sparty
 * @param elapsed Time elapsed since the last update
 */
void Sparty::Update(double elapsed)
{
    ProductDetector detector;
    GetGame()->Accept(&detector);

    bool currentPinState = mInputPin->IsOne();

    // Check for rising edge (0 to 1 transition)
    if (currentPinState && !mPreviousPinState)
    {
        mIsKicking = true;
        mKickTime = mKickDuration;
    }

	// Checks if sparty is supposed to kick
	if(mIsKicking)
	{
        Kicking(elapsed);
        detector.UpdateSparty();
	}

    mPreviousPinState = currentPinState;
}

/**
 * Load the XML for Sparty
 * @param node The XML node to load from
 */
void Sparty::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    node->GetAttribute(L"kick-duration", L"0.25").ToDouble(&mKickDuration);
    node->GetAttribute(L"kick-speed", L"1000").ToDouble(&mKickSpeed);

    // Load pin position
    wxString pinPos = node->GetAttribute(L"pin", L"0,0");
    double pinX, pinY;
    wxSscanf(pinPos, L"%lf,%lf", &pinX, &pinY);
    mInputPin->SetPosition(pinX, pinY);

    // Set height and calculate width to maintain aspect ratio
    double height;
    node->GetAttribute(L"height", L"300").ToDouble(&height);
    SetHeight(height);
    double aspectRatio = (double)mSpartyBackImage->GetWidth() / mSpartyBackImage->GetHeight();
    SetWidth(height * aspectRatio);
}

/**
 * Check if Sparty should kick the product
 * @param productY The Y coordinate of the product
 * @return True if the product should be kicked, false otherwise
 */
bool Sparty::ShouldKickProduct(double productY)
{
    if (!mIsKicking)
    {
        return false;
    }

    double kickY = GetY() - GetHeight() / 2 + GetHeight() * SpartyBootPercentage;
    double tolerance = 5.0; // Adjust this value as needed

    return std::abs(productY - kickY) <= tolerance &&
           mKickTime >= mKickDuration * SpartyKickPoint;
}

/**
 * Sets the pin relative to Sparty
 * @param x x location in pixels
 * @param y y location in pixels
 */
void Sparty::SetPin(double x, double y)
{
    mInputPin->SetPosition(x, y);
}

/**
 * Sets the kick duration for Sparty
 * @param duration the duration of the kick
 */
void Sparty::SetKickDuration(double duration)
{
    mKickDuration = duration;
}

/**
 * Sets the kick speed
 * @param speed the speed of the kick
 */
void Sparty::SetKickSpeed(double speed)
{
    mKickSpeed = speed;
}

/**
 * Gets the x coordinate of the boot pivot point
 * @return the x coordinate of the pivot point for Sparty's boot in pixels
 */
double Sparty::GetBootPivotX() const
{
    return SpartyBootPivot.m_x * GetWidth();
}

/**
 * Gets the y coordinate of the boot pivot point
 * @return the y coordinate of the pivot point for Sparty's boot in pixels
 */
double Sparty::GetBootPivotY() const
{
    return SpartyBootPivot.m_y * GetHeight();
}

/**
 * Handles the animation for kicking a product
 * @param elapsed the time elapsed
 */
void Sparty::Kicking(double elapsed)
{
	if(mKickTime > 0)
	{
		// Subtract time that has elapsed
		mKickTime -= elapsed;

		// Checks if we are done with rotation
		if(mKickTime < 0)
		{
			// Done with rotation,
			// set time and rotation to 0, set IsKicking to false
			mKickTime = 0;
			mBootRotation = 0;
			mIsKicking = false;
		}
		else
		{
			// Time elapsed since rotation
			double kickProgress = mKickDuration - mKickTime;

			// Kicking angle
			mBootRotation = sin(kickProgress * M_PI) * SpartyBootMaxRotation;
		}
	}
}


/**
 * Accept a visitor
 * @param visitor the visitor we are accepting
 */
void Sparty::Accept(VisitorBase* visitor)
{
    visitor->VisitSparty(this);
}

/**
 * Try to connect the pin we are dragging from to Sparty's input pin
 * @param pin The pin we are dragging from
 * @param lineEnd The end of the line we are dragging
 * @return True if a connection occurs, false otherwise
 */
bool Sparty::Connect(Pin* pin, wxPoint lineEnd)
{
	return pin->Connect(mInputPin.get(), lineEnd);
}

/**
 * Function to set output when a product is detected
 * @param range y coordinates of the product
 * @return true if product is detected, false otherwise
 * */
bool Sparty::DetectProduct(std::tuple<double, double> range)
{
    int bootY = int(GetHeight() * SpartyBootPercentage);
    double kickY = GetY() - GetHeight()/2 + bootY;

    if(std::get<0>(range) <= kickY && kickY <= std::get<1>(range))
    {
        return true;
    }
    return false;
}