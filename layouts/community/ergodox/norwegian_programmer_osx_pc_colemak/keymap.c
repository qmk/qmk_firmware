#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "keymap_norwegian.h"

#define BASE 0 // default layer
#define BASE_MAC 1 // default layer mac
#define NUMB_FUNC 2 // numbers and function keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Basic layer PC
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    *   |   [  |   ]  |   {  |   }  |   ~  |Mac/PC|           |   ^  |   $  |   (  |   )  |   <  |   >  |   @    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |    +   |   Q  |   W  |   F  |   P  |   G  |  "   |           |   '  |   J  |   L  |   U  |   Y  |   Å  |   Æ    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    /   |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |   O  |   Ø    |
 * |--------+------+------+------+------+------|  ;   |           |   =  |------+------+------+------+------+--------|
 * |    -   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  | RIGHT| DOWN |   UP |   _    |
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
        KC_PAST,       NO_LBRC, NO_RBRC, NO_LCBR,  NO_RCBR, KC_FN2,  TG(1),
        KC_PPLS,         KC_Q,         KC_W,    KC_F,   KC_P,   KC_G,   NO_QUO2,
        KC_PSLS,         KC_A,         KC_R,    KC_S,   KC_T,   KC_D,
        KC_PMNS,        KC_Z,         KC_X,    KC_C,   KC_V,   KC_B,   NO_SCLN,
        ALT_T(KC_ESC), KC_EXLM , NO_QUES, NO_COLN, KC_TAB,
                                                      KC_HASH, KC_FN7,
                                                              KC_FN6,
                                               OSM(MOD_LSFT),CTL_T(KC_DOT),GUI_T(KC_COMMA),
        // right hand
             KC_FN5, NO_DLR, NO_LPRN, NO_RPRN ,KC_FN3, KC_FN4,NO_AT,
             NO_APOS,      KC_J,    KC_L,    KC_U,      KC_Y,     NO_AA,   NO_AE  ,
                           KC_H,    KC_N,    KC_E,      KC_I,      KC_O,    NO_OSLH,
             NO_EQL,        KC_K,    KC_M, KC_RIGHT,  KC_DOWN,   KC_UP,    NO_BSLS,
                                  KC_LEFT,  NO_UNDS, NO_AMPR,  NO_PIPE,    OSL(2),
             KC_INSERT,  KC_PERC,
             KC_DEL,
             KC_BSPC,KC_ENT,KC_SPC
    ),
/* Keymap 1: Basic layer MAC (Same as pc, except for cmd/ctrl, which are swapped)
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
       KC_TRNS, KC_TRNS,KC_TRNS, NO_LCBR_MAC,NO_RCBR_MAC, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, NO_GRV_MAC,
                                                    KC_FN10,
                                  KC_TRNS,GUI_T(KC_DOT) , CTL_T(KC_COMMA),
    // right hand
       KC_TRNS,  NO_DLR_MAC, KC_TRNS,KC_TRNS,KC_FN8, KC_FN9,NO_AT_MAC,
       NO_APOS_MAC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NO_BSLS_MAC,
                          KC_TRNS, KC_TRNS, KC_TRNS, NO_PIPE_MAC, OSL(2),
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Number ++´ánd Fn layer pc
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

enum macro_id {
    TILDE_NO, LESS_NO, GRTR_NO, CIRC_NO, ACUT_NO,  GRV_NO, LESS_NO_MAC, GRTR_NO_MAC, ACUT_NO_MAC
};

const uint16_t PROGMEM fn_actions[] = {
    [2] = ACTION_MACRO(TILDE_NO), // Completed ~ character(pc and mac), no space needed.
    [3] = ACTION_MACRO(LESS_NO), // < completed on keypress down, to avoid shifting the next character if it is not released first.
    [4] = ACTION_MACRO(GRTR_NO), // > completed on keypress down, to avoid shifting the next character if it is not released first.
    [5] = ACTION_MACRO(CIRC_NO), // Completed ^ character, no space needed.
    [6] = ACTION_MACRO(ACUT_NO), // Completed ´ character, no space needed.
    [7] = ACTION_MACRO(GRV_NO), // Completed ` character, no space needed.
    [8] = ACTION_MACRO(LESS_NO_MAC), // < completed on keypress down, to avoid same button problem when typing <> quickly
    [9] = ACTION_MACRO(GRTR_NO_MAC), // > completed on keypress down, to avoid same button problem when typing <> quickly
    [10] = ACTION_MACRO(ACUT_NO_MAC), // Completed ´ character, no space needed
};



const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;

    switch (id) {
        case TILDE_NO:
            return (event.pressed ? MACRO( D(RALT), T(RBRC), U(RALT), T(SPC), END ) : MACRO_NONE);
        case LESS_NO:
            return (event.pressed ? MACRO( T(NUBS), END ) : MACRO_NONE);
        case GRTR_NO:
            return (event.pressed ? MACRO( D(LSFT), T(NUBS), U(LSFT), END ) : MACRO_NONE);
        case CIRC_NO:
            return (event.pressed ? MACRO( D(LSFT), T(RBRC), U(LSFT), T(SPC), END ) : MACRO_NONE);
        case ACUT_NO:
            return (event.pressed ? MACRO( D(RALT), T(EQL), U(RALT), T(SPC),  END ) : MACRO_NONE);
        case GRV_NO:
            return (event.pressed ? MACRO( D(LSFT), T(EQL), T(SPC), U(LSFT),  END ) : MACRO_NONE);
        case LESS_NO_MAC:
            return (event.pressed ? MACRO( T(GRV), END ) : MACRO_NONE);
        case GRTR_NO_MAC:
            return (event.pressed ? MACRO( D(LSFT), T(GRV), U(LSFT), END ) : MACRO_NONE);
        case ACUT_NO_MAC:
            return (event.pressed ? MACRO( T(EQL), T(SPC),  END ) : MACRO_NONE);
    }
    return MACRO_NONE;
};
