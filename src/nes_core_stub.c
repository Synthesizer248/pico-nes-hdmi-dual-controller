#include "nes_core.h"
#include "controller.h"

#include <stddef.h>
#include <stdint.h>

static nes_input_t gInput;
static uint16_t gFrameCounter;

typedef struct {
    int x;
    int y;
    uint16_t color;
} sprite_t;

static sprite_t gP1 = { 60, 60, 0xF800 };   // red
static sprite_t gP2 = { 180, 140, 0x07E0 }; // green

static uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) {
    return (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

static void clear_frame(uint16_t* fb, uint16_t width, uint16_t height) {
    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width; ++x) {
            const uint8_t shade = (uint8_t)((x + y + gFrameCounter) & 0x3F);
            fb[y * width + x] = rgb((uint8_t)(shade * 2), 0, (uint8_t)(80 + shade));
        }
    }
}

static void move_sprite(sprite_t* s, uint8_t input, uint16_t width, uint16_t height) {
    if (input & NES_BTN_UP) {
        s->y -= 2;
    }
    if (input & NES_BTN_DOWN) {
        s->y += 2;
    }
    if (input & NES_BTN_LEFT) {
        s->x -= 2;
    }
    if (input & NES_BTN_RIGHT) {
        s->x += 2;
    }

    if (s->x < 0) s->x = 0;
    if (s->y < 0) s->y = 0;
    if (s->x > (int)width - 12) s->x = (int)width - 12;
    if (s->y > (int)height - 12) s->y = (int)height - 12;
}

static void draw_sprite(uint16_t* fb, uint16_t width, uint16_t height, const sprite_t* s) {
    for (int yy = 0; yy < 10; ++yy) {
        const int py = s->y + yy;
        if (py < 0 || py >= (int)height) continue;

        for (int xx = 0; xx < 10; ++xx) {
            const int px = s->x + xx;
            if (px < 0 || px >= (int)width) continue;

            fb[(uint32_t)py * width + (uint32_t)px] = s->color;
        }
    }
}

static void draw_input_flags(uint16_t* fb, uint16_t width, uint8_t input, uint16_t ybase, uint16_t color) {
    for (int i = 0; i < 8; ++i) {
        const bool set = (input & (1u << i)) != 0;
        const uint16_t x0 = (uint16_t)(8 + i * 14);
        const uint16_t y0 = ybase;

        for (uint16_t y = 0; y < 8; ++y) {
            for (uint16_t x = 0; x < 10; ++x) {
                const uint32_t idx = (uint32_t)(y0 + y) * width + (x0 + x);
                fb[idx] = set ? color : 0x18C3;
            }
        }
    }
}

bool nes_core_init(void) {
    gInput.player1 = 0;
    gInput.player2 = 0;
    gFrameCounter = 0;
    return true;
}

const char* nes_core_name(void) {
    return "Stub NES Core (replace with real emulator)";
}

void nes_core_set_input(nes_input_t input) {
    gInput = input;
}

void nes_core_step_frame(uint16_t* rgb565_out, uint16_t width, uint16_t height) {
    if (rgb565_out == NULL || width == 0 || height == 0) {
        return;
    }

    gFrameCounter++;

    move_sprite(&gP1, gInput.player1, width, height);
    move_sprite(&gP2, gInput.player2, width, height);

    clear_frame(rgb565_out, width, height);
    draw_sprite(rgb565_out, width, height, &gP1);
    draw_sprite(rgb565_out, width, height, &gP2);

    draw_input_flags(rgb565_out, width, gInput.player1, 8, 0xFFFF);
    draw_input_flags(rgb565_out, width, gInput.player2, 24, 0xFFE0);
}
