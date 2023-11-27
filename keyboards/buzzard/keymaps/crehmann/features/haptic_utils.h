// Copyright 2021 Christoph Rehmann (crehmann)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record);

void process_layer_pulse(layer_state_t state);