// Copyright 2026 Andre Brait (@andrebrait)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include <stdbool.h>

#define OS_DETECTION_STORED_SETUPS 50

void nvm_os_detection_erase(void);

bool nvm_os_detection_read_disabled(void);
void nvm_os_detection_update_disabled(bool disabled);

#ifdef OS_DETECTION_BOOT_LOOP_GUARD
void nvm_os_detection_read_boot_loop_guard(uint8_t *count, uint32_t *last_reboot_uptime);
void nvm_os_detection_update_boot_loop_guard(uint8_t count, uint32_t last_reboot_uptime);
#endif // OS_DETECTION_BOOT_LOOP_GUARD

#ifdef OS_DETECTION_DEBUG_ENABLE
uint8_t  nvm_os_detection_read_setup_count(void);
uint8_t  nvm_os_detection_read_setup_reason(void);
uint16_t nvm_os_detection_read_setup(uint8_t index);
void     nvm_os_detection_update_setups(const uint16_t *setups, uint8_t count, uint8_t reason);
#endif // OS_DETECTION_DEBUG_ENABLE
