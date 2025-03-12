// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include <stdbool.h>

void nvm_dynamic_keymap_erase(void);
void nvm_dynamic_keymap_macro_erase(void);

uint16_t nvm_dynamic_keymap_read_keycode(uint8_t layer, uint8_t row, uint8_t column);
void     nvm_dynamic_keymap_update_keycode(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode);

#ifdef ENCODER_MAP_ENABLE
uint16_t nvm_dynamic_keymap_read_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise);
void     nvm_dynamic_keymap_update_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise, uint16_t keycode);
#endif // ENCODER_MAP_ENABLE

void nvm_dynamic_keymap_read_buffer(uint32_t offset, uint32_t size, uint8_t *data);
void nvm_dynamic_keymap_update_buffer(uint32_t offset, uint32_t size, uint8_t *data);

uint32_t nvm_dynamic_keymap_macro_size(void);

void nvm_dynamic_keymap_macro_read_buffer(uint32_t offset, uint32_t size, uint8_t *data);
void nvm_dynamic_keymap_macro_update_buffer(uint32_t offset, uint32_t size, uint8_t *data);

void nvm_dynamic_keymap_macro_reset(void);
