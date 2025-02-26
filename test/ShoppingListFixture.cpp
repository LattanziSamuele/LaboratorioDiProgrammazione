//
// Created by Roberto on 09/01/2025.
//
#include <gtest/gtest.h>
#include "../ShoppingList.h"

class ShoppingListTest : public ::testing::Test {
protected:
    std::shared_ptr<ShoppingList> shoppingList;
    User u{"UtenteTest"};

    void SetUp() override {
        shoppingList = std::make_shared<ShoppingList>("ListaTest");
        shoppingList->addItem("Mela", "Frutta", 5);
    }

    void TearDown() override {
        shoppingList.reset();
    }
};

TEST_F(ShoppingListTest, AddItem) {
    shoppingList->addItem("Pera", "Frutta", 6);
    ASSERT_EQ(shoppingList->toString(), "Nome: Mela, Categoria: Frutta, Quantita': 5, Acquistato: No\n"
                                             ", Numero di Item non acquistati: 2\n"
                                             "Nome: Pera, Categoria: Frutta, Quantita': 6, Acquistato: No\n"
                                             ", Numero di Item non acquistati: 2\n");

    shoppingList->addItem("Mela", "Frutta", 3);
    ASSERT_EQ(shoppingList->toString(), "Nome: Mela, Categoria: Frutta, Quantita': 8, Acquistato: No\n"
                                             ", Numero di Item non acquistati: 2\n"
                                             "Nome: Pera, Categoria: Frutta, Quantita': 6, Acquistato: No\n"
                                             ", Numero di Item non acquistati: 2\n");
}

TEST_F(ShoppingListTest, RemoveExistingItem) {
    ASSERT_TRUE(shoppingList->removeItem("Mela"));
    ASSERT_EQ(shoppingList->toString(), "");
}

TEST_F(ShoppingListTest, RemoveNonExistingItem) {
    ASSERT_FALSE(shoppingList->removeItem("Pera"));
}

TEST_F(ShoppingListTest, ToggleItemPurchased) {
    ASSERT_TRUE(shoppingList->toggleItemPurchased("Mela"));
    ASSERT_TRUE(shoppingList->toggleItemPurchased("Mela"));
    ASSERT_FALSE(shoppingList->toggleItemPurchased("Pera"));
}

TEST_F(ShoppingListTest, UpdateItemQuantity) {
    shoppingList->updateItemQuantity("Mela", 10);
    ASSERT_EQ(shoppingList->toString(), "Nome: Mela, Categoria: Frutta, Quantita': 10, Acquistato: No\n, Numero di Item non acquistati: 1\n");

    shoppingList->updateItemQuantity("Mela", 0);
    EXPECT_EQ(shoppingList->toString(), "");

    EXPECT_THROW(shoppingList->updateItemQuantity("Mela", 5), std::invalid_argument);

    shoppingList->addItem("Banana", "Frutta", 3);
    EXPECT_THROW(shoppingList->updateItemQuantity("Banana", -1), std::invalid_argument);
}
TEST_F(ShoppingListTest, CountAllItems) {
    ASSERT_EQ(shoppingList->countAllItems(), 5);

    shoppingList->addItem("Pera", "Frutta", 3);
    ASSERT_EQ(shoppingList->countAllItems(), 8);
}
TEST_F(ShoppingListTest, FindItemsByName) {
    shoppingList->addItem("Melone", "Frutta", 2);
    shoppingList->addItem("Banana", "Frutta", 4);

    auto foundItems = shoppingList->findItemsByName("Me");
    ASSERT_EQ(foundItems.size(), 2);

    auto foundItems2 = shoppingList->findItemsByName("Banana");
    ASSERT_EQ(foundItems2.size(), 1);

    auto foundItems3 = shoppingList->findItemsByName("Ananas");
    ASSERT_TRUE(foundItems3.empty());
}


TEST_F(ShoppingListTest, Subscribe) {
    ASSERT_EQ(shoppingList->getObserverCount(), 0);

    shoppingList->subscribe(&u);
    ASSERT_EQ(shoppingList->getObserverCount(), 1);
}
TEST_F(ShoppingListTest, Unsubscribe) {
    shoppingList->subscribe(&u);
    ASSERT_EQ(shoppingList->getObserverCount(), 1);

    shoppingList->unsubscribe(&u);
    ASSERT_EQ(shoppingList->getObserverCount(), 0);
}

