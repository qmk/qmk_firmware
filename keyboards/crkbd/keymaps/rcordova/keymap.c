/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
*/

#include QMK_KEYBOARD_H

// ──────────────────────────────────────────────────────────────
// Keymaps
// ──────────────────────────────────────────────────────────────

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        QK_GESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLS,
        KC_TAB, LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F),   KC_G,        KC_H, RCTL_T(KC_J), RSFT_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
        KC_BSPC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_DEL,
                                            KC_DEL,  MO(1),  LSFT_T(KC_SPC),  RCTL_T(KC_ENT),  MO(2),  KC_DEL
    ),

    [1] = LAYOUT_split_3x6_3(
        TO(0),   _______, KC_EXLM,  KC_AT, KC_HASH, KC_VOLU,                      KC_MNXT,   KC_7,   KC_8,   KC_9, KC_PLUS, KC_MINS,
        _______, _______, KC_DLR, KC_PERC, KC_CIRC, KC_VOLD,                      KC_MPRV,   KC_4,   KC_5,   KC_6, KC_ASTR, KC_SLSH,
        _______, _______, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                      KC_0,      KC_1,   KC_2,   KC_3, KC_PLUS, _______,
                                          KC_LBRC, _______, _______,              KC_MPLY, _______, KC_RBRC
    ),

    [2] = LAYOUT_split_3x6_3(
        TO(0),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END, KC_PGDN, _______,
        _______,  KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______,  KC_F11,  KC_F12,                      _______, LCTL(KC_LEFT), _______, LCTL(KC_RGHT), _______, _______,
                                          KC_LCBR, _______, LSFT_T(KC_SPC),       _______, _______, KC_RCBR
    ),

    [3] = LAYOUT_split_3x6_3(
        TO(0),   _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, QK_BOOT,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RM_SPDU, _______,                      _______, _______, _______, _______, _______, _______,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RM_SPDD, _______,                      _______, _______, _______, _______, _______, _______,
                                          _______, _______, _______,              _______, _______, _______
    ),
};

void keyboard_post_init_user(void) {
    rgb_matrix_enable();  // force on after boot
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, 1, 2, 3);
}

// ──────────────────────────────────────────────────────────────
// OLED (Right: logo + rain + TV glitch, Left: layer + WPM)
// Master (LEFT) controls sleep/wake; slave follows via SPLIT_OLED_ENABLE.
// ──────────────────────────────────────────────────────────────

#ifdef OLED_ENABLE

#include "timer.h"
#include "wpm.h"
#include <stdio.h>
#include <string.h>

#define OLED_W      128
#define OLED_H       32
#define OLED_BYTES  (OLED_W * OLED_H / 8)

// Rain
#define NUM_DROPS   14
#define FRAME_MS    60

// TV glitch burst (logo-only)
#define FX_PERIOD_MS     3000
#define FX_DURATION_MS   1500
#define FX_MAX_PASSES       4

// Master-controlled OLED sleep timeout (ms)
#define OLED_IDLE_TIMEOUT_MS 60000

static uint32_t oled_last_activity_ms = 0;

