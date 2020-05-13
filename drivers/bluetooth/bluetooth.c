#include "bluetooth.h"

__attribute__((weak)) void bluetooth_task(void) {}

__attribute__((weak)) bool bluetooth_is_connected(void) { return true; }

__attribute__((weak)) void bluetooth_unpair(void) {}

__attribute__((weak)) void bluetooth_send_keyboard(report_keyboard_t *report) {}

__attribute__((weak)) void bluetooth_send_consumer(uint16_t keycode) {}

#ifdef MOUSE_ENABLE
__attribute__((weak)) void bluetooth_send_mouse(report_mouse_t *report) {}
#endif

#ifdef BLUETOOTH_BATTERY_ENABLE
__attribute__((weak)) uint8_t bluetooth_get_battery_level_kb(void) { return bluetooth_get_battery_level_user(); }

__attribute__((weak)) uint8_t bluetooth_get_battery_level_user() { return 100; }
#endif
