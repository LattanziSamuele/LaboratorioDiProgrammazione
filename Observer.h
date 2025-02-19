//
// Created by Roberto on 03/12/2024.
//

#ifndef LABORATORIODIPROGRAMMAZIONE_OBSERVER_H
#define LABORATORIODIPROGRAMMAZIONE_OBSERVER_H

#include <string>
#include "Subject.h"


class Observer{

public:
    virtual ~Observer() = default;

    virtual void update(const std::string& shoppingListName, ShoppingListEvent event, const std::string& itemName) = 0;

};

#endif //LABORATORIODIPROGRAMMAZIONE_OBSERVER_H
