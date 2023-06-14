#include <smoothled.h>

static uint32_t sourceColor = 0x000000;
static uint32_t currentColor = 0x000000;
static uint32_t targetColor = 0x000000;
static int32_t smoothledTimer = -1;

void smoothled_set(uint32_t color) {
    smoothledTimer = timer_read32();
    sourceColor = currentColor;
    targetColor = color;
}

void smoothled_process(void) {
    if (smoothledTimer < 0) {
        return;
    }
    int32_t kb = timer_elapsed32(smoothledTimer);
    int32_t ka = SMOOTH_DURATION - kb;
    if (kb > SMOOTH_DURATION) {
        kb = SMOOTH_DURATION;
        ka = 0;
        smoothledTimer = -1;
    }
    currentColor = 0;
    for (int i = 2; i >= 0; i--) {
        uint32_t shift = i * 8;
        currentColor |= (ka * ((uint32_t)(sourceColor >> shift) & 0xFF) + kb * ((uint32_t)(targetColor >> shift) & 0xFF)) / SMOOTH_DURATION;
        /*currentColor |= ((targetColor >> shift) & 0xFF);*/
        currentColor <<= 8;
    }
    currentColor >>= 8;
    rgblight_setrgb((currentColor >> 16) & 0xFF, (currentColor >> 8) & 0xFF, currentColor & 0xFF);
}
