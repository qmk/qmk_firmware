/*
 * keymaps.c QMK keymap for BitDeck10
 * Copyright (C) 2026 morisoba
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

enum layers { _BASE, _LOWER, _RAISE, _ADJUST };

#ifdef ENCODER_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    // Volume UP/DOWN
    [_BASE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LOWER]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_RAISE]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_ADJUST] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
};
#endif // ENCODER_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* For Text
     *                                     ┌────────┐
     *                                     │  MUTE  │
     * ┌────────┬────────┬────────┬────────┼────────┤
     * │  COPY  │ PASTE  │  UNDO  │  REDO  │_ADJUST │
     * ├────────┼────────┼────────┼────────┼────────┤
     * │SEL_ALL │SEL_WORD│ ←WORD  │ WORD→  │ _LOWER │
     * └────────┴────────┴────────┴────────┴────────┘
     */
    [_BASE] = LAYOUT(KC_MUTE,
        C(KC_C),        C(KC_V),        C(KC_Z),        C(KC_Y),        TO(_ADJUST),
        C(KC_A),        LCS(KC_RGHT),   C(KC_LEFT),     C(KC_RIGHT),    TO(_LOWER)),

    /* For Browser
     *                                     ┌────────┐
     *                                     │  MUTE  │
     * ┌────────┬────────┬────────┬────────┼────────┤
     * │REFRESH │  URL   │ BACK   │  FWD   │ _BASE  │
     * ├────────┼────────┼────────┼────────┼────────┤
     * │ NewTab │CloseTab│  ←TAB  │  TAB→  │ _RAISE │
     * └────────┴────────┴────────┴────────┴────────┘
     */
    [_LOWER] = LAYOUT(KC_MUTE,
        KC_WREF,        C(KC_R),        KC_WBAK,        KC_WFWD,        TO(_BASE),
        C(KC_T),        C(KC_W),        LCS(KC_LEFT),   LCS(KC_RIGHT),  TO(_RAISE)
    ),

    /* For YouTube
     *                                     ┌────────┐
     *                                     │  MUTE  │
     * ┌────────┬────────┬────────┬────────┼────────┤
     * │  PLAY  │MiniPlay│ -5sec  │ +5sec  │ _LOWER │
     * ├────────┼────────┼────────┼────────┼────────┤
     * │SubTitle│FullScrn│SpdDown │ SpdUp  │_ADJUST │
     * └────────┴────────┴────────┴────────┴────────┘
     */
    [_RAISE] = LAYOUT(KC_MUTE,
        KC_MPLY,        KC_I,           KC_LEFT,        KC_RIGHT,       TO(_LOWER),
        KC_C,           KC_F,           S(KC_COMM),     S(KC_DOT),      TO(_ADJUST)
    ),

    /* For Excel
     *                                     ┌────────┐
     *                                     │  MUTE  │
     * ┌────────┬────────┬────────┬────────┼────────┤
     * │ COPY   │ PASTE  │  UNDO  │  REDO  │ _RAISE │
     * ├────────┼────────┼────────┼────────┼────────┤
     * │AUTOSUM*│PASTE_V │ ←SHEET │ SHEET→ │ _BASE  │
     * └────────┴────────┴────────┴────────┴────────┘
     * * AUTOSUM is set for Japanese keymap.
     */
    [_ADJUST] = LAYOUT(KC_MUTE,
        C(KC_C),        C(KC_V),        C(KC_Z),        C(KC_Y),        TO(_RAISE),
        LSA(JP_MINS),   LCS(KC_V),      C(KC_PGDN),     C(KC_PGUP),     TO(_BASE)
    )
};


#ifdef OLED_ENABLE
#define OLED_ENCODER_TIMEOUT 200
#define KEYSTR_MAX_LEN 25
#define KEYDISPLAY_LEN 15 // 128dots / 6dots(1char) - 5chars(keystatus)
#define KEYLOG_LEN 32

#ifdef ENCODER_ENABLE
// record encoder status
typedef enum { ENC_NONE = 0, ENC_UP = 1, ENC_DOWN = 2 } encoder_state_t;
static encoder_state_t encoder_state      = ENC_NONE;
static uint32_t        last_encoder_moved = 0;
#endif // ENCODER_ENABLE

// keylogger
typedef struct {
    keyevent_t event;
    char       keystr[KEYSTR_MAX_LEN];
} keylog_t;

static keylog_t keylog[KEYLOG_LEN]                                = {0};
static char     keyhistory[KEYSTR_MAX_LEN * (KEYDISPLAY_LEN + 1)] = {0};

// for keylog sort
static int keylog_compare(const void *a, const void *b) {
    if (((keylog_t *)a)->event.time > ((keylog_t *)b)->event.time) {
        return 1;
    } else if (((keylog_t *)a)->event.time < ((keylog_t *)b)->event.time) {
        return -1;
    } else {
        return 0;
    }
}

