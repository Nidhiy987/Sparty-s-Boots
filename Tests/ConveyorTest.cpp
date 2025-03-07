/**
 * @file ConveyorTest.cpp
 * @author Attulya Pratap Gupta
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <wx/xml/xml.h>
#include <Conveyor.h>
#include <Game.h>
#include <Level.h>


class ConveyorTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_shared<Game>();
        level = std::make_shared<Level>(game.get());
    }

    std::shared_ptr<Game> game;
    std::shared_ptr<Level> level;
};

TEST_F(ConveyorTest, ConveyorXmlLoad) {
    auto conveyor = std::make_shared<Conveyor>(level.get());
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"conveyor");

    node->AddAttribute(L"x", L"150");
    node->AddAttribute(L"y", L"400");
    node->AddAttribute(L"speed", L"100");
    node->AddAttribute(L"height", L"800");
    node->AddAttribute(L"panel", L"60,-390");

    conveyor->XmlLoad(node);

    EXPECT_DOUBLE_EQ(conveyor->GetX(), 150);
    EXPECT_DOUBLE_EQ(conveyor->GetY(), 400);
    EXPECT_DOUBLE_EQ(conveyor->GetSpeed(), 100);
    EXPECT_DOUBLE_EQ(conveyor->GetHeight(), 800);

    wxPoint panelPos = conveyor->GetPanelLocation();
    EXPECT_EQ(panelPos.x, 60);
    EXPECT_EQ(panelPos.y, -390);

    delete node;
}