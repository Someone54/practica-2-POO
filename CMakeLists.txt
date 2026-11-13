cmake_minimum_required(VERSION 3.16)

project(Practica2POO LANGUAGES CXX)

add_executable(
    practica2
    src/main.cpp
)

target_compile_features(
    practica2
    PRIVATE cxx_std_17
)

add_executable(
    studentScores
    src/studentScoresMain.cpp
)

target_compile_features(
    studentScores
    PRIVATE cxx_std_17
)

add_executable(
    memoryAnalysis
    src/memoryAnalysis.cpp
)

target_compile_features(
    memoryAnalysis
    PRIVATE cxx_std_17
)
