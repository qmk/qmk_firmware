#ifndef RN42_TASK_H
#define RN42_TASK_H

#include <stdbool.h>
#include "rn42.h"

#ifdef NKRO_ENABLE
bool rn42_nkro_last;
#endif

void rn42_task_init(void);
void rn42_task(void);

#endif
