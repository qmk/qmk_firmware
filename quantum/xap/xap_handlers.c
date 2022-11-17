/* Copyright 2021 Nick Brassel (@tzarc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <quantum.h>
#include <xap.h>

#include "hardware_id.h"
#include "secure.h"
#ifndef SECURE_ENABLE
#    define secure_get_status() SECURE_UNLOCKED
#    define secure_request_unlock()
#    define secure_lock()
#    define secure_is_unlocked() false
#endif

#ifdef DYNAMIC_KEYMAP_ENABLE
#    define keymap_max_layer_count() DYNAMIC_KEYMAP_LAYER_COUNT
#else
#    define keymap_max_layer_count() keymap_layer_count()
#endif

void xap_respond_success(xap_token_t token) {
    xap_send(token, XAP_RESPONSE_FLAG_SUCCESS, NULL, 0);
}

void xap_respond_failure(xap_token_t token, xap_response_flags_t response_flags) {
    xap_send(token, response_flags, NULL, 0);
}

bool xap_respond_data(xap_token_t token, const void *data, size_t length) {
    xap_send(token, XAP_RESPONSE_FLAG_SUCCESS, data, length);
    return true;
}

bool xap_respond_data_P(xap_token_t token, const void *data, size_t length) {
    uint8_t blob[length];
    memcpy_P(blob, data, length);
    return xap_respond_data(token, blob, length);
}

bool xap_respond_u32(xap_token_t token, uint32_t value) {
    xap_send(token, XAP_RESPONSE_FLAG_SUCCESS, &value, sizeof(value));
    return true;
}

uint32_t xap_route_qmk_ffffffffffffffff_getter(void) {
    return 0x12345678;
}

bool xap_respond_get_config_blob_chunk(xap_token_t token, const void *data, size_t length) {
    if (length != sizeof(uint16_t)) {
        return false;
    }

    uint16_t offset;
    memcpy(&offset, data, sizeof(uint16_t));

    xap_route_qmk_config_blob_chunk_t ret = {0};

    bool get_config_blob_chunk(uint16_t offset, uint8_t * data, uint8_t data_len);
    if (!get_config_blob_chunk(offset, (uint8_t *)&ret, sizeof(ret))) {
        return false;
    }

    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_respond_secure_status(xap_token_t token, const void *data, size_t length) {
    uint8_t ret = secure_get_status();
    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_respond_secure_unlock(xap_token_t token, const void *data, size_t length) {
    secure_request_unlock();
    return xap_respond_data(token, NULL, 0);
}

bool xap_respond_secure_lock(xap_token_t token, const void *data, size_t length) {
    secure_lock();
    return xap_respond_data(token, NULL, 0);
}

#ifdef BOOTLOADER_JUMP_SUPPORTED
bool xap_respond_request_bootloader_jump(xap_token_t token, const void *data, size_t length) {
    uint8_t ret = secure_is_unlocked();

    // TODO: post to deferred queue so this request can return?
    bool res = xap_respond_data(token, &ret, sizeof(ret));
    reset_keyboard();
    return res;
}
#endif

#ifndef NO_RESET
bool xap_respond_request_eeprom_reset(xap_token_t token, const void *data, size_t length) {
    uint8_t ret = secure_is_unlocked();

    // TODO: post to deferred queue so this request can return?
    bool res = xap_respond_data(token, &ret, sizeof(ret));
    eeconfig_disable();
    soft_reset_keyboard();
    return res;
}
#endif

bool xap_respond_get_hardware_id(xap_token_t token, const void *data, size_t length) {
    hardware_id_t ret = get_hardware_id();
    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_respond_keymap_get_layer_count(xap_token_t token, const void *data, size_t length) {
    uint8_t ret = keymap_max_layer_count();
    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_respond_get_keymap_keycode(xap_token_t token, const void *data, size_t length) {
    if (length != sizeof(xap_route_keymap_get_keymap_keycode_arg_t)) {
        return false;
    }

    xap_route_keymap_get_keymap_keycode_arg_t *arg = (xap_route_keymap_get_keymap_keycode_arg_t *)data;

    if (arg->layer >= keymap_max_layer_count()) {
        return false;
    }

    uint16_t keycode = keycode_at_keymap_location(arg->layer, arg->row, arg->column);
    return xap_respond_data(token, &keycode, sizeof(keycode));
}

#if ((defined(ENCODER_MAP_ENABLE)))
bool xap_respond_get_encoder_keycode(xap_token_t token, const void *data, size_t length) {
    if (length != sizeof(xap_route_keymap_get_encoder_keycode_arg_t)) {
        return false;
    }

    xap_route_keymap_get_encoder_keycode_arg_t *arg = (xap_route_keymap_get_encoder_keycode_arg_t *)data;

    if (arg->layer >= keymap_max_layer_count()) {
        return false;
    }

    uint16_t keycode = keycode_at_encodermap_location(arg->layer, arg->encoder, arg->clockwise);
    return xap_respond_data(token, &keycode, sizeof(keycode));
}
#endif

#if ((defined(DYNAMIC_KEYMAP_ENABLE)))
bool xap_respond_dynamic_keymap_set_keycode(xap_token_t token, const void *data, size_t length) {
    if (length != sizeof(xap_route_remapping_set_keymap_keycode_arg_t)) {
        return false;
    }

    xap_route_remapping_set_keymap_keycode_arg_t *arg = (xap_route_remapping_set_keymap_keycode_arg_t *)data;

    if (arg->layer >= keymap_max_layer_count()) {
        return false;
    }

    dynamic_keymap_set_keycode(arg->layer, arg->row, arg->column, arg->keycode);
    xap_respond_success(token);
    return true;
}
#endif

#if ((defined(DYNAMIC_KEYMAP_ENABLE) && defined(ENCODER_MAP_ENABLE)))
bool xap_respond_dynamic_encoder_set_keycode(xap_token_t token, const void *data, size_t length) {
    if (length != sizeof(xap_route_remapping_set_encoder_keycode_arg_t)) {
        return false;
    }

    xap_route_remapping_set_encoder_keycode_arg_t *arg = (xap_route_remapping_set_encoder_keycode_arg_t *)data;

    if (arg->layer >= keymap_max_layer_count()) {
        return false;
    }

    dynamic_keymap_set_encoder(arg->layer, arg->encoder, arg->clockwise, arg->keycode);
    xap_respond_success(token);
    return true;
}
#endif

#define INVALID_EFFECT 0xFF

#if ((defined(BACKLIGHT_ENABLE)))
#    include "backlight.h"

extern backlight_config_t backlight_config;

bool xap_respond_get_backlight_config(xap_token_t token, const void *data, size_t length) {
    xap_route_lighting_backlight_get_config_t ret;

    ret.enable = backlight_config.enable;
    ret.mode   = backlight_config.breathing;
    ret.val    = backlight_config.level;

    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_respond_set_backlight_config(xap_token_t token, const void *data, size_t length) {
    if (length != sizeof(xap_route_lighting_backlight_set_config_arg_t)) {
        return false;
    }

    xap_route_lighting_backlight_set_config_arg_t *arg = (xap_route_lighting_backlight_set_config_arg_t *)data;

    if (arg->enable) {
        backlight_level_noeeprom(arg->val);
    } else {
        backlight_level_noeeprom(0);
    }

#    ifdef BACKLIGHT_BREATHING
    if (arg->mode) {
        backlight_enable_breathing();
    } else {
        backlight_disable_breathing();
    }
#    endif

    xap_respond_success(token);
    return true;
}

bool xap_respond_save_backlight_config(xap_token_t token, const void *data, size_t length) {
    eeconfig_update_backlight_current();

    xap_respond_success(token);
    return true;
}
#endif

#if ((defined(RGBLIGHT_ENABLE)))
#    include "rgblight.h"

extern rgblight_config_t rgblight_config;

uint8_t rgblight2xap(uint8_t val);
uint8_t xap2rgblight(uint8_t val);

void rgblight_enabled_noeeprom(bool val) {
    val ? rgblight_enable_noeeprom() : rgblight_disable_noeeprom();
}

bool xap_respond_get_rgblight_config(xap_token_t token, const void *data, size_t length) {
    xap_route_lighting_rgblight_get_config_t ret;

    ret.enable = rgblight_config.enable;
    ret.mode   = rgblight2xap(rgblight_config.mode);
    ret.hue    = rgblight_config.hue;
    ret.sat    = rgblight_config.sat;
    ret.val    = rgblight_config.val;
    ret.speed  = rgblight_config.speed;

    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_respond_set_rgblight_config(xap_token_t token, const void *data, size_t length) {
    if (length != sizeof(xap_route_lighting_rgblight_set_config_arg_t)) {
        return false;
    }

    xap_route_lighting_rgblight_set_config_arg_t *arg = (xap_route_lighting_rgblight_set_config_arg_t *)data;

    uint8_t mode = xap2rgblight(arg->mode);
    if (mode == INVALID_EFFECT) {
        return false;
    }

    rgblight_enabled_noeeprom(arg->enable);
    rgblight_mode_noeeprom(mode);
    rgblight_sethsv_noeeprom(arg->hue, arg->sat, arg->val);
    rgblight_set_speed_noeeprom(arg->speed);

    xap_respond_success(token);
    return true;
}

bool xap_respond_save_rgblight_config(xap_token_t token, const void *data, size_t length) {
    eeconfig_update_rgblight_current();

    xap_respond_success(token);
    return true;
}
#endif

#if ((defined(RGB_MATRIX_ENABLE)))
#    include "rgb_matrix.h"

extern rgb_config_t rgb_matrix_config;

uint8_t rgb_matrix2xap(uint8_t val);
uint8_t xap2rgb_matrix(uint8_t val);

void rgb_matrix_enabled_noeeprom(bool val) {
    val ? rgb_matrix_enable_noeeprom() : rgb_matrix_disable_noeeprom();
}

bool xap_respond_get_rgb_matrix_config(xap_token_t token, const void *data, size_t length) {
    xap_route_lighting_rgb_matrix_get_config_t ret;

    ret.enable = rgb_matrix_config.enable;
    ret.mode   = rgb_matrix2xap(rgb_matrix_config.mode);
    ret.hue    = rgb_matrix_config.hsv.h;
    ret.sat    = rgb_matrix_config.hsv.s;
    ret.val    = rgb_matrix_config.hsv.v;
    ret.speed  = rgb_matrix_config.speed;
    ret.flags  = rgb_matrix_config.flags;

    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_respond_set_rgb_matrix_config(xap_token_t token, const void *data, size_t length) {
    if (length != sizeof(xap_route_lighting_rgb_matrix_set_config_arg_t)) {
        return false;
    }

    xap_route_lighting_rgb_matrix_set_config_arg_t *arg = (xap_route_lighting_rgb_matrix_set_config_arg_t *)data;

    uint8_t mode = xap2rgb_matrix(arg->mode);
    if (mode == INVALID_EFFECT) {
        return false;
    }

    rgb_matrix_enabled_noeeprom(arg->enable);
    rgb_matrix_mode_noeeprom(mode);
    rgb_matrix_sethsv_noeeprom(arg->hue, arg->sat, arg->val);
    rgb_matrix_set_speed_noeeprom(arg->speed);
    rgb_matrix_set_flags_noeeprom(arg->flags);

    xap_respond_success(token);
    return true;
}

bool xap_respond_save_rgb_matrix_config(xap_token_t token, const void *data, size_t length) {
    eeconfig_update_rgb_matrix();

    xap_respond_success(token);
    return true;
}
#endif
