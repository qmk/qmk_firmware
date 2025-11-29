// Copyright 2025 Dimitrix LLC
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum LAYER {
  _PC = 0,
  _MAC = 1,
  _FN = 2
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_PC] = LAYOUT(
    KC_ESC,  KC_F1, KC_F2, KC_F3,  KC_F4, KC_F5, KC_F6, KC_F7, KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_BSPC, 
    KC_GRV,  KC_1,   KC_2, KC_3,   KC_4,  KC_5,  KC_6,  KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS,
    KC_TAB,  KC_Q,   KC_W, KC_E,   KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_ENT,
    KC_LGUI, KC_A,   KC_S, KC_D,   KC_F,  KC_G,  KC_H,  KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT, 
    KC_LSFT, KC_Z,   KC_X, KC_C,   KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH,          KC_UP,   KC_RSFT,
    KC_LCTL, KC_LALT,              KC_SPC,                              MO(_FN),         KC_LEFT, KC_DOWN, KC_RGHT
),
[_MAC] = LAYOUT(
    KC_ESC,  KC_F1, KC_F2, KC_F3,  KC_F4, KC_F5, KC_F6, KC_F7, KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_BSPC, 
    KC_GRV,  KC_1,   KC_2, KC_3,   KC_4,  KC_5,  KC_6,  KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS,
    KC_TAB,  KC_Q,   KC_W, KC_E,   KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_ENT,
    KC_LALT, KC_A,   KC_S, KC_D,   KC_F,  KC_G,  KC_H,  KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT, 
    KC_LSFT, KC_Z,   KC_X, KC_C,   KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH,          KC_UP,   KC_RSFT,
    KC_LCTL, KC_LGUI,              KC_SPC,                              MO(_FN),         KC_LEFT, KC_DOWN, KC_RGHT
),
[_FN] = LAYOUT(
    KC_PAUSE, KC_WWW_BACK, KC_WWW_FORWARD, KC_WWW_REFRESH, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_SYSTEM_POWER, KC_PRINT_SCREEN, KC_DEL, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_CAPS_LOCK, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_PAGE_UP,   KC_TRNS,
    KC_TRNS, KC_TRNS,              KC_TRNS,                                     KC_TRNS,          KC_HOME, KC_PAGE_DOWN, KC_END
)
};
// clang-format on

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_keyboard = true;
#else
    debug_enable = false;
    debug_keyboard = false;
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

bool process_detected_host_os_kb(os_variant_t os)
{
#ifdef CONSOLE_ENABLE
    switch (os) {
        case OS_MACOS:
            uprintf("MacOS detected\n");
            break;
        case OS_IOS:
            uprintf("iOS detected\n");
            break;
        case OS_WINDOWS:
            uprintf("Windows detected\n");
            break;
        case OS_LINUX:
            uprintf("Linux detected\n");
            break;
        case OS_UNSURE:
            uprintf("Unable to detect host OS\n");
            break;
    }
#endif
    /* If Apple, swap to macOS layer. */
    if (os == OS_MACOS || os == OS_IOS) {
        set_single_default_layer(_MAC);
    }
    else /* Else use PC layer */ {
        set_single_default_layer(_PC);
    }
    return true;
}
