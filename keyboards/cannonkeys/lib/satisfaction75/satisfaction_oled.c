// Copyright 2023 Andrew Kannan
// SPDX-License-Identifier: GPL-2.0-or-later

#include "satisfaction_core.h"
#include "action_layer.h"
#include "action_util.h"
#include "timer.h"
#include "matrix.h"
#include "led.h"
#include "host.h"
#include "progmem.h"
#include <stdio.h>

void draw_default(void);
void draw_clock(void);

#ifdef OLED_ENABLE
#include "oled_driver.h"

oled_rotation_t oled_init_kb(oled_rotation_t rotation) { return OLED_ROTATION_0; }

bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    if (!oled_task_needs_to_repaint()) {
        return false;
    }
    oled_clear();
    if (clock_set_mode) {
        draw_clock();
        return false;
    }
    switch (oled_mode) {
        default:
        case OLED_DEFAULT:
            draw_default();
            break;
        case OLED_TIME:
            draw_clock();
            break;
    }
    return false;
}

// Request a repaint of the OLED image without resetting the OLED sleep timer.
// Used for things like clock updates that should not keep the OLED turned on
// if there is no other activity.
void oled_request_repaint(void) {
    if (is_oled_on()) {
        oled_repaint_requested = true;
    }
}

// Request a repaint of the OLED image and reset the OLED sleep timer.
// Needs to be called after any activity that should keep the OLED turned on.
void oled_request_wakeup(void) {
    oled_wakeup_requested = true;
}

// Check whether oled_task_user() needs to repaint the OLED image.  This
// function should be called at the start of oled_task_user(); it also handles
// the OLED sleep timer and the OLED_OFF mode.
bool oled_task_needs_to_repaint(void) {
    // In the OLED_OFF mode the OLED is kept turned off; any wakeup requests
    // are ignored.
    if ((oled_mode == OLED_OFF) && !clock_set_mode) {
        oled_wakeup_requested = false;
        oled_repaint_requested = false;
        oled_off();
        return false;
    }

    // If OLED wakeup was requested, reset the sleep timer and do a repaint.
    if (oled_wakeup_requested) {
        oled_wakeup_requested = false;
        oled_repaint_requested = false;
        oled_sleep_timer = timer_read32() + CUSTOM_OLED_TIMEOUT;
        oled_on();
        return true;
    }

    // If OLED repaint was requested, just do a repaint without touching the
    // sleep timer.
    if (oled_repaint_requested) {
        oled_repaint_requested = false;
        return true;
    }

    // If the OLED is currently off, skip the repaint (which would turn the
    // OLED on if the image is changed in any way).
    if (!is_oled_on()) {
        return false;
    }

    // If the sleep timer has expired while the OLED was on, turn the OLED off.
    if (timer_expired32(timer_read32(), oled_sleep_timer)) {
        oled_off();
        return false;
    }

    // Always perform a repaint if the OLED is currently on.  (This can
    // potentially be optimized to avoid unneeded repaints if all possible
    // state changes are covered by oled_request_repaint() or
    // oled_request_wakeup(), but then any missed calls to these functions
    // would result in displaying a stale image.)
    return true;
}


static void draw_line_h(uint8_t x, uint8_t y, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        oled_write_pixel(i + x, y, true);
    }
}

static void draw_line_v(uint8_t x, uint8_t y, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        oled_write_pixel(x, i + y, true);
    }
}

static char* get_enc_mode(void) {
    switch (encoder_mode) {
        default:
        case ENC_MODE_VOLUME:
            return "VOL";
        case ENC_MODE_MEDIA:
            return "MED";
        case ENC_MODE_SCROLL:
            return "SCR";
        case ENC_MODE_BRIGHTNESS:
            return "BRT";
        case ENC_MODE_BACKLIGHT:
            return "BKL";
        case ENC_MODE_CLOCK_SET:
            return "CLK";
        case ENC_MODE_CUSTOM0:
            return "CS0";
        case ENC_MODE_CUSTOM1:
            return "CS1";
        case ENC_MODE_CUSTOM2:
            return "CS2";
    }
}

