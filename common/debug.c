#include <stdbool.h>
#include "debug.h"

#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

debug_config_t debug_config = {
/* GCC Bug 10676 - Using unnamed fields in initializers
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=10676 */
#if GCC_VERSION >= 40600
    .enable = false,
    .matrix = false,
    .keyboard = false,
    .mouse = false,
    .reserved = 0
#else
    {
        false,  // .enable
        false,  // .matrix
        false,  // .keyboard
        false,  // .mouse
        0       // .reserved
    }
#endif
};
