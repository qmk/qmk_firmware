// Copyright 2026 Heer (@heer)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "gpio.h"

// ─────────────────────────────────────────────
//  ENCODER SWITCH PINS
//  GP16 = ENC1 button press
//  GP17 = ENC2 button press
// ─────────────────────────────────────────────
#define ENC1_SW_PIN GP16
#define ENC2_SW_PIN GP17

// ─────────────────────────────────────────────
//  LAYER NAMES
// ─────────────────────────────────────────────
enum layers {
    L_BASE  = 0,
    L_MEDIA = 1,
    L_EDIT  = 2,
    L_SYS   = 3,
};

// ─────────────────────────────────────────────
//  KEYMAPS
//
//  Physical layout:
//  [ K1 ][ K2 ][ K3 ][ K4 ]
//  [ K5 ][ K6 ][ K7 ][ K8 ]
//  [ K9 ][K10 ][K11 ][K12 ]
//  [K13 ][K14 ][K15 ][K16 ]
// ─────────────────────────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ── LAYER 0: BASE / NUMPAD ───────────────
    [L_BASE] = LAYOUT_ortho_4x4(
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8,
        KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_BSPC, KC_ENT,  KC_ESC,  KC_TAB
    ),

    // ── LAYER 1: MEDIA ───────────────────────
    [L_MEDIA] = LAYOUT_ortho_4x4(
        KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT,
        KC_VOLD, KC_VOLU, KC_MUTE, _______,
        KC_BRID, KC_BRIU, _______, _______,
        _______, _______, _______, _______
    ),

    // ── LAYER 2: EDITING ─────────────────────
    [L_EDIT] = LAYOUT_ortho_4x4(
        LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),
        LCTL(KC_A), LCTL(KC_S), LCTL(KC_F), LCTL(KC_H),
        LCTL(KC_N), LCTL(KC_W), LCTL(KC_T), LCTL(KC_P),
        KC_DEL,     KC_HOME,    KC_END,      KC_INS
    ),

    // ── LAYER 3: SYSTEM ──────────────────────
    [L_SYS] = LAYOUT_ortho_4x4(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,
        KC_F5,   KC_F6,   KC_F7,   KC_F8,
        KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_PSCR, KC_SCRL, KC_PAUS, KC_NUM
    ),
};

// ─────────────────────────────────────────────
//  ENCODER ROTATION MAP
// ─────────────────────────────────────────────
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [L_BASE]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),       ENCODER_CCW_CW(KC_LEFT,    KC_RGHT) },
    [L_MEDIA] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT),       ENCODER_CCW_CW(KC_BRID,    KC_BRIU) },
    [L_EDIT]  = { ENCODER_CCW_CW(LCTL(KC_Z), LCTL(KC_Y)), ENCODER_CCW_CW(KC_UP,      KC_DOWN) },
    [L_SYS]   = { ENCODER_CCW_CW(KC_F11,  KC_F12),        ENCODER_CCW_CW(KC_PGDN,    KC_PGUP) },
};
#endif

// ─────────────────────────────────────────────
//  ENCODER SWITCH — LAYER CONTROL
//  ENC1 press → cycle next layer (0→1→2→3→0)
//  ENC2 press → jump back to layer 0
// ─────────────────────────────────────────────
static bool enc1_prev = true;
static bool enc2_prev = true;

void keyboard_post_init_user(void) {
    gpio_set_pin_input_high(ENC1_SW_PIN);
    gpio_set_pin_input_high(ENC2_SW_PIN);
}

void matrix_scan_user(void) {
    // ENC1 press — cycle layer forward
    bool enc1_now = gpio_read_pin(ENC1_SW_PIN);
    if (!enc1_now && enc1_prev) {
        uint8_t next = (get_highest_layer(layer_state) + 1) % 4;
        layer_move(next);
    }
    enc1_prev = enc1_now;

    // ENC2 press — return to base layer
    bool enc2_now = gpio_read_pin(ENC2_SW_PIN);
    if (!enc2_now && enc2_prev) {
        layer_move(L_BASE);
    }
    enc2_prev = enc2_now;
}

// ─────────────────────────────────────────────
//  OLED DISPLAY — SH1106
// ─────────────────────────────────────────────
#ifdef OLED_ENABLE

bool oled_task_user(void) {
    oled_set_cursor(0, 0);

    // ── Line 1: board name ──
    oled_write_P(PSTR("   HEER  S1"), false);

    // ── Line 2: divider ──
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("---------------"), false);

    // ── Line 3: current layer name ──
    oled_set_cursor(0, 2);
    oled_write_P(PSTR("LYR: "), false);
    switch (get_highest_layer(layer_state)) {
        case L_BASE:
            oled_write_P(PSTR("BASE  "), false);
            break;
        case L_MEDIA:
            oled_write_P(PSTR("MEDIA "), false);
            break;
        case L_EDIT:
            oled_write_P(PSTR("EDIT  "), false);
            break;
        case L_SYS:
            oled_write_P(PSTR("SYSTEM"), false);
            break;
        default:
            oled_write_P(PSTR("??????"), false);
            break;
    }

    // ── Line 4: layer indicator blocks ──
    oled_set_cursor(0, 3);
    oled_write_P(PSTR("["), false);
    uint8_t current = get_highest_layer(layer_state);
    oled_write_P(current == 0 ? PSTR("*") : PSTR("-"), false);
    oled_write_P(current == 1 ? PSTR("*") : PSTR("-"), false);
    oled_write_P(current == 2 ? PSTR("*") : PSTR("-"), false);
    oled_write_P(current == 3 ? PSTR("*") : PSTR("-"), false);
    oled_write_P(PSTR("]"), false);

    // ── Line 5: WPM ──
    oled_set_cursor(0, 4);
    oled_write_P(PSTR("WPM: "), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);

    return false;
}

#endif // OLED_ENABLE