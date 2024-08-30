cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_COMPILER aarch64-rpi3-linux-gnu-gcc)
set(CMAKE_C_COMPILER aarch64-rpi3-linux-gnu-gcc)
set(CMAKE_BUILD_TYPE Debug)
project ("briefer")
include_directories(src/)

add_executable(briefer src/briefer.c src/briefer_lcd.c src/briefer_gpio.c)
target_link_libraries(briefer "pthread")
