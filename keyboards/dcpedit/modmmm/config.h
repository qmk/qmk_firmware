// Copyright 2023 Ming-Gih Lam (@dcpedit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SOLENOID_PIN A10

#define AUDIO_INIT_DELAY
#define AUDIO_PIN A8
#define AUDIO_PWM_DRIVER PWMD1
#define AUDIO_PWM_CHANNEL 1
#define AUDIO_PWM_PAL_MODE 1
#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_RANDOMNESS 1.5f

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(STARTUP_SOUND)
#endif