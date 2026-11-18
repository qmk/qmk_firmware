// Copyright 2025 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdbool.h>
#include "cmk_cm6646.h"

static bool cm6646_enabled = 0;
static bool mic_mute_pressed = 0;
static bool cm6646_enabled_prev = 0;
static bool starting_up = false;

void update_mic_mute_led(void) {
    if (!starting_up) {
        //mic mute is stateful within CM6646, so simply convey the status provided by CM6646 (when enabled)
        if (cm6646_enabled) {
            gpio_write_pin(LED_MIC_MUTE_PIN, (CMK_6646_LED_PIN_ON_STATE == gpio_read_pin(MIC_MUTE_STATE_PIN)));
        }
        else {
            gpio_write_pin(LED_MIC_MUTE_PIN, !CMK_6646_LED_PIN_ON_STATE);
        }
    }
}

void update_mic_mute_control(void) {
    // This function briefly asserts MIC_MUTE_CONTROL_PIN
    // whenever the mic mute keycode is pressed. CM6646
    // has internal debouncing of this pin, so we are just
    // simulating a mechanical key being pressed
    static uint32_t mic_mute_timer = 0;
    static bool mic_mute_in_progress = 0;

    if (mic_mute_in_progress) {
        if (timer_elapsed32(mic_mute_timer) > 40) {
            gpio_write_pin(MIC_MUTE_CONTROL_PIN, 0);
            mic_mute_in_progress = 0;
            mic_mute_pressed = 0;
        }
    }
    else if (mic_mute_pressed) {
        mic_mute_pressed = 0;
        mic_mute_in_progress = 1;
        gpio_write_pin(MIC_MUTE_CONTROL_PIN, 1);
        mic_mute_timer = timer_read32();
    }
}

void update_usb_audio_enable(void) {
    static uint32_t start_up_timer = 0;
    static uint32_t led_flash_counter = 0;
    static bool LED_state = CMK_6646_LED_PIN_ON_STATE;

    gpio_write_pin(USB_AUDIO_ENABLE_PIN, cm6646_enabled);
    if (cm6646_enabled) {
        if (!cm6646_enabled_prev) {
            starting_up = true;
            start_up_timer = timer_read32();
            led_flash_counter = 0;
        }
        if (starting_up == true) {
            if (timer_elapsed32(start_up_timer) > 500) {
                if (led_flash_counter > 8) {
                    starting_up = false;     
                } else {
                    //wait for CM6646 to initialize
                    //flash the mic mute LED while waiting
                    gpio_write_pin(LED_MIC_MUTE_PIN, LED_state);
                    LED_state = !LED_state;
                    start_up_timer = timer_read32();
                    led_flash_counter++;
                }
            }
        }
    }
    else {
        starting_up = false;
        start_up_timer = 0;
        led_flash_counter = 0;
    }
    cm6646_enabled_prev = cm6646_enabled;
}

void process_record_cmk_cm6646(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KB_MIC_MUTE) {
        if (record->event.pressed) {
            mic_mute_pressed = 1;
        }
    }
    else if (keycode == KB_USB_AUDIO_TOGGLE) {
        if (record->event.pressed) {
            cm6646_enabled = !cm6646_enabled;
        }
    }
}

void cmk_cmk6646_init(bool enabled) {
    gpio_set_pin_input(MIC_MUTE_STATE_PIN);
    gpio_set_pin_output(LED_MIC_MUTE_PIN);
    gpio_set_pin_output(MIC_MUTE_CONTROL_PIN);
    gpio_write_pin(MIC_MUTE_CONTROL_PIN, 0);
    gpio_set_pin_output(USB_AUDIO_ENABLE_PIN);


    cm6646_enabled = enabled;
    cm6646_enabled_prev = false;
    update_usb_audio_enable();
}

bool cmk_cmk6646_housekeeping_task(void) {
    update_mic_mute_control();
    update_mic_mute_led();
    update_usb_audio_enable();
    // Return value is enabled state of the CM6646
    return cm6646_enabled;
}
