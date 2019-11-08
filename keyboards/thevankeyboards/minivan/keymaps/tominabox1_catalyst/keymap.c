#include QMK_KEYBOARD_H
#include "tominabox1.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    *  |GESC| Q  | W  | F  | P  | G  | J  | L  | U  | Y  | ;  | BSPC |
    *  | TAB | A  | R  | S  | T  | D  | H  | N  | E  | I  | O  | '   |
    *  |SHIFT | Z  | X  | C  | V  | B  | K  | M  | ,  | UP  | . | /  |
    *  |CTRL | WIN   | ALT |   ENTR   |  SPACE | LFT  |DOWN|RGHT|FKEY|
    */

    [_BASE] = LAYOUT_arrow_wrapper(
      __________________MINIVAN1_________________,
      __________________MINIVAN2_________________,
      __________________MINIVAN3_________________,
      __________________MINIVAN4_________________
    ),

    /*
    *  | ~  | !  | @  | #  | $  | %  | ^  | &  | *  | (  | )  | DEL  |
    *  |     |    |    |    |    |    |    |  _ |  + |  { |  } | PIPE|
    *  |SHIFT |    |    |    |    |    |    |    |PGDN| UP  | ? | /  |
    *  |CTRL | WIN   | ALT |   ENTR   |  SPACE | LFT  |DOWN|RGHT|FKEY|
    */

    [_LOWER] = LAYOUT_arrow_wrapper(
      _________________LOWER_1___________________,
      _________________LOWER_2___________________,
      __________________MININUM3_________________,
      __________________MININUM4_________________
    ),

    /*
    *  | `  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  | BSPC |
    *  | INS |    |    |    |    |    |    |  - |  = |  [ |  ] |  \  |
    *  |      |    |    |    |    |    |    |    |    |    |  / |    |
    *  |CTRL | WIN   | ALT |   ENTR   |  SPACE | LFT  |DOWN|RGHT|FKEY|
    */

    [_RAISE] = LAYOUT_arrow_wrapper(
      ___________________RAISE1__________________,
      ___________________RAISE2__________________,
      ___________________RVAN_3__________________,
      ___________________RVAN_4__________________
    ),

    /*
     *  |REST|EERS|    |    |    |    |    |    |    |    |    |      |
     *  |     |    |    |    |    |    |    |    |    |    |    |     |
     *  |      |    |    |    |    |    |    |    |    |    |    |    |
     *  |     |       |     |   ENTR   |  SPACE |      |    |    |    |
     */

    [_ADJUST] = LAYOUT_arrow_wrapper(
      ___________________ADJST1__________________,
      ___________________ADJST2__________________,
      ___________________ADJVAN3_________________,
      ___________________ADJVAN4_________________
    ),

    /*
     *  |    | F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10|      |
     *  |     |    |    |    |    |    |    |    |    |F11 | F12|     |
     *  |      |    |    |    |    |    |    |    |    |    |    |    |
     *  |     |       |     |          |        | FKEY |    |    |    |
     */

    [_FKEY] = LAYOUT_arrow_wrapper(
      ___________________FKEY1___________________,
      ___________________FKEY2___________________,
      ___________________FVAN_3__________________,
      ___________________FVAN_4__________________
    ),
  };

const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {100, 30, 5, 1};

  void keyboard_post_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      // Set up RGB effects on _only_ the third LED (index 2)
      rgblight_set_effect_range(2, 1);
      // Set LED effects to breathing mode in a tealish blue color
      rgblight_sethsv_noeeprom(0, 255, 50);
      rgblight_mode_noeeprom(RGBLIGHT_EFFECT_BREATHING+3);

      // Init the first two LEDs to a static color
      setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
      setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
      rgblight_set();
    #endif //RGBLIGHT_ENABLE
  }

  uint32_t layer_state_set_keymap(uint32_t state){
    #ifdef RGBLIGHT_ENABLE
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led1r = 0; uint8_t led1g = 0; uint8_t led1b = 0;
      if (layer_state_cmp(state, _LOWER)) {
        led0r = 25;
        led0g = 25;
      }
      if (layer_state_cmp(state, _RAISE)) {
        led1g = 25;
        led1b = 25;
      }

      if (layer_state_cmp(state, _FKEY)) {
        led0b = 25;
        led0r = 25;
        led1b = 25;
        led1r = 25;
      }
      if (layer_state_cmp(state, _ADJUST)) {
        led1r = 0;
        led1b = 25;
      }
      setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]);
      setrgb(led1r, led1g, led1b, (LED_TYPE *)&led[1]);
      rgblight_set();

    #endif //RGBLIGHT_ENABLE
    return state;
  }

  void led_set_user(uint8_t usb_led) {
    if(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
      rgblight_set_effect_range(2, 1);
      rgblight_sethsv_noeeprom(180, 200, 50);
      rgblight_mode_noeeprom(0);
    } else{
      rgblight_set_effect_range(2, 1);
      rgblight_sethsv_noeeprom(125, 200, 50);
      rgblight_mode_noeeprom(RGBLIGHT_EFFECT_BREATHING+3);
    }
  }
