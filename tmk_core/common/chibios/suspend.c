/* TODO */

#include <ch.h>
#include <hal.h>

#include "matrix.h"
#include "action.h"
#include "action_util.h"
#include "mousekey.h"
#include "host.h"
#include "suspend.h"
#include "led.h"
#include "wait.h"

#ifdef AUDIO_ENABLE
#    include "audio.h"
#endif /* AUDIO_ENABLE */

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
#    include "rgblight.h"
#endif

/** \brief suspend idle
 *
 * FIXME: needs doc
 */
void suspend_idle(uint8_t time) {
    // TODO: this is not used anywhere - what units is 'time' in?
    wait_ms(time);
}

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

/** \brief suspend power down
 *
 * FIXME: needs doc
 */
void suspend_power_down(void) {
#ifdef BACKLIGHT_ENABLE
    backlight_set(0);
#endif

    // Turn off LED indicators
    uint8_t leds_off = 0;
#if defined(BACKLIGHT_CAPS_LOCK) && defined(BACKLIGHT_ENABLE)
    if (is_backlight_enabled()) {
        // Don't try to turn off Caps Lock indicator as it is backlight and backlight is already off
        leds_off |= (1 << USB_LED_CAPS_LOCK);
    }
#endif
    led_set(leds_off);

    // TODO: figure out what to power down and how
    // shouldn't power down TPM/FTM if we want a breathing LED
    // also shouldn't power down USB
#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
    rgblight_suspend();
#endif
#ifdef AUDIO_ENABLE
    stop_all_notes();
#endif /* AUDIO_ENABLE */

    suspend_power_down_kb();
    // on AVR, this enables the watchdog for 15ms (max), and goes to
    // SLEEP_MODE_PWR_DOWN

    wait_ms(17);
}

/** \brief suspend wakeup condition
 *
 * FIXME: needs doc
 */
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

/** \brief suspend wakeup condition
 *
 * run immediately after wakeup
 * FIXME: needs doc
 */
void suspend_wakeup_init(void) {
    // clear keyboard state
    // need to do it manually, because we're running from ISR
    //  and clear_keyboard() calls print
    // so only clear the variables in memory
    // the reports will be sent from main.c afterwards
    // or if the PC asks for GET_REPORT
    clear_mods();
    clear_weak_mods();
    clear_keys();
#ifdef MOUSEKEY_ENABLE
    mousekey_clear();
#endif /* MOUSEKEY_ENABLE */
#ifdef EXTRAKEY_ENABLE
    host_system_send(0);
    host_consumer_send(0);
#endif /* EXTRAKEY_ENABLE */
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif /* BACKLIGHT_ENABLE */
    led_set(host_keyboard_leds());
#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
    rgblight_wakeup();
#endif
    suspend_wakeup_init_kb();
}
