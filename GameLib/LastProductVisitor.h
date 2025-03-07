/**
 * @file LastProductVisitor.h
 * @author Attulya Pratap Gupta
 *
 *
 */
 
#ifndef LASTPRODUCTVISITOR_H
#define LASTPRODUCTVISITOR_H

#include "VisitorBase.h"
#include "Product.h"
#include "Conveyor.h"

/**
 * Class for visitor to determine if the last product has passed through the beam
 */
class LastProductVisitor : public VisitorBase
{
private:
	/// Have the products passed through the beam?
    bool mLastProductReached = true;

public:
	/**
	 * Visits product and checks if the product has passed through the beam
	 * @param product Pointer to the product we are visiting
	 */
	void VisitProduct(Product* product) override { mLastProductReached = product->GetPassedBeam(); }

	/**
	 * Getter for if the last product has passed through the beam
	 * @return True if the last product has passed through the beam
	 */
	bool HasLastProductReached() const { return mLastProductReached; }
};

#endif // LASTPRODUCTVISITOR_H
