// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "satan.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DEF 0
#define _SPC 1
#define _TAB 2
#define _SFX 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _DEF: Default Layer
     * ,-----------------------------------------------------------.
     * |Grv|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   \ | Tab is Fn1 !!
     * |-----------------------------------------------------------|
     * |Ctrl   | A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| Return |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn2| RShift is UP
     * |-----------------------------------------------------------|
     * |Ctrl|Win |Alt |      Space/Fn0         |Alt |Win |Menu|RCtl| Gui Menu, RCtrl is 
     * `-----------------------------------------------------------'   LEFT DWN RIGHT
     */
    [_DEF] = KEYMAP_ISO_SPLITRSHIFT(
            KC_GRV,          KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS,        KC_EQL,          KC_BSPC,         \
            LT(_TAB,KC_TAB), KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC,        KC_RBRC,         KC_BSLS,         \
            CTL_T(KC_ESC),   KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,        KC_NUHS,         CTL_T(KC_ENT),   \
            KC_LSFT,         KC_NUBS, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,        TG(_SFX),        SFT_T(KC_UP),    \
            KC_LCTL,         KC_LGUI, KC_LALT,             LT(_SPC,KC_SPACE),               KC_RALT, ALT_T(KC_LEFT), GUI_T(KC_DOWN),  CTL_T(KC_RIGHT)),

    /* Keymap 1: F-and-vim Layer, modified with Space (by holding space)
     * ,-----------------------------------------------------------.
     * |PrSc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete|
     * |-----------------------------------------------------------|
     * |    |Paus| Up| [ | ] |   |   |   | ( | ) |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |Lft|Dwn|Rgt|   |   |   |Left|Down|Right|Up|  | PLAY |
     * |-----------------------------------------------------------|
     * |        |   |   | < | > |   |M0 |   | { | } |   | Vol+ |   |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |Alt |Prev|Vol-|Next|
     * `-----------------------------------------------------------'
     */
    [_SPC] = KEYMAP_ISO_SPLITRSHIFT(
            KC_PSCR, KC_F1,   KC_F2,   KC_F3,      KC_F4,      KC_F5,         KC_F6,   KC_F7,      KC_F8,      KC_F9,      KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
            KC_TRNS, KC_PAUS, KC_UP,   RALT(KC_8), RALT(KC_9), KC_TRNS,       KC_TRNS, LSFT(KC_8), LSFT(KC_9), KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
            KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,   KC_TRNS,    KC_TRNS,       KC_LEFT, KC_DOWN,    KC_UP,      KC_RGHT,    KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, \
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_NUBS,    LSFT(KC_NUBS), KC_SPACE,M(0),       RALT(KC_7), RALT(KC_0), KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, \
            KC_TRNS, KC_TRNS, KC_TRNS,                                        KC_TRNS,                                     KC_TRNS, KC_MPRV, KC_VOLD, KC_MNXT),

    /* Keymap 2: Tab Layer w/ vim pageup, modified with Tab (by holding tab)
     * ,-----------------------------------------------------------.
     * |WAKE|   |   |   |   |   |   |   |   |   |   |   |   |Insert|  TAB+GRC = WAKE
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   |   |Pos1|PgDn|PgUp|End|  |Retrn |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |AF2|   |   |   |   | PgUp |   |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |Alt |Pos1|PgDn|End |
     * `-----------------------------------------------------------'
     */
    [_TAB] = KEYMAP_ISO_SPLITRSHIFT(
            KC_WAKE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  \
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT,  \
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(1),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, \
            KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_HOME, KC_PGDN, KC_END),

    /* Keymap 3: Split right shift Numpad toggle Layer (by tapping the split rshift key)
     * ,-----------------------------------------------------------.
     * |RSET|  |   |   |   |   |   |  7|  8|  9|   |   |   |Backsp |
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   | 4 | 5 | 6 |   |   |   |   \ |
     * |-----------------------------------------------------------|
     * |      | L | L |   |   |   |   | 1 | 2 | 3 |   |   | Return |
     * |-----------------------------------------------------------|
     * |        | L | L | L | L | L | L |   | 0 |   |  /|  Up  |   | All "L"s represent
     * |-----------------------------------------------------------| LED controlling
     * |Ctrl|Win |Alt |                        |Alt |Left|Down|Right|
     * `-----------------------------------------------------------'
     */
    [_SFX] = KEYMAP_ISO_SPLITRSHIFT(
            RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_7,    KC_8,    KC_9, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, \
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4,    KC_5,    KC_6, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, \
            KC_TRNS, F(2),    F(3),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_1,    KC_2,    KC_3, KC_TRNS, KC_TRNS, KC_NO,   KC_ENT,  \
            KC_TRNS, F(4),    F(5),    F(6),    F(7),    F(8),    F(9),    KC_TRNS, KC_TRNS, KC_0, KC_TRNS, KC_SLSH, KC_TRNS, KC_UP,   \
            KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                         KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),
};

enum function_id {
    LAUNCH,
    RGBLED_TOGGLE,
    RGBLED_STEP_MODE,
    RGBLED_INCREASE_HUE,
    RGBLED_DECREASE_HUE,
    RGBLED_INCREASE_SAT,
    RGBLED_DECREASE_SAT,
    RGBLED_INCREASE_VAL,
    RGBLED_DECREASE_VAL,
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_FUNCTION(LAUNCH),
    [2] = ACTION_FUNCTION(RGBLED_TOGGLE),
    [3] = ACTION_FUNCTION(RGBLED_STEP_MODE),
    [4] = ACTION_FUNCTION(RGBLED_INCREASE_HUE),
    [5] = ACTION_FUNCTION(RGBLED_DECREASE_HUE),
    [6] = ACTION_FUNCTION(RGBLED_INCREASE_SAT),
    [7] = ACTION_FUNCTION(RGBLED_DECREASE_SAT),
    [8] = ACTION_FUNCTION(RGBLED_INCREASE_VAL),
    [9] = ACTION_FUNCTION(RGBLED_DECREASE_VAL),
    [10] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ENT),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch(id) {
        case 0:
            return (record->event.pressed ? 
                    MACRO( D(RALT), T(SPC), U(RALT), END )
                    :MACRO( END ));
            break;
        case 1:
            return (record->event.pressed ? 
                    MACRO( D(LALT), T(F2), U(LALT), END )
                    :MACRO( END ));
            break;
    }
    return MACRO_NONE;
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
        case RGBLED_TOGGLE:
            //led operations
            if (record->event.pressed) {
                rgblight_toggle();
            }
            break;
        case RGBLED_INCREASE_HUE:
            if (record->event.pressed) {
                rgblight_increase_hue();
            }
            break;
        case RGBLED_DECREASE_HUE:
            if (record->event.pressed) {
                rgblight_decrease_hue();
            }
            break;
        case RGBLED_INCREASE_SAT:
            if (record->event.pressed) {
                rgblight_increase_sat();
            }
            break;
        case RGBLED_DECREASE_SAT:
            if (record->event.pressed) {
                rgblight_decrease_sat();
            }
            break;
        case RGBLED_INCREASE_VAL:
            if (record->event.pressed) {
                rgblight_increase_val();
            }
            break;
        case RGBLED_DECREASE_VAL:
            if (record->event.pressed) {
                rgblight_decrease_val();
            }
            break;
        case RGBLED_STEP_MODE:
            if (record->event.pressed) {
                rgblight_step();
            }
            break;
    }
}
