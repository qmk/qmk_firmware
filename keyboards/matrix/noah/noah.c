/**
 * noah.c
 */

#include "noah.h"

#ifdef RGBLIGHT_ENABLE
#include <string.h>
#include "rgblight.h"
#include "ws2812.h"
extern rgblight_config_t rgblight_config;

// led 0 for caps lock, led 1 for scroll lock, led 3 for num lock
// led 4 for layer 1, led 5 for layer 2, led 6 for layer 3, led 7 for layer 4
#if RGBLED_NUM < 7
#error "MUST set the RGBLED_NUM bigger than 7"
#endif
LED_TYPE noah_leds[RGBLED_NUM];
static bool noah_led_mode = false;
void rgblight_set(void) {
    memset(&noah_leds[0], 0, sizeof(noah_leds));
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLED_NUM; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    }
    if (noah_led_mode) {
      uint8_t ind_led = host_keyboard_leds();
      if (IS_LED_ON(ind_led, USB_LED_CAPS_LOCK)) {
        noah_leds[0] = led[0];
      }
      if (IS_LED_ON(ind_led, USB_LED_SCROLL_LOCK)) {
        noah_leds[1] = led[1];
      }
      if (IS_LED_ON(ind_led, USB_LED_NUM_LOCK)) {
        noah_leds[2] = led[2];
      }
      for (int32_t i = 0; i < 4; i++) {
        if(layer_state_is(i+1)) {
          noah_leds[i + 3] = led[i + 3];
        }
      }
    } else {
      memcpy(&noah_leds[0], &led[0], sizeof(noah_leds));
    }

  ws2812_setleds(noah_leds, RGBLED_NUM);
}
#endif

void matrix_scan_kb(void) { matrix_scan_user(); }

void matrix_init_kb(void) {
  matrix_init_user();
}
__attribute__((weak))
void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_enable();
#endif

#ifdef RGB_MATRIX_ENABLE
  rgb_matrix_disable();
#endif
}

__attribute__((weak))
void matrix_scan_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_task();
#endif
}


#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */

// left CB
    {0, C1_9,   C3_10,  C4_10},
    {0, C1_10,  C2_10,  C4_11},
    {0, C1_11,  C2_11,  C3_11},
    {0, C1_12,  C2_12,  C3_12},
    {0, C1_13,  C2_13,  C3_13},
    {0, C1_14,  C2_14,  C3_14},
    {0, C1_15,  C2_15,  C3_15},
    {0, C1_16,  C2_16,  C3_16},

    {0, C5_9,   C4_9,   C6_9},
    {0, C5_16,  C4_16,  C6_16},

    {0, C9_9,   C8_9,   C7_9},
    {0, C9_10,  C8_10,  C7_10},
    {0, C9_11,  C8_11,  C7_11},
    {0, C9_12,  C8_12,  C7_12},
    {0, C9_13,  C8_13,  C7_13},
    {0, C9_14,  C8_14,  C7_14},
    {0, C9_15,  C8_15,  C6_14},
    {0, C9_16,  C7_15,  C6_15},

// left CA
    {0, C1_1,   C3_2,   C4_2},
    {0, C1_2,   C2_2,   C4_3},
    {0, C1_3,   C2_3,   C3_3},
    {0, C1_4,   C2_4,   C3_4},
    {0, C1_5,   C2_5,   C3_5},
    {0, C1_6,   C2_6,   C3_6},
    {0, C1_7,   C2_7,   C3_7},
    {0, C1_8,   C2_8,   C3_8},

    {0, C5_1,   C4_1,   C6_1},
    {0, C5_8,   C4_8,   C6_8},

    {0, C9_1,   C8_1,   C7_1},
    {0, C9_2,   C8_2,   C7_2},
    {0, C9_3,   C8_3,   C7_3},
    {0, C9_4,   C8_4,   C7_4},
    {0, C9_5,   C8_5,   C7_5},
    {0, C9_6,   C8_6,   C7_6},
    {0, C9_7,   C8_7,   C6_6},
    {0, C9_8,   C7_7,   C6_7},