// Your logo (128x32, vertical 1-bit, SSD1306 raw)
static const uint8_t PROGMEM raw_logo[] = {
	// 'Brand of the sacrificefixed, 128x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 
	0x30, 0x18, 0x1c, 0x0e, 0x1e, 0x3c, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0x7c, 0x3c, 0x0e, 0x0e, 0x08, 0x78, 0xf0, 0xc0, 
	0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x90, 0xa2, 0xc1, 0xc0, 0xc0, 0x80, 
	0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc3, 0xc3, 0x8f, 0x0e, 0xbc, 0xf8, 0xf0, 0xf0, 
	0xf8, 0xfc, 0xde, 0xcf, 0xc7, 0x83, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0xc1, 
	0xc2, 0xc3, 0xcf, 0xdc, 0xdc, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x41, 0x80, 0x00, 0x00, 
	0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0xc1, 0xc1, 0xc1, 0xd1, 0x3c, 0x1f, 0x0f, 0x07, 0x01, 0x01, 
	0x03, 0x0f, 0x1f, 0x05, 0x69, 0x31, 0x60, 0x81, 0x81, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0xc1, 
	0xe0, 0x71, 0x79, 0x3d, 0x1f, 0x0f, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
	0x06, 0x04, 0x0c, 0x08, 0x1e, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x2c, 0x3c, 0x1e, 0x0f, 0x07, 0x03, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// ──────────────── animation state ────────────────

typedef struct {
    uint8_t x;     // 0..127
    int16_t y;     // can be negative (above screen)
    uint8_t speed; // 1..3
    uint8_t len;   // 2..10
} drop_t;

static drop_t drops[NUM_DROPS];
static bool   drops_inited = false;

static uint32_t rng_state = 0xA5A5A5A5u;
static uint8_t  frame[OLED_BYTES];

static uint32_t xorshift32(void) {
    uint32_t x = rng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng_state = x;
    return x;
}

static uint8_t rand_u8(uint8_t max_exclusive) {
    return (uint8_t)(xorshift32() % max_exclusive);
}

static inline uint8_t rand8(void) {
    return (uint8_t)xorshift32();
}

static inline void set_px(uint8_t *buf, uint8_t x, int16_t y) {
    if (y < 0 || y >= OLED_H) return;
    uint16_t idx = (uint16_t)(y >> 3) * OLED_W + x;
    buf[idx] |= (uint8_t)(1u << (y & 7));
}

static void spawn_drop(drop_t *d) {
    d->x     = rand_u8(OLED_W);
    d->y     = -(int16_t)rand_u8(OLED_H);
    d->speed = 1 + rand_u8(3);
    d->len   = 2 + rand_u8(9);
}

static void init_drops(void) {
    rng_state ^= timer_read32();
    for (uint8_t i = 0; i < NUM_DROPS; i++) {
        spawn_drop(&drops[i]);
        drops[i].y = -(int16_t)rand_u8(OLED_H * 2);
    }
    drops_inited = true;
}

static void update_drops(void) {
    for (uint8_t i = 0; i < NUM_DROPS; i++) {
        drops[i].y += drops[i].speed;
        if (drops[i].y - (int16_t)drops[i].len > OLED_H + 2) {
            spawn_drop(&drops[i]);
        }
    }
}

static void draw_drops(uint8_t *buf) {
    for (uint8_t i = 0; i < NUM_DROPS; i++) {
        for (uint8_t t = 0; t < drops[i].len; t++) {
            set_px(buf, drops[i].x, drops[i].y - (int16_t)t);
        }

        if (drops[i].y >= OLED_H - 1 && (rand_u8(5) == 0)) {
            uint8_t x = drops[i].x;
            set_px(buf, x, OLED_H - 1);
            if (x > 0)        set_px(buf, x - 1, OLED_H - 1);
            if (x < OLED_W-1) set_px(buf, x + 1, OLED_H - 1);
        }
    }
}

static void apply_logo_tv_fx(uint8_t *buf) {
    uint32_t now   = timer_read32();
    uint32_t phase = now % FX_PERIOD_MS;

    if (phase >= FX_DURATION_MS) return;

    uint16_t half = FX_DURATION_MS / 2;
    uint8_t amt = (phase < half)
        ? (uint8_t)((phase * FX_MAX_PASSES) / half)
        : (uint8_t)(((FX_DURATION_MS - phase) * FX_MAX_PASSES) / half);

    for (uint16_t i = 0; i < OLED_BYTES; i++) {
        uint8_t orig = buf[i];
        if (!orig) continue;

        uint8_t out = orig;

        for (uint8_t p = 0; p < amt; p++) {
            out &= rand8();
        }

        if (amt) {
            uint8_t area  = orig | (orig << 1) | (orig >> 1);
            uint8_t noise = rand8();

            out |= (noise & area);
            if ((rand8() & 0x03) == 0) {
                out ^= (rand8() & area);
            }
        }

        buf[i] = out;
    }

    if (amt >= 2 && (rand8() < 80)) {
        uint8_t  page  = rand_u8(OLED_H / 8);
        uint16_t base  = (uint16_t)page * OLED_W;
        int8_t   shift = (rand8() & 1) ? 1 : -1;

        if (shift > 0) {
            for (int16_t x = OLED_W - 1; x > 0; x--) {
                buf[base + x] = buf[base + x - 1];
            }
            buf[base] = 0;
        } else {
            for (uint16_t x = 0; x < OLED_W - 1; x++) {
                buf[base + x] = buf[base + x + 1];
            }
            buf[base + (OLED_W - 1)] = 0;
        }
    }
}

static void oled_render_logo_rain(void) {
    static uint32_t last_step_ms = 0;
    static uint32_t last_call_ms = 0;

    uint32_t now = timer_read32();

    // If we were "paused" for a while (e.g., OLED slept), restart the animation cleanly.
    if (last_call_ms && timer_elapsed32(last_call_ms) > 500) {
        drops_inited = false;
    }
    last_call_ms = now;

    if (!drops_inited) {
        init_drops();
        last_step_ms = now;
    }

    if (timer_elapsed32(last_step_ms) > FRAME_MS) {
        last_step_ms = now;
        update_drops();
    }

    memcpy_P(frame, raw_logo, OLED_BYTES);
    apply_logo_tv_fx(frame);
    draw_drops(frame);

    oled_write_raw((const char *)frame, OLED_BYTES);
}

// Left side content
static void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0: oled_write_ln_P(PSTR("Default"), false); break;
        case 1: oled_write_ln_P(PSTR("Lower"), false);   break;
        case 2: oled_write_ln_P(PSTR("Raise"), false);   break;
        case 3: oled_write_ln_P(PSTR("Adjust"), false);  break;
        default: oled_write_ln_P(PSTR("Other"), false);  break;
    }
}

