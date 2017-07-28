// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#ifdef BACKLIGHT_ENABLE
#  include "backlight.h"
#endif
#include "timer.h"
#include <bootloader.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum userlayer {
    _QW = 0,
    _CM,
    _PP,
    _PPG,
    _NM,
    _LW,
    _RS,
    _DL,
    _DYN,
};

enum planck_keycodes {
    KM_LW = SAFE_RANGE,
    KM_RS,
    KM_SHLK,                    /* ShiftLock */
    KM_RST,                     /* Reset */
    KM_NUM,                     /* Numeric layer */
    KM_SLP,                     /* Sleep 250 ms */
    KM_PPLR,                    /* Pure Pro layer */
    DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
    {KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_FN0 },
    {KC_LCTL,       MO(_DYN),KC_LGUI, KC_LALT, KM_LW,   KC_SPC, KC_SPC, KM_RS,   KC_RALT, KC_DOWN, KC_UP,   KC_RCTL}
},
[_CM] = { /* Colemak */
    {KC_TAB,        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
    {CTL_T(KC_ESC), KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
    {KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_FN0 },
    {KC_LCTL,       MO(_DYN),KC_LGUI, KC_LALT, KM_LW,   KC_SPC,  KC_SPC,  KM_RS,   KC_RALT, KC_DOWN, KC_UP,   KC_RCTL}
},
[_PP] = { /* Pure Pro */
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT },
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_RSFT, KC_UP,   KC_RCTL},
    {KC_LCTL, MO(_DYN),KC_LGUI, KC_LALT, KM_LW,   KC_SPC,  KC_SPC,  KM_RS,   KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT}
},
[_PPG] = { /* Pure Pro: Gaming */
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, XXXXXXX, _______, KM_RS  , _______, _______, KM_LW  , _______, _______, _______, _______},
},
[_NM] = { /* Numeric */
    {KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {KC_LSFT, _______, _______, _______, _______, _______, _______, _______, KC_COMM, KC_DOT,  _______, KC_FN0 },
    {_______, _______, _______, _______, _______, KC_SPC,  KC_SPC,  _______, _______, _______, _______, _______}
},
[_LW]= { /* LOWER */
    {KC_TILD, KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
    {KC_ESC,  LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), KM_NUM,  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
    {_______, LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), LGUI(KC_0), KM_SLP,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_ENT },
    {_______, BL_TOGG,    _______,    _______,    _______,    KC_BTN1,    KC_BTN1, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[_RS]= { /* RAISE */
    {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL },
    {KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
    {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_CM), KM_PPLR, KM_RST,  KC_ENT },
    {_______, BL_STEP, _______, _______, _______, KC_BTN2, KC_BTN2, _______, KC_MPLY, KC_VOLD, KC_VOLU, _______}
},
[_DL]= { /* DUAL */
    {_______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______,     _______,        KC_APP,  KC_INS,  _______, KC_PSCR, _______},
    {_______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,     KC_LEFT,        KC_DOWN, KC_UP,   KC_RGHT, KC_ACL0, KC_ACL2},
    {_______, _______, KC_BTN2, KC_BTN3, KC_BTN1, KC_WWW_BACK, KC_WWW_FORWARD, KC_MUTE, _______, _______, _______, _______},
    {_______, _______, KC_LGUI, KC_LALT, _______, _______,     _______,        _______, _______, _______, _______, _______}
},
[_DYN]= { /* special */
    {_______,  DYN_REC_START1, DYN_MACRO_PLAY1, _______, _______, _______, _______, KC_APP,  KC_INS,  _______, KC_PSCR, KC_PAUS},
    {_______,  DYN_REC_START2, DYN_MACRO_PLAY2, _______, _______, _______, _______, _______, _______, KC_CAPS, KC_SLCK, KC_NLCK},
    {KM_SHLK,  _______,        _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______,  _______,        _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______}
},
};

#undef _______

const uint16_t PROGMEM fn_actions[] = {
    ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t key_timer;

    uint16_t macro_kc = (keycode == MO(_DYN) ? DYN_REC_STOP : keycode);
    if (!process_record_dynamic_macro(macro_kc, record)) {
        return false;
    }

    switch (keycode) {
    case KM_LW:
        if (record->event.pressed) {
            layer_on(_LW);
        } else {
            layer_off(_LW);
        }
        update_tri_layer(_LW, _RS, _DL);
        return false;
        break;
    case KM_RS:
        if (record->event.pressed) {
            layer_on(_RS);
        } else {
            layer_off(_RS);
        }
        update_tri_layer(_LW, _RS, _DL);
        return false;
        break;
    case KM_SHLK:
        register_code(KC_LSFT);
        break;
    case KM_RST:
        if (record->event.pressed) {
            key_timer = timer_read();
        } else {
            if (timer_elapsed(key_timer) >= 500) {
                clear_keyboard();
                backlight_toggle();
                _delay_ms(250);
                backlight_toggle();
                bootloader_jump();
            }
        }
        break;
    case KM_PPLR:
        if (record->event.pressed) {
            key_timer = timer_read();
        } else {
            if (timer_elapsed(key_timer) >= 250) {
                default_layer_set((1UL << _PP) | (1UL << _PPG));
                backlight_toggle();
                _delay_ms(100);
                backlight_toggle();
            } else {
                default_layer_set(1UL << _PP);
            }
        }
        break;
    case KM_NUM:
        layer_on(_NM);
        break;
    case KM_SLP:
        if (record->event.pressed) {
            _delay_ms(250);
        }
        break;
    }


    if (record->event.pressed
        && IS_LAYER_ON(_NM)
        && keymap_key_to_keycode(_NM, record->event.key) == KC_TRNS) {

        layer_off(_NM);
    }

    return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    return MACRO_NONE;
}
