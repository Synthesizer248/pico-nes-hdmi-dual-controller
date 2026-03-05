#pragma once

#include <stdbool.h>
#include <stdint.h>

bool hdmi_video_init(void);
void hdmi_video_present_frame(const uint16_t* rgb565_frame, uint16_t width, uint16_t height);

// Useful for status text/logging.
const char* hdmi_video_backend_name(void);
