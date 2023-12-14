// Copyright 2022 Conor Burns (@Conor-Burns)
/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#ifdef AUDIO_ENABLE
#    define AUDIO_PIN GP12
#    define AUDIO_PWM_DRIVER PWMD6
#    define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#    define AUDIO_CLICKY
#endif

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17 // Specify a optional status led which blinks when entering the bootloader
