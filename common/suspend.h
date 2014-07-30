#ifndef SUSPEND_H
#define SUSPEND_H

#include <stdint.h>
#include <stdbool.h>


void suspend_power_down(void);
bool suspend_wakeup_condition(void);
void suspend_wakeup_init(void);

#endif
