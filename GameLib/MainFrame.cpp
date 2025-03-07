/**
 * @file MainFrame.cpp
 * @author Rachel Jansen
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"

/**
 * Initialize the MainFrame window
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sparty's Boots",
           wxDefaultPosition, wxSize(1000, 800));

    wxIcon icon("SpartysBoots.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Create a sizer that will lay out child windows vertically
    auto sizer = new wxBoxSizer(wxVERTICAL);

    // Create the view class object as a child of MainFrame
    mGameView = new GameView();
    mGameView->Initialize(this);

    // Add it to the sizer
    sizer->Add(mGameView, 1, wxEXPAND | wxALL);

    // Set the sizer for this frame
    SetSizer(sizer);

    // Layout (place) the child windows.
    Layout();

    // Add a menu bar
    auto menuBar = new wxMenuBar();

    auto fileMenu = new wxMenu();
    auto viewMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File");
    menuBar->Append(viewMenu, L"&View");

    // Add menus using GameView
    mGameView->AddMenus(this, menuBar, fileMenu, viewMenu);

    menuBar->Append(helpMenu, L"&Help");

    SetMenuBar(menuBar);

    // Add a status bar
    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    // Connect events
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}

/**
 * Exit menu option handler
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handler
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to Sparty's Boots!",
                 L"A Game Designed by Team Varistor",
                 wxOK,
                 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
 mGameView->Stop();
 Destroy();
}