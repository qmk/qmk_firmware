#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define APP 2 // app layer
#define CNTL 3 // control layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  L2/`  |   1  |   2  |   3  |   4  |   5  |CmdSpc|           | -    |   6  |   7  |   8  |   9  |   0  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | MEH/Tab|   Q  |   W  |   E  |   R  |   T  | [    |           | ]    |  Y   |   U  |   I  |   O  |   P  | MEH/\  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Hyp/Esc |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | L2/; | Hyp/'  |
 * |--------+------+------+------+------+------| Tab  |           | STab |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  | L2// | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |L1/Lft|L3/Rht| LCtl | LAlt | LGui |                                       | Rgui |  Up  |  Dn  |  L3  |  L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.       ,-------------.
 *                                         | LCtl | LGui |       |AltGui|ShfGui|
 *                                 ,-------|------|------|       |------+--------+------.
 *                                 |       |      |L1/Hom|       |L2/PUp|       |       |
 *                                 | Backsp|Delete|------|       |------| Enter | Space |
 *                                 |       |      |L3/End|       |L1/PDn|       |       |
 *                                 `--------------------'       `-----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        LT(APP,KC_GRV),   KC_1,                KC_2,    KC_3,    KC_4,    KC_5,   LGUI(KC_SPC),
        MEH_T(KC_TAB),    KC_Q,                KC_W,    KC_E,    KC_R,    KC_T,   KC_LBRC,
        ALL_T(KC_ESC),    KC_A,                KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT,          KC_Z,                KC_X,    KC_C,    KC_V,    KC_B,   KC_TAB,
        LT(SYMB,KC_LEFT), LT(CNTL,KC_RIGHT),   KC_LCTL, KC_LALT, KC_LGUI,
                                                                    KC_LCTL,   KC_LGUI,
                                                                               LT(SYMB,KC_HOME),
                                                           KC_BSPC, KC_DELETE, LT(CNTL,KC_END),
        // right hand
       KC_MINS,          KC_6,    KC_7,    KC_8,     KC_9,      KC_0,             KC_EQL,
       KC_RBRC,          KC_Y,    KC_U,    KC_I,     KC_O,      KC_P,             MEH_T(KC_BSLS),
                         KC_H,    KC_J,    KC_K,     KC_L,      LT(APP,KC_SCLN),  ALL_T(KC_QUOT),
       S(KC_TAB),        KC_N,    KC_M,    KC_COMM,  KC_DOT,    LT(APP,KC_SLSH),  KC_RSFT,
                                  KC_RGUI, KC_UP,    KC_DOWN,   TT(CNTL),         TT(SYMB),
       LALT(KC_LGUI),    S(KC_LGUI),
       LT(APP,KC_PGUP),
       LT(SYMB,KC_PGDN), KC_ENT, KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           | Tab  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |  <   |           |  >   |   :  |   7  |   8  |   9  |   /  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------|   ;  |   4  |   5  |   6  |   *  |        |
 * |--------+------+------+------+------+------|  F14 |           | F15  |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   -  |  Entr  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0   |   . |  =   |   +  |       |
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
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,S(KC_COMM),
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_F14,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TAB,    KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       S(KC_DOT), KC_COLN, KC_7,   KC_8,    KC_9,    KC_BSLS, KC_F12,
                  KC_SCLN, KC_4,   KC_5,    KC_6,    KC_ASTR, KC_TRNS,
       KC_F15,    KC_AMPR, KC_1,   KC_2,    KC_3,    KC_MINS, KC_ENT,
                           KC_0,   KC_DOT,  KC_EQL,  KC_PLUS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: App Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | CmdQ | CmdW |      |      |      | Stab |           | Play | Prev | Next |      |      |PrtSc |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| VolDn|VolUp |      |      |      |        |
 * |--------+------+------+------+------+------|      |           | Mute |------+------+------+------+------+--------|
 * |        | CmdZ | CmdX | CmdC | CmdY | CtrlC|      |           |      |      |      |      |      |      |        |
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
// Control
[APP] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS, LGUI(KC_Q), LGUI(KC_W), KC_TRNS,    KC_TRNS,    KC_TRNS,    S(KC_TAB),
       KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LCTL(KC_C), KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                              KC_TRNS,  KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_MPLY,  KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS,
                 KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_MUTE,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 3: Control Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Pwr   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght| Lclk |------|           |------|  Lft | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      | Rclk |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Shift|      |       | Home | End  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | LAtl |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Control
[CNTL] = LAYOUT_ergodox(
       KC_PWR,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN2, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_LSFT, KC_TRNS,
                                                    KC_LALT,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_HOME, KC_END,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

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
        case 3:
          ergodox_right_led_3_on();
          break;
        default:
            // none
            break;
    }

};
