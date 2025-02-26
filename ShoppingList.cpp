//
// Created by Roberto on 03/12/2024.
//

#include "ShoppingList.h"


std::string ShoppingList::getName() const {
    return name;
}

void ShoppingList::addItem(const std::string& itemName, const std::string& category, int quantity) {
    auto it = items.find(itemName);
    if (it != items.end() && it->second->getCategory()==category) {
        it->second->setQuantity(it->second->getQuantity() + quantity);
        notify(ShoppingListEvent::QUANTITY_UPDATED, itemName);
    } else {
        auto newItem = std::make_shared<Item>(itemName, category, quantity);
        items.insert(std::make_pair(itemName, newItem));
        notify(ShoppingListEvent::ITEM_ADDED, itemName);
    }
}

void ShoppingList::addItem(const Item& newItem) {
    auto it = items.find(newItem.getName());
    if (it != items.end() && it->second->getCategory() == newItem.getCategory()) {
            it->second->setQuantity(it->second->getQuantity() + newItem.getQuantity());
            notify(ShoppingListEvent::QUANTITY_UPDATED, newItem.getName());
    } else {
        auto itemPtr = std::make_shared<Item>(newItem);
        items.insert(std::make_pair(newItem.getName(), itemPtr));
        notify(ShoppingListEvent::ITEM_ADDED, newItem.getName());
    }
}

bool ShoppingList::removeItem(const std::string& itemName) {
    auto it = items.find(itemName);
    if (it != items.end()){
        it->second->setQuantity(0);
        items.erase(it);
        notify(ShoppingListEvent::ITEM_REMOVED, itemName);
        return true;
    }
    else
        return false;
}
bool ShoppingList::toggleItemPurchased(const std::string &itemName) {
    auto it = items.find(itemName);
    if (it != items.end()) {
        it->second->togglePurchased();
        notify(ShoppingListEvent::PURCHASED_STATUS_UPDATED, itemName);
        return true;
    } else
        return false;
}

void ShoppingList::updateItemQuantity(const std::string& itemName, int newQuantity) {
    if (newQuantity < 0) {
        throw std::invalid_argument("La quantita' non può essere negativa");
    }

    auto it = items.find(itemName);
    if (it != items.end()) {
        if (newQuantity > 0) {
            it->second->setQuantity(newQuantity);
            notify(ShoppingListEvent::QUANTITY_UPDATED, itemName);
        } else {
            items.erase(it);
            notify(ShoppingListEvent::ITEM_REMOVED, itemName);
        }
    } else {
        throw std::invalid_argument("Hai fornito un nome invalido per l'Item");
    }
}


void ShoppingList::subscribe(Observer* observer) {
    observers.push_back(observer);
}

void ShoppingList::unsubscribe(Observer* observer) {
    observers.remove(observer);
}

void ShoppingList::notify(ShoppingListEvent event, const std::string& itemName) {
    for (auto& observer : observers) {
        observer->update(name, event, itemName);
    }
}

int ShoppingList::countUnpurchasedItems() const {
    int count = 0;
    for (const auto& pair : items) {
        if (!pair.second->IsPurchased()) {
            count++;
        }
    }
    return count;
}
int ShoppingList::countAllItems() const {
    int totalQuantity = 0;
    for (const auto& pair : items) {
        totalQuantity += pair.second->getQuantity();
    }
    return totalQuantity;
}

std::string ShoppingList::toString() const {
    std::ostringstream oss;
    for (const auto& pair : items) {
            oss << "Nome: " << pair.second->getName()
            << ", Categoria: " << pair.second->getCategory()
            << ", Quantita': " << pair.second->getQuantity()
            << ", Acquistato: " << (pair.second->IsPurchased() ? "Si" : "No")
            << "\n"
            << ", Numero di Item non acquistati: " << countUnpurchasedItems()
            << "\n";
    }
    return oss.str();
}

std::string ShoppingList::toStringByCategory() const {
    std::map<std::string, std::vector<std::string>> categoryMap;

    for (const auto& pair : items) {
        categoryMap[pair.second->getCategory()].push_back(pair.second->getName());
    }

    std::ostringstream oss;
    for (const auto& category : categoryMap) {
        oss << "Categoria: " << category.first << "\n";
        for (const auto& itemName : category.second) {
            oss << "  - " << itemName << "\n";
        }
    }
    return oss.str();
}
std::list<std::shared_ptr<Item>> ShoppingList::findItemsByName(const std::string& searchString) const {
    std::list<std::shared_ptr<Item>> foundItems;
    if (searchString.empty()) {
        return foundItems;
    }
    for (const auto &pair : items) {
        const std::shared_ptr<Item> &item = pair.second;
        if (item->getName().find(searchString) != std::string::npos) {
            foundItems.push_back(item);
        }
    }

    return foundItems;
}

int ShoppingList::getObserverCount() const {
    return observers.size();
}