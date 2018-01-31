#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define QWERTY 0 // qwerty layer 
#define HALFQWERTY 1 // mirrored qwerty layer 
#define DVORAK 2 // dvorak layer 
#define HALFDVORAK 3 // mirrored dvorak layer 
#define SYMB 5 // symbols
#define MDIA 6 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: qwerty
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |  BSPC  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |ENTER   |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL|ALT  |CTL-TAB|CTLShTab| LGui|                                       |  RGui| UP   | DOWN |  ALT | RCTRL  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Alt  | LGui |       | RGui |Alt   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |mirror|ace   | End  |       | PgDn |        |mirror|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[QWERTY] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TG(SYMB),
        KC_BSPC,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,  		  KC_X,   KC_C,   KC_V,   KC_B,   BL_ON,
        KC_LCTRL, 		KC_LALT,	  LCTL(KC_TAB), LCTL(LSFT(KC_TAB)),  KC_LGUI,
                                              KC_LALT,  TG(DVORAK),
                                                              KC_HOME,
                                         LT(HALFQWERTY, KC_SPACE),KC_BSPC,KC_END,
        // right hand
             KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_BSPC,
             TG(SYMB),    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,		   KC_ENT,
             MEH_T(KC_NO),KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLASH,   	   KC_RSFT,
                                  KC_RGUI, KC_UP,KC_DOWN,KC_RALT,           KC_RCTRL,
             TG(DVORAK),        KC_RALT,
             KC_PGUP,
             KC_PGDN,KC_TAB, LT(HALFQWERTY, KC_ENT)
    ),
