/* Bluetooth Low Energy Protocol for QMK.
 * Author: Wez Furlong, 2016
 * Supports the Adafruit BLE board built around the nRF51822 chip.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "report.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Instruct the module to enable HID keyboard support and reset */
extern bool bluefruit_le_enable_keyboard(void);

/* Query to see if the BLE module is connected */
extern bool bluefruit_le_query_is_connected(void);

/* Returns true if we believe that the BLE module is connected.
 * This uses our cached understanding that is maintained by
 * calling ble_task() periodically. */
extern bool bluefruit_le_is_connected(void);

extern void bluefruit_le_init(void);

/* Call this periodically to process BLE-originated things */
extern void bluefruit_le_task(void);

/* Generates keypress events for a set of keys.
 * The hid modifier mask specifies the state of the modifier keys for
 * this set of keys.
 * Also sends a key release indicator, so that the keys do not remain
 * held down. */
extern void bluefruit_le_send_keyboard(report_keyboard_t *report);

/* Send a consumer usage.
 * (milliseconds) */
extern void bluefruit_le_send_consumer(uint16_t usage);

/* Send a mouse/wheel movement report.
 * The parameters are signed and indicate positive or negative direction
 * change. */
extern void bluefruit_le_send_mouse(report_mouse_t *report);

/* Compute battery voltage by reading an analog pin.
 * Returns the integer number of millivolts */
extern uint32_t bluefruit_le_read_battery_voltage(void);

extern bool bluefruit_le_set_mode_leds(bool on);
extern bool bluefruit_le_set_power_level(int8_t level);

#ifdef __cplusplus
}
#endif
