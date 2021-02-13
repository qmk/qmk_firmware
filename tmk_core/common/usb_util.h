#pragma once

#include <stdbool.h>

bool usb_active_connection(void);
void usb_disable(void);
bool usb_vbus_state(void);
