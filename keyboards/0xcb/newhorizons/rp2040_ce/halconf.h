/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

// Enable PWM for audio driver output
#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE

#include_next <halconf.h>
