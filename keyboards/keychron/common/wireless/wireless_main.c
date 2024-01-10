/* Copyright 2023 @ lokher (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "wireless.h"
#include "transport.h"
#include "factory_test.h"
#include "keychron_task.h"

__attribute__((weak)) void wireless_pre_task(void) {}
__attribute__((weak)) void wireless_post_task(void) {}

bool wireless_tasks(void) {
    wireless_pre_task();
    wireless_task();
    wireless_post_task();

    /* usb_remote_wakeup() should be invoked last so that we have chance
     * to switch to wireless after start-up when usb is not connected
     */
    if (get_transport() == TRANSPORT_USB) usb_remote_wakeup();
    return true;
}

#ifdef KEYCHRON_CALLBACK_ENABLE
void register_wt_tasks(void) {
    register_keychron_task(wireless_tasks, true);
}
#endif
