// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "puckbuddy.h"

#ifndef GLIDEPOINT_DPI_OPTIONS
#    define GLIDEPOINT_DPI_OPTIONS \
        { 400, 800, 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000 }
#    ifndef GLIDEPOINT_DPI_DEFAULT
#        define GLIDEPOINT_DPI_DEFAULT 1
#    endif
#endif
#ifndef GLIDEPOINT_DPI_DEFAULT
#    define GLIDEPOINT_DPI_DEFAULT 1
#endif

keyboard_config_t keyboard_config;
uint16_t          dpi_array[] = GLIDEPOINT_DPI_OPTIONS;
#define DPI_OPTION_SIZE ARRAY_SIZE(dpi_array)

void board_init(void) {
    // B9 is configured as I2C1_SDA in the board file; that function must be
    // disabled before using B7 as I2C1_SDA.
    setPinInputHigh(B9);
}

#ifdef DYNAMIC_TAPPING_TERM_ENABLE
void tap_modify(int change_value, bool tap_status) {
    if (keyboard_config.dt_term_config < 0) {
        keyboard_config.dt_term_config *= -1;
    }

    keyboard_config.dt_term_config += change_value;

    if (tap_status == false ) {
        keyboard_config.dt_term_config *= -1;
        g_tapping_term = 0;
    } else {
        g_tapping_term = keyboard_config.dt_term_config;
    }
    eeconfig_update_kb(keyboard_config.raw);
}

void tap_toggle(void) {
    keyboard_config.dt_term_config *= -1;
    if (keyboard_config.dt_term_config > 0) {
        g_tapping_term = keyboard_config.dt_term_config;
    } else {
        g_tapping_term = 0;
    }
    eeconfig_update_kb(keyboard_config.raw);
}
#endif

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) { return false; }
    switch (index) {
        case 0:
            if(active) { tap_code(KC_CAPS_LOCK); }
            break;
        break;
    }
    return true;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case 1:
            if (clockwise) {
                tap_code(KC_PGUP);
            } else {
                tap_code(KC_PGDN);
            }
        break;
    }
    return true;
}
#endif

#ifdef OLED_ENABLE   // OLED Functionality
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;       // flips the display 180 degrees
}

bool clear_screen = true;           // used to manage singular screen clears to prevent display glitch
bool clear_screen_art = true;       // used to manage singular screen clears to prevent display glitch
static void render_name(void) {     // Render Puckbuddy "Get Puck'd" text
    static const char PROGMEM name_1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0xB6, 0xB6, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x00};
    static const char PROGMEM name_2[] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xB6, 0xB6, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0x00};
    static const char PROGMEM name_3[] = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xB6, 0xB6, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0x00};
    oled_set_cursor(0,0);
    oled_write_P(name_1, false);
    oled_set_cursor(0,1);
    oled_write_P(name_2, false);
    oled_set_cursor(0,2);
    oled_write_P(name_3, false);
}

static void render_logo(void) {     // Render MechWild "MW" Logo
    static const char PROGMEM logo_1[] = {0x97, 0x98, 0x99, 0x9A,0x00};
    static const char PROGMEM logo_2[] = {0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x00};
    static const char PROGMEM logo_3[] = {0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xB6, 0x00};
    static const char PROGMEM logo_4[] = {0xB6, 0xB6, 0xB6, 0x9B, 0x9C, 0x9D, 0x9E, 0x00};
    oled_set_cursor(0,0);
    oled_write_P(logo_1, false);
    oled_set_cursor(0,1);
    oled_write_P(logo_2, false);
    oled_set_cursor(0,2);
    oled_write_P(logo_3, false);
    oled_set_cursor(0,3);
    oled_write_P(logo_4, false);
}

bool oled_task_kb(void) {
    if(!oled_task_user()) {
        return false;
    }
    if ( IS_HOST_LED_OFF(USB_LED_NUM_LOCK) && IS_HOST_LED_OFF(USB_LED_CAPS_LOCK) && IS_HOST_LED_OFF(USB_LED_SCROLL_LOCK) && get_highest_layer(layer_state) == 0 ) {
        if (clear_screen_art == true) {
            oled_clear();
            oled_render();
            clear_screen_art = false;
        }
        render_name();
        oled_set_cursor(0,3);
#ifdef POINTING_DEVICE_ENABLE
        oled_write_P(PSTR(" DPI:"), false);
        oled_write(get_u16_str(dpi_array[keyboard_config.dpi_config], ' '), false);
#endif
#ifdef DYNAMIC_TAPPING_TERM_ENABLE                      // only display tap info if it is being configured dynamically
        oled_write_P(PSTR(" TAP:"), false);
        if (keyboard_config.dt_term_config < 0) {
            oled_write_P(PSTR("Off  "), false);
        } else {
            oled_write(get_u16_str(g_tapping_term, ' '), false);
        }
#endif
        clear_screen = true;
    } else {
        if (clear_screen == true) {
            oled_clear();
            oled_render();
            clear_screen = false;
        }
        render_logo();
        oled_set_cursor(8,1);
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("Layer 0"), false);
                break;
            case 1:
                oled_write_P(PSTR("Layer 1"), false);
                break;
            case 2:
                oled_write_P(PSTR("Layer 2"), false);
                break;
            case 3:
                oled_write_P(PSTR("Layer 3"), false);
                break;
            default:
                oled_write_P(PSTR("Layer ?"), false);    // Should never display, here as a catchall
        }
        led_t led_state = host_keyboard_led_state();
        oled_set_cursor(8,0);
        oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
        oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
        oled_write_P(led_state.scroll_lock ? PSTR("SCR") : PSTR("    "), false);
