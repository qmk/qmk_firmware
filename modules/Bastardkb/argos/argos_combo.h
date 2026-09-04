// Copyright 2026 Quentin LEBASTARD <bstkbd@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "process_combo.h"

// TODO move non-public functions into the c file.

void argos_combos_load_from_eeprom(void);
void argos_combos_copy_from_QMK(void);
bool argos_combo_read_eeprom(uint8_t index, argos_combo_t* combo);
void argos_combo_write_eeprom(uint8_t index, argos_combo_t* combo);
combo_t argos_combo_get(uint8_t index);
void argos_combo_load_from_eeprom(uint8_t index);
void argos_combo_set_keycode(uint8_t combo_index, uint16_t keycode, uint8_t key_index);