cmake_minimum_required(VERSION 3.24)
project(asm_decoder C)

set(CMAKE_C_STANDARD 11)

add_executable(asm_decoder main.c instructions.h)
