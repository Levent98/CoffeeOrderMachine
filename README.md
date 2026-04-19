# Coffee Order Machine

A simple C++ console-based coffee ordering system built using object-oriented design principles.
This project simulates a coffee machine where users can browse a menu and place orders interactively.

---

## Features

* Interactive coffee menu
* Multiple coffee types with ingredients
* Price management per product
* Order processing simulation
* Modular and extensible architecture
* Clean object-oriented design

---

## Architecture

The project is structured using a layered approach with clear separation of responsibilities.

### Core Components

#### Coffee

* Represents a coffee item
* Contains:

  * Name
  * Price
  * Ingredients

#### CoffeeMenu

* Stores available coffee options
* Displays menu to the user
* Provides access to selected coffee

#### CoffeeOrderService

* Handles user interaction
* Processes orders
* Simulates preparation flow

#### CoffeeApp

* Entry point of the application
* Coordinates menu and service layer

---

## Project Structure

```
kahvesiparisi/
│
├── main.cpp
├── coffee.h / coffee.cpp
├── coffeemenu.h / coffeemenu.cpp
├── coffeeorderservice.h / coffeeorderservice.cpp
├── coffeeapp.h / coffeeapp.cpp
├── CMakeLists.txt
└── umldiyagramı.txt
```

---

## How to Run

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
./CoffeeOrderMachine
```

### Manual Compilation

```bash
g++ *.cpp -o coffee_app
./coffee_app
```

---

## Design Highlights

* Object-oriented design with clear class responsibilities
* Separation of concerns between UI, business logic, and data
* Extensible structure for adding new features or products

---

## UML Diagram

See:
umldiyagramı.txt

---

## Author

Levent Keskin
Embedded and Software Engineer

---

## License

This project is developed for educational purposes.
