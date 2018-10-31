#include "dmc12.h"

uint32_t dmc12_color = 0;
uint16_t dmc12_timer = 0;
int8_t dmc12_current = 0;
uint8_t dmc12_direction = 1;

void dmc12_start(uint32_t color) {
    dmc12_color = color;
    dmc12_timer = 0;
    dmc12_current = 0;
    dmc12_direction = 1;
}

void dmc12_process(void) {
    if (!dmc12_timer) {
        dmc12_timer = timer_read();
        return;
    }
    float dist_from_center = ((float)abs(dmc12_current - RGBLED_NUM / 2)) / ((float)RGBLED_NUM);
    if (timer_elapsed(dmc12_timer) > dist_from_center * LED_INTERVAL) {
        dmc12_current += dmc12_direction;
        if (dmc12_current == 0 || dmc12_current == RGBLED_NUM - 1) {
            dmc12_direction *= -1;
        }
        dmc12_timer = timer_read();
        for (int i = 0; i < RGBLED_NUM; i++) {
            if (i > dmc12_current - LED_RADIUS && i < dmc12_current + LED_RADIUS) {
                float intensity = (LED_RADIUS - abs(i - dmc12_current)) / ((float)LED_RADIUS);
                if (i != dmc12_current) {
                    intensity /= 4.0;
                }
                rgblight_setrgb_at(
                        ((dmc12_color >> 16) & 0xFF) * intensity,
                        ((dmc12_color >> 8) & 0xFF) * intensity,
                        (dmc12_color & 0xFF) * intensity,
                        i
                );
            } else {
                rgblight_setrgb_at(0, 0, 0, i);
            }
        }
    }
}
