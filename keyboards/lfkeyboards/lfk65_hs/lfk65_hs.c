#include "lfk65_hs.h"
#include <avr/wdt.h>

bool process_record_kb(uint16_t keycode, keyrecord_t* record)
{
    if (keycode == QK_BOOT) {
        reset_keyboard_kb();
    }
    return process_record_user(keycode, record);
}

void reset_keyboard_kb(void){
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif
    reset_keyboard();
}
