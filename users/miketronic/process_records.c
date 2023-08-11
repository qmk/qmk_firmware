// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include "miketronic.h"
#include "process_records.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case VERSION:
            if (!record->event.pressed) {
                send_string_with_delay_P(PSTR(QMK_KEYBOARD ":" QMK_KEYMAP "\nVersion:" QMK_VERSION ", built: " QMK_BUILDDATE "\n"), MACRO_TIMER);
            }
            break;

        case M01:
            if (record->event.pressed) {
                SEND_STRING("//a11");
            }
            break;

        case M02:
            if (record->event.pressed) {
                SEND_STRING("//a12");
            }
            break;

        case M03:
            if (record->event.pressed) {
                SEND_STRING("//a08");
            }
            break;

        case M04:
            if (record->event.pressed) {
                SEND_STRING("//a09");
            }
            break;

        case M05:
            if (record->event.pressed) {
                SEND_STRING("//th");
            }
            break;

        case M06:
            if (record->event.pressed) {
                SEND_STRING("//re");
            }
            break;

        case M07:
            if (record->event.pressed) {
                SEND_STRING("//yw");
            }
            break;

        case M08:
            if (record->event.pressed) {
                tap_random_base64();
            }
            break;

        case CCCV: // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) { // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else { // Tap, paste
                    tap_code16(LCTL(KC_V));
                }
            }
            break;

        case IENTER: // Tap for letter "i", slight hold for "enter"
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) { // Hold, enter
                    tap_code16(KC_ENT);
                } else { // Tap, "i"
                    tap_code16(KC_I);
                }
            }
            break;

        case PRN:
            if (record->event.pressed) {
                SEND_STRING("()");
                tap_code(KC_LEFT);
            }
            break;

        case BRACES:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
                    if (shifted) {
                        unregister_code(KC_LSFT);
                        unregister_code(KC_RSFT);
                        SEND_STRING("<>"SS_TAP(X_LEFT));
                    }
                    else {
                        SEND_STRING("[]"SS_TAP(X_LEFT));
                    }
            }
            break;

#if defined(RGBLIGHT_ENABLE)
        case RGB1:
            if (record->event.pressed) {
                rgblight_sethsv_noeeprom(HSV_BLUE);
            }
            break;

        case RGB2:
            if (record->event.pressed) {
                rgblight_sethsv_noeeprom(HSV_RED);
            }
            break;

        case RGB3:
            if (record->event.pressed) {
                rgblight_sethsv_noeeprom(HSV_ORANGE);
            }
            break;

        case RGB4:
            if (record->event.pressed) {
                rgblight_sethsv_noeeprom(HSV_WHITE);
            }
            break;

        case RGB5:
            if (record->event.pressed) {
                rgblight_sethsv_noeeprom(HSV_GREEN);
            }
            break;
#endif
    }
    return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
}
