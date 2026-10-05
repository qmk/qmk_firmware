// Copyright 2026 doombadroid (@doombadroid)
// SPDX-License-Identifier: GPL-2.0-or-later

// DIP switches on the underside: wired between PE9 and matrix rows 0-3 (PD0 PD8 PD9 PD1). Stock reads them by
// driving PE9 low with the rows as pulled-up inputs (V1.15 @0x9b8x). QMK leaves idle rows as pulled-up inputs,
// so PE9 is only pulsed low for the read and released again: held low, an ON switch would pull its row low and
// every key pressed in that row would ghost into the others.
#include "quantum.h"
#ifdef VIA_ENABLE
#    include "via.h"
#endif

#ifndef DIP_ON_LEVEL
#    define DIP_ON_LEVEL 0 // row level read for a switch in the ON position
#endif

static const pin_t dip_rows[4] = {D0, D8, D9, D1}; // DIP1..4 = matrix rows 0..3
static uint8_t     dip_raw     = 0xFF;             // bit n: row level for DIP n+1; 0xFF = not read yet
static uint8_t     dip_on;                         // bit n: DIP n+1 is ON

static uint8_t dip_read_raw(void) {
    uint8_t raw = 0;
    gpio_set_pin_output(E9);
    gpio_write_pin_low(E9);
    wait_us(1);
    for (uint8_t i = 0; i < 4; i++) {
        raw |= gpio_read_pin(dip_rows[i]) << i;
    }
    gpio_set_pin_input(E9);
    wait_us(10); // rows pulled low by an ON switch recover through their weak pull-up before the next scan
    return raw;
}

// Stock functions (manual p. 28): DIP1 ON disables the Win-key lock, DIP2 ON selects 6KRO instead of NKRO,
// DIP3 (Ducky/user VID) has no QMK equivalent and is unused, DIP4 ON turns Right Win into Menu.
static void dip_apply(uint8_t changed) {
    if (changed & (1 | 2 | 8)) clear_keyboard(); // no keys left held across a report-mode or keycode change
    if ((changed & 1) && (dip_on & 1)) keymap_config.no_gui = false;
    if (changed & 2) keymap_config.nkro = !(dip_on & 2);
}

void matrix_scan_kb(void) {
    static uint16_t last;
    if (timer_elapsed(last) >= 20) {
        last        = timer_read();
        uint8_t raw = dip_read_raw();
        if (raw != dip_raw) {
            uint8_t on      = (DIP_ON_LEVEL ? raw : ~raw) & 0xF;
            uint8_t changed = dip_raw == 0xFF ? 0xF : (on ^ dip_on);
            dip_raw         = raw;
            dip_on          = on;
            dip_apply(changed);
        }
    }
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) return false;
    if ((dip_on & 1) && (keycode == GU_TOGG || keycode == GU_ON)) return false;
    if ((dip_on & 8) && keycode == KC_RGUI) {
        if (record->event.pressed) {
            register_code(KC_APP);
        } else {
            unregister_code(KC_APP);
        }
        return false;
    }
    return true;
}

#ifdef VIA_ENABLE
// VIA custom channel 0, value 1 (read only): raw DIP row levels, bit n = DIP n+1.
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    if (data[0] == id_custom_get_value && data[1] == id_custom_channel && data[2] == 1) {
        data[3] = dip_raw;
        return;
    }
    data[0] = id_unhandled;
}
#endif
