// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "cheapino.h"

// Startup LED animation: cycle through some colours for 2.5 seconds, then
// go back to the user's colour. Runs on the deferred executor so the
// keyboard is usable meanwhile, and doesn't write to EEPROM.

static uint8_t flash_steps_left = 50;

static uint32_t flash_led(uint32_t trigger_time, void *cb_arg) {
    if (--flash_steps_left == 0) {
        rgblight_reload_from_eeprom();
        return 0;
    }
    rgblight_sethsv_noeeprom(flash_steps_left * 5, 230, 70);
    return 50;
}

void keyboard_post_init_kb(void) {
    defer_exec(50, flash_led, NULL);
    keyboard_post_init_user();
}

// Ghosting
//
// The Cheapino uses a "duplex" matrix: every column pin carries two logical
// columns that are scanned in opposite directions (even columns: drive the
// column, read the rows; odd columns: drive the row, read the columns), each
// with its own diode direction. That saves pins, but lets current sneak
// through two held keys in one row when they sit on different column pins
// and scan in opposite directions. A third key in another row, on the same
// pin as one of them, then makes a key that isn't pressed show up.
//
// Example (v2, QWERTY, left half): hold Q and W, press D, and A shows up too.
// See https://github.com/tompi/cheapino/issues/33
//
// QMK's MATRIX_HAS_GHOST can't catch this. It only looks for the classic
// rectangle (two rows sharing two logical columns), which never happens here
// because the sneak path uses both logical columns of one pin. It also
// ignores the whole row while a ghost is possible, which would drop real
// chords such as home row mods.
//
// Rule: with keys (i, a), (i, b) and (j, a ^ 1) held, where a and b are on
// different pins (a / 2 != b / 2) and scan in opposite directions
// (a % 2 != b % 2), a ghost appears at (j, b). Remove it.
//
// The revisions call this for each group of rows that share column pins.

#define CHEAPINO_MAX_GHOST_ROWS 3

void cheapino_remove_ghosts(matrix_row_t matrix[], uint8_t first_row, uint8_t num_rows, uint8_t first_col, uint8_t num_cols) {
    matrix_row_t rows[CHEAPINO_MAX_GHOST_ROWS];
    matrix_row_t ghosts[CHEAPINO_MAX_GHOST_ROWS] = {0};

    if (num_rows > CHEAPINO_MAX_GHOST_ROWS) num_rows = CHEAPINO_MAX_GHOST_ROWS;

    for (uint8_t r = 0; r < num_rows; r++) {
        rows[r] = (matrix[first_row + r] >> first_col) & (((matrix_row_t)1 << num_cols) - 1);
    }

    for (uint8_t i = 0; i < num_rows; i++) {
        for (uint8_t j = 0; j < num_rows; j++) {
            if (i == j) continue;
            for (uint8_t a = 0; a < num_cols; a++) {
                if (!(rows[i] & ((matrix_row_t)1 << a)) || !(rows[j] & ((matrix_row_t)1 << (a ^ 1)))) continue;
                for (uint8_t b = 0; b < num_cols; b++) {
                    bool other_pin       = (b >> 1) != (a >> 1);
                    bool other_direction = (b & 1) != (a & 1);
                    if (other_pin && other_direction && (rows[i] & ((matrix_row_t)1 << b))) {
                        ghosts[j] |= (matrix_row_t)1 << b;
                    }
                }
            }
        }
    }

    for (uint8_t r = 0; r < num_rows; r++) {
        matrix[first_row + r] &= ~(ghosts[r] << first_col);
    }
}

// Encoder
//
// There aren't enough pins on the RJ45 for dedicated encoder pins, so the
// encoder's A and B contacts sit in the matrix. Each revision picks them out
// during the matrix scan, clears them so they never reach the keymap (where
// they could, for example, resolve a tap-hold key early), and hands them over
// here. The encoder press is a normal key at [3, 0].

static bool enc_a = false;
static bool enc_b = false;

void cheapino_set_encoder_contacts(bool a_closed, bool b_closed) {
    enc_a = a_closed;
    enc_b = b_closed;
}

void encoder_driver_init(void) {}

void encoder_driver_task(void) {
    static bool both_closed = false;

    if (enc_a && enc_b) {
        both_closed = true;
    } else if (both_closed && (enc_a || enc_b)) {
        // A+B followed by only A means clockwise, only B counter-clockwise
        both_closed = false;
        encoder_queue_event(0, enc_a);
    }
}
