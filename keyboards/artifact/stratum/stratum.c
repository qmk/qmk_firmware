// Copyright 2026 Yiancar
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void led_init_ports(void) {
    // Set our LED pins as open drain outputs
    gpio_set_pin_output_open_drain(LED_CAPS_LOCK_PIN);
}
