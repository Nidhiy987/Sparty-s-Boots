/**
 * @file GameView.h
 * @author Navanidhiy  Achuthan Kumaraguru
 *
 *
 */

#ifndef GAMEVIEW_H
#define GAMEVIEW_H


#include <memory>
#include <wx/timer.h>
#include <wx/stopwatch.h>
#include "Game.h"


class Item;

/**
 * Class representing game view
 * */
class GameView : public wxWindow
{
private:
    /// The game object that contains all the game logic and data
    Game mGame;

    /// The item currently being dragged or interacted with
    std::shared_ptr<Item> mGrabbedItem;

    /// The timer used for game updates and animations
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last recorded stopwatch time
    long mTime = 0;

    /// Optional: Image or visual asset for game interactions (e.g., trash bin or other UI elements)
    std::unique_ptr<wxBitmap> mVisualAsset;

    bool mShowOutlines = false; ///< Outline game objects for debugging?

    void OnPaint(wxPaintEvent& event);

    /// Current level
	int mLevel = 0;


public:
  //  void LoadLevel(int level);
    void Initialize(wxFrame* mainFrame);

    void AddMenus(wxFrame* mainFrame, wxMenuBar* menuBar, wxMenu* fileMenu, wxMenu* viewMenu);

    /**
     * Stops the game timer for cleanup when closing the window.
     */
    void Stop() { mTimer.Stop(); }

    // Event handlers for mouse and paint events
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftDoubleClick(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnLevelOption(wxCommandEvent& event);
    void OnGateOption(wxCommandEvent& event);
    void OnViewControlPoints(wxCommandEvent& event);

};


#endif //GAMEVIEW_H
