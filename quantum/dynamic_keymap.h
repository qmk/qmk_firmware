#ifndef DYNAMIC_KEYMAP_H
#define DYNAMIC_KEYMAP_H

#include <stdint.h>
#include <stdbool.h>

#include "zeal_keycode.h"

void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column);
uint16_t dynamic_keymap_keycode_load(uint8_t layer, uint8_t row, uint8_t column);
void dynamic_keymap_keycode_save(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode);
void dynamic_keymap_default_save(void);

// This overrides the one in quantum/keymap_common.c
// uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);

#endif //DYNAMIC_KEYMAP_H
