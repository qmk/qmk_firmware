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
#include <stddef.h> // offsetof
#include "eeprom.h"
#include "util.h"
#include "action_layer.h" // layer_state_t

#ifndef EECONFIG_MAGIC_NUMBER
#    define EECONFIG_MAGIC_NUMBER (uint16_t)0xFEE5 // When changing, decrement this value to avoid future re-init issues
#endif
#define EECONFIG_MAGIC_NUMBER_OFF (uint16_t)0xFFFF

// Dummy struct only used to calculate offsets
typedef struct PACKED {
    uint16_t magic;
    uint8_t  debug;
    uint8_t  default_layer;
    uint16_t keymap;
    uint8_t  backlight;
    uint8_t  audio;
    uint32_t rgblight;
    uint8_t  unicode;
    uint8_t  steno;
    uint8_t  handedness;
    uint32_t keyboard;
    uint32_t user;
    union { // Mutually exclusive
        uint32_t led_matrix;
        uint64_t rgb_matrix;
    };
    uint32_t haptic;
    uint8_t  rgblight_ext;
} eeprom_core_t;

/* EEPROM parameter address */
#define EECONFIG_MAGIC (uint16_t *)(offsetof(eeprom_core_t, magic))
#define EECONFIG_DEBUG (uint8_t *)(offsetof(eeprom_core_t, debug))
#define EECONFIG_DEFAULT_LAYER (uint8_t *)(offsetof(eeprom_core_t, default_layer))
#define EECONFIG_KEYMAP (uint16_t *)(offsetof(eeprom_core_t, keymap))
#define EECONFIG_BACKLIGHT (uint8_t *)(offsetof(eeprom_core_t, backlight))
#define EECONFIG_AUDIO (uint8_t *)(offsetof(eeprom_core_t, audio))
#define EECONFIG_RGBLIGHT (uint32_t *)(offsetof(eeprom_core_t, rgblight))
#define EECONFIG_UNICODEMODE (uint8_t *)(offsetof(eeprom_core_t, unicode))
#define EECONFIG_STENOMODE (uint8_t *)(offsetof(eeprom_core_t, steno))
#define EECONFIG_HANDEDNESS (uint8_t *)(offsetof(eeprom_core_t, handedness))
#define EECONFIG_KEYBOARD (uint32_t *)(offsetof(eeprom_core_t, keyboard))
#define EECONFIG_USER (uint32_t *)(offsetof(eeprom_core_t, user))
#define EECONFIG_LED_MATRIX (uint32_t *)(offsetof(eeprom_core_t, led_matrix))
#define EECONFIG_RGB_MATRIX (uint64_t *)(offsetof(eeprom_core_t, rgb_matrix))
#define EECONFIG_HAPTIC (uint32_t *)(offsetof(eeprom_core_t, haptic))
#define EECONFIG_RGBLIGHT_EXTENDED (uint8_t *)(offsetof(eeprom_core_t, rgblight_ext))

// Size of EEPROM being used for core data storage
#define EECONFIG_BASE_SIZE ((uint8_t)sizeof(eeprom_core_t))

// Size of EEPROM dedicated to keyboard- and user-specific data
#ifndef EECONFIG_KB_DATA_SIZE
#    define EECONFIG_KB_DATA_SIZE 0
#endif
#ifndef EECONFIG_KB_DATA_VERSION
#    define EECONFIG_KB_DATA_VERSION (EECONFIG_KB_DATA_SIZE)
#endif
#ifndef EECONFIG_USER_DATA_SIZE
#    define EECONFIG_USER_DATA_SIZE 0
#endif
#ifndef EECONFIG_USER_DATA_VERSION
#    define EECONFIG_USER_DATA_VERSION (EECONFIG_USER_DATA_SIZE)
#endif

#define EECONFIG_KB_DATABLOCK ((uint8_t *)(EECONFIG_BASE_SIZE))
#define EECONFIG_USER_DATABLOCK ((uint8_t *)((EECONFIG_BASE_SIZE) + (EECONFIG_KB_DATA_SIZE)))

