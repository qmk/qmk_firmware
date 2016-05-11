// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#ifdef BACKLIGHT_ENABLE
#  include "backlight.h"
#endif
#include "timer.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum userlayer {
    _QW = 0,
    _CM,
    _PP,
    _LW,
    _RS,
    _DL,
    _SP,
    NUM_LAYERS,
};

#include "macro_record.h"

/* My macros */
enum usermacro {
    _MLW,
    _MRS,
    _SHLK,                      /* ShiftLock */
};

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
    {KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_FN0 },
    {KC_LCTL,       MO(_SP), KC_LGUI, KC_LALT, M(_MLW), KC_SPC, KC_SPC, M(_MRS), KC_RALT, KC_DOWN, KC_UP,   KC_RCTL}
},
[_CM] = { /* Colemak */
    {KC_TAB,        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
    {CTL_T(KC_ESC), KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
    {KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_FN0 },
    {KC_LCTL,       MO(_SP), KC_LGUI, KC_LALT, M(_MLW), KC_SPC,  KC_SPC,  M(_MRS), KC_RALT, KC_DOWN, KC_UP,   KC_RCTL}
},
[_PP] = { /* Pure Pro / Gaming */
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT },
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_RSFT, KC_UP,   KC_RCTL},
    {KC_LCTL, MO(_SP), KC_LGUI, KC_LALT, M(_MLW), KC_SPC,  KC_SPC,  M(_MRS), KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT}
},
[_LW]= { /* LOWER */
    {KC_TILD, KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
    {KC_ESC,  LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), KC_NO,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
    {_______, LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), LGUI(KC_0), KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_ENT },
    {_______, BL_TOGG,    _______,    _______,    M(_MLW),    KC_BTN1,    KC_BTN1, M(_MRS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[_RS]= { /* RAISE */
    {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL },
    {KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
    {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_CM), DF(_PP), RESET,   KC_ENT },
    {_______, BL_STEP, _______, _______, M(_MLW), KC_BTN2, KC_BTN2, M(_MRS), KC_MPLY, KC_VOLD, KC_VOLU, _______}
},
[_DL]= { /* DUAL */
    {_______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______,       _______,        _______, KC_INS,  _______, KC_PSCR, _______},
    {_______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,       KC_LEFT,        KC_DOWN, KC_UP,   KC_RGHT, KC_ACL0, KC_ACL2},
    {_______, _______, KC_BTN2, KC_BTN3, KC_BTN1, LALT(KC_LEFT), LALT(KC_RIGHT), KC_MUTE, _______, _______, _______, _______},
    {_______, _______, KC_LGUI, KC_LALT, _______, _______,       _______,        _______, _______, _______, _______, _______}
},
[_SP]= { /* special */
    {_______,  M(_REC_START1), M(_MACRO_PLAY1), _______, _______, _______, _______, _______, KC_INS,  _______, KC_PSCR, KC_PAUS},
    {_______,  M(_REC_START2), M(_MACRO_PLAY2), _______, _______, _______, _______, _______, _______, KC_CAPS, KC_SLCK, KC_NLCK},
    {M(_SHLK), _______,        _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______,  _______,        _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______}
},
MACRO_RECORD_KEYMAPS,
};

#undef _______

const uint16_t PROGMEM fn_actions[] = {
    ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),
};




static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (macro_record_macro_handler(record, id)) {
        return MACRO_NONE;
    }

    // MACRODOWN only works in this function
    switch (id) {
    case _MLW:
        if (record->event.pressed) {
            layer_on(_LW);
        } else {
            layer_off(_LW);
        }
        update_tri_layer(_LW, _RS, _DL);
        break;
    case _MRS:
        if (record->event.pressed) {
            layer_on(_RS);
        } else {
            layer_off(_RS);
        }
        update_tri_layer(_LW, _RS, _DL);
        break;
    case _SHLK:
        register_code(KC_LSFT);
        break;
    }
    return MACRO_NONE;
};
