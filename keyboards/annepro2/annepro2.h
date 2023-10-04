/*
 * Copyright (c) 2018 Yaotian Feng
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "quantum.h"
#include <stdint.h>
#include "ap2_led.h"

typedef struct __attribute__((__packed__)) {
    uint8_t _dummy[10];
    bool    caps_lock;
} ble_capslock_t;
extern ble_capslock_t ble_capslock;

enum AP2KeyCodes {
    KC_AP2_BT1 = QK_KB_0,
    KC_AP2_BT2,
    KC_AP2_BT3,
    KC_AP2_BT4,
    KC_AP2_BT_UNPAIR,
    KC_AP2_USB,
    KC_AP_LED_ON,
    KC_AP_LED_OFF,
    KC_AP_LED_TOG,
    KC_AP_LED_NEXT_PROFILE,
    KC_AP_LED_PREV_PROFILE,
    KC_AP_LED_NEXT_INTENSITY,
    KC_AP_LED_SPEED,
    KC_AP_RGB_VAI,
    KC_AP_RGB_VAD,
    KC_AP_RGB_TOG,
    KC_AP_RGB_MOD,
};
