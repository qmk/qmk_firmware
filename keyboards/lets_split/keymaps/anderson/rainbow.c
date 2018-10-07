#include "rainbow.h"

uint32_t rainbow_phase = 0;
uint32_t rainbow_timer = 0;

void rainbow_start(void) {
    rainbow_phase = 0;
    rainbow_timer = 0;
}

void rainbow_process(void) {
    if (!rainbow_timer) {
        rainbow_timer = timer_read();
        return;
    }
    if (timer_elapsed(rainbow_timer) > RAINBOW_INTERVAL) {
        rainbow_phase = (rainbow_phase + RAINBOW_SPEED) % 360;
        for (int i = 0; i < RGBLED_NUM; i++) {
            rgblight_sethsv_at(
                    (rainbow_phase + i * RAINBOW_STEP) % 360,
                    255,
                    255,
                    i
            );
            /*rgblight_sethsv_at(*/
            /*        rainbow_phase + (i * RAINBOW_STEP) % 360,*/
            /*        100,*/
            /*        100,*/
            /*        i*/
            /*);*/
        }
        rainbow_timer = timer_read();
    }
    /*rgblight_setrgb(*/
    /*        (solid_color >> 16) & 0xFF,*/
    /*        (solid_color >> 8) & 0xFF,*/
    /*        solid_color & 0xFF*/
    /*);*/
}
