#include "controller.h"
#include "project_config.h"

#include "hardware/gpio.h"

typedef struct {
    uint8_t pin;
    uint8_t mask;
} button_pin_t;

typedef struct {
    bool stable_pressed;
    uint8_t integrator;
} debounce_t;

static const button_pin_t kPlayer1Map[] = {
    { PIN_P1_A, NES_BTN_A },
    { PIN_P1_B, NES_BTN_B },
    { PIN_P1_SELECT, NES_BTN_SELECT },
    { PIN_P1_START, NES_BTN_START },
    { PIN_P1_UP, NES_BTN_UP },
    { PIN_P1_DOWN, NES_BTN_DOWN },
    { PIN_P1_LEFT, NES_BTN_LEFT },
    { PIN_P1_RIGHT, NES_BTN_RIGHT }
};

static const button_pin_t kPlayer2Map[] = {
    { PIN_P2_A, NES_BTN_A },
    { PIN_P2_B, NES_BTN_B },
    { PIN_P2_SELECT, NES_BTN_SELECT },
    { PIN_P2_START, NES_BTN_START },
    { PIN_P2_UP, NES_BTN_UP },
    { PIN_P2_DOWN, NES_BTN_DOWN },
    { PIN_P2_LEFT, NES_BTN_LEFT },
    { PIN_P2_RIGHT, NES_BTN_RIGHT }
};

static debounce_t gDebounce[16];

static void init_button_pin(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
}

static bool read_pressed_raw(uint8_t pin) {
    // Active-low button.
    return gpio_get(pin) == 0;
}

static bool debounce_update(debounce_t* db, bool raw_pressed) {
    if (raw_pressed == db->stable_pressed) {
        db->integrator = 0;
        return db->stable_pressed;
    }

    if (db->integrator < CONTROLLER_DEBOUNCE_THRESHOLD) {
        db->integrator++;
    }

    if (db->integrator >= CONTROLLER_DEBOUNCE_THRESHOLD) {
        db->stable_pressed = raw_pressed;
        db->integrator = 0;
    }

    return db->stable_pressed;
}

static uint8_t read_player(const button_pin_t* mapping, int map_size, int debounce_base) {
    uint8_t state = 0;
    for (int i = 0; i < map_size; ++i) {
        const bool raw = read_pressed_raw(mapping[i].pin);
        const bool stable = debounce_update(&gDebounce[debounce_base + i], raw);
        if (stable) {
            state |= mapping[i].mask;
        }
    }

    // Ignore impossible opposite directions.
    if ((state & NES_BTN_UP) && (state & NES_BTN_DOWN)) {
        state &= (uint8_t)~(NES_BTN_UP | NES_BTN_DOWN);
    }
    if ((state & NES_BTN_LEFT) && (state & NES_BTN_RIGHT)) {
        state &= (uint8_t)~(NES_BTN_LEFT | NES_BTN_RIGHT);
    }

    return state;
}

void controller_init(void) {
    for (unsigned i = 0; i < sizeof(kPlayer1Map) / sizeof(kPlayer1Map[0]); ++i) {
        init_button_pin(kPlayer1Map[i].pin);
    }
    for (unsigned i = 0; i < sizeof(kPlayer2Map) / sizeof(kPlayer2Map[0]); ++i) {
        init_button_pin(kPlayer2Map[i].pin);
    }
}

controller_state_t controller_read_state(void) {
    controller_state_t out;
    out.player1 = read_player(kPlayer1Map, (int)(sizeof(kPlayer1Map) / sizeof(kPlayer1Map[0])), 0);
    out.player2 = read_player(kPlayer2Map, (int)(sizeof(kPlayer2Map) / sizeof(kPlayer2Map[0])), 8);
    return out;
}

bool controller_self_test(void) {
    const button_pin_t* sets[] = { kPlayer1Map, kPlayer2Map };
    const int sizes[] = {
        (int)(sizeof(kPlayer1Map) / sizeof(kPlayer1Map[0])),
        (int)(sizeof(kPlayer2Map) / sizeof(kPlayer2Map[0]))
    };

    for (int s = 0; s < 2; ++s) {
        for (int i = 0; i < sizes[s]; ++i) {
            const uint8_t pin = sets[s][i].pin;
            if (pin > 29) {
                return false;
            }
        }
    }

    return true;
}
