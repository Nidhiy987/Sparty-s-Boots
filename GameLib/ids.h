/**
 * @file ids.h
 * @author Attulya Pratap Gupta
 *
 *
 */

#ifndef GAME_IDS_H
#define GAME_IDS_H

/**
 * ID values for the menu items and game elements
 */
enum IDs
{
    // Level menu items
    IDM_LEVEL_0 = wxID_HIGHEST + 1,
    IDM_LEVEL_1 = wxID_HIGHEST + 2,
    IDM_LEVEL_2 = wxID_HIGHEST + 3,
    IDM_LEVEL_3 = wxID_HIGHEST + 4,
    IDM_LEVEL_4 = wxID_HIGHEST + 5,
    IDM_LEVEL_5 = wxID_HIGHEST + 6,
    IDM_LEVEL_6 = wxID_HIGHEST + 7,
    IDM_LEVEL_7 = wxID_HIGHEST + 8,
    IDM_LEVEL_8 = wxID_HIGHEST + 9,

    // Gate menu items
    IDM_GATE_OR = wxID_HIGHEST + 10,
    IDM_GATE_AND = wxID_HIGHEST + 11,
    IDM_GATE_NOT = wxID_HIGHEST + 12,
    IDM_GATE_SR_FLIPFLOP = wxID_HIGHEST + 13,
    IDM_GATE_D_FLIPFLOP = wxID_HIGHEST + 14,

    //View Options:
    IDM_VIEW_CONTROLPOINTS = wxID_HIGHEST + 15,
};

#endif //GAME_IDS_H
