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
//   2) OLED basic display. The SSD1306 (QMK core OLED driver on I2C1) shows a
//      minimal view (board name + active layer + last-key label) from
//      oled_task_kb. A keymap with its own elaborate UI overrides
//      oled_task_user and re-draws over this basic view.

#include QMK_KEYBOARD_H
#include "keycode_string.h"
#include "hal.h"
#include <stdlib.h>
#include <string.h>

/* ============================================================
   AS5600 encoder — read angle and synthesize quadrature pulses
   ============================================================ */

/* ---- Quadrature pulse timing ---- */
#define PULSE_DELAY 10000               // 10 ms total per pulse
#define PHASE_DELAY (PULSE_DELAY / 2)   // 5 ms B-channel phase offset

// The AS5600 has the I2C0 peripheral to itself, driven directly via ChibiOS.
static const I2CConfig as5600_i2c_cfg = { .baudrate = 100000 };

// Read the 12-bit raw angle (0..4095) from the AS5600. Returns 0 on any I2C
// error or out-of-range value (caller treats 0 as "no reading").
static uint16_t as5600_read_angle(void) {
    uint8_t reg = AS5600_ANGLE_REG;
    uint8_t data[2];
    msg_t status = i2cMasterTransmitTimeout(&I2CD0, AS5600_ADDRESS, &reg, 1, data, 2, TIME_MS2I(20));
    if (status != MSG_OK) return 0;

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
   Uses QMK's core OLED driver (6x8 font). Keymaps that want a
   richer UI define oled_task_user(); oled_task_kb checks that
   first and defers to it when it returns false.
   ============================================================ */

#define KB_OLED_ACTION_MS 2500    // how long a key label stays on screen

static char     kb_oled_action_text[16] = "";
static uint32_t kb_oled_action_until    = 0;

static void kb_oled_show_action(const char *text) {
    if (!text) return;
    strncpy(kb_oled_action_text, text, sizeof(kb_oled_action_text) - 1);
    kb_oled_action_text[sizeof(kb_oled_action_text) - 1] = 0;
    kb_oled_action_until = timer_read32() + KB_OLED_ACTION_MS;
}

/* ============================================================
   QMK keyboard-level hooks
   ============================================================ */

void keyboard_post_init_kb(void) {
    // AS5600 on the I2C0 peripheral, driven directly via ChibiOS. (The core
    // OLED driver owns the I2C1 peripheral through i2c_master.)
    palSetLineMode(AS5600_SDA_PIN, PAL_MODE_ALTERNATE_I2C | PAL_RP_PAD_SLEWFAST | PAL_RP_PAD_PUE | PAL_RP_PAD_DRIVE4);
    palSetLineMode(AS5600_SCL_PIN, PAL_MODE_ALTERNATE_I2C | PAL_RP_PAD_SLEWFAST | PAL_RP_PAD_PUE | PAL_RP_PAD_DRIVE4);
    i2cStart(&I2CD0, &as5600_i2c_cfg);
    wait_ms(200);

    // GP20/GP21 carry the synthetic quadrature pulses, physically wired back
    // to the encoder input pins GP22/GP23 on the PCB.
    gpio_set_pin_output_push_pull(AS5600_PIN_A);
    gpio_set_pin_output_push_pull(AS5600_PIN_B);
    gpio_write_pin_high(AS5600_PIN_A);
    gpio_write_pin_high(AS5600_PIN_B);

    gpio_set_pin_input_high(GP22);
    gpio_set_pin_input_high(GP23);

    // Board indicator LEDs, shared by every keymap. The two NPN-driven blue
    // switch-LED columns are held on; the D6 user LED (active-LOW) lights as a
    // "device alive" indicator. Keymaps may animate these further afterwards.
    gpio_set_pin_output_push_pull(LED_COL0_PIN);
    gpio_set_pin_output_push_pull(LED_COL1_PIN);
    gpio_write_pin_high(LED_COL0_PIN);
    gpio_write_pin_high(LED_COL1_PIN);
    gpio_set_pin_output_push_pull(USER_LED_PIN);
    gpio_write_pin_low(USER_LED_PIN);

    keyboard_post_init_user();
}

// Extend the row-select settle delay. QMK's RP2040 default (~250 ns via
// GPIO_INPUT_PIN_DELAY) is too short for the row 3 (GP11) trace on this PCB,
// so SW9 is never detected without it. 100 us settles any GPIO on this board.
void matrix_output_select_delay(void) {
    wait_us(100);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Capture the pressed key's label for the basic OLED. Richer keymaps
    // re-render in housekeeping_task_user() and visually replace this.
    if (record->event.pressed) {
        kb_oled_show_action(get_keycode_string(keycode));
    }
    return process_record_user(keycode, record);
}

void housekeeping_task_kb(void) {
    as5600_encoder_task();
    as5600_encoder_task();
}

bool oled_task_kb(void) {
    if (!oled_task_user()) return false;

    // Top line: board name + active layer (1-indexed for friendliness).
    oled_set_cursor(0, 0);
    oled_write("SM Macro2040 L:", false);
    oled_write_char('1' + get_highest_layer(layer_state), false);

    // Third line: most recent key label for KB_OLED_ACTION_MS, else board name.
    oled_set_cursor(0, 2);
    bool show = kb_oled_action_text[0] && (timer_read32() < kb_oled_action_until);
    oled_write(show ? kb_oled_action_text : "Macro2040", false);
    return false;
}
