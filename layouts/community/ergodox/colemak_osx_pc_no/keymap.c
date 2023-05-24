#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "keymap_norwegian.h"

#define BASE 0 // default layer
#define BASE_MAC 1 // default layer mac
#define NUMB_SYMB 2 // numbers and symbols
#define NUMB_SYMB_MAC 3 // numbers and symbols mac
#define FUNCTION 4 // function keys

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
 * |    \   |   [  |   ]  |   {  |   }  |   *  |Mac/PC|           |   ^  |   $  |   (  |   )  |   <  |   >  |   @    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    ?   |   Q  |   W  |   F  |   P  |   G  |  "   |           |   '  |   J  |   L  |   U  |   Y  |   Å  |   Æ    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    :   |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |   O  |   Ø    |
 * |--------+------+------+------+------+------|  ;   |           |   =  |------+------+------+------+------+--------|
 * |    !   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  | RIGHT| DOWN |   UP |   _    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Func | Lclk | Rclk | TAB  |,/CTRL|                                       | LEFT | Esc  |   `  |   #  | Num  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,--------------.
 *                                        |   &  |   |  |       |Insert|   /   |
 *                                 ,------|------|------|       |------+-------+------.
 *                                 |      |      |   +  |       |  Del |        |     |
 *                                 | Shift| ./Spc|------|       |------|  Enter |Space|
 *                                 |      |      |-/Alt |       | Bspc |        |     |
 *                                 `--------------------'       `---------------------'
 */
[BASE] = LAYOUT_ergodox(
        // left hand
        NO_BSLS,       NO_LBRC, NO_RBRC, NO_LCBR,  NO_RCBR, NO_ASTR,  TG(1),
        NO_QUES,         KC_Q,         KC_W,    KC_F,   KC_P,   KC_G,   NO_DQUO,
        NO_COLN,         KC_A,         KC_R,    KC_S,   KC_T,   KC_D,
        KC_EXLM,        KC_Z,         KC_X,    KC_C,   KC_V,   KC_B,   NO_SCLN,
        MO(4),     KC_BTN1,      KC_BTN2, KC_TAB,GUI_T(KC_COMMA),
                                                      NO_AMPR, NO_PIPE,
                                                              NO_PLUS,
                                               OSM(MOD_LSFT),CTL_T(KC_DOT),ALT_T(NO_MINS),
        // right hand
             CIRC_NO, NO_DLR, NO_LPRN, NO_RPRN ,LESS_NO, GRTR_NO,NO_AT,
             NO_QUOT,      KC_J,    KC_L,    KC_U,      KC_Y,     NO_ARNG, NO_AE  ,
                           KC_H,    KC_N,    KC_E,      KC_I,      KC_O,    NO_OSTR,
             NO_EQL,        KC_K,    KC_M, KC_RIGHT,  KC_DOWN,   KC_UP, NO_UNDS,
                                  KC_LEFT,  KC_ESC,   GRV_NO,   KC_HASH,   MO(2),
             KC_INSERT,  NO_SLSH,
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
 *   | Func |      |      |      |,/Ctrl|                                       |      |      |  `   |      | Num  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |  |   |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |./Cmd |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[BASE_MAC] = LAYOUT_ergodox(
       S(ALGR(NO_7)), KC_TRNS,KC_TRNS, S(ALGR(NO_8)),S(ALGR(NO_9)), KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, CTL_T(KC_COMMA),
                                           KC_TRNS, ALGR(NO_7),
                                                    KC_TRNS,
                                  KC_TRNS,GUI_T(KC_DOT) , KC_TRNS,
    // right hand
       KC_TRNS,  S(NO_4), KC_TRNS,KC_TRNS,LESS_NO_MAC, GRTR_NO_MAC,NO_QUOT,
       NO_LABK,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, ALGR(NO_BSLS), KC_TRNS, MO(3),
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Number ++ layer pc
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |   %  |      |      |           |      |      |   ~  |   ´  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   3  |  2   |  1   |   0  |      |------|           |------|      |   5  |   6  |   7  |   8  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |   4  |      |      |           |      |      |   9  |  END | PGDWN| PGUP |        |
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
[NUMB_SYMB] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_PERC, KC_TRNS , KC_TRNS,
       KC_TRNS, KC_3   , KC_2   , KC_1   , KC_0   , KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, TILDE_NO, ACUT_NO , KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_5, KC_6, KC_7, KC_8, KC_TRNS,
       KC_TRNS,  KC_HOME, KC_9, KC_END, KC_PGDN, KC_PGUP, KC_TRNS,
                          KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 3: Number ++ layer mac. Some keys have to be repeated from the pc symbol layer, since transient keys inherit from the layer we jump from, not the layer above.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |   %  |      |      |           |      |      |   ~  |   ´  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   3  |  2   |  1   |   0  |      |------|           |------|      |   5  |   6  |   7  |   8  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |   4  |      |      |           |      |      |   9  |  END | PGDWN| PGUP |        |
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
[NUMB_SYMB_MAC] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_PERC, KC_TRNS , KC_TRNS,
       KC_TRNS, KC_3   , KC_2   , KC_1   , KC_0   , KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, TILDE_NO, ACUT_NO_MAC, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_5, KC_6, KC_7, KC_8, KC_TRNS,
       KC_TRNS,  KC_HOME, KC_9, KC_END, KC_PGDN, KC_PGUP, KC_TRNS,
                          KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 4: Function layer mac + pc
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F3  |  F2  |  F1  |     |      |------|           |------|       |  F5  |  F6  |  F7  |  F8  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |  F4  |      |      |           |      |      |  F9  |  F10 |  F11 |  F12 |        |
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
[FUNCTION] = LAYOUT_ergodox(
       KC_5, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS,
       KC_TRNS, KC_F3   , KC_F2   , KC_F1 , KC_TRNS   , KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F4, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_TRNS,
       KC_TRNS,  NO_TILD, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
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
