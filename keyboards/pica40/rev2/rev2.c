// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rev2.h"

#ifdef ENCODER_ENABLE // code based on encoder.c

static const pin_t encoders_pad_a[] = ENCODERS_PAD_A;
static const pin_t encoders_pad_b[] = ENCODERS_PAD_B;

static int8_t  encoder_LUT[]  = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
static uint8_t encoder_state  = 3;
static int8_t  encoder_pulses = 0;
static uint8_t encoder_value  = 0;

typedef struct encoder_sync_data {
    int value;
} encoder_sync_data;

// custom handler that returns encoder B pin status from slave side
void encoder_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    encoder_sync_data *data = (encoder_sync_data *)out_data;
    data->value = readPin(encoders_pad_b[0]);
}

__attribute__((weak)) bool encoder_update_user(uint8_t index, bool clockwise) {
    return true;
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;

    tap_code(clockwise ? KC_VOLU : KC_VOLD);

    return false;
}

#ifdef ENCODER_MAP_ENABLE
static void encoder_exec_mapping(uint8_t index, bool clockwise) {
    action_exec(clockwise ? ENCODER_CW_EVENT(index, true) : ENCODER_CCW_EVENT(index, true));
    wait_ms(ENCODER_MAP_KEY_DELAY);
    action_exec(clockwise ? ENCODER_CW_EVENT(index, false) : ENCODER_CCW_EVENT(index, false));
    wait_ms(ENCODER_MAP_KEY_DELAY);
}
#endif // ENCODER_MAP_ENABLE

void encoder_init(void) {
    setPinInputHigh(encoders_pad_a[0]);
    setPinInputHigh(encoders_pad_b[0]);
    wait_us(100);
    transaction_register_rpc(ENCODER_SYNC, encoder_sync_slave_handler);
}

bool encoder_read(void) {
    // ignore if running on slave side
    if (!is_keyboard_master()) return false;

    bool changed = false;
    encoder_sync_data data = {0};
    // request pin B status from slave side
    if (transaction_rpc_recv(ENCODER_SYNC, sizeof(data), &data)) {
        uint8_t new_status = (readPin(encoders_pad_a[0]) << 0) | (data.value << 1);
        if ((encoder_state & 0x3) != new_status) {
            encoder_state <<= 2;
            encoder_state |= new_status;
            encoder_pulses += encoder_LUT[encoder_state & 0xF];

            if (encoder_pulses >= ENCODER_RESOLUTION) {
                encoder_value++;
                changed = true;
#ifdef ENCODER_MAP_ENABLE
                encoder_exec_mapping(0, false);
#else  // ENCODER_MAP_ENABLE
                encoder_update_kb(0, false);
#endif // ENCODER_MAP_ENABLE
            }

            if (encoder_pulses <= -ENCODER_RESOLUTION) {
                encoder_value--;
                changed = true;
#ifdef ENCODER_MAP_ENABLE
                encoder_exec_mapping(0, true);
#else  // ENCODER_MAP_ENABLE
                encoder_update_kb(0, true);
#endif // ENCODER_MAP_ENABLE
            }

            encoder_pulses %= ENCODER_RESOLUTION;
        }
    }
    return changed;
}

// do not use standard split encoder transactions
void encoder_state_raw(uint8_t *slave_state) {}
void encoder_update_raw(uint8_t *slave_state) {}

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
    setPinOutput(PICA40_RGB_POWER_PIN);

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
                writePinHigh(PICA40_RGB_POWER_PIN);
            } else {
                writePinLow(PICA40_RGB_POWER_PIN);
            }
        }
    }
#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)

    housekeeping_task_user();
}
