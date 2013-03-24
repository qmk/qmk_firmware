#include "suspend.h"
#include "matrix.h"
#include "action.h"


void suspend_power_down(void)
{
#ifndef NO_SUSPEND_POWER_DOWN
    // Enable watchdog to wake from MCU sleep
    cli();
    wdt_reset();

    // Watchdog Interrupt and System Reset Mode
    //wdt_enable(WDTO_1S);
    //WDTCSR |= _BV(WDIE);
    
    // Watchdog Interrupt Mode
    wdt_intr_enable(WDTO_120MS);
    
    // TODO: more power saving
    // See PicoPower application note
    // - I/O port input with pullup
    // - prescale clock
    // - BOD disable
    // - Power Reduction Register PRR
    // sleep in power down mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();

    // Disable watchdog after sleep
    wdt_disable();
#endif
}

bool suspend_wakeup_condition(void)
{
    matrix_scan();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        if (matrix_get_row(r)) return true;
    }
    return false;
}

void suspend_wakeup_init(void)
{
    matrix_init();
    clear_keyboard();
}
