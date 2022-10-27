cmake_minimum_required (VERSION 3.15 FATAL_ERROR)

project(WiredPanda
    VERSION 4.1.10
    DESCRIPTION "Logic Circuit Simulator"
    LANGUAGES CXX
)

add_compile_definitions(APP_VERSION="4.1.10")

if (MSVC)
    cmake_policy(SET CMP0092 NEW) # don't add W3 by default
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_compile_definitions(
    QT_USE_QSTRINGBUILDER
    QT_STRICT_ITERATORS
)

include_directories(./app)
include_directories(./app/arduino)
include_directories(./app/element)
include_directories(./app/logicelement)
include_directories(./app/nodes)

add_subdirectory(app)
add_subdirectory(test)
