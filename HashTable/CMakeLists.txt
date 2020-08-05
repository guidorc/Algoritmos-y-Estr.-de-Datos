cmake_minimum_required(VERSION 3.16)
project(HashTable)

set(CMAKE_CXX_STANDARD 14)

add_executable(HashTable main.cpp HashTable/Tabla.h HashTable/Tabla.cpp)