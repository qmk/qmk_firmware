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

#ifndef EECONFIG_H
#define EECONFIG_H

#include <stdint.h>
#include <stdbool.h>


#define EECONFIG_MAGIC_NUMBER                       (uint16_t)0xFEED
#define EECONFIG_MAGIC_NUMBER_OFF                   (uint16_t)0xFFFF

/* EEPROM parameter address */
#define EECONFIG_MAGIC                              (uint16_t *)0
#define EECONFIG_DEBUG                               (uint8_t *)2
#define EECONFIG_DEFAULT_LAYER                       (uint8_t *)3
#define EECONFIG_KEYMAP                              (uint8_t *)4
#define EECONFIG_MOUSEKEY_ACCEL                      (uint8_t *)5
#define EECONFIG_BACKLIGHT                           (uint8_t *)6
#define EECONFIG_AUDIO                               (uint8_t *)7
#define EECONFIG_RGBLIGHT                           (uint32_t *)8
#define EECONFIG_UNICODEMODE                        (uint8_t *)12
#define EECONFIG_STENOMODE                          (uint8_t *)13
// EEHANDS for two handed boards
#define EECONFIG_HANDEDNESS         			        	(uint8_t *)14
#define EECONFIG_KEYBOARD                          (uint32_t *)15
#define EECONFIG_USER                              (uint32_t *)19
/* Note that Via Support uses address 32 and up for dynamic keymap support */

// VIA Support EEPROM usage

// TODO: refactor with new user EEPROM code (coming soon)
#define EEPROM_MAGIC 0x451F
#define EEPROM_MAGIC_ADDR 32
// Bump this every time we change what we store
// This will automatically reset the EEPROM with defaults
// and avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x08
#define EEPROM_VERSION_ADDR 34

// Dynamic keymap starts after EEPROM version
#define DYNAMIC_KEYMAP_EEPROM_ADDR 35
// Dynamic macro starts after dynamic keymaps (35+(4*10*6*2)) = (35+480)
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR 515
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 509    // 1024-DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR
#define DYNAMIC_KEYMAP_MACRO_COUNT 16

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* debug bit */
#define EECONFIG_DEBUG_ENABLE                       (1<<0)
#define EECONFIG_DEBUG_MATRIX                       (1<<1)
#define EECONFIG_DEBUG_KEYBOARD                     (1<<2)
#define EECONFIG_DEBUG_MOUSE                        (1<<3)

/* keyconf bit */
#define EECONFIG_KEYMAP_SWAP_CONTROL_CAPSLOCK       (1<<0)
#define EECONFIG_KEYMAP_CAPSLOCK_TO_CONTROL         (1<<1)
#define EECONFIG_KEYMAP_SWAP_LALT_LGUI              (1<<2)
#define EECONFIG_KEYMAP_SWAP_RALT_RGUI              (1<<3)
#define EECONFIG_KEYMAP_NO_GUI                      (1<<4)
#define EECONFIG_KEYMAP_SWAP_GRAVE_ESC              (1<<5)
#define EECONFIG_KEYMAP_SWAP_BACKSLASH_BACKSPACE    (1<<6)
#define EECONFIG_KEYMAP_NKRO                        (1<<7)


bool eeconfig_is_enabled(void);
bool eeconfig_is_disabled(void);

void eeconfig_init(void);
void eeconfig_init_quantum(void);
void eeconfig_init_kb(void);
void eeconfig_init_user(void);

void eeconfig_enable(void);

void eeconfig_disable(void);

uint8_t eeconfig_read_debug(void);
void eeconfig_update_debug(uint8_t val);

uint8_t eeconfig_read_default_layer(void);
void eeconfig_update_default_layer(uint8_t val);

uint8_t eeconfig_read_keymap(void);
void eeconfig_update_keymap(uint8_t val);

#ifdef BACKLIGHT_ENABLE
uint8_t eeconfig_read_backlight(void);
void eeconfig_update_backlight(uint8_t val);
#endif

#ifdef AUDIO_ENABLE
uint8_t eeconfig_read_audio(void);
void eeconfig_update_audio(uint8_t val);
#endif

uint32_t eeconfig_read_kb(void);
void eeconfig_update_kb(uint32_t val);
uint32_t eeconfig_read_user(void);
void eeconfig_update_user(uint32_t val);

bool eeprom_is_valid(void);
void eeprom_set_valid(bool valid);
void eeprom_reset(void);

#endif
