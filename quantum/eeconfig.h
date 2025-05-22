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
#include <stddef.h>       // offsetof
#include "action_layer.h" // layer_state_t

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

typedef union debug_config_t debug_config_t;
void                         eeconfig_read_debug(debug_config_t *debug_config) __attribute__((nonnull));
void                         eeconfig_update_debug(const debug_config_t *debug_config) __attribute__((nonnull));

layer_state_t eeconfig_read_default_layer(void);
void          eeconfig_update_default_layer(layer_state_t state);

typedef union keymap_config_t keymap_config_t;
void                          eeconfig_read_keymap(keymap_config_t *keymap_config) __attribute__((nonnull));
void                          eeconfig_update_keymap(const keymap_config_t *keymap_config) __attribute__((nonnull));

#ifdef AUDIO_ENABLE
typedef union audio_config_t audio_config_t;
void                         eeconfig_read_audio(audio_config_t *audio_config) __attribute__((nonnull));
void                         eeconfig_update_audio(const audio_config_t *audio_config) __attribute__((nonnull));
#endif // AUDIO_ENABLE

#ifdef UNICODE_COMMON_ENABLE
typedef union unicode_config_t unicode_config_t;
void                           eeconfig_read_unicode_mode(unicode_config_t *unicode_config) __attribute__((nonnull));
void                           eeconfig_update_unicode_mode(const unicode_config_t *unicode_config) __attribute__((nonnull));
#endif // UNICODE_COMMON_ENABLE

#ifdef BACKLIGHT_ENABLE
typedef union backlight_config_t backlight_config_t;
void                             eeconfig_read_backlight(backlight_config_t *backlight_config) __attribute__((nonnull));
void                             eeconfig_update_backlight(const backlight_config_t *backlight_config) __attribute__((nonnull));
#endif // BACKLIGHT_ENABLE

#ifdef STENO_ENABLE
uint8_t eeconfig_read_steno_mode(void);
void    eeconfig_update_steno_mode(uint8_t val);
#endif // STENO_ENABLE

#ifdef RGB_MATRIX_ENABLE
typedef union rgb_config_t rgb_config_t;
void                       eeconfig_read_rgb_matrix(rgb_config_t *rgb_matrix_config) __attribute__((nonnull));
void                       eeconfig_update_rgb_matrix(const rgb_config_t *rgb_matrix_config) __attribute__((nonnull));
#endif // RGB_MATRIX_ENABLE

#ifdef LED_MATRIX_ENABLE
typedef union led_eeconfig_t led_eeconfig_t;
void                         eeconfig_read_led_matrix(led_eeconfig_t *led_matrix_config) __attribute__((nonnull));
void                         eeconfig_update_led_matrix(const led_eeconfig_t *led_matrix_config) __attribute__((nonnull));
#endif // LED_MATRIX_ENABLE

#ifdef RGBLIGHT_ENABLE
typedef union rgblight_config_t rgblight_config_t;
void                            eeconfig_read_rgblight(rgblight_config_t *rgblight_config) __attribute__((nonnull));
void                            eeconfig_update_rgblight(const rgblight_config_t *rgblight_config) __attribute__((nonnull));
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
typedef union haptic_config_t haptic_config_t;
void                          eeconfig_read_haptic(haptic_config_t *haptic_config) __attribute__((nonnull));
void                          eeconfig_update_haptic(const haptic_config_t *haptic_config) __attribute__((nonnull));
#endif

#ifdef CONNECTION_ENABLE
typedef union connection_config_t connection_config_t;
void                              eeconfig_read_connection(connection_config_t *config);
void                              eeconfig_update_connection(const connection_config_t *config);
#endif

bool eeconfig_read_handedness(void);
void eeconfig_update_handedness(bool val);

#if (EECONFIG_KB_DATA_SIZE) > 0
bool     eeconfig_is_kb_datablock_valid(void);
uint32_t eeconfig_read_kb_datablock(void *data, uint32_t offset, uint32_t length) __attribute__((nonnull));
uint32_t eeconfig_update_kb_datablock(const void *data, uint32_t offset, uint32_t length) __attribute__((nonnull));
void     eeconfig_init_kb_datablock(void);
#    define eeconfig_read_kb_datablock_field(__object, __field) eeconfig_read_kb_datablock(&(__object.__field), offsetof(typeof(__object), __field), sizeof(__object.__field))
#    define eeconfig_update_kb_datablock_field(__object, __field) eeconfig_update_kb_datablock(&(__object.__field), offsetof(typeof(__object), __field), sizeof(__object.__field))
#endif // (EECONFIG_KB_DATA_SIZE) > 0

#if (EECONFIG_USER_DATA_SIZE) > 0
bool     eeconfig_is_user_datablock_valid(void);
uint32_t eeconfig_read_user_datablock(void *data, uint32_t offset, uint32_t length) __attribute__((nonnull));
uint32_t eeconfig_update_user_datablock(const void *data, uint32_t offset, uint32_t length) __attribute__((nonnull));
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
