// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define FN1_SPC     LT(1, KC_SPC)
#define FN2_SPC     LT(2, KC_SPC)
#define HSV_SILLY_PURPLE 180, 255, 255

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _RS3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {    
    [_BASE] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                         KC_MINS,  KC_7,    KC_8,    KC_9,    KC_0,   _______, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,                             KC_Y,    KC_U,    KC_I,    KC_O,       KC_P,      KC_BSLS,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,                         KC_SCLN, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
        KC_LSFT, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    TG(_RS3),   KC_MUTE, KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(2),      FN1_SPC, FN2_SPC,       RGB_RMOD,   RGB_MOD,       FN2_SPC, FN1_SPC,  MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN1] = LAYOUT(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        _______,   KC_F7,   KC_F8,   KC_F9, KC_F10,  _______, KC_DEL, 
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______,  KC_LBRC,    KC_RBRC,   _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, KC_SCLN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, KC_SLSH, KC_PGUP, _______,
        _______, _______, _______, _______,     _______, _______,      _______,    _______,    _______, _______,     _______, KC_HOME, KC_PGDN, KC_END
    ),
    [_FN2] = LAYOUT(                                                                                   
        _______, KC_F11,  KC_F12,  _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, QK_BOOT, _______, _______,                         _______, _______, _______,  _______,    _______,   _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,     _______, _______,      _______,    _______,      _______, _______,     _______, _______, _______, _______
    ),
    [_RS3] = LAYOUT(                                                                                   
        KC_PAST, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        KC_PSLS, _______, _______, _______, _______, _______, _______,                         _______, _______, _______,  _______,    _______,   _______,
        KC_PPLS, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        KC_PMNS, _______, _______, _______, _______, _______, _______, TG(_RS3),   _______, _______, _______, _______, _______, _______, _______, _______,
        KC_HOME, KC_END,  KC_PGUP, KC_K,        KC_L,    KC_M,         KC_PGDN,    _______,      KC_F1,   KC_F2,       KC_F3,   _______, _______, _______
    )
};

#ifdef OLED_ENABLE
     static void render_logo(void) {     // Render MechWild "MW" Logo
          static const char PROGMEM logo_1[] = {0x8A, 0x8B, 0x8C, 0x8D, 0x00};
          static const char PROGMEM logo_2[] = {0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0x00};
          static const char PROGMEM logo_3[] = {0xCA, 0xCB, 0xCC, 0xCD, 0x00};
          static const char PROGMEM logo_4[] = {0x20, 0x8E, 0x8F, 0x90, 0x00};
          oled_set_cursor(0,0);
          oled_write_P(logo_1, false);
          oled_set_cursor(0,1);
          oled_write_P(logo_2, false);
          oled_set_cursor(0,2);
          oled_write_P(logo_3, false);
          oled_set_cursor(0,3);
          oled_write_P(logo_4, false);
     }
    bool oled_task_user(void) {
        render_logo();
        oled_set_cursor(0,6);

        oled_write_ln_P(PSTR("Layer"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("FN 1"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("FN 2"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("RS3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_ln_P(PSTR(""), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    return false;
    }
#endif

#ifdef RGBLIGHT_ENABLE
    // Optional RGB Light Mapping Zones {LED Posiiton, Number of LEDs, Colour}
    const rgblight_segment_t PROGMEM _rgb_fn1[] = RGBLIGHT_LAYER_SEGMENTS(
        {4, 3, HSV_GREEN},
        {12, 3, HSV_GREEN}
    );
    // Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
    const rgblight_segment_t PROGMEM _rgb_fn2[] = RGBLIGHT_LAYER_SEGMENTS(
        {4, 3, HSV_GREEN},
        {12, 3, HSV_GREEN}
    );
    const rgblight_segment_t PROGMEM _rgb_rs3[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, 16, HSV_SILLY_PURPLE}
    );
    const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        _rgb_fn1,
        _rgb_fn2,
        _rgb_rs3
    );
    layer_state_t layer_state_set_user(layer_state_t state) {
        rgblight_set_layer_state(0, layer_state_cmp(state, _FN1));
        rgblight_set_layer_state(1, layer_state_cmp(state, _FN2));
        rgblight_set_layer_state(2, layer_state_cmp(state, _RS3));
        return state;
    }
#endif // RGBLIGHT_ENABLE

void keyboard_post_init_user(void) {
    // Enable the LED layers
    #ifdef RGBLIGHT_ENABLE
        rgblight_layers = _rgb_layers;
    #endif // RGBLIGHT_ENABLE
    }