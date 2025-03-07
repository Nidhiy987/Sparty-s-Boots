/**
 * @file ScoreboardTest.cpp
 * @author Flower Akaliza
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <Game.h>
#include <Scoreboard.h>

class ScoreboardTest : public ::testing::Test {

protected:
    void SetUp() override {
        game = std::make_shared<Game>();
        level = std::make_shared<Level>(game.get());
        scoreboard = std::make_shared<Scoreboard>(level.get());
    }
    std::shared_ptr<Game> game;
    std::shared_ptr<Level> level;
    std::shared_ptr<Scoreboard> scoreboard;
};
TEST_F(ScoreboardTest, XmlLoad) {

    // Create an XML node with all attributes
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"scoreboard");
    node->AddAttribute(L"x", L"700");
    node->AddAttribute(L"y", L"40");
    node->AddAttribute(L"good", L"10");
    node->AddAttribute(L"bad", L"-5");

    auto childNode = new wxXmlNode(wxXML_TEXT_NODE, L"");
    childNode->SetContent(L"Make Sparty kick all product from the conveyor<br/>that are not green.");

    node->AddChild(childNode);

    scoreboard->XmlLoad(node);

    ASSERT_EQ(scoreboard->GetX(), 700);
    ASSERT_EQ(scoreboard->GetY(), 40);
    ASSERT_EQ(scoreboard->GetGood(), 10);
    ASSERT_EQ(scoreboard->GetBad(), -5);

    ASSERT_EQ(scoreboard->GetInstructions(), L"Make Sparty kick all product from the conveyor<br/>that are not green.\r\n");

    delete node;

}

TEST_F(ScoreboardTest, XmlLoadDefault)
{
    // Create an XML node with all attributes
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"scoreboard");
    node->AddAttribute(L"x", L"700");
    node->AddAttribute(L"y", L"40");

    auto childNode = new wxXmlNode(wxXML_TEXT_NODE, L"");
    childNode->SetContent(L"Make Sparty kick all product from the conveyor<br/>that are not green.");

    node->AddChild(childNode);

    scoreboard->XmlLoad(node);

    ASSERT_EQ(scoreboard->GetX(), 700);
    ASSERT_EQ(scoreboard->GetY(), 40);
    ASSERT_EQ(scoreboard->GetGood(), 10);
    ASSERT_EQ(scoreboard->GetBad(), 0);

    ASSERT_EQ(scoreboard->GetInstructions(), L"Make Sparty kick all product from the conveyor<br/>that are not green.\r\n");

    delete node;

}