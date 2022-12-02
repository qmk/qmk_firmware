// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "xap.h"

#if ((defined(AUDIO_ENABLE)))
#    include "audio.h"

extern audio_config_t audio_config;

bool xap_respond_get_audio_config(xap_token_t token, const void *data, size_t length) {
    xap_route_audio_get_config_t ret;

    ret.enable        = audio_config.enable;
    ret.clicky_enable = audio_config.clicky_enable;

    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_respond_set_audio_config(xap_token_t token, const void *data, size_t length) {
    if (length != sizeof(xap_route_audio_set_config_arg_t)) {
        return false;
    }

    xap_route_audio_set_config_arg_t *arg = (xap_route_audio_set_config_arg_t *)data;

    audio_config.enable        = arg->enable;
    audio_config.clicky_enable = arg->clicky_enable;

    return xap_respond_success(token);
}

bool xap_respond_save_audio_config(xap_token_t token, const void *data, size_t length) {
    eeconfig_update_audio(audio_config.raw);

    return xap_respond_success(token);
}
#endif
