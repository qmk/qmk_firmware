#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define QW 1 // qwerty
#define SYMB 2 // symbols
#define NUM 3 // media keys

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
 * | Esc    |   1  |   2  |   3  |   4  |   5  | SHIFT|           | SYM  |   6  |   7  |   8  |   9  |   0  |   Bck  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   D  |   R  |   W  |   B  | `~   |           |  "'  |   J  |   F  |   U  |   P  |   :  |   \ |  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Ctr/Es |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |  I   | Enter  |
 * |--------+------+------+------+------+------| = +  |           |  -_  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  | /    | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |MEH   |  Gui |AltShf| Left | Right|                                       | DOWN | UP   |   [  |   ]  | ~SYM |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | ESC  |Home  |       | PgUp  | QW  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |  ENT | End  |       | PgDn |        |      |
 *                                 | Space| WIN  |------|       |------|  Tab   |Back  |
 *                                 |  SYM |      | SCTR |       | SALT |   SYM  |      |
 *                                 `--------------------'       `----------------------'
 */

[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,        KC_2,     KC_3,   KC_4,   KC_5,   KC_LSFT,
        KC_TAB,         KC_Q,        KC_D,     KC_R,   KC_W,   KC_B,   KC_GRV,
        CTL_T(KC_ESC),  KC_A,        KC_S,     KC_H,   KC_T,   KC_G,
        KC_LSFT,        KC_Z,        KC_X,     KC_M,   KC_C,   KC_V,   KC_EQL,
        KC_MEH,         KC_LGUI,     KC_LALT,  KC_LEFT,KC_RGHT,
                                                       KC_ESC,  KC_HOME,
                                                                KC_END,
                            LT(SYMB, KC_SPC),   LGUI_T(KC_ENT), S(KC_LGUI),
        // right hand
             TG(NUM),     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,     KC_BSPC,
             KC_QUOT,     KC_J,   KC_F,   KC_U,   KC_P,   KC_SCLN,  KC_BSLS,
                          KC_Y,   KC_N,   KC_E,   KC_O,   KC_I ,    KC_ENT,
             KC_MINS,     KC_K,   KC_L,   KC_COMM,KC_DOT, KC_SLSH,  KC_RSFT,
                                  KC_DOWN,KC_UP,  KC_LBRC,KC_RBRC,  MO(SYMB),
                       KC_PGUP,  TG(QW),
             KC_PGDN,
             S(KC_LALT),LT(SYMB, KC_TAB), KC_BSPC
    ),

[QW] = LAYOUT_ergodox(
       _______, _______, _______, _______, _______, _______, _______,
       _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,
       _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
       _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, _______, _______, _______, _______, _______,
       _______,  KC_Y,    KC_U,    KC_I   , KC_O,    KC_P,    _______,
                 KC_H,    KC_J,    KC_K   , KC_L,    KC_SCLN, _______,
       _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
                          _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   DEL  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   *  |      |           |      |   <  |  H  |   U  |   PU  |   *  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------|   >  |   L  |   D  |   R  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   E  |   D  |  PD  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,
       _______,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_ASTR,_______,
       _______,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       _______,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,_______,
       _______,_______,_______,_______,_______,
                                       _______,_______,
                                               _______,
                               _______,_______,_______,
       // right hand
       _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_DEL,
       _______, KC_LABK, KC_HOME, KC_UP,   KC_PGUP,  KC_ASTR, _______,
                KC_RABK, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PLUS, _______,
       _______, KC_AMPR, KC_END,  KC_DOWN, KC_PGDN,  KC_BSLS, _______,
                         _______, _______, _______,  _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |  L   | MsUp |   R  |      |      |           |      |      |  4   |   5  |  6   |      |  TAB   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |  1   |   2  |   3  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |   0  |   0  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NUM] = LAYOUT_ergodox(
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,
       _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, _______, _______, _______, _______, _______,
       _______,  _______, KC_4,    KC_5   , KC_6,    _______, KC_TAB,
                 _______, KC_1,    KC_2   , KC_3,    _______, _______,
       _______,  _______, _______, KC_0,    KC_0,    _______, _______,
                          _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),
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
        case 1:
            ergodox_board_led_on();
            break;
        case 3:
            ergodox_board_led_on();
            break;
        default:
            // none
            break;
    }

};
