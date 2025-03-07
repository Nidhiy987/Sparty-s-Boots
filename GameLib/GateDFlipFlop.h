/**
 * @file GateDFlipFlop.h
 * @author Rachel Jansen
 *
 * Class to represent D Flip Flop gate
 */

#ifndef GATEDFLIPFLOP_H
#define GATEDFLIPFLOP_H

#include "Gate.h"

/**
 * Class to represent D Flip Flop gate
 */
class GateDFlipFlop : public Gate
{
private:
	/// Input pin D
	std::shared_ptr<Pin> mInputPinD;
	/// Input pin for the clock
	std::shared_ptr<Pin> mInputPinClock;
	/// Output pin Q
	std::shared_ptr<Pin> mOutputPinQ;
	/// Output pin Q'
	std::shared_ptr<Pin> mOutputPinQNot;

	/// previous state of clock
	bool mPrevState = false;

public:
	GateDFlipFlop(Game *game);
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void UpdateOutputPin() override;
	void UpdatePinPositions() override;
	void Accept(VisitorBase *visitor) override;
	std::shared_ptr<IDraggable> HitDraggable(int x, int y) override;
	bool Connect(Pin *pin, wxPoint lineEnd) override;
	std::pair<std::shared_ptr<Pin>, std::shared_ptr<Pin>> GetOutputPins() override;

    void SetShowControlPoints(bool show) override;

    /**
	 * Get the input pins for this gate
	 * @return Vector of input pins
	 */
	std::vector<std::shared_ptr<Pin>> GetInputPins() override
	{
		return {mInputPinD, mInputPinClock};
	}
};


#endif //GATEDFLIPFLOP_H
