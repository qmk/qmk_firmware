#pragma once

// clang-format off

// Deprecated Quantum keycodes

#define KC_LEAD QK_LEADER

#define TERM_ON _Static_assert(false, "The Terminal feature has been removed from QMK. Please remove use of TERM_ON/TERM_OFF from your keymap.")
#define TERM_OFF _Static_assert(false, "The Terminal feature has been removed from QMK.. Please remove use of TERM_ON/TERM_OFF from your keymap.")
// #define RESET _Static_assert(false, "The RESET keycode has been removed from QMK.. Please remove use from your keymap.")
