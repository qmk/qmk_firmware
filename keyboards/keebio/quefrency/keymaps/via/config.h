// Copyright 2024 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if defined(KEYBOARD_keebio_quefrency_rev1)
    // Set 65% column (option 1) and Macro (option 2) on by default
    #define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x60

#elif defined(KEYBOARD_keebio_quefrency_rev2)
    // Set 65% column (option 3) and Macro (option 4) on by default
    #define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x00DE
    #define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2

#elif defined(KEYBOARD_keebio_quefrency_rev3)
    // Set 65% column (option 3) and Macro (option 4) on by default
    #define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x00DE
    #define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2

#elif defined(KEYBOARD_keebio_quefrency_rev6)
    #define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2

#endif
