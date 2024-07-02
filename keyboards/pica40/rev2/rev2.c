// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rev2.h"
#include "gpio.h"

#ifdef ENCODER_ENABLE // code based on encoder.c

#define ENCODER_PIN_A (((pin_t[])ENCODER_A_PINS)[0])
#define ENCODER_PIN_B (((pin_t[])ENCODER_B_PINS)[0])

// custom handler that returns encoder B pin status from slave side
void encoder_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    *(uint8_t *)out_data = gpio_read_pin(ENCODER_PIN_B) ? 1 : 0;
}

void encoder_quadrature_init_pin(uint8_t index, bool pad_b) {}

uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b) {
    if(pad_b) {
        uint8_t data = 0;
        transaction_rpc_recv(ENCODER_SYNC, sizeof(data), &data);
        return data;
    }
    return gpio_read_pin(ENCODER_PIN_A) ? 1 : 0;
}

#endif // ENCODER_ENABLE

#ifdef PICA40_RGBLIGHT_TIMEOUT
uint16_t check_rgblight_timer = 0;
uint16_t idle_timer = 0;
int8_t counter = 0;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && timer_elapsed(idle_timer) > 1000) {
        idle_timer = timer_read();
        counter = 0;
        if (!rgblight_is_enabled()) {
            rgblight_enable_noeeprom();
        }
    }

    return process_record_user(keycode, record);
}

#endif // PICA40_RGBLIGHT_TIMEOUT

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
uint16_t check_layer_timer = 0;
bool is_layer_active = false;
bool should_set_rgblight = false;
#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

void keyboard_post_init_kb(void) {
    gpio_set_pin_output(PICA40_RGB_POWER_PIN);

#ifdef ENCODER_ENABLE
    gpio_set_pin_input_high(ENCODER_PIN_A);
    gpio_set_pin_input_high(ENCODER_PIN_B);
    transaction_register_rpc(ENCODER_SYNC, encoder_sync_slave_handler);
#endif // ENCODER_ENABLE

#ifdef PICA40_RGBLIGHT_TIMEOUT
    idle_timer = timer_read();
    check_rgblight_timer = timer_read();
    rgblight_enable_noeeprom();
#endif // RGBLIGHT_ENABLE

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    check_layer_timer = timer_read();
#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
#ifdef PICA40_RGBLIGHT_TIMEOUT
    if (is_keyboard_master()) {
        if (timer_elapsed(check_rgblight_timer) > 1000) {
            check_rgblight_timer = timer_read();

            if (rgblight_is_enabled() && timer_elapsed(idle_timer) > 10000) {
                idle_timer = timer_read();
                counter++;
            }

            if (rgblight_is_enabled() && counter > PICA40_RGBLIGHT_TIMEOUT * 6) {
                counter = 0;
                rgblight_disable_noeeprom();
            }
        }
    }
#endif // PICA40_RGBLIGHT_TIMEOUT

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    if (timer_elapsed(check_layer_timer) > 100) {
        check_layer_timer = timer_read();

        if (should_set_rgblight) {
            // set in the next housekeeping cycle after setting pin to avoid issues
            rgblight_set();
            should_set_rgblight = false;
        }

        bool current_is_layer_active = false;
        for (uint8_t i = 0; i < RGBLIGHT_MAX_LAYERS; i++) {
            current_is_layer_active = current_is_layer_active || rgblight_get_layer_state(i);
        }

        if (is_layer_active != current_is_layer_active) {
            is_layer_active = current_is_layer_active;
            should_set_rgblight = true;

            if (is_layer_active) {
                gpio_write_pin_high(PICA40_RGB_POWER_PIN);
            } else {
                gpio_write_pin_low(PICA40_RGB_POWER_PIN);
            }
        }
    }
#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

    housekeeping_task_user();
}
