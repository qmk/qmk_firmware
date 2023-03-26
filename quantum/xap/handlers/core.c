// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "xap.h"
#include "hardware_id.h"

bool xap_execute_get_config_blob_chunk(xap_token_t token, uint16_t offset) {
    xap_route_qmk_config_blob_chunk_t ret = {0};

    bool get_config_blob_chunk(uint16_t offset, uint8_t * data, uint8_t data_len);
    if (!get_config_blob_chunk(offset, (uint8_t *)&ret, sizeof(ret))) {
        return false;
    }

    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_execute_secure_status(xap_token_t token) {
    uint8_t ret = secure_get_status();
    return xap_respond_data(token, &ret, sizeof(ret));
}

bool xap_execute_secure_unlock(xap_token_t token) {
    secure_request_unlock();
    return xap_respond_success(token);
}

bool xap_execute_secure_lock(xap_token_t token) {
    secure_lock();
    return xap_respond_success(token);
}

#ifdef BOOTLOADER_JUMP_SUPPORTED
bool xap_execute_request_bootloader(xap_token_t token) {
    uint8_t ret = secure_is_unlocked();

    // TODO: post to deferred queue so this request can return?
    bool res = xap_respond_data(token, &ret, sizeof(ret));
    reset_keyboard();
    return res;
}
#endif

#ifndef NO_RESET
bool xap_execute_request_eeprom_reset(xap_token_t token) {
    uint8_t ret = secure_is_unlocked();

    // TODO: post to deferred queue so this request can return?
    bool res = xap_respond_data(token, &ret, sizeof(ret));
    eeconfig_disable();
    soft_reset_keyboard();
    return res;
}
#endif

bool xap_execute_get_hardware_id(xap_token_t token) {
    hardware_id_t ret = get_hardware_id();
    return xap_respond_data(token, &ret, sizeof(ret));
}