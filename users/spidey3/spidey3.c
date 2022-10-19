// Copyright 2022 Joshua Diamond josh@windowoffire.com (@spidey3)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "spidey3.h"
#include "version.h"
#include <stdlib.h>

static bool rand_seeded = false;

uint16_t spi_replace_mode = SPI_NORMAL;
bool     spi_gflock       = false;

#if defined(CONSOLE_ENABLE) && !defined(NO_DEBUG)
static uint32_t matrix_scan_count = 0;
static bool     reported_version  = false;

#    if defined(SPI_DEBUG_SCAN_RATE)
static uint32_t matrix_timer = 0;
#    endif

void report_version(void) {
    uprintln(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " - " QMK_BUILDDATE);
    reported_version = true;
}
#endif

void matrix_scan_user(void) {
#if defined(CONSOLE_ENABLE) && !defined(NO_DEBUG)
#    if defined(SPI_DEBUG_SCAN_RATE)
    matrix_scan_count++;
    if (debug_enable) {
        uint32_t timer_now = timer_read32();
        if (matrix_timer == 0) {
            matrix_timer      = timer_now;
            matrix_scan_count = 0;
        } else if (TIMER_DIFF_32(timer_now, matrix_timer) > SPI_SCAN_RATE_INTERVAL * 1000) {
            matrix_timer = timer_now;
            uprintf("scan rate: %lu/s\n", matrix_scan_count / SPI_SCAN_RATE_INTERVAL);
            matrix_scan_count = 0;
            if (!reported_version) report_version();
        }
    }
#    else
    if (!reported_version) {
        matrix_scan_count++;
        if (matrix_scan_count > 300) report_version();
    }
#    endif
#endif
#ifdef RGBLIGHT_ENABLE
    matrix_scan_user_rgb();
#endif
}

static uint32_t math_glyph_exceptions(const uint16_t keycode, const bool shifted) {
    bool caps = host_keyboard_led_state().caps_lock;
    if (shifted != caps) {
        switch (keycode) {
            // clang-format off
            case KC_C: return 0x2102;
            case KC_H: return 0x210D;
            case KC_N: return 0x2115;
            case KC_P: return 0x2119;
            case KC_Q: return 0x211A;
            case KC_R: return 0x211D;
            case KC_Z: return 0x2124;
                // clang-format on
        }
    }
    return 0;
}

bool process_record_glyph_replacement(uint16_t keycode, keyrecord_t *record, uint32_t baseAlphaLower, uint32_t baseAlphaUpper, uint32_t zeroGlyph, uint32_t baseNumberOne, uint32_t spaceGlyph, uint32_t (*exceptions)(const uint16_t keycode, const bool shifted), uint8_t temp_mod, uint8_t temp_osm) {
    void _register(uint32_t codepoint) {
        unicode_input_start();
        register_hex32(codepoint);
        unicode_input_finish();
    }

    if ((((temp_mod | temp_osm) & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI))) == 0) {
        bool shifted = ((temp_mod | temp_osm) & MOD_MASK_SHIFT);
        if (exceptions) {
            uint32_t res = exceptions(keycode, shifted);
            if (res) {
                if (record->event.pressed) {
                    _register(res);
                }
                return false;
            }
        }
        switch (keycode) {
            case KC_A ... KC_Z:
                if (record->event.pressed) {
                    clear_mods();
#ifndef NO_ACTION_ONESHOT
                    clear_oneshot_mods();
#endif

                    bool     caps = host_keyboard_led_state().caps_lock;
                    uint32_t base = ((shifted == caps) ? baseAlphaLower : baseAlphaUpper);
                    _register(base + (keycode - KC_A));
                    set_mods(temp_mod);
                }
                return false;
            case KC_0:
                if (shifted) { // skip shifted numbers, so that we can still use symbols etc.
                    return true;
                }
                if (record->event.pressed) {
                    _register(zeroGlyph);
                }
                return false;
            case KC_1 ... KC_9:
                if (shifted) { // skip shifted numbers, so that we can still use symbols etc.
                    return true;
                }
                if (record->event.pressed) {
                    _register(baseNumberOne + (keycode - KC_1));
                }
                return false;
            case KC_SPACE:
                if (record->event.pressed) {
                    _register(spaceGlyph); // em space
                }
                return false;
        }
    }

    return true;
}

