#pragma once

#include "report.h"

#ifdef __cplusplus
extern "C" {
#endif

void bluetooth_task(void);
bool bluetooth_is_connected(void);
void bluetooth_unpair(void);
void bluetooth_send_keyboard(report_keyboard_t *report);
void bluetooth_send_consumer(uint16_t keycode);

#ifdef MOUSE_ENABLE
void bluetooth_send_mouse(report_mouse_t *report);
#endif

#ifdef BLUETOOTH_BATTERY_ENABLE
uint8_t bluetooth_get_battery_level_kb(void);
uint8_t bluetooth_get_battery_level_user();
#endif

#ifdef __cplusplus
}
#endif
