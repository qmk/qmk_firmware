#pragma once


#define KEYBOARD_PCB_REV 11

/* key matrix pins */
#if KEYBOARD_PCB_REV == 10
#define MATRIX_ROW_PINS { D2, D3, D4, D5, D6, D7 }
#else
#define MATRIX_ROW_PINS { D2, D3, D4, D5, E6, D7 }
#endif
#define MATRIX_COL_PINS { F0, F1, F2, F3, F4, F5, F6, F7, C7, C6, C5, C4, C3, C2, C1, C0, B0, B1, B2, B3, B4, B5, B6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define DYNAMIC_MACRO_COUNT 12
#define DYNAMIC_MACRO_SIZE 48
#define DYNAMIC_MACRO_EEPROM_STORAGE
#define DYNAMIC_MACRO_EEPROM_MAGIC_ADDR (uint16_t*)32
#define DYNAMIC_MACRO_EEPROM_BLOCK0_ADDR (uint8_t*)34