bool process_gflock(uint16_t keycode, keyrecord_t *record) {
    if (!spi_gflock) {
        return true;
    }

    if (record->event.pressed) {
        register_code16(G(keycode));
    } else {
        unregister_code16(G(keycode));
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    dprintf("key event: kc: %02X, col: %02u, row: %02u, pressed: %u mods: %08b "
#if !defined(NO_ACTION_ONESHOT)
            "os: %08b "
#endif
            "weak: %08b\n",
            keycode, record->event.key.col, record->event.key.row, record->event.pressed, bitrev(get_mods()),
#if !defined(NO_ACTION_ONESHOT)
            bitrev(get_oneshot_mods()),
#endif
            bitrev(get_weak_mods()));

    if (!rand_seeded) {
        srand(record->event.time % keycode);
        rand_seeded = true;
    }

    uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    uint8_t osm = get_oneshot_mods();
#else
    uint8_t osm = 0;
#endif

    if (record->event.pressed) {
        switch (keycode) {
#ifndef NO_DEBUG
            // Re-implement this here, but fix the persistence!
            case QK_DEBUG_TOGGLE:
                if (get_mods() & MOD_MASK_SHIFT) {
                    debug_enable   = 0;
                    debug_keyboard = 0;
                    debug_matrix   = 0;
                } else if (!debug_enable) {
                    debug_enable = 1;
#    if defined(SPI_DEBUG_SCAN_RATE)
                    matrix_timer = 0;
                    report_version();
#    endif
                } else if (!debug_keyboard) {
                    debug_keyboard = 1;
                } else if (!debug_matrix) {
                    debug_matrix = 1;
                } else {
                    debug_enable   = 0;
                    debug_keyboard = 0;
                    debug_matrix   = 0;
                }
                uprintf("DEBUG: enable=%u, kb=%u, matrix=%u\n", debug_enable, debug_keyboard, debug_matrix);
                eeconfig_update_debug(debug_config.raw);
                return false;
#endif

                // clang-format off

            case CH_SUSP: tap_code16(LGUI(LSFT(KC_L))); return true;

                // clang-format on

            case SPI_NORMAL ... SPI_MATH:
                spi_replace_mode = (spi_replace_mode == keycode) ? SPI_NORMAL : keycode;
                break;

            case SPI_GFLOCK:
                spi_gflock = !spi_gflock;
                break;

            case SPI_KP_00:
                tap_code(KC_KP_0);
#if TAP_CODE_DELAY > 0
                wait_ms(TAP_CODE_DELAY);
#endif
                register_code(KC_KP_0);
                return false;

            case KC_PSCR: {
                // It's kind of a hack, but we use unicode input mode
                // to determine what Print Screen key should do. The
                // idea here is to make it consistent across hosts.
                switch (get_unicode_input_mode()) {
                    case UC_MAC:
                        if ((mods | osm) & MOD_MASK_ALT) {
                            // Window screenshot
                            clear_mods();
#ifndef NO_ACTION_ONESHOT
                            clear_oneshot_mods();
#endif
                            tap_code16(LSFT(LGUI(KC_4)));
                            wait_ms(100);
                            tap_code(KC_SPC);
                            set_mods(mods);
                            return false;
                        } else if ((mods | osm) & MOD_MASK_SHIFT) {
                            // Partial screenshot
                            tap_code16(LSFT(LGUI(KC_4)));
                            return false;
                        } else {
                            // Full screenshot
                            tap_code16(LSFT(LGUI(KC_3)));
                            return false;
                        }
                        break;

                    case UC_WIN:
                    case UC_WINC:
                        if ((mods | osm) & MOD_MASK_ALT) {
                            // Window screenshot
                            // Alt+PrintScreen should work as is
                        } else if ((mods | osm) & MOD_MASK_SHIFT) {
                            // Partial screenshot
                            tap_code16(LGUI(LSFT(KC_S)));
                            return false;
                        } else {
                            // Full screenshot
                            // PrintScreen should work as is
                        }
                        break;

                    default:
                        // Note: These are specific to ChromeOS
                        if ((mods | osm) & MOD_MASK_ALT) {
                            // Window screenshot
                            tap_code16(LCTL(LALT(KC_F5)));
                            return false;
                        } else if ((mods | osm) & MOD_MASK_SHIFT) {
                            // Partial screenshot
                            tap_code16(LCTL(LSFT(KC_F5)));
                            return false;
                        } else {
                            // Full screenshot
                            // PrintScreen should work as is
                        }
                        break;
                }
                break;
            }
        }
    } else {
        switch (keycode) {
            case SPI_KP_00:
                unregister_code(KC_KP_0);
                return false;
        }
    }

    switch (keycode) {
        case KC_A ... KC_0:
        case KC_SPACE:
            switch (spi_replace_mode) {
                case SPI_WIDE:
                    return process_record_glyph_replacement(keycode, record, 0xFF41, 0xFF21, 0xFF10, 0xFF11, 0x2003, NULL, mods, osm);
                case SPI_SCRIPT:
                    return process_record_glyph_replacement(keycode, record, 0x1D4EA, 0x1D4D0, 0x1D7CE, 0x1D7CF, 0x2002, NULL, mods, osm);
                case SPI_BLOCKS:
                    return process_record_glyph_replacement(keycode, record, 0x1F170, 0x1F170, '0', '1', 0x2002, NULL, mods, osm);
                case SPI_CIRCLE:
                    return process_record_glyph_replacement(keycode, record, 0x1F150, 0x1F150, '0', '1', 0x2002, NULL, mods, osm);
                case SPI_SQUARE:
                    return process_record_glyph_replacement(keycode, record, 0x1F130, 0x1F130, '0', '1', 0x2002, NULL, mods, osm);
                case SPI_PARENS:
                    return process_record_glyph_replacement(keycode, record, 0x1F110, 0x1F110, '0', '1', 0x2002, NULL, mods, osm);
                case SPI_FRAKTR:
                    return process_record_glyph_replacement(keycode, record, 0x1D586, 0x1D56C, '0', '1', 0x2002, NULL, mods, osm);
                case SPI_BOLD:
                    return process_record_glyph_replacement(keycode, record, 0x1D41A, 0x1D400, '0', '1', 0x2002, NULL, mods, osm);
                case SPI_MATH:
                    return process_record_glyph_replacement(keycode, record, 0x1D552, 0x1D538, '0', '1', 0x2002, &math_glyph_exceptions, mods, osm);
            }
            break;

        case KC_F1 ... KC_F12:
            return process_gflock(keycode, record);

#ifdef SHIFT_BACKSPACE_DELETE
        case KC_BSPC: {
            static bool delkey_registered;
            if (record->event.pressed) {
                if ((mods | osm) & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
#    ifndef NO_ACTION_ONESHOT
                    clear_oneshot_mods();
#    endif
                    register_code(KC_DEL);
                    delkey_registered = true;
                    set_mods(mods);
                    return false;
                }
            } else { // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
        }
#endif
    }

#ifdef RGBLIGHT_ENABLE
    return process_record_user_rgb(keycode, record);
#else
    return true;
#endif
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_ENABLE
    post_process_record_user_rgb(keycode, record);
#endif
    return;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    return default_layer_state_set_user_rgb(state);
#else
    return state;
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    return layer_state_set_user_rgb(state);
#else
    return state;
#endif
}

bool led_update_user(led_t led_state) {
#ifdef RGBLIGHT_ENABLE
    return led_update_user_rgb(led_state);
#else
    return true;
#endif
}

#if defined(UNICODE_COMMON_ENABLE)
void unicode_input_mode_set_user(uint8_t input_mode) {
#    ifdef RGBLIGHT_ENABLE
    unicode_input_mode_set_user_rgb(input_mode);
#    endif
}
#endif
