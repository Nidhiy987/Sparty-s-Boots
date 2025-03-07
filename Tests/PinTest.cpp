/**
 * @file PinTest.cpp
 * @author Rachel Jansen
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Pin.h>
#include <Game.h>
#include <GateOr.h>

TEST(PinTest, State)
{
	Game game;
	Pin pin(10,10, true, nullptr);
	ASSERT_TRUE(pin.IsUnknown());
	GateOr gate(&game);
	auto outpin = gate.GetOutputPins();
	ASSERT_TRUE(outpin.first->IsUnknown());
}

