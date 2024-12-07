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

#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
#endif

static struct usb_device_state usb_device_state = {.idle_rate = 0, .leds = 0, .protocol = USB_PROTOCOL_REPORT, .configure_state = USB_DEVICE_STATE_NO_INIT};

__attribute__((weak)) void notify_usb_device_state_change_kb(struct usb_device_state usb_device_state) {
    notify_usb_device_state_change_user(usb_device_state);
}

__attribute__((weak)) void notify_usb_device_state_change_user(struct usb_device_state usb_device_state) {}

static void notify_usb_device_state_change(struct usb_device_state usb_device_state) {
#if defined(HAPTIC_ENABLE) && HAPTIC_OFF_IN_LOW_POWER
    haptic_notify_usb_device_state_change();
#endif

    notify_usb_device_state_change_kb(usb_device_state);

#ifdef OS_DETECTION_ENABLE
    os_detection_notify_usb_device_state_change(usb_device_state);
#endif
}

void usb_device_state_set_configuration(bool is_configured, uint8_t configuration_number) {
    usb_device_state.configure_state = is_configured ? USB_DEVICE_STATE_CONFIGURED : USB_DEVICE_STATE_INIT;
    notify_usb_device_state_change(usb_device_state);
}

void usb_device_state_set_suspend(bool is_configured, uint8_t configuration_number) {
    usb_device_state.configure_state = USB_DEVICE_STATE_SUSPEND;
    notify_usb_device_state_change(usb_device_state);
}

void usb_device_state_set_resume(bool is_configured, uint8_t configuration_number) {
    usb_device_state.configure_state = is_configured ? USB_DEVICE_STATE_CONFIGURED : USB_DEVICE_STATE_INIT;
    notify_usb_device_state_change(usb_device_state);
}

void usb_device_state_set_reset(void) {
    usb_device_state.configure_state = USB_DEVICE_STATE_INIT;
    notify_usb_device_state_change(usb_device_state);
}

void usb_device_state_init(void) {
    usb_device_state.configure_state = USB_DEVICE_STATE_INIT;
    notify_usb_device_state_change(usb_device_state);
}

inline usb_configure_state_t usb_device_state_get_configure_state(void) {
    return usb_device_state.configure_state;
}

void usb_device_state_set_protocol(usb_hid_protocol_t protocol) {
    usb_device_state.protocol = protocol == USB_PROTOCOL_BOOT ? USB_PROTOCOL_BOOT : USB_PROTOCOL_REPORT;
    notify_usb_device_state_change(usb_device_state);
}

inline usb_hid_protocol_t usb_device_state_get_protocol() {
    return usb_device_state.protocol;
}

void usb_device_state_set_leds(uint8_t leds) {
    usb_device_state.leds = leds;
    notify_usb_device_state_change(usb_device_state);
}

inline uint8_t usb_device_state_get_leds(void) {
    return usb_device_state.leds;
}

void usb_device_state_set_idle_rate(uint8_t idle_rate) {
    usb_device_state.idle_rate = idle_rate;
    notify_usb_device_state_change(usb_device_state);
}

inline uint8_t usb_device_state_get_idle_rate(void) {
    return usb_device_state.idle_rate;
}
