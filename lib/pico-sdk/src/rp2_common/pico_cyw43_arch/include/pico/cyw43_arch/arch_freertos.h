/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_CYW43_ARCH_ARCH_FREERTOS_H
#define _PICO_CYW43_ARCH_ARCH_FREERTOS_H

// PICO_CONFIG: CYW43_TASK_STACK_SIZE, Stack size for the CYW43 FreeRTOS task in 4-byte words, type=int, default=1024, group=pico_cyw43_arch
#ifndef CYW43_TASK_STACK_SIZE
#define CYW43_TASK_STACK_SIZE 1024
#endif

// PICO_CONFIG: CYW43_TASK_PRIORITY, Priority for the CYW43 FreeRTOS task, type=int default=4, group=pico_cyw43_arch
#ifndef CYW43_TASK_PRIORITY
#define CYW43_TASK_PRIORITY (tskIDLE_PRIORITY + 4)
#endif

#endif
