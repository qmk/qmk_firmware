// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "hid_display.h"
#include "raw_hid.h"
#include "transactions.h"

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

// bottom mods
#define SYM_SPC LT(_SYMBOL, KC_SPC)
#define NUM_TAB LT(_NUMBER, KC_TAB)
#define FUNC_ESC LT(_FUNC, KC_ESC)
#define FUNC_ENT LT(_FUNC, KC_ENT)
#define NAV_BSPC LT(_NAV, KC_BSPC)
#define RALT_DEL LALT_T(KC_DEL)

// game layer mods
#define LALT_Q LALT_T(KC_Q)
#define LSFT_MINS LSFT_T(KC_MINS)
#define LCTL_ESC LCTL_T(KC_ESC)
#define LGUI_QUOT LGUI_T(KC_QUOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY
     *               .---------------------------.                    .---------------------------.
     *               |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |
     * .------+------+------+------+------+------|                    |------+------+------+------+------+------.
     * |  Q   |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   P  |  ;   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  -   |   Z  |   X  |   C  |   V  |   B  |--------.  .--------|   N  |   M  |   ,  |   .  |   /  |  '   |
     * '-----------------------------------------/       /    \       \-----------------------------------------'
     *                         | Esc  | Tab  |  / Space /      \ Enter \  | Bsps | Del  |
     *                         |_FUNC | _NUM | /_SYMBOL/        \ _FUNC \ | _NAV | RAlt |
     *                         `-------------''-------'          '-------''-------------'
     */
    // clang-format off
    [_QWERTY] = LAYOUT(
                            KC_W,    KC_E,    KC_R,    KC_T,                KC_Y,    KC_U,    KC_I,     KC_O,
        KC_Q,     HOME_A,   HOME_S,  HOME_D,  HOME_F,  KC_G,                KC_H,    HOME_J,  HOME_K,   HOME_L,  HOME_SCLN,  KC_P,
        KC_MINS,  KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,                KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,    KC_QUOT,
                                   FUNC_ESC,  NUM_TAB,  SYM_SPC,     FUNC_ENT,  NAV_BSPC,  RALT_DEL
    ),

    [_GAME] = LAYOUT(
                            KC_W,    KC_E,    KC_R,    KC_T,               KC_Y,    KC_U,    KC_I,     KC_O,
        LALT_Q,     KC_A,   KC_S,    KC_D,    KC_F,    KC_G,               KC_H,    KC_J,    KC_K,     KC_L,    KC_SCLN,  KC_P,
        LSFT_MINS,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,               KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  LGUI_QUOT,
                                    LCTL_ESC,  NUM_TAB,  SYM_SPC,    FUNC_ENT,  NAV_BSPC,  RALT_DEL
    ),

    [_NAV] = LAYOUT(
                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,             XXXXXXX,  XXXXXXX,  KC_PGDN,  KC_PGUP,
        XXXXXXX,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX,             XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_PAUS,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,             XXXXXXX,  KC_HOME,  KC_END,   KC_INS,   KC_APP,   XXXXXXX,
                                       FUNC_ESC,   NUM_TAB,   SYM_SPC,     XXXXXXX,  _______,  RALT_DEL
    ),

    [_NUMBER] = LAYOUT(
                            KC_7,    KC_8,    KC_9,    KC_GRV,              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_EQL,   KC_0,     KC_4,    KC_5,    KC_6,    KC_LBRC,             XXXXXXX,  KC_RSFT,  KC_RCTL,  KC_LALT,  KC_RGUI,  XXXXXXX,
        KC_MINS,  KC_BSLS,  KC_1,    KC_2,    KC_3,    KC_RBRC,             XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                     KC_ENT,  _______,  TG(_GAME),       FUNC_ENT,  NAV_BSPC,  RALT_DEL
    ),

    [_SYMBOL] = LAYOUT(
                                        LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_GRV),           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        LSFT(KC_EQL),   LSFT(KC_0),     LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_LBRC),          XXXXXXX,  KC_RSFT,  KC_RCTL,  KC_LALT,  KC_RGUI,  XXXXXXX,
        LSFT(KC_MINS),  LSFT(KC_BSLS),  LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_RBRC),          XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                                MO(_SYS),  KC_BSPC, _______,     FUNC_ENT,  NAV_BSPC,  RALT_DEL
    ),

    [_FUNC] = LAYOUT(
                            KC_F7,   KC_F8,   KC_F9,   KC_CAPS,            XXXXXXX,  KC_PSCR,  KC_SCRL,  KC_NUM,
        KC_F12,   KC_F11,   KC_F4,   KC_F5,   KC_F6,   KC_F12,             XXXXXXX,  KC_RSFT,  KC_RCTL,  KC_LALT,  KC_RGUI,  XXXXXXX,
        XXXXXXX,  KC_F10,   KC_F1,   KC_F2,   KC_F3,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                         _______, KC_MNXT, KC_MPLY,     _______, XXXXXXX,  MO(_SYS)
    ),

    [_SYS] = LAYOUT(
                            BL_DOWN,  BL_UP,    BL_TOGG,  XXXXXXX,            XXXXXXX,  RM_TOGG,  RM_NEXT,  RM_PREV,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  RM_HUEU,  RM_SATU,  RM_VALU,  RM_SPDU,  RGB_M_P,
        EH_LEFT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  EH_RGHT,            EH_RGHT,  RM_HUED,  RM_SATD,  RM_VALD,  RM_SPDD,  EH_LEFT,
                                            _______, QK_BOOT, _______,     _______, QK_BOOT, _______
    )
    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    dprintf("process_record_user %u %s %s %d\n", keycode, record->event.pressed ? "pressed" : "depressed", record->tap.interrupted ? "interrupted" : "not interrupted", record->tap.count);

    if (record->event.pressed) {
        uint8_t data[32];
        data[0] = 0;

        switch (keycode) {
            // send hid commands
            case KC_VOLU:
            case KC_VOLD:
                data[0] = _VOLUME;
                break;
        }

        if (data[0]) {
            dprintf("raw_hid_send %u\n", data[0]);
            raw_hid_send(data, sizeof(data));
        }
    }

    return true;
}

/* Caps Word processing */
#ifdef CAPS_WORD_ENABLE
void caps_word_set_user(bool active) {
    if (is_display_enabled()) {
        display_process_caps_word(active);
    } else if (is_keyboard_master() && !is_keyboard_left()) {
        dprintf("RPC_ID_USER_CAPS_WORD_SYNC: %s\n", active ? "active" : "inactive");
        transaction_rpc_send(RPC_ID_USER_CAPS_WORD_SYNC, 1, &active);
    }
}
#endif

/* Active Layer processing */
layer_state_t layer_state_set_user(layer_state_t state) {
    if (is_display_enabled()) {
        display_process_layer_state(get_highest_layer(state));
    } else if (is_keyboard_master() && !is_keyboard_left()) {
        uint8_t layer = get_highest_layer(state);
        dprintf("RPC_ID_USER_LAYER_SYNC: %u\n", layer);
        transaction_rpc_send(RPC_ID_USER_LAYER_SYNC, 1, &layer);
    }

    return state;
}

/* Raw HID processing*/
void raw_hid_receive(uint8_t *data, uint8_t length) {
    dprintf("raw_hid_receive - received %u bytes \n", length);

    if (is_display_enabled()) {
        display_process_raw_hid_data(data, length);
    } else if (is_keyboard_master() && !is_keyboard_left()) {
        dprint("RPC_ID_USER_HID_SYNC \n");
        transaction_rpc_send(RPC_ID_USER_HID_SYNC, length, data);
    }
}

void hid_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (is_display_enabled()) {
        display_process_raw_hid_data((uint8_t *)initiator2target_buffer, initiator2target_buffer_size);
    }
}

void layer_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (is_display_enabled()) {
        display_process_layer_state(*(uint8_t *)initiator2target_buffer);
    }
}

void caps_word_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (is_display_enabled()) {
        display_process_caps_word(*(bool *)initiator2target_buffer);
    }
}

void keyboard_post_init_user() {
    // sync received hid data
    transaction_register_rpc(RPC_ID_USER_HID_SYNC, hid_sync);
    // sync highest layer (a bit more performant than standard SPLIT_LAYER_STATE_ENABLE)
    transaction_register_rpc(RPC_ID_USER_LAYER_SYNC, layer_sync);
    // sync caps word state
    transaction_register_rpc(RPC_ID_USER_CAPS_WORD_SYNC, caps_word_sync);
}
