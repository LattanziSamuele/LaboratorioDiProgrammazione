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
    ASSERT_EQ(shoppingList->printAllItems(), "Nome: Mela, Categoria: Frutta, Quantita': 5, Acquistato: No\n"
                                             ", Numero di Item non acquistati: 2\n"
                                             "Nome: Pera, Categoria: Frutta, Quantita': 6, Acquistato: No\n"
                                             ", Numero di Item non acquistati: 2\n");

    shoppingList->addItem("Mela", "Frutta", 3);
    ASSERT_EQ(shoppingList->printAllItems(), "Nome: Mela, Categoria: Frutta, Quantita': 8, Acquistato: No\n"
                                             ", Numero di Item non acquistati: 2\n"
                                             "Nome: Pera, Categoria: Frutta, Quantita': 6, Acquistato: No\n"
                                             ", Numero di Item non acquistati: 2\n");
}

TEST_F(ShoppingListTest, RemoveExistingItem) {
    shoppingList->removeItem("Mela");
    ASSERT_EQ(shoppingList->printAllItems(), "");
}

TEST_F(ShoppingListTest, RemoveNonExistingItem) {
    EXPECT_THROW(shoppingList->removeItem("Pera"), std::invalid_argument);
}

TEST_F(ShoppingListTest, UpdateItemQuantity) {
    shoppingList->updateItemQuantity("Mela", 10);
    ASSERT_EQ(shoppingList->printAllItems(), "Nome: Mela, Categoria: Frutta, Quantita': 10, Acquistato: No\n, Numero di Item non acquistati: 1\n");

    shoppingList->updateItemQuantity("Mela", 0);
    EXPECT_EQ(shoppingList->printAllItems(), "");

    EXPECT_THROW(shoppingList->updateItemQuantity("Mela", 5), std::invalid_argument);

    shoppingList->addItem("Banana", "Frutta", 3);
    EXPECT_THROW(shoppingList->updateItemQuantity("Banana", -1), std::invalid_argument);
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

