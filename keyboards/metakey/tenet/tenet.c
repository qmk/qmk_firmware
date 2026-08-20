// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tenet.h"
#include "config.h"
#include "quantum.h"
#include "ssd1326.h"
#include "eeconfig.h"
#include <string.h>
#include <ctype.h>

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {  // Key Matrix to LED Index (5 rows × 18 cols)
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, NO_LED, 14, 15, 16 },
        { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, NO_LED, 31, 32, 33 },
        { 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, NO_LED, NO_LED, NO_LED, NO_LED },
        { 48, NO_LED, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, NO_LED, 61, 62, 63 },
        { 64, 65, 66, NO_LED, 67, NO_LED, 68, 69, 70, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 71, 72, 73 },
    },
    {  // LED Index to Physical Position (placeholder — refine after measuring)
        {0,0},{12,0},{24,0},{36,0},{48,0},{60,0},{72,0},{84,0},{96,0},{108,0},{120,0},{132,0},{144,0},{162,0}, {192,0},{204,0},{216,0},
        {0,16},{18,16},{30,16},{42,16},{54,16},{66,16},{78,16},{90,16},{102,16},{114,16},{126,16},{138,16},{150,16},{165,16}, {192,16},{204,16},{216,16},
        {0,32},{21,32},{33,32},{45,32},{57,32},{69,32},{81,32},{93,32},{105,32},{117,32},{129,32},{141,32},{159,32},{174,32},
        {0,48},{27,48},{39,48},{51,48},{63,48},{75,48},{87,48},{99,48},{111,48},{123,48},{135,48},{150,48},{168,48}, {192,48},{204,48},{216,48},
        {0,64},{18,64},{33,64},{72,64},{132,64},{150,64},{168,64}, {192,64},{204,64},{216,64},
    },
    {  // LED Index to Flag
        4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
        4,LED_FLAG_INDICATOR,4,4,4,4,4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,4,4,
    }
};
#endif

/* PA15 is the orientation-detect pin. HIGH = regular, LOW = southpaw (pulled
 * low by the daughterboard's southpaw-side connector). */
tenet_orientation_t tenet_read_orientation(void) {
    gpio_set_pin_input_high(A15);
    wait_us(20);
    return gpio_read_pin(A15) ? TENET_ORIENTATION_REGULAR : TENET_ORIENTATION_SOUTHPAW;
}

/* OLED text: stored in the kb EEPROM datablock as a flat byte run.
 * On read, the first non-printable byte terminates (blank EEPROM reads 0x00
 * on the transient HT32 backend; real EEPROM reads 0xFF). */
static char oled_text[TENET_OLED_TEXT_MAX_LEN + 1];

const char *tenet_oled_text_get(void) { return oled_text; }

void tenet_oled_text_set(const char *text) {
    uint8_t i;
    for (i = 0; i < TENET_OLED_TEXT_MAX_LEN && text[i]; i++) {
        char c = text[i];
        if (c >= 'a' && c <= 'z') c -= 0x20;
        if (c < 0x20 || c > 0x5F) c = ' ';   /* font covers 0x20..0x5F */
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

void keyboard_post_init_kb(void) {
    ssd1326_init();
    load_text_from_eeprom_or_default();
    ssd1326_set_text(oled_text);
    keyboard_post_init_user();
}

/* Hexcore IAP bootloader checks a RAM magic word on reset and stays in IAP
 * mode if it matches. Same convention as Anne Pro 2. */
void bootloader_jump(void) {
    *((volatile uint32_t *)0x20001ffc) = 0x0000fab2;
    __disable_irq();
    NVIC_SystemReset();
}

/* -------- Edit mode (KC_OLED_EDIT) -------- */

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
    if (keycode >= KC_A && keycode <= KC_Z) return 'A' + (keycode - KC_A);  /* uppercase always */
    if (keycode >= KC_1 && keycode <= KC_9) return shift ? "!@#$%^&*("[keycode - KC_1] : '1' + (keycode - KC_1);
    if (keycode == KC_0)    return shift ? ')' : '0';
    if (keycode == KC_SPC)  return ' ';
    if (keycode == KC_MINS) return shift ? '_' : '-';
    if (keycode == KC_EQL)  return shift ? '+' : '=';
    if (keycode == KC_DOT)  return shift ? '>' : '.';
    if (keycode == KC_COMM) return shift ? '<' : ',';
    if (keycode == KC_SLSH) return shift ? '?' : '/';
    return 0;
}

static bool oled_l_held = false;
static bool oled_r_held = false;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    /* 3-key recovery chord: OLED-L + OLED-R held, then ESC → enter IAP. */
    if (keycode == KC_OLED_L) { oled_l_held = record->event.pressed; return false; }
    if (keycode == KC_OLED_R) { oled_r_held = record->event.pressed; return false; }
    if (record->event.pressed && keycode == KC_ESC && oled_l_held && oled_r_held) {
        bootloader_jump();
        return false;
    }

    if (keycode == KC_OLED_EDIT) {
        if (record->event.pressed) {
            if (edit_active) edit_cancel();
            else             edit_enter();
        }
        return false;
    }

    if (edit_active) {
        /* Swallow press AND release while in edit mode so no stray
         * characters leak to the host. */
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
                    if (c >= 'a' && c <= 'z') c -= 0x20;
                    edit_buf[edit_len++] = c;
                    edit_repaint();
                }
            }
        }
        return false;
    }

    return process_record_user(keycode, record);
}
