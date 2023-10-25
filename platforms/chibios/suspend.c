/* TODO */

#include <ch.h>
#include <hal.h>

#include "matrix.h"
#include "action.h"
#include "action_util.h"
#include "mousekey.h"
#include "programmable_button.h"
#include "host.h"
#include "suspend.h"
#include "led.h"
#include "wait.h"

/** \brief suspend power down
 *
 * FIXME: needs doc
 */
void suspend_power_down(void) {
    suspend_power_down_quantum();
    // on AVR, this enables the watchdog for 15ms (max), and goes to
    // SLEEP_MODE_PWR_DOWN

    wait_ms(17);
}

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
#ifdef PROGRAMMABLE_BUTTON_ENABLE
    programmable_button_clear();
#endif /* PROGRAMMABLE_BUTTON_ENABLE */
#ifdef EXTRAKEY_ENABLE
    host_system_send(0);
    host_consumer_send(0);
#endif /* EXTRAKEY_ENABLE */

    suspend_wakeup_init_quantum();
}
