#pragma once

#define MATRIX_ROWS 10
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }

#define DEBOUNCE 5

#define DISABLE_LEADER
#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }

#define EE_HANDS
#define USE_SERIAL_PD2

#define SSD1306OLED
#define OLED_TIMEOUT 300000

#define NO_MUSIC_MODE
#define PREVENT_STUCK_MODIFIERS

#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 120

#ifdef COMBO_COUNT
#undef COMBO_COUNT
#endif
#define COMBO_COUNT 2
#define COMBO_TERM 20
