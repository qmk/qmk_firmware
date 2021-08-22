/*
 * Copyright 2021 Andrei Purdea <andrei@purdea.ro>
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

#include "usb_power.h"

enum usb_power_state usb_power_state = USB_POWER_STATE_NO_INIT;

__attribute__((weak)) void notify_usb_power_state_change_kb(enum usb_power_state usb_power_state) { notify_usb_power_state_change_user(usb_power_state); }

__attribute__((weak)) void notify_usb_power_state_change_user(enum usb_power_state usb_power_state) {}

static void notify_usb_power_state_change(enum usb_power_state usb_power_state) { notify_usb_power_state_change_kb(usb_power_state); }

void usb_power_set_configuration(bool isConfigured, uint8_t configurationNumber) {
    usb_power_state = isConfigured ? USB_POWER_STATE_CONFIGURED : USB_POWER_STATE_INIT;
    notify_usb_power_state_change(usb_power_state);
}

void usb_power_set_suspend(bool isConfigured, uint8_t configurationNumber) {
    usb_power_state = USB_POWER_STATE_SUSPEND;
    notify_usb_power_state_change(usb_power_state);
}

void usb_power_set_resume(bool isConfigured, uint8_t configurationNumber) {
    usb_power_state = isConfigured ? USB_POWER_STATE_CONFIGURED : USB_POWER_STATE_INIT;
    notify_usb_power_state_change(usb_power_state);
}

void usb_power_set_reset(void) {
    usb_power_state = USB_POWER_STATE_INIT;
    notify_usb_power_state_change(usb_power_state);
}

void usb_power_init(void) {
    usb_power_state = USB_POWER_STATE_INIT;
    notify_usb_power_state_change(usb_power_state);
}
