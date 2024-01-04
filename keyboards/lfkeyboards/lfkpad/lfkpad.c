#include "quantum.h"
#include <avr/wdt.h>

void matrix_init_kb(void) {
    matrix_init_user();

#ifdef WATCHDOG_ENABLE
    // This is done after turning the layer LED red, if we're caught in a loop
    // we should get a flashing red light
    wdt_enable(WDTO_500MS);
#endif
}

void matrix_scan_kb(void) {
#ifdef WATCHDOG_ENABLE
    wdt_reset();
#endif

    matrix_scan_user();
}
