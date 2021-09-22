#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "keymap_norwegian.h"

#define BASE 0 // default layer
#define BASE_MAC 1 // default layer mac
#define NUMB_FUNC 2 // numbers and function keys

enum custom_keycodes {
    TILDE_NO = SAFE_RANGE,
    LESS_NO,
    GRTR_NO,
    CIRC_NO,
    ACUT_NO,
    GRV_NO,
    LESS_NO_MAC,
    GRTR_NO_MAC,
    ACUT_NO_MAC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Basic layer PC
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    *   |   [  |   ]  |   {  |   }  |   ~  |Mac/PC|           |   ^  |   $  |   (  |   )  |   <  |   >  |   @    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    +   |   Q  |   W  |   E  |   R  |   T  |  "   |           |   '  |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    /   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ø  |   Æ    |
 * |--------+------+------+------+------+------|  ;   |           |   =  |------+------+------+------+------+--------|
 * |    -   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  | RIGHT| DOWN |   UP |   _    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Alt/esc|  !  |   ?  |   :  | TAB  |                                       | LEFT |  _  |   &   |   |  |Num/fn|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,--------------.
 *                                        |   #  |  `   |       |Insert|   %   |
 *                                 ,------|------|------|       |------+-------+------.
 *                                 |      |      |  ´   |       |  Del |       |      |
 *                                 | Shift|Ctrl/.|------|       |------| Enter |Space |
 *                                 |      |      |GUI/, |       | Bspc |       |      |
 *                                 `--------------------'       `---------------------'
 */
[BASE] = LAYOUT_ergodox(
        // left hand
        KC_PAST,       NO_LBRC, NO_RBRC, NO_LCBR,  NO_RCBR, TILDE_NO,  TG(1),
        KC_PPLS,         KC_Q,         KC_W,    KC_E,   KC_R,   KC_T,   NO_DQUO,
        KC_PSLS,         KC_A,         KC_S,    KC_D,   KC_F,   KC_G,
        KC_PMNS,        KC_Z,         KC_X,    KC_C,   KC_V,   KC_B,   NO_SCLN,
        ALT_T(KC_ESC), KC_EXLM , NO_QUES, NO_COLN, KC_TAB,
                                                      KC_HASH, GRV_NO,
                                                              ACUT_NO,
                                               OSM(MOD_LSFT),CTL_T(KC_DOT),GUI_T(KC_COMMA),
        // right hand
             CIRC_NO, NO_DLR, NO_LPRN, NO_RPRN ,LESS_NO, GRTR_NO,NO_AT,
             NO_QUOT,      KC_Y,    KC_U,    KC_I,      KC_O,     KC_P,   NO_ARNG,
                           KC_H,    KC_J,    KC_K,      KC_L,  NO_OSTR,    NO_AE,
             NO_EQL,        KC_N,    KC_M, KC_RIGHT,  KC_DOWN,   KC_UP,    NO_BSLS,
                                  KC_LEFT,  NO_UNDS, NO_AMPR,  NO_PIPE,    OSL(2),
             KC_INSERT,  KC_PERC,
             KC_DEL,
             KC_BSPC,KC_ENT,KC_SPC
    ),
/* Keymap 1: Basic layer MACS (Same as pc, except for cmd/ctrl, which are swapped)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   \    |      |      |   {  |   }  |      |      |           |      |   $  |      |      |  <   |   >  |    @   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |  '   |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |,/Ctrl|                                       |      |      |  `   |      |Num/fn|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |  `   |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |   ´  |       |      |      |      |
 *                                 |      |GUI/. |------|       |------|      |      |
 *                                 |      |      |crtl/,|       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[BASE_MAC] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS,KC_TRNS, S(ALGR(NO_8)),S(ALGR(NO_9)), KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, ALGR(NO_BSLS),
                                                    ACUT_NO_MAC,
                                  KC_TRNS,GUI_T(KC_DOT) , CTL_T(KC_COMMA),
    // right hand
       KC_TRNS,  S(NO_4), KC_TRNS,KC_TRNS,LESS_NO_MAC, GRTR_NO_MAC,NO_QUOT,
       NO_LABK,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, S(ALGR(NO_7)),
                          KC_TRNS, KC_TRNS, KC_TRNS, ALGR(NO_7), OSL(2),
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Number ++´ánd Fn layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |  F9  |  F10 |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  8   |  7   |  6   |   5  |  9   |      |           |      |      |  F5  |  F6  |  F7  |  F8  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  4   |  3   |  2   |   1  |  0   |------|           |------|      |  F1  |  F2  |  F3  |  F4  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |  END | PGDWN| PGUP |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | HOME |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NUMB_FUNC] = LAYOUT_ergodox(
       NO_ASTR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       NO_PLUS, KC_8, KC_7,KC_6,KC_5, KC_9 , KC_TRNS,
       NO_SLSH , KC_4   , KC_3   , KC_2   , KC_1   , KC_0,
       NO_MINS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_F5, KC_F6 , KC_F7, KC_F8, KC_TRNS,
                 KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS,
       KC_TRNS,  KC_HOME, KC_TRNS, KC_END, KC_PGDN, KC_PGUP, KC_TRNS,
                          KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TILDE_NO:
            if (record->event.pressed) {
                tap_code16(ALGR(KC_RBRC));
                tap_code(KC_SPC);
            }
            return false;
        case LESS_NO:
            if (record->event.pressed) {
                tap_code(KC_NUBS);
            }
            return false;
        case GRTR_NO:
            if (record->event.pressed) {
                tap_code16(S(KC_NUBS));
            }
            return false;
        case CIRC_NO:
            if (record->event.pressed) {
                tap_code16(S(KC_RBRC));
                tap_code(KC_SPC);
            }
            return false;
        case ACUT_NO:
            if (record->event.pressed) {
                tap_code16(ALGR(KC_EQL));
                tap_code(KC_SPC);
            }
            return false;
        case GRV_NO:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT("= "));
            }
            return false;
        case LESS_NO_MAC:
            if (record->event.pressed) {
                tap_code(KC_GRV);
            }
            return false;
        case GRTR_NO_MAC:
            if (record->event.pressed) {
                tap_code16(S(KC_GRV));
            }
            return false;
        case ACUT_NO_MAC:
            if (record->event.pressed) {
                tap_code(KC_EQL);
                tap_code(KC_SPC);
            }
            return false;
    }
    return true;
}
