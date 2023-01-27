cmake_minimum_required(VERSION 3.10)

project(NRF24L01 
        LANGUAGES CXX 
        DESCRIPTION "A Library to Simplify the Use of the NRF24L01 Chip")

file(GLOB SOURCES "src/*.cpp")

add_subdirectory("depends/RF24" "depends/RF24/build")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC src)