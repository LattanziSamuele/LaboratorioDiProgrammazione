//
// Created by Roberto on 03/12/2024.
//

#include "User.h"
#include "ShoppingList.h"

#include <iostream>

User::User(const std::string& name) : name(name) {}

User::~User() {
    for (auto& itr : shoppingLists) {
        itr.second->unsubscribe(this);
    }
}

std::string User::getName() const {
    return name;
}


void User::addShoppingList(std::shared_ptr<ShoppingList> shoppingList) {
    if (shoppingLists.find(shoppingList->getName()) == shoppingLists.end()) {
        shoppingLists[shoppingList->getName()] = shoppingList;
        shoppingList->subscribe(this);
    } else {
        std::cout << "L'Utente gia' e' iscritto alla lista '" << shoppingList->getName() << "'." << std::endl;
    }
}

void User::removeShoppingList(const std::string& listName) {
    auto itr = shoppingLists.find(listName);
    if (itr == shoppingLists.end())
        throw std::invalid_argument("Hai inserito un nome invalido per la lista");
    else {
        itr->second->unsubscribe(this);
        shoppingLists.erase(listName);
    }
}

void User::update(const std::string& shoppingListName, ShoppingListEvent event, const std::string& itemName) {
    auto itr = shoppingLists.find(shoppingListName);
    std::string message = "Notifica dalla lista '" + shoppingListName + "': ";
    switch (event) {
        case ShoppingListEvent::ITEM_ADDED:
            message += "Aggiunto l'Item : " + itemName;
            break;
        case ShoppingListEvent::ITEM_REMOVED:
            message += "Rimosso l'Item: " + itemName;
            break;
        case ShoppingListEvent::QUANTITY_UPDATED:
            message += "Aggiornata la quantita' dell'Item: " + itemName;
            break;
        case ShoppingListEvent::PURCHASED_STATUS_UPDATED:
            message += "Aggiornato lo stato di acquisto dell'Item: " + itemName;
            break;
    }
    std::cout << message << std::endl;
}

void User::shareShoppingList(User& otherUser, const std::string& shoppingListName) {
    auto it = shoppingLists.find(shoppingListName);
    if (it != shoppingLists.end()) {
        otherUser.addShoppingList(it->second);
        std::cout << "La lista '" << shoppingListName << "' e' stata condivisa dall'utente "
                  << name << " con " << otherUser.getName() << std::endl;
    } else {
        throw std::invalid_argument("La lista non esiste.");
    }
}

std::shared_ptr<ShoppingList> User::getShoppingList(const std::string& listName) const {
    auto it = shoppingLists.find(listName);
    if (it != shoppingLists.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("La lista della spesa '" + listName + "' non esiste.");
    }
}

std::string User::printShoppingLists() {
    std::ostringstream oss;
    oss << "Liste della spesa dell'utente '" << name << "':\n";

    if (shoppingLists.empty()) {
        oss << "Nessuna lista della spesa disponibile.\n";
    } else {
        for (const auto& pair : shoppingLists) {
            oss << "- " << pair.first << "\n";
        }
    }

    return oss.str();
}


