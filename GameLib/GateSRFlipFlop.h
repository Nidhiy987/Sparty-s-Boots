/**
 * @file GateSRFlipFlop.h
 * @author Rachel Jansen
 *
 * Class to represent SR Flip Flop gate
 */

#ifndef GATESRFLIPFLOP_H
#define GATESRFLIPFLOP_H

#include "Gate.h"

/**
 * Class to represent SR Flip Flop gate
 */
class GateSRFlipFlop : public Gate
{
private:
	/// Input pin S
	std::shared_ptr<Pin> mInputPinS;
	/// Input pin R
	std::shared_ptr<Pin> mInputPinR;
	/// Output pin Q
	std::shared_ptr<Pin> mOutputPinQ;
	/// Output pin Q'
	std::shared_ptr<Pin> mOutputPinQNot;

public:
	GateSRFlipFlop(Game *game);
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
		return {mInputPinS, mInputPinR};
	}
};


#endif //GATESRFLIPFLOP_H
