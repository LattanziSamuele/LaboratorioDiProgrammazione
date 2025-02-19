#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "User.h"
#include "ShoppingList.h"
#include "Item.h"

std::map<std::string, std::shared_ptr<User>> registeredUsers;
std::shared_ptr<User> loggedInUser = nullptr;

void registerUser() {
    std::string name;
    std::cout << "Inserisci il nome utente da registrare: ";
    std::cin >> name;

    if (registeredUsers.find(name) == registeredUsers.end()) {
        registeredUsers[name] = std::make_shared<User>(name);
        std::cout << "Utente registrato con successo.\n";
    } else {
        std::cout << "Nome utente gia' registrato.\n";
    }
}

void loginUser() {
    std::string name;
    std::cout << "Inserisci il nome utente per il login: ";
    std::cin >> name;

    auto it = registeredUsers.find(name);
    if (it != registeredUsers.end()) {
        loggedInUser = it->second;
        std::cout << "Login eseguito con successo.\n";
    } else {
        std::cout << "Nome utente non trovato. Registrati prima.\n";
    }
}

void logoutUser() {
    if (loggedInUser) {
        std::cout << "Logout eseguito per l'utente: " << loggedInUser->getName() << "\n";
        loggedInUser = nullptr;
    } else {
        std::cout << "Nessun utente loggato.\n";
    }
}

void createShoppingList() {
    if (!loggedInUser) {
        std::cout << "Devi essere loggato per creare una lista della spesa.\n";
        return;
    }

    std::string listName;
    std::cout << "Inserisci il nome della lista della spesa: ";
    std::cin >> listName;

    auto shoppingList = std::make_shared<ShoppingList>(listName);
    loggedInUser->addShoppingList(shoppingList);
    std::cout << "Lista della spesa '" << listName << "' creata con successo.\n";
}
void deleteShoppingList() {
    if (!loggedInUser) {
        std::cout << "Devi essere loggato per eliminare una lista della spesa.\n";
        return;
    }

    std::string listName;
    std::cout << "Inserisci il nome della lista della spesa da eliminare: ";
    std::cin >> listName;

    try {
        loggedInUser->removeShoppingList(listName);
        std::cout << "Lista della spesa '" << listName << "' è stata eliminata con successo.\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
    }
}
void addItemToShoppingList() {
    if (!loggedInUser) {
        std::cout << "Devi essere loggato per aggiungere un item a una lista della spesa.\n";
        return;
    }

    std::string listName, itemName, category;
    int quantity;

    std::cout << "Inserisci il nome della lista della spesa: ";
    std::cin >> listName;
    std::cout << "Inserisci il nome dell'item: ";
    std::cin >> itemName;
    std::cout << "Inserisci la categoria dell'item: ";
    std::cin >> category;
    std::cout << "Inserisci la quantita' dell'item: ";
    std::cin >> quantity;

    try {
        loggedInUser->getShoppingList(listName)->addItem(itemName, category, quantity);
        //std::cout << "Item '" << itemName << "' aggiunto alla lista '" << listName << "'.\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
    }
}

void removeItemFromShoppingList() {
    if (!loggedInUser) {
        std::cout << "Devi essere loggato per rimuovere un item da una lista della spesa.\n";
        return;
    }

    std::string listName, itemName;

    std::cout << "Inserisci il nome della lista della spesa: ";
    std::cin >> listName;
    std::cout << "Inserisci il nome dell'item da rimuovere: ";
    std::cin >> itemName;

    try {
        loggedInUser->getShoppingList(listName)->removeItem(itemName);
        //std::cout << "Item '" << itemName << "' rimosso dalla lista '" << listName << "'.\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
    }
}

void toggleItemPurchased() {
    if (!loggedInUser) {
        std::cout << "Devi essere loggato per modificare lo stato di acquisto di un item.\n";
        return;
    }

    std::string listName, itemName;

    std::cout << "Inserisci il nome della lista della spesa: ";
    std::cin >> listName;
    std::cout << "Inserisci il nome dell'item: ";
    std::cin >> itemName;

    try {
        loggedInUser->getShoppingList(listName)->toggleItemPurchased(itemName);
        //std::cout << "Stato di acquisto dell'item '" << itemName << "' modificato.\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
    }
}

