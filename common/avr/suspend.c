#include <stdbool.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include "matrix.h"
#include "action.h"
#include "backlight.h"
#include "suspend_avr.h"
#include "suspend.h"


#define wdt_intr_enable(value)   \
__asm__ __volatile__ (  \
    "in __tmp_reg__,__SREG__" "\n\t"    \
    "cli" "\n\t"    \
    "wdr" "\n\t"    \
    "sts %0,%1" "\n\t"  \
    "out __SREG__,__tmp_reg__" "\n\t"   \
    "sts %0,%2" "\n\t" \
    : /* no outputs */  \
    : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
    "r" (_BV(_WD_CHANGE_BIT) | _BV(WDE)), \
    "r" ((uint8_t) ((value & 0x08 ? _WD_PS3_MASK : 0x00) | \
        _BV(WDIE) | (value & 0x07)) ) \
    : "r0"  \
)


void suspend_power_down(void)
{
#ifdef BACKLIGHT_ENABLE
    backlight_set(0);
#endif
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

// run immediately after wakeup
void suspend_wakeup_init(void)
{
    // clear keyboard state
    clear_keyboard();
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif
}

#ifndef NO_SUSPEND_POWER_DOWN
/* watchdog timeout */
ISR(WDT_vect)
{
    /* wakeup from MCU sleep mode */
/*
    // blink LED
    static uint8_t led_state = 0;
    static uint8_t led_count = 0;
    led_count++;
    if ((led_count & 0x07) == 0) {
        led_set((led_state ^= (1<<USB_LED_CAPS_LOCK)));
    }
*/
}
#endif
