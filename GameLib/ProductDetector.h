/**
 * @file ProductDetector.h
 * @author Flower Akaliza
 *
 *
 */

#ifndef PROJECT1_GAMELIB_PRODUCTDETECTOR_H
#define PROJECT1_GAMELIB_PRODUCTDETECTOR_H

#include "VisitorBase.h"
#include "Sparty.h"
#include "Beam.h"
#include "Sensor.h"
#include "OutputSetter.h"
#include "Scoreboard.h"

/**
 * @class ProductDetector
 * @brief A visitor class for finding and updating specific items in the game.
 *
 * This class inherits from VisitorBase and implements visitor methods for various game objects.
 * It is used to find Sparty, Sensor, and Beam, as well as to detect products and update each of them.
 */
class ProductDetector : public VisitorBase
{
private:
    Sparty* mSparty = nullptr;         ///< Pointer to the Sparty object
    Beam* mBeam = nullptr;             ///< Pointer to the Beam object
    Sensor* mSensor = nullptr;         ///< Pointer to the Sensor object
	Scoreboard* mScoreboard = nullptr;	///< Pointer to the Scoreboard object
    std::vector<Product*> mProducts;   ///< Vector of pointers to Product objects

public:
    /**
     * @brief Visit Sparty object
     * @param sparty Pointer to Sparty object
     */
    void VisitSparty(Sparty* sparty) override { mSparty = sparty; }

    /**
     * @brief Visit Sensor object
     * @param sensor Pointer to Sensor object
     */
    void VisitSensor(Sensor* sensor) override { mSensor = sensor; }

    /**
     * @brief Visit Beam object
     * @param beam Pointer to Beam object
     */
    void VisitBeam(Beam * beam) override { mBeam = beam; }

    /**
     * @brief Visit Scorboard object
     * @param scoreboard Pointer to Scoreboard object
     */
    void VisitScoreboard(Scoreboard* scoreboard) override { mScoreboard = scoreboard; }

    void VisitProduct(Product* product) override;

    void UpdateBeam();

    void UpdateSensor();

    void UpdateSparty();

    void UpdateScoreboard();

};

#endif //PROJECT1_GAMELIB_PRODUCTDETECTOR_H