/* Keymap 1: mirrored qwerty
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  BSPC  |   0  |   9  |   8  |   7  |   6  | LEFT |           | RIGHT|   5  |   4  |   3  |   2  |   1  |  ESC  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  \     |   P  |   O  |   I  |   U  |   Y  |  L1  |           |  L1  |   T  |   R  |   E  |   W  |   Q  |   TAB  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ENTER  |   ;  |   L  |   K  |   J  |   H  |------|           |------|   G  |   F  |   D  |   S  |   A  | BSPC   |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |   /  |   .  |   ,  |   M  |   N  |      |           |      |   B  |   V  |   C  |   X  |   Z  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL|ALT  |CTL-TAB|CTLShTab| LGui|                                       |  RGui| UP   | DOWN |  ALT | RCTRL  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Alt  | LGui |       | RGui |Alt   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |mirror|ace   | End  |       | PgDn |        |mirror|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[HALFQWERTY] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_BSPC,        KC_0,         KC_9,   KC_8,   KC_7,   KC_6,   KC_LEFT,
        KC_TAB,         KC_P,         KC_O,   KC_I,   KC_U,   KC_Y,   TG(SYMB),
        KC_BSPC,        KC_SCLN,      KC_L,   KC_K,   KC_J,   KC_H,
        KC_LSFT,        KC_SLASH,  	  KC_DOT, KC_COMM,KC_M,   KC_N,   KC_TRANSPARENT,
        KC_LCTRL, 		KC_LALT,	  LCTL(KC_TAB), LCTL(LSFT(KC_TAB)),  KC_LGUI,
                                              KC_LALT,  KC_TRANSPARENT,
                                                              KC_HOME,
                                         KC_TRANSPARENT,KC_BSPC,KC_END,
        // right hand
             KC_RGHT,     KC_5,   KC_4,  KC_3,   KC_2,   KC_1,             KC_BSPC,
             TG(SYMB),    KC_T,   KC_R,  KC_E,   KC_W,   KC_Q,             KC_BSLS,
                          KC_G,   KC_F,  KC_D,   KC_S,   KC_A,  		   KC_ENT,
             MEH_T(KC_NO),KC_B,   KC_V,  KC_C,   KC_X,   KC_Z,		   	   KC_RSFT,
                                  KC_RGUI, KC_UP,KC_DOWN,KC_RALT,           KC_RCTRL,
             KC_TRANSPARENT,        KC_RALT,
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_TRANSPARENT
    ),
/* Keymap 3: dvorak
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |  BSPC  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   '  |   ,  |   .  |   P  |   Y  |  L1  |           |  L1  |   F  |   G  |   C  |   R  |   L  |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   S  |  -   |ENTER   |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |   ;  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |  Z   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL|ALT  |CTL-TAB|CTLShTab| LGui|                                       |  RGui| UP   | DOWN |  ALT | RCTRL  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Alt  | LGui |       | RGui |Alt   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |mirror|ace   | End  |       | PgDn |        |mirror|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[DVORAK] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_TAB,         KC_QUOTE,	  KC_COMM,KC_DOT, KC_P,   KC_Y,   TG(SYMB),
        KC_BSPC,        KC_A,         KC_O,   KC_E,   KC_U,   KC_I,
        KC_LSFT,        KC_SCLN,	  KC_Q,   KC_J,   KC_K,   KC_X,   ALL_T(KC_NO),
        KC_LCTRL, 		KC_LALT,	  LCTL(KC_TAB), LCTL(LSFT(KC_TAB)),  KC_LGUI,
                                              KC_LALT,  KC_TRANSPARENT,
                                                              KC_HOME,
                                         LT(HALFDVORAK, KC_SPACE),KC_BSPC,KC_END,
        // right hand
             KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_BSPC,
             TG(SYMB),    KC_F,   KC_G,  KC_C,   KC_R,   KC_L,             KC_BSLS,
                          KC_D,   KC_H,  KC_T,   KC_S,   KC_MINUS,		   KC_ENT,
             MEH_T(KC_NO),KC_B,   KC_M,  KC_W,	 KC_V,	 KC_Z,		   	   KC_RSFT,
                                  KC_RGUI, KC_UP,KC_DOWN,KC_RALT,           KC_RCTRL,
             KC_TRANSPARENT,        KC_RALT,
             KC_PGUP,
             KC_PGDN,KC_TAB, LT(HALFDVORAK, KC_ENT)
    ),
/* Keymap 3: mirrored dvorak
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  BSPC  |   0  |   9  |   8  |   7  |   6  | LEFT |           | RIGHT|   5  |   4  |   3  |   2  |   1  |  ESC  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   L  |   R  |   C  |   G  |   F  |  L1  |           |  L1  |   Y  |   P  |   .  |   ,  |   '  |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   -  |   S  |   T  |   H  |   D  |------|           |------|   I  |   U  |   E  |   O  |   A  |ENTER   |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |   Z  |   V  |   W  |   M  |   B  |      |           |      |   X  |   K  |   J  |   Q  |   ;  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL|ALT  |CTL-TAB|CTLShTab| LGui|                                       |  RGui| UP   | DOWN |  ALT | RCTRL  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Alt  | LGui |       | RGui |Alt   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |mirror|ace   | End  |       | PgDn |        |mirror|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[HALFDVORAK] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_BSPC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_SLASH,         KC_L,         KC_R,   KC_C,   KC_G,   KC_F,   TG(SYMB),
        KC_ENT,        KC_S,         KC_N,   KC_T,   KC_H,   KC_D,
        KC_LSFT,        KC_Z,  		  KC_V,   KC_W,   KC_M,   KC_B,   ALL_T(KC_NO),
        KC_LCTRL, 		KC_LALT,	  LCTL(KC_TAB), LCTL(LSFT(KC_TAB)),  KC_LGUI,
                                              KC_LALT,  KC_TRANSPARENT,
                                                              KC_HOME,
                                         KC_TRANSPARENT,KC_BSPC,KC_END,
        // right hand
             KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_ESC,
             TG(SYMB),    KC_Y,   KC_P,  KC_DOT, KC_COMM,KC_P,             KC_TAB,
                          KC_I,   KC_U,  KC_E,   KC_O,   KC_A,		 	   KC_ENT,
             MEH_T(KC_NO),KC_X,   KC_K,  KC_J,	 KC_Q,   KC_SCLN,	   	   KC_RSFT,
                                  KC_RGUI, KC_UP,KC_DOWN,KC_RALT,           KC_RCTRL,
             KC_TRANSPARENT,        KC_RALT,
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_TRANSPARENT
    ),
/* Keymap 5: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
          EPRM,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       RGB_MOD,KC_TRNS,
                                               KC_TRNS,
                               RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       RGB_TOG, RGB_SLD,
       KC_TRNS,
       KC_TRNS, RGB_HUD, RGB_HUI
),
/* Keymap 6: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
