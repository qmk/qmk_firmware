#include QMK_KEYBOARD_H

#define KC_MO1 MO(1)
#define KC_MO2 MO(2)
#define KC_MO3 MO(3)

#define KC_BLTG BL_TOGG

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_kc(
        ESC, Q, W, F, P, G, J, L, U, Y, SCLN, QUOT, BSPC,
        FN8, A, R, S, T, D, H, N, E, I, O, ENT,
        LSFT, Z, X, C, V, B, K, M, COMM, DOT, SLSH, FN6,
        FN4, LGUI, FN7, MO2, MO1, SPC, FN5, RALT, MO3, FN0),
    [1] = LAYOUT_kc(
        TRNS, FN10, FN11, FN12, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, UP, DEL,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, HOME, PGUP, LEFT, RGHT,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, END, PGDN, DOWN, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS),
    [2] = LAYOUT_kc(
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, 7, 8, 9, 0, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, LBRC, 4, 5, 6, DOT, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, RBRC, 1, 2, 3, BSLS, TRNS,
        TRNS, BLTG, TRNS, TRNS, TRNS, PAUSE, EQL, MINS, TRNS, TRNS),
    [3] = LAYOUT_kc(
        TRNS, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS),
    [4] = LAYOUT_kc(
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, 7, 8, 9, 0, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, LBRC, 4, 5, 6, DOT, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, RBRC, 1, 2, 3, BSLS, TRNS,
        TRNS, BLTG, TRNS, TRNS, TRNS, PAUSE, EQL, MINS, TRNS, TRNS),
};

enum macro_id
{
    PSWD1,
    PSWD2,
    PSWD3,
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_MINS),
    [4] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_GRV),
    [5] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_RGUI),
    [6] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_CAPS),
    [7] = ACTION_LAYER_MODS(4, MOD_LSFT), // FN4
    [8] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_TAB),

    [10] = ACTION_MACRO(PSWD1),
    [11] = ACTION_MACRO(PSWD2),
    [12] = ACTION_MACRO(PSWD3)
};

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id)
    {
    case PSWD1:
        return (record->event.pressed ? MACRO(I(0), T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(ENT), END) : MACRO_NONE);
    case PSWD2:
        return (record->event.pressed ? MACRO(I(0), T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(ENT), END) : MACRO_NONE);
    case PSWD3:
        return (record->event.pressed ? MACRO(I(0), T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(ENT), END) : MACRO_NONE);
        //case VOLUP:
        //    return (record->event.pressed ?
        //            MACRO( D(VOLU), U(VOLU), END ) :
        //            MACRO_NONE );
        //case ALT_TAB:
        //    return (record->event.pressed ?
        //            MACRO( D(LALT), D(TAB), END ) :
        //            MACRO( U(TAB), END ));
    }
    return MACRO_NONE;
}
