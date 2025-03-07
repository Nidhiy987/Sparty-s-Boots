/**
 * @file ProductTest.cpp
 * @author Attulya Pratap Gupta
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Product.h>
#include <Game.h>
#include <Level.h>
#include <wx/xml/xml.h>

/// The possible product properties
     enum class Properties
     {
         None, Red, Green, Blue, White, Square, Circle, Diamond,
         Izzo, Smith, Football, Basketball
        };

/// The property types
enum class Types { Color, Shape, Content };

class ProductTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_shared<Game>();
        level = std::make_shared<Level>(game.get());
        product = std::make_shared<Product>(level.get());
    }

    std::shared_ptr<Game> game;
    std::shared_ptr<Level> level;
    std::shared_ptr<Product> product;
};

TEST_F(ProductTest, XmlLoad) {
    // Create an XML node with all attributes
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"product");
    node->AddAttribute(L"placement", L"100");
    node->AddAttribute(L"shape", L"diamond");
    node->AddAttribute(L"color", L"blue");
    node->AddAttribute(L"content", L"basketball");
    node->AddAttribute(L"kick", L"no");

    // Load the XML
    product->XmlLoad(node);

    // Test all attributes
    EXPECT_DOUBLE_EQ(product->GetPlacement(), 100);
    EXPECT_EQ(static_cast<int>(product->GetShape()), static_cast<int>(Properties::Diamond));
    EXPECT_EQ(static_cast<int>(product->GetColor()), static_cast<int>(Properties::Blue));
    EXPECT_EQ(static_cast<int>(product->GetContent()), static_cast<int>(Properties::Basketball));
    EXPECT_FALSE(product->ShouldKick());

    delete node;
}

TEST_F(ProductTest, XmlLoadRelativePlacement) {
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"product");
    node->AddAttribute(L"placement", L"+150");
    node->AddAttribute(L"shape", L"square");
    node->AddAttribute(L"color", L"red");
    node->AddAttribute(L"content", L"football");
    node->AddAttribute(L"kick", L"yes");

    product->XmlLoad(node);

    EXPECT_DOUBLE_EQ(product->GetPlacement(), 150);
    EXPECT_EQ(static_cast<int>(product->GetShape()), static_cast<int>(Properties::Square));
    EXPECT_EQ(static_cast<int>(product->GetColor()), static_cast<int>(Properties::Red));
    EXPECT_EQ(static_cast<int>(product->GetContent()), static_cast<int>(Properties::Football));
    EXPECT_TRUE(product->ShouldKick());

    delete node;
}

TEST_F(ProductTest, XmlLoadDefaultValues) {
    auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"product");
    node->AddAttribute(L"placement", L"120");

    product->XmlLoad(node);

    EXPECT_DOUBLE_EQ(product->GetPlacement(), 120);
    EXPECT_EQ(static_cast<int>(product->GetShape()), static_cast<int>(Properties::None));
    EXPECT_EQ(static_cast<int>(product->GetColor()), static_cast<int>(Properties::None));
    EXPECT_EQ(static_cast<int>(product->GetContent()), static_cast<int>(Properties::None));
    EXPECT_FALSE(product->ShouldKick());

    delete node;
}