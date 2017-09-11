cmake_minimum_required(VERSION 3.8)
project(VendingWithC)

set(CMAKE_C_STANDARD 90)

file(GLOB SOURCES *.c *h)
add_executable(VendingWithC ${SOURCES})