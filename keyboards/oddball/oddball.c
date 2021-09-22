/* Copyright 2020 Alexander Tulloh
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
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

#include "oddball.h"
#include "pointing_device.h"
#include "optical_sensor/optical_sensor.h"

#define CLAMP_HID(value) value < -127 ? -127 : value > 127 ? 127 : value

static bool scroll_pressed;
static bool mouse_buttons_dirty;
static int8_t scroll_h;
static int8_t scroll_v;

void pointing_device_init(void){
    if(!is_keyboard_master())
        return;

    optical_sensor_init();

    // read config from EEPROM and update if needed

    config_oddball_t kb_config;
    kb_config.raw = eeconfig_read_kb();

    if(!kb_config.cpi) {
        kb_config.cpi = CPI_2;
        eeconfig_update_kb(kb_config.raw);
    }

    optical_sensor_set_config((config_optical_sensor_t){ kb_config.cpi });
}

void pointing_device_task(void){
    if(!is_keyboard_master())
        return;

    report_mouse_t mouse_report = pointing_device_get_report();
    report_optical_sensor_t sensor_report = optical_sensor_get_report();

    int8_t clamped_x = CLAMP_HID(sensor_report.x);
    int8_t clamped_y = CLAMP_HID(sensor_report.y);

    if(scroll_pressed) {

        // accumulate scroll
        scroll_h += clamped_x;
        scroll_v += clamped_y;

        int8_t scaled_scroll_h = scroll_h / SCROLL_DIVIDER;
        int8_t scaled_scroll_v = scroll_v / SCROLL_DIVIDER;

        // clear accumulated scroll on assignment

        if(scaled_scroll_h != 0){
            mouse_report.h = -scaled_scroll_h;
            scroll_h = 0;
        }

        if(scaled_scroll_v != 0){
            mouse_report.v = -scaled_scroll_v;
            scroll_v = 0;
        }
    }
    else {
        mouse_report.x = -clamped_x;
        mouse_report.y = clamped_y;
    }

    pointing_device_set_report(mouse_report);

    // only send report on change as even sending report with no change is treated as movement
    if(mouse_buttons_dirty ||
       mouse_report.x != 0 ||
       mouse_report.y != 0 ||
       mouse_report.h != 0 ||
       mouse_report.v != 0){

        mouse_buttons_dirty = false;
        pointing_device_send();
    }
}

static void on_cpi_button(uint16_t cpi, keyrecord_t *record) {

    if(!record->event.pressed)
        return;

    optical_sensor_set_config((config_optical_sensor_t){ cpi });

    config_oddball_t kb_config;
    kb_config.cpi = cpi;
    eeconfig_update_kb(kb_config.raw);
}

static void on_mouse_button(uint8_t mouse_button, keyrecord_t *record) {

    report_mouse_t report = pointing_device_get_report();

    if(record->event.pressed)
        report.buttons |= mouse_button;
    else
        report.buttons &= ~mouse_button;

    pointing_device_set_report(report);
    mouse_buttons_dirty = true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if(!process_record_user(keycode, record))
        return false;

    // handle mouse drag and scroll

    switch (keycode) {
        case KC_BTN1:
            on_mouse_button(MOUSE_BTN1, record);
            return false;

        case KC_BTN2:
            on_mouse_button(MOUSE_BTN2, record);
            return false;

        case KC_BTN3:
            on_mouse_button(MOUSE_BTN3, record);
            return false;

        case KC_BTN4:
            on_mouse_button(MOUSE_BTN4, record);
            return false;

        case KC_BTN5:
            on_mouse_button(MOUSE_BTN5, record);
            return false;

        case KC_SCROLL:
            scroll_pressed = record->event.pressed;
            return false;

        case KC_CPI_1:
            on_cpi_button(CPI_1, record);
            return false;

        case KC_CPI_2:
            on_cpi_button(CPI_2, record);
            return false;

        case KC_CPI_3:
            on_cpi_button(CPI_3, record);
            return false;

        default:
            return true;
  }
}
