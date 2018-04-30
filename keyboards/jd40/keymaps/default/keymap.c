#include QMK_KEYBOARD_H
#include "action_layer.h"

#define _BL 0
#define _AL 1
#define _FL 2
#define _UL 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT(
        F12, Q, W, E, R, T, Y, U, I, O, P, BSPC,
        TAB, A, S, D, F, G, H, J, K, L, ENT,
        LSFT, Z, X, C, V, B, N, M, COMM, UP, DOT,
        LCTL, LGUI, LALT, FN0, SPC, SPC, FN0, LEFT, DOWN, RIGHT),

    [_AL] = LAYOUT(
        GRV, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, DEL,
        CAPS, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, SCLN, PGUP, QUOT,
        TRNS, TRNS, TRNS, TRNS, FN3, FN3, TRNS, HOME, PGDN, END),

    [_FL] = LAYOUT(
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS),

    [_UL] = LAYOUT(
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, FN4, FN5, FN11, FN10, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS),
};

enum function_id
{
    RGBLED_TOGGLE,
    RGBLED_STEP_MODE,
    RGBLED_INCREASE_HUE,
    RGBLED_DECREASE_HUE,
    RGBLED_INCREASE_SAT,
    RGBLED_DECREASE_SAT,
    RGBLED_INCREASE_VAL,
    RGBLED_DECREASE_VAL,
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),         // Momentary Fn overlay
    [1] = ACTION_LAYER_TOGGLE(2),            // Toggle Arrow Layer overlay
    [2] = ACTION_LAYER_TAP_KEY(2, KC_CAPS),  // Tap to toggle caps lock and hold to activate function layer
    [3] = ACTION_LAYER_TOGGLE(3),            // Toggle Underglow Layer overlay
    [4] = ACTION_FUNCTION(RGBLED_TOGGLE),    //Turn on/off underglow
    [5] = ACTION_FUNCTION(RGBLED_STEP_MODE), // Change underglow mode
    [6] = ACTION_FUNCTION(RGBLED_INCREASE_HUE),
    [7] = ACTION_FUNCTION(RGBLED_DECREASE_HUE),
    [8] = ACTION_FUNCTION(RGBLED_INCREASE_SAT),
    [9] = ACTION_FUNCTION(RGBLED_DECREASE_SAT),
    [10] = ACTION_FUNCTION(RGBLED_INCREASE_VAL),
    [11] = ACTION_FUNCTION(RGBLED_DECREASE_VAL),
    [12] = ACTION_FUNCTION(SHIFT_ESC),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch (id)
    {
    case 0:
        if (record->event.pressed)
        {
            register_code(KC_RSFT);
        }
        else
        {
            unregister_code(KC_RSFT);
        }
        break;
    }
    return MACRO_NONE;
};

void matrix_scan_user(void)
{

    // Layer LED indicators
    // ESC led on when in function layer, WASD cluster leds enabled when on arrow cluster
    uint32_t layer = layer_state;
    if (layer & (1 << 1))
    {
        //gh60_wasd_leds_on();
    }
    else
    {
        //gh60_wasd_leds_off();
    }

    if (layer & (1 << 2))
    {
        //gh60_esc_led_on();
    }
    else
    {
        //gh60_esc_led_off();
    }
};

#define MODS_CTRL_MASK (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id)
    {
    case RGBLED_TOGGLE:
        //led operations
        if (record->event.pressed)
        {
            rgblight_toggle();
        }
        break;
    case RGBLED_INCREASE_HUE:
        if (record->event.pressed)
        {
            rgblight_increase_hue();
        }
        break;
    case RGBLED_DECREASE_HUE:
        if (record->event.pressed)
        {
            rgblight_decrease_hue();
        }
        break;
    case RGBLED_INCREASE_SAT:
        if (record->event.pressed)
        {
            rgblight_increase_sat();
        }
        break;
    case RGBLED_DECREASE_SAT:
        if (record->event.pressed)
        {
            rgblight_decrease_sat();
        }
        break;
    case RGBLED_INCREASE_VAL:
        if (record->event.pressed)
        {
            rgblight_increase_val();
        }
        break;
    case RGBLED_DECREASE_VAL:
        if (record->event.pressed)
        {
            rgblight_decrease_val();
        }
        break;
    case RGBLED_STEP_MODE:
        if (record->event.pressed)
        {
            rgblight_step();
        }
        break;
        static uint8_t shift_esc_shift_mask;
    // Shift + ESC = ~
    case SHIFT_ESC:
        shift_esc_shift_mask = get_mods() & MODS_CTRL_MASK;
        if (record->event.pressed)
        {
            if (shift_esc_shift_mask)
            {
                add_key(KC_GRV);
                send_keyboard_report();
            }
            else
            {
                add_key(KC_ESC);
                send_keyboard_report();
            }
        }
        else
        {
            if (shift_esc_shift_mask)
            {
                del_key(KC_GRV);
                send_keyboard_report();
            }
            else
            {
                del_key(KC_ESC);
                send_keyboard_report();
            }
        }
        break;
    }
};
