// Copyright 2023 Persama (@Persama)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "ansi.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
    if (!process_record_user(keycode, record)) {
        return false;
    }
{
    switch (keycode) {
        case MAC_SEARCH:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_SPACE);
                wait_ms(50);
                unregister_code(KC_LGUI);
                unregister_code(KC_SPACE);
            }
            return false;
        case MAC_VOICE:
            if (record->event.pressed) {
                host_consumer_send(0xcf);
            } else {
                host_consumer_send(0);
            }
            return false;
        case MAC_PRT:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                register_code(KC_3);
                wait_ms(50);
                unregister_code(KC_3);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            }
            return false;
        case MAC_PRTA:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                register_code(KC_4);
                wait_ms(50);
                unregister_code(KC_4);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            }
            return false;
        default:
            return true;
    }
}

void dial_sw_scan(void)
{
    static uint8_t dial_scan = 0;
    static uint8_t dial_save = 0xff;
    static uint32_t dial_scan_timer = 0;

    // 20ms扫描间隔
    if (timer_elapsed32(dial_scan_timer) < 50) return;
    dial_scan_timer = timer_read32();  // store time of last refresh

    dial_scan = readPin(SYS_MODE_PIN);
    if (dial_scan != dial_save) {
        if (dial_scan) {
            default_layer_set(1 << 0);  // MAC
            keymap_config.nkro = 0;
        } else {
            default_layer_set(1 << 2);  // WIN
            keymap_config.nkro = 1;
        }
    }
    dial_save = dial_scan;
}

void keyboard_post_init_kb(void)
{
    setPinOutput(DRIVER_LED_CS_PIN);
    setPinOutput(DC_BOOST_PIN);
    setPinInputHigh(SYS_MODE_PIN);

    writePinLow(DRIVER_LED_CS_PIN);
    writePinHigh(DC_BOOST_PIN);

    keyboard_post_init_user();
}

void housekeeping_task_kb(void)
{
    dial_sw_scan();
    housekeeping_task_user();
}