// Copyright 2025 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#pragma once

#ifndef CMK_CM6646_KEYCODES_START
#    define CMK_CM6646_KEYCODES_START QK_KB_0
#endif

#ifndef CMK_CM6646_KEYCODES_END
#    define CMK_CM6646_KEYCODES_END QK_KB_2
#endif

#define CMK_CM6646_NUM_KEYCODES 2

#ifndef LED_MIC_MUTE_PIN
#    define LED_MIC_MUTE_PIN B13
#endif

#ifndef MIC_MUTE_STATE_PIN
#    define MIC_MUTE_STATE_PIN B9
#endif

#ifndef MIC_MUTE_CONTROL_PIN
#    define MIC_MUTE_CONTROL_PIN A0
#endif

#ifndef USB_AUDIO_ENABLE_PIN
#    define USB_AUDIO_ENABLE_PIN B6
#endif

#ifndef CMK_6646_LED_PIN_ON_STATE
#    define CMK_6646_LED_PIN_ON_STATE 0
#endif

enum cmk_cm6646_keycodes {
    KB_MIC_MUTE = CMK_CM6646_KEYCODES_START,
    KB_USB_AUDIO_TOGGLE
};

void process_record_cmk_cm6646(uint16_t keycode, keyrecord_t *record);
void cmk_cmk6646_init(bool enabled);
bool cmk_cmk6646_housekeeping_task(void);
