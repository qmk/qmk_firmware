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

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif  // CONSOLE_ENABLE

#ifdef POINTING_DEVICE_ENABLE
#ifndef CHARYBDIS_MINIMUM_DEFAULT_DPI
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 400
#endif  // CHARYBDIS_MINIMUM_DEFAULT_DPI

#ifndef CHARYBDIS_DEFAULT_DPI_CONFIG_STEP
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 200
#endif  // CHARYBDIS_DEFAULT_DPI_CONFIG_STEP

#ifndef CHARYBDIS_MINIMUM_SNIPING_DPI
#define CHARYBDIS_MINIMUM_SNIPING_DPI 200
#endif  // CHARYBDIS_MINIMUM_SNIPER_MODE_DPI

#ifndef CHARYBDIS_SNIPING_DPI_CONFIG_STEP
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 100
#endif  // CHARYBDIS_SNIPING_DPI_CONFIG_STEP

// Fixed DPI for drag-scroll.  TODO(delay): implemented variable drag-scroll.
#ifndef CHARYBDIS_DRAGSCROLL_DPI
#define CHARYBDIS_DRAGSCROLL_DPI 100
#endif  // CHARYBDIS_DRAGSCROLL_DPI

#ifndef CHARYBDIS_DRAGSCROLL_INERTIA_FACTOR
#define CHARYBDIS_DRAGSCROLL_INERTIA_FACTOR 6
#endif  // !CHARYBDIS_DRAGSCROLL_INERTIA_FACTOR

#ifndef CHARYBDIS_POINTER_ACCELERATION_FACTOR
#define CHARYBDIS_POINTER_ACCELERATION_FACTOR 24
#endif  // !CHARYBDIS_POINTER_ACCELERATION_FACTOR

typedef union {
  uint8_t raw;
  struct {
    uint8_t pointer_default_dpi : 4;  // 16 steps available.
    uint8_t pointer_sniping_dpi : 2;  // 4 steps available.
    bool is_dragscroll_enabled : 1;
    bool is_sniping_enabled : 1;
  } __attribute__((packed));
} charybdis_config_t;

static charybdis_config_t g_charybdis_config = {0};

/**
 * Set the value of `config` from EEPROM.
 *
 * Note that `is_dragscroll_enabled` and `is_sniping_enabled` are purposefully
 * ignored since we do not want to persist this state to memory.  In practice,
 * this state is always written to maximize write-performances.  Therefore, we
 * explicitly set them to `false` in this function.
 */
static void _read_charybdis_config_from_eeprom(charybdis_config_t* config) {
  config->raw = eeconfig_read_kb() & 0xff;
  config->is_dragscroll_enabled = false;
  config->is_sniping_enabled = false;
}

/**
 * Save the value of `config` to eeprom.
 *
 * Note that all values are written verbatim, including whether drag-scroll
 * and/or sniper mode are enabled.  `_read_charybdis_config_from_eeprom(…)`
 * resets these 2 values to `false` since it does not make sense to persist
 * these across reboots of the board.
 */
static void _write_charybdis_config_to_eeprom(charybdis_config_t* config) {
  eeconfig_update_kb(config->raw);
}

/** Return the current value of the pointer's default DPI. */
static uint32_t _get_pointer_default_dpi(charybdis_config_t* config) {
  return (uint32_t)config->pointer_default_dpi *
             CHARYBDIS_DEFAULT_DPI_CONFIG_STEP +
         CHARYBDIS_MINIMUM_DEFAULT_DPI;
}

/** Return the current value of the pointer's sniper-mode DPI. */
static uint32_t _get_pointer_sniping_dpi(charybdis_config_t* config) {
  return (uint32_t)config->pointer_sniping_dpi *
             CHARYBDIS_SNIPING_DPI_CONFIG_STEP +
         CHARYBDIS_MINIMUM_SNIPING_DPI;
}

/** Set the appropriate DPI for the input config. */
static void _maybe_adjust_pmw_cpi(charybdis_config_t* config) {
  if (config->is_dragscroll_enabled) {
    pmw_set_cpi(CHARYBDIS_DRAGSCROLL_DPI);
  } else if (config->is_sniping_enabled) {
    pmw_set_cpi(_get_pointer_sniping_dpi(config));
  } else {
    pmw_set_cpi(_get_pointer_default_dpi(config));
  }
}

