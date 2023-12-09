/* Copyright 2017 Colin T.A. Gray
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef IS_COLINTA
#include "secrets.h"
#else
#define SENDSTRING_MM0 ""
#define SENDSTRING_MM1 ""
#define SENDSTRING_MM2 ""
#endif

// layers:
// - colemak,
// - record-mode (adds stop buttons)
// - qwerty
// - fn (recording, changing layers)
#define LAYER_COLEMAK 0
#define LAYER_RECORD 1
#define LAYER_QWERTY 2
#define LAYER_FN 3

// custom keys:
// - goto layer keys
#define GOTO_FN TT(LAYER_FN)
#define GOTO_CM TO(LAYER_COLEMAK)
#define GOTO_QW TO(LAYER_QWERTY)
// - sticky keys, aka one-shot
#define OSCTL OSM(MOD_LCTL)
#define OSALT OSM(MOD_LALT)
#define OSSFT OSM(MOD_LSFT)
#define OSGUI OSM(MOD_LGUI)
// "MMENU" is a macro for "CMD+SPC" (aka Spotlight/Alfred)
#define MMENU LGUI(KC_SPC)
#define _____ KC_TRNS
#define MM_0 DM_PLY1
#define MM_1 DM_PLY2

// tap-hold settings
#define LONGPRESS_DELAY 250
#define TH_EVENTS_COUNT 13

enum my_keycods {
    TH_M0 = SAFE_RANGE,
    TH_M1,
    TH_M2,
    TH_F1,
    TH_F2,
    TH_F3,
    TH_F4,
    TH_F5,
    TH_F6,
    TH_F7,
    TH_F8,
    TH_F9,
    TH_F10,
    TH_LAST,
    MM_2,
    DM_CLEAR,
    DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | M(0)   | M(1)   | DEL    | 6      | 7      | 8      | 9      | 0      | -      |
 * |--------+-/F1----+-/F2----+-/F3----+-/F4----+-/F5----+--------+--------+--------+-/F6----+-/F7----+-/F8----+-/F9----+-/F10---+--------|
 * | TAB    | Q      | W      | F      | P      | G      | M(2)   |  (FN)  | BKSP   | J      | L      | U      | Y      | ;      | =      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | SHIFT  | A      | R      | S      | T      | D      | [      | ]      | ENTER  | H      | N      | E      | I      | O      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | CTRL   | Z      | X      | C      | V      | B      | HOME   | END    | PG UP  | K      | M      | ,      | .      | /      | \      |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | VOL-   | PLAY   | VOL+   | ALT    | GUI    |          SPACE           | PG DN  | MENU   | ESC    | LEFT   | DOWN   | UP     | RIGHT  |
 * '--/RRND----/MUTE----/FFWD-------------------------------------------------------------------------------------------------------------'
 */

  [LAYER_COLEMAK] = LAYOUT(
    KC_GRV, TH_F1, TH_F2, TH_F3, TH_F4, TH_F5,  MM_0,    MM_1,    KC_DEL,  TH_F6, TH_F7,  TH_F8,   TH_F9,   TH_F10,  KC_MINS,
    KC_TAB, KC_Q,  KC_W,  KC_F,  KC_P,  KC_G,   MM_2,    GOTO_FN, KC_BSPC, KC_J,  KC_L,   KC_U,    KC_Y,    KC_SCLN, KC_EQL,
    OSCTL,  KC_A,  KC_R,  KC_S,  KC_T,  KC_D,   KC_LBRC, KC_RBRC, KC_ENT,  KC_H,  KC_N,   KC_E,    KC_I,    KC_O,    KC_QUOT,
    OSSFT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,   KC_HOME, KC_END,  KC_PGUP, KC_K,  KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
    TH_M0,  TH_M1,  TH_M2, OSALT, OSGUI, _____ , KC_SPC,  _____ ,  KC_PGDN, MMENU, KC_ESC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

/* DYN_REC LAYER - recording tap/hold keys is possible, but they will always "tap" (macros don't record holding duration)
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |  STOP  |  STOP  |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |  STOP  |  STOP  |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |                          |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [LAYER_RECORD] = LAYOUT(
    _____, _____, _____, _____, _____, _____, DM_RSTP, DM_RSTP, _____, _____, _____, _____, _____, _____, _____,
    _____, _____, _____, _____, _____, _____, DM_RSTP, DM_RSTP, _____, _____, _____, _____, _____, _____, _____,
    _____, _____, _____, _____, _____, _____,    _____,        _____,     _____, _____, _____, _____, _____, _____, _____,
    _____, _____, _____, _____, _____, _____,    _____,        _____,     _____, _____, _____, _____, _____, _____, _____,
    _____, _____, _____, _____, _____, _____,    _____,        _____,     _____, _____, _____, _____, _____, _____, _____
  ),

/* QWERTY - doesn't support recording of macros, btw.  Falls through to colemak for most keys, but passes through the recording layer, so heads up.
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        | M(0)   | M(1)   |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | Q      | W      | E      | R      | T      | M(2)   |  (FN)  |        | Y      | U      | I      | O      | P      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | SHIFT  | A      | S      | D      | F      | G      |        |        |        | H      | J      | K      | L      | ;      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | CTRL   | Z      | X      | C      | V      | B      |        |        |        | N      | M      |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        | ALT    | GUI    |                          |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [LAYER_QWERTY] = LAYOUT(
    _____,    _____, _____, _____,    _____,    _____,    MM_0,  MM_1,    _____, _____, _____, _____, _____, _____, _____,
    _____,    KC_Q,  KC_W,  KC_E,     KC_R,     KC_T,     MM_2,  GOTO_FN, _____, KC_Y,  KC_U, KC_I,  KC_O,  KC_P,    _____,
    MOD_LSFT, KC_A,  KC_S,  KC_D,     KC_F,     KC_G,     _____,  _____,  _____, KC_H,  KC_J, KC_K,  KC_L,  KC_SCLN, _____,
    MOD_LCTL, KC_Z,  KC_X,  KC_C,     KC_V,     KC_B,     _____,  _____,  _____, KC_N,  KC_M, _____, _____, _____,   _____,
    _____,    _____, _____, MOD_LALT, MOD_LGUI, _____, _____,  _____,  _____, _____, _____, _____, _____, _____, _____
  ),

/* FN LAYER - change layouts and start recording a macro
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | COLEMAK| QWERTY |        |        |        |        | REC 1  | REC 2  |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        | ------ |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        | QK_BOOT  |         DM_CLEAR         |        |        | QK_BOOT  |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [LAYER_FN] = LAYOUT(
    GOTO_CM, GOTO_QW, KC_NO, KC_NO, KC_NO, KC_NO, DM_REC1, DM_REC2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,          KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,          KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,          KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO,   KC_NO,   KC_NO, KC_NO, QK_BOOT,  KC_NO, DM_CLEAR, KC_NO,             KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO
  )
};

typedef struct {
    bool is_pressed;
    uint16_t timer;
    uint16_t kc_tap;
    uint16_t kc_hold;
} tap_hold_t;

static tap_hold_t th_events[] = {
    { .is_pressed = false, .timer = 0, .kc_tap = KC_VOLD, .kc_hold = KC_MRWD }, // TH_M0
    { .is_pressed = false, .timer = 0, .kc_tap = KC_MPLY, .kc_hold = KC_MUTE }, // TH_M1
    { .is_pressed = false, .timer = 0, .kc_tap = KC_VOLU, .kc_hold = KC_MFFD }, // TH_M2

    { .is_pressed = false, .timer = 0, .kc_tap = KC_1, .kc_hold = KC_F1 }, // TH_F1
    { .is_pressed = false, .timer = 0, .kc_tap = KC_2, .kc_hold = KC_F2 }, // TH_F2
    { .is_pressed = false, .timer = 0, .kc_tap = KC_3, .kc_hold = KC_F3 }, // TH_F3
    { .is_pressed = false, .timer = 0, .kc_tap = KC_4, .kc_hold = KC_F4 }, // TH_F4
    { .is_pressed = false, .timer = 0, .kc_tap = KC_5, .kc_hold = KC_F5 }, // TH_F5
    { .is_pressed = false, .timer = 0, .kc_tap = KC_6, .kc_hold = KC_F6 }, // TH_F6
    { .is_pressed = false, .timer = 0, .kc_tap = KC_7, .kc_hold = KC_F7 }, // TH_F7
    { .is_pressed = false, .timer = 0, .kc_tap = KC_8, .kc_hold = KC_F8 }, // TH_F8
    { .is_pressed = false, .timer = 0, .kc_tap = KC_9, .kc_hold = KC_F9 }, // TH_F9
    { .is_pressed = false, .timer = 0, .kc_tap = KC_0, .kc_hold = KC_F10 } // TH_F10
};

void taphold_tapped(uint8_t index, bool pressed) {
    if (index >= TH_EVENTS_COUNT) { return; }

    tap_hold_t *th_event = &th_events[index];

    if (pressed) {
        th_event->timer = timer_read();
        th_event->is_pressed = true;
    } else if (th_event->is_pressed) {
        register_code(th_event->kc_tap);
        unregister_code(th_event->kc_tap);
        th_event->is_pressed = false;
    }
}

void matrix_scan_user(void) {
    for (uint8_t index = 0 ; index < TH_EVENTS_COUNT ; ++index ) {
        tap_hold_t *th_event = &th_events[index];
        if ( th_event->is_pressed && timer_elapsed(th_event->timer) > LONGPRESS_DELAY) {
            register_code(th_event->kc_hold);
            unregister_code(th_event->kc_hold);
            th_event->is_pressed = false;
        }
    }
}

// if the dynamic macros haven't been recorded, we send the default macro strings.
bool did_record_m1 = false;
bool did_record_m2 = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool try_dynamic_macro = true;
    if ((keycode == QK_DYNAMIC_MACRO_PLAY_1 && !did_record_m1) || (keycode == QK_DYNAMIC_MACRO_PLAY_2 && !did_record_m2)) {
        try_dynamic_macro = false;
    }
    else if (keycode == DM_CLEAR) {
        try_dynamic_macro = false;
        did_record_m1 = false;
        did_record_m2 = false;
    }

    if (try_dynamic_macro && !process_record_dynamic_macro(keycode, record)) {
        if (keycode == QK_DYNAMIC_MACRO_PLAY_1) {
                did_record_m1 = true;
        }

        if (keycode == QK_DYNAMIC_MACRO_PLAY_2) {
                did_record_m2 = true;
        }

        if (keycode == QK_DYNAMIC_MACRO_RECORD_START_1 || keycode == QK_DYNAMIC_MACRO_RECORD_START_2) {
                layer_move(LAYER_RECORD);
        }
        else if (keycode == QK_DYNAMIC_MACRO_RECORD_STOP) {
                layer_move(LAYER_COLEMAK);
        }

        return false;
    }

    switch (keycode) {
    case QK_DYNAMIC_MACRO_PLAY_1:
        SEND_STRING(SENDSTRING_MM0);
        return false;
    case QK_DYNAMIC_MACRO_PLAY_2:
        SEND_STRING(SENDSTRING_MM1);
        return false;
    case MM_2:
        SEND_STRING(SENDSTRING_MM2);
        return false;
    case TH_M0 ... TH_LAST:
        taphold_tapped(keycode - TH_M0, record->event.pressed);
        return false;
    }

    return true;
}
