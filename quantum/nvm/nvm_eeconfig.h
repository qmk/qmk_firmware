// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix_types.h"
#endif

#ifdef LED_MATRIX_ENABLE
#    include "led_matrix_types.h"
#endif

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif

bool nvm_eeconfig_is_enabled(void);
bool nvm_eeconfig_is_disabled(void);

void nvm_eeconfig_enable(void);
void nvm_eeconfig_disable(void);

uint8_t nvm_eeconfig_read_debug(void);
void    nvm_eeconfig_update_debug(uint8_t val);

uint8_t nvm_eeconfig_read_default_layer(void);
void    nvm_eeconfig_update_default_layer(uint8_t val);

uint16_t nvm_eeconfig_read_keymap(void);
void     nvm_eeconfig_update_keymap(uint16_t val);

#ifdef AUDIO_ENABLE
uint8_t nvm_eeconfig_read_audio(void);
void    nvm_eeconfig_update_audio(uint8_t val);
#endif // AUDIO_ENABLE

#ifdef UNICODE_COMMON_ENABLE
uint8_t nvm_eeconfig_read_unicode_mode(void);
void    nvm_eeconfig_update_unicode_mode(uint8_t val);
#endif // UNICODE_COMMON_ENABLE

#ifdef BACKLIGHT_ENABLE
uint8_t nvm_eeconfig_read_backlight(void);
void    nvm_eeconfig_update_backlight(uint8_t val);
#endif // BACKLIGHT_ENABLE

#ifdef STENO_ENABLE
uint8_t nvm_eeconfig_read_steno_mode(void);
void    nvm_eeconfig_update_steno_mode(uint8_t val);
#endif // STENO_ENABLE

#ifdef RGB_MATRIX_ENABLE
void nvm_eeconfig_read_rgb_matrix(rgb_config_t *rgb_matrix_config);
void nvm_eeconfig_update_rgb_matrix(const rgb_config_t *rgb_matrix_config);
#endif

#ifdef LED_MATRIX_ENABLE
void nvm_eeconfig_read_led_matrix(led_eeconfig_t *led_matrix_config);
void nvm_eeconfig_update_led_matrix(const led_eeconfig_t *led_matrix_config);
#endif // LED_MATRIX_ENABLE

#ifdef RGBLIGHT_ENABLE
void nvm_eeconfig_read_rgblight(rgblight_config_t *rgblight_config);
void nvm_eeconfig_update_rgblight(const rgblight_config_t *rgblight_config);
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
uint32_t nvm_eeconfig_read_haptic(void);
void     nvm_eeconfig_update_haptic(uint32_t val);
#endif // HAPTIC_ENABLE

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
