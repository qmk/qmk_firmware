// Copyright 2026 Andre Brait (@andrebrait)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>

#define OS_DETECTION_STORED_SETUPS 50

void nvm_os_detection_erase(void);

#ifdef OS_DETECTION_DEBUG_ENABLE
uint8_t  nvm_os_detection_read_setup_count(void);
uint16_t nvm_os_detection_read_setup(uint8_t index);
void     nvm_os_detection_update_setups(const uint16_t *setups, uint8_t count);
#endif // OS_DETECTION_DEBUG_ENABLE
