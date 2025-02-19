//
// Created by Roberto on 03/12/2024.
//

#ifndef LABORATORIODIPROGRAMMAZIONE_ITEM_H
#define LABORATORIODIPROGRAMMAZIONE_ITEM_H

#include <string>

class Item {

public:

    Item(const std::string& name, const std::string& category, int quantity, bool isPurchased = false);

    std::string getName() const;
    std::string getCategory() const;
    int getQuantity() const;
    bool IsPurchased() const;

    void setQuantity(int quantity);
    void setIsPurchased(bool isPurchased);
    void togglePurchased();


private:
    std::string name;
    std::string category;
    int quantity;
    bool purchased;
};


#endif //LABORATORIODIPROGRAMMAZIONE_ITEM_H
