#pragma once

// clang-format off

// Deprecated Quantum keycodes

#define RESET        QK_BOOTLOADER
#define DEBUG        QK_DEBUG_TOGGLE
#define GRAVE_ESC    QK_GRAVE_ESCAPE
#define EEPROM_RESET QK_CLEAR_EEPROM

#define KC_GESC QK_GRAVE_ESCAPE
#define EEP_RST QK_CLEAR_EEPROM

#define TERM_ON _Static_assert(false, "The Terminal feature has been removed from QMK. Please remove use of TERM_ON/TERM_OFF from your keymap.")
#define TERM_OFF _Static_assert(false, "The Terminal feature has been removed from QMK.. Please remove use of TERM_ON/TERM_OFF from your keymap.")