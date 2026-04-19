#ifndef COFFEE_H
#define COFFEE_H

#include <map>
#include <string>

class Coffee {
public:
    Coffee() = default;
    Coffee(const std::string& name, int price, const std::map<std::string, int>& ingredients);

    std::string getName() const;
    int getPrice() const;
    const std::map<std::string, int>& getIngredients() const;

private:
    std::string name;
    int price = 0;
    std::map<std::string, int> ingredients;
};

#endif
