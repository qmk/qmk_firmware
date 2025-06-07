// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "xap.h"
#include "keymap_introspection.h"

#ifdef DYNAMIC_KEYMAP_ENABLE
#    include "dynamic_keymap.h"
#    define keymap_max_layer_count() DYNAMIC_KEYMAP_LAYER_COUNT
#else
#    define keymap_max_layer_count() keymap_layer_count()
#endif

bool xap_execute_keymap_get_layer_count(xap_token_t token) {
    uint8_t ret = keymap_max_layer_count();
    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_execute_get_keymap_keycode(xap_token_t token, const xap_route_keymap_get_keymap_keycode_arg_t *arg) {
    if (arg->layer >= keymap_max_layer_count()) {
        return false;
    }

    uint16_t keycode = keycode_at_keymap_location(arg->layer, arg->row, arg->column);
    return xap_respond_data(token, &keycode, sizeof(keycode));
}

#if ((defined(ENCODER_MAP_ENABLE)))
bool xap_execute_get_encoder_keycode(xap_token_t token, const xap_route_keymap_get_encoder_keycode_arg_t *arg) {
    if (arg->layer >= keymap_max_layer_count()) {
        return false;
    }

    uint16_t keycode = keycode_at_encodermap_location(arg->layer, arg->encoder, arg->clockwise);
    return xap_respond_data(token, &keycode, sizeof(keycode));
}
#endif

#if ((defined(DYNAMIC_KEYMAP_ENABLE)))
bool xap_execute_dynamic_keymap_set_keycode(xap_token_t token, const xap_route_remapping_set_keymap_keycode_arg_t *arg) {
    if (arg->layer >= keymap_max_layer_count()) {
        return false;
    }

    dynamic_keymap_set_keycode(arg->layer, arg->row, arg->column, arg->keycode);
    return xap_respond_success(token);
}
#endif

#if ((defined(DYNAMIC_KEYMAP_ENABLE) && defined(ENCODER_MAP_ENABLE)))
bool xap_execute_dynamic_encoder_set_keycode(xap_token_t token, const xap_route_remapping_set_encoder_keycode_arg_t *arg) {
    if (arg->layer >= keymap_max_layer_count()) {
        return false;
    }

    dynamic_keymap_set_encoder(arg->layer, arg->encoder, arg->clockwise, arg->keycode);
    return xap_respond_success(token);
}
#endif
