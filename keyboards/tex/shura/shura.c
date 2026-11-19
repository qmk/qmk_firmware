// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include "tex_hw.h"

#define SHURA_FN_LAYER_MASK 0x0EU
// Stick counts per wheel notch at TrackPoint level 0; each level up takes one fewer.
#define SHURA_SCROLL_COUNTS 14

#define SHURA_TP_DATA_IN_PIN B4
#define SHURA_GPIO_MODE PAL_HT32_MODE_AF(AFIO_GPIO)

static ShuraFnState fn_state;
static int16_t      scroll_x;
static int16_t      scroll_y;
static uint8_t      current_profile = UINT8_MAX;
uint8_t             tex_dip;

void HardFault_Handler(void);

// A crash restarts into the TEX loader even if the scheduler is unavailable.
void HardFault_Handler(void) {
    TEX_ENTER_IAP();
}

// The loader leaves the watchdog running. Reload before ht32_clock_init().
void early_hardware_init_pre(void) {
    TEX_WDT_RELOAD();
}

// Called after PAL initialization at boot and again after the clocks resume.
void board_init(void) {
    // Reset leaves these pins in AF0; QMK's direction helpers do not select GPIO (AF1).
    palSetLineMode(PS2_CLOCK_PIN, SHURA_GPIO_MODE | PAL_MODE_INPUT);
    palSetLineMode(SHURA_TP_DATA_IN_PIN, SHURA_GPIO_MODE | PAL_MODE_INPUT);
    gpio_write_pin_high(PS2_DATA_PIN);
    palSetLineMode(PS2_DATA_PIN, SHURA_GPIO_MODE | PAL_MODE_OUTPUT_OPENDRAIN);
    gpio_write_pin_low(SHURA_TP_POWER_PIN);
    palSetLineMode(SHURA_TP_POWER_PIN, SHURA_GPIO_MODE | PAL_MODE_OUTPUT_PUSHPULL);
    gpio_write_pin_high(SHURA_CAPS_LED_PIN);
    palSetLineMode(SHURA_CAPS_LED_PIN, SHURA_GPIO_MODE | PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(SHURA_WAKEUP_PIN, SHURA_GPIO_MODE | PAL_MODE_INPUT);
    // Trim the internal oscillator against USB SOF; the Shura has no crystal.
    CKCU->HSICR = (CKCU->HSICR & ~0x30U) | 0x23U;
}

static void middle_click(void) {
    // A keymap holding MS_BTN3 owns the middle button; leave it alone.
    if (!(pointing_device_get_report().buttons & MOUSE_BTN3)) {
        pointing_device_keycode_handler(MS_BTN3, true);
        pointing_device_keycode_handler(MS_BTN3, false);
    }
}

// The middle button and dedicated Fn keys each hold their layer independently.
static bool process_fn(uint16_t keycode, bool pressed) {
    if (keycode == SHURA_MIDDLE) {
        if (shura_fn_middle(&fn_state, pressed)) {
            middle_click();
        }
        if (!pressed) {
            scroll_x = 0;
            scroll_y = 0;
        }
    } else if (keycode >= SHURA_FN1 && keycode <= SHURA_FN3) {
        shura_fn_dedicated(&fn_state, keycode - SHURA_FN1, pressed);
    } else {
        if (pressed) {
            shura_fn_consume(&fn_state);
        }
        return true;
    }

    layer_state_set((layer_state & ~(layer_state_t)SHURA_FN_LAYER_MASK) | shura_fn_layers(&fn_state));
    return false;
}

void keyboard_post_init_kb(void) {
    power_init();
    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    power_input();
    if (!process_record_user(keycode, record)) {
        // Even a key handled entirely by the keymap cancels a pending middle click.
        if (record->event.pressed && keycode != SHURA_MIDDLE) {
            shura_fn_consume(&fn_state);
        }
        return false;
    }
    if (!process_fn(keycode, record->event.pressed)) {
        return false;
    }
    if (!ble_process_record(keycode, record)) {
        return false;
    }
    if (!shura_trackpoint_record(keycode, record->event.pressed)) {
        return false;
    }
    if (keycode == BAT_REPORT) {
        if (record->event.pressed) {
            battery_report();
        }
        return false;
    }
    if (keycode >= SLEEP1 && keycode <= SLEEP9) {
        if (record->event.pressed) {
            power_set_sleep(keycode - SLEEP1, true);
        }
        return false;
    }
    return true;
}

static void scroll_motion(report_mouse_t *report) {
    uint8_t divisor = SHURA_SCROLL_COUNTS - tp_level;

    scroll_x += report->x;
    scroll_y += report->y;
    report->h = shura_div(scroll_x, divisor);
    report->v = shura_div(scroll_y, divisor);
    scroll_x -= report->h * divisor;
    scroll_y -= report->v * divisor;
    if (!(tex_dip & TEX_DIP5_REVERSE)) {
        report->v = -report->v;
    }
    report->x = 0;
    report->y = 0;
}

report_mouse_t pointing_device_task_kb(report_mouse_t report) {
    if (report.x || report.y) {
        power_pointer_activity();
        shura_fn_consume(&fn_state);
        if (shura_fn_scroll(&fn_state, tex_dip & TEX_DIP4_FN_SCROLL)) {
            scroll_motion(&report);
        } else {
            scroll_x = 0;
            scroll_y = 0;
            shura_trackpoint_scale(&report);
        }
    }
    return pointing_device_task_user(report);
}

static void update_dip(void) {
    uint8_t profile = 0;

    tex_dip = 0;
    for (uint8_t row = 0; row < 6; row++) {
        if (matrix_is_on(row, PROFILE_SWITCH_COL)) {
            tex_dip |= 1U << row;
        }
    }
    switch (tex_dip & 7U) {
        case 1:
            profile = 1;
            break;
        case 2:
            profile = 2;
            break;
        case 4:
            profile = 3;
            break;
    }
    if (profile != current_profile) {
        current_profile = profile;
        profile_switch_user(profile);
    }
}

__attribute__((weak)) void profile_switch_user(uint8_t profile) {}

void housekeeping_task_kb(void) {
    update_dip();
    ble_housekeeping();
    shura_trackpoint_task();
    power_task();
    housekeeping_task_user();
}

void suspend_power_down_kb(void) {
    // Drop pending clicks and held Fn layers; never click on resume.
    fn_state = (ShuraFnState){0};
    scroll_x = 0;
    scroll_y = 0;
    layer_state_set(layer_state & ~(layer_state_t)SHURA_FN_LAYER_MASK);
    suspend_power_down_user();
}
