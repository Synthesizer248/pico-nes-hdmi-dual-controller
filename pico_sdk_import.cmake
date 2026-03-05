# This is a standard Pico SDK import helper.
# Set PICO_SDK_PATH to your Pico SDK checkout path.

if (DEFINED ENV{PICO_SDK_PATH})
    set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
endif ()

if (NOT PICO_SDK_PATH)
    message(FATAL_ERROR "PICO_SDK_PATH is not set. Export PICO_SDK_PATH before configuring.")
endif ()

if (NOT EXISTS ${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
    message(FATAL_ERROR "PICO_SDK_PATH does not appear to contain a valid Pico SDK checkout.")
endif ()

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
