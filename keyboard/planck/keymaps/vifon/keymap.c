// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#ifdef BACKLIGHT_ENABLE
#  include "backlight.h"
#endif
#include "action_layer.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum {
    _QW = 0,
    _CM,
    _PP,
    _LW,
    _RS,
    _SP,
    _REC,
};


/* My macros */
enum {
    /* Warning! _REC_START and _MACRO_PLAY *must* be on the same layer! */
    _REC_START,
    _REC_KEY,
    _REC_STOP,
    _MACRO_PLAY,

    _MC1,
    _MC2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
    {KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_FN0 },
    {KC_LCTL,       MO(_SP), KC_LGUI, KC_LALT, MO(_LW), KC_SPC, KC_SPC, MO(_RS), KC_RALT, KC_DOWN, KC_UP,   KC_RCTL}
},
[_CM] = { /* Colemak */
    {KC_TAB,        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
    {CTL_T(KC_ESC), KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
    {KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_FN0 },
    {KC_LCTL,       MO(_SP), KC_LGUI, KC_LALT, MO(_LW), KC_SPC,  KC_SPC,  MO(_RS), KC_RALT, KC_DOWN, KC_UP,   KC_RCTL}
},
[_PP] = { /* Pure Pro / Gaming */
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT },
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_RSFT, KC_UP,   KC_RCTL},
    {KC_LCTL, MO(_SP), KC_LGUI, KC_LALT, MO(_LW), KC_SPC,  KC_SPC,  MO(_RS), KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT}
},
[_LW]= { /* LOWER */
    {KC_TILD, KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,        KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
    {KC_TRNS, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), M(_REC_START),  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
    {KC_TRNS, LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), LGUI(KC_0), M(_MACRO_PLAY), KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS},
    {KC_TRNS, BL_TOGG,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        MO(_SP), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[_RS]= { /* RAISE */
    {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL },
    {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
    {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_CM), DF(_PP), RESET,   KC_TRNS},
    {KC_TRNS, BL_STEP, KC_TRNS, KC_TRNS, MO(_SP), KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_VOLD, KC_VOLU, KC_TRNS}
},
[_SP]= { /* special */
    {KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_PSCR, KC_BSPC},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SLCK, KC_QUOT},
    {KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
    {KC_LCTL, KC_TRNS, KC_LGUI, KC_LALT, M(_MC1), KC_SPC,  KC_SPC,  M(_MC2), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
},
[_REC] = { /* Macro recording */
    {M(_REC_KEY), M(_REC_KEY),  M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY)},
    {M(_REC_KEY), M(_REC_KEY),  M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY)},
    {M(_REC_KEY), M(_REC_KEY),  M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY)},
    {M(_REC_KEY), M(_REC_STOP), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY), M(_REC_KEY)}
},
};

const uint16_t PROGMEM fn_actions[] = {
    ACTION(ACT_MODS_TAP, ((MOD_RSFT)&0x1f)<<8 | (KC_ENT))
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    static keyrecord_t macro_buffer[256];
    static keyrecord_t *macro_end = macro_buffer;
    static keyrecord_t *macro_pointer = macro_buffer;

    // MACRODOWN only works in this function
    switch(id) {
    case _REC_START:
        backlight_toggle();
        if (!record->event.pressed) {
            clear_keyboard();
            macro_pointer = macro_buffer;
            layer_on(_REC);
        }
        break;
    case _MACRO_PLAY:
        backlight_toggle();
        if (!record->event.pressed) {
            uint32_t saved_layer_state = layer_state;

            clear_keyboard();
            macro_pointer = macro_buffer;
            while (macro_pointer != macro_end) {
                process_action(macro_pointer);
                ++macro_pointer;
            }

            layer_state = saved_layer_state;
        }
        break;
    case _REC_KEY:
        *macro_pointer++ = *record;
        break;
    case _REC_STOP:
        backlight_toggle();
        if (!record->event.pressed) {
            macro_end = macro_pointer;
            layer_off(_REC);

            /* Disable the modifier held while starting the recording.
             * Its keyup was recorded at the very beginning of the
             * recording so we just play the first key now.
             */
            process_action(&macro_buffer[0]);
        }
        break;

    case _MC1:
        if (!record->event.pressed) {
            layer_off(_LW);
            layer_on(_RS);
            layer_off(_SP);
        }
        break;
    case _MC2:
        if (!record->event.pressed) {
            layer_on(_LW);
            layer_off(_RS);
            layer_off(_SP);
        }
        break;
    }
    return MACRO_NONE;
};
