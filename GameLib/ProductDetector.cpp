/**
 * @file ProductDetector.cpp
 * @author Flower Akaliza
 */

#include "pch.h"
#include "ProductDetector.h"
#include "OutputSetter.h"

/**
 * @brief Visit Product object
 * @param product Pointer to Product object
 *
 * Adds the product to the mProducts vector and moves it if mDistance is non-zero.
 */
void ProductDetector::VisitProduct(Product *product)
{
    mProducts.push_back(product);
}

/**
 * Function to update the beam using the list of products
 * */
void ProductDetector::UpdateBeam()
{
    for(auto product: mProducts)
    {
        if(mBeam->DetectProduct(product->GetYRange()) && !product->GetKicked())
        {
            mBeam->SetOutput(true);
            product->SetDetected(true);
            break;
        }
        else
        {
            mBeam->SetOutput(false);
        	product->SetDetected(false);
        }
    }
}

/**
 * Function to update the sensor using the list of products
 * */
void ProductDetector::UpdateSensor()
{
    OutputSetter setter;
    for(auto product: mProducts)
    {
        int color = static_cast<int>(product->GetColor());
        int shape = static_cast<int>(product->GetShape());
        int content = static_cast<int>(product->GetContent());

        setter.SetProductProperties(color, shape, content);

        if(mSensor->DetectProduct(product->GetYRange(), product->GetY()) && !product->GetKicked())
        {
            mSensor->GetGame()->Accept(&setter);
            break;
        }
    }

}

/**
 * Function to update Sparty using the list of products
 * */
void ProductDetector::UpdateSparty()
{
    for(auto product : mProducts)
    {
        if(mSparty->DetectProduct(product->GetYRange()) && !product->GetKicked())
        {
            product->SetKicked(true);
            product->SetKickSpeed(mSparty->GetKickSpeed());
            break;
        }
    }
}

/**
 * Function to update Scoreboard using the list of products
 */
void ProductDetector::UpdateScoreboard()
{
    if(mSparty->IsConnected())
    {
        // temp variable for score
        int nextLevelScore = mScoreboard->GetLevelScore();
        for(auto product : mProducts)
        {
            if(!product->GetScored() && product->GetPassedBeam())
            {
                if(product->GetKicked() == product->ShouldKick())
                {
                    // Adds to level score if kicked correctly
                    nextLevelScore += mScoreboard->GetGood();

                    // Marks product as scored
                    product->SetScored(true);
                }
                else
                {
                    // Subtract from level score if kicked incorrectly
                    nextLevelScore += mScoreboard->GetBad();

                    // Marks product as scored
                    product->SetScored(true);
                }
                break;
            }
        }


        // Update scoreboard with new score
        mScoreboard->SetLevelScore(nextLevelScore);
    }
}