/**
 * @file Item.cpp
 * @author Flower AKaliza
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"
#include <string>


using namespace std;

/**
 * Constructor for Item
 * @param game The game the item is in
 */
Item::Item(Game* game) : mGame(game)
{
}

/**
 * Destructor
 */
Item::~Item()
{
}



/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode* node)
{
     node->GetAttribute(L"x", L"0").ToDouble(&mX);
     node->GetAttribute(L"y", L"0").ToDouble(&mY);

}