/**
 * Update the pointer's default DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to CHARYBDIS_DEFAULT_DPI_CONFIG_STEP.
 */
static void _step_pointer_default_dpi(charybdis_config_t* config,
                                      bool forward) {
  config->pointer_default_dpi += forward ? 1 : -1;
  _maybe_adjust_pmw_cpi(config);
}

/**
 * Update the pointer's sniper-mode DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to CHARYBDIS_SNIPING_DPI_CONFIG_STEP.
 */
static void _step_pointer_sniping_dpi(charybdis_config_t* config,
                                      bool forward) {
  config->pointer_sniping_dpi += forward ? 1 : -1;
  _maybe_adjust_pmw_cpi(config);
}

uint32_t charybdis_get_pointer_default_dpi(void) {
  return _get_pointer_default_dpi(&g_charybdis_config);
}

uint32_t charybdis_get_pointer_sniping_dpi(void) {
  return _get_pointer_sniping_dpi(&g_charybdis_config);
}

void charybdis_cycle_pointer_default_dpi_noeeprom(bool forward) {
  _step_pointer_default_dpi(&g_charybdis_config, forward);
}

void charybdis_cycle_pointer_default_dpi(bool forward) {
  _step_pointer_default_dpi(&g_charybdis_config, forward);
  _write_charybdis_config_to_eeprom(&g_charybdis_config);
}

void charybdis_cycle_pointer_sniping_dpi_noeeprom(bool forward) {
  _step_pointer_sniping_dpi(&g_charybdis_config, forward);
}

void charybdis_cycle_pointer_sniping_dpi(bool forward) {
  _step_pointer_sniping_dpi(&g_charybdis_config, forward);
  _write_charybdis_config_to_eeprom(&g_charybdis_config);
}

bool charybdis_get_pointer_sniping_enabled(void) {
  return g_charybdis_config.is_sniping_enabled;
}

void charybdis_set_pointer_sniping_enabled(bool enable) {
  g_charybdis_config.is_sniping_enabled = enable;
  _maybe_adjust_pmw_cpi(&g_charybdis_config);
}

bool charybdis_get_pointer_dragscroll_enabled(void) {
  return g_charybdis_config.is_dragscroll_enabled;
}

void charybdis_set_pointer_dragscroll_enabled(bool enable) {
  g_charybdis_config.is_dragscroll_enabled = enable;
  _maybe_adjust_pmw_cpi(&g_charybdis_config);
}

void pointing_device_init(void) {
  pmw_spi_init();
  _maybe_adjust_pmw_cpi(&g_charybdis_config);
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
  } else if (g_charybdis_config.is_sniping_enabled) {
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
#ifdef CONSOLE_ENABLE
  uprintf(
      "(charybdis) process_record_kb: config = {\n"
      "\traw = 0x%04X,\n"
      "\t{\n"
      "\t\tis_dragscroll_enabled=%b\n"
      "\t\tis_sniping_enabled=%b\n"
      "\t\tdefault_dpi=0x%02X (%ld)\n"
      "\t\tsniping_dpi=0x%01X (%ld)\n"
      "\t}\n"
      "}\n",
      g_charybdis_config.raw, g_charybdis_config.is_dragscroll_enabled,
      g_charybdis_config.is_sniping_enabled,
      g_charybdis_config.pointer_default_dpi,
      charybdis_get_pointer_default_dpi(),
      g_charybdis_config.pointer_sniping_dpi,
      charybdis_get_pointer_sniping_dpi());
#endif  // CONSOLE_ENABLE
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

void eeconfig_init_kb(void) {
  g_charybdis_config.raw = 0;
  _write_charybdis_config_to_eeprom(&g_charybdis_config);
  _maybe_adjust_pmw_cpi(&g_charybdis_config);
  eeconfig_init_user();
}

void matrix_init_kb(void) {
  _read_charybdis_config_from_eeprom(&g_charybdis_config);
  matrix_init_user();
}
#endif  // POINTING_DEVICE_ENABLE
