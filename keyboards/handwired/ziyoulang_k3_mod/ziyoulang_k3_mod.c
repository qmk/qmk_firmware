// Copyright 2023 Coom (@coomstoolbox)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include <stdio.h>

void keyboard_post_init_kb(void) {
#ifdef CONSOLE_ENABLE
    debug_enable=true;
    debug_matrix=true;
#endif
    keyboard_post_init_user();
}

static uint16_t last_keycode = KC_NO;
static keypos_t last_key = {0, 0};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
   // コンソールが有効化されている場合、マトリックス上の位置とキー押下状態を出力します
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    if (record->event.pressed) {
        if (last_keycode != keycode) {
            last_keycode = keycode;
            last_key = record->event.key;
        }
    }
    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
#ifdef CONSOLE_ENABLE
    uprintf("Ziyoulang K3 Mod\n");
    oled_set_cursor(3, 0);
    oled_write_P(PSTR("Ziyoulang K3 Mod"), false);
#endif
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    int uptime_seconds = (int)(timer_read32() / 1000);
    if (uptime_seconds < 5) {
        render_logo();
        return false;
    }

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("2\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("3\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    if (led_state.num_lock) {
        oled_write_P(PSTR("NUM"), true);
        oled_write_P(PSTR(" "), false);
    } else {
        oled_write_P(PSTR("    "), false);
    }
    if (led_state.caps_lock) {
        oled_write_P(PSTR("CAP"), true);
        oled_write_P(PSTR(" "), false);
    } else {
        oled_write_P(PSTR("    "), false);
    }
    if (led_state.scroll_lock) {
        oled_write_P(PSTR("SCR"), true);
        oled_write_ln_P(PSTR(" "), false);
    } else {
        oled_write_ln_P(PSTR("    "), false);
    }

    // Last Key pressed info
    oled_write_P(PSTR("kc : "), false);
    if (last_keycode > 21000) {
      oled_write_ln_P(PSTR("    Fn"), false);
    } else {
      oled_write_ln_P(get_u16_str(last_keycode, ' '), false);
    }
    oled_write_P(PSTR("col: "), false);
    oled_write_P(get_u8_str(last_key.col, ' '), false);
    oled_write_P(PSTR(",row: "), false);
    oled_write_P(get_u8_str(last_key.row, ' '), false);

    return false;
}
#endif
