/* Bluetooth Low Energy Protocol for QMK.
 * Author: Wez Furlong, 2016
 * Supports the Adafruit BLE board built around the nRF51822 chip.
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "config_common.h"
#include "progmem.h"
#include "report.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Returns true if we believe that the BLE module is connected.
 * This uses our cached understanding that is maintained by
 * calling ble_task() periodically. */
extern bool adafruit_ble_is_connected(void);

/* Call this periodically to process BLE-originated things */
extern void adafruit_ble_task(void);

/* Generates keypress events for a set of keys.
 * The hid modifier mask specifies the state of the modifier keys for
 * this set of keys.
 * Also sends a key release indicator, so that the keys do not remain
 * held down. */
extern bool adafruit_ble_send_keyboard(report_keyboard_t *report);

/* Send a consumer keycode, holding it down for the specified duration
 * (milliseconds) */
extern bool adafruit_ble_send_consumer(uint16_t keycode, int hold_duration);

extern bool adafruit_ble_unpair(void);

#ifdef MOUSE_ENABLE
/* Send a mouse/wheel movement report.
 * The parameters are signed and indicate positive of negative direction
 * change. */
extern bool adafruit_ble_send_mouse(report_mouse_t *report);
#endif

#ifdef __cplusplus
}
#endif
