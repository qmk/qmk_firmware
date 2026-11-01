// Copyright 2026 Andreas Hirschauer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Repeat held lighting controls and batch RP2040 flash writes until idle.
#define LIGHT_REPEAT_DELAY_MS 300
#define LIGHT_REPEAT_INTERVAL_MS 40
#define LIGHT_SAVE_DELAY_MS 3000

static uint16_t light_repeat_keycode;
static uint32_t light_repeat_at;
static bool     light_save_pending;
static uint32_t light_save_at;

static bool light_repeatable(uint16_t keycode) {
    switch (keycode) {
        case RM_VALU:
        case RM_VALD:
        case RM_HUEU:
        case RM_HUED:
        case RM_SATU:
        case RM_SATD:
        case RM_SPDU:
        case RM_SPDD:
            return true;
        default:
            return false;
    }
}

static void light_step(uint16_t keycode) {
    const bool shifted = get_mods() & MOD_MASK_SHIFT;
    switch (keycode) {
        case RM_ON:
            rgb_matrix_enable_noeeprom();
            break;
        case RM_OFF:
            rgb_matrix_disable_noeeprom();
            break;
        case RM_TOGG:
            rgb_matrix_toggle_noeeprom();
            break;
        case RM_NEXT:
            shifted ? rgb_matrix_step_reverse_noeeprom() : rgb_matrix_step_noeeprom();
            break;
        case RM_PREV:
            shifted ? rgb_matrix_step_noeeprom() : rgb_matrix_step_reverse_noeeprom();
            break;
        case RM_FLGN:
            rgb_matrix_flags_step_noeeprom();
            break;
        case RM_FLGP:
            rgb_matrix_flags_step_reverse_noeeprom();
            break;
        case RM_VALU:
            rgb_matrix_increase_val_noeeprom();
            break;
        case RM_VALD:
            rgb_matrix_decrease_val_noeeprom();
            break;
        case RM_HUEU:
            rgb_matrix_increase_hue_noeeprom();
            break;
        case RM_HUED:
            rgb_matrix_decrease_hue_noeeprom();
            break;
        case RM_SATU:
            rgb_matrix_increase_sat_noeeprom();
            break;
        case RM_SATD:
            rgb_matrix_decrease_sat_noeeprom();
            break;
        case RM_SPDU:
            rgb_matrix_increase_speed_noeeprom();
            break;
        case RM_SPDD:
            rgb_matrix_decrease_speed_noeeprom();
            break;
        default:
            return;
    }
    light_save_pending = true;
    light_save_at      = timer_read32() + LIGHT_SAVE_DELAY_MS;
}

static void process_light_keycode(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        light_step(keycode);
        light_repeat_keycode = light_repeatable(keycode) ? keycode : KC_NO;
        light_repeat_at      = timer_read32() + LIGHT_REPEAT_DELAY_MS;
    } else if (keycode == light_repeat_keycode) {
        light_repeat_keycode = KC_NO;
    }
}

// Store pending lighting changes before a reset or bootloader jump.
static void light_save_now(void) {
    if (light_save_pending) {
        light_save_pending = false;
        eeconfig_force_flush_rgb_matrix();
    }
}

static void light_task(void) {
    const uint32_t now = timer_read32();
    if (light_repeat_keycode != KC_NO && timer_expired32(now, light_repeat_at)) {
        light_step(light_repeat_keycode);
        light_repeat_at = now + LIGHT_REPEAT_INTERVAL_MS;
    }
    if (light_save_pending && timer_expired32(now, light_save_at)) {
        light_save_now();
    }
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
    light_save_now();
    return true;
}

void keyboard_post_init_kb(void) {
    reform4_oled_show(R4_OLED_SPLASH, 1500);
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    light_task();
    housekeeping_task_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case RGB_MATRIX_KEYCODE_RANGE:
            process_light_keycode(keycode, record);
            if (record->event.pressed && !layer_state_is(R4_LAYER_CIRCLE)) {
                reform4_oled_show(R4_OLED_RGB, 2000);
            }
            return false;
    }

    return true;
}
