// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include <stdbool.h>

void nvm_via_erase(void);

void nvm_via_read_magic(uint8_t *magic0, uint8_t *magic1, uint8_t *magic2);
void nvm_via_update_magic(uint8_t magic0, uint8_t magic1, uint8_t magic2);

uint32_t nvm_via_read_layout_options(void);
void     nvm_via_update_layout_options(uint32_t val);

uint32_t nvm_via_read_custom_config(void *buf, uint32_t offset, uint32_t length);
uint32_t nvm_via_update_custom_config(const void *buf, uint32_t offset, uint32_t length);
