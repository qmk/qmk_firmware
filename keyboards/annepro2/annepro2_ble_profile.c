/*
 * Copyright 2026 BHE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include "annepro2_ble_profile.h"

#include <string.h>

#define AP2_BLE_EECONFIG_MAGIC 0xA2
#define AP2_BLE_EECONFIG_VERSION 0x02
#define AP2_BLE_EECONFIG_CHECK_XOR 0x5A

#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_C18_205
static bool annepro2_ble_consumer_205_bit(uint16_t usage, uint8_t *bit) {
    switch (usage) {
        case 0x00E2:
            *bit = 0;
            return true;
        case 0x00E9:
            *bit = 1;
            return true;
        case 0x00EA:
            *bit = 2;
            return true;
        case 0x00CD:
            *bit = 3;
            return true;
        case 0x00B5:
            *bit = 4;
            return true;
        case 0x00B6:
            *bit = 5;
            return true;
        case 0x006F:
            *bit = 6;
            return true;
        case 0x0070:
            *bit = 7;
            return true;
        default:
            return false;
    }
}
#endif

bool annepro2_ble_encode_consumer(const uint16_t *usages, size_t usage_count, uint8_t out[ANNEPRO2_BLE_CONSUMER_REPORT_SIZE]) {
    memset(out, 0, ANNEPRO2_BLE_CONSUMER_REPORT_SIZE);

#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
    if (usage_count > 4) {
        return false;
    }
    for (size_t i = 0; i < usage_count; i++) {
        out[i * 2]     = (uint8_t)usages[i];
        out[i * 2 + 1] = (uint8_t)(usages[i] >> 8);
    }
    return true;
#else
    for (size_t i = 0; i < usage_count; i++) {
        uint8_t bit;
        if (usages[i] == 0) {
            continue;
        }
        if (!annepro2_ble_consumer_205_bit(usages[i], &bit)) {
            return false;
        }
        out[0] |= (uint8_t)(1U << bit);
    }
    return true;
#endif
}

void annepro2_ble_encode_slot_state(bool broadcast, annepro2_ble_slot_state_t *state) {
#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
    state->command = broadcast ? 0x0B : 0x24;
    state->action  = broadcast ? 1 : 2;
#else
    state->command = 0x0B;
    state->action  = broadcast ? 1 : 0;
#endif
}

bool annepro2_ble_decode_caps_lock(const uint8_t *frame, size_t size, bool *caps_lock) {
    static const uint8_t prefix[] = {
        0x7B, 0x12, 0x35, 0x00, 0x03, 0x00, 0x00, 0x7D, 0x20, 0x07,
    };

    if (frame == NULL || caps_lock == NULL || size != sizeof(prefix) + 1 || frame[sizeof(prefix)] > 1 || memcmp(frame, prefix, sizeof(prefix)) != 0) {
        return false;
    }

    *caps_lock = frame[sizeof(prefix)] != 0;
    return true;
}

bool annepro2_ble_encode_config(int8_t slot, uint32_t *config) {
    if (config == NULL || slot < -1 || slot > 3) {
        return false;
    }

    const uint8_t payload  = slot < 0 ? 0 : (uint8_t)slot + 1;
    const uint8_t checksum = AP2_BLE_EECONFIG_MAGIC ^ AP2_BLE_EECONFIG_VERSION ^ payload ^ AP2_BLE_EECONFIG_CHECK_XOR;
    *config                = ((uint32_t)AP2_BLE_EECONFIG_MAGIC << 24) | ((uint32_t)AP2_BLE_EECONFIG_VERSION << 16) | ((uint32_t)checksum << 8) | payload;
    return true;
}

bool annepro2_ble_decode_config(uint32_t config, int8_t *slot) {
    const uint8_t magic    = config >> 24;
    const uint8_t version  = config >> 16;
    const uint8_t checksum = config >> 8;
    const uint8_t payload  = config;

    if (slot == NULL || magic != AP2_BLE_EECONFIG_MAGIC || version != AP2_BLE_EECONFIG_VERSION || payload > 4 || checksum != (uint8_t)(magic ^ version ^ payload ^ AP2_BLE_EECONFIG_CHECK_XOR)) {
        return false;
    }

    *slot = payload == 0 ? -1 : (int8_t)payload - 1;
    return true;
}
