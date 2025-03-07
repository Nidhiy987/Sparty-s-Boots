/**
 * @file ItemFactory.cpp
 * @author Attulya Pratap Gupta
 */
 
#include "pch.h"
#include "ItemFactory.h"
#include "Conveyor.h"
#include "Sensor.h"
#include "Beam.h"
#include "Sparty.h"
#include "Scoreboard.h"
#include "Product.h"
#include "Game.h"

/**
 *
 * @param name the name of the item to add
 * @param game the game this item is in
 * @return pointer to the item or nullptr if the name is not the name of an item in the game
 */
std::shared_ptr<Item> ItemFactory::CreateItem(const std::wstring& name, Game* game)
{
     if (name == L"conveyor")
     {
         return std::make_shared<Conveyor>(game->GetLevel());
     }
     else if (name == L"sensor")
     {
         return std::make_shared<Sensor>(game->GetLevel());
     }
     else if (name == L"beam")
     {
         return std::make_shared<Beam>(game->GetLevel());
     }
     else if (name == L"sparty")
     {
         return std::make_shared<Sparty>(game->GetLevel());
     }
     else if (name == L"scoreboard")
     {
         return std::make_shared<Scoreboard>(game->GetLevel());
     }
     else if (name == L"product")
     {
         return std::make_shared<Product>(game->GetLevel());
     }

     return nullptr;
}