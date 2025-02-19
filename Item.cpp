//
// Created by Roberto on 03/12/2024.
//
#include "Item.h"
#include <sstream>


Item::Item(const std::string& name, const std::string& category, int quantity, bool isPurchased)
        : name(name), category(category), purchased(isPurchased) {
    if (quantity < 0) {
        throw std::invalid_argument("La quantita' non può essere un numero negativo");
    }
    this->quantity = quantity;
}

std::string Item::getName() const {
    return name;
}

std::string Item::getCategory() const {
    return category;
}

int Item::getQuantity() const {
    return quantity;
}

bool Item::IsPurchased() const {
    return purchased;
}


void Item::setQuantity(int quantity) {
    if (quantity < 0) {
        throw std::invalid_argument("La quantita' non puo' essere un numero negativo");
    }
    this->quantity = quantity;
}

void Item::setIsPurchased(bool isPurchased) {
    this->purchased = isPurchased;
}

void Item::togglePurchased() {
    purchased = !purchased;
}

