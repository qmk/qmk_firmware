/**
 * noah.c
 */

#include "quantum.h"

void bootloader_jump(void) {
    // This board doesn't use the standard DFU bootloader, and no information is available regarding how to enter bootloader mode. All we can do here is reset.
    NVIC_SystemReset();
}

#ifdef RGBLIGHT_ENABLE
#include <string.h>
#include "rgblight.h"
#include "ws2812.h"
extern rgblight_config_t rgblight_config;

// led 0 for caps lock, led 1 for scroll lock, led 3 for num lock
// led 4 for layer 1, led 5 for layer 2, led 6 for layer 3, led 7 for layer 4
#if RGBLIGHT_LED_COUNT < 7
#error "MUST set the RGBLIGHT_LED_COUNT bigger than 7"
#endif
rgb_led_t noah_leds[RGBLIGHT_LED_COUNT];
static bool noah_led_mode = false;
void setleds_custom(rgb_led_t *ledarray, uint16_t num_leds) {
    memset(&noah_leds[0], 0, sizeof(noah_leds));
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
            ledarray[i].r = 0;
            ledarray[i].g = 0;
            ledarray[i].b = 0;
        }
    }
    if (noah_led_mode) {
      led_t led_state = host_keyboard_led_state();
      if (led_state.caps_lock) {
        noah_leds[0] = ledarray[0];
      }
      if (led_state.scroll_lock) {
        noah_leds[1] = ledarray[1];
      }
      if (led_state.num_lock) {
        noah_leds[2] = ledarray[2];
      }
      for (int32_t i = 0; i < 4; i++) {
        if(layer_state_is(i+1)) {
          noah_leds[i + 3] = ledarray[i + 3];
        }
      }
    } else {
      memcpy(&noah_leds[0], &ledarray[0], sizeof(noah_leds));
    }

  ws2812_setleds(noah_leds, RGBLIGHT_LED_COUNT);
}

const rgblight_driver_t rgblight_driver = {
    .init    = ws2812_init,
    .setleds = setleds_custom,
};
#endif

#ifdef RGB_MATRIX_ENABLE
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
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
  return process_record_user(keycode, record);
}
