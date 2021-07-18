// https://github.com/manna-harbour/qmk_firmware/blob/crkbd/keyboards/crkbd/keymaps/manna-harbour/readme.org

#pragma once

#define EE_HANDS

#if defined MH_MODULE_TRACKPOINT && defined PS2_MOUSE_ENABLE
  // clock on pin 3 (d0, int0)
  #define PS2_CLOCK_PORT PORTD
  #define PS2_CLOCK_PIN PIND
  #define PS2_CLOCK_DDR DDRD
  #define PS2_CLOCK_BIT 0
  #define PS2_INT_INIT() do { EICRA |= ((1<<ISC01) | (0<<ISC00)); } while (0)
  #define PS2_INT_ON() do { EIMSK |= (1<<INT0); } while (0)
  #define PS2_INT_OFF() do { EIMSK &= ~(1<<INT0); } while (0)
  #define PS2_INT_VECT INT0_vect
  // data on pin 2 (d1)
  #define PS2_DATA_PORT PORTD
  #define PS2_DATA_PIN PIND
  #define PS2_DATA_DDR DDRD
  #define PS2_DATA_BIT 1
  #define PS2_MOUSE_ROTATE 270 // compensate for east-facing device orientation
  #define PS2_MOUSE_SCROLL_BTN_MASK (1 << PS2_MOUSE_BTN_MIDDLE)
  #define PS2_MOUSE_SCROLL_BTN_SEND TAPPING_TERM
  #define PS2_MOUSE_SCROLL_DIVISOR_V 3
  #define PS2_MOUSE_SCROLL_DIVISOR_H PS2_MOUSE_SCROLL_DIVISOR_V
#endif

#if defined MH_AUTO_BUTTONS
  #define MH_AUTO_BUTTONS_LAYER MBO
  #define MH_AUTO_BUTTONS_TIMEOUT 750
#endif

#if !defined MH_LOW_MOUSE && defined PS2_MOUSE_ENABLE
  #define PS2_MOUSE_X_MULTIPLIER 3
  #define PS2_MOUSE_Y_MULTIPLIER PS2_MOUSE_X_MULTIPLIER
  #define PS2_MOUSE_USE_2_1_SCALING
#endif

#if defined MH_LOW_MOUSE && defined MOUSEKEY_ENABLE
  #undef MOUSEKEY_TIME_TO_MAX
  #define MOUSEKEY_TIME_TO_MAX 128
#endif

#if defined MH_LOW_MOUSE
  #undef PRODUCT
  #define PRODUCT Corne Keyboard (crkbd) with low rate mouse
#endif

#if defined OLED_DRIVER_ENABLE
  #define OLED_TIMEOUT 30000 // ms
  #define MH_OLED_TIMEOUT
#endif

#if defined RGB_MATRIX_ENABLE
  #define RGB_MATRIX_KEYPRESSES
  #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
  #define RGB_DISABLE_WHEN_USB_SUSPENDED true
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
  #define RGB_MATRIX_HUE_STEP 8
  #define RGB_MATRIX_SAT_STEP 8
  #define RGB_MATRIX_VAL_STEP 8
  #define RGB_MATRIX_SPD_STEP 10
  #define MH_RGB_TOGGLE_OFF
#endif

#if defined RGBLIGHT_ENABLE
  #undef RGBLED_NUM
  #if defined MH_RGB_UNDERGLOW
    #define RGBLED_NUM 6
  #else
    #define RGBLED_NUM 27
  #endif
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_LIMIT_VAL 120
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_SPLIT
#endif

#if defined MH_DEBUG
  #define PS2_MOUSE_DEBUG_RAW
#endif

#define LAYOUT_miryoku( \
       K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09, \
       K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19, \
       K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29, \
       N30,   N31,   K32,   K33,   K34,   K35,   K36,   K37,   N38,   N39 \
) \
LAYOUT( \
KC_NO, K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   KC_NO, \
KC_NO, K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   KC_NO, \
KC_NO, K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   KC_NO, \
                     K32,   K33,   K34,   K35,   K36,   K37 \
)
