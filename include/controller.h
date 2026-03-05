#pragma once

#include <stdbool.h>
#include <stdint.h>

enum {
    NES_BTN_A      = 1u << 0,
    NES_BTN_B      = 1u << 1,
    NES_BTN_SELECT = 1u << 2,
    NES_BTN_START  = 1u << 3,
    NES_BTN_UP     = 1u << 4,
    NES_BTN_DOWN   = 1u << 5,
    NES_BTN_LEFT   = 1u << 6,
    NES_BTN_RIGHT  = 1u << 7
};

typedef struct {
    uint8_t player1;
    uint8_t player2;
} controller_state_t;

void controller_init(void);
controller_state_t controller_read_state(void);

// Returns true if all controller GPIOs are readable.
bool controller_self_test(void);
