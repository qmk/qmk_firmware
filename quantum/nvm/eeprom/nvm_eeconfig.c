// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <string.h>
#include "nvm_eeconfig.h"
#include "nvm_eeprom_eeconfig_internal.h"
#include "util.h"
#include "eeconfig.h"
#include "debug.h"
#include "eeprom.h"
#include "keycode_config.h"

#ifdef EEPROM_DRIVER
#    include "eeprom_driver.h"
#endif

#ifdef AUDIO_ENABLE
#    include "audio.h"
#endif

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix_types.h"
#endif

#ifdef LED_MATRIX_ENABLE
#    include "led_matrix_types.h"
#endif

#ifdef UNICODE_COMMON_ENABLE
#    include "unicode.h"
#endif

#ifdef HAPTIC_ENABLE
#    include "haptic.h"
#endif

bool nvm_eeconfig_is_enabled(void) {
    return eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER;
}

bool nvm_eeconfig_is_disabled(void) {
    return eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER_OFF;
}

void nvm_eeconfig_enable(void) {
    eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER);
}

void nvm_eeconfig_disable(void) {
#if defined(EEPROM_DRIVER)
    eeprom_driver_format(false);
#endif
    eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER_OFF);
}

void nvm_eeconfig_read_debug(debug_config_t *debug_config) {
    debug_config->raw = eeprom_read_byte(EECONFIG_DEBUG);
}
void nvm_eeconfig_update_debug(const debug_config_t *debug_config) {
    eeprom_update_byte(EECONFIG_DEBUG, debug_config->raw);
}

uint8_t nvm_eeconfig_read_default_layer(void) {
    return eeprom_read_byte(EECONFIG_DEFAULT_LAYER);
}
void nvm_eeconfig_update_default_layer(uint8_t val) {
    eeprom_update_byte(EECONFIG_DEFAULT_LAYER, val);
}

void nvm_eeconfig_read_keymap(keymap_config_t *keymap_config) {
    keymap_config->raw = eeprom_read_word(EECONFIG_KEYMAP);
}
void nvm_eeconfig_update_keymap(const keymap_config_t *keymap_config) {
    eeprom_update_word(EECONFIG_KEYMAP, keymap_config->raw);
}

#ifdef AUDIO_ENABLE
void nvm_eeconfig_read_audio(audio_config_t *audio_config) {
    audio_config->raw = eeprom_read_byte(EECONFIG_AUDIO);
}
void nvm_eeconfig_update_audio(const audio_config_t *audio_config) {
    eeprom_update_byte(EECONFIG_AUDIO, audio_config->raw);
}
#endif // AUDIO_ENABLE

#ifdef UNICODE_COMMON_ENABLE
void nvm_eeconfig_read_unicode_mode(unicode_config_t *unicode_config) {
    unicode_config->raw = eeprom_read_byte(EECONFIG_UNICODEMODE);
}
void nvm_eeconfig_update_unicode_mode(const unicode_config_t *unicode_config) {
    eeprom_update_byte(EECONFIG_UNICODEMODE, unicode_config->raw);
}
#endif // UNICODE_COMMON_ENABLE

#ifdef BACKLIGHT_ENABLE
void nvm_eeconfig_read_backlight(backlight_config_t *backlight_config) {
    backlight_config->raw = eeprom_read_byte(EECONFIG_BACKLIGHT);
}
void nvm_eeconfig_update_backlight(const backlight_config_t *backlight_config) {
    eeprom_update_byte(EECONFIG_BACKLIGHT, backlight_config->raw);
}
#endif // BACKLIGHT_ENABLE

#ifdef STENO_ENABLE
uint8_t nvm_eeconfig_read_steno_mode(void) {
    return eeprom_read_byte(EECONFIG_STENOMODE);
}
void nvm_eeconfig_update_steno_mode(uint8_t val) {
    eeprom_update_byte(EECONFIG_STENOMODE, val);
}
#endif // STENO_ENABLE

#ifdef RGBLIGHT_ENABLE
#endif // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
void nvm_eeconfig_read_rgb_matrix(rgb_config_t *rgb_matrix_config) {
    eeprom_read_block(rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_config_t));
}
void nvm_eeconfig_update_rgb_matrix(const rgb_config_t *rgb_matrix_config) {
    eeprom_update_block(rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_config_t));
}
#endif // RGB_MATRIX_ENABLE

#ifdef LED_MATRIX_ENABLE
void nvm_eeconfig_read_led_matrix(led_eeconfig_t *led_matrix_config) {
    eeprom_read_block(led_matrix_config, EECONFIG_LED_MATRIX, sizeof(led_eeconfig_t));
}
void nvm_eeconfig_update_led_matrix(const led_eeconfig_t *led_matrix_config) {
    eeprom_update_block(led_matrix_config, EECONFIG_LED_MATRIX, sizeof(led_eeconfig_t));
}
#endif // LED_MATRIX_ENABLE

#ifdef RGBLIGHT_ENABLE
void nvm_eeconfig_read_rgblight(rgblight_config_t *rgblight_config) {
    rgblight_config->raw = eeprom_read_dword(EECONFIG_RGBLIGHT);
    rgblight_config->raw |= ((uint64_t)eeprom_read_byte(EECONFIG_RGBLIGHT_EXTENDED) << 32);
}
void nvm_eeconfig_update_rgblight(const rgblight_config_t *rgblight_config) {
    eeprom_update_dword(EECONFIG_RGBLIGHT, rgblight_config->raw & 0xFFFFFFFF);
    eeprom_update_byte(EECONFIG_RGBLIGHT_EXTENDED, (rgblight_config->raw >> 32) & 0xFF);
}
#endif // RGBLIGHT_ENABLE

