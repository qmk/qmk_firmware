#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

//Tap Dance Declarations
enum {
  TD_J_LBRC = 0,
  TD_K_RBRC,
  TD_Y_ESC,
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_J_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_LBRC),
  [TD_K_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_RBRC),
  [TD_Y_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_ESC)
};

//Macro Declarations
static uint16_t sunds_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   x  |   x  |   x  |   _  | Hypr | Home |           | End  | Hypr |  Esc |   x  |   x  |   x  |   `~   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |Tab/Ctrl|   Q  |   W  |   E  |   R  |   T  |  Up  |           | PgUp |Y 2Esc|   U  |   I  |   O  |   P  |Bks/Ctrl|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | '"/Cmd |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  | J 2[ | K 2] |   L  |  ;:  |Entr/Cmd|
 * |--------+------+------+------+------+------| Down |           | PgDn |------+------+------+------+------+--------|
 * | _/Shft |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |  ,<  |  .>  |  /?  | _/Shft |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Alt  |   x  |   x  |   x  | Left |                                       |Right |   x  |   x  |   x  |  Alt |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Mute | VolUp|       | Play |  Del   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | VolDn|       | Next |        |      |
 *                                 |Sp/~L1|  L2  |------|       |------|   L2   |Sp/~L1|
 *                                 |      |      |Teensy|       | Prev |        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,          KC_1,          KC_1,          KC_1,            KC_UNDS,  ALL_T(KC_NO),      KC_HOME,
        CTL_T(KC_TAB),   KC_Q,          KC_W,          KC_E,            KC_R,     KC_T,              KC_UP,
        GUI_T(KC_QUOT),  KC_A,          KC_S,          KC_D,            KC_F,     KC_G,
        M(1),            KC_Z,          KC_X,          KC_C,            KC_V,     KC_B,              KC_DOWN,
        KC_LALT,         KC_1,          KC_1,          KC_1,            KC_LEFT,
                                                                        KC_MUTE,  KC_VOLU,
                                                                        KC_VOLD,
                                                                        LT(SYMB, KC_SPC),  TG(MDIA),  RESET,
        // right hand
        KC_END,          ALL_T(KC_NO),  KC_ESC,         KC_1,           KC_1,     KC_1,              KC_GRV,
        KC_PGUP,         TD(TD_Y_ESC),  KC_U,           KC_I,           KC_O,     KC_P,              CTL_T(KC_BSPC),
                         KC_H,          TD(TD_J_LBRC),  TD(TD_K_RBRC),  KC_L,     KC_SCOLON,         GUI_T(KC_ENT),
        KC_PGDN,         KC_N,          KC_M,           KC_COMM,        KC_DOT,   KC_SLSH,           M(1),
                                        KC_RGHT,        KC_1,           KC_1,     KC_1,              KC_RALT,
        KC_MPLY,         KC_DEL,
        KC_MNXT,
        KC_MPRV,         TG(MDIA),      LT(SYMB, KC_SPC)
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   ^  |   {  |   (  |   [  |      |           |      |   =  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   &  |   $  |   }  |   )  |   ]  |------|           |------|   +  |   4  |   5  |   6  |   *  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   \  |   #  |   @  |   %  |   |  |      |           |      |   -  |   1  |   2  |   3  |   /  |        |
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
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_TRNS,
       KC_TRNS,  KC_EXLM,  KC_CIRC,  KC_LCBR,  KC_LPRN,  KC_LBRC,  KC_TRNS,
       KC_TRNS,  KC_AMPR,  KC_DLR,   KC_RCBR,  KC_RPRN,  KC_RBRC,
       KC_TRNS,  KC_BSLS,  KC_HASH,  KC_AT,    KC_PERC,  KC_PIPE,  KC_TRNS,
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
[MDIA] = KEYMAP(
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
            register_code (KC_LSFT);
          } else {
            if (timer_elapsed (sunds_timer) < TAPPING_TERM) {
              register_code (KC_MINS);
              unregister_code (KC_MINS);
            }
            unregister_code (KC_LSFT);
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