static void write_keylog(keyevent_t event, const char *keystr) {
    if (event.pressed) {
#ifdef ENCODER_ENABLE
        if (event.key.row == KEYLOC_ENCODER_CW) {
            encoder_state      = ENC_UP;
            last_encoder_moved = timer_read32();
        } else if (event.key.row == KEYLOC_ENCODER_CCW) {
            encoder_state      = ENC_DOWN;
            last_encoder_moved = timer_read32();
        }
#endif // ENCODER_ENABLE
        for (uint8_t idx = 0; idx < KEYLOG_LEN; idx++) {
            if (keylog[idx].event.pressed == false) {
                keylog[idx].event = event;
                snprintf(keylog[idx].keystr, KEYSTR_MAX_LEN, "%s", keystr);
                break;
            }
        }
    } else {
#ifdef ENCODER_ENABLE
        if (event.key.row != KEYLOC_ENCODER_CW && event.key.row != KEYLOC_ENCODER_CCW) {
#endif // ENCODER_ENABLE
            for (uint8_t idx = 0; idx < KEYLOG_LEN; idx++) {
                if (keylog[idx].event.key.row == event.key.row && keylog[idx].event.key.col == event.key.col && keylog[idx].event.pressed == true) {
                    keylog[idx].event = event;
                    break;
                }
            }
#ifdef ENCODER_ENABLE
        }
#endif // ENCODER_ENABLE
    }
}

static void create_keyhistory(void) {
    qsort(keylog, KEYLOG_LEN, sizeof(keylog_t), keylog_compare);
    keyhistory[0] = '\0';
    for (uint8_t idx = 0; idx < KEYLOG_LEN; idx++) {
        if (keylog[idx].event.pressed) {
            strcat(keyhistory, keylog[idx].keystr);
            strcat(keyhistory, " ");
        }
    }
    for (uint8_t ptr = strlen(keyhistory); ptr < KEYDISPLAY_LEN; ptr++) {
        keyhistory[ptr] = ' ';
    }
    keyhistory[KEYDISPLAY_LEN] = '\0';
}

#ifdef ENCODER_ENABLE
static void delete_encoder_log(void) {
    for (uint8_t idx = 0; idx < KEYLOG_LEN; idx++) {
        if (keylog[idx].event.key.row == KEYLOC_ENCODER_CW || keylog[idx].event.key.row == KEYLOC_ENCODER_CCW) {
            if (keylog[idx].event.pressed == true && (timer_elapsed32(last_encoder_moved) > OLED_ENCODER_TIMEOUT)) {
                keylog[idx].event.pressed = false;
            }
        }
    }
}
#endif // ENCODER_ENABLE

static void render_logo(void) {
    static const char PROGMEM bitdeck_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0xFF, 0xFF,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xFF, 0xFF, 0x00};
    oled_write_P(bitdeck_logo, false);
}

// drawing OLED
bool oled_task_user(void) {
    // show logo
    render_logo();

#ifdef ENCODER_ENABLE
    delete_encoder_log();
#endif // ENCODER_ENABLE
    create_keyhistory();

    // phisycal-electric key matrix relation; encoder = [0], sw1 = [1], sw2 = [2],...and so on
    uint8_t sw_row[11] = {3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1}; // row
    uint8_t sw_col[11] = {4, 1, 1, 1, 1, 2, 2, 2, 2, 4, 4}; // column bitmask

    // show key status
    oled_set_cursor(0, 2); // for upper row
    for (uint8_t offset = 1; offset <= 6; offset += 5) {
        for (uint8_t sw = offset; sw < offset + 5; sw++) {
            matrix_row_t row_state = matrix_get_row(sw_row[sw]);
            if (row_state & sw_col[sw]) {
                oled_write_P(PSTR("\xC1"), false); // key pressed
            } else {
                oled_write_P(PSTR("\xC0"), false);
            }
        }
        oled_set_cursor(0, 3); // for lower row
    }

#ifdef ENCODER_ENABLE
    // OLED status clear
    if (timer_elapsed32(last_encoder_moved) > OLED_ENCODER_TIMEOUT) {
        encoder_state = ENC_NONE;
    }
    // get OLED push button status
    bool pushed = matrix_get_row(sw_row[0]) & sw_col[0];
    // show encoder status
    oled_set_cursor(5, 2);
    switch (encoder_state) {
        case ENC_UP:
            oled_write_P(pushed ? PSTR("\xC6") : PSTR("\xC3"), false);
            break;
        case ENC_DOWN:
            oled_write_P(pushed ? PSTR("\xC7") : PSTR("\xC4"), false);
            break;
        default:
            oled_write_P(pushed ? PSTR("\xC5") : PSTR("\xC2"), false);
    }
#endif // ENCODER_ENABLE

    // show layer
    oled_set_cursor(7, 2);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("BASE     "), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER    "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE    "), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJUST   "), false);
            break;
        case 4:
            oled_write_P(PSTR("LAYER_A  "), false);
            break;
        case 5:
            oled_write_P(PSTR("LAYER_B  "), false);
            break;
        case 6:
            oled_write_P(PSTR("LAYER_C  "), false);
            break;
        default:
            char buf[KEYDISPLAY_LEN];
            snprintf(buf, sizeof(buf), "LAYER%02d  ", get_highest_layer(layer_state));
            oled_write(buf, false);
    }

    // show keycode
    oled_set_cursor(6, 3);
    oled_write(keyhistory, false);
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    write_keylog(record->event, get_keycode_string(keycode));
    return true;
}

#endif // OLED_ENABLE
