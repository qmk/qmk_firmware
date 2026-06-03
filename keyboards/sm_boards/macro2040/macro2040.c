// Copyright 2024 SM Boards (@sm_boards)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Keyboard-level hardware glue for the SM Boards Macro2040.
//
// Two pieces of "the board just works" functionality live here so every
// keymap (default, via, ...) gets them for free:
//
//   1) AS5600 encoder loopback. The rotary control is a magnetic angle
//      sensor, not a real quadrature encoder, so we read its angle over I2C
//      and SYNTHESIZE quadrature pulses on GP20/GP21 (AS5600_PIN_A/B), which
//      are physically wired back to the encoder input pins GP22/GP23. QMK's
//      standard encoder driver then sees them like any other encoder.
//
//   2) OLED basic display. The SSD1306 is initialised at the keyboard level
//      and a minimal renderer (board name + active layer + last-key label)
//      runs from housekeeping_task_kb. A keymap with its own elaborate UI
//      (e.g. the via keymap) overrides housekeeping_task_user and re-draws
//      the screen each tick, which simply replaces this basic view.

#include QMK_KEYBOARD_H
#include "i2c_master.h"
#include "oled_custom.h"
#include "keycode_label.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ============================================================
   AS5600 encoder — read angle and synthesize quadrature pulses
   ============================================================ */

/* ---- Quadrature pulse timing ---- */
#define PULSE_DELAY 10000               // 10 ms total per pulse
#define PHASE_DELAY (PULSE_DELAY / 2)   // 5 ms B-channel phase offset

// Read the 12-bit raw angle (0..4095) from the AS5600. Returns 0 on any I2C
// error or out-of-range value (caller treats 0 as "no reading").
static uint16_t as5600_read_angle(void) {
    uint8_t data[2];
    i2c_status_t status = i2c_read_register(AS5600_ADDRESS << 1, AS5600_ANGLE_REG, data, 2, 200);
    if (status != I2C_STATUS_SUCCESS) return 0;

    uint16_t angle = ((uint16_t)data[0] << 8) | data[1];
    if (angle > 4095) return 0;
    return angle;
}

/* ---- Virtual quadrature pulse generator (non-blocking state machine) ---- */

typedef enum {
    QUAD_IDLE,
    QUAD_STATE_0,
    QUAD_STATE_1,
    QUAD_STATE_2,
    QUAD_STATE_3,
    QUAD_STATE_4
} quad_state_t;

static quad_state_t quad_state     = QUAD_IDLE;
static bool         quad_direction = true;   // true = CW, false = CCW
static uint32_t     quad_next_time = 0;

static void start_quadrature_pulse(bool clockwise) {
    if (quad_state == QUAD_IDLE) {
        quad_direction = clockwise;
        quad_state     = QUAD_STATE_0;
        quad_next_time = timer_read32();
    }
}

static void update_quadrature_pulse(void) {
    if (quad_state == QUAD_IDLE) return;

    uint32_t now = timer_read32();
    if (now < quad_next_time) return;

    if (quad_direction) {
        switch (quad_state) {
            case QUAD_STATE_0: gpio_write_pin_high(AS5600_PIN_A); gpio_write_pin_high(AS5600_PIN_B); quad_next_time = now + (PULSE_DELAY / 1000); quad_state = QUAD_STATE_1; break;
            case QUAD_STATE_1: gpio_write_pin_low(AS5600_PIN_A);  quad_next_time = now + (PHASE_DELAY / 1000); quad_state = QUAD_STATE_2; break;
            case QUAD_STATE_2: gpio_write_pin_low(AS5600_PIN_B);  quad_next_time = now + (PHASE_DELAY / 1000); quad_state = QUAD_STATE_3; break;
            case QUAD_STATE_3: gpio_write_pin_high(AS5600_PIN_A); quad_next_time = now + (PHASE_DELAY / 1000); quad_state = QUAD_STATE_4; break;
            case QUAD_STATE_4: gpio_write_pin_high(AS5600_PIN_B); quad_state = QUAD_IDLE; break;
            default:           quad_state = QUAD_IDLE; break;
        }
    } else {
        switch (quad_state) {
            case QUAD_STATE_0: gpio_write_pin_high(AS5600_PIN_A); gpio_write_pin_high(AS5600_PIN_B); quad_next_time = now + (PULSE_DELAY / 1000); quad_state = QUAD_STATE_1; break;
            case QUAD_STATE_1: gpio_write_pin_low(AS5600_PIN_B);  quad_next_time = now + (PHASE_DELAY / 1000); quad_state = QUAD_STATE_2; break;
            case QUAD_STATE_2: gpio_write_pin_low(AS5600_PIN_A);  quad_next_time = now + (PHASE_DELAY / 1000); quad_state = QUAD_STATE_3; break;
            case QUAD_STATE_3: gpio_write_pin_high(AS5600_PIN_B); quad_next_time = now + (PHASE_DELAY / 1000); quad_state = QUAD_STATE_4; break;
            case QUAD_STATE_4: gpio_write_pin_high(AS5600_PIN_A); quad_state = QUAD_IDLE; break;
            default:           quad_state = QUAD_IDLE; break;
        }
    }
}

