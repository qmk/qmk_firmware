#include <avr/sfr_defs.h>
#include <avr/timer_avr.h>
#include <avr/wdt.h>
#include "lfk65_hs.h"
#include "keymap.h"

void matrix_init_kb(void)
{
    matrix_init_user();

}

void matrix_scan_kb(void)
{
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record)
{
    /* FIXME(skullydazed):
     *     Originally this code always ran no matter what process_record_user() did.
     *     With this PR it will only run if process_record_user() returns true. We
     *     should think through the implications here.
     */
    if (keycode == RESET) {
        reset_keyboard_kb();
    } else {
    }
    return true;
}

void reset_keyboard_kb(){
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif
    reset_keyboard();
}
