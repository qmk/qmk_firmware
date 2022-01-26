// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pointing.h"

static uint16_t mouse_timer           = 0;
static uint16_t mouse_debounce_timer  = 0;
static uint8_t  mouse_keycode_tracker = 0;
bool            tap_toggling = false, enable_acceleration = false;

#ifdef TAPPING_TERM_PER_KEY
#    define TAP_CHECK get_tapping_term(KC_BTN1, NULL)
#else
#    ifndef TAPPING_TERM
#        define TAPPING_TERM 200
#    endif
#    define TAP_CHECK TAPPING_TERM
#endif

__attribute__((weak)) report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    int8_t x = mouse_report.x, y = mouse_report.y;
    mouse_report.x = 0;
    mouse_report.y = 0;

    if (x != 0 && y != 0) {
        mouse_timer = timer_read();
#ifdef OLED_ENABLE
        oled_timer = timer_read32();
#endif
        if (timer_elapsed(mouse_debounce_timer) > TAP_CHECK) {
            if (enable_acceleration) {
                x = (x > 0 ? x * x / 16 + x : -x * x / 16 + x);
                y = (y > 0 ? y * y / 16 + y : -y * y / 16 + y);
            }
            mouse_report.x = x;
            mouse_report.y = y;
            if (!layer_state_is(_MOUSE)) {
                layer_on(_MOUSE);
            }
        }
    }
    return pointing_device_task_keymap(mouse_report);
}

void matrix_scan_pointing(void) {
    if (timer_elapsed(mouse_timer) > 650 && layer_state_is(_MOUSE) && !mouse_keycode_tracker && !tap_toggling) {
        layer_off(_MOUSE);
    }
    if (tap_toggling) {
        if (!layer_state_is(_MOUSE)) {
            layer_on(_MOUSE);
        }
    }
}

bool process_record_pointing(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case TT(_MOUSE):
            if (record->event.pressed) {
                mouse_keycode_tracker++;
            } else {
#if TAPPING_TOGGLE != 0
                if (record->tap.count == TAPPING_TOGGLE) {
                    tap_toggling ^= 1;
#    if TAPPING_TOGGLE == 1
                    if (!tap_toggling) mouse_keycode_tracker -= record->tap.count + 1;
#    else
                    if (!tap_toggling) mouse_keycode_tracker -= record->tap.count;
#    endif
                } else {
                    mouse_keycode_tracker--;
                }
#endif
            }
            mouse_timer = timer_read();
            break;
        case TG(_MOUSE):
            if (record->event.pressed) {
                tap_toggling ^= 1;
            }
            break;
        case MO(_MOUSE):
#if defined(KEYBOARD_ploopy) || defined(KEYBOARD_handwired_tractyl_manuform)
        case DPI_CONFIG:
#elif defined(KEYBOARD_bastardkb_charybdis)
        case SAFE_RANGE ... (CHARYBDIS_SAFE_RANGE-1):
#endif
        case KC_MS_UP ... KC_MS_WH_RIGHT:
            record->event.pressed ? mouse_keycode_tracker++ : mouse_keycode_tracker--;
            mouse_timer = timer_read();
            break;
        case KC_ACCEL:
            enable_acceleration = record->event.pressed;
            record->event.pressed ? mouse_keycode_tracker++ : mouse_keycode_tracker--;
            mouse_timer = timer_read();
            break;
        default:
            if (IS_NOEVENT(record->event)) break;
            if ((keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) && (((keycode >> 0x8) & 0xF) == _MOUSE)) {
                record->event.pressed ? mouse_keycode_tracker++ : mouse_keycode_tracker--;
                mouse_timer = timer_read();
                break;
            }
            if (layer_state_is(_MOUSE) && !mouse_keycode_tracker && !tap_toggling) {
                layer_off(_MOUSE);
            }
            mouse_keycode_tracker = 0;
            mouse_debounce_timer  = timer_read();
            break;
    }
    return true;
}

layer_state_t layer_state_set_pointing(layer_state_t state) {
    if (layer_state_cmp(state, _GAMEPAD) || layer_state_cmp(state, _DIABLO)) {
        state |= ((layer_state_t)1 << _MOUSE);
    }
    return state;
}
