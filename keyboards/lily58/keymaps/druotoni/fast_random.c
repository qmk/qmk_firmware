#include "fast_random.h"

static unsigned long g_seed = 0;
int                  fastrand(void) {
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}

 unsigned long                  fastrand_long(void) {
    g_seed = (214013 * g_seed + 2531011);
   return g_seed;
}
