#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "../../../../quantum/keymap_extras/keymap_norwegian.c"

#define BASE 0 // default layer
#define BASE_MAC 1 // default layer mac
#define NUMB_SYMB 2 // numbers and symbols
#define NUMB_SYMB_MAC 3 // numbers and symbols mac
#define FUNCTION 4 // function keys

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
[BASE] = KEYMAP(
        // left hand
        NO_BSLS,       NO_LBRC, NO_RBRC, NO_LCBR,  NO_RCBR, NO_ASTR,  TG(1),
        NO_QUES,         KC_Q,         KC_W,    KC_F,   KC_P,   KC_G,   NO_QUO2,
        NO_COLN,         KC_A,         KC_R,    KC_S,   KC_T,   KC_D,
        KC_EXLM,        KC_Z,         KC_X,    KC_C,   KC_V,   KC_B,   NO_SCLN,
        MO(4),     KC_BTN1,      KC_BTN2, KC_TAB,GUI_T(KC_COMMA),
                                                      NO_AMP, NO_PIPE,
                                                              NO_PLUS,
                                               KC_FN1,CTL_T(KC_DOT),ALT_T(NO_MINS),
        // right hand
             KC_FN5, NO_DLR, NO_LPRN, NO_RPRN ,KC_FN3, KC_FN4,NO_AT,
             NO_APOS,      KC_J,    KC_L,    KC_U,      KC_Y,     NO_AA,   NO_AE  ,
                           KC_H,    KC_N,    KC_E,      KC_I,      KC_O,    NO_OSLH,
             NO_EQL,        KC_K,    KC_M, KC_RIGHT,  KC_DOWN,   KC_UP, NO_UNDS,
                                  KC_LEFT,  KC_ESC,   KC_FN7,   KC_HASH,   MO(2),
             KC_INSERT,  NO_SLSH,
             KC_DELT,
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
[BASE_MAC] = KEYMAP(
       NO_BSLS_MAC, KC_TRNS,KC_TRNS, NO_LCBR_MAC,NO_RCBR_MAC, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, CTL_T(KC_COMMA),
                                           KC_TRNS, NO_PIPE_MAC,
                                                    KC_TRNS,
                                  KC_TRNS,GUI_T(KC_DOT) , KC_TRNS,
    // right hand
       KC_TRNS,  NO_DLR_MAC, KC_TRNS,KC_TRNS,KC_FN8, KC_FN9,NO_AT_MAC,
       NO_APOS_MAC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, NO_GRV_MAC, KC_TRNS, MO(3),
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
[NUMB_SYMB] = KEYMAP(
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
       KC_TRNS,  KC_TRNS, KC_FN2, KC_FN6 , KC_TRNS, KC_TRNS, KC_TRNS,
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
[NUMB_SYMB_MAC] = KEYMAP(
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
       KC_TRNS,  KC_TRNS, KC_FN2, KC_FN10, KC_TRNS, KC_TRNS, KC_TRNS,
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
[FUNCTION] = KEYMAP(
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

enum macro_id {
    TILDE_NO, LESS_NO, GRTR_NO, CIRC_NO, ACUT_NO,  GRV_NO, LESS_NO_MAC, GRTR_NO_MAC, ACUT_NO_MAC
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_MODS_ONESHOT(MOD_LSFT),  // Sticky shift light. Tap for the next keypress to be shifted. Hold for regular shift.
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
