// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SOLENOID_PIN B3
#define HAPTIC_ENABLE_PIN A15
#define SOLENOID_DEFAULT_DWELL 4
#define SOLENOID_MIN_DWELL 4
#define SOLENOID_MAX_DWELL 45
#define HAPTIC_OFF_IN_LOW_POWER 1
#define NO_HAPTIC_MOD

#define AUDIO_CLICKY
#define AUDIO_PIN A6
#define AUDIO_PWM_DRIVER PWMD3
#define AUDIO_PWM_CHANNEL 1
#define AUDIO_STATE_TIMER GPTD4
#define AUDIO_PIN_ALT_AS_NEGATIVE
#define AUDIO_PIN_ALT A13
#define DEFAULT_LAYER_SONGS { \
                              SONG(CAPS_LOCK_ON_SOUND), \
                              SONG(CAPS_LOCK_OFF_SOUND), \
                              SONG(NUM_LOCK_ON_SOUND), \
                              SONG(NUM_LOCK_OFF_SOUND), \
                              SONG(SCROLL_LOCK_ON_SOUND), \
                              SONG(SCROLL_LOCK_OFF_SOUND) \
                            }
