/**
 * @file GateTest.cpp
 * @author Rachel Jansen
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Gate.h>

class GateMock : public Gate {
public:
	GateMock(Game* game) : Gate(game) {}
	void Accept(VisitorBase* visitor) override {}
	std::pair<std::shared_ptr<Pin>, std::shared_ptr<Pin>> GetOutputPins() override { return std::make_pair(nullptr, nullptr); }
	std::vector<std::shared_ptr<Pin>> GetInputPins() override { return {}; }
};

TEST(GateTest, Construct) {
	Game game;
	GateMock gate(&game);
}

TEST(GateTest, HitTest)
{
	Game game;
	GateMock gate(&game);
	// Set width and height to 100
	gate.SetSize(wxSize(100, 100));
	// Position center of the gate at point (300, 300)
	gate.SetLocation(300, 300);

	// Test center of the gate
	ASSERT_TRUE(gate.HitTest(300, 300));
	// Test left edge of the gate
	ASSERT_TRUE(gate.HitTest(250, 300));
	// Test right edge of the gate
	ASSERT_TRUE(gate.HitTest(350, 300));
	// Test top edge of gate
	ASSERT_TRUE(gate.HitTest(300, 250));
	// Test bottom edge of gate
	ASSERT_TRUE(gate.HitTest(300, 350));

	// Test all four corners of gate
	ASSERT_TRUE(gate.HitTest(350, 350));
	ASSERT_TRUE(gate.HitTest(350, 250));
	ASSERT_TRUE(gate.HitTest(250, 350));
	ASSERT_TRUE(gate.HitTest(250, 250));

	// Test just outside edge of gate
	ASSERT_FALSE(gate.HitTest(351, 351));
	ASSERT_FALSE(gate.HitTest(351, 250));
	ASSERT_FALSE(gate.HitTest(249,249));
	ASSERT_FALSE(gate.HitTest(249,250));
	ASSERT_FALSE(gate.HitTest(300,351));
	ASSERT_FALSE(gate.HitTest(300,249));
}