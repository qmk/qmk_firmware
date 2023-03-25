// Copyright 2022-2023 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "print.h"
#include "wait.h"
// let us assume we start with both layers off
static bool toggle_lwr = false;
static bool toggle_rse = false;

#ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_lwr_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_CYAN});
const rgblight_segment_t PROGMEM my_rse_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_RED});
const rgblight_segment_t PROGMEM my_adj_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_GREEN});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_qwerty_layer, my_lwr_layer, my_rse_layer, my_adj_layer);

#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QW] = LAYOUT_ortho_2x2(
       KC_2   , KC_4     ,
      TT(_LWR), TT(_RSE)),

  [_LWR] = LAYOUT_ortho_2x2(
       RGB_TOG, KC_3     ,
       _______, _______ ),

  [_RSE] = LAYOUT_ortho_2x2(
      KC_5   , KC_6    ,
      _______, _______),

  [_ADJ] = LAYOUT_ortho_2x2(
      RGB_TOG , QK_BOOT ,
       _______, _______),

};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QW]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LWR] = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [_RSE] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_ADJ] = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
};
#endif

bool led_update_user(led_t led_state) {
    // Disable the default LED update code, so that lock LEDs could be reused to show layer status.
    return false;
}

void matrix_scan_user(void) {
    toggle_leds(toggle_lwr, toggle_rse);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    switch (keycode) {
        case (TT(_LWR)):
            if (!record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
                // This runs before the TT() handler toggles the layer state, so the current layer state is the opposite of the final one after toggle.
                set_led_toggle(_LWR, !layer_state_is(_LWR));
            }
            return true;
            break;
        case (TT(_RSE)):
            if (record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
                set_led_toggle(_RSE, !layer_state_is(_RSE));
            }
            return true;
            break;
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE

    set_rgb_layers(state);

#endif

    return update_tri_layer_state(state, _LWR, _RSE, _ADJ);
}

#ifdef RGBLIGHT_ENABLE

layer_state_t default_layer_state_set_user(layer_state_t state) {
    set_default_rgb_layers(state);
    return state;
}

#endif

#ifdef RGBLIGHT_ENABLE

void set_rgb_layers(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _QW));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LWR));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RSE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJ));
}

void set_default_rgb_layers(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _QW));
}

const rgblight_segment_t* const* my_rgb(void) {
    return my_rgb_layers;
}

#endif

void set_led_toggle(const uint8_t layer, const bool state) {
    switch (layer) {
        case _LWR:
            toggle_lwr = state;
            break;
        case _RSE:
            toggle_rse = state;
            break;
        default:
            break;
    }
}

#ifdef OLED_ENABLE

void user_oled_magic(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QW:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LWR:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RSE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJ:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("Caps Lock") : PSTR("         "), false);

#    ifdef UNICODE_COMMON_ENABLE
    oled_write_P(PSTR("\nunicode: "), false);
    switch (get_unicode_input_mode()) {
        case UC_LNX:
            oled_write_P(PSTR("Linux"), false);
            break;
        case UC_MAC:
            oled_write_P(PSTR("apple"), false);
            break;
        case UC_WIN:
            oled_write_P(PSTR("windows"), false);
            break;
        case UC_WINC:
            oled_write_P(PSTR("windows c"), false);
            break;
        default:
            oled_write_ln_P(PSTR("not supported"), false);
    }
#    endif

#    ifdef WPM_ENABLE
    oled_write_P(PSTR("\nwpm: "), false);
    uint8_t wpm = get_current_wpm();
    oled_write_P(wpm != 0 ? get_u8_str(wpm, ' ') : PSTR("   "), false);
#    endif
}

#endif

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
#    ifdef RGB_ENABLE_PIN
    setPinOutput(RGB_ENABLE_PIN);
    writePinHigh(RGB_ENABLE_PIN);
    wait_ms(20);
#    endif

    // Enable the LED layers
    rgblight_layers = my_rgb();
#endif

    init_lwr_rse_led();

#ifdef CONSOLE_ENABLE
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
#endif

#ifdef OLED_ENABLE
    init_timer();
#endif
}
