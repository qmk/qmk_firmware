/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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
#include QMK_KEYBOARD_H
#include <string.h>

// definitions

#define RECORD_SIZE 4
#ifndef PLOOPY_DRAGMEDIA_DPI
#define PLOOPY_DRAGMEDIA_DPI 800
#endif

// enumerators

enum extra_ploopy_keycodes {
  DRAG_MEDIA = PLOOPY_SAFE_RANGE,
  OMNI_WHEEL
};

// variables

bool is_drag_media = false;
bool is_omni_wheel = false;
bool btn_pressed = false;
int move_array[10][2];
int save_row = 0;
int aver_x, aver_y = 0;
int pointer_heading;
static uint16_t timer;

// functions

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_NO, KC_BTN1, KC_BTN3, KC_BTN2, DPI_CONFIG, DRAG_MEDIA, OMNI_WHEEL, RESET)
    // defaults: most left, left, middle, right, most right, lower side, upper side, underneath scoll
};

void keyboard_post_init_user(void) {
  #ifdef CONSOLE_ENABLE
    debug_enable=true;
  #endif
  timer = timer_read();
}

void smoothen_pointer_movement(int x, int y) {
  move_array[save_row][0] = x;
  move_array[save_row][1] = y;
  save_row = (save_row + 1) % RECORD_SIZE;
  for(int j=0;j<RECORD_SIZE;j++) {
    aver_x += move_array[j][0];
    aver_y += move_array[j][1];
  }
  aver_x /= RECORD_SIZE;
  aver_y /= RECORD_SIZE;
  if (debug_enable) dprintf("Mouse R/L: %d, Mouse U/D: %d. Filtered, R/L: %d, U/D: %d\n", x, y, aver_x, aver_y); // debug
}

// convert x,y offset to a cardianal direction
// 1 = North, 2 = Northwest, 3 = West, etc.
int direction(int x, int y)
{
    // get angle in radians assuming starting point is 0,0 (scale: -1*pi ~ 1*pi)
    float angle = atan2(y, x);
    // devide by pi for some more managable numbers (scale: -1 ~ 1)
    angle = angle / M_PI;
    // add an offset of 1 so we don't have negative results. (scale: 0 ~ 2)
    angle = angle + 1;
    // rotate by 3/16 of the circle (2/16*3 = 0.375) so "0" points to NNW.
    angle = angle - 0.375;
    if(angle < 0) angle = angle + 2;
    // scale to 8 equal parts and cast to int.
    return (int)(angle / 0.25);
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  if (!(is_drag_media || is_omni_wheel)) {
    btn_pressed = false;
    return mouse_report;
  }
  smoothen_pointer_movement(mouse_report.x, mouse_report.y);
  // if (debug_enable) dprintf("Mouse R/L: %d, Mouse U/D: %d\n", mouse_report.x, mouse_report.y); // debug
  // if (is_drag_media) {
  //   if (abs(aver_x) > abs(aver_y) && abs(aver_x) > 3) {
  //     if (timer_elapsed(timer) < BTN_TAP_TIMEOUT) {
  //       mouse_report.x = 0;
  //       return mouse_report;
  //     }
  //     if (aver_x > 0) {
  //       tap_code(KC_MNXT);
  //     } else {
  //       tap_code(KC_MPRV);
  //     }
  //     timer = timer_read();
  //   } else {
  //     for(int i=0;i<abs(mouse_report.y);i+=10) {
  //       if (mouse_report.y>0) {
  //         tap_code(KC_VOLD);
  //       } else {
  //         tap_code(KC_VOLU);
  //       }
  //     }
  //   }
  // }
  if (is_omni_wheel) {
    if (btn_pressed == false && (abs(aver_x) > 0 || abs(aver_y) > 0)) {
      pointer_heading = direction(aver_x, aver_y);
      if (debug_enable) dprintf("Direction: %d\n", pointer_heading);
      switch (pointer_heading) {
        case 0:
          tap_code(KC_1);
          break;
        case 1:
          tap_code(KC_2);
          break;
        case 2:
          tap_code(KC_3);
          break;
        case 3:
          tap_code(KC_4);
          break;
        case 4:
          tap_code(KC_5);
          break;
        case 5:
          tap_code(KC_6);
          break;
        case 6:
          tap_code(KC_7);
          break;
        case 7:
          tap_code(KC_8);
          break;
      }
      btn_pressed = true;
      // save_row = 0;
      // memset(move_array, 0, sizeof(move_array));
    }
  }
  mouse_report.x = 0;
  mouse_report.y = 0;
  return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case DRAG_MEDIA:
      if (record->event.pressed) {
        is_drag_media = true;
        pointing_device_set_cpi(PLOOPY_DRAGMEDIA_DPI);
      } else {
        is_drag_media = false;
        pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
      }
      return false;
      break;
    case OMNI_WHEEL:
      if (record->event.pressed) {
        is_omni_wheel = true;
        pointing_device_set_cpi(PLOOPY_DRAGMEDIA_DPI);
      } else {
        is_omni_wheel = false;
        pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
      }
      return false;
      break;
  }
  return true;
}

void matrix_power_up(void) { pointing_device_task(); }
