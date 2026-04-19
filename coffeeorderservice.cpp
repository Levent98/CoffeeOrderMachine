#include "coffeeorderservice.h"
#include "coffeemenu.h"

#include <sstream>

CoffeeOrderService::CoffeeOrderService(CoffeeMenu& menu)
    : menu(menu) {}

Coffee CoffeeOrderService::getCoffeeById(int id) const {
    return menu.getCoffeeById(id);
}

std::string CoffeeOrderService::createPreparationMessage(const Coffee& coffee, int quantity) const {
    std::ostringstream oss;
    oss << "Thank you. Your order is being prepared.";
    oss << "\n\nSelected drink: " << coffee.getName();
    oss << "\nQuantity: " << quantity;
    oss << "\nIngredients per drink: ";

    const auto& ingredients = coffee.getIngredients();
    bool first = true;
    for (const auto& [name, amount] : ingredients) {
        if (!first) {
            oss << ", ";
        }
        oss << amount << " x " << name;
        first = false;
    }

    oss << "\n\nPlease wait while we prepare your coffee. Enjoy your drink.";
    return oss.str();
}
