// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "qpwm.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

#ifdef QUANTUM_PWM_DEBUG
#    include <debug.h>
#    include <print.h>
#    define qpwm_dprintf(...) dprintf(__VA_ARGS__)
#else
#    define qpwm_dprintf(...) \
        do {                  \
        } while (0)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Specific internal definitions
#include <qpwm_internal_driver.h>
