#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_french.h"

#define BASE 0 // default Colemak Mod-DH layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base Colemak Mod-DH layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    | & _1 | é _2 | " _3 | ' _4 | ( _5 |      |           |      | - _6 | è _7 | _ _8 | ç _9 | à _0 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   F  |   P  |   B  | TO(0)|           |TO(2) |   J  |   L  |   U  |   Y  |   ;  | Ins    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Tab    |   A  |   R  |   S  |   T  |   G  |------|           |------|   M  |   N  |   E  |   I  |   O  | Bcksp  |
 * |--------+------+------+------+------+------| TO(1)|           | MEH  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  |      |           |      |   K  |   H  |   ,  |   .  |   :  | Rshift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  ù   |      | Left | Right| MO(2)|                                       | MO(2)| Down |  Up  | PgDn | PgUp  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      | Ralt |       | Ralt |      |
 *                                ,-------|------|------|       |------+------+------.
 *                                |       |      | Home |       | End  |      |       |
 *                                | Space | Ctrl |------|       |------| Ctrl | Enter |
 *                                |       |      | LAlt |       | LAlt |      |       |
 *                                `---------------------'       `---------------------'
 */
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,       KC_3,        KC_4,    KC_5,   KC_NO,
        KC_NO,          FR_Q,         FR_W,       KC_F,        KC_P,    KC_B,   TO(BASE),
        KC_TAB,         FR_A,         KC_R,       KC_S,        KC_T,    KC_G,
        KC_LSFT,        FR_Z,         KC_X,       KC_C,        KC_D,    KC_V,   TO(SYMB),
        FR_UGRV,        KC_NO,        KC_LEFT,    KC_RIGHT,    MO(SYMB),
                                               KC_NO,             KC_RALT,
                                                                  KC_HOME,
                                               KC_SPC,KC_LCTRL,   KC_LALT,
        // right hand
        KC_NO,        KC_6,    KC_7,       KC_8,             KC_9,      KC_0,             KC_NO,
        TO(MDIA),     KC_J,    KC_L,       KC_U,             KC_Y,      FR_SCLN,          KC_INS,
                      FR_M,    KC_N,       KC_E,             KC_I,      KC_O,             KC_BSPC,
        OSM(MOD_MEH), KC_K,    KC_H,       FR_COMM,          FR_DOT,    FR_COLN,          KC_RSFT,
                               MO(SYMB),   KC_DOWN, KC_UP,   KC_PGDN,   KC_PGUP,

        KC_RALT,        KC_NO,
        KC_END,
        KC_LALT,KC_RCTL, KC_ENT
                  ),


/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   §  |   <  |   {  |   \  |   ~  |      |           |      |   %  |   @  |   }  |  >   |   ¨  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   '  |   =  |   -  |   (  |   +  |------|           |------|   *  |   )  |   _  |  /   |   "  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   `  |   ?  |   #  |   [  |   |  |      |           |      |   &  |   ]  |   $  |   !  |   ^  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   €  |   £  |   ¤  |  ²   |      |                                       |      |   °  |  µ   |   ß  |      |
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
       M(0),       KC_F1,     KC_F2,      KC_F3,      KC_F4,       KC_F5,      KC_TRNS,
       KC_TRNS,    FR_SECT,   FR_LABK,    FR_LCBR,    FR_BSLS,     FR_TILD,    KC_TRNS,
       KC_TRNS,    FR_QUOT,   FR_EQL,     FR_MINS,    FR_LPRN,     FR_PLUS,
       KC_TRNS,    FR_GRV,    FR_QUES,    FR_HASH,    FR_LBRC,     FR_PIPE,    KC_TRNS,
          FR_EURO, FR_PND,    FR_CURR,    FR_SUP2,    KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
       KC_TRNS,    FR_PERC,    FR_AT,      FR_RCBR,    FR_RABK,    FR_DIAE,    KC_F12,
                   FR_ASTR,    FR_RPRN,    FR_UNDS,    FR_SLSH,    FR_DQUO,    KC_TRNS,
       KC_TRNS,    FR_AMPR,    FR_RBRC,    FR_DLR,     FR_EXLM,    FR_CIRC,    KC_TRNS,
                               KC_TRNS,    FR_DEG,     FR_MICR,    ALGR(KC_S), KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Lclk | Rclk |      |      |  Play  |
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
                 KC_TRNS, KC_BTN1, KC_BTN2, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
    case SYMB:
      ergodox_right_led_1_on();
      break;
    case MDIA:
      ergodox_right_led_2_on();
      break;
    default:
      // none
      break;
    }

};
