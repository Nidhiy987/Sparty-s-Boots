/**
 * @file SensorTest.cpp
 * @author Flower Akaliza
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <Game.h>
#include <Sensor.h>

class SensorTest : public ::testing::Test {

protected:
    void SetUp() override {
        game = std::make_shared<Game>();
        level = std::make_shared<Level>(game.get());
        sensor = std::make_shared<Sensor>(level.get());
    }
    std::shared_ptr<Game> game;
    std::shared_ptr<Level> level;
    std::shared_ptr<Sensor> sensor;
};
TEST_F(SensorTest, XmlLoad) {

    // Create an XML node with all attributes
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"sensor");
    node->AddAttribute(L"x", L"155");
    node->AddAttribute(L"y", L"430");

    // Create and add its children nodes. Used to test all possible outputs the sensor can have
    auto childNode1 = new wxXmlNode(wxXML_ELEMENT_NODE , L"red");
    auto childNode2 = new wxXmlNode(wxXML_ELEMENT_NODE, L"green");
    auto childNode3 = new wxXmlNode(wxXML_ELEMENT_NODE, L"blue");
    auto childNode4 = new wxXmlNode(wxXML_ELEMENT_NODE, L"white");
    auto childNode5 = new wxXmlNode(wxXML_ELEMENT_NODE, L"square");
    auto childNode6 = new wxXmlNode(wxXML_ELEMENT_NODE, L"circle");
    auto childNode7 = new wxXmlNode(wxXML_ELEMENT_NODE, L"diamond");
    auto childNode8 = new wxXmlNode(wxXML_ELEMENT_NODE, L"izzo");
    auto childNode9 = new wxXmlNode(wxXML_ELEMENT_NODE, L"smith");
    auto childNode10 = new wxXmlNode(wxXML_ELEMENT_NODE, L"basketball");
    auto childNode11 = new wxXmlNode(wxXML_ELEMENT_NODE, L"football");

    node->AddChild(childNode1);
    node->AddChild(childNode2);
    node->AddChild(childNode3);
    node->AddChild(childNode4);
    node->AddChild(childNode5);
    node->AddChild(childNode6);
    node->AddChild(childNode7);
    node->AddChild(childNode8);
    node->AddChild(childNode9);
    node->AddChild(childNode10);
    node->AddChild(childNode11);


    // Assert the sensor has no outputs before it has been loaded
    ASSERT_EQ(sensor->GetOutputCount(), 0);

    // Load the sensor
    sensor->XmlLoad(node);

    // Test all attributes
    ASSERT_EQ(sensor->GetX(), 155);
    ASSERT_EQ(sensor->GetY(), 430);

    ASSERT_EQ(sensor->GetOutputCount(), 11);


    delete node;

}

TEST_F(SensorTest, DetectProduct)
{
    // Set sensor location and confirm y coordinate is correct
    sensor->SetLocation(155, 430);
    ASSERT_EQ(sensor->GetY(), 430);

    // Test product above beam
    std::tuple<double, double> productLocation = std::make_tuple(0, 100);
    // Test product out of range
    ASSERT_FALSE(sensor->DetectProduct(productLocation, 50));

    // Test product within the range
    productLocation = std::make_tuple(337, 450);
    ASSERT_TRUE(sensor->DetectProduct(productLocation, 390));

    // Test product with top in range
    productLocation = std::make_tuple(430, 530);
    ASSERT_TRUE(sensor->DetectProduct(productLocation, 480));

    // Test product with bottom of range
    productLocation = std::make_tuple(300, 400);
    ASSERT_TRUE(sensor->DetectProduct(productLocation, 350));

    // Test product out of range again
    productLocation = std::make_tuple(450, 550);
    ASSERT_FALSE(sensor->DetectProduct(productLocation, 500));
}