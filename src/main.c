#include "project_config.h"
#include "controller.h"
#include "hdmi_video.h"
#include "nes_core.h"

#include <stdio.h>

#include "pico/stdlib.h"

static uint16_t g_framebuffer[PICO_NES_FRAME_WIDTH * PICO_NES_FRAME_HEIGHT];

static void wait_for_next_frame(absolute_time_t* next_deadline) {
    *next_deadline = delayed_by_us(*next_deadline, 1000000 / PICO_NES_TARGET_FPS);
    sleep_until(*next_deadline);
}

int main(void) {
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 0);

    controller_init();

    if (!hdmi_video_init()) {
        printf("[ERR] HDMI init failed. Check video hardware/dependencies.\n");
        while (true) {
            gpio_xor_mask(1u << PICO_DEFAULT_LED_PIN);
            sleep_ms(150);
        }
    }

    if (!nes_core_init()) {
        printf("[ERR] NES core init failed.\n");
        while (true) {
            gpio_xor_mask(1u << PICO_DEFAULT_LED_PIN);
            sleep_ms(300);
        }
    }

    printf("Pico NES started.\n");
    printf("Video backend: %s\n", hdmi_video_backend_name());
    printf("NES core: %s\n", nes_core_name());

    absolute_time_t next_deadline = get_absolute_time();
    uint32_t heartbeat_counter = 0;

    while (true) {
        const controller_state_t pad = controller_read_state();

        nes_input_t input = {
            .player1 = pad.player1,
            .player2 = pad.player2
        };

        nes_core_set_input(input);
        nes_core_step_frame(g_framebuffer, PICO_NES_FRAME_WIDTH, PICO_NES_FRAME_HEIGHT);
        hdmi_video_present_frame(g_framebuffer, PICO_NES_FRAME_WIDTH, PICO_NES_FRAME_HEIGHT);

        if ((heartbeat_counter++ % 60u) == 0u) {
            gpio_xor_mask(1u << PICO_DEFAULT_LED_PIN);
        }

        wait_for_next_frame(&next_deadline);
    }

    return 0;
}
