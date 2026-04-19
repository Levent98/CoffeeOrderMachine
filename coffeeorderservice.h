#ifndef COFFEEORDERSERVICE_H
#define COFFEEORDERSERVICE_H

#include "coffee.h"

#include <string>

class CoffeeMenu;

class CoffeeOrderService {
public:
    explicit CoffeeOrderService(CoffeeMenu& menu);

    Coffee getCoffeeById(int id) const;
    std::string createPreparationMessage(const Coffee& coffee, int quantity) const;

private:
    CoffeeMenu& menu;
};

#endif
