/**
 * @file ItemFactory.h
 * @author Attulya Pratap Gupta
 *
 *
 */
 
#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <memory>
#include <string>

class Item;
class Game;

/**
 * Class to create items in the Level Class
 * */
class ItemFactory
{
public:
 static std::shared_ptr<Item> CreateItem(const std::wstring& name, Game* game);
};

#endif // ITEMFACTORY_H