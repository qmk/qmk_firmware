// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Raw HID is now handled cleanly via the host_driver_t interface.
// The wireless_driver includes send_raw_hid which routes to md_send_raw()
// when in wireless mode. No macro hacks needed.
