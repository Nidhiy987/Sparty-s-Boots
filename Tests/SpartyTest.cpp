/**
 * @file SpartyTest.cpp
 * @author Attulya Pratap Gupta
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Sparty.h>
#include <Game.h>
#include <Level.h>
#include <wx/xml/xml.h>

class SpartyTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_shared<Game>();
        level = std::make_shared<Level>(game.get());
        sparty = std::make_shared<Sparty>(level.get());
    }

    std::shared_ptr<Game> game;
    std::shared_ptr<Level> level;
    std::shared_ptr<Sparty> sparty;
};

TEST_F(SpartyTest, XmlLoad) {
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"sparty");
    node->AddAttribute(L"x", L"345");
    node->AddAttribute(L"y", L"340");
    node->AddAttribute(L"height", L"300");
    node->AddAttribute(L"pin", L"1100, 400");
    node->AddAttribute(L"kick-duration", L"0.25");
    node->AddAttribute(L"kick-speed", L"1000");

    sparty->XmlLoad(node);

    EXPECT_DOUBLE_EQ(sparty->GetX(), 345);
    EXPECT_DOUBLE_EQ(sparty->GetY(), 340);
    EXPECT_DOUBLE_EQ(sparty->GetHeight(), 300);

    auto pin = sparty->GetInputPin();
    EXPECT_DOUBLE_EQ(pin->GetX(), 1100);
    EXPECT_DOUBLE_EQ(pin->GetY(), 400);

    EXPECT_DOUBLE_EQ(sparty->GetKickDuration(), 0.25);
    EXPECT_DOUBLE_EQ(sparty->GetKickSpeed(), 1000);

    delete node;
}

TEST_F(SpartyTest, XmlLoadDefaultValues) {
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"sparty");
    node->AddAttribute(L"x", L"100");
    node->AddAttribute(L"y", L"200");

    sparty->XmlLoad(node);

    EXPECT_DOUBLE_EQ(sparty->GetX(), 100);
    EXPECT_DOUBLE_EQ(sparty->GetY(), 200);
    EXPECT_NE(sparty->GetHeight(), 0);  // Ensure a default height is set

    auto pin = sparty->GetInputPin();
    EXPECT_NE(pin, nullptr);  // Ensure a default pin is created

    EXPECT_NE(sparty->GetKickDuration(), 0);  // Ensure a default kick duration is set
    EXPECT_NE(sparty->GetKickSpeed(), 0);  // Ensure a default kick speed is set

    delete node;
}