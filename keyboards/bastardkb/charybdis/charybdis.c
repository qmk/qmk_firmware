/* Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "charybdis.h"
#include "drivers/sensors/pmw3360.h"

#ifndef CHARYBDIS_DPI_OPTIONS
#    define CHARYBDIS_DPI_OPTIONS \
        { 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800  }
#endif
#ifndef CHARYBDIS_DPI_DEFAULT
#    define CHARYBDIS_DPI_DEFAULT 0
#endif

#ifndef CHARYBDIS_SNIPER_OPTIONS
#define CHARYBDIS_SNIPER_OPTIONS \
        { 100, 200, 300, 400 }
#endif
#ifndef CHARYBDIS_SNIPER_DEFAULT
#    define CHARYBDIS_SNIPER_DEFAULT 0
#endif
#ifndef CHARYBDIS_AUTO_SNIPER_LAYER
#    define CHARYBDIS_AUTO_SNIPER_LAYER 4
#endif

#ifndef CHARYBDIS_DRAGSCROLL_DPI
#    define CHARYBDIS_DRAGSCROLL_DPI 100 // Fixed-DPI Drag Scroll
#endif

#ifndef CHARYBDIS_DRAGSCROLL_MULTIPLIER
#    define CHARYBDIS_DRAGSCROLL_MULTIPLIER 0.2 // Variable-DPI Drag Scroll
#endif


#ifndef CHARYBDIS_TRACKBALL_SPEED_DIVIDER_X
#    define CHARYBDIS_TRACKBALL_SPEED_DIVIDER_X 30
#endif

#ifndef CHARYBDIS_TRACKBALL_SPEED_DIVIDER_Y
#    define CHARYBDIS_TRACKBALL_SPEED_DIVIDER_Y 12
#endif

keyboard_config_t keyboard_config;
uint16_t          dpi_array[] = CHARYBDIS_DPI_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))

uint16_t          sniper_array[] = CHARYBDIS_SNIPER_OPTIONS;
#define SNIPER_OPTION_SIZE (sizeof(sniper_array) / sizeof(uint16_t))

bool    is_drag_scroll    = false;
bool    is_sniper_on      = false;

scroll_inertia_t scroll_inertia; // Scroll value storage to make scrolling slower

keyboard_config_t keyboard_config;

__attribute__((weak)) void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y) {
    mouse_report->x = x;
    mouse_report->y = y;
}

__attribute__((weak)) void process_mouse(report_mouse_t* mouse_report) {
    report_pmw_t data = pmw_read_burst();
    if (data.isOnSurface && data.isMotion) {
        // Wrap to HID size
        data.dx = constrain(data.dx, -127, 127);
        data.dy = constrain(data.dy, -127, 127);

        process_mouse_user(mouse_report, -data.dx, data.dy);
    }
}

void trigger_sniper(void){
    if (is_sniper_on) {
        pmw_set_cpi(sniper_array[keyboard_config.sniper_config]);
        } else {
        pmw_set_cpi(dpi_array[keyboard_config.dpi_config]);
    } 
}

// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    if (layer_state_cmp(state, CHARYBDIS_AUTO_SNIPER_LAYER) != is_sniper_on) {
        is_sniper_on ^= 1;
        trigger_sniper();
    }
    return state;
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) { return false; }

    switch(keycode){
        case SNIPER_CONFIG:
            if(record->event.pressed){
                if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
                    keyboard_config.sniper_config = keyboard_config.sniper_config - 1;
                } else {
                    keyboard_config.sniper_config = keyboard_config.sniper_config + 1;
                }
                keyboard_config.sniper_config = constrain(keyboard_config.sniper_config, 0, SNIPER_OPTION_SIZE - 1);
                eeconfig_update_kb(keyboard_config.raw);
                trigger_sniper();
            }
        break;

        case DPI_CONFIG:
            if(record->event.pressed){
                if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
                    keyboard_config.dpi_config = keyboard_config.dpi_config - 1;
                } else {
                    keyboard_config.dpi_config = keyboard_config.dpi_config + 1;
                }
                keyboard_config.dpi_config = constrain(keyboard_config.dpi_config, 0, DPI_OPTION_SIZE - 1);
                eeconfig_update_kb(keyboard_config.raw);
                pmw_set_cpi(dpi_array[keyboard_config.dpi_config]);
            }
        break;
        
        case SNIPING:
            is_sniper_on ^= 1;
            trigger_sniper();
        break;

        case DRAG_SCROLL:
#ifdef CHARYBDIS_DRAGSCROLL_TOGGLE
            if (record->event.pressed)
#endif
            {
                is_drag_scroll ^= 1;
            }
#ifndef CHARYBDIS_DRAGSCROLL_VARIABLE
            pmw_set_cpi(is_drag_scroll ? CHARYBDIS_DRAGSCROLL_DPI : dpi_array[keyboard_config.dpi_config]);
#else
            pmw_set_cpi(is_drag_scroll ? (dpi_array[keyboard_config.dpi_config] * CHARYBDIS_DRAGSCROLL_MULTIPLIER) : dpi_array[keyboard_config.dpi_config]);
#endif
        break;
    }

/* If Mousekeys is disabled, then use handle the mouse button
 * keycodes.  This makes things simpler, and allows usage of
 * the keycodes in a consistent manner.  But only do this if
 * Mousekeys is not enable, so it's not handled twice.
 */
