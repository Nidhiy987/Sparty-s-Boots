/**
 * @file MainFrame.h
 * @author Rachel Jansen
 *
 * The top level (main) frame of the application
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H

class GameView;
/**z
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// View class for our game
    GameView *mGameView;

public:
    void Initialize();
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose(wxCloseEvent &event);
};


#endif //MAINFRAME_H
