cmake_minimum_required(VERSION 3.29)
project(sortingAlgorithm)

set(CMAKE_CXX_STANDARD 20)
# Добавить команду для копирования файлов данных в директорию сборки
set(DATA_FILES d16.txt d100.txt d500.txt d1000.txt d5000.txt)

# Копирование файлов в директорию сборки (CMAKE_BINARY_DIR)
foreach(file ${DATA_FILES})
    configure_file(${CMAKE_SOURCE_DIR}/${file} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()

add_executable(sortingAlgorithm main.cpp)