// Poll AS5600, accumulate angle, emit a virtual encoder "click" each time
// the accumulator crosses ±AS5600_RESOLUTION.
static void as5600_encoder_task(void) {
    static uint16_t last_angle  = 0;
    static bool     first_read  = true;
    static int32_t  accumulated = 0;
    static uint8_t  error_count = 0;

    update_quadrature_pulse();   // keep any in-flight pulse moving

    uint16_t current_angle = as5600_read_angle();

    if (current_angle == 0) {
        if (++error_count == 20) {
            first_read  = true;
            accumulated = 0;
            error_count = 0;
        }
        return;
    }
    error_count = 0;

    if (first_read) {
        last_angle = current_angle;
        first_read = false;
        return;
    }

    int16_t diff = current_angle - last_angle;
    if (diff > 2048)  diff -= 4096;
    if (diff < -2048) diff += 4096;
    diff = -diff;   // magnet decreases on physical CW; normalise to +diff = CW
    if (abs(diff) < 10) return;   // jitter filter

    accumulated += diff;
    last_angle   = current_angle;

    if (accumulated >= AS5600_RESOLUTION) {
        accumulated -= AS5600_RESOLUTION;
        start_quadrature_pulse(true);
    }
    if (accumulated <= -AS5600_RESOLUTION) {
        accumulated += AS5600_RESOLUTION;
        start_quadrature_pulse(false);
    }
}

/* ============================================================
   Keyboard-level OLED — basic board / layer / last-key display
   ------------------------------------------------------------
   Provides a working OLED for every keymap. Keymaps that want a
   richer UI (e.g. the via keymap with its scrolling banner,
   games, and timer) define housekeeping_task_user(), which runs
   AFTER housekeeping_task_kb() and simply re-draws over this.
   ============================================================ */

#define KB_OLED_ACTION_MS  2500    // how long a key/layer label stays on
#define KB_OLED_REFRESH_MS 100     // 10 Hz redraw

static char     kb_oled_action_text[16] = "";
static uint32_t kb_oled_action_until    = 0;

static void kb_oled_show_action(const char *text) {
    if (!text) return;
    strncpy(kb_oled_action_text, text, sizeof(kb_oled_action_text) - 1);
    kb_oled_action_text[sizeof(kb_oled_action_text) - 1] = 0;
    kb_oled_action_until = timer_read32() + KB_OLED_ACTION_MS;
}

static void kb_oled_render(void) {
    oled_clear();

    // Top line: board name + active layer (1-indexed for friendliness).
    char top[24];
    uint8_t layer = get_highest_layer(layer_state);
    snprintf(top, sizeof(top), "SM Macro2040 L:%u", (unsigned)(layer + 1));
    oled_write(top);

    // Bottom: most recent key label (big font, centred) for KB_OLED_ACTION_MS,
    // otherwise the static board name.
    bool show = kb_oled_action_text[0] && (timer_read32() < kb_oled_action_until);
    if (show) {
        uint8_t len = (uint8_t)strlen(kb_oled_action_text);
        if (len > 10) len = 10;
        uint16_t w = (uint16_t)len * 12;
        uint8_t  x = (w >= OLED_DISP_WIDTH) ? 0 : (uint8_t)((OLED_DISP_WIDTH - w) / 2);
        oled_write_big(x, 2, kb_oled_action_text);
    } else {
        // "Macro2040" = 9 chars * 12 = 108 px; centered at (128-108)/2 = 10.
        oled_write_big(10, 2, "Macro2040");
    }

    oled_flush();
}

/* ============================================================
   QMK keyboard-level hooks
   ============================================================ */

void keyboard_post_init_kb(void) {
    // I2C0 master for the AS5600 (QMK's i2c_master owns I2CD0).
    i2c_init();
    wait_ms(200);

    // GP20/GP21 carry the synthetic quadrature pulses, physically wired back
    // to the encoder input pins GP22/GP23 on the PCB.
    gpio_set_pin_output_push_pull(AS5600_PIN_A);
    gpio_set_pin_output_push_pull(AS5600_PIN_B);
    gpio_write_pin_high(AS5600_PIN_A);
    gpio_write_pin_high(AS5600_PIN_B);

    gpio_set_pin_input_high(GP22);
    gpio_set_pin_input_high(GP23);

    // OLED on I2C1 (independent of QMK's i2c_master on I2C0).
    oled_init();

    keyboard_post_init_user();
}

void matrix_scan_kb(void) {
    as5600_encoder_task();
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Capture the pressed key's label for the basic OLED. Richer keymaps
    // re-render in housekeeping_task_user() and visually replace this.
    if (record->event.pressed) {
        kb_oled_show_action(keycode_label(keycode));
    }
    return process_record_user(keycode, record);
}

void housekeeping_task_kb(void) {
    static uint32_t last_render = 0;
    if (timer_elapsed32(last_render) >= KB_OLED_REFRESH_MS) {
        last_render = timer_read32();
        kb_oled_render();
    }
    housekeeping_task_user();
}
