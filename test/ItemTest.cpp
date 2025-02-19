//
// Created by Roberto on 09/01/2025.
//
#include <gtest/gtest.h>
#include "../Item.h"

TEST(ItemTest, TestConstructorAndGetters) {
    Item* item = new Item("Pane", "Cibo", 3);
    EXPECT_EQ(item->getName(), "Pane");
    EXPECT_EQ(item->getCategory(), "Cibo");
    EXPECT_EQ(item->getQuantity(), 3);
    EXPECT_FALSE(item->IsPurchased());

    ASSERT_THROW(Item item2("Acqua","Bevande",-4),std::invalid_argument);
}

TEST(ItemTest, Setters) {
    Item* item = new Item("Pane", "Cibo", 3);

    item->setQuantity(5);
    EXPECT_EQ(item->getQuantity(), 5);
    item->setIsPurchased(true);
    EXPECT_TRUE(item->IsPurchased());
    ASSERT_THROW(item->setQuantity(-1), std::invalid_argument);
}

TEST(ItemTest, TogglePurchasedWorksCorrectly) {
    Item* item = new Item("Pane", "Cibo", 3);
    EXPECT_FALSE(item->IsPurchased());

    item->togglePurchased();
    EXPECT_TRUE(item->IsPurchased());

    item->togglePurchased();
    EXPECT_FALSE(item->IsPurchased());
}
