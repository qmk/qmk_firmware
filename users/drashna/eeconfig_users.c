// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "eeconfig_users.h"
#include "eeprom.h"
#include "eeconfig.h"
#include <string.h>

#if (TOTAL_EEPROM_BYTE_COUNT - 1) < EECONFIG_SIZE && !defined(KEYBOARD_input_club_ergodox_infinity)
#    error "More eeprom configured than is available."
#endif
#if (EECONFIG_USER_DATA_SIZE) != 0 && (EECONFIG_USER_DATA_SIZE) < 4
#    error "Not enough EEPROM configured for user config."
#endif

#if (EECONFIG_USER_DATA_SIZE) == 0
#    define EECONFIG_USER_TEMP EECONFIG_USER
#else
#    define EECONFIG_USER_TEMP (uint32_t *)(EECONFIG_USER_DATABLOCK)
#endif

void eeconfig_read_user_config(uint32_t *data) {
#if (EECONFIG_USER_DATA_SIZE) > 0
    if (!eeconfig_is_user_datablock_valid()) {
        memset(data, 0, 4);
    } else
#endif
        eeprom_read_block(data, EECONFIG_USER_TEMP, 4);
}

void eeconfig_update_user_config(const uint32_t *data) {
    eeprom_update_block(data, EECONFIG_USER_TEMP, 4);
#if (EECONFIG_USER_DATA_SIZE) > 0
    eeprom_update_dword(EECONFIG_USER, (EECONFIG_USER_DATA_VERSION));
#endif
}

void eeconfig_read_user_data(void *data) {
#if (EECONFIG_USER_DATA_SIZE) > 4
    if (eeconfig_is_user_datablock_valid()) {
        eeprom_read_block(data, EECONFIG_USER_DATABLOCK + 4, (EECONFIG_USER_DATA_SIZE)-4);
    } else {
        memset(data, 0, (EECONFIG_USER_DATA_SIZE));
    }
#endif
}

void eeconfig_update_user_data(const void *data) {
#if (EECONFIG_USER_DATA_SIZE) > 4
    eeprom_update_dword(EECONFIG_USER, (EECONFIG_USER_DATA_VERSION));
    eeprom_update_block(data, EECONFIG_USER_DATABLOCK + 4, (EECONFIG_USER_DATA_SIZE)-4);
#endif
}
