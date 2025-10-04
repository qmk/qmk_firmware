// Copyright 2023 Stefan Kerkmann (@KarlK90)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <ch.h>
#include <hal.h>
#include <stdint.h>

#include "timer.h"

typedef struct {
    time_msecs_t idle_rate;
    systime_t    last_report;
    uint8_t      data[64];
    size_t       length;
} usb_fs_report_t;

typedef struct {
    usb_fs_report_t **reports;
    const void (*get_report)(usb_fs_report_t **, uint8_t, usb_fs_report_t *);
    const void (*set_report)(usb_fs_report_t **, const uint8_t *, size_t);
    const void (*reset_report)(usb_fs_report_t **);
    const void (*set_idle)(usb_fs_report_t **, uint8_t, uint8_t);
    const uint8_t (*get_idle)(usb_fs_report_t **, uint8_t);
    const bool (*idle_timer_elasped)(usb_fs_report_t **, uint8_t);
} usb_report_storage_t;

#define QMK_USB_REPORT_STROAGE_ENTRY(_report_id, _report_size) [_report_id] = &((usb_fs_report_t){.data = {[0] = _report_id}, .length = _report_size})

#define QMK_USB_REPORT_STORAGE(_get_report, _set_report, _reset_report, _get_idle, _set_idle, _idle_timer_elasped, _report_count, _reports...) \
    &((usb_report_storage_t){                                                                                                                  \
        .reports            = (_Alignas(4) usb_fs_report_t *[_report_count]){_reports},                                                        \
        .get_report         = _get_report,                                                                                                     \
        .set_report         = _set_report,                                                                                                     \
        .reset_report       = _reset_report,                                                                                                   \
        .get_idle           = _get_idle,                                                                                                       \
        .set_idle           = _set_idle,                                                                                                       \
        .idle_timer_elasped = _idle_timer_elasped,                                                                                             \
    })

#define QMK_USB_REPORT_STORAGE_DEFAULT(_report_length)                        \
    QMK_USB_REPORT_STORAGE(&usb_get_report,         /* _get_report */         \
                           &usb_set_report,         /* _set_report */         \
                           &usb_reset_report,       /* _reset_report */       \
                           &usb_get_idle_rate,      /* _get_idle */           \
                           &usb_set_idle_rate,      /* _set_idle */           \
                           &usb_idle_timer_elapsed, /* _idle_timer_elasped */ \
                           1,                       /* _report_count */       \
                           QMK_USB_REPORT_STROAGE_ENTRY(0, _report_length))

// USB HID SET_REPORT and GET_REPORT  handling functions
void usb_set_report(usb_fs_report_t **reports, const uint8_t *data, size_t length);
void usb_shared_set_report(usb_fs_report_t **reports, const uint8_t *data, size_t length);

void usb_get_report(usb_fs_report_t **reports, uint8_t report_id, usb_fs_report_t *report);
void usb_shared_get_report(usb_fs_report_t **reports, uint8_t report_id, usb_fs_report_t *report);

void usb_reset_report(usb_fs_report_t **reports);
void usb_shared_reset_report(usb_fs_report_t **reports);

bool usb_get_report_cb(USBDriver *driver);

// USB HID SET_IDLE and GET_IDLE handling functions
void usb_idle_task(void);

void usb_set_idle_rate(usb_fs_report_t **timers, uint8_t report_id, uint8_t idle_rate);
void usb_shared_set_idle_rate(usb_fs_report_t **timers, uint8_t report_id, uint8_t idle_rate);

uint8_t usb_get_idle_rate(usb_fs_report_t **timers, uint8_t report_id);
uint8_t usb_shared_get_idle_rate(usb_fs_report_t **timers, uint8_t report_id);

bool usb_idle_timer_elapsed(usb_fs_report_t **timers, uint8_t report_id);
bool usb_shared_idle_timer_elapsed(usb_fs_report_t **timers, uint8_t report_id);

bool usb_get_idle_cb(USBDriver *driver);
bool usb_set_idle_cb(USBDriver *driver);
