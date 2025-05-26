// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action_layer.h" // layer_state_t

#ifndef EECONFIG_MAGIC_NUMBER
#    define EECONFIG_MAGIC_NUMBER (uint16_t)0xFEE3 // When changing, decrement this value to avoid future re-init issues
#endif
#define EECONFIG_MAGIC_NUMBER_OFF (uint16_t)0xFFFF

void nvm_eeconfig_erase(void);

bool nvm_eeconfig_is_enabled(void);
bool nvm_eeconfig_is_disabled(void);

void nvm_eeconfig_enable(void);
void nvm_eeconfig_disable(void);

typedef union debug_config_t debug_config_t;
void                         nvm_eeconfig_read_debug(debug_config_t *debug_config);
void                         nvm_eeconfig_update_debug(const debug_config_t *debug_config);

layer_state_t nvm_eeconfig_read_default_layer(void);
void          nvm_eeconfig_update_default_layer(layer_state_t state);

typedef union keymap_config_t keymap_config_t;
void                          nvm_eeconfig_read_keymap(keymap_config_t *keymap_config);
void                          nvm_eeconfig_update_keymap(const keymap_config_t *keymap_config);

#ifdef AUDIO_ENABLE
typedef union audio_config_t audio_config_t;
void                         nvm_eeconfig_read_audio(audio_config_t *audio_config);
void                         nvm_eeconfig_update_audio(const audio_config_t *audio_config);
#endif // AUDIO_ENABLE

#ifdef UNICODE_COMMON_ENABLE
typedef union unicode_config_t unicode_config_t;
void                           nvm_eeconfig_read_unicode_mode(unicode_config_t *unicode_config);
void                           nvm_eeconfig_update_unicode_mode(const unicode_config_t *unicode_config);
#endif // UNICODE_COMMON_ENABLE

#ifdef BACKLIGHT_ENABLE
typedef union backlight_config_t backlight_config_t;
void                             nvm_eeconfig_read_backlight(backlight_config_t *backlight_config);
void                             nvm_eeconfig_update_backlight(const backlight_config_t *backlight_config);
#endif // BACKLIGHT_ENABLE

#ifdef STENO_ENABLE
uint8_t nvm_eeconfig_read_steno_mode(void);
void    nvm_eeconfig_update_steno_mode(uint8_t val);
#endif // STENO_ENABLE

#ifdef RGB_MATRIX_ENABLE
typedef union rgb_config_t rgb_config_t;
void                       nvm_eeconfig_read_rgb_matrix(rgb_config_t *rgb_matrix_config);
void                       nvm_eeconfig_update_rgb_matrix(const rgb_config_t *rgb_matrix_config);
#endif

#ifdef LED_MATRIX_ENABLE
typedef union led_eeconfig_t led_eeconfig_t;
void                         nvm_eeconfig_read_led_matrix(led_eeconfig_t *led_matrix_config);
void                         nvm_eeconfig_update_led_matrix(const led_eeconfig_t *led_matrix_config);
#endif // LED_MATRIX_ENABLE

#ifdef RGBLIGHT_ENABLE
typedef union rgblight_config_t rgblight_config_t;
void                            nvm_eeconfig_read_rgblight(rgblight_config_t *rgblight_config);
void                            nvm_eeconfig_update_rgblight(const rgblight_config_t *rgblight_config);
#endif // RGBLIGHT_ENABLE

#if (EECONFIG_KB_DATA_SIZE) == 0
uint32_t nvm_eeconfig_read_kb(void);
void     nvm_eeconfig_update_kb(uint32_t val);
#endif // (EECONFIG_KB_DATA_SIZE) == 0

#if (EECONFIG_USER_DATA_SIZE) == 0
uint32_t nvm_eeconfig_read_user(void);
void     nvm_eeconfig_update_user(uint32_t val);
#endif // (EECONFIG_USER_DATA_SIZE) == 0

#ifdef HAPTIC_ENABLE
typedef union haptic_config_t haptic_config_t;
void                          nvm_eeconfig_read_haptic(haptic_config_t *haptic_config);
void                          nvm_eeconfig_update_haptic(const haptic_config_t *haptic_config);
#endif // HAPTIC_ENABLE

#ifdef CONNECTION_ENABLE
typedef union connection_config_t connection_config_t;
void                              nvm_eeconfig_read_connection(connection_config_t *config);
void                              nvm_eeconfig_update_connection(const connection_config_t *config);
#endif // CONNECTION_ENABLE

bool nvm_eeconfig_read_handedness(void);
void nvm_eeconfig_update_handedness(bool val);

#if (EECONFIG_KB_DATA_SIZE) > 0
bool     nvm_eeconfig_is_kb_datablock_valid(void);
uint32_t nvm_eeconfig_read_kb_datablock(void *data, uint32_t offset, uint32_t length);
uint32_t nvm_eeconfig_update_kb_datablock(const void *data, uint32_t offset, uint32_t length);
void     nvm_eeconfig_init_kb_datablock(void);
#endif // (EECONFIG_KB_DATA_SIZE) > 0

#if (EECONFIG_USER_DATA_SIZE) > 0
bool     nvm_eeconfig_is_user_datablock_valid(void);
uint32_t nvm_eeconfig_read_user_datablock(void *data, uint32_t offset, uint32_t length);
uint32_t nvm_eeconfig_update_user_datablock(const void *data, uint32_t offset, uint32_t length);
void     nvm_eeconfig_init_user_datablock(void);
#endif // (EECONFIG_USER_DATA_SIZE) > 0
