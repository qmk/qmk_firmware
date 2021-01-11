#include QMK_KEYBOARD_H

/* Mike's Layout for JD45 with backlight LEDs acting as layer indicator
 */

#define KC_TT2 TT(2)
#define KC_BLST BL_STEP
#define KC_BLTG BL_TOGG

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_kc(
        TAB, Q, W, E, R, T, Y, U, I, O, P, MINS, BSLS,
        FN1, A, S, D, F, G, H, J, K, L, QUOT, ENT,
        FN0, Z, X, C, V, B, N, M, COMM, DOT, SLSH, RSFT,
        NO, LCTL, LALT, LGUI, SPC, BSPC, APP, TT2, ESC, NO),
    [1] = LAYOUT_kc(
        GRV, TRNS, UP, TRNS, 7, 8, 9, 0, MINS, EQL, PSCR, LBRC, RBRC,
        TRNS, LEFT, DOWN, RGHT, 4, 5, 6, INS, HOME, PGUP, SCLN, TRNS,
        TRNS, TRNS, TRNS, TRNS, 1, 2, 3, DEL, END, PGDN, TRNS, TRNS,
        TRNS, TRNS, TRNS, SPC, TRNS, DEL, TRNS, BLST, TRNS, TRNS),
    [2] = LAYOUT_kc(
        TRNS, TRNS, VOLU, TRNS, F7, F8, F9, F10, F11, F12, PSCR, BLST, BLTG,
        TRNS, MPRV, VOLD, MNXT, F4, F5, F6, J, K, L, SCLN, TRNS,
        TRNS, TRNS, TRNS, TRNS, F1, F2, F3, MUTE, MPRV, MNXT, MSTP, TRNS,
        TRNS, TRNS, TRNS, LGUI, TRNS, TRNS, TRNS, TRNS, PAUS, TRNS)
    /*  ,
[3] = LAYOUT_kc(
TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
TRNS, TRNS, TRNS, TRNS, TRNS, BTLD, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS )*/
};

enum macro_id
{
    M_LAYER1,
    M_LAYER2
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_TOGGLE(MOD_LSFT),
    [1] = ACTION_MACRO(M_LAYER1)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch (id)
    {
    case M_LAYER1:
        // need to add a timer for doubletap: https://github.com/jackhumbert/qmk_firmware/wiki#timer-functionality
        // action_function_tap may also handle this...
        if (record->event.pressed)
        {
            breathing_period_set(3);
            breathing_enable();
            layer_on(1);
        }
        else
        {
            breathing_period_set(1);
            breathing_self_disable();
            layer_off(1);
        }
        break;
    case M_LAYER2:
        if (record->event.pressed)
        {
            breathing_period_set(2);
            breathing_pulse();
            layer_on(2);
        }
        else
        {
            breathing_period_set(1);
            breathing_self_disable();
            layer_off(2);
        }
        break;
    }
    return MACRO_NONE;
};
