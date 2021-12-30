// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#if defined(K20x)
/* Teensy 3.0, 3.1, 3.2; mchck; infinity keyboard */
// The EEPROM is really RAM with a hardware-based backup system to
// flash memory.  Selecting a smaller size EEPROM allows more wear
// leveling, for higher write endurance.  If you edit this file,
// set this to the smallest size your application can use.  Also,
// due to Freescale's implementation, writing 16 or 32 bit words
// (aligned to 2 or 4 byte boundaries) has twice the endurance
// compared to writing 8 bit bytes.
//
#    ifndef EEPROM_SIZE
#        define EEPROM_SIZE 32
#    endif
#elif defined(KL2x) /* Teensy LC (emulated) */
#    define EEPROM_SIZE 128
#else
#    error Unsupported Teensy EEPROM.
#endif
