#include "board.h"
#include <hal.h>

/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
void __chibios_override___early_init(void) {
}

/*
 * Board-specific initialization code.
 */
void __chibios_override_boardInit(void) {

    /* USB */
    palSetLineMode(USBVBUS, MODE_FUNC_ALT1 | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(USBCONN, MODE_FUNC_ALT1);
}
