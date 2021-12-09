#include "fast_random.h"

// seed for random
static unsigned long g_seed = 0;

// black magic for an int
int                  fastrand(void) {
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}

// black magic for an insigned long
 unsigned long                  fastrand_long(void) {
    g_seed = (214013 * g_seed + 2531011);
   return g_seed;
}
