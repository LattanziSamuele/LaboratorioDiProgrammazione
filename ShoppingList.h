//
// Created by Roberto on 03/12/2024.
//

#ifndef LABORATORIODIPROGRAMMAZIONE_SHOPPINGLIST_H
#define LABORATORIODIPROGRAMMAZIONE_SHOPPINGLIST_H

#include "Observer.h"
#include "Subject.h"
#include "User.h"
#include "Item.h"
#include <string>
#include <map>
#include <list>
#include <memory>
#include <utility>
#include <stdexcept>
#include <exception>
#include <vector>
#include <iostream>
#include <sstream>

enum class ShoppingListEvent;

class ShoppingList: public Subject {

public:
    ShoppingList(const std::string& name): name(name){};

    virtual ~ShoppingList() = default;

    std::string getName() const;
    // bool remove toggle, aggiungere calcolo ntotale, metodo cercaitem(stringa) rende item con tale stringa
    void addItem(const std::string& itemName, const std::string& category, int quantity);
    void addItem(const Item& newItem);
    bool removeItem(const std::string& itemName);
    bool toggleItemPurchased(const std::string& itemName);
    void updateItemQuantity(const std::string& itemName, int newQuantity);

    virtual void subscribe(Observer* observer) override;
    virtual void unsubscribe(Observer* observer) override;
    virtual void notify(ShoppingListEvent event, const std::string& itemName = "") override;

    int countUnpurchasedItems() const;
    int countAllItems() const;

    //trasformare in tostring
    std::string toString() const;
    std::string toStringByCategory() const;
    std::list<std::shared_ptr<Item>> findItemsByName(const std::string& searchString) const;

    int getObserverCount() const;


private:
    std::string name;
    std::map<std::string, std::shared_ptr<Item>> items;
    std::list<Observer*> observers;
};



#endif //LABORATORIODIPROGRAMMAZIONE_SHOPPINGLIST_H
