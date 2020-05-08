#pragma once

#include "report.h"

void bluetooth_classic_task(void);

void bluetooth_classic_send_keyboard(report_keyboard_t *report);

void bluetooth_classic_send_consumer(uint16_t data, int hold_duration);

#ifdef MOUSE_ENABLE
void bluetooth_classic_send_mouse(report_mouse_t *report);
#endif
