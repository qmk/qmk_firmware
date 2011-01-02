#ifndef MOUSEKEY_H
#define  MOUSEKEY_H

#include <stdbool.h>

void mousekey_decode(uint8_t code);
bool mousekey_changed(void);
void mousekey_usb_send(void);

#endif

