/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include "keycode.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "mousekey.h"

static report_mouse_t mouse_report = {};
enum {
  mkspd_slow,
  mkspd_med,
  mkspd_fast,
  mkspd_COUNT
};
#ifdef MK_MOMENTARY_ACCEL
static uint8_t mkspd_DEFAULT = mkspd_med;
#endif
static uint8_t mk_speed = mkspd_med;
static uint16_t last_timer   = 0;
static uint16_t last_timer_c = 0;
static uint16_t last_timer_w = 0;
uint16_t c_offsets[mkspd_COUNT] = {
  MK_C_OFFSET_SLOW, MK_C_OFFSET_MED, MK_C_OFFSET_FAST
};
uint16_t c_intervals[mkspd_COUNT] = {
  MK_C_INTERVAL_SLOW, MK_C_INTERVAL_MED, MK_C_INTERVAL_FAST
};
uint16_t w_offsets[mkspd_COUNT] = {
  MK_W_OFFSET_SLOW, MK_W_OFFSET_MED, MK_W_OFFSET_FAST
};
uint16_t w_intervals[mkspd_COUNT] = {
  MK_W_INTERVAL_SLOW, MK_W_INTERVAL_MED, MK_W_INTERVAL_FAST
};

inline int8_t times_inv_sqrt2(int8_t x) {
  // 181/256 is pretty close to 1/sqrt(2)
  // 0.70703125                 0.707106781
  // 1 too small for x=99 and x=198
  // This ends up being a mult and discard lower 8 bits
  return (x * 181) >> 8;
}

void mousekey_task(void) {
  // report cursor and scroll movement independently
  report_mouse_t const tmpmr = mouse_report;
  if ((mouse_report.x  ||  mouse_report.y)  &&  timer_elapsed(last_timer_c) > c_intervals[mk_speed]) {
  mouse_report.h = 0;
  mouse_report.v = 0;
  mousekey_send();
  last_timer_c = last_timer;
  mouse_report = tmpmr;
  }
  if ((mouse_report.h  ||  mouse_report.v)  &&  timer_elapsed(last_timer_w) > w_intervals[mk_speed]) {
  mouse_report.x = 0;
  mouse_report.y = 0;
  mousekey_send();
  last_timer_w = last_timer;
  mouse_report = tmpmr;
  }
}

void adjust_speed(void) {
  uint16_t const c_offset = c_offsets[mk_speed];
  uint16_t const w_offset = w_offsets[mk_speed];
  if (mouse_report.x > 0) mouse_report.x = c_offset;
  if (mouse_report.x < 0) mouse_report.x = c_offset * -1;
  if (mouse_report.y > 0) mouse_report.y = c_offset;
  if (mouse_report.y < 0) mouse_report.y = c_offset * -1;
  if (mouse_report.h > 0) mouse_report.h = w_offset;
  if (mouse_report.h < 0) mouse_report.h = w_offset * -1;
  if (mouse_report.v > 0) mouse_report.v = w_offset;
  if (mouse_report.v < 0) mouse_report.v = w_offset * -1;
  // adjust for diagonals
  if (mouse_report.x && mouse_report.y) {
  mouse_report.x = times_inv_sqrt2(mouse_report.x);
  mouse_report.y = times_inv_sqrt2(mouse_report.y);
  }
  if (mouse_report.h && mouse_report.v) {
  mouse_report.h = times_inv_sqrt2(mouse_report.h);
  mouse_report.v = times_inv_sqrt2(mouse_report.v);
  }
}