static char* get_time(void) {
    uint8_t  hour   = last_minute / 60;
    uint16_t minute = last_minute % 60;

    if (encoder_mode == ENC_MODE_CLOCK_SET) {
        hour   = hour_config;
        minute = minute_config;
    }

    bool is_pm = (hour / 12) > 0;
    hour       = hour % 12;
    if (hour == 0) {
        hour = 12;
    }

    static char time_str[8] = "";
    snprintf(time_str, sizeof(time_str), "%02hhu:%02hu%s", hour, minute, is_pm ? "pm" : "am");

    return time_str;
}

static char* get_date(void) {
    int16_t year  = last_timespec.year + 1980;
    int8_t  month = last_timespec.month;
    int8_t  day   = last_timespec.day;

    if (encoder_mode == ENC_MODE_CLOCK_SET) {
        year  = year_config + 1980;
        month = month_config;
        day   = day_config;
    }

    static char date_str[11] = "";
    snprintf(date_str, sizeof(date_str), "%04hd-%02hhd-%02hhd", year, month, day);

    return date_str;
}

void draw_default(void) {
    oled_write_P(PSTR("LAYER "), false);
    oled_write_char(get_highest_layer(layer_state) + 0x30, true);

    oled_write_P(PSTR(" ENC "), false);
    oled_write(get_enc_mode(), true);

    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(18, 0);
    oled_write_P(PSTR("CAP"), led_state.caps_lock);
    oled_set_cursor(18, 1);
    oled_write_P(PSTR("SCR"), led_state.scroll_lock);

    uint8_t mod_state = get_mods();
    oled_set_cursor(6, 3);
    oled_write_P(PSTR("S"), mod_state & MOD_MASK_SHIFT);
    oled_advance_char();
    oled_write_P(PSTR("C"), mod_state & MOD_MASK_CTRL);
    oled_advance_char();
    oled_write_P(PSTR("A"), mod_state & MOD_MASK_ALT);
    oled_advance_char();
    oled_write_P(PSTR("G"), mod_state & MOD_MASK_GUI);
    oled_advance_char();

    oled_write(get_time(), false);

/* Matrix display is 12 x 12 pixels */
#define MATRIX_DISPLAY_X 0
#define MATRIX_DISPLAY_Y 18

    // matrix
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        for (uint8_t y = 0; y < MATRIX_COLS; y++) {
            bool on = (matrix_get_row(x) & (1 << y)) > 0;
            oled_write_pixel(MATRIX_DISPLAY_X + y + 2, MATRIX_DISPLAY_Y + x + 2, on);
        }
    }

    // outline
    draw_line_h(MATRIX_DISPLAY_X, MATRIX_DISPLAY_Y, 19);
    draw_line_h(MATRIX_DISPLAY_X, MATRIX_DISPLAY_Y + 9, 19);
    draw_line_v(MATRIX_DISPLAY_X, MATRIX_DISPLAY_Y, 9);
    draw_line_v(MATRIX_DISPLAY_X + 19, MATRIX_DISPLAY_Y, 9);

    // oled location
    draw_line_h(MATRIX_DISPLAY_X + 14, MATRIX_DISPLAY_Y + 2, 3);

    // bodge extra lines for invert layer and enc mode
    draw_line_v(35, 0, 8);
    draw_line_v(71, 0, 8);
}

void draw_clock(void) {
    oled_set_cursor(0, 0);
    oled_write(get_date(), false);
    oled_set_cursor(0, 2);
    oled_write(get_time(), false);

    oled_set_cursor(12, 0);
    oled_write_P(PSTR(" ENC "), false);
    oled_write(get_enc_mode(), true);

    oled_set_cursor(13, 1);
    oled_write_P(PSTR("LAYER "), false);
    oled_write_char(get_highest_layer(layer_state) + 0x30, true);

    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(15, 3);
    oled_write_P(PSTR("CAPS"), led_state.caps_lock);

    if (clock_set_mode) {
        switch (time_config_idx) {
            case 0:  // hour
            default:
                draw_line_h(0, 25, 10);
                break;
            case 1:  // minute
                draw_line_h(18, 25, 10);
                break;
            case 2:  // year
                draw_line_h(0, 9, 24);
                break;
            case 3:  // month
                draw_line_h(30, 9, 10);
                break;
            case 4:  // day
                draw_line_h(48, 9, 10);
                break;
        }
    }

    // bodge extra lines for invert layer and enc mode
    draw_line_v(101, 0, 8);
    draw_line_v(113, 8, 8);
}

#else

void oled_request_repaint(void){
}

void oled_request_wakeup(void){
}

#endif