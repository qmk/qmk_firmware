// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include <hal.h>
#include <string.h>
#include <ctype.h>
#include "backlight.h"
#include "qp.h"
#include <printf.h>
#include "transactions.h"
#include "split_util.h"

// Layer definitions
enum { _QWERTY, _LOWER, _RAISE, _ADJUST };

//----------------------------------------------------------
// Key map

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_all(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,      KC_5,    KC_GRV,                              KC_DEL,  KC_6,     KC_7,      KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,      KC_T,    KC_LBRC,                             KC_RBRC, KC_Y,     KC_U,      KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,      KC_G,    KC_HOME,                             KC_PGUP, KC_H,     KC_J,      KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,      KC_B,    KC_END,                              KC_PGDN, KC_N,     KC_M,      KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   KC_LGUI, MO(_LOWER),KC_SPC,  KC_NO,                               KC_NO,   KC_SPC,   MO(_RAISE),KC_LALT,
                                                                      RGB_RMOD,              RGB_MOD,
                                                       KC_UP,                                                 KC_UP,
                                            KC_LEFT,   _______, KC_RIGHT,                            KC_LEFT, _______, KC_RIGHT,
                                                       KC_DOWN,                                               KC_DOWN
    ),
    [_LOWER] = LAYOUT_all(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   _______,                             _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, KC_UP,   _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______,   _______, _______,                             _______, _______, _______, _______,
                                                                      BL_DEC,                BL_INC,
                                                     _______,                                               _______,
                                            _______,   _______, _______,                             _______, _______, _______,
                                                     _______,                                               _______
    ),
    [_RAISE] = LAYOUT_all(
        KC_F12, KC_F1,   KC_F2,    KC_F3,   KC_F4,     KC_F5,   _______,                             _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______,_______, KC_UP,    _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______,KC_LEFT, KC_DOWN,  KC_RIGHT,_______,   KC_UNDS, KC_NO,                               KC_NO,   KC_EQL,  _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   KC_MINS, KC_NO,                               KC_NO,   KC_PLUS, _______, _______, _______, _______, _______,
                                   _______, _______,   _______, _______,                             _______, _______, _______, _______,
                                                                      _______,               _______,
                                                     _______,                                               _______,
                                            _______,   _______, _______,                             _______, _______, _______,
                                                     _______,                                               _______
    ),
    [_ADJUST] = LAYOUT_all(
        _______, KC_CLCK, KC_NLCK, KC_SLCK, _______,   _______, _______,                             _______, _______, _______, _______, DEBUG,   EEP_RST, QK_BOOT,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______,   _______, _______,                             _______, _______, _______, _______,
                                                                      _______,               _______,
                                                     _______,                                               _______,
                                            _______,   _______, _______,                             _______, _______, _______,
                                                     _______,                                               _______
    )
};
// clang-format on

//----------------------------------------------------------
// Encoder map

// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_LOWER]  = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [_RAISE]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
    [_ADJUST] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),          ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
};
// clang-format on

//----------------------------------------------------------
// Layer naming

const char *current_layer_name(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            return "qwerty";
        case _LOWER:
            return "lower";
        case _RAISE:
            return "raise";
        case _ADJUST:
            return "adjust";
    }
    return "unknown";
}

//----------------------------------------------------------
// Sync

#pragma pack(push)
#pragma pack(1)
typedef struct user_runtime_config {
    uint32_t scan_rate;
} user_runtime_config;
#pragma pack(pop)

user_runtime_config user_state;

void rpc_user_sync_callback(uint8_t m2s_size, const void *m2s_buffer, uint8_t s2m_size, void *s2m_buffer) {
    if (m2s_size == sizeof(user_state)) {
        memcpy(&user_state, m2s_buffer, m2s_size);
    }
}

void keyboard_post_init_user(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(USER_DATA_SYNC, rpc_user_sync_callback);

    // Reset the initial shared data value between master and slave
    memset(&user_state, 0, sizeof(user_state));

    void keyboard_post_init_display(void);
    keyboard_post_init_display();
}

void user_state_update(void) {
    if (is_keyboard_master()) {
        // Keep the scan rate in sync
        user_state.scan_rate = get_matrix_scan_rate();
    }
}

void user_state_sync(void) {
    if (!is_transport_connected()) return;

    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static user_runtime_config last_user_state;
        static uint32_t            last_sync;
        bool                       needs_sync = false;

        // Check if the state values are different
        if (memcmp(&user_state, &last_user_state, sizeof(user_runtime_config))) {
            needs_sync = true;
            memcpy(&last_user_state, &user_state, sizeof(user_runtime_config));
        }

        // Send to slave every 125ms regardless of state change
        if (timer_elapsed32(last_sync) > 125) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(USER_DATA_SYNC, sizeof(user_runtime_config), &user_state)) {
                last_sync = timer_read32();
            } else {
                dprint("Failed to perform rpc call\n");
            }
        }
    }
}

void housekeeping_task_user(void) {
    // Update kb_state so we can send to slave
    user_state_update();

    // Data sync from master to slave
    user_state_sync();
}

//----------------------------------------------------------
// Display theme

#include "theme_djinn_default.inl.c"