// Size of EEPROM being used, other code can refer to this for available EEPROM
#define EECONFIG_SIZE ((EECONFIG_BASE_SIZE) + (EECONFIG_KB_DATA_SIZE) + (EECONFIG_USER_DATA_SIZE))

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

layer_state_t eeconfig_read_default_layer(void);
void          eeconfig_update_default_layer(layer_state_t val);

uint16_t eeconfig_read_keymap(void);
void     eeconfig_update_keymap(uint16_t val);

#ifdef AUDIO_ENABLE
uint8_t eeconfig_read_audio(void);
void    eeconfig_update_audio(uint8_t val);
#endif

#if (EECONFIG_KB_DATA_SIZE) == 0
uint32_t eeconfig_read_kb(void);
void     eeconfig_update_kb(uint32_t val);
#endif // (EECONFIG_KB_DATA_SIZE) == 0

#if (EECONFIG_USER_DATA_SIZE) == 0
uint32_t eeconfig_read_user(void);
void     eeconfig_update_user(uint32_t val);
#endif // (EECONFIG_USER_DATA_SIZE) == 0

#ifdef HAPTIC_ENABLE
uint32_t eeconfig_read_haptic(void);
void     eeconfig_update_haptic(uint32_t val);
#endif

bool eeconfig_read_handedness(void);
void eeconfig_update_handedness(bool val);

#if (EECONFIG_KB_DATA_SIZE) > 0
bool eeconfig_is_kb_datablock_valid(void);
void eeconfig_read_kb_datablock(void *data);
void eeconfig_update_kb_datablock(const void *data);
void eeconfig_init_kb_datablock(void);
#endif // (EECONFIG_KB_DATA_SIZE) > 0

#if (EECONFIG_USER_DATA_SIZE) > 0
bool eeconfig_is_user_datablock_valid(void);
void eeconfig_read_user_datablock(void *data);
void eeconfig_update_user_datablock(const void *data);
void eeconfig_init_user_datablock(void);
#endif // (EECONFIG_USER_DATA_SIZE) > 0

// Any "checked" debounce variant used requires implementation of:
//    -- bool eeconfig_check_valid_##name(void)
//    -- void eeconfig_post_flush_##name(void)
#define EECONFIG_DEBOUNCE_HELPER_CHECKED(name, offset, config)          \
    static uint8_t dirty_##name = false;                                \
                                                                        \
    bool eeconfig_check_valid_##name(void);                             \
    void eeconfig_post_flush_##name(void);                              \
                                                                        \
    static inline void eeconfig_init_##name(void) {                     \
        dirty_##name = true;                                            \
        if (eeconfig_check_valid_##name()) {                            \
            eeprom_read_block(&config, offset, sizeof(config));         \
            dirty_##name = false;                                       \
        }                                                               \
    }                                                                   \
    static inline void eeconfig_flush_##name(bool force) {              \
        if (force || dirty_##name) {                                    \
            eeprom_update_block(&config, offset, sizeof(config));       \
            eeconfig_post_flush_##name();                               \
            dirty_##name = false;                                       \
        }                                                               \
    }                                                                   \
    static inline void eeconfig_flush_##name##_task(uint16_t timeout) { \
        static uint16_t flush_timer = 0;                                \
        if (timer_elapsed(flush_timer) > timeout) {                     \
            eeconfig_flush_##name(false);                               \
            flush_timer = timer_read();                                 \
        }                                                               \
    }                                                                   \
    static inline void eeconfig_flag_##name(bool v) {                   \
        dirty_##name |= v;                                              \
    }                                                                   \
    static inline void eeconfig_write_##name(typeof(config) *conf) {    \
        if (memcmp(&config, conf, sizeof(config)) != 0) {               \
            memcpy(&config, conf, sizeof(config));                      \
            eeconfig_flag_##name(true);                                 \
        }                                                               \
    }

#define EECONFIG_DEBOUNCE_HELPER(name, offset, config)     \
    EECONFIG_DEBOUNCE_HELPER_CHECKED(name, offset, config) \
                                                           \
    bool eeconfig_check_valid_##name(void) {               \
        return true;                                       \
    }                                                      \
    void eeconfig_post_flush_##name(void) {}
