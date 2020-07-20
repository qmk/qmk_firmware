#ifndef USERSPACE
#define USERSPACE

#pragma once
#include QMK_KEYBOARD_H

#include <stdbool.h>
#include "version.h"
#include "wrappers.h"
#include "process_records.h"

#ifdef OLED_DRIVER_ENABLE
#include "oled_utils.h"
#endif

#ifdef ENCODER_ENABLE
#include "encoder_utils.h"
#endif

enum userspace_layers {
    _QWERTY = 0,
    _COLEMAK,
    _DVORAK,
    _WORKMAN,
    _NORMAN,
    _GAME,
    _GAMENUM,
    _LOWER,
    _RAISE,
    _ADJUST,
};

void keyboard_pre_init_keymap(void);
void matrix_init_keymap(void);
void keyboard_post_init_keymap(void);
void matrix_scan_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
bool led_update_keymap(led_t led_state);

#endif
