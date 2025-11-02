// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "xap.h"

#define INVALID_EFFECT 0xFF

#if ((defined(BACKLIGHT_ENABLE)))
#    include "backlight.h"

extern backlight_config_t backlight_config;

bool xap_execute_get_backlight_config(xap_token_t token) {
    xap_route_lighting_backlight_get_config_t ret;

    ret.enable = backlight_config.enable;
    ret.mode   = backlight_config.breathing;
    ret.val    = backlight_config.level;

    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_execute_set_backlight_config(xap_token_t token, xap_route_lighting_backlight_set_config_arg_t* arg) {
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

    return xap_respond_success(token);
}

bool xap_execute_save_backlight_config(xap_token_t token) {
    eeconfig_update_backlight_current();

    return xap_respond_success(token);
}
#endif

#if ((defined(RGBLIGHT_ENABLE)))
#    include "rgblight.h"

extern rgblight_config_t rgblight_config;

uint8_t rgblight_effect_to_id(uint8_t val);
uint8_t rgblight_id_to_effect(uint8_t val);

bool xap_execute_get_rgblight_config(xap_token_t token) {
    xap_route_lighting_rgblight_get_config_t ret;

    ret.enable = rgblight_config.enable;
    ret.mode   = rgblight_effect_to_id(rgblight_config.mode);
    ret.hue    = rgblight_config.hue;
    ret.sat    = rgblight_config.sat;
    ret.val    = rgblight_config.val;
    ret.speed  = rgblight_config.speed;

    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_execute_set_rgblight_config(xap_token_t token, xap_route_lighting_rgblight_set_config_arg_t* arg) {
    uint8_t mode = rgblight_id_to_effect(arg->mode);
    if (mode == INVALID_EFFECT) {
        return false;
    }

    rgblight_enabled_noeeprom(arg->enable);
    rgblight_mode_noeeprom(mode);
    rgblight_sethsv_noeeprom(arg->hue, arg->sat, arg->val);
    rgblight_set_speed_noeeprom(arg->speed);

    return xap_respond_success(token);
}

bool xap_execute_save_rgblight_config(xap_token_t token) {
    eeconfig_update_rgblight_current();

    return xap_respond_success(token);
}
#endif

#if ((defined(RGB_MATRIX_ENABLE)))
#    include "rgb_matrix.h"

extern rgb_config_t rgb_matrix_config;

uint8_t rgb_matrix_effect_to_id(uint8_t val);
uint8_t rgb_matrix_id_to_effect(uint8_t val);

void rgb_matrix_enabled_noeeprom(bool val) {
    val ? rgb_matrix_enable_noeeprom() : rgb_matrix_disable_noeeprom();
}

bool xap_execute_get_rgb_matrix_config(xap_token_t token) {
    xap_route_lighting_rgb_matrix_get_config_t ret;

    ret.enable = rgb_matrix_config.enable;
    ret.mode   = rgb_matrix_effect_to_id(rgb_matrix_config.mode);
    ret.hue    = rgb_matrix_config.hsv.h;
    ret.sat    = rgb_matrix_config.hsv.s;
    ret.val    = rgb_matrix_config.hsv.v;
    ret.speed  = rgb_matrix_config.speed;
    ret.flags  = rgb_matrix_config.flags;

    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_execute_set_rgb_matrix_config(xap_token_t token, xap_route_lighting_rgb_matrix_set_config_arg_t* arg) {
    uint8_t mode = rgb_matrix_id_to_effect(arg->mode);
    if (mode == INVALID_EFFECT) {
        return false;
    }

    rgb_matrix_enabled_noeeprom(arg->enable);
    rgb_matrix_mode_noeeprom(mode);
    rgb_matrix_sethsv_noeeprom(arg->hue, arg->sat, arg->val);
    rgb_matrix_set_speed_noeeprom(arg->speed);
    rgb_matrix_set_flags_noeeprom(arg->flags);

    return xap_respond_success(token);
}

bool xap_execute_save_rgb_matrix_config(xap_token_t token) {
    eeconfig_force_flush_rgb_matrix();

    return xap_respond_success(token);
}
#endif