#ifdef POINTING_DEVICE_ENABLE
        oled_set_cursor(8,2);
        oled_write_P(PSTR("DPI:"), false);
        oled_write(get_u16_str(dpi_array[keyboard_config.dpi_config], ' '), false);
#endif
#ifdef DYNAMIC_TAPPING_TERM_ENABLE              // only display tap info if it is being configured dynamically
        oled_set_cursor(8,3);
        oled_write_P(PSTR("TAP:"), false);
        if (keyboard_config.dt_term_config < 0) {
            oled_write_P(PSTR("Off  "), false);
        } else {
            oled_write(get_u16_str(g_tapping_term, ' '), false);
        }
#endif
        clear_screen_art = true;
    }
    return true;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
#ifdef POINTING_DEVICE_ENABLE
        case DPI_UP:
            if (record->event.pressed) {
                keyboard_config.dpi_config = (keyboard_config.dpi_config + 1) % DPI_OPTION_SIZE;
                eeconfig_update_kb(keyboard_config.raw);
                pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
            }
            return false;
        case DPI_DN:
            if (record->event.pressed) {
                if (keyboard_config.dpi_config > 0) {
                    keyboard_config.dpi_config = (keyboard_config.dpi_config - 1) % DPI_OPTION_SIZE;
                } else {
                    keyboard_config.dpi_config = DPI_OPTION_SIZE - 1;
                }
                eeconfig_update_kb(keyboard_config.raw);
                pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
            }
            return false;
        case DPI_FINE:
            if (record->event.pressed) {
                pointing_device_set_cpi(dpi_array[0]);
            } else {
                pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
            }
            return false;
#endif
#ifdef DYNAMIC_TAPPING_TERM_ENABLE // only include tap info keycodes if it is being configured dynamically
        case TAP_UP:
            if (record->event.pressed) {
                tap_modify(DYNAMIC_TAPPING_TERM_INCREMENT, true);
            }
            return false;
        case TAP_DN:
            if (record->event.pressed) {
                if (keyboard_config.dt_term_config > 0) {
                    tap_modify(-1 * DYNAMIC_TAPPING_TERM_INCREMENT, true);
                }
            }
            return false;
        case TAP_ON:
            if (record->event.pressed) {
                tap_modify(0, true);
            }
            return false;
        case TAP_OFF:
            if (record->event.pressed) {
                tap_modify(0, false);
            }
            return false;
        case TAP_TOG:
            if (record->event.pressed) {
                tap_toggle();
            }
            return false;
#endif
    }
    return process_record_user(keycode, record);
}

void pointing_device_init_kb(void) {
#ifdef POINTING_DEVICE_ENABLE
    pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
#endif
}

void eeconfig_init_kb(void) {
#ifdef POINTING_DEVICE_ENABLE
    keyboard_config.dpi_config = GLIDEPOINT_DPI_DEFAULT;
#endif
#ifdef DYNAMIC_TAPPING_TERM_ENABLE // only set tap term from eeprom if it is being configured dynamically
    keyboard_config.dt_term_config = TAPPING_TERM;
#endif
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    // is safe to just read DPI setting since matrix init
    // comes before pointing device init.
    keyboard_config.raw = eeconfig_read_kb();
#ifdef POINTING_DEVICE_ENABLE
    if (keyboard_config.dpi_config > DPI_OPTION_SIZE) {
        eeconfig_init_kb();
    }
#endif
    matrix_init_user();
}

void keyboard_post_init_kb(void) {
#ifdef POINTING_DEVICE_ENABLE
    pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_toggle_noeeprom();     //double toggle post init removes the weirdness with rgb strips having a yellow first LED
    rgblight_toggle_noeeprom();
#endif
#ifdef DYNAMIC_TAPPING_TERM_ENABLE
    tap_toggle();   // Need it to reevaluate this setting after initiating so that it is current after init
    tap_toggle();
#endif
    keyboard_post_init_user();
#ifdef OLED_ENABLE  // purposefully after user post init to allow the RGB to startup first
    wait_ms(200);   // Avoids a startup issue where the oled renders and then turns off with blackpill
    oled_on();
#endif
}
