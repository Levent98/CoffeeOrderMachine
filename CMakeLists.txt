cmake_minimum_required(VERSION 3.16)

project(CoffeeOrderMachineQt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(CoffeeOrderMachineQt
    main.cpp
    mainwindow.cpp
    mainwindow.h
    coffee.cpp
    coffee.h
    coffeemenu.cpp
    coffeemenu.h
    coffeeorderservice.cpp
    coffeeorderservice.h
)

target_link_libraries(CoffeeOrderMachineQt PRIVATE Qt6::Widgets)
