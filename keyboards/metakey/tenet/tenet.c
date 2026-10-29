// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tenet.h"
#include "ssd1326.h"
#include <string.h>

tenet_orientation_t tenet_read_orientation(void) {
    gpio_set_pin_input_high(A15);
    wait_us(20);
    return gpio_read_pin(A15) ? TENET_ORIENTATION_REGULAR : TENET_ORIENTATION_SOUTHPAW;
}

// The transient EEPROM backend reads as 0x00 when unset and real EEPROM as
// 0xFF, so a non-printable first byte means the default text is used.
static char oled_text[TENET_OLED_TEXT_MAX_LEN + 1];

const char *tenet_oled_text_get(void) {
    return oled_text;
}

void tenet_oled_text_set(const char *text) {
    uint8_t i;
    for (i = 0; i < TENET_OLED_TEXT_MAX_LEN && text[i]; i++) {
        char c = text[i];
        if (c >= 'a' && c <= 'z') c -= 0x20;
        if (c < 0x20 || c > 0x5F) c = ' ';
        oled_text[i] = c;
    }
    oled_text[i] = '\0';

    uint8_t eebuf[TENET_OLED_TEXT_MAX_LEN];
    memset(eebuf, 0xFF, sizeof(eebuf));
    memcpy(eebuf, oled_text, i);
    eeconfig_update_kb_datablock(eebuf, 0, sizeof(eebuf));

    ssd1326_set_text(oled_text);
}

static void load_text_from_eeprom_or_default(void) {
    uint8_t eebuf[TENET_OLED_TEXT_MAX_LEN];
    eeconfig_read_kb_datablock(eebuf, 0, sizeof(eebuf));

    if (eebuf[0] < 0x20 || eebuf[0] > 0x7E) {
        strncpy(oled_text, TENET_OLED_TEXT_DEFAULT, TENET_OLED_TEXT_MAX_LEN);
        oled_text[TENET_OLED_TEXT_MAX_LEN] = '\0';
        return;
    }
    uint8_t i;
    for (i = 0; i < TENET_OLED_TEXT_MAX_LEN; i++) {
        uint8_t c = eebuf[i];
        if (c < 0x20 || c > 0x7E) break;
        oled_text[i] = (char)c;
    }
    oled_text[i] = '\0';
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(TENET_LED_IND_L, 255, 255, 255);
        rgb_matrix_set_color(TENET_LED_IND_R, 255, 255, 255);
    }
    return true;
}
#endif

void keyboard_post_init_kb(void) {
    ssd1326_init();
    load_text_from_eeprom_or_default();
    ssd1326_set_text(oled_text);
    keyboard_post_init_user();
}

// The IAP bootloader stays resident after reset when this word is in RAM,
// the same scheme the Anne Pro 2 uses.
void bootloader_jump(void) {
    *((volatile uint32_t *)0x20001ffc) = 0x0000fab2;
    __disable_irq();
    NVIC_SystemReset();
}

static bool    edit_active = false;
static char    edit_buf[TENET_OLED_TEXT_MAX_LEN + 1];
static uint8_t edit_len    = 0;

static void edit_enter(void) {
    edit_active = true;
    edit_len    = 0;
    edit_buf[0] = '\0';
    ssd1326_set_text("EDIT_");
}

static void edit_repaint(void) {
    char display[TENET_OLED_TEXT_MAX_LEN + 2];
    memcpy(display, edit_buf, edit_len);
    display[edit_len]     = '_';
    display[edit_len + 1] = '\0';
    ssd1326_set_text(display);
}

static void edit_commit_and_exit(void) {
    edit_buf[edit_len] = '\0';
    tenet_oled_text_set(edit_buf);
    edit_active = false;
}

static void edit_cancel(void) {
    edit_active = false;
    ssd1326_set_text(oled_text);
}

static char keycode_to_ascii(uint16_t keycode, uint8_t mods) {
    bool shift = mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
    if (keycode >= KC_A && keycode <= KC_Z) return 'A' + (keycode - KC_A);
    if (keycode >= KC_1 && keycode <= KC_9) return shift ? "!@#$%^&*("[keycode - KC_1] : '1' + (keycode - KC_1);
    if (keycode == KC_0) return shift ? ')' : '0';
    if (keycode == KC_SPC) return ' ';
    if (keycode == KC_MINS) return shift ? '_' : '-';
    if (keycode == KC_EQL) return shift ? '+' : '=';
    if (keycode == KC_DOT) return shift ? '>' : '.';
    if (keycode == KC_COMM) return shift ? '<' : ',';
    if (keycode == KC_SLSH) return shift ? '?' : '/';
    return 0;
}

static bool oled_l_held = false;
static bool oled_r_held = false;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Holding both OLED keys and pressing Esc drops into the bootloader.
    if (keycode == KC_OLED_L) {
        oled_l_held = record->event.pressed;
        return false;
    }
    if (keycode == KC_OLED_R) {
        oled_r_held = record->event.pressed;
        return false;
    }
    if (record->event.pressed && keycode == KC_ESC && oled_l_held && oled_r_held) {
        bootloader_jump();
        return false;
    }

    if (keycode == KC_OLED_EDIT) {
        if (record->event.pressed) {
            if (edit_active) {
                edit_cancel();
            } else {
                edit_enter();
            }
        }
        return false;
    }

    // Swallow presses and releases while editing so nothing reaches the host.
    if (edit_active) {
        if (record->event.pressed) {
            if (keycode == KC_ENTER || keycode == KC_PENT) {
                edit_commit_and_exit();
            } else if (keycode == KC_BSPC) {
                if (edit_len > 0) edit_len--;
                edit_repaint();
            } else if (keycode == KC_ESC) {
                edit_cancel();
            } else {
                char c = keycode_to_ascii(keycode, get_mods());
                if (c && edit_len < TENET_OLED_TEXT_MAX_LEN) {
                    edit_buf[edit_len++] = c;
                    edit_repaint();
                }
            }
        }
        return false;
    }

    return process_record_user(keycode, record);
}
