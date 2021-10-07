#include "mw65_rgb.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_default(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, _______, KC_ENT, KC_PGDN,
        KC_LSFT, _______, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, RGB_TOG,
        KC_LCTL, KC_LGUI, KC_LALT, KC_VOLU, KC_VOLD, _______, KC_SPACE, _______, _______, _______, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RIGHT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

	[1] = LAYOUT_default(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, RGB_HUI,
        RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NLCK, RGB_SAI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLCK, RGB_VAI, RGB_SAD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, _______, RGB_SPD, RGB_VAD, RGB_SPI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

	[2] = LAYOUT_default(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

	[3] = LAYOUT_default(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {


	switch (id) {

	}
	return MACRO_NONE;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
        tap_code(dynamic_keymap_get_keycode(biton32(layer_state), 4, 3));
    } else {
        tap_code(dynamic_keymap_get_keycode(biton32(layer_state), 4, 4));
    }
  }
  return true;
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (host_keyboard_led_state().num_lock) {
        for (size_t i = 16; i < 83; i++)
        {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0); // assuming caps lock is at led #5
        }
    }
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(52, 0, 255, 255); // assuming caps lock is at led #5
    }
    if (host_keyboard_led_state().scroll_lock) {
        for (size_t i = 0; i < 16; i++)
        {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0); // assuming caps lock is at led #5
        }
    }
}
