/*
Copyright 2018 Sekigon

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

#include <stdbool.h>
#include "app_ble_func.h"
#include "keycode_str_converter.h"
#include "config_file_util.h"

/* TMK includes */
#include "report.h"
#include "host.h"
#include "host_driver.h"
#include "keyboard.h"
#include "action.h"
#include "action_util.h"
#include "mousekey.h"
#include "led.h"
#include "sendchar.h"
#include "debug.h"
#include "printf.h"
#ifdef SLEEP_LED_ENABLE
#include "sleep_led.h"
#endif
#ifdef SERIAL_LINK_ENABLE
#include "serial_link/system/serial_link.h"
#endif
#ifdef VISUALIZER_ENABLE
#include "visualizer/visualizer.h"
#endif
#ifdef MIDI_ENABLE
#include "qmk_midi.h"
#endif
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif
#include "suspend.h"
#include "wait.h"
#include "matrix.h"

#include "apidef.h"
#include "cli.h"
#include "configurator.h"
#include "bmp.h"
#include "bmp_config.h"
#include "bmp_encoder.h"
#include "bmp_indicator_led.h"

#ifndef MATRIX_SCAN_TIME_MS
#define MATRIX_SCAN_TIME_MS 17
#endif
const uint8_t MAINTASK_INTERVAL=MATRIX_SCAN_TIME_MS;

/* -------------------------
 *   TMK host driver defs
 * -------------------------
 */

/* declarations */
uint8_t keyboard_leds(void);
void send_keyboard(report_keyboard_t *report);
void send_mouse(report_mouse_t *report);
void send_system(uint16_t data);
void send_consumer(uint16_t data);
void sendchar_pf(void *p, char c);

/* host struct */
host_driver_t nrf_ble_driver = {
  keyboard_leds,
  send_keyboard,
  send_mouse,
  send_system,
  send_consumer
};
rgblight_syncinfo_t rgblight_sync;

#ifdef VIRTSER_ENABLE
void virtser_task(void);
#endif

#ifdef RAW_HID_ENABLE
void raw_hid_task(void);
#endif

#ifdef CONSOLE_ENABLE
void console_task(void);
void console_task(void) {
    // TODO implement here
}
#endif
void timer_tick(uint8_t interval);
void main_tasks(void* context) {
//  UNUSED_PARAMETER(p_context);
  /* Main loop */
  timer_tick(MAINTASK_INTERVAL);

  bmp_indicator_task(MAINTASK_INTERVAL);

  if (BMPAPI->app.get_config()->mode == SPLIT_SLAVE)
  {
    matrix_scan();
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_ANIMATIONS)
    rgblight_task();
#endif
  }
  else
  {
    bmp_keyboard_task();
#ifdef CONSOLE_ENABLE
    console_task();
#endif
#ifdef VIRTSER_ENABLE
    virtser_task();
#endif
#ifdef RAW_HID_ENABLE
    raw_hid_task();
#endif
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_ANIMATIONS)
    rgblight_task();

    if (rgblight_get_change_flags()) {
      rgblight_get_syncinfo(&rgblight_sync);
      BMPAPI->ble.nus_send_bytes((uint8_t*)&rgblight_sync, sizeof(rgblight_sync));
      rgblight_clear_change_flags();
    }
#endif
  }
}

uint8_t keyboard_idle __attribute__((aligned(2))) = 0;
uint8_t keyboard_protocol __attribute__((aligned(2))) = 1;
uint16_t keyboard_led_stats __attribute__((aligned(2))) = 0;
uint8_t keyboard_leds(void) {
    return 0;
}

void send_keyboard(report_keyboard_t *report) {
  if (get_ble_enabled()) {
    BMPAPI->ble.send_key((bmp_api_key_report_t*)report);
  }
  if (get_usb_enabled()) {
    BMPAPI->usb.send_key((bmp_api_key_report_t*)report);
  }
}
_Static_assert(sizeof(report_keyboard_t) == sizeof(bmp_api_key_report_t),
        "Invalid report definition. Check SHARED_EP options");

void send_mouse(report_mouse_t *report) {
  if (get_ble_enabled()) {
    static bool is_zeros_send = false;
    if (report->buttons == 0 && report->x == 0 && report->y == 0
        && report->v == 0 && report->h ==0) {
      if (is_zeros_send) {
        // skip no move packet if it has been already send
        return;
      }
      else {
        is_zeros_send = true;
      }
    }
    else {
      is_zeros_send = false;
    }

    BMPAPI->ble.send_mouse((bmp_api_mouse_report_t*)report);
  }

  if (get_usb_enabled()) {
    BMPAPI->usb.send_mouse((bmp_api_mouse_report_t*)report);
  }
}

_Static_assert(sizeof(report_mouse_t) == sizeof(bmp_api_mouse_report_t),
        "Invalid report definition. Check MOUSE_SHARED_EP options");

void send_system(uint16_t data) {
  if (get_ble_enabled()) {
    BMPAPI->ble.send_system(data);
  }
  if (get_usb_enabled()) {
    BMPAPI->usb.send_system(data);
  }
}

void send_consumer(uint16_t data) {
  if (get_ble_enabled()) {
    BMPAPI->ble.send_consumer(data);
  }
  if (get_usb_enabled()) {
    BMPAPI->usb.send_consumer(data);
  }
}

void serial_putc(void *p, char c) {
  BMPAPI->usb.serial_putc(c);
}

/**@brief Function for application main entry.
 */
int main(void) {

  bmp_init();

  init_printf(NULL, serial_putc);
  host_driver_t* driver = NULL;
  driver = &nrf_ble_driver;

  keyboard_init();
  host_set_driver(driver);

  const bmp_api_config_t * config = BMPAPI->app.get_config();

  rgblight_set_clipping_range(0, config->led.num);
  rgblight_set_effect_range(0, config->led.num);

  bmp_indicator_init(config->reserved[1]);

  BMPAPI->app.main_task_start(main_tasks, MAINTASK_INTERVAL);
  bmp_encoder_init(get_bmp_encoder_config());

  for (;;) {
    BMPAPI->app.process_task();
    BMPAPI->usb.process();
    cli_exec();
  }
}
