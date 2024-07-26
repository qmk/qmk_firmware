// Copyright 2025 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#if defined(POINTING_DEVICE_DRIVER_digitizer)
#    include "pointing_device.h"

const pointing_device_driver_t digitizer_pointing_device_driver;
extern bool digitizer_send_mouse_reports;

__attribute__((weak)) void digitizer_update_mouse_report(report_digitizer_t *report);
__attribute__((weak)) bool digitizer_update_gesture_state(void);
#endif
