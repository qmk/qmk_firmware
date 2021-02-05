/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef EECONFIG_MAGIC_NUMBER
#    define EECONFIG_MAGIC_NUMBER (uint16_t)0xFEEC
#endif
#define EECONFIG_MAGIC_NUMBER_OFF (uint16_t)0xFFFF

/* EEPROM parameter address */
#define EECONFIG_MAGIC (uint16_t *)0
#define EECONFIG_DEBUG (uint8_t *)2
#define EECONFIG_DEFAULT_LAYER (uint8_t *)3
#define EECONFIG_KEYMAP (uint8_t *)4
#define EECONFIG_MOUSEKEY_ACCEL (uint8_t *)5
#define EECONFIG_BACKLIGHT (uint8_t *)6
#define EECONFIG_AUDIO (uint8_t *)7
#define EECONFIG_RGBLIGHT (uint32_t *)8
#define EECONFIG_UNICODEMODE (uint8_t *)12
#define EECONFIG_STENOMODE (uint8_t *)13
// EEHANDS for two handed boards
#define EECONFIG_HANDEDNESS (uint8_t *)14
#define EECONFIG_KEYBOARD (uint32_t *)15
#define EECONFIG_USER (uint32_t *)19
#define EECONFIG_VELOCIKEY (uint8_t *)23

#define EECONFIG_HAPTIC (uint32_t *)24
#define EECONFIG_RGB_MATRIX (uint32_t *)28
#define EECONFIG_RGB_MATRIX_SPEED (uint8_t *)32
// TODO: Combine these into a single word and single block of EEPROM
#define EECONFIG_KEYMAP_UPPER_BYTE (uint8_t *)33
// Size of EEPROM being used, other code can refer to this for available EEPROM
#define EECONFIG_SIZE 34
/* debug bit */
#define EECONFIG_DEBUG_ENABLE (1 << 0)
#define EECONFIG_DEBUG_MATRIX (1 << 1)
#define EECONFIG_DEBUG_KEYBOARD (1 << 2)
#define EECONFIG_DEBUG_MOUSE (1 << 3)

/* keyconf bit */
#define EECONFIG_KEYMAP_SWAP_CONTROL_CAPSLOCK (1 << 0)
#define EECONFIG_KEYMAP_CAPSLOCK_TO_CONTROL (1 << 1)
#define EECONFIG_KEYMAP_SWAP_LALT_LGUI (1 << 2)
#define EECONFIG_KEYMAP_SWAP_RALT_RGUI (1 << 3)
#define EECONFIG_KEYMAP_NO_GUI (1 << 4)
#define EECONFIG_KEYMAP_SWAP_GRAVE_ESC (1 << 5)
#define EECONFIG_KEYMAP_SWAP_BACKSLASH_BACKSPACE (1 << 6)
#define EECONFIG_KEYMAP_NKRO (1 << 7)

#define EECONFIG_KEYMAP_LOWER_BYTE EECONFIG_KEYMAP

bool eeconfig_is_enabled(void);
bool eeconfig_is_disabled(void);

void eeconfig_init(void);
void eeconfig_init_quantum(void);
void eeconfig_init_kb(void);
void eeconfig_init_user(void);

void eeconfig_enable(void);

void eeconfig_disable(void);

uint8_t eeconfig_read_debug(void);
void    eeconfig_update_debug(uint8_t val);

uint8_t eeconfig_read_default_layer(void);
void    eeconfig_update_default_layer(uint8_t val);

uint16_t eeconfig_read_keymap(void);
void     eeconfig_update_keymap(uint16_t val);

#ifdef BACKLIGHT_ENABLE
uint8_t eeconfig_read_backlight(void);
void    eeconfig_update_backlight(uint8_t val);
#endif

#ifdef AUDIO_ENABLE
uint8_t eeconfig_read_audio(void);
void    eeconfig_update_audio(uint8_t val);
#endif

uint32_t eeconfig_read_kb(void);
void     eeconfig_update_kb(uint32_t val);
uint32_t eeconfig_read_user(void);
void     eeconfig_update_user(uint32_t val);

#ifdef HAPTIC_ENABLE
uint32_t eeconfig_read_haptic(void);
void     eeconfig_update_haptic(uint32_t val);
#endif

bool eeconfig_read_handedness(void);
void eeconfig_update_handedness(bool val);
