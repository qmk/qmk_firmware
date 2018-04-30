/* TODO */

#include "ch.h"
#include "hal.h"

#include "matrix.h"
#include "action.h"
#include "action_util.h"
#include "mousekey.h"
#include "host.h"
#include "backlight.h"
#include "suspend.h"
#include "wait.h"

/** \brief suspend idle
 *
 * FIXME: needs doc
 */
void suspend_idle(uint8_t time) {
	// TODO: this is not used anywhere - what units is 'time' in?
	wait_ms(time);
}

/** \brief suspend power down
 *
 * FIXME: needs doc
 */
void suspend_power_down(void) {
	// TODO: figure out what to power down and how
	// shouldn't power down TPM/FTM if we want a breathing LED
	// also shouldn't power down USB

	// on AVR, this enables the watchdog for 15ms (max), and goes to
	// SLEEP_MODE_PWR_DOWN

	wait_ms(17);
}

/** \brief suspend wakeup condition
 *
 * FIXME: needs doc
 */
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

/** \brief suspend wakeup condition
 *
 * run immediately after wakeup
 * FIXME: needs doc
 */
void suspend_wakeup_init(void)
{
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
}
