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

#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix_types.h"
#endif

#ifdef LED_MATRIX_ENABLE
#    include "led_matrix_types.h"
#endif

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif

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

uint8_t eeconfig_read_default_layer(void);
void    eeconfig_update_default_layer(uint8_t val);

uint16_t eeconfig_read_keymap(void);
void     eeconfig_update_keymap(uint16_t val);

#ifdef AUDIO_ENABLE
uint8_t eeconfig_read_audio(void);
void    eeconfig_update_audio(uint8_t val);
#endif // AUDIO_ENABLE

#ifdef UNICODE_COMMON_ENABLE
uint8_t eeconfig_read_unicode_mode(void);
void    eeconfig_update_unicode_mode(uint8_t val);
#endif // UNICODE_COMMON_ENABLE

#ifdef BACKLIGHT_ENABLE
uint8_t eeconfig_read_backlight(void);
void    eeconfig_update_backlight(uint8_t val);
#endif // BACKLIGHT_ENABLE

#ifdef STENO_ENABLE
uint8_t eeconfig_read_steno_mode(void);
void    eeconfig_update_steno_mode(uint8_t val);
#endif // STENO_ENABLE

#ifdef RGB_MATRIX_ENABLE
void eeconfig_read_rgb_matrix(rgb_config_t *rgb_matrix_config);
void eeconfig_update_rgb_matrix(const rgb_config_t *rgb_matrix_config);
#endif // RGB_MATRIX_ENABLE

#ifdef LED_MATRIX_ENABLE
void eeconfig_read_led_matrix(led_eeconfig_t *led_matrix_config);
void eeconfig_update_led_matrix(const led_eeconfig_t *led_matrix_config);
#endif // LED_MATRIX_ENABLE

#ifdef RGBLIGHT_ENABLE
void eeconfig_read_rgblight(rgblight_config_t *rgblight_config);
void eeconfig_update_rgblight(const rgblight_config_t *rgblight_config);
#endif // RGBLIGHT_ENABLE

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
bool     eeconfig_is_kb_datablock_valid(void);
uint32_t eeconfig_read_kb_datablock(void *data, uint32_t offset, uint32_t length);
uint32_t eeconfig_update_kb_datablock(const void *data, uint32_t offset, uint32_t length);
void     eeconfig_init_kb_datablock(void);
#    define eeconfig_read_kb_datablock_field(__object, __field) eeconfig_read_kb_datablock(&(__object.__field), offsetof(__object, __field), sizeof(__object.__field))
#    define eeconfig_update_kb_datablock_field(__object, __field) eeconfig_update_kb_datablock(&(__object.__field), offsetof(__object, __field), sizeof(__object.__field))
#endif // (EECONFIG_KB_DATA_SIZE) > 0

#if (EECONFIG_USER_DATA_SIZE) > 0
bool     eeconfig_is_user_datablock_valid(void);
uint32_t eeconfig_read_user_datablock(void *data, uint32_t offset, uint32_t length);
uint32_t eeconfig_update_user_datablock(const void *data, uint32_t offset, uint32_t length);
void     eeconfig_init_user_datablock(void);
#    define eeconfig_read_user_datablock_field(__object, __field) eeconfig_read_user_datablock(&(__object.__field), offsetof(__object, __field), sizeof(__object.__field))
#    define eeconfig_update_user_datablock_field(__object, __field) eeconfig_update_user_datablock(&(__object.__field), offsetof(__object, __field), sizeof(__object.__field))
#endif // (EECONFIG_USER_DATA_SIZE) > 0

// Any "checked" debounce variant used requires implementation of:
//    -- bool eeconfig_check_valid_##name(void)
//    -- void eeconfig_post_flush_##name(void)
#define EECONFIG_DEBOUNCE_HELPER_CHECKED(name, config)                  \
    static uint8_t dirty_##name = false;                                \
                                                                        \
    bool eeconfig_check_valid_##name(void);                             \
    void eeconfig_post_flush_##name(void);                              \
                                                                        \
    static inline void eeconfig_init_##name(void) {                     \
        dirty_##name = true;                                            \
        if (eeconfig_check_valid_##name()) {                            \
            eeconfig_read_##name(&config);                              \
            dirty_##name = false;                                       \
        }                                                               \
    }                                                                   \
    static inline void eeconfig_flush_##name(bool force) {              \
        if (force || dirty_##name) {                                    \
            eeconfig_update_##name(&config);                            \
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

#define EECONFIG_DEBOUNCE_HELPER(name, config)     \
    EECONFIG_DEBOUNCE_HELPER_CHECKED(name, config) \
                                                   \
    bool eeconfig_check_valid_##name(void) {       \
        return true;                               \
    }                                              \
    void eeconfig_post_flush_##name(void) {}
