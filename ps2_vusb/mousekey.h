#ifndef MOUSEKEY_H
#define  MOUSEKEY_H

#include <stdbool.h>
#include "host.h"

void mousekey_decode(uint8_t code);
bool mousekey_changed(void);
void mousekey_send(void);
void mousekey_clear_report(void);

#endif