#ifndef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        report_mouse_t currentReport = pointing_device_get_report();
        if (record->event.pressed) {
            currentReport.buttons |= 1 << (keycode - KC_MS_BTN1);
        } else {
            currentReport.buttons &= ~(1 << (keycode - KC_MS_BTN1));
        }
        pointing_device_set_report(currentReport);
        pointing_device_send();
    }
#endif

    return true;
}

// Hardware Setup
void keyboard_pre_init_kb(void) {
    scroll_inertia.x = 0;
    scroll_inertia.y = 0;
    
    keyboard_pre_init_user();
}

void pointing_device_init(void) {
    pmw_spi_init();
    pmw_set_cpi(dpi_array[keyboard_config.dpi_config]);
}

void pointing_device_task(void) {
    report_mouse_t mouse_report = pointing_device_get_report();
    process_mouse(&mouse_report);
    
    if (is_drag_scroll) { 
#ifdef CHARYBDIS_DRAGSCROLL_INVERT_X
        scroll_inertia.x -= mouse_report.x;
#else
        scroll_inertia.x += mouse_report.x;
#endif
#ifdef CHARYBDIS_DRAGSCROLL_INVERT_Y
        // Invert vertical scroll direction
        scroll_inertia.y -= mouse_report.y;
#else
        scroll_inertia.y += mouse_report.y;
#endif
        // we only want to trigger scrolling once in 12 scrolls, for slower scroll
        if(scroll_inertia.y > CHARYBDIS_TRACKBALL_SPEED_DIVIDER_Y || scroll_inertia.y < -CHARYBDIS_TRACKBALL_SPEED_DIVIDER_Y){
            mouse_report.v = constrain(scroll_inertia.y / CHARYBDIS_TRACKBALL_SPEED_DIVIDER_Y * 2, 
                                -CHARYBDIS_TRACKBALL_SPEED_DIVIDER_Y/2, CHARYBDIS_TRACKBALL_SPEED_DIVIDER_Y/2);
            scroll_inertia.y = 0;
        }
        if(scroll_inertia.x > CHARYBDIS_TRACKBALL_SPEED_DIVIDER_X || scroll_inertia.x < -CHARYBDIS_TRACKBALL_SPEED_DIVIDER_X){
            mouse_report.h = constrain(scroll_inertia.x / CHARYBDIS_TRACKBALL_SPEED_DIVIDER_X * 2, 
                                -CHARYBDIS_TRACKBALL_SPEED_DIVIDER_X/2, CHARYBDIS_TRACKBALL_SPEED_DIVIDER_X/2);
            scroll_inertia.x = 0;
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    pointing_device_set_report(mouse_report);
    pointing_device_send();
}

void eeconfig_init_kb(void) {
	keyboard_config.raw = 0;
    keyboard_config.dpi_config = CHARYBDIS_DPI_DEFAULT;
    keyboard_config.sniper_config = CHARYBDIS_SNIPER_DEFAULT;
    pmw_set_cpi(dpi_array[keyboard_config.dpi_config]);
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    // is safe to just read DPI setting since matrix init
    // comes before pointing device init.
    keyboard_config.raw = eeconfig_read_kb();
    if (keyboard_config.dpi_config >= DPI_OPTION_SIZE ||
            keyboard_config.sniper_config >= SNIPER_OPTION_SIZE) {
        eeconfig_init_kb();
    }
    matrix_init_user();
}