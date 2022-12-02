// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rev2.h"
#include "quantum.h"
#include "gpio.h"

#ifdef PICA40_ENCODER_SYNC_ENABLE

typedef struct encoder_sync_data {
    int value;
} encoder_sync_data;

static int8_t  encoder_LUT[]  = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
static uint8_t encoder_state  = 3;
static int8_t  encoder_pulses = 0;
static uint8_t encoder_value  = 0;

void encoder_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    encoder_sync_data *data = (encoder_sync_data *)out_data;
    data->value = readPin(PICA40_ENCODER_PIN);
}

#endif // PICA40_ENCODER_SYNC_ENABLE

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

void suspend_wakeup_init_kb(void) {
    rgblight_enable_noeeprom();

    suspend_wakeup_init_user();
}

void suspend_power_down_kb(void) {
    rgblight_disable_noeeprom();

    suspend_power_down_user();
}
#endif // PICA40_RGBLIGHT_TIMEOUT

#ifdef RGBLIGHT_LAYERS
uint16_t check_layer_timer = 0;
bool is_layer_active = false;
bool should_set_rgblight = false;
#endif // RGBLIGHT_LAYERS

void keyboard_post_init_kb(void) {
    setPinOutput(PICA40_RGB_POWER_PIN);

#ifdef PICA40_ENCODER_SYNC_ENABLE
    setPinInputHigh(PICA40_ENCODER_PIN);
    transaction_register_rpc(ENCODER_SYNC, encoder_sync_slave_handler);
#endif // PICA40_ENCODER_SYNC_ENABLE

#ifdef PICA40_RGBLIGHT_TIMEOUT
    idle_timer = timer_read();
    check_rgblight_timer = timer_read();
    rgblight_enable_noeeprom();
#endif // RGBLIGHT_ENABLE

#ifdef RGBLIGHT_LAYERS
    check_layer_timer = timer_read();
#endif // RGBLIGHT_LAYERS

    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
#ifdef PICA40_ENCODER_SYNC_ENABLE
        encoder_sync_data data = {0};
        if (transaction_rpc_recv(ENCODER_SYNC, sizeof(data), &data)) {
            uint8_t new_status = (readPin(PICA40_ENCODER_PIN) << 0) | (data.value << 1);
            if ((encoder_state & 0x3) != new_status) {
                encoder_state <<= 2;
                encoder_state |= new_status;
                encoder_pulses += encoder_LUT[encoder_state & 0xF];

                if (encoder_pulses >= ENCODER_RESOLUTION) {
                    encoder_value++;
                    encoder_update_user(0, false);
                }

                if (encoder_pulses <= -ENCODER_RESOLUTION) {
                    encoder_value--;
                    encoder_update_user(0, true);
                }

                encoder_pulses %= ENCODER_RESOLUTION;
            }
        }
#endif // PICA40_ENCODER_SYNC_ENABLE

#ifdef PICA40_RGBLIGHT_TIMEOUT
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
#endif // PICA40_RGBLIGHT_TIMEOUT
    }

#ifdef RGBLIGHT_LAYERS
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
                writePinHigh(PICA40_RGB_POWER_PIN);
            } else {
                writePinLow(PICA40_RGB_POWER_PIN);
            }
        }
    }
#endif // RGBLIGHT_LAYERS

    housekeeping_task_user();
}
