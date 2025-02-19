//
// Created by Roberto on 09/01/2025.
//

#include "gtest/gtest.h"
#include "../ShoppingList.h"


class ObserverTest : public Observer {

public:
    bool isUpdated() const {
        return updated;
    }
    const std::string& getReceivedListName() const {
        return receivedListName;
    }
    const ShoppingListEvent& getReceivedEvent() const {
        return receivedEvent;
    }
    const std::string& getReceivedItemName() const {
        return receivedItemName;
    }

protected:
    std::string receivedListName;
    ShoppingListEvent receivedEvent;
    std::string receivedItemName;
    bool updated = false;

    virtual void update(const std::string& shoppingListName, ShoppingListEvent event, const std::string& itemName) override {
        receivedListName = shoppingListName;
        receivedEvent = event;
        receivedItemName = itemName;
        updated = true;
    }
};

TEST(ObserverTest, UpdateObserver) {
    ShoppingList shoppingList("ListaTest");
    ObserverTest TestObserver;

    shoppingList.subscribe(&TestObserver);

    ASSERT_FALSE(TestObserver.isUpdated());

    shoppingList.addItem("Latte", "Cibo", 2);

    ASSERT_TRUE(TestObserver.isUpdated());
    EXPECT_EQ(TestObserver.getReceivedListName(), "ListaTest");
    EXPECT_EQ(TestObserver.getReceivedEvent(), ShoppingListEvent::ITEM_ADDED);
    EXPECT_EQ(TestObserver.getReceivedItemName(), "Latte");
}


