#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_GESC,  KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,  KC_7,   KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_DEL,  KC_BSPC,
        KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,   KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,  KC_J,   KC_K,  KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,  KC_C,  KC_V,  KC_B,  KC_N,   KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  MO(1),
        KC_LCTL,  KC_LGUI,  KC_LALT,                              KC_SPC,                  KC_RALT,  KC_RGUI,  KC_APP,   KC_RCTL),

    [1] = LAYOUT_all(
        KC_GRV,  KC_F1,     KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_DEL,
        KC_TRNS,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  KC_TRNS,  KC_PSCR,  KC_SLCK,  KC_PAUS,  RESET,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_INS,   KC_HOME,  KC_PGUP,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BL_DEC,   BL_TOGG,  BL_INC,   BL_STEP,  KC_TRNS,  KC_DEL,   KC_END,   KC_PGDN,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                          KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS)
};

// Encoder rotate function
void encoder_update_user(uint8_t index, bool clockwise) {
    /* First encoder */
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_AUDIO_VOL_UP);
        } else {
            tap_code(KC_AUDIO_VOL_DOWN);
        }
  }
}

// Encoder click function
void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
    /* First encoder */
    case 0:
        if (active) {
            tap_code(KC_MUTE);
        }
        break;
    }
}
