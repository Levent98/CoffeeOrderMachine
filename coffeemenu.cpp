#include "coffeemenu.h"

#include <stdexcept>

CoffeeMenu::CoffeeMenu() {
    coffees.emplace(1, Coffee("Espresso", 20, {{"Espresso", 1}}));
    coffees.emplace(2, Coffee("Double Espresso", 27, {{"Espresso", 2}}));
    coffees.emplace(3, Coffee("Cappuccino", 28, {{"Espresso", 1}, {"Steamed Milk", 2}, {"Milk Foam", 2}}));
    coffees.emplace(4, Coffee("Caffe Latte", 28, {{"Espresso", 1}, {"Steamed Milk", 3}, {"Milk Foam", 1}}));
    coffees.emplace(5, Coffee("Mocha", 32, {{"Espresso", 1}, {"Steamed Milk", 1}, {"Milk Foam", 1}, {"Hot Chocolate", 2}}));
    coffees.emplace(6, Coffee("Americano", 26, {{"Espresso", 1}, {"Hot Water", 4}}));
    coffees.emplace(7, Coffee("Hot Water", 5, {{"Hot Water", 5}}));
}

CoffeeMenu& CoffeeMenu::getInstance() {
    static CoffeeMenu instance;
    return instance;
}

Coffee CoffeeMenu::getCoffeeById(int id) const {
    auto it = coffees.find(id);
    if (it != coffees.end()) {
        return it->second;
    }
    throw std::out_of_range("Invalid coffee ID");
}

size_t CoffeeMenu::getMenuSize() const {
    return coffees.size();
}

std::vector<int> CoffeeMenu::getCoffeeIds() const {
    std::vector<int> ids;
    ids.reserve(coffees.size());
    for (const auto& [id, _coffee] : coffees) {
        ids.push_back(id);
    }
    return ids;
}
