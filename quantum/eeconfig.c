#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "eeprom.h"
#include "eeconfig.h"
#include "action_layer.h"
#include "nvm_eeconfig.h"

#ifdef EEPROM_DRIVER
#    include "eeprom_driver.h"
#endif // EEPROM_DRIVER

#ifdef HAPTIC_ENABLE
#    include "haptic.h"
#endif // HAPTIC_ENABLE

#ifdef VIA_ENABLE
bool via_eeprom_is_valid(void);
void via_eeprom_set_valid(bool valid);
void eeconfig_init_via(void);
#endif // VIA_ENABLE

__attribute__((weak)) void eeconfig_init_user(void) {
#if (EECONFIG_USER_DATA_SIZE) == 0
    // Reset user EEPROM value to blank, rather than to a set value
    eeconfig_update_user(0);
#endif // (EECONFIG_USER_DATA_SIZE) == 0
}

__attribute__((weak)) void eeconfig_init_kb(void) {
#if (EECONFIG_KB_DATA_SIZE) == 0
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);
#endif // (EECONFIG_KB_DATA_SIZE) == 0

    eeconfig_init_user();
}

void eeconfig_init_quantum(void) {
#ifdef EEPROM_DRIVER
    eeprom_driver_format(false);
#endif // EEPROM_DRIVER

    eeconfig_enable();
    eeconfig_update_debug(0);
    default_layer_state = (layer_state_t)1 << 0;
    eeconfig_update_default_layer(default_layer_state);
    // Enable oneshot and autocorrect by default: 0b0001 0100 0000 0000
    eeconfig_update_keymap(0x1400);

#ifdef BACKLIGHT_ENABLE
    eeconfig_update_backlight(0);
#endif // BACKLIGHT_ENABLE

#ifdef AUDIO_ENABLE
    eeconfig_update_audio(0);
#endif // AUDIO_ENABLE

#ifdef RGBLIGHT_ENABLE
    rgblight_config_t rgblight_config = {0};
    eeconfig_update_rgblight(&rgblight_config);
#endif // RGBLIGHT_ENABLE

#ifdef UNICODE_COMMON_ENABLE
    eeconfig_update_unicode_mode(0);
#endif // UNICODE_COMMON_ENABLE

#ifdef STENO_ENABLE
    nvm_eeconfig_update_steno_mode(0);
#endif // STENO_ENABLE

#ifdef RGB_MATRIX_ENABLE
    rgb_config_t rgb_matrix_config = {0};
    eeconfig_update_rgb_matrix(&rgb_matrix_config);
#endif

#ifdef LED_MATRIX_ENABLE
    led_eeconfig_t led_matrix_config = {0};
    eeconfig_update_led_matrix(&led_matrix_config);
#endif // LED_MATRIX_ENABLE

#ifdef HAPTIC_ENABLE
    nvm_eeconfig_update_haptic(0);
    haptic_reset();
#endif // HAPTIC_ENABLE

#if (EECONFIG_KB_DATA_SIZE) > 0
    eeconfig_init_kb_datablock();
#endif // (EECONFIG_KB_DATA_SIZE) > 0

#if (EECONFIG_USER_DATA_SIZE) > 0
    eeconfig_init_user_datablock();
#endif // (EECONFIG_USER_DATA_SIZE) > 0

#if defined(VIA_ENABLE)
    // Invalidate VIA eeprom config, and then reset.
    // Just in case if power is lost mid init, this makes sure that it pets
    // properly re-initialized.
    via_eeprom_set_valid(false);
    eeconfig_init_via();
#endif

    eeconfig_init_kb();
}

void eeconfig_init(void) {
    eeconfig_init_quantum();
}

void eeconfig_enable(void) {
    nvm_eeconfig_enable();
}

void eeconfig_disable(void) {
    nvm_eeconfig_disable();
}

bool eeconfig_is_enabled(void) {
    return nvm_eeconfig_is_enabled();
}

bool eeconfig_is_disabled(void) {
    return nvm_eeconfig_is_disabled();
}

uint8_t eeconfig_read_debug(void) {
    return nvm_eeconfig_read_debug();
}
void eeconfig_update_debug(uint8_t val) {
    nvm_eeconfig_update_debug(val);
}

uint8_t eeconfig_read_default_layer(void) {
    return nvm_eeconfig_read_default_layer();
}
void eeconfig_update_default_layer(uint8_t val) {
    nvm_eeconfig_update_default_layer(val);
}

uint16_t eeconfig_read_keymap(void) {
    return nvm_eeconfig_read_keymap();
}
void eeconfig_update_keymap(uint16_t val) {
    nvm_eeconfig_update_keymap(val);
}

#ifdef AUDIO_ENABLE
uint8_t eeconfig_read_audio(void) {
    return nvm_eeconfig_read_audio();
}
void eeconfig_update_audio(uint8_t val) {
    nvm_eeconfig_update_audio(val);
}
#endif // AUDIO_ENABLE

