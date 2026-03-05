cmake_minimum_required(VERSION 3.19)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(pico_sdk_import.cmake)

project(pico_nes_hdmi_dual_controller C CXX ASM)

pico_sdk_init()

option(USE_PICODVI "Enable HDMI/DVI output through PicoDVI dependency" OFF)

add_subdirectory(src)
