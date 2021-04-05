#include <stdbool.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include "matrix.h"
#include "action.h"
#include "suspend_avr.h"
#include "suspend.h"
#include "timer.h"
#include "led.h"
#include "host.h"

#ifdef PROTOCOL_LUFA
#    include "lufa.h"
#endif

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#ifdef AUDIO_ENABLE
#    include "audio.h"
#endif /* AUDIO_ENABLE */

#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
#    include "rgblight.h"
#endif

/** \brief Suspend idle
 *
 * FIXME: needs doc
 */
void suspend_idle(uint8_t time) {
    cli();
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();
}

// TODO: This needs some cleanup

/** \brief Run keyboard level Power down
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_power_down_user(void) {}
/** \brief Run keyboard level Power down
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_power_down_kb(void) { suspend_power_down_user(); }

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

/** \brief Power down
 *
 * FIXME: needs doc
 */
static void power_down(uint8_t wdto) {
#    ifdef PROTOCOL_LUFA
    if (USB_DeviceState == DEVICE_STATE_Configured) return;
#    endif
    wdt_timeout = wdto;

    // Watchdog Interrupt Mode
    wdt_intr_enable(wdto);

#    ifdef BACKLIGHT_ENABLE
    backlight_set(0);
#    endif

    // Turn off LED indicators
    uint8_t leds_off = 0;
#    if defined(BACKLIGHT_CAPS_LOCK) && defined(BACKLIGHT_ENABLE)
    if (is_backlight_enabled()) {
        // Don't try to turn off Caps Lock indicator as it is backlight and backlight is already off
        leds_off |= (1 << USB_LED_CAPS_LOCK);
    }
#    endif
    led_set(leds_off);

#    ifdef AUDIO_ENABLE
    // This sometimes disables the start-up noise, so it's been disabled
    // stop_all_notes();
#    endif /* AUDIO_ENABLE */
#    if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
    rgblight_suspend();
#    endif
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
void suspend_power_down(void) {
    suspend_power_down_kb();

#ifndef NO_SUSPEND_POWER_DOWN
    power_down(WDTO_15MS);
#endif
}

__attribute__((weak)) void matrix_power_up(void) {}
__attribute__((weak)) void matrix_power_down(void) {}
bool                       suspend_wakeup_condition(void) {
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
__attribute__((weak)) void suspend_wakeup_init_user(void) {}

/** \brief run keyboard level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_wakeup_init_kb(void) { suspend_wakeup_init_user(); }
/** \brief run immediately after wakeup
 *
 * FIXME: needs doc
 */
void suspend_wakeup_init(void) {
    // clear keyboard state
    clear_keyboard();
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif
    led_set(host_keyboard_leds());
#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
    rgblight_wakeup();
#endif
    suspend_wakeup_init_kb();
}

#ifndef NO_SUSPEND_POWER_DOWN
/* watchdog timeout */
ISR(WDT_vect) {
    // compensate timer for sleep
    switch (wdt_timeout) {
        case WDTO_15MS:
            timer_count += 15 + 2;  // WDTO_15MS + 2(from observation)
            break;
        default:;
    }
}
#endif