void displayShoppingLists() {
    if (!loggedInUser) {
        std::cout << "Devi essere loggato per visualizzare le liste della spesa.\n";
        return;
    }

    std::cout << loggedInUser->printShoppingLists() << "\n";
}

void displayItemsInShoppingList() {
    if (!loggedInUser) {
        std::cout << "Devi essere loggato per visualizzare gli item di una lista della spesa.\n";
        return;
    }

    std::string listName;
    int choice;
    std::cout << "Inserisci il nome della lista della spesa: ";
    std::cin >> listName;

    std::cout << "Scegli il tipo di visualizzazione:\n";
    std::cout << "1. Tutti gli item\n";
    std::cout << "2. Item suddivisi per categoria\n";
    std::cout << "Seleziona un'opzione: ";
    std::cin >> choice;

    try {
        auto shoppingList = loggedInUser->getShoppingList(listName);
        if (choice == 1) {
            std::cout << shoppingList->printAllItems() << "\n";
        } else if (choice == 2) {
            std::cout << shoppingList->printItemsByCategory() << "\n";
        } else {
            std::cout << "Opzione non valida.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
    }
}

void updateItemQuantity() {
    if (!loggedInUser) {
        std::cout << "Devi essere loggato per aggiornare la quantita' di un item.\n";
        return;
    }

    std::string listName, itemName;
    int newQuantity;

    std::cout << "Inserisci il nome della lista della spesa: ";
    std::cin >> listName;
    std::cout << "Inserisci il nome dell'item: ";
    std::cin >> itemName;
    std::cout << "Inserisci la nuova quantita': ";
    std::cin >> newQuantity;

    try {
        loggedInUser->getShoppingList(listName)->updateItemQuantity(itemName, newQuantity);
        //std::cout << "Quantita' dell'item '" << itemName << "' aggiornata a " << newQuantity << ".\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
    }
}

void shareShoppingList() {
    if (!loggedInUser) {
        std::cout << "Devi essere loggato per condividere una lista della spesa.\n";
        return;
    }

    std::string listName, otherUserName;

    std::cout << "Inserisci il nome della lista della spesa: ";
    std::cin >> listName;
    std::cout << "Inserisci il nome dell'utente con cui condividere la lista: ";
    std::cin >> otherUserName;

    auto it = registeredUsers.find(otherUserName);
    if (it != registeredUsers.end()) {
        loggedInUser->shareShoppingList(*it->second, listName);
        //std::cout << "Lista condivisa con l'utente '" << otherUserName << "'.\n";
    } else {
        std::cout << "Utente non trovato.\n";
    }
}

void displayMenu() {
    std::cout << "\n=== Menu ===\n";
    std::cout << "1. Registrare un utente\n";
    std::cout << "2. Fare il login\n";
    std::cout << "3. Fare il logout\n";
    std::cout << "4. Creare una lista della spesa\n";
    std::cout << "5. Eliminare una lista della spesa\n";
    std::cout << "6. Aggiungere un item a una lista della spesa\n";
    std::cout << "7. Rimuovere un item da una lista della spesa\n";
    std::cout << "8. Modificare lo stato di acquisto di un item\n";
    std::cout << "9. Visualizzare tutte le liste della spesa\n";
    std::cout << "10. Visualizzare gli item di una lista della spesa\n";
    std::cout << "11. Modificare la quantita' di un item in una lista della spesa\n";
    std::cout << "12. Condividere una lista della spesa\n";
    std::cout << "13. Uscire\n";
    std::cout << "Seleziona un'opzione: ";
}

int main() {
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                logoutUser();
                break;
            case 4:
                createShoppingList();
                break;
            case 5:
                deleteShoppingList();
                break;
            case 6:
                addItemToShoppingList();
                break;
            case 7:
                removeItemFromShoppingList();
                break;
            case 8:
                toggleItemPurchased();
                break;
            case 9:
                displayShoppingLists();
                break;
            case 10:
                displayItemsInShoppingList();
                break;
            case 11:
                updateItemQuantity ();
                break;
            case 12:
                shareShoppingList();
                break;
            case 13:
                std::cout << "Uscita dal programma.\n";
                break;


            default:
                std::cout << "Opzione non valida. Riprova.\n";
        }
    } while (choice != 13);

    return 0;
}

