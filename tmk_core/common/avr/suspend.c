#include <stdbool.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include "matrix.h"
#include "action.h"
#include "backlight.h"
#include "suspend_avr.h"
#include "suspend.h"
#include "timer.h"
#include "led.h"
#include "host.h"

#ifdef PROTOCOL_LUFA
	#include "lufa.h"
#endif

#ifdef AUDIO_ENABLE
    #include "audio.h"
#endif /* AUDIO_ENABLE */

#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
  #include "rgblight.h"
#endif


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


/** \brief Suspend idle
 *
 * FIXME: needs doc
 */
void suspend_idle(uint8_t time)
{
    cli();
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();
}

#ifndef NO_SUSPEND_POWER_DOWN
/** \brief Power down MCU with watchdog timer
 *
 * wdto: watchdog timer timeout defined in <avr/wdt.h>
 *          WDTO_15MS
 *          WDTO_30MS
 *          WDTO_60MS
 *          WDTO_120MS
 *          WDTO_250MS
 *          WDTO_500MS
 *          WDTO_1S
 *          WDTO_2S
 *          WDTO_4S
 *          WDTO_8S
 */
static uint8_t wdt_timeout = 0;

/** \brief Run keyboard level Power down
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void suspend_power_down_user (void) { }
/** \brief Run keyboard level Power down
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void suspend_power_down_kb(void) {
  suspend_power_down_user();
}

/** \brief Power down
 *
 * FIXME: needs doc
 */
static void power_down(uint8_t wdto)
{
#ifdef PROTOCOL_LUFA
    if (USB_DeviceState == DEVICE_STATE_Configured) return;
#endif
    wdt_timeout = wdto;

    // Watchdog Interrupt Mode
    wdt_intr_enable(wdto);

#ifdef BACKLIGHT_ENABLE
	backlight_set(0);
#endif

	// Turn off LED indicators
	led_set(0);

	#ifdef AUDIO_ENABLE
        // This sometimes disables the start-up noise, so it's been disabled
		// stop_all_notes();
	#endif /* AUDIO_ENABLE */
#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
#ifdef RGBLIGHT_ANIMATIONS
  rgblight_timer_disable();
#endif
  rgblight_disable_noeeprom();
#endif
  suspend_power_down_kb();

    // TODO: more power saving
    // See PicoPower application note
    // - I/O port input with pullup
    // - prescale clock
    // - BOD disable
    // - Power Reduction Register PRR
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();

    // Disable watchdog after sleep
    wdt_disable();
}
#endif

/** \brief Suspend power down
 *
 * FIXME: needs doc
 */
void suspend_power_down(void)
{
#ifndef NO_SUSPEND_POWER_DOWN
    power_down(WDTO_15MS);
#endif
}

__attribute__ ((weak)) void matrix_power_up(void) {}
__attribute__ ((weak)) void matrix_power_down(void) {}
bool suspend_wakeup_condition(void)
{
    matrix_power_up();
    matrix_scan();
    matrix_power_down();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        if (matrix_get_row(r)) return true;
    }
     return false;
}

/** \brief run user level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void suspend_wakeup_init_user(void) { }

/** \brief run keyboard level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void suspend_wakeup_init_kb(void) {
  suspend_wakeup_init_user();
}
/** \brief run immediately after wakeup
 *
 * FIXME: needs doc
 */
void suspend_wakeup_init(void)
{
    // clear keyboard state
    clear_keyboard();
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif
	led_set(host_keyboard_leds());
#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
  rgblight_enable_noeeprom();
#ifdef RGBLIGHT_ANIMATIONS
  rgblight_timer_enable();
#endif
#endif
  suspend_wakeup_init_kb();
}

#ifndef NO_SUSPEND_POWER_DOWN
/* watchdog timeout */
ISR(WDT_vect)
{
    // compensate timer for sleep
    switch (wdt_timeout) {
        case WDTO_15MS:
            timer_count += 15 + 2;  // WDTO_15MS + 2(from observation)
            break;
        default:
            ;
    }
}
#endif
