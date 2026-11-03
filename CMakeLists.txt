cmake_minimum_required(VERSION 3.16)
project(Practica2POO LANGUAGES CXX)

add_executable(practica2 src/main.cpp)
target_compile_features(practica2 PRIVATE cxx_std_17)
