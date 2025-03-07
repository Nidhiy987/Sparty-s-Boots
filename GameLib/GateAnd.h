/**
 * @file GateAnd.h
 * @author Rachel Jansen
 *
 * Class to represent And gate
 */

#ifndef GATEAND_H
#define GATEAND_H

#include "Gate.h"

/**
 * Class to represent And gate
 */
class GateAnd : public Gate
{
private:
	/// Input pin 1
	std::shared_ptr<Pin> mInputPin1;
	/// Input pin 2
	std::shared_ptr<Pin> mInputPin2;
	/// Output pin
	std::shared_ptr<Pin> mOutputPin;

public:
	GateAnd(Game* game);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void UpdateOutputPin() override;
	void UpdatePinPositions() override;
	void Accept(VisitorBase *visitor) override;
	std::shared_ptr<IDraggable> HitDraggable(int x, int y) override;
	bool Connect(Pin *pin, wxPoint lineEnd) override;
	std::pair<std::shared_ptr<Pin>, std::shared_ptr<Pin>> GetOutputPins() override;

    /**
     * Setter for control points
     * @param show whether or not we should show control points
     * */
    void SetShowControlPoints(bool show) override { mOutputPin->SetShowControlPoints(show);}

    /**
	 * Get the input pins for this gate
	 * @return Vector of input pins
	 */
	std::vector<std::shared_ptr<Pin>> GetInputPins() override
    {
    	return {mInputPin1, mInputPin2};
    }
};


#endif //GATEAND_H
