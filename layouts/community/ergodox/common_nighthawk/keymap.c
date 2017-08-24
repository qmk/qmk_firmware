#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

//Tap Dance Declarations
enum {
  TD_U_LBRC = 0,
  TD_I_RBRC,
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_U_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_U, KC_LBRC),
  [TD_I_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_RBRC)
};

//Macro Declarations
static uint16_t sunds_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  _     |   x  |   x  |   _  |  Esc | Hypr | Home |           | End  | Hypr |   [  |   ]  |  `~  |  `~  |  Bks   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |Ctrl/Tab|   Q  |   W  |   E  |   R  |   T  |  Up  |           | PgUp |   Y  |   U  |   I  |   O  |   P  |  Ctrl  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Cmd/"' |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;:  |Cmd/Entr|
 * |--------+------+------+------+------+------| Down |           | PgDn |------+------+------+------+------+--------|
 * |  Shft  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |  ,<  |  .>  |  /?  |  Shft  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Alt  |   x  |   x  |   x  | Left |                                       |Right |  Bks |   x  |   x  |  Alt |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Teensy| VolUp|       | Play |  Del   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | VolDn|       | Next |        |      |
 *                                 |Sp/~L1|  L2  |------|       |------|   L2   |'"/~L1|
 *                                 |      |      | Mute |       | Prev |        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_UNDS,         KC_1,          KC_1,          KC_UNDS,         KC_ESC,   ALL_T(KC_NO),      KC_HOME,
        CTL_T(KC_TAB),   KC_Q,          KC_W,          KC_E,            KC_R,     KC_T,              KC_UP,
        M(1),            KC_A,          KC_S,          KC_D,            KC_F,     KC_G,
        KC_LSFT,         KC_Z,          KC_X,          KC_C,            KC_V,     KC_B,              KC_DOWN,
        KC_LALT,         KC_1,          KC_1,          KC_1,            KC_LEFT,
                                                                        RESET,    KC_VOLU,
                                                                        KC_VOLD,
                                                                        LT(SYMB, KC_SPC),  TG(MDIA), KC_MUTE,
        // right hand
        KC_END,          ALL_T(KC_NO),  KC_LBRC,        KC_RBRC,        KC_GRV,   KC_GRV,            KC_BSPC,
        KC_PGUP,         KC_Y,          KC_U,           KC_I,           KC_O,     KC_P,              KC_LCTRL,
                         KC_H,          KC_J,           KC_K,           KC_L,     KC_SCOLON,         GUI_T(KC_ENT),
        KC_PGDN,         KC_N,          KC_M,           KC_COMM,        KC_DOT,   KC_SLSH,           KC_RSFT,
                                        KC_RGHT,        KC_BSPC,        KC_1,     KC_1,              KC_RALT,
        KC_MPLY,         KC_DEL,
        KC_MNXT,
        KC_MPRV,         TG(MDIA),      LT(SYMB, KC_QUOT)
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   ^  |   [  |   (  |   {  |      |           |      |   =  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   &  |   $  |   ]  |   )  |   }  |------|           |------|   +  |   4  |   5  |   6  |   *  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   \  |   @  |   #  |   %  |   |  |      |           |      |   -  |   1  |   2  |   3  |   /  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0  |   0  |   .  |      |      |
 *   `----------------------------------'                                       `----------------------------------'
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
       KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_TRNS,
       KC_TRNS,  KC_EXLM,  KC_CIRC,  KC_LBRC,  KC_LPRN,  KC_LCBR,  KC_TRNS,
       KC_TRNS,  KC_AMPR,  KC_DLR,   KC_RBRC,  KC_RPRN,  KC_RCBR,
       KC_TRNS,  KC_BSLS,  KC_AT,    KC_HASH,  KC_PERC,  KC_PIPE,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                               KC_TRNS,  KC_TRNS,
                                               KC_TRNS,
                                               KC_TRNS,  KC_TRNS,  KC_TRNS,
       // right hand
       KC_TRNS,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_TRNS,
       KC_TRNS,  KC_EQL,   KC_7,     KC_8,     KC_9,     KC_0,     KC_TRNS,
                 KC_PLUS,  KC_4,     KC_5,     KC_6,     KC_ASTR,  KC_TRNS,
       KC_TRNS,  KC_MINS,  KC_1,     KC_2,     KC_3,     KC_TRNS,  KC_TRNS,
                           KC_0,     KC_0,     KC_DOT,   KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,
       KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | WhDn | WhUp |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      | R-Ck | L-Ck |      |------|           |------| MsLt | MsDn | MsUp | MsRt |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
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
       M(0),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN2, KC_BTN1, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,     KC_WH_U,     KC_WH_D,     KC_TRNS,     KC_TRNS, KC_TRNS,
                 KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_UP,    KC_MS_RIGHT, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS, KC_TRNS,
                              KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS, KC_TRNS,
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
          if (record->event.pressed) {
            sunds_timer = timer_read();
            register_code (KC_LGUI);
          } else {
            if (timer_elapsed (sunds_timer) < TAPPING_TERM) {
              unregister_code (KC_LGUI);
              register_code (KC_LSFT);
              register_code (KC_QUOT);
              unregister_code (KC_QUOT);
              unregister_code (KC_LSFT);
              register_code (KC_LGUI);
            }
            unregister_code (KC_LGUI);
          }
          break;

      }
    return MACRO_NONE;
};

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
            ergodox_right_led_3_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
    if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
        ergodox_right_led_1_on ();
    }
};
