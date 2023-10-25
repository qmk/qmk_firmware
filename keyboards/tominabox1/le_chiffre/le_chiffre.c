// Copyright 2020 tominabox1 (@tominabox1)
// Copyright 2019 @foostan
// Copyright 2020 Drashna Jaelre <@drashna>
// Copyright 2023 QMK Contributors <@qmk>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "le_chiffre.h"

#if defined(OLED_ENABLE) // Special thanks to Sickbabies for this great OLED widget!

/* CONSTANTS */
const char PROGMEM code_to_name[53] = {
    'a', 'b', 'c', 'd', 'e', 'f',  'g', 'h', 'i',  'j',
    'k', 'l', 'm', 'n', 'o', 'p',  'q', 'r', 's',  't',
    'u', 'v', 'w', 'x', 'y', 'z',  '1', '2', '3',  '4',
    '5', '6', '7', '8', '9', '0',  'R', 'E', 'B',  'T',
    '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`',
    ',', '.', '/'
};

const char PROGMEM lechiffre_logo[96] = {
    // 'lechiffre_logo', 32x20px
    0x00, 0x3e, 0x20, 0x20, 0x00, 0x18, 0x2c, 0xa8, 0x80, 0x00, 0x1c, 0x22, 0x22, 0x00, 0x3e, 0x08,
    0x30, 0x00, 0x34, 0x00, 0x3c, 0x0a, 0x00, 0xbc, 0x8a, 0x00, 0x38, 0x08, 0x00, 0x18, 0x2c, 0x28,
    0x00, 0xb6, 0xb6, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00,
    0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xb6, 0xb6, 0x00,
    0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00,
    0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00
};

const char PROGMEM oled_section_break[6] = OLED_SECTION_BREAK;
/* END CONSTANTS */

/* TRACKERS */
static char     keylog_str[KEYLOG_LEN] = {};
static uint16_t log_timer              = 0;
/* END TRACKERS */

/* BEGIN STANDARD QMK FUNCTIONS */

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    oled_write_raw_P(lechiffre_logo, sizeof(lechiffre_logo));
    oled_set_cursor(0, 3);
    oled_write_P(oled_section_break, false);
    render_layer_status(get_u8_str(get_highest_layer(layer_state | default_layer_state), ' '));
    oled_write_P(oled_section_break, false);
    render_mod_status(get_mods() | get_oneshot_mods());
    oled_write_P(oled_section_break, false);
    render_keylock_status(host_keyboard_led_state());
    return true;
}

/* END STANDARD QMK FUNCTIONS */
/* BEGIN CUSTOM HELPER FUNCTIONS FOR OLED */

/**
 * Sickbabies deserves credit for the original OLED implementation,
 * however most of the keylogging code appears to have been lifted from crkbd
 * -- which is why @foostan and @drashna are now credited here as well.
 *
 * Improvements were lifted from crkbd again in 2023, with gratitude.
 */
void add_keylog(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_MOD_TAP(keycode) && record->tap.count) {
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    }

    if (keycode >= KC_A && keycode < KC_CAPS) {
        keycode -= KC_A; // shift to first letter of alphabet
        for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
            keylog_str[i] = keylog_str[i - 1];
        }
        keylog_str[0] = pgm_read_byte(&(code_to_name[keycode]));
        keylog_str[KEYLOG_LEN - 1] = 0x00;
    }

    log_timer = timer_read();
}

void render_keylock_status(led_t led_state) {
    oled_write_P(PSTR("C"), led_state.caps_lock);
    oled_advance_char();
    oled_write_P(PSTR("N"), led_state.num_lock);
    oled_advance_char();
    oled_write_P(PSTR("S"), led_state.scroll_lock);
}

void render_keylogger_status(void) {
    // zero out log after 30s idle time
    if (strlen(keylog_str) > 0 && timer_elapsed(log_timer) > 30000) {
        keylog_str[0] = 0x00;
        oled_advance_page(true);
        oled_advance_page(true);
    }
    oled_write(keylog_str, false);
}

void render_layer_status(const char* layer_name) {
    oled_write(layer_name, false);
    if (strlen(layer_name) < oled_max_chars()) {
        oled_advance_page(true);
    }
}

void render_mod_status(uint8_t modifiers) {
    oled_write_ln_P(PSTR("SHFT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_ln_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("CTRL"), (modifiers & MOD_MASK_CTRL));
    oled_write_ln_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
}
#endif // OLED_ENABLE
