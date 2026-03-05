#include "hdmi_video.h"

#include <stdio.h>

#include "pico/stdlib.h"

static const uint16_t* gLastFrame;
static uint16_t gLastWidth;
static uint16_t gLastHeight;

bool hdmi_video_init(void) {
#ifdef USE_PICODVI
    // Integrate your PicoDVI initialization here.
    // Keep function signature stable so only this module changes when backend changes.
    printf("[HDMI] USE_PICODVI enabled (backend hook placeholder).\n");
#else
    printf("[HDMI] Stub backend active (no physical HDMI output).\n");
#endif

    gLastFrame = NULL;
    gLastWidth = 0;
    gLastHeight = 0;
    return true;
}

void hdmi_video_present_frame(const uint16_t* rgb565_frame, uint16_t width, uint16_t height) {
    // Stub: stores pointer/size. Replace with DMA/scanout push for real HDMI backend.
    gLastFrame = rgb565_frame;
    gLastWidth = width;
    gLastHeight = height;

    (void)gLastFrame;
    (void)gLastWidth;
    (void)gLastHeight;
}

const char* hdmi_video_backend_name(void) {
#ifdef USE_PICODVI
    return "PicoDVI (integration hook)";
#else
    return "Stub (no signal)";
#endif
}
