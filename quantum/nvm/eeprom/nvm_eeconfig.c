// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <string.h>
#include "nvm_eeconfig.h"
#include "nvm_eeprom_eeconfig_internal.h"
#include "util.h"
#include "eeconfig.h"
#include "eeprom.h"

#if defined(EEPROM_DRIVER)
#    include "eeprom_driver.h"
#endif

#if defined(VIA_ENABLE)
bool via_eeprom_is_valid(void);
void via_eeprom_set_valid(bool valid);
void eeconfig_init_via(void);
#endif

bool nvm_eeconfig_is_enabled(void) {
    bool is_eeprom_enabled = (eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER);
#ifdef VIA_ENABLE
    if (is_eeprom_enabled) {
        is_eeprom_enabled = via_eeprom_is_valid();
    }
#endif // VIA_ENABLE
    return is_eeprom_enabled;
}

bool nvm_eeconfig_is_disabled(void) {
    bool is_eeprom_disabled = (eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER_OFF);
#ifdef VIA_ENABLE
    if (!is_eeprom_disabled) {
        is_eeprom_disabled = !via_eeprom_is_valid();
    }
#endif // VIA_ENABLE
    return is_eeprom_disabled;
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

uint8_t nvm_eeconfig_read_debug(void) {
    return eeprom_read_byte(EECONFIG_DEBUG);
}
void nvm_eeconfig_update_debug(uint8_t val) {
    eeprom_update_byte(EECONFIG_DEBUG, val);
}

uint8_t nvm_eeconfig_read_default_layer(void) {
    return eeprom_read_byte(EECONFIG_DEFAULT_LAYER);
}
void nvm_eeconfig_update_default_layer(uint8_t val) {
    eeprom_update_byte(EECONFIG_DEFAULT_LAYER, val);
}

uint16_t nvm_eeconfig_read_keymap(void) {
    return eeprom_read_word(EECONFIG_KEYMAP);
}
void nvm_eeconfig_update_keymap(uint16_t val) {
    eeprom_update_word(EECONFIG_KEYMAP, val);
}

#ifdef AUDIO_ENABLE
uint8_t nvm_eeconfig_read_audio(void) {
    return eeprom_read_byte(EECONFIG_AUDIO);
}
void nvm_eeconfig_update_audio(uint8_t val) {
    eeprom_update_byte(EECONFIG_AUDIO, val);
}
#endif // AUDIO_ENABLE

#ifdef UNICODE_COMMON_ENABLE
uint8_t nvm_eeconfig_read_unicode_mode(void) {
    return eeprom_read_byte(EECONFIG_UNICODEMODE);
}
void nvm_eeconfig_update_unicode_mode(uint8_t val) {
    eeprom_update_byte(EECONFIG_UNICODEMODE, val);
}
#endif // UNICODE_COMMON_ENABLE

#ifdef BACKLIGHT_ENABLE
uint8_t nvm_eeconfig_read_backlight(void) {
    return eeprom_read_byte(EECONFIG_BACKLIGHT);
}
void nvm_eeconfig_update_backlight(uint8_t val) {
    eeprom_update_byte(EECONFIG_BACKLIGHT, val);
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
uint32_t nvm_eeconfig_read_haptic(void) {
    return eeprom_read_dword(EECONFIG_HAPTIC);
}
void nvm_eeconfig_update_haptic(uint32_t val) {
    eeprom_update_dword(EECONFIG_HAPTIC, val);
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
