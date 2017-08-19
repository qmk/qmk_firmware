#ifndef ZEAL_EEPROM_H
#define ZEAL_EEPROM_H

#include <stdint.h>
#include <stdbool.h>
#include "tmk_core/common/eeprom.h"

#define EEPROM_MAGIC 0x451F
#define EEPROM_MAGIC_ADDR ((void*)32)

// Bump this every time we change what we store
// This will automatically reset the EEPROM with defaults
// and avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x05
#define EEPROM_VERSION_ADDR ((void*)34)

#define EEPROM_BACKLIGHT_CONFIG_ADDR ((void*)35)

// zeal_backlight_config uses 36 bytes
// 35+36=71
#define EEPROM_BACKLIGHT_KEY_COLOR_ADDR ((void*)71)

// key colors use 72*3=216
// 71+216=287

#define EEPROM_KEYMAP_ADDR ((void*)287)
#define EEPROM_KEYMAP_MAX 4

// Each keymap is MATRIX_ROWS*MATRIX_COLS*2 bytes
// For Zeal60 this is 5*14*2=140 bytes
// 4 keymaps = 560 bytes
// 287 + 560 = 847
// 847 < 1024 :-)

// For Zeal65 this is 5*15*2=150 bytes
// 4 keymaps = 600 bytes
// 287 + 600 = 887
// 887 < 1024 :-)

bool eeprom_is_valid(void);
void eeprom_set_valid(bool valid);





#endif // ZEAL_EEPROM_H