#if (EECONFIG_KB_DATA_SIZE) == 0
uint32_t nvm_eeconfig_read_kb(void) {
    return eeprom_read_dword(EECONFIG_KEYBOARD);
}
void nvm_eeconfig_update_kb(uint32_t val) {
    eeprom_update_dword(EECONFIG_KEYBOARD, val);
}
#endif // (EECONFIG_KB_DATA_SIZE) == 0

#if (EECONFIG_USER_DATA_SIZE) == 0
uint32_t nvm_eeconfig_read_user(void) {
    return eeprom_read_dword(EECONFIG_USER);
}
void nvm_eeconfig_update_user(uint32_t val) {
    eeprom_update_dword(EECONFIG_USER, val);
}
#endif // (EECONFIG_USER_DATA_SIZE) == 0

#ifdef HAPTIC_ENABLE
void nvm_eeconfig_read_haptic(haptic_config_t *haptic_config) {
    haptic_config->raw = eeprom_read_dword(EECONFIG_HAPTIC);
}
void nvm_eeconfig_update_haptic(const haptic_config_t *haptic_config) {
    eeprom_update_dword(EECONFIG_HAPTIC, haptic_config->raw);
}
#endif // HAPTIC_ENABLE

bool nvm_eeconfig_read_handedness(void) {
    return !!eeprom_read_byte(EECONFIG_HANDEDNESS);
}
void nvm_eeconfig_update_handedness(bool val) {
    eeprom_update_byte(EECONFIG_HANDEDNESS, !!val);
}

#if (EECONFIG_KB_DATA_SIZE) > 0

bool nvm_eeconfig_is_kb_datablock_valid(void) {
    return eeprom_read_dword(EECONFIG_KEYBOARD) == (EECONFIG_KB_DATA_VERSION);
}

uint32_t nvm_eeconfig_read_kb_datablock(void *data, uint32_t offset, uint32_t length) {
    if (eeconfig_is_kb_datablock_valid()) {
        void *ee_start = (void *)(uintptr_t)(EECONFIG_KB_DATABLOCK + offset);
        void *ee_end   = (void *)(uintptr_t)(EECONFIG_KB_DATABLOCK + MIN(EECONFIG_KB_DATA_SIZE, offset + length));
        eeprom_read_block(data, ee_start, ee_end - ee_start);
        return ee_end - ee_start;
    } else {
        memset(data, 0, length);
        return length;
    }
}

uint32_t nvm_eeconfig_update_kb_datablock(const void *data, uint32_t offset, uint32_t length) {
    eeprom_update_dword(EECONFIG_KEYBOARD, (EECONFIG_KB_DATA_VERSION));

    void *ee_start = (void *)(uintptr_t)(EECONFIG_KB_DATABLOCK + offset);
    void *ee_end   = (void *)(uintptr_t)(EECONFIG_KB_DATABLOCK + MIN(EECONFIG_KB_DATA_SIZE, offset + length));
    eeprom_update_block(data, ee_start, ee_end - ee_start);
    return ee_end - ee_start;
}

void nvm_eeconfig_init_kb_datablock(void) {
    uint8_t dummy_kb[(EECONFIG_KB_DATA_SIZE)] = {0};
    eeconfig_update_kb_datablock(dummy_kb, 0, (EECONFIG_KB_DATA_SIZE));
}

#endif // (EECONFIG_KB_DATA_SIZE) > 0

#if (EECONFIG_USER_DATA_SIZE) > 0

bool nvm_eeconfig_is_user_datablock_valid(void) {
    return eeprom_read_dword(EECONFIG_USER) == (EECONFIG_USER_DATA_VERSION);
}

uint32_t nvm_eeconfig_read_user_datablock(void *data, uint32_t offset, uint32_t length) {
    if (eeconfig_is_user_datablock_valid()) {
        void *ee_start = (void *)(uintptr_t)(EECONFIG_USER_DATABLOCK + offset);
        void *ee_end   = (void *)(uintptr_t)(EECONFIG_USER_DATABLOCK + MIN(EECONFIG_USER_DATA_SIZE, offset + length));
        eeprom_read_block(data, ee_start, ee_end - ee_start);
        return ee_end - ee_start;
    } else {
        memset(data, 0, length);
        return length;
    }
}

uint32_t nvm_eeconfig_update_user_datablock(const void *data, uint32_t offset, uint32_t length) {
    eeprom_update_dword(EECONFIG_USER, (EECONFIG_USER_DATA_VERSION));

    void *ee_start = (void *)(uintptr_t)(EECONFIG_USER_DATABLOCK + offset);
    void *ee_end   = (void *)(uintptr_t)(EECONFIG_USER_DATABLOCK + MIN(EECONFIG_USER_DATA_SIZE, offset + length));
    eeprom_update_block(data, ee_start, ee_end - ee_start);
    return ee_end - ee_start;
}

void nvm_eeconfig_init_user_datablock(void) {
    uint8_t dummy_user[(EECONFIG_USER_DATA_SIZE)] = {0};
    eeconfig_update_user_datablock(dummy_user, 0, (EECONFIG_USER_DATA_SIZE));
}

#endif // (EECONFIG_USER_DATA_SIZE) > 0
