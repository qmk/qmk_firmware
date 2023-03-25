// Copyright 2022-2023 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "m20.h"

void toggle_leds(const bool toggle_lwr, const bool toggle_rse) {
    led_lwr(toggle_lwr);
    led_rse(toggle_rse);
    if (layer_state_is(_ADJ)) {
        led_lwr(true);
        led_rse(true);
    }
}