void mousekey_on(uint8_t code) {
  uint16_t const c_offset = c_offsets[mk_speed];
  uint16_t const w_offset = w_offsets[mk_speed];
  uint8_t const old_speed = mk_speed;
  if      (code == KC_MS_UP)       mouse_report.y = c_offset * -1;
  else if (code == KC_MS_DOWN)     mouse_report.y = c_offset;
  else if (code == KC_MS_LEFT)     mouse_report.x = c_offset * -1;
  else if (code == KC_MS_RIGHT)    mouse_report.x = c_offset;
  else if (code == KC_MS_WH_UP)    mouse_report.v = w_offset;
  else if (code == KC_MS_WH_DOWN)  mouse_report.v = w_offset * -1;
  else if (code == KC_MS_WH_LEFT)  mouse_report.h = w_offset * -1;
  else if (code == KC_MS_WH_RIGHT) mouse_report.h = w_offset;
  else if (code == KC_MS_BTN1)     mouse_report.buttons |= MOUSE_BTN1;
  else if (code == KC_MS_BTN2)     mouse_report.buttons |= MOUSE_BTN2;
  else if (code == KC_MS_BTN3)     mouse_report.buttons |= MOUSE_BTN3;
  else if (code == KC_MS_BTN4)     mouse_report.buttons |= MOUSE_BTN4;
  else if (code == KC_MS_BTN5)     mouse_report.buttons |= MOUSE_BTN5;
  else if (code == KC_MS_ACCEL0)   mk_speed = mkspd_slow;
  else if (code == KC_MS_ACCEL1)   mk_speed = mkspd_med;
  else if (code == KC_MS_ACCEL2)   mk_speed = mkspd_fast;
  if (mk_speed != old_speed) adjust_speed();
}

void mousekey_off(uint8_t code) {
#ifdef MK_MOMENTARY_ACCEL
  uint8_t const old_speed = mk_speed;
#endif
  if      (code == KC_MS_UP       && mouse_report.y < 0) mouse_report.y = 0;
  else if (code == KC_MS_DOWN     && mouse_report.y > 0) mouse_report.y = 0;
  else if (code == KC_MS_LEFT     && mouse_report.x < 0) mouse_report.x = 0;
  else if (code == KC_MS_RIGHT    && mouse_report.x > 0) mouse_report.x = 0;
  else if (code == KC_MS_WH_UP    && mouse_report.v > 0) mouse_report.v = 0;
  else if (code == KC_MS_WH_DOWN  && mouse_report.v < 0) mouse_report.v = 0;
  else if (code == KC_MS_WH_LEFT  && mouse_report.h < 0) mouse_report.h = 0;
  else if (code == KC_MS_WH_RIGHT && mouse_report.h > 0) mouse_report.h = 0;
  else if (code == KC_MS_BTN1) mouse_report.buttons &= ~MOUSE_BTN1;
  else if (code == KC_MS_BTN2) mouse_report.buttons &= ~MOUSE_BTN2;
  else if (code == KC_MS_BTN3) mouse_report.buttons &= ~MOUSE_BTN3;
  else if (code == KC_MS_BTN4) mouse_report.buttons &= ~MOUSE_BTN4;
  else if (code == KC_MS_BTN5) mouse_report.buttons &= ~MOUSE_BTN5;
#ifdef MK_MOMENTARY_ACCEL
  else if (code == KC_MS_ACCEL0) mk_speed = mkspd_DEFAULT;
  else if (code == KC_MS_ACCEL1) mk_speed = mkspd_DEFAULT;
  else if (code == KC_MS_ACCEL2) mk_speed = mkspd_DEFAULT;
  if (mk_speed != old_speed) adjust_speed();
#endif
}

static void mousekey_debug(void) {
  if (!debug_mouse) return;
  print("mousekey [btn|x y v h](rep/acl): [");
  phex(mouse_report.buttons); print("|");
  print_decs(mouse_report.x); print(" ");
  print_decs(mouse_report.y); print(" ");
  print_decs(mouse_report.v); print(" ");
  print_decs(mouse_report.h); print("](");
}

void mousekey_send(void) {
  mousekey_debug();
  host_mouse_send(&mouse_report);
  last_timer = timer_read();
}

void mousekey_clear(void) {
  mouse_report = (report_mouse_t){0};
}
