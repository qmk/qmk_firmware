// Copyright 2023 jlw
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define HM_A	LGUI_T(KC_A)
#define HM_R	LALT_T(KC_R)
#define HM_S	LCTL_T(KC_S)

#define HM_E	RCTL_T(KC_E)
#define HM_I	LALT_T(KC_I)
#define HM_O	LGUI_T(KC_O)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_3thumb(
         KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,        KC_MUTE,           KC_J,   KC_L,   KC_U,    KC_Y,   KC_QUOT,
         HM_A,   HM_R,   HM_S,   KC_T,   KC_G,                   KC_M,   KC_N,   HM_E,    HM_I,   HM_O,
         KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,                   KC_K,   KC_H,   KC_COMM, KC_DOT, KC_SLSH,
                         LT(3, KC_TAB), KC_RALT, SFT_T(KC_BSPC),          LT(1, KC_SPC), KC_LGUI, LT(2,KC_ENT)
    ),

    [1] = LAYOUT_3thumb(
         KC_GRAVE, KC_F2,    XXXXXXX,  KC_F4,    KC_F5, _______,     KC_BSLS,  KC_MINUS, KC_EQUAL, KC_LBRC,  KC_RBRC,
         KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
         DF(0),    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            DF(1),    XXXXXXX,  _______,  _______,  KC_SCLN,
                                       _______,  _______,            _______,  _______, _______,  _______
    ),

    [2] = LAYOUT_3thumb(
         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  KC_F11,   KC_F12,   XXXXXXX,  XXXXXXX,
         KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,
         DF(0),    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            DF(2),    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                       _______,  _______,            _______,  _______, _______,  _______
    ),
    [3] = LAYOUT_3thumb(
         XXXXXXX,  XXXXXXX,  LSG(KC_4),LSG(KC_S),XXXXXXX,  _______,  KC_HOME,  XXXXXXX,  KC_UP,    XXXXXXX,  KC_PGUP,
         KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX,            KC_END,   KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_PGDN,
         DF(0),    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            DF(3),    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                       _______,  _______,            _______,  _______, _______,  _______
    )
};

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_BSPC):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

// Encoder Map
#ifdef ENCODER_MAP_ENABLE
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
        [0] =   { ENCODER_CCW_CW(S(KC_F2), KC_F2) },
        [1] =   { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
        [2] =   { ENCODER_CCW_CW(_______, _______) },
        [3] =   { ENCODER_CCW_CW(_______, _______) }
    };
#endif

// Combos disabled for Vial
#ifdef COMBO_ENABLE
    const uint16_t PROGMEM combo_esc[] = {KC_Q, KC_W,    COMBO_END};
    const uint16_t PROGMEM combo_del[] = {KC_Y, KC_QUOT, COMBO_END};
    combo_t key_combos[] = {
        COMBO(combo_esc, KC_ESC),
        COMBO(combo_del, KC_DEL),
    };
#endif

// RGB settings for indicator lights
// Layer and Mods indicator
#define LED_CENTER_TOP 1
#define LED_CENTER_BOTTOM 0

#define LAYER_R layer_colors[layer][0] *  RGB_INDICATOR_BRIGHTNESS / 255
#define LAYER_G layer_colors[layer][1] *  RGB_INDICATOR_BRIGHTNESS / 255
#define LAYER_B layer_colors[layer][2] *  RGB_INDICATOR_BRIGHTNESS / 255

#define MODS_ACTIVE(mods) \
    ((get_mods()|get_oneshot_mods()) & MOD_MASK_##mods ? RGB_INDICATOR_BRIGHTNESS:0)
#define SHIFT_ACTIVE (get_mods() & MOD_MASK_SHIFT ? RGB_INDICATOR_BRIGHTNESS/4:0)
#define MODS_R MODS_ACTIVE(CTRL) + SHIFT_ACTIVE
#define MODS_G MODS_ACTIVE(GUI) + SHIFT_ACTIVE
#define MODS_B MODS_ACTIVE(ALT) + SHIFT_ACTIVE

const uint8_t PROGMEM layer_colors[][3] = {
    {RGB_OFF},
    {RGB_RED},
    {RGB_GREEN},
    {RGB_BLUE},
    {RGB_YELLOW},
    {RGB_PURPLE},
    {RGB_PINK},
    {RGB_TEAL}
};

void set_rgb_matrix_indicators(uint8_t led_min, uint8_t led_max) {
    #if defined(RGB_LAYER_INDICATOR_ENABLE)
    int layer = get_highest_layer(layer_state|default_layer_state);
    RGB_MATRIX_INDICATOR_SET_COLOR(LED_CENTER_TOP, LAYER_R, LAYER_G, LAYER_B);
    /* uprintf("layer RGB: (%u, %u, %u)\n", LAYER_R, LAYER_G, LAYER_B); */
    #else
    RGB_MATRIX_INDICATOR_SET_COLOR(LED_CENTER_TOP, 0, 0, 0);
    #endif

    #if defined(RGB_MODS_INDICATOR_ENABLE)
    RGB_MATRIX_INDICATOR_SET_COLOR(LED_CENTER_BOTTOM, MODS_R, MODS_G, MODS_B);
    /* uprintf("mod RGB: (%u, %u, %u)\n", MODS_R, MODS_G, MODS_B); */
    #else
    RGB_MATRIX_INDICATOR_SET_COLOR(LED_CENTER_BOTTOM, 0, 0, 0);
    #endif
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    set_rgb_matrix_indicators(led_min, led_max);
    return false;
}
