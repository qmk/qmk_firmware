#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   -    |   1  |   2  |   3  |   4  |   5  | Esc  |           | Esc  |   6  |   7  |   8  |   9  |   0  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  [{  |           |  ]}  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------|  L1  |           |  L1  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf|  `~  |  '"  |                                       | Left | Down |  Up  | Right| ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | LGui |       | LGui |        |      |
 *                                 | LGui | FN1  |------|       |------| Backspa|Space |
 *                                 |      |      | Alt  |       | Alt  | ce     |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
    // left hand
    KC_MINUS,         KC_1,    KC_2,    KC_3,   KC_4,    KC_5,   KC_ESC,
    KC_TAB,           KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,   LT(MDIA,KC_LBRACKET),
    CTL_T(KC_CAPS),   KC_A,    KC_S,    KC_D,   KC_F,    KC_G,
    KC_LSPO,          KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,   KC_FN1,
    LT(SYMB,KC_MUTE), KC_VOLD, KC_VOLU, KC_GRV, KC_QUOT,

                                                    KC_MPLY,  TG(MDIA),
                                                              KC_LCTRL,
                                          KC_LGUI, MO(SYMB), KC_LALT,

    // right hand
    KC_ESC,               KC_6,   KC_7,    KC_8,    KC_9,   KC_0,              KC_EQUAL,
    LT(MDIA,KC_RBRACKET), KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,              KC_BSLS,
                          KC_H,   KC_J,    KC_K,    KC_L,   KC_SCOLON,         KC_ENTER,
    KC_FN1,               KC_N,   KC_M,    KC_COMM, KC_DOT, LT(MDIA, KC_SLSH), KC_RSPC,
                                  KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT,          TO(SYMB),

    TG(MDIA), TG(SYMB),
    KC_RCTRL,
    KC_RALT,  KC_BSPACE, KC_SPACE
),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|  L2  |           |  L2  |------+------+------+------+------+--------|
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
    VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F11,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                        KC_TRNS,  KC_TRNS,
                                                  RGB_MOD,
                                KC_TRNS, KC_TRNS,  KC_TRNS,

    // right hand
    KC_F12,  KC_F6,   KC_F7,   KC_F8,  KC_F9, KC_F10,  KC_TRNS,
    KC_TRNS, KC_UP,   KC_7,    KC_8,   KC_9,  KC_ASTR, KC_TRNS,
              KC_DOWN, KC_4,    KC_5,   KC_6,  KC_PLUS, KC_TRNS,
    KC_TRNS, KC_AMPR, KC_1,    KC_2,   KC_3,  KC_BSLS, KC_TRNS,
                      KC_TRNS, KC_DOT, KC_0,  KC_EQL,  TO(MDIA),

    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_DEL,  KC_TRNS
),

/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Prev | Play | Next |      |      |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |Brwser|Brwser|
 *                                 |      |      |------|       |------|Back  |Fwd   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
    // left hand
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_D, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,
    KC_TRNS, KC_TRNS, KC_WH_L, KC_BTN3, KC_WH_R, KC_TRNS, KC_TRNS,
    KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS,

                                        KC_TRNS, KC_TRNS,
                                                  KC_WH_D,
                                KC_BTN1, KC_BTN2, KC_WH_U,

    // right hand
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                        KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, TO(BASE),

    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_WBAK, KC_WFWD
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
