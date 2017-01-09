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
#define EEPROM_VERSION 0x01
#define EEPROM_VERSION_ADDR ((void*)34)

#define EEPROM_BACKLIGHT_CONFIG_ADDR ((void*)35)

// zeal_backlight_config uses 20 bytes
// 35+20=55
#define EEPROM_BACKLIGHT_KEY_COLOR_ADDR ((void*)55)

// key colors use 72*3=216
// 55+216=271

#define EEPROM_KEYMAP_ADDR ((void*)271)
#define EEPROM_KEYMAP_MAX 4

// Each keymap is MATRIX_ROWS*MATRIX_COLS*2 bytes
// For Zeal60 this is 5*14*2=140 bytes
// 4 keymaps = 560 bytes
// 271 + 560 = 831
// 831 < 1024 :-)

bool eeprom_is_valid(void);
void eeprom_set_valid(bool valid);





#endif // ZEAL_EEPROM_H
