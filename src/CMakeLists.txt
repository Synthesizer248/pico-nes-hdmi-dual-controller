set(APP_NAME pico_nes_hdmi_dual_controller)

set(APP_SOURCES
    main.c
    controller.c
    hdmi_video.c
    nes_core_stub.c
)

add_executable(${APP_NAME} ${APP_SOURCES})

target_include_directories(${APP_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../include
)

target_link_libraries(${APP_NAME}
    pico_stdlib
    hardware_gpio
    hardware_timer
    hardware_sync
)

if (USE_PICODVI)
    if (EXISTS ${CMAKE_SOURCE_DIR}/lib/PicoDVI/CMakeLists.txt)
        add_subdirectory(${CMAKE_SOURCE_DIR}/lib/PicoDVI ${CMAKE_BINARY_DIR}/PicoDVI)
        target_compile_definitions(${APP_NAME} PRIVATE USE_PICODVI=1)
        # Replace this target name if your PicoDVI fork uses a different exported target.
        target_link_libraries(${APP_NAME} picodvi)
    else()
        message(FATAL_ERROR "USE_PICODVI=ON but lib/PicoDVI not found. Run scripts/fetch_dependencies.ps1.")
    endif()
endif()

pico_enable_stdio_uart(${APP_NAME} 0)
pico_enable_stdio_usb(${APP_NAME} 1)

pico_add_extra_outputs(${APP_NAME})
