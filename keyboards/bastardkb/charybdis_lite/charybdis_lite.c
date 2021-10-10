/*
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "charybdis_lite.h"
#ifdef POINTING_DEVICE_ENABLE
#include "drivers/sensors/pmw3360.h"
#include "pointing_device.h"
#endif  // POINTING_DEVICE_ENABLE

/**
 * LEDs index.
 *
 * ╭────────────────────╮                 ╭────────────────────╮
 *    2   3   8   9  12                     30  27  26  21  20
 * ├────────────────────┤                 ├────────────────────┤
 *    1   4   7  10  13                     31  28  25  22  19
 * ├────────────────────┤                 ├────────────────────┤
 *    0   5   6  11  14                     32  29  24  23  18
 * ╰────────────────────╯                 ╰────────────────────╯
 *                   15  16  17     XX  XX  XX
 *                 ╰────────────╯ ╰────────────╯
 */
// clang-format off
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    /* Key Matrix to LED index. */
    // Left split.
    {      2,      3,      8,      9,     12 }, // Top row
    {      1,      4,      7,     10,     13 }, // Middle row
    {      0,      5,      6,     11,     14 }, // Bottom row
    {     17, NO_LED,     15,     16, NO_LED }, // Thumb cluster
    // Right split.
    {     20,     21,     26,     27,     30 }, // Top row
    {     19,     22,     25,     28,     31 }, // Middle row
    {     18,     23,     24,     29,     32 }, // Bottom row
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, // Thumb cluster
}, {
    /* LED index to physical position. */
    // Left split.
    /* index=0  */ {   0,  42 }, {   0,  21 }, {   0,   0 }, // col 1 (left most)
    /* index=3  */ {  18,   0 }, {  18,  21 }, {  18,  42 }, // col 2
    /* index=6  */ {  36,  42 }, {  36,  21 }, {  36,   0 },
    /* index=9  */ {  54,   0 }, {  54,  21 }, {  54,  42 },
    /* index=12 */ {  72,   0 }, {  72,  21 }, {  72,  42 },
    /* index=15 */ {  72,  64 }, {  90,  64 }, { 108,  64 }, // Thumb cluster
    // Right split.
    /* index=18 */ { 224,  42 }, { 224,  21 }, { 224,   0 }, // col 10 (right most)
    /* index=21 */ { 206,   0 }, { 206,  21 }, { 206,  42 }, // col 9
    /* index=24 */ { 188,  42 }, { 188,  21 }, { 188,   0 },
    /* index=27 */ { 170,   0 }, { 170,  21 }, { 170,  42 },
    /* index=30 */ { 152,   0 }, { 152,  21 }, { 152,  42 },
}, {
    /* LED index to flag. */
    // Left split.
    /* index=0  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 1
    /* index=3  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 2
    /* index=6  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=9  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=12 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=15 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster
    // Right split.
    /* index=18 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 10
    /* index=21 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 9
    /* index=24 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=27 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=30 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
} };
#endif
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#ifndef CHARYBDIS_DEFAULT_DPI
#define CHARYBDIS_DEFAULT_DPI 500
#endif  // CHARYBDIS_DEFAULT_DPI

#ifndef CHARYBDIS_SNIPER_DPI
#define CHARYBDIS_SNIPER_DPI 200
#endif  // CHARYBDIS_SNIPER_DPI

// Fixed DPI for drag-scroll.
#ifndef CHARYBDIS_DRAGSCROLL_DPI
#define CHARYBDIS_DRAGSCROLL_DPI 100
#endif  // CHARYBDIS_DRAGSCROLL_DPI

#ifndef CHARYBDIS_DRAGSCROLL_INERTIA_FACTOR
#define CHARYBDIS_DRAGSCROLL_INERTIA_FACTOR 6
#endif  // !CHARYBDIS_DRAGSCROLL_INERTIA_FACTOR

#ifndef CHARYBDIS_POINTER_ACCELERATION_FACTOR
#define CHARYBDIS_POINTER_ACCELERATION_FACTOR 24
#endif  // !CHARYBDIS_POINTER_ACCELERATION_FACTOR

typedef struct {
  bool is_dragscroll_enabled : 1;
  bool is_sniper_enabled : 1;
} __attribute__((packed)) charybdis_config_t;

static charybdis_config_t g_charybdis_config = {0};

/** Set the appropriate DPI for the input config. */
static void _maybe_adjust_pmw_cpi(charybdis_config_t* config) {
  if (config->is_dragscroll_enabled) {
    pmw_set_cpi(CHARYBDIS_DRAGSCROLL_DPI);
  } else if (config->is_sniper_enabled) {
    pmw_set_cpi(CHARYBDIS_SNIPER_DPI);
  } else {
    pmw_set_cpi(CHARYBDIS_DEFAULT_DPI);
  }
}

void charybdis_set_pointer_sniper_mode(bool enable) {
  g_charybdis_config.is_sniper_enabled = enable;
  _maybe_adjust_pmw_cpi(&g_charybdis_config);
}

void charybdis_set_pointer_dragscroll_mode(bool enable) {
  g_charybdis_config.is_dragscroll_enabled = enable;
  _maybe_adjust_pmw_cpi(&g_charybdis_config);
}

void pointing_device_init(void) {
  pmw_spi_init();
  pmw_set_cpi(CHARYBDIS_DEFAULT_DPI);
}

#ifndef _CONSTRAIN_TO_INT8
#define _CONSTRAIN_TO_INT8(value) (constrain(value, -127, 127))
#endif  // !_CONSTRAIN_TO_INT8

/**
 * If `CHARYBDIS_ENABLE_POINTER_ACCELERATION` is defined, add a simple and naive
 * acceleration effect to the provided value.  Return the value unchanged
 * otherwise.
 */
#ifndef _DISPLACEMENT_WITH_ACCELERATION
#ifdef CHARYBDIS_ENABLE_POINTER_ACCELERATION
#define _DISPLACEMENT_WITH_ACCELERATION(d)                      \
  (_CONSTRAIN_TO_INT8(                                          \
      d > 0 ? d * d / CHARYBDIS_POINTER_ACCELERATION_FACTOR + d \
            : -d * d / CHARYBDIS_POINTER_ACCELERATION_FACTOR + d))
#else  // !CHARYBDIS_ENABLE_POINTER_ACCELERATION
#define _DISPLACEMENT_WITH_ACCELERATION(d) (_CONSTRAIN_TO_INT8(d))
#endif  // CHARYBDIS_ENABLE_POINTER_ACCELERATION
#endif  // !_DISPLACEMENT_WITH_ACCELERATION

__attribute__((weak)) void process_pmw_report(report_mouse_t* mouse_report,
                                              int16_t dx, int16_t dy) {
  static int16_t scroll_inertia_x = 0;
  static int16_t scroll_inertia_y = 0;
  if (g_charybdis_config.is_dragscroll_enabled) {
    scroll_inertia_x += dx;
    scroll_inertia_y -= dy;
    if (abs(scroll_inertia_x) > CHARYBDIS_DRAGSCROLL_INERTIA_FACTOR) {
      mouse_report->h = _DISPLACEMENT_WITH_ACCELERATION(
          scroll_inertia_x / CHARYBDIS_DRAGSCROLL_INERTIA_FACTOR);
      scroll_inertia_x = 0;
    }
    if (abs(scroll_inertia_y) > CHARYBDIS_DRAGSCROLL_INERTIA_FACTOR) {
      mouse_report->v = _DISPLACEMENT_WITH_ACCELERATION(
          scroll_inertia_y / CHARYBDIS_DRAGSCROLL_INERTIA_FACTOR);
      scroll_inertia_y = 0;
    }
  } else if (g_charybdis_config.is_sniper_enabled) {
    mouse_report->x = _CONSTRAIN_TO_INT8(dx);
    mouse_report->y = _CONSTRAIN_TO_INT8(dy);
  } else {
    mouse_report->x = _DISPLACEMENT_WITH_ACCELERATION(dx);
    mouse_report->y = _DISPLACEMENT_WITH_ACCELERATION(dy);
  }
}

__attribute__((weak)) void process_mouse_report(report_mouse_t* mouse_report) {
  const report_pmw_t pmw_report = pmw_read_burst();
  if (pmw_report.isOnSurface && pmw_report.isMotion) {
    process_pmw_report(mouse_report, -pmw_report.dx, pmw_report.dy);
  }
}

void pointing_device_task(void) {
  report_mouse_t mouse_report = pointing_device_get_report();
  process_mouse_report(&mouse_report);

  pointing_device_set_report(mouse_report);
  pointing_device_send();
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
#ifndef MOUSEKEY_ENABLE
  // Simulate mouse keys if full support is not enabled (reduces firmware size
  // while maintaining support for mouse keys).
  switch (keycode) {
    case KC_MS_BTN1 ... KC_MS_BTN8: {
      report_mouse_t mouse_report = pointing_device_get_report();
      if (record->event.pressed) {
        mouse_report.buttons |= 1 << (keycode - KC_MS_BTN1);
      } else {
        mouse_report.buttons &= ~(1 << (keycode - KC_MS_BTN1));
      }
      pointing_device_set_report(mouse_report);
      pointing_device_send();
      break;
    }
  }
#endif  // !MOUSEKEY_ENABLE

  return process_record_user(keycode, record);
}
#endif  // POINTING_DEVICE_ENABLE
