#ifndef __CLOCK_ARCH_H__
#define __CLOCK_ARCH_H__

#include "global-conf.h"
#include <stdint.h>

typedef uint16_t clock_time_t;
#define CLOCK_CONF_SECOND (F_CPU / 1024 / 255)  //Freqency divided prescaler and counter register size
void clock_init(void);
clock_time_t clock_time(void);

#endif /* __CLOCK_ARCH_H__ */