static void oled_render_wpm(void) {
    char wpm_str[16];
    snprintf(wpm_str, sizeof(wpm_str), "WPM: %3d\n", get_current_wpm());
    oled_write(wpm_str, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left()) {
        return OLED_ROTATION_180;
    }
    return OLED_ROTATION_0;
}

bool oled_task_user(void) {
    // NOTE: left half is your master (USB-C), right is slave.

    static bool oled_sleeping = false;

    // Init activity timestamp on first run
    if (oled_last_activity_ms == 0) {
        oled_last_activity_ms = timer_read32();
    }

    // If we thought we were sleeping but the OLED is ON (master likely woke us via SPLIT_OLED_ENABLE),
    // immediately reset animation state so it doesn't stay static.
    if (oled_sleeping && is_oled_on()) {
        oled_sleeping         = false;
        oled_last_activity_ms = timer_read32();
        oled_clear();
        drops_inited = false;
    }

    // MASTER (left) decides when to sleep/wake
    if (is_keyboard_left()) {
        if (timer_elapsed32(oled_last_activity_ms) > OLED_IDLE_TIMEOUT_MS) {
            if (!oled_sleeping) {
                oled_off();
                oled_sleeping = true;
            }
            return false;
        }

        if (oled_sleeping) {
            oled_on();
            oled_clear();
            oled_sleeping = false;
        }
    }

    // If the OLED is currently off on this half, don't try to render.
    if (!is_oled_on()) {
        return false;
    }

    if (is_keyboard_left()) {
        oled_render_layer_state();
        oled_render_wpm();
    } else {
        oled_render_logo_rain();
    }

    return false;
}

// Update master activity timer on ANY keypress (left or right keys still land here on the master)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_last_activity_ms = timer_read32();

        // If the master had turned the OLED off, wake it immediately.
        // With SPLIT_OLED_ENABLE, the slave will follow.
        if (is_keyboard_left() && !is_oled_on()) {
            oled_on();
        }
    }
    return true;
}

#endif // OLED_ENABLE
