cmake_minimum_required(VERSION 3.9.0)

project(yugen VERSION 0.1 LANGUAGES C ASM)

add_compile_options(
    -ffreestanding
    -O2
    -Wall
    -Wextra
    -std=gnu99
    -nostdlib
    -masm=intel
)

add_subdirectory(kernel)