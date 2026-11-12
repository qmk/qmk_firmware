// Copyright 2026 key10iq
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#define ALARM_LED_PIN C7
#define D3000PC_LED_PIN B11
#define DESKPC_LED_PIN B2

static layer_state_t current_layer_state = 0;

void set_inverted_led_state(uint32_t pin, bool desired_state) {
    gpio_write_pin(pin, !desired_state);
}

// Control LEDs based on the selected layer
void update_layer_leds(void) {
    bool layer1_active = (current_layer_state & (1 << 1)) != 0;
    bool layer2_active = (current_layer_state & (1 << 2)) != 0;
    bool layer3_active = (current_layer_state & (1 << 3)) != 0;
    
    if (layer3_active) {
        set_inverted_led_state(D3000PC_LED_PIN, true);
        set_inverted_led_state(DESKPC_LED_PIN, true);
    } else if (layer2_active) {
        set_inverted_led_state(D3000PC_LED_PIN, false);
        set_inverted_led_state(DESKPC_LED_PIN, true);
    } else if (layer1_active) {
        set_inverted_led_state(D3000PC_LED_PIN, true);
        set_inverted_led_state(DESKPC_LED_PIN, false);
    } else {
        set_inverted_led_state(D3000PC_LED_PIN, false);
        set_inverted_led_state(DESKPC_LED_PIN, false);
    }
}

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output_open_drain(ALARM_LED_PIN);
    gpio_set_pin_output_open_drain(D3000PC_LED_PIN);
    gpio_set_pin_output_open_drain(DESKPC_LED_PIN);

	// Alarm LED is constantly on
    set_inverted_led_state(ALARM_LED_PIN, true);

    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        led_update_ports(led_state);

        update_layer_leds();
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    current_layer_state = state;
    update_layer_leds();
	
    return layer_state_set_user(state);
}
