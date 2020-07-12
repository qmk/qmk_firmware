#include "terrazzo.h"

#ifdef LED_MATRIX_ENABLE
    #include "is31fl3731-simple.h"
    #include <math.h>
    #include <print.h>
    #include "quantum.h"

const is31_led g_is31_leds[LED_DRIVER_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 * https://cdn-learn.adafruit.com/downloads/pdf/adafruit-15x7-7x15-charlieplex-led-matrix-charliewing-featherwing.pdf
 *  driver
 *  |   LED address
 *  |   | */
    {0, C1_2}, {0, C1_3}, {0, C1_4}, {0, C1_5}, {0, C1_6}, {0, C1_7}, {0, C1_8},
    {0, C2_2}, {0, C2_3}, {0, C2_4}, {0, C2_5}, {0, C2_6}, {0, C2_7}, {0, C2_8},
    {0, C3_2}, {0, C3_3}, {0, C3_4}, {0, C3_5}, {0, C3_6}, {0, C3_7}, {0, C3_8},
    {0, C4_2}, {0, C4_3}, {0, C4_4}, {0, C4_5}, {0, C4_6}, {0, C4_7}, {0, C4_8},
    {0, C5_2}, {0, C5_3}, {0, C5_4}, {0, C5_5}, {0, C5_6}, {0, C5_7}, {0, C5_8},
    {0, C6_2}, {0, C6_3}, {0, C6_4}, {0, C6_5}, {0, C6_6}, {0, C6_7}, {0, C6_8},
    {0, C7_2}, {0, C7_3}, {0, C7_4}, {0, C7_5}, {0, C7_6}, {0, C7_7}, {0, C7_8},
    {0, C8_2}, {0, C8_3}, {0, C8_4}, {0, C8_5}, {0, C8_6}, {0, C8_7}, {0, C8_8},
    //
    {0, C8_15},{0, C8_14},{0, C8_13},{0, C8_12},{0, C8_11},{0, C8_10},{0, C8_9},
    {0, C7_15},{0, C7_14},{0, C7_13},{0, C7_12},{0, C7_11},{0, C7_10},{0, C7_9},
    {0, C6_15},{0, C6_14},{0, C6_13},{0, C6_12},{0, C6_11},{0, C6_10},{0, C6_9},
    {0, C5_15},{0, C5_14},{0, C5_13},{0, C5_12},{0, C5_11},{0, C5_10},{0, C5_9},
    {0, C4_15},{0, C4_14},{0, C4_13},{0, C4_12},{0, C4_11},{0, C4_10},{0, C4_9},
    {0, C3_15},{0, C3_14},{0, C3_13},{0, C3_12},{0, C3_11},{0, C3_10},{0, C3_9},
    {0, C2_15},{0, C2_14},{0, C2_13},{0, C2_12},{0, C2_11},{0, C2_10},{0, C2_9}
};

#define TERRAZZO_EFFECT(name)
#define TERRAZZO_EFFECT_IMPLS

#include "terrazzo_effects/terrazzo_effects.inc"

#undef TERRAZZO_EFFECT_IMPLS
#undef TERRAZZO_EFFECT

uint8_t terrazzo_led_index = 0;
uint8_t terrazzo_dir = 1;
uint8_t terrazzo_effect = 1;

void terrazzo_set_pixel(uint8_t x, uint8_t y, uint8_t value) {
  uint8_t target = y * LED_MATRIX_COLS + x;
  if (target < LED_DRIVER_LED_COUNT && target >= 0) {
    // TODO: Wrapper function with max value check
    led_matrix_set_index_value(y * LED_MATRIX_COLS + x, value);
  }
}


void terrazzo_draw_at(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t image[]) {
    uint8_t index = 0;
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            uint8_t pixel_value = image[index];
            if (pixel_value != 0) {
               terrazzo_set_pixel(x + h, y + v, image[index]);
            }
            index++;
        }
    }
}

void terrazzo_scroll_pixel(bool clockwise) {
    uint8_t speed = 1;
    terrazzo_dir = clockwise;

    if (clockwise) {
        terrazzo_led_index = terrazzo_led_index + speed;
    } else {
        terrazzo_led_index = terrazzo_led_index - speed;
    } 
    
    if (terrazzo_led_index >= LED_DRIVER_LED_COUNT) {
        terrazzo_led_index = 0;
    } else if (terrazzo_led_index <= 0 ) {
        terrazzo_led_index = LED_DRIVER_LED_COUNT - 1;
    }
}

void terrazzo_step_mode(void) {
    terrazzo_effect++;
    if (terrazzo_effect >= TERRAZZO_EFFECT_MAX) {
        terrazzo_effect = 1;
    }
}

void terrazzo_step_mode_reverse(void) {
    terrazzo_effect--;
    if (terrazzo_effect < 1) {
        terrazzo_effect = TERRAZZO_EFFECT_MAX - 1;
    }
}

void terrazzo_render(void) {
    // led_matrix_set_index_value(terrazzo_led_index, 5);
    switch(terrazzo_effect) {
        case TERRAZZO_NONE:
            led_matrix_set_index_value_all(0);
            break;
        // ---------------------------------------------
        // -----Begin rgb effect switch case macros-----
        #define TERRAZZO_EFFECT(name, ...)              \
            case TERRAZZO_EFFECT_##name:                \
                name(terrazzo_led_index, terrazzo_dir); \
                break;
        #include "terrazzo_effects/terrazzo_effects.inc"
        #undef TERRAZZO_EFFECT
        // -----End rgb effect switch case macros-------
        // ---------------------------------------------
    }
}

void led_matrix_indicators_kb(void) {
  terrazzo_render();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // #ifdef TYPE_ANIMATE
        switch(keycode) {
            case KC_BSPC:
                terrazzo_scroll_pixel(0);
                return true;
            default:
              terrazzo_scroll_pixel(1);
              break;

        }
        //#endif
    }
    return process_record_user(keycode, record);
}


#endif