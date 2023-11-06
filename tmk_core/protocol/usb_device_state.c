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

#include "usb_device_state.h"
#if defined(HAPTIC_ENABLE)
#    include "haptic.h"
#endif

enum usb_device_state usb_device_state = USB_DEVICE_STATE_NO_INIT;

__attribute__((weak)) void notify_usb_device_state_change_kb(enum usb_device_state usb_device_state) {
    notify_usb_device_state_change_user(usb_device_state);
}

__attribute__((weak)) void notify_usb_device_state_change_user(enum usb_device_state usb_device_state) {}

static void notify_usb_device_state_change(enum usb_device_state usb_device_state) {
#if defined(HAPTIC_ENABLE) && HAPTIC_OFF_IN_LOW_POWER
    haptic_notify_usb_device_state_change();
#endif
    notify_usb_device_state_change_kb(usb_device_state);
}

void usb_device_state_set_configuration(bool isConfigured, uint8_t configurationNumber) {
    usb_device_state = isConfigured ? USB_DEVICE_STATE_CONFIGURED : USB_DEVICE_STATE_INIT;
    notify_usb_device_state_change(usb_device_state);
}

void usb_device_state_set_suspend(bool isConfigured, uint8_t configurationNumber) {
    usb_device_state = USB_DEVICE_STATE_SUSPEND;
    notify_usb_device_state_change(usb_device_state);
}

void usb_device_state_set_resume(bool isConfigured, uint8_t configurationNumber) {
    usb_device_state = isConfigured ? USB_DEVICE_STATE_CONFIGURED : USB_DEVICE_STATE_INIT;
    notify_usb_device_state_change(usb_device_state);
}

void usb_device_state_set_reset(void) {
    usb_device_state = USB_DEVICE_STATE_INIT;
    notify_usb_device_state_change(usb_device_state);
}

void usb_device_state_init(void) {
    usb_device_state = USB_DEVICE_STATE_INIT;
    notify_usb_device_state_change(usb_device_state);
}
