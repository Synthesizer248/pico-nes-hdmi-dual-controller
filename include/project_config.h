#pragma once

#include <stdint.h>

#define PICO_NES_FRAME_WIDTH   256
#define PICO_NES_FRAME_HEIGHT  240
#define PICO_NES_TARGET_FPS    60

// GPIO assignments for custom two-player push-button controllers.
// Active-low buttons with pull-ups enabled in firmware.

// Player 1
#define PIN_P1_A       2
#define PIN_P1_B       3
#define PIN_P1_SELECT  4
#define PIN_P1_START   5
#define PIN_P1_UP      6
#define PIN_P1_DOWN    7
#define PIN_P1_LEFT    8
#define PIN_P1_RIGHT   9

// Player 2
#define PIN_P2_A       10
#define PIN_P2_B       11
#define PIN_P2_SELECT  12
#define PIN_P2_START   13
#define PIN_P2_UP      14
#define PIN_P2_DOWN    15
#define PIN_P2_LEFT    16
#define PIN_P2_RIGHT   17

// Status LED used for basic heartbeat.
#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 25
#endif

// Debounce integrator threshold (higher = stronger filtering).
#define CONTROLLER_DEBOUNCE_THRESHOLD 3
