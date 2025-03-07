/**
 * @file BeamTest.cpp
 * @author Flower Akaliza
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <Game.h>
#include <Beam.h>


class BeamTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_shared<Game>();
        level = std::make_shared<Level>(game.get());
        beam = std::make_shared<Beam>(level.get());
    }

    std::shared_ptr<Game> game;
    std::shared_ptr<Level> level;
    std::shared_ptr<Beam> beam;
};

TEST_F(BeamTest, XmlLoad) {
    // Create an XML node with all attributes
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"beam");
    node->AddAttribute(L"x", L"242");
    node->AddAttribute(L"y", L"437");
    node->AddAttribute(L"sender", L"-185");

    // Load the XML
    beam->XmlLoad(node);

    // Test all attributes
    EXPECT_DOUBLE_EQ(beam->GetX(), 242);
    EXPECT_DOUBLE_EQ(beam->GetY(), 437);
    EXPECT_DOUBLE_EQ(beam->GetSender(), -185);

    delete node;
}

TEST_F(BeamTest, DetectProduct){

    // Set beam location can confirm it's been set correctly
    beam->SetLocation(242, 437);
    ASSERT_EQ(beam->GetY(), 437);

    // Test product above beam
    std::tuple<double, double> productLocation = std::make_tuple(0, 0);
    ASSERT_FALSE(beam->DetectProduct(productLocation));

    // Test product with bottom at beam and top out of range
    productLocation = std::make_tuple(337, 437);
    ASSERT_TRUE(beam->DetectProduct(productLocation));

    // Test product with top at beam and bottom out of range
    productLocation = std::make_tuple(437, 550);
    ASSERT_TRUE(beam->DetectProduct(productLocation));

    // Test product with top and bottom in range
    productLocation = std::make_tuple(337, 500);
    ASSERT_TRUE(beam->DetectProduct(productLocation));

    // Test product with top and bottom out of range
    productLocation = std::make_tuple(500, 600);
    ASSERT_FALSE(beam->DetectProduct(productLocation));
}
