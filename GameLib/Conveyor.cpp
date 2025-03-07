/**
 * @file Conveyor.cpp
 * @author Attulya Pratap Gupta
 *
 *
 */
#include "pch.h"
#include "Conveyor.h"
#include "Game.h"
#include "ItemFinder.h"
#include "VisitorBase.h"

using namespace std;

/// Image for the background (base) of the conveyor
const std::wstring ConveyorBackgroundImage = L"images/conveyor-back.png";

/// Image for the conveyor belt
const std::wstring ConveyorBeltImage = L"images/conveyor-belt.png";

/// Image for the conveyor control panel when stopped.
const std::wstring ConveyorPanelStoppedImage = L"images/conveyor-switch-stop.png";

/// Image for the conveyor control panel when started.
const std::wstring ConveyorPanelStartedImage = L"images/conveyor-switch-start.png";

/// Rectangle representing the location of the start button relative to the panel
/// @return the location of the rectangle representing the start button
const wxRect StartButtonRect(35, 29, 95, 36);

/// Rectangle representing the location of the stop button relative to the panel
/// /// @return the location of the rectangle representing the stop button
const wxRect StopButtonRect(35, 87, 95, 36);

/**
 * Constructor
 * @param level The level this conveyor belongs to
 */
Conveyor::Conveyor(Level* level) : Item(level->GetGame())
{
    mBackgroundImage = make_unique<wxImage>(ConveyorBackgroundImage, wxBITMAP_TYPE_PNG);
    mBackgroundBitmap = make_unique<wxBitmap>(*mBackgroundImage);

    mBeltImage = make_unique<wxImage>(ConveyorBeltImage, wxBITMAP_TYPE_PNG);
    mBeltBitmap = make_unique<wxBitmap>(*mBeltImage);

    mPanelStoppedImage = make_unique<wxImage>(ConveyorPanelStoppedImage, wxBITMAP_TYPE_PNG);
    mPanelStoppedBitmap = make_unique<wxBitmap>(*mPanelStoppedImage);

    mPanelStartedImage = make_unique<wxImage>(ConveyorPanelStartedImage, wxBITMAP_TYPE_PNG);
    mPanelStartedBitmap = make_unique<wxBitmap>(*mPanelStartedImage);
}

/**
 * Destructor
 */
Conveyor::~Conveyor()
{
}

/**
 * Draw the conveyor
 * @param graphics The graphics context to draw on
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Calculate width based on aspect ratio if not set
    if (GetWidth() <= 0 && mBackgroundImage && mBackgroundImage->IsOk())
    {
        double aspectRatio = static_cast<double>(mBackgroundImage->GetWidth()) / mBackgroundImage->GetHeight();
        SetWidth(GetHeight() * aspectRatio);
    }

    // Draw the background
    graphics->DrawBitmap(*mBackgroundBitmap,
        mInitialX - GetWidth() / 2,
        mInitialY - GetHeight() / 2,
        GetWidth(),
        GetHeight());

    // Set up clipping region for the belt
    graphics->PushState();
    graphics->Clip(mInitialX - GetWidth() / 2, mInitialY - GetHeight() / 2, GetWidth(), GetHeight());

    // Calculate belt dimensions
    double beltWidth = mBeltImage->GetWidth();
    double beltHeight = mBeltImage->GetHeight();
    double scaleFactor = GetHeight() / beltHeight;
    beltWidth *= scaleFactor;
    beltHeight *= scaleFactor;

    // Calculate belt position for animation
    double beltY = mInitialY - GetHeight() / 2 - mBeltPosition * scaleFactor;
    while (beltY > mInitialY - GetHeight() / 2)
    {
        beltY -= beltHeight;
    }

    // Draw the belt
    while (beltY < mInitialY + GetHeight() / 2)
    {
        graphics->DrawBitmap(*mBeltBitmap,
            mInitialX - GetWidth() / 2,
            beltY,
            beltWidth, beltHeight);
        beltY += beltHeight;
    }

    // Remove clipping
    graphics->PopState();

    // Draw the appropriate panel image
    wxBitmap* panelBitmap = mIsRunning ? mPanelStartedBitmap.get() : mPanelStoppedBitmap.get();
    graphics->DrawBitmap(*panelBitmap,
                         mInitialX + mPanelLocation.x,
                         mInitialY + mPanelLocation.y,
                         panelBitmap->GetWidth(),
                         panelBitmap->GetHeight());
}

/**
 * Update the conveyor
 * @param elapsed The elapsed time since the last update
 */
