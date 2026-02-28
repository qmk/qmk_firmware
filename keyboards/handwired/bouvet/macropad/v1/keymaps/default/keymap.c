// Copyright 2023 Kenneth Fossen
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌──────────────────┬─────────┬─────────┬─────────────┐
     * │ MISSION CONTROL  │ PREVTAB │ NEXTTAB │ MUSIC PAUSE │
     * ├──────────────────┼─────────┼─────────┼─────────────┤
     * │ 4                │ 5       │ 6       │ *           │
     * ├──────────────────┼─────────┼─────────┼─────────────┤
     * │ 1                │ 2       │ 3       │ ENTER       │
     * ├──────────────────┼─────────┼─────────┼─────────────┤
     * │                  │ COPY    │ PASTE   │             │
     * └──────────────────┴─────────┴─────────┴─────────────┘
     */
    [0] = LAYOUT(
        KC_MCTL,   LCS(KC_TAB), C(KC_TAB), KC_MPLY,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
                 LCMD(KC_C), LCMD(KC_V)
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    // uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    uprintf("kc: %s\n", get_keycode_string(keycode));
#endif
  return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    uprintf("OLED");

    render_logo();

    return false;
}
#endif


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
