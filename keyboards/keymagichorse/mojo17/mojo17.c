#include "quantum.h"

#if defined(BLUETOOTH_BHQ)
#   include "bhq.h"
#   include "bhq_common.h"
#endif

#if defined(KB_LPM_ENABLED)
#   include "lpm.h"
#endif

#if defined(KM_DEBUG)
#   include "km_printf.h"
#endif

void board_init(void) {
#if defined(BLUETOOTH_BHQ)
#   if defined(KB_LPM_ENABLED)
    lpm_init();
#   endif
#endif

#   if defined(KM_DEBUG)
    km_printf_init();
    km_printf("hello rtt log1111111\r\n");
#   endif
}

void housekeeping_task_kb(void) {
#if defined(BLUETOOTH_BHQ)
    bhq_switch_host_task();
    #   if defined(KB_LPM_ENABLED)
        lpm_task();
    #   endif
#endif
}
