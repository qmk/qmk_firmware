// SPDX-FileCopyrightText: 2024 TaFahiro Natsume ( @nuovotaFa )
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#include "freeadrs32.h"

#include <string.h>

static const char BL = '\x5F'; // Blank indicator character

knob_t knob = {
    .pressing_keys = { BL, BL, BL, BL, BL, 0 },
};

//////////////////////////////////////////////////////////////////////////////
// Hook points

__attribute__((weak)) void free32knob_on_adjust_layout(free32knob_adjust_t v) {}

//////////////////////////////////////////////////////////////////////////////
// Static utilities

// clip2int8 clips an integer fit into int8_t.
static inline int8_t clip2int8(int16_t v) {
    return (v) < -127 ? -127 : (v) > 127 ? 127 : (int8_t)v;
}

#ifdef OLED_ENABLE

static char to_1x(uint8_t x) {
    x &= 0x0f;
    return x < 10 ? x + '0' : x + 'a' - 10;
}
#endif

//////////////////////////////////////////////////////////////////////////////
// OLED utility

#ifdef OLED_ENABLE
// clang-format off
const char PROGMEM code_to_name[] = {
    'a', 'b', 'c', 'd', 'e', 'f',  'g', 'h', 'i',  'j',
    'k', 'l', 'm', 'n', 'o', 'p',  'q', 'r', 's',  't',
    'u', 'v', 'w', 'x', 'y', 'z',  '1', '2', '3',  '4',
    '5', '6', '7', '8', '9', '0',  'R', 'E', 'B',  'T',
    '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`',
    ',', '.', '/',
};
// clang-format on
#endif

void free32knob_oled_render_keyinfo(void) {
#ifdef OLED_ENABLE
    // Output example:
    // Key
    // 
    // keycode
    //
    // R C 
    // Row Col
    // _____
    // "Key"
    oled_set_cursor(0,5);
    oled_write_P(PSTR("Key  "), false);
    // "keycode"
    oled_write_char(to_1x(knob.last_kc >> 4), false);
    oled_write_char(to_1x(knob.last_kc), false);
    // 改行を入れる
    oled_write_ln_P(PSTR(" "), false);

    // Row and Column
    oled_write_P(PSTR("R C  "), false);
    oled_write_char(to_1x(knob.last_pos.row), false);
    oled_write_P(PSTR(" "), false);
    oled_write_char(to_1x(knob.last_pos.col), false);

    // Pressing keys
    oled_write_P(PSTR("  "), false);
    oled_write(knob.pressing_keys, false);
   // 改行を入れる
    oled_write_ln_P(PSTR(" "), false);
#endif
}

void free32knob_oled_render_layerinfo(void) {
#ifdef OLED_ENABLE
    // Output example:
    // Layer
    //  x
    //
    // 現在のレイヤーを表示する
    oled_write_ln_P(PSTR("Layer"), false);
    char layer_str[12];
    snprintf(layer_str, sizeof(layer_str), "%d", get_highest_layer(layer_state));
    oled_write_ln(layer_str, false);

    // 改行を入れる
    oled_write_ln_P(PSTR(" "), false);
#endif
}

//////////////////////////////////////////////////////////////////////////////
// Keyboard hooks

void keyboard_post_init_kb(void) {
    free32knob_on_adjust_layout(FREE32KNOB_ADJUST_PENDING);
    keyboard_post_init_user();
}

static void pressing_keys_update(uint16_t keycode, keyrecord_t *record) {
    // Process only valid keycodes.
    if (keycode >= 4 && keycode < 57) {
        char value = pgm_read_byte(code_to_name + keycode - 4);
        char where = BL;
        if (!record->event.pressed) {
            // Swap `value` and `where` when releasing.
            where = value;
            value = BL;
        }
        // Rewrite the last `where` of pressing_keys to `value` .
        for (int i = 0; i < FREE32KNOB_OLED_MAX_PRESSING_KEYCODES; i++) {
            if (knob.pressing_keys[i] == where) {
                knob.pressing_keys[i] = value;
                break;
            }
        }
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // store last keycode, row, and col for OLED
    knob.last_kc  = keycode;
    knob.last_pos = record->event.key;

    pressing_keys_update(keycode, record);

    if (!process_record_user(keycode, record)) {
        return false;
    }

    // strip QK_MODS part.
    if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
        keycode &= 0xff;
    }

    return true;
}
