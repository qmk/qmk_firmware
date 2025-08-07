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

#ifdef CONNECTION_ENABLE
#    include "connection.h"
#endif

void nvm_eeconfig_erase(void) {
#ifdef EEPROM_DRIVER
    eeprom_driver_format(false);
#endif // EEPROM_DRIVER
}

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

layer_state_t nvm_eeconfig_read_default_layer(void) {
    uint8_t val = eeprom_read_byte(EECONFIG_DEFAULT_LAYER);
#ifdef DEFAULT_LAYER_STATE_IS_VALUE_NOT_BITMASK
    // stored as a layer number, so convert back to bitmask
    return (layer_state_t)1 << val;
#else
    // stored as 8-bit-wide bitmask, so read the value directly - handling padding to 16/32 bit layer_state_t
    return (layer_state_t)val;
#endif
}
void nvm_eeconfig_update_default_layer(layer_state_t state) {
#ifdef DEFAULT_LAYER_STATE_IS_VALUE_NOT_BITMASK
    // stored as a layer number, so only store the highest layer
    uint8_t val = get_highest_layer(state);
#else
    // stored as 8-bit-wide bitmask, so write the value directly - handling truncation from 16/32 bit layer_state_t
    uint8_t val = (uint8_t)state;
#endif
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

#ifdef CONNECTION_ENABLE
void nvm_eeconfig_read_connection(connection_config_t *config) {
    config->raw = eeprom_read_byte(EECONFIG_CONNECTION);
}
void nvm_eeconfig_update_connection(const connection_config_t *config) {
    eeprom_update_byte(EECONFIG_CONNECTION, config->raw);
}
#endif // CONNECTION_ENABLE

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
    eeprom_update_dword(EECONFIG_KEYBOARD, (EECONFIG_KB_DATA_VERSION));

    void *  start     = (void *)(uintptr_t)(EECONFIG_KB_DATABLOCK);
    void *  end       = (void *)(uintptr_t)(EECONFIG_KB_DATABLOCK + EECONFIG_KB_DATA_SIZE);
    long    remaining = end - start;
    uint8_t dummy[16] = {0};
    for (int i = 0; i < EECONFIG_KB_DATA_SIZE; i += sizeof(dummy)) {
        int this_loop = remaining < sizeof(dummy) ? remaining : sizeof(dummy);
        eeprom_update_block(dummy, start, this_loop);
        start += this_loop;
        remaining -= this_loop;
    }
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
    eeprom_update_dword(EECONFIG_USER, (EECONFIG_USER_DATA_VERSION));

    void *  start     = (void *)(uintptr_t)(EECONFIG_USER_DATABLOCK);
    void *  end       = (void *)(uintptr_t)(EECONFIG_USER_DATABLOCK + EECONFIG_USER_DATA_SIZE);
    long    remaining = end - start;
    uint8_t dummy[16] = {0};
    for (int i = 0; i < EECONFIG_USER_DATA_SIZE; i += sizeof(dummy)) {
        int this_loop = remaining < sizeof(dummy) ? remaining : sizeof(dummy);
        eeprom_update_block(dummy, start, this_loop);
        start += this_loop;
        remaining -= this_loop;
    }
}

#endif // (EECONFIG_USER_DATA_SIZE) > 0
