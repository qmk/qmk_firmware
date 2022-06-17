// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pointing.h"
#include "print.h"
#include "christrotter.h"

static uint16_t mouse_timer           = 0; // changing this does nothing to layer timings
static uint16_t mouse_debounce_timer  = 0; // changing this does nothing to layer timings
static uint8_t  mouse_keycode_tracker = 0;
bool            tap_toggling = false, enable_acceleration = false;

#define KEEP_MOUSE_LAYER_ON_FOR 700 // inactivity while on mouse layer, in ms
#define AUTO_MOUSE_LAYER_DELAY 5 // xy value threshold

// this is making sure both TAPPING_TERM and TAP_CHECK are defined
// #ifdef TAPPING_TERM_PER_KEY
// #    define TAP_CHECK get_tapping_term(KC_BTN1, NULL)
// #else
// #    ifndef TAPPING_TERM
// #        define TAPPING_TERM 200
// #    endif
// // changing tap check doesn't seem to affect anything
// #    define TAP_CHECK TAPPING_TERM
// #endif
#    define TAP_CHECK TAPPING_TERM


// this is grabbing mouse movement state?
__attribute__((weak)) report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    int8_t x = mouse_report.x, y = mouse_report.y;
    
    // set mouse_report x and y to zero for sure
    // so x and y now have the real life mouse coords, and the mouse_report obj coords are zero'd out
    mouse_report.x = 0;
    mouse_report.y = 0;
    if (x != 0 && y != 0) {
        
            // if x or y, our real-life coords, are not zero, the mouse has moved, so exec this block
            // ...set mouse_timer to timer_read...what is that...
            mouse_timer = timer_read();
            // do a check that ...wait where is that callled...that is set above to 0
            // do a check for "timer_elapsed" which is...uh...started..where?
            // if obj(timer_elapsed, populated with the value of mouse_debounce_timer) is greater than tap_check's value...
            // i.e. if mouse_debounce_timer is greater than tap_check
            // except if you mash here nothing changes...
            // if the mouse debounce timer is past tap check, turn on the mouse layer
            // therefore mouse debouce timer is what we want to add a delay to
            // but changing the logic here does nothing...if you set tap check to 2000 you get the same behaviour
            // could that be a split issue?
            if (timer_elapsed(mouse_debounce_timer) > 2000) {
                // no accel enabled, we can ignore this...
                if (enable_acceleration) {
                    x = (x > 0 ? x * x / 16 + x : -x * x / 16 + x);
                    y = (y > 0 ? y * y / 16 + y : -y * y / 16 + y);
                }
                // if our magical timer is more than tap_check...
                // set the mouse_report object coords back; we have validated that yes, the mouse moved, so turn on the mouse layer.
                mouse_report.x = x;
                mouse_report.y = y;
                // ...unless it's already on...but if not, turn it on
                if (!layer_state_is(_MOUSE)) {
                    if (x > AUTO_MOUSE_LAYER_DELAY || y > AUTO_MOUSE_LAYER_DELAY) {
                    layer_on(_MOUSE);
                    }
                }
            
        }
    // if the mouse coords ARE zero, then...
    } else if (timer_elapsed(mouse_timer) > KEEP_MOUSE_LAYER_ON_FOR && layer_state_is(_MOUSE) && !mouse_keycode_tracker && !tap_toggling) {
        // if the timer/mousetimer is greater than 650 and the layer is mouse &&&&&, turn off the mouse layer
        layer_off(_MOUSE);
    } else if (tap_toggling) {
        if (!layer_state_is(_MOUSE)) {
            layer_on(_MOUSE);
        }
    }
    // this returns the info to the mouse??
    return pointing_device_task_keymap(mouse_report);
}

// do we need this???
bool process_record_pointing(uint16_t keycode, keyrecord_t* record) {
    // debug_enable=true;
    // debug_matrix=true;
    //dprintf("process_record_pointing activated");
    //uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    switch (keycode) {
        // this is used if you just want to click one mouse button
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
        // if you hit TG_MOUSE you also turn on tap_toggling...?
            if (record->event.pressed) {
                tap_toggling ^= 1;
            }
            break;
        // this is a momentary layer toggle into mouse...if you MO_MOUSE, ensure safe_range is set or something
        case MO(_MOUSE):
#if defined(KEYBOARD_ploopy)
        case DPI_CONFIG:
#elif (defined(KEYBOARD_bastardkb_charybdis) || defined(KEYBOARD_handwired_tractyl_manuform_ct)) && !defined(NO_CHARYBDIS_KEYCODES)
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
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            break;
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (record->event.pressed || !record->tap.count) {
                break;
            }
        // ohay there is a default???
        default:
            // if nothing, break
            if (IS_NOEVENT(record->event)) break;
            // wat is qk_layer_tap...max...
            // if keycode fits params, do stuff
            if ((keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) && (((keycode >> 0x8) & 0xF) == _MOUSE)) {
                record->event.pressed ? mouse_keycode_tracker++ : mouse_keycode_tracker--;
                mouse_timer = timer_read();
                break;
            }
            // if you are on mouse, turn off
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
    // this seems very drashna-specific
    // if you are coming from those layers...do something w. state...???
    if (layer_state_cmp(state, _SYMBOLS) || layer_state_cmp(state, _SYMBOLS) || layer_state_cmp(state, _SYMBOLS)) {
        state |= ((layer_state_t)1 << _MOUSE);
    }
    return state;
}
