#ifndef __CLOCK_ARCH_H__
#define __CLOCK_ARCH_H__

#include <stdint.h>
#include <util/atomic.h>

typedef uint16_t clock_time_t;
#define CLOCK_SECOND 100
void clock_init(void);
clock_time_t clock_time(void);

#endif /* __CLOCK_ARCH_H__ */

