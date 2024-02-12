// Copyright 2023 John Barbero Unenge (@jbarberu)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

// oled keylog rendering has been kindly borrowed from crkbd <3

char     key_name = ' ';
uint16_t last_keycode;
uint8_t  last_row;
uint8_t  last_col;

static const char PROGMEM code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

static void set_keylog(uint16_t keycode, keyrecord_t *record) {
    last_row = record->event.key.row;
    last_col = record->event.key.col;

    key_name     = ' ';
    last_keycode = keycode;
    if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count) {
          keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        } else {
          keycode = 0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) + biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10);
        }
    } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
        keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
    }
    if (keycode > ARRAY_SIZE(code_to_name)) {
        return;
    }

    // update keylog
    key_name = pgm_read_byte(&code_to_name[keycode]);
}

static const char *depad_str(const char *depad_str, char depad_char) {
    while (*depad_str == depad_char) {
        ++depad_str;
    }
    return depad_str;
}

static void oled_render_keylog(void) {
    oled_write_char('0' + last_row, false);
    oled_write("x", false);
    oled_write_char('0' + last_col, false);
    oled_write(", k", false);
    const char *last_keycode_str = get_u16_str(last_keycode, ' ');
    oled_write(depad_str(last_keycode_str, ' '), false);
    oled_write(":", false);
    oled_write_char(key_name, false);
}

__attribute__((weak)) const char * get_layer_name_user(uint8_t layer) {
    return get_u8_str(layer, ' ');
}

static void oled_render_layer(void) {
    oled_write("Layer: ", false);
    oled_write_ln(get_layer_name_user(get_highest_layer(layer_state)), false);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    oled_render_layer();
    oled_render_keylog();
    oled_advance_page(true);
    return false;
}

static void setupForFlashing(void) {
    oled_clear();
    oled_write("                     ", false);
    oled_write("  In flash mode...   ", false);
    oled_write("                     ", false);
    oled_write("                     ", false);

    // Force data to be rendered
    oled_render_dirty(true);

    // Set alternating backlight colors
    const uint8_t max = 20;
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    for (size_t i = 0; i < RGBLED_NUM; ++i) {
        rgb_led_t *led_ = (rgb_led_t *)&led[i];
        switch (i % 2) {
            case 0:
                setrgb(max, 0, max, led_);
                break;
            case 1:
                setrgb(0, max, max, led_);
                break;
        }
    }
    rgblight_set();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    if (keycode == QK_BOOT) {
        setupForFlashing();
    }
    return process_record_user(keycode, record);
}

void keyboard_post_init_kb(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_MAGENTA);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
    keyboard_post_init_user();
}
