// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
    The size of the EEPROM area handed to QMK, in bytes.
    The LPC11U35 has 4 kB of EEPROM, of which the top 64 bytes are reserved by the ROM.
*/
#ifndef LPC11UXX_EEPROM_SIZE
#    define LPC11UXX_EEPROM_SIZE 1024
#endif

#if LPC11UXX_EEPROM_SIZE > (4096 - 64)
#    error LPC11UXX_EEPROM_SIZE is larger than the usable on-chip EEPROM
#endif

// Writes out any bytes still waiting to be written. Call before a reset.
void eeprom_lpc11uxx_flush(void);
