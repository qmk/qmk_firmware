// Need to override the SysTick timer to use TIM3 -- this is a 16-bit timer on F303
// so we need to change resolution and frequency to match.
#define CH_CFG_ST_RESOLUTION 16
#define CH_CFG_ST_FREQUENCY 10000
#include_next "chconf.h"
