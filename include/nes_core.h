#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t player1;
    uint8_t player2;
} nes_input_t;

bool nes_core_init(void);
const char* nes_core_name(void);
void nes_core_set_input(nes_input_t input);

// Produces one NES frame into RGB565 output buffer.
// Buffer size must be width * height entries.
void nes_core_step_frame(uint16_t* rgb565_out, uint16_t width, uint16_t height);
