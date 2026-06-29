// Copyright 2021 Colin Lam (Ploopy Corporation)
// Copyright 2026 HorrorTroll <https://github.com/HorrorTroll>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "pointing_device.h"

#ifndef PMW3325_CS_PIN
#    ifdef POINTING_DEVICE_CS_PIN
#        define PMW3325_CS_PIN POINTING_DEVICE_CS_PIN
#    else
#        error "No chip select pin defined -- missing POINTING_DEVICE_CS_PIN or PMW3325_CS_PIN define"
#    endif
#endif

#ifndef PMW3325_SPI_DIVISOR
#    error "No PMW3325 SPI divisor defined -- missing PMW3325_SPI_DIVISOR"
#endif

typedef struct {
    int16_t dx;
    int16_t dy;
} report_pmw3325_t;

extern const pointing_device_driver_t pmw3325_pointing_device_driver;

bool             pmw3325_init(void);
report_pmw3325_t pmw3325_read_burst(void);
void             pmw3325_set_cpi(uint16_t cpi);
uint16_t         pmw3325_get_cpi(void);
report_mouse_t   pmw3325_get_report(report_mouse_t mouse_report);
bool             pmw3325_check_signature(void);

#if !defined(PMW3325_CPI)
#    define PMW3325_CPI 2000
#endif

#define PMW3325_CPI_MIN 100
#define PMW3325_CPI_MAX 5000
#define PMW3325_CPI_STEP 100
#define CONSTRAIN(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
