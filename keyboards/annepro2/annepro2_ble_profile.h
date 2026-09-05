/*
 * Copyright 2026 BHE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define ANNEPRO2_BLE_PROFILE_C18_205 0
#define ANNEPRO2_BLE_PROFILE_AP2D_213 1

#ifndef ANNEPRO2_BLE_PROFILE
#    define ANNEPRO2_BLE_PROFILE ANNEPRO2_BLE_PROFILE_C18_205
#endif

#if ANNEPRO2_BLE_PROFILE != ANNEPRO2_BLE_PROFILE_C18_205 && ANNEPRO2_BLE_PROFILE != ANNEPRO2_BLE_PROFILE_AP2D_213
#    error "Unsupported Anne Pro 2 BLE profile"
#endif

#if ANNEPRO2_BLE_PROFILE == ANNEPRO2_BLE_PROFILE_AP2D_213
#    define ANNEPRO2_BLE_CONSUMER_REPORT_SIZE 8
#else
#    define ANNEPRO2_BLE_CONSUMER_REPORT_SIZE 4
#endif

typedef struct {
    uint8_t command;
    uint8_t action;
} annepro2_ble_slot_state_t;

bool annepro2_ble_encode_consumer(const uint16_t *usages, size_t usage_count, uint8_t out[ANNEPRO2_BLE_CONSUMER_REPORT_SIZE]);
void annepro2_ble_encode_slot_state(bool broadcast, annepro2_ble_slot_state_t *state);
bool annepro2_ble_decode_caps_lock(const uint8_t *frame, size_t size, bool *caps_lock);
bool annepro2_ble_encode_config(int8_t slot, uint32_t *config);
bool annepro2_ble_decode_config(uint32_t config, int8_t *slot);
