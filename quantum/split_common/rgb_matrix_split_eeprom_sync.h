// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>

static inline void rgb_matrix_split_eeprom_sync_flag_set(bool *pending_write_to_eeprom, bool write_to_eeprom) {
    *pending_write_to_eeprom |= write_to_eeprom;
}

static inline bool rgb_matrix_split_eeprom_sync_flag_take(bool *pending_write_to_eeprom) {
    bool write_to_eeprom = *pending_write_to_eeprom;
    *pending_write_to_eeprom = false;
    return write_to_eeprom;
}
