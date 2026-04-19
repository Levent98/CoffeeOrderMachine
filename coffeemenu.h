#ifndef COFFEEMENU_H
#define COFFEEMENU_H

#include "coffee.h"

#include <cstddef>
#include <map>
#include <vector>

class CoffeeMenu {
public:
    static CoffeeMenu& getInstance();

    Coffee getCoffeeById(int id) const;
    size_t getMenuSize() const;
    std::vector<int> getCoffeeIds() const;

    CoffeeMenu(const CoffeeMenu&) = delete;
    CoffeeMenu& operator=(const CoffeeMenu&) = delete;

private:
    CoffeeMenu();
    std::map<int, Coffee> coffees;
};

#endif
