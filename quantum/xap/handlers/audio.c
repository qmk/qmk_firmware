// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "xap.h"

#if ((defined(AUDIO_ENABLE)))
#    include "audio.h"

extern audio_config_t audio_config;

bool xap_execute_get_audio_config(xap_token_t token) {
    xap_route_audio_get_config_t ret;

    ret.enable        = audio_config.enable;
    ret.clicky_enable = audio_config.clicky_enable;

    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_execute_set_audio_config(xap_token_t token, xap_route_audio_set_config_arg_t* arg) {
    audio_config.enable        = arg->enable;
    audio_config.clicky_enable = arg->clicky_enable;

    return xap_respond_success(token);
}

bool xap_execute_save_audio_config(xap_token_t token) {
    eeconfig_update_audio_current();

    return xap_respond_success(token);
}
#endif
