//
// Created by Roberto on 03/12/2024.
//

#ifndef LABORATORIODIPROGRAMMAZIONE_USER_H
#define LABORATORIODIPROGRAMMAZIONE_USER_H

#include <string>
#include "Observer.h"
#include "ShoppingList.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <map>

class ShoppingList;

class User: public Observer {

public:
    User(const std::string& name);

    virtual ~User();

    std::string getName() const;

    void addShoppingList(std::shared_ptr<ShoppingList> shoppingList);
    void removeShoppingList(const std::string& listName);

    virtual void update(const std::string& shoppingListName, ShoppingListEvent event, const std::string& itemName) override;

    void shareShoppingList(User& otherUser, const std::string& shoppingListName);

    std::shared_ptr<ShoppingList> getShoppingList(const std::string& listName) const;
    //bool existsShoppingList(const std::string& listName) const;

    std::string printShoppingLists();
    //cerca lista con nome, test con lista non esistente

private:
    std::string name;
    std::map<std::string, std::shared_ptr<ShoppingList>> shoppingLists;

};


#endif //LABORATORIODIPROGRAMMAZIONE_USER_H
