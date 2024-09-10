// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

typedef enum {
    TRANSPORT_NONE,
    TRANSPORT_USB,
    TRANSPORT_WLS,
} transport_t;

void wls_transport_enable(bool enable);
void usb_transport_enable(bool enable);
void set_transport(transport_t new_transport);
transport_t get_transport(void);
void usb_power_connect(void);
void usb_power_disconnect(void);
void usb_remote_wakeup(void);
