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

#pragma once

#include <stdbool.h>
#include <stdint.h>

void usb_device_state_set_configuration(bool isConfigured, uint8_t configurationNumber);
void usb_device_state_set_suspend(bool isConfigured, uint8_t configurationNumber);
void usb_device_state_set_resume(bool isConfigured, uint8_t configurationNumber);
void usb_device_state_set_reset(void);
void usb_device_state_init(void);

enum usb_device_state {
    USB_DEVICE_STATE_NO_INIT    = 0, // We're in this state before calling usb_device_state_init()
    USB_DEVICE_STATE_INIT       = 1, // Can consume up to 100mA
    USB_DEVICE_STATE_CONFIGURED = 2, // Can consume up to what is specified in configuration descriptor, typically 500mA
    USB_DEVICE_STATE_SUSPEND    = 3  // Can consume only suspend current
};

extern enum usb_device_state usb_device_state;

void notify_usb_device_state_change_kb(enum usb_device_state usb_device_state);
void notify_usb_device_state_change_user(enum usb_device_state usb_device_state);
