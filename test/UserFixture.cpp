//
// Created by Roberto on 09/01/2025.
//
#include <gtest/gtest.h>
#include "../User.h"

class UserTest : public ::testing::Test {
protected:


    virtual void SetUp() override{
        user.addShoppingList(std::make_shared<ShoppingList>(list));
    }

    User user{"UtenteTest"};
    ShoppingList list{"Spesa"};
};

TEST_F(UserTest, AddShoppingList) {
    ShoppingList newList("Scorta");
    user.addShoppingList(std::make_shared<ShoppingList>(newList));
    ASSERT_EQ(user.printShoppingLists(), "Liste della spesa dell'utente 'UtenteTest':\n- Scorta\n- Spesa\n");
}

TEST_F(UserTest, RemoveExistingShoppingList) {
    user.removeShoppingList("Spesa");
    ASSERT_EQ(user.printShoppingLists(), "Liste della spesa dell'utente 'UtenteTest':\nNessuna lista della spesa disponibile.\n");
}

TEST_F(UserTest, RemoveNonExistingShoppingList) {
    EXPECT_THROW(user.removeShoppingList("Casa"), std::invalid_argument);
}

TEST_F(UserTest, ShareShoppingList) {
    User otherUser("AltroUtente");
    user.shareShoppingList(otherUser, "Spesa");
    ASSERT_EQ(otherUser.printShoppingLists(), "Liste della spesa dell'utente 'AltroUtente':\n- Spesa\n");
}

