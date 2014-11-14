#include <stdbool.h>
#include "debug.h"

#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

debug_config_t debug_config = {
#if GCC_VERSION >= 40600
    /* GCC Bug 10676 - Using unnamed fields in initializers
     * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=10676 */
    .enable = false,
    .matrix = false,
    .keyboard = false,
    .mouse = false,
#endif
};
