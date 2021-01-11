#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "keymap_colemak.h"

enum {
    BASE = 0,
    BASE_CM,
    SYMB,
    MACR
};

enum {
    LWIN = 1,
    PC1,
    PC2,
    PC3,
    PC4,
    DL_BASE,
    DL_BASE_CM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0a: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   F  |   P  |   G  |  L1  |           |  L1  |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Esc    |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |  O   |   '    |
 * |--------+------+------+------+------+------|   =  |           |   -  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LAlt | LGui |       | LAlt | RAlt |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |Backsp| Home |       | PgUp |        |      |
 *                                 | Space|ace/  |------|       |------|  Tab/  |Enter/|
 *                                 | /Shft|Ctrl  |  1)  |       |  2)  |  Ctrl  |Shift |
 *                                 `--------------------'       `----------------------'
 *
 * 1) End/L1
 * 2) PgDown/L2
 */
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,     KC_2,   KC_3,   KC_4,          KC_5,   KC_LEFT,
        KC_DEL,         KC_Q,     KC_W,   KC_F,   KC_P,          KC_G,   TG(SYMB),
        KC_ESC,         KC_A,     KC_R,   KC_S,   KC_T,          KC_D,
        KC_LSFT,        KC_Z,     KC_X,   KC_C,   KC_V,          KC_B,   KC_EQL,
        LT(SYMB,KC_GRV),KC_QUOT,  LALT(KC_LSFT),  KC_LEFT,       KC_RGHT,
                                                             KC_LALT,       F(LWIN),
                                                                            KC_HOME,
                                               SFT_T(KC_SPC),CTL_T(KC_BSPC),LT(SYMB, KC_END),
        // right hand
             KC_RGHT,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
             TG(SYMB),    KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,          KC_BSLS,
                          KC_H,   KC_N,   KC_E,   KC_I,   KC_O,             KC_QUOT,
             KC_MINS,     KC_K,   KC_M,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_UP,  KC_DOWN,KC_LBRC,KC_RBRC,          LT(SYMB,KC_NO),
             KC_LALT,         KC_RALT,
             KC_PGUP,
             LT(MACR,KC_PGDN),CTL_T(KC_TAB), SFT_T(KC_ENT)
    ),
/* Keymap 0b: Basic layer (Colemak keycodes or QWERTY)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   F  |   P  |   G  |  L1  |           |  L1  |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Esc    |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |  O   |   '    |
 * |--------+------+------+------+------+------|   =  |           |   -  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LAlt | LGui |       | LAlt | RAlt |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |Backsp| Home |       | PgUp |        |      |
 *                                 | Space|ace/  |------|       |------|  Tab/  |Enter/|
 *                                 | /Shft|Ctrl  |  1)  |       |  2)  |  Ctrl  |Shift |
 *                                 `--------------------'       `----------------------'
 *
 * 1) End/L1
 * 2) PgDown/L2
 */
[BASE_CM] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,     KC_2,   KC_3,   KC_4,          KC_5,   KC_LEFT,
        KC_DEL,         CM_Q,     CM_W,   CM_F,   CM_P,          CM_G,   TG(SYMB),
        KC_ESC,         CM_A,     CM_R,   CM_S,   CM_T,          CM_D,
        KC_LSFT,        CM_Z,     CM_X,   CM_C,   CM_V,          CM_B,   KC_EQL,
        LT(SYMB,KC_GRV),KC_QUOT,  LALT(KC_LSFT),  KC_LEFT,       KC_RGHT,
                                                             KC_LALT,       F(LWIN),
                                                                            KC_HOME,
                                               SFT_T(KC_SPC),CTL_T(KC_BSPC),LT(SYMB, KC_END),
        // right hand
             KC_RGHT,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
             TG(SYMB),    CM_J,   CM_L,   CM_U,   CM_Y,   KC_P, /*CM_SCLN*/ KC_BSLS,
                          CM_H,   CM_N,   CM_E,   CM_I,   CM_O,             KC_QUOT,
             KC_MINS,     CM_K,   CM_M,   CM_COMM,CM_DOT, CTL_T(CM_SLSH),   KC_RSFT,
                                  KC_UP,  KC_DOWN,KC_LBRC,KC_RBRC,          LT(SYMB,KC_NO),
             KC_LALT,         KC_RALT,
             KC_PGUP,
             LT(MACR,KC_PGDN),CTL_T(KC_TAB), SFT_T(KC_ENT)
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
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
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Macros
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | DLa  | DLb  |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | PC1  | PC2  | PC3  | PC4  |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
// MACROS
[MACR] = LAYOUT_ergodox(
       KC_NO,   KC_NO,     KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   F(DL_BASE),F(DL_BASE_CM),KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   F(PC1),    F(PC2),       F(PC3),  F(PC4),  KC_NO,
       KC_NO,   KC_NO,     KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_NO,     KC_NO,        KC_NO,   KC_NO,
                                           KC_TRNS,KC_TRNS,
                                                   KC_TRNS,
                                   KC_TRNS,KC_TRNS,KC_TRNS,
    // right hand
       KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
       KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [LWIN] = ACTION_MACRO(LWIN),
    [PC1] = ACTION_MACRO(PC1),
    [PC2] = ACTION_MACRO(PC2),
    [PC3] = ACTION_MACRO(PC3),
    [PC4] = ACTION_MACRO(PC4),
    [DL_BASE] = ACTION_DEFAULT_LAYER_SET(BASE),
    [DL_BASE_CM] = ACTION_DEFAULT_LAYER_SET(BASE_CM)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
    case 0:
        if (record->event.pressed) {
            register_code(KC_RSFT);
        } else {
            unregister_code(KC_RSFT);
        }
        break;
    case LWIN:
        if (record->event.pressed) {
             register_code(KC_RSFT);
             unregister_code(KC_RSFT);
             register_code(KC_LGUI);
        } else {
             unregister_code(KC_LGUI);
        }
        break;
    case PC1:
        if (!record->event.pressed) {
             return MACRO(T(SLCK), W(50), T(SLCK), W(50), T(1), W(50), T(ENT), END);
        }
        break;
    case PC2:
        if (!record->event.pressed) {
             return MACRO(T(SLCK), W(50), T(SLCK), W(50), T(2), W(50), T(ENT), END);
        }
        break;
    case PC3:
        if (!record->event.pressed) {
             return MACRO(T(SLCK), W(50), T(SLCK), W(50), T(3), W(50), T(ENT), END);
        }
        break;
    case PC4:
        if (!record->event.pressed) {
             return MACRO(T(SLCK), W(50), T(SLCK), W(50), T(4), W(50), T(ENT), END);
        }
        break;
    }
    return MACRO_NONE;
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
        case SYMB:
            ergodox_right_led_1_on();
            break;
        case MACR:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
};
