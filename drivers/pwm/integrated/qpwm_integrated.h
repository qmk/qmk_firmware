// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qpwm_internal.h"

////////////////////////////////////////////////////////////////////
// Quantum PWM configurables (add to your keyboard's config.h)

typedef struct integrated_pwm_device_t {
    pwm_driver_t base;
} integrated_pwm_device_t;
