/**
 * @file ItemFinder.cpp
 * @author Flower Akaliza
 */

#include "pch.h"
#include "ItemFinder.h"

/**
 * @brief Visit Product object
 * @param product Pointer to Product object
 *
 * Adds the product to the mProducts vector and moves it if mDistance is non-zero.
 */
void ItemFinder::VisitProduct(Product *product)
{
	mProducts.push_back(product);
}

/**
 * @brief Reset all products to their initial positions on the conveyor
 * @param conveyor Pointer to the conveyor the products are on
 */
void ItemFinder::ResetProducts(Conveyor *conveyor)
{
	for (auto product : mProducts)
	{
		product->Reset(conveyor);
	}
	mProducts.clear();
}

/**
 * Moves the products on the conveyor belt
 * @param elapsed The time elapsed
 * @param speed The speed of the conveyor
 */
void ItemFinder::MoveProducts(double elapsed, double speed)
{
	for (auto product : mProducts)
	{
		product->Move(elapsed, speed);
	}
}
