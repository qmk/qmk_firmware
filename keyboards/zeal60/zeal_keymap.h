#ifndef ZEAL_KEYMAP_H
#define ZEAL_KEYMAP_H

#include <stdint.h>
#include <stdbool.h>

#include "zeal_keycode.h"

void *keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column);
uint16_t keymap_keycode_load(uint8_t layer, uint8_t row, uint8_t column);
void keymap_keycode_save(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode);
void keymap_default_save(void);

// This overrides the one in quantum/keymap_common.c
// uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);

#endif //ZEAL_EEPROM_H
