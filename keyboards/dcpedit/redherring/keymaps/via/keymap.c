// Copyright 2023 Ming-Gih Lam (@dcpedit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#define LOGO_SIZE 1024

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_default(

      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL,          KC_MUTE,
               KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC, KC_HOME,
               KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
               KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGDN,
      KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(1),   MO(1),   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,          KC_UP,
               KC_LCTL, KC_LGUI,          KC_LALT, KC_MENU, KC_SPC,                    KC_SPC,  KC_ALGR,          KC_RGUI, KC_RCTL,                   KC_LEFT, KC_DOWN, KC_RGHT ),

  [1] = LAYOUT_default(

      QK_RBT,  QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          HF_TOGG,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
               KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS )
};

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM oled_logo[LOGO_SIZE] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xc3, 0x06, 0x18, 0xe1, 0x03, 0x0c, 0xb0, 0x60, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x78, 0x00, 0x00, 0x00, 0xe0, 0x1c, 
        0x00, 0x00, 0xc0, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x04, 0x78, 0x80, 0x00, 
        0x00, 0x38, 0xf8, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 

        0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0xff, 0x1f, 0x3f, 0xfe, 0x3e, 0x7f, 0xfe, 0x7c, 0x7f, 0x7c, 
        0x3c, 0x20, 0x20, 0xe0, 0x7c, 0x43, 0x40, 0xc0, 0xf8, 0x87, 0x80, 0x80, 0xe0, 0x1e, 0x01, 0x00, 
        0xc0, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1e, 0xe0, 0x00, 0x00, 0x07, 0x78, 
        0x80, 0x80, 0x83, 0xbf, 0xff, 0xff, 0xe3, 0xc1, 0xc1, 0xc1, 0xc1, 0xf7, 0xfe, 0xfe, 0xfc, 0x78, 
        0x00, 0x00, 0x10, 0x90, 0x88, 0x4c, 0x64, 0x22, 0x12, 0x11, 0x08, 0x0c, 0x07, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x3c, 0x03, 0x00, 0x80, 0x78, 0x07, 0x00, 0x00, 0xe0, 0x1e, 0x01, 0x01, 0xc1, 0x3d, 
        0x07, 0x02, 0x02, 0xf2, 0x0e, 0x02, 0x02, 0x06, 0x7e, 0xc2, 0x02, 0x03, 0x1f, 0xe1, 0x01, 0x01, 
        0x07, 0x78, 0x80, 0x00, 0x03, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x0f, 0x03, 0x00, 0x00, 
        0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x20, 0x1e, 0x01, 0x00, 0xc0, 0x7c, 0x07, 0x00, 
        0x00, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x7c, 0xc0, 0x00, 0x01, 0x1e, 0xe0, 
        0x00, 0x00, 0x07, 0x38, 0x00, 0x00, 0x03, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 
        0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x38, 0xfe, 0xc7, 0x83, 0xff, 0xff, 0x01, 0x81, 0x03, 0x0f, 0xfe, 0xf0, 0x00, 0xff, 0xff, 0x01, 
        0x01, 0x61, 0xff, 0x9f, 0x01, 0xfe, 0xef, 0x83, 0xff, 0xff, 0x01, 0x01, 0x03, 0x07, 0xfe, 0xf8, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x01, 0x19, 0xff, 0xff, 0x3b, 0x79, 0xf8, 0xcf, 0x07, 0x01, 0x00, 0xf1, 0xff, 0x0e, 
        0x0e, 0x0e, 0x04, 0x00, 0x00, 0x00, 0x01, 0x01, 0xff, 0xff, 0x03, 0x01, 0x00, 0x80, 0xff, 0x7f, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x30, 0xf0, 0xf0, 0x00, 0x00, 0x10, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0x30, 0x30, 0x30, 0xb0, 0xf0, 
        0x70, 0x90, 0xc0, 0xe2, 0xf3, 0xf3, 0x70, 0x30, 0x31, 0x63, 0xe3, 0xc2, 0x00, 0x83, 0xc3, 0xe3, 
        0xf3, 0xf3, 0x73, 0x33, 0x33, 0x60, 0xe0, 0x82, 0x03, 0xf3, 0xf3, 0x13, 0x63, 0xf3, 0xb1, 0xf0, 
        0xe0, 0x00, 0x00, 0x00, 0x10, 0xf0, 0xf0, 0x00, 0xc0, 0xe0, 0x70, 0x30, 0x30, 0x30, 0xe0, 0xc0, 

        0x00, 0xff, 0xff, 0x30, 0x30, 0x30, 0xff, 0xff, 0x80, 0x1f, 0x7f, 0xe0, 0xc0, 0xc0, 0x9f, 0x1f, 
        0x00, 0x07, 0x1f, 0x38, 0xff, 0xff, 0x60, 0x60, 0x10, 0x80, 0xff, 0xff, 0x00, 0x0f, 0x1f, 0x38, 
        0xff, 0xff, 0x60, 0x60, 0x00, 0x80, 0xff, 0x7f, 0x00, 0xff, 0xff, 0x00, 0x00, 0x01, 0x03, 0xff, 
        0xff, 0x1c, 0x78, 0xe0, 0xc0, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x04, 0xe6, 0xe7, 0x63, 
        0x60, 0x7f, 0x7f, 0x00, 0x02, 0x46, 0x7f, 0x7f, 0x00, 0x7c, 0x7f, 0x63, 0x61, 0x61, 0x60, 0x60, 
        0x60, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x47, 0x07, 0x0f, 0x3f, 0x79, 0x60, 0x40, 0x00, 0x00, 0x00, 
        0x7f, 0x7f, 0x47, 0x07, 0x0f, 0x3f, 0x71, 0x40, 0x00, 0x7f, 0x7f, 0x40, 0x00, 0x00, 0x00, 0x7f, 
        0x7f, 0x40, 0x00, 0x00, 0x47, 0x7f, 0x7f, 0x00, 0x1f, 0x3f, 0x70, 0x60, 0x60, 0x7f, 0x7f, 0x40, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(oled_logo, LOGO_SIZE);
}

bool oled_task_user(void) {
    oled_set_cursor(0,0);
    render_logo();
    return false;
}
#endif

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
};
#endif