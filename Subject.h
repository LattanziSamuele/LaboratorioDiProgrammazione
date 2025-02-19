//
// Created by Roberto on 03/12/2024.
//

#ifndef LABORATORIODIPROGRAMMAZIONE_SUBJECT_H
#define LABORATORIODIPROGRAMMAZIONE_SUBJECT_H

#include "Observer.h"

enum class ShoppingListEvent {
    ITEM_ADDED,
    ITEM_REMOVED,
    QUANTITY_UPDATED,
    PURCHASED_STATUS_UPDATED
};

class Observer;

class Subject {
public:
    virtual ~Subject() = default;

    virtual void subscribe(Observer* o) = 0;

    virtual void unsubscribe(Observer* o) = 0;

    virtual void notify(ShoppingListEvent event, const std::string& itemName = "") = 0;
};

#endif //LABORATORIODIPROGRAMMAZIONE_SUBJECT_H
