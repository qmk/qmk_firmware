#ifndef XM04_H
#define XM04_H

#include <stdbool.h>
#include "host.h"

host_driver_t xm04_driver;

void xm04_init(void);

bool bt_powered(void);
void turn_off_bt(void);
void turn_on_bt(void);
void toggle_bt(void);

#endif
