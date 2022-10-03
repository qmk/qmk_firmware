// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdint.h>
#include <string.h>

#include "eeprom_driver.h"
#include "wear_leveling.h"

void eeprom_driver_init(void) {
    wear_leveling_init();
}

void eeprom_driver_erase(void) {
    wear_leveling_erase();
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    wear_leveling_read((uint32_t)addr, buf, len);
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    wear_leveling_write((uint32_t)addr, buf, len);
}
