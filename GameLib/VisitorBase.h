/**
 * @file VisitorBase.h
 * @author Navanidhiy  Achuthan Kumaraguru
 *
 *
 */

#ifndef VISITORBASE_H
#define VISITORBASE_H


// Forward declarations of all item types (inheriting from Item)
class Gate;
class Sensor;
class Beam;
class Sparty;
class Conveyor;
class Scoreboard;
class Product;
class SensorOutput;
class GateOr;
class GateAnd;
class GateNot;
class GateDFlipFlop;
class GateSRFlipFlop;
class Pin;

/**
 * Visitor base class for items
 */
class VisitorBase
{
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    VisitorBase() {}

public:
    /**
     * Destructor
     */
    virtual ~VisitorBase() {}

    /**
     * Visit an ItemGate object
     * @param gate Gate item we are visiting
     */
    virtual void VisitGate(Gate* gate) {}

    /**
     * Visit an ItemSensor object
     * @param sensor Sensor item we are visiting
     */
    virtual void VisitSensor(Sensor* sensor) {}

    /**
     * Visit an ItemBeam object
     * @param beam Beam item we are visiting
     */
    virtual void VisitBeam(Beam* beam) {}

    /**
     * Visit an ItemSparty object
     * @param sparty Sparty item we are visiting
     */
    virtual void VisitSparty(Sparty* sparty) {}

   /**
    * Visit an ItemConveyor object
    * @param conveyor Conveyor item we are visiting
    */
    virtual void VisitConveyor(Conveyor* conveyor) {}

	/**
	 * Visit a Scoreboard object
	 * @param scoreboard Scoreboard object we are visiting
	 */
	virtual void VisitScoreboard(Scoreboard* scoreboard) {};

	/**
	 * Visit a product object
	 * @param product we are visiting
	 */
	virtual void VisitProduct(Product* product) {};

	/**
	 * Visit a SensorOutput object
	 * @param sensorOutput sensor output we are visiting
	 */
	virtual void VisitSensorOutput(SensorOutput* sensorOutput) {};

	/**
	 * Visit an or gate object
	 * @param gateOr or gate we are visiting
	 */
	virtual void VisitGateOr(GateOr* gateOr) {};

	/**
	 * Visit an and gate object
	 * @param gateAnd and gate we are visiting
	 */
	virtual void VisitGateAnd(GateAnd* gateAnd) {};

	/**
	 * Visit a not gate object
	 * @param gateNot not gate we are visiting
	 */
	virtual void VisitGateNot(GateNot* gateNot) {};

	/**
	 * Visit an SR flip flop object
	 * @param gateSRFlipFlop SR flip flop we are visiting
	 */
	virtual void VisitGateSRFlipFlop(GateSRFlipFlop* gateSRFlipFlop) {};

	/**
	 * Visit a D flip flop object
	 * @param gateDFlipFlop D flip flop we are visiting
	 */
	virtual void VisitGateDFlipFlop(GateDFlipFlop* gateDFlipFlop) {};

	/**
	 * Visit a pin object
	 * @param pin The pin we are visiting
	 */
	virtual void VisitPin(Pin* pin) {};

};


#endif //VISITORBASE_H
