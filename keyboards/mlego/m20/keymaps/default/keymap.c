// Copyright 2022-2023 Alin M Elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

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
    [_NUM] = LAYOUT_ortho_5x4(
        KC_PSLS, KC_PAST, KC_MINS,   KC_EQL,
           KC_7,    KC_8,    KC_9,  KC_BSPC,
           KC_4,    KC_5,    KC_6,  KC_PPLS,
           KC_1,    KC_2,    KC_3,  KC_PENT,
       TT(_LWR),    KC_0,  KC_DOT,  TT(_RSE)
    ),
    [_LWR] = LAYOUT_ortho_5x4(
         KC_ESC, _______, _______, _______,
        KC_HOME,   KC_UP, KC_PGUP, _______,
        KC_LEFT, _______, KC_RGHT, _______,
         KC_END, KC_DOWN, KC_PGDN, _______,
        _______, _______,  KC_DEL, _______
    ),
    [_RSE] = LAYOUT_ortho_5x4(
        _______, _______, _______, _______,
        KC_HOME,   KC_UP, KC_PGUP, _______,
        KC_LEFT, _______, KC_RGHT, _______,
         KC_END, KC_DOWN, KC_PGDN, _______,
        _______, _______,  KC_DEL, _______
    ),
    [_ADJ] = LAYOUT_ortho_5x4(
        _______, _______, _______, _______,
        KC_HOME,   KC_UP, KC_PGUP, _______,
        KC_LEFT, _______, KC_RGHT, _______,
         KC_END, KC_DOWN, KC_PGDN, _______,
        _______, QK_BOOT,  KC_DEL, _______
    )
};

// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_NUM] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LWR] = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [_RSE] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_ADJ] = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
};
#endif

void matrix_scan_user(void) {
    toggle_leds(toggle_lwr, toggle_rse);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
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
    rgblight_set_layer_state(0, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LWR));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RSE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJ));
}

void set_default_rgb_layers(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _NUM));
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
        case _NUM:
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

#    ifdef WPM_ENABLE
    oled_write_P(PSTR("\nwpm: "), false);
    uint8_t wpm = get_current_wpm();
    oled_write_P(wpm != 0 ? get_u8_str(wpm, ' ') : PSTR("   "), false);
#    endif
}

#endif

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    // Enable the LED layers
    rgblight_layers = my_rgb();
#endif

    init_lwr_rse_led();

#ifdef OLED_ENABLE
    init_timer();
#endif
}