// right CA
    {1, C1_1,   C3_2,   C4_2},
    {1, C1_2,   C2_2,   C4_3},
    {1, C1_3,   C2_3,   C3_3},
    {1, C1_4,   C2_4,   C3_4},
    {1, C1_5,   C2_5,   C3_5},
    {1, C1_6,   C2_6,   C3_6},
    {1, C1_7,   C2_7,   C3_7},
    {1, C1_8,   C2_8,   C3_8},

    {1, C5_1,   C4_1,   C6_1},
    {1, C5_8,   C4_8,   C6_8},

    {1, C9_1,   C8_1,   C7_1},
    {1, C9_2,   C8_2,   C7_2},
    {1, C9_3,   C8_3,   C7_3},
    {1, C9_4,   C8_4,   C7_4},
    {1, C9_5,   C8_5,   C7_5},
    {1, C9_6,   C8_6,   C7_6},
    {1, C9_7,   C8_7,   C6_6},
    {1, C9_8,   C7_7,   C6_7},
// right CB
    {1, C1_9,   C3_10,  C4_10},
    {1, C1_10,  C2_10,  C4_11},
    {1, C1_11,  C2_11,  C3_11},
    {1, C1_12,  C2_12,  C3_12},
    {1, C1_13,  C2_13,  C3_13},
    {1, C1_14,  C2_14,  C3_14},
    {1, C1_15,  C2_15,  C3_15},
    {1, C1_16,  C2_16,  C3_16},

    {1, C5_9,   C4_9,   C6_9},
    {1, C5_16,  C4_16,  C6_16},

    {1, C9_9,   C8_9,   C7_9},
    {1, C9_10,  C8_10,  C7_10},
    {1, C9_11,  C8_11,  C7_11},
    {1, C9_12,  C8_12,  C7_12},
    {1, C9_13,  C8_13,  C7_13},
    {1, C9_14,  C8_14,  C7_14},
    {1, C9_15,  C8_15,  C6_14},
    {1, C9_16,  C7_15,  C6_15},
};

led_config_t g_led_config = {
    {
        {  1,  2,      3,      4,      5,      6,   7,  36,     37,     38,      39,   40, NO_LED, 41},
        {  0,  8,     10,     11,     12,     13,  14,  44,     46,     47,      48,   49,     50, 51},
        { 30, 18,     26,      9,     19,     15,  16,  17,     55,     56,      57,   58,     59, 60},
        { 29, 31,     32,     33,     20,     21,  23,  22,     54,     62,      64,   65,     66, 63},
        { 34, 35,     27,     25,     67,     68,  69,  70,     71,     61,      53,   45,     42, 43},
    },
    {
        {  0, 16},{  0,  0},{ 15,  0},{ 30,  0},{ 45,  0},{ 60,  0},{ 75,  0},{ 90,  0},
        { 20, 16},{ 42, 32},
        { 45, 16},{ 50, 16},{ 65, 16},{ 80, 16},{ 95, 16},{ 70, 32},{ 84, 32},{ 98, 32},

        { 14, 32},{ 56, 32},{ 50, 48},{ 80, 48},{110, 48},{ 95, 48},{100, 64},{112, 64},
        { 42, 32},{ 38, 64},
        {  0, 32},{ 10, 48},{  0, 48},{ 20, 48},{ 35, 48},{ 65, 48},{  0, 64},{ 19, 64},

        {105,  0},{120,  0},{135,  0},{150,  0},{165,  0},{180,  0},{202,  0},{224,  0},
        {110, 16},{224, 16},
        {125, 16},{140, 16},{155, 16},{172, 16},{187, 16},{202, 16},{210, 32},{224, 32},

        {125, 48},{112, 32},{126, 32},{140, 32},{154, 32},{168, 32},{182, 32},{224, 48},
        {140, 48},{200, 48},
        {155, 48},{170, 48},{185, 48},{150, 64},{173, 64},{195, 64},{210, 64},{224, 64}
    },
    {
        1, 1, 4, 4, 4, 4, 4, 4,
        4, 4,
        4, 4, 4, 4, 4, 4, 4, 4,

        4, 4, 4, 4, 4, 4, 4, 4,
        4, 4,
        1, 1, 1, 4, 4, 4, 1, 1,

        4, 4, 4, 4, 4, 4, 1, 1,
        4, 1,
        4, 4, 4, 4, 4, 4, 4, 1,

        4, 4, 4, 4, 4, 4, 4, 1,
        4, 4,
        4, 4, 4, 1, 1, 1, 1, 1,
    }
};

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
    #ifdef RGBLIGHT_ENABLE
        case KC_F24: // switch the led mode on or off
        noah_led_mode = !noah_led_mode;
        return false;

    #ifdef RGB_MATRIX_ENABLE
        case KC_F13: // toggle rgb matrix
        rgb_matrix_toggle();
        return false;
        case KC_F14:
        rgb_matrix_step();
        return false;
    #endif
    #endif
        default:
        break;
    }
  }
  return true;
}
