/**
 * @file GateNot.h
 * @author Rachel Jansen
 *
 * Class to represent Not gate
 */

#ifndef GATENOT_H
#define GATENOT_H

#include "Gate.h"

/**
 * Class to represent Not gate
 */
class GateNot : public Gate
{
private:
	/// Input pin
	std::shared_ptr<Pin> mInputPin;

	/// Output pin
	std::shared_ptr<Pin> mOutputPin;

public:
	GateNot(Game *game);
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void UpdatePinPositions() override;
	void UpdateOutputPin() override;
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
    	return {mInputPin};
    }
};


#endif //GATENOT_H