#ifdef UNICODE_COMMON_ENABLE
uint8_t eeconfig_read_unicode_mode(void) {
    return nvm_eeconfig_read_unicode_mode();
}
void eeconfig_update_unicode_mode(uint8_t val) {
    nvm_eeconfig_update_unicode_mode(val);
}
#endif // UNICODE_COMMON_ENABLE

#ifdef BACKLIGHT_ENABLE
uint8_t eeconfig_read_backlight(void) {
    return nvm_eeconfig_read_backlight();
}
void eeconfig_update_backlight(uint8_t val) {
    nvm_eeconfig_update_backlight(val);
}
#endif // BACKLIGHT_ENABLE

#ifdef STENO_ENABLE
uint8_t eeconfig_read_steno_mode(void) {
    return nvm_eeconfig_read_steno_mode();
}
void eeconfig_update_steno_mode(uint8_t val) {
    nvm_eeconfig_update_steno_mode(val);
}
#endif // STENO_ENABLE

#ifdef RGB_MATRIX_ENABLE
void eeconfig_read_rgb_matrix(rgb_config_t *rgb_matrix_config) {
    nvm_eeconfig_read_rgb_matrix(rgb_matrix_config);
}
void eeconfig_update_rgb_matrix(const rgb_config_t *rgb_matrix_config) {
    nvm_eeconfig_update_rgb_matrix(rgb_matrix_config);
}
#endif // RGB_MATRIX_ENABLE

#ifdef LED_MATRIX_ENABLE
void eeconfig_read_led_matrix(led_eeconfig_t *led_matrix_config) {
    nvm_eeconfig_read_led_matrix(led_matrix_config);
}
void eeconfig_update_led_matrix(const led_eeconfig_t *led_matrix_config) {
    nvm_eeconfig_update_led_matrix(led_matrix_config);
}
#endif // LED_MATRIX_ENABLE

#ifdef RGBLIGHT_ENABLE
void eeconfig_read_rgblight(rgblight_config_t *rgblight_config) {
    nvm_eeconfig_read_rgblight(rgblight_config);
}
void eeconfig_update_rgblight(const rgblight_config_t *rgblight_config) {
    nvm_eeconfig_update_rgblight(rgblight_config);
}
#endif // RGBLIGHT_ENABLE

#if (EECONFIG_KB_DATA_SIZE) == 0
uint32_t eeconfig_read_kb(void) {
    return nvm_eeconfig_read_kb();
}
void eeconfig_update_kb(uint32_t val) {
    nvm_eeconfig_update_kb(val);
}
#endif // (EECONFIG_KB_DATA_SIZE) == 0

#if (EECONFIG_USER_DATA_SIZE) == 0
uint32_t eeconfig_read_user(void) {
    return nvm_eeconfig_read_user();
}
void eeconfig_update_user(uint32_t val) {
    nvm_eeconfig_update_user(val);
}
#endif // (EECONFIG_USER_DATA_SIZE) == 0

#ifdef HAPTIC_ENABLE
uint32_t eeconfig_read_haptic(void) {
    return nvm_eeconfig_read_haptic();
}
void eeconfig_update_haptic(uint32_t val) {
    nvm_eeconfig_update_haptic(val);
}
#endif // HAPTIC_ENABLE

bool eeconfig_read_handedness(void) {
    return nvm_eeconfig_read_handedness();
}
void eeconfig_update_handedness(bool val) {
    nvm_eeconfig_update_handedness(val);
}

#if (EECONFIG_KB_DATA_SIZE) > 0
bool eeconfig_is_kb_datablock_valid(void) {
    return nvm_eeconfig_is_kb_datablock_valid();
}
void eeconfig_read_kb_datablock(void *data) {
    nvm_eeconfig_read_kb_datablock(data);
}
void eeconfig_update_kb_datablock(const void *data) {
    nvm_eeconfig_update_kb_datablock(data);
}
__attribute__((weak)) void eeconfig_init_kb_datablock(void) {
    nvm_eeconfig_init_kb_datablock();
}
#endif // (EECONFIG_KB_DATA_SIZE) > 0

#if (EECONFIG_USER_DATA_SIZE) > 0
bool eeconfig_is_user_datablock_valid(void) {
    return nvm_eeconfig_is_user_datablock_valid();
}
void eeconfig_read_user_datablock(void *data) {
    nvm_eeconfig_read_user_datablock(data);
}
void eeconfig_update_user_datablock(const void *data) {
    nvm_eeconfig_update_user_datablock(data);
}
__attribute__((weak)) void eeconfig_init_user_datablock(void) {
    nvm_eeconfig_init_user_datablock();
}
#endif // (EECONFIG_USER_DATA_SIZE) > 0