void Conveyor::Update(double elapsed)
{
    if (mIsRunning)
    {
        mBeltPosition += mSpeed * elapsed;

        // Wrapping the belt position to create a continuous animation
        double beltHeight = mBeltImage->GetHeight();
        while (mBeltPosition >= beltHeight)
        {
            mBeltPosition -= beltHeight;
        }

        // Move the products
        auto visitor = std::make_shared<ItemFinder>();
        GetGame()->Accept(visitor.get());
        visitor->MoveProducts(elapsed, mSpeed);
    }
}
/**
 * Load the XML for the conveyor
 * @param node The XML node to load from
 */
void Conveyor::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    mInitialX = GetX();
    mInitialY = GetY();
    mInitialBeltPosition = mBeltPosition;

    node->GetAttribute(L"speed", L"0").ToDouble(&mSpeed);
    node->GetAttribute(L"height", L"0").ToDouble(&mHeight);
    SetHeight(mHeight);

    // Calculate width based on aspect ratio
    if (mBackgroundImage && mBackgroundImage->IsOk())
    {
        double aspectRatio = static_cast<double>(mBackgroundImage->GetWidth()) / mBackgroundImage->GetHeight();
        SetWidth(mHeight * aspectRatio);
    }

    wxString panelPos = node->GetAttribute(L"panel", L"0,0");
    double panelX, panelY;
    wxSscanf(panelPos, L"%lf,%lf", &panelX, &panelY);
    SetPanel(panelX, panelY);
}

/**
 * Start the conveyor
 */
void Conveyor::Start()
{
    ResetProducts();
    mBeltPosition = mInitialBeltPosition;
    mIsRunning = true;
}

/**
 * Stop the conveyor
 */
void Conveyor::Stop()
{
    mIsRunning = false;
}

/**
 * Reset the belt position and the products to their original position
 */
void Conveyor::ResetProducts()
{
    auto visitor = std::make_shared<ItemFinder>();
    GetGame()->Accept(visitor.get());
    visitor->ResetProducts(this);
}

/**
 * Test if we have clicked on the conveyor
 * @param x X location on the game to test
 * @param y Y location on the game to test
 * @return false
 */
bool Conveyor::HitTest(int x, int y)
{
	OnClick(x,y);
    return false;
}

/**
 * Handle a click on the conveyor
 * @param x X location clicked on
 * @param y Y location clicked on
 */
void Conveyor::OnClick(int x, int y)
{
    // Convert to conveyor panel coordinates
    int testX = x - (GetX() + mPanelLocation.x);
    int testY = y - (GetY() + mPanelLocation.y);

    if (StartButtonRect.Contains(testX, testY))
    {
        Start();
    }
    else if (StopButtonRect.Contains(testX, testY))
    {
        Stop();
    }
}

/**
 * Get the Y location to place a product
 * @param placement The placement value from the XML
 * @return Y location for the product
 */
double Conveyor::GetProductY(double placement) const
{
    return GetY() - placement;
}

/**
 * Sets the location of the panel
 * @param x x coordinate of the panel in pixels
 * @param y y coordinate of the panel in pixels
 */
void Conveyor::SetPanel(double x, double y)
{
    mPanelLocation = wxPoint(x, y);
}

/**
 * Accept a visitor
 * @param visitor the visitor we accept
 */
void Conveyor::Accept(VisitorBase* visitor)
{
    visitor->VisitConveyor(this);
}
