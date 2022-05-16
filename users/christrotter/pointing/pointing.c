// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pointing.h"
#include "print.h"

static uint16_t mouse_timer           = 0;
static uint16_t mouse_debounce_timer  = 0;
static uint8_t  mouse_keycode_tracker = 0;
bool            tap_toggling = false, enable_acceleration = false;

// this is making sure both TAPPING_TERM and TAP_CHECK are defined
#ifdef TAPPING_TERM_PER_KEY
#    define TAP_CHECK get_tapping_term(KC_BTN1, NULL)
#else
#    ifndef TAPPING_TERM
#        define TAPPING_TERM 200
#    endif
#    define TAP_CHECK TAPPING_TERM
#endif


// this is grabbing mouse movement state?
__attribute__((weak)) report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // ohh here we are setting x and y to the mouse reports
    print("entering report_mouse_t")
    int8_t x = mouse_report.x, y = mouse_report.y;
    // set mouse_report x and y to zero for future tasks
    mouse_report.x = 0;
    mouse_report.y = 0;
    // now, x and y will maybe have a non-zero value compared to mouse_report.x/y
    
    if (x != 0 && y != 0) {
        print("detected non-zero mouse coords")
        // not sure how this works...if x/y are not zero??...but we just set them to zero two lines up???
        // yeah so x is our original mouse report...
        // if non-zero, then do this block
        // set mouse_timer to a timer_read function thingy
        mouse_timer = timer_read();
        // do a check that ...wait where is that callled...that is set above to 0
        // do a check for "timer_elapsed" which is...uh...started..where?
        if (timer_elapsed(mouse_debounce_timer) > TAP_CHECK) {
            // if our magical timer is more than tap_check...
            
            // no accel enabled, we can ignore this...
            if (enable_acceleration) {
                x = (x > 0 ? x * x / 16 + x : -x * x / 16 + x);
                y = (y > 0 ? y * y / 16 + y : -y * y / 16 + y);
            }
            // set mouse_report coords
            // OH but we set them to zero above, so they need to be set back... ???
            
            mouse_report.x = x;
            mouse_report.y = y;
            // if we're not already on the mouse layer, mouse layer on
            if (!layer_state_is(_MOUSE)) {
                print("turning on mouse layer")
                layer_on(_MOUSE);
            }
        }
    } else if (timer_elapsed(mouse_timer) > 650 && layer_state_is(_MOUSE) && !mouse_keycode_tracker && !tap_toggling) {
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
    debug_enable=true;
    // debug_matrix=true;
    dprintf("process_record_pointing activated");
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
    if (layer_state_cmp(state, _GAMEPAD) || layer_state_cmp(state, _DIABLO) || layer_state_cmp(state, _DIABLOII)) {
        state |= ((layer_state_t)1 << _MOUSE);
    }
    return state;
}
