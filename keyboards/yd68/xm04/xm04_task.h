#ifndef XM04_TASK_H
#define XM04_TASK_H

#include <stdbool.h>
#include "xm04.h"

#ifdef NKRO_ENABLE
bool xm04_nkro_last;
#endif

void xm04_task_init(void);
void xm04_task(void);

#endif
