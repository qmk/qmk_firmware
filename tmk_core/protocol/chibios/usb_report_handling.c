// Copyright 2023 Stefan Kerkmann (@KarlK90)
// SPDX-License-Identifier: GPL-3.0-or-later

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "usb_report_handling.h"
#include "usb_endpoints.h"
#include "usb_main.h"
#include "usb_types.h"
#include "usb_driver.h"
#include "report.h"

extern usb_endpoint_in_t     usb_endpoints_in[USB_ENDPOINT_IN_COUNT];
extern usb_endpoint_in_lut_t usb_endpoint_interface_lut[TOTAL_INTERFACES];

void usb_set_report(usb_fs_report_t **reports, const uint8_t *data, size_t length) {
    if (*reports == NULL) {
        return;
    }

    (*reports)->last_report = chVTGetSystemTimeX();
    (*reports)->length      = length;
    memcpy(&(*reports)->data, data, length);
}

void usb_get_report(usb_fs_report_t **reports, uint8_t report_id, usb_fs_report_t *report) {
    (void)report_id;
    if (*reports == NULL) {
        return;
    }

    report->length = (*reports)->length;
    memcpy(&report->data, &(*reports)->data, report->length);
}

void usb_reset_report(usb_fs_report_t **reports) {
    if (*reports == NULL) {
        return;
    }

    memset(&(*reports)->data, 0, (*reports)->length);
    (*reports)->idle_rate   = 0;
    (*reports)->last_report = 0;
}

void usb_shared_set_report(usb_fs_report_t **reports, const uint8_t *data, size_t length) {
    uint8_t report_id = data[0];

    if (report_id > REPORT_ID_COUNT || reports[report_id] == NULL) {
        return;
    }

    reports[report_id]->last_report = chVTGetSystemTimeX();
    reports[report_id]->length      = length;
    memcpy(&reports[report_id]->data, data, length);
}

void usb_shared_get_report(usb_fs_report_t **reports, uint8_t report_id, usb_fs_report_t *report) {
    if (report_id > REPORT_ID_COUNT || reports[report_id] == NULL) {
        return;
    }

    report->length = reports[report_id]->length;
    memcpy(&report->data, &reports[report_id]->data, report->length);
}

void usb_shared_reset_report(usb_fs_report_t **reports) {
    for (int i = 0; i <= REPORT_ID_COUNT; i++) {
        if (reports[i] == NULL) {
            continue;
        }
        memset(&reports[i]->data, 0, reports[i]->length);
        reports[i]->idle_rate   = 0;
        reports[i]->last_report = 0;
    }
}

bool usb_get_report_cb(USBDriver *driver) {
    usb_control_request_t *setup     = (usb_control_request_t *)driver->setup;
    uint8_t                interface = setup->wIndex;
    uint8_t                report_id = setup->wValue.lbyte;

    static usb_fs_report_t report;

    if (!IS_VALID_INTERFACE(interface) || !IS_VALID_REPORT_ID(report_id)) {
        return false;
    }

    usb_endpoint_in_lut_t ep = usb_endpoint_interface_lut[interface];

    if (!IS_VALID_USB_ENDPOINT_IN_LUT(ep)) {
        return false;
    }

    usb_report_storage_t *report_storage = usb_endpoints_in[ep].report_storage;

    if (report_storage == NULL) {
        return false;
    }

    report_storage->get_report(report_storage->reports, report_id, &report);

    usbSetupTransfer(driver, (uint8_t *)report.data, report.length, NULL);

    return true;
}

static bool run_idle_task = false;

void usb_set_idle_rate(usb_fs_report_t **reports, uint8_t report_id, uint8_t idle_rate) {
    (void)report_id;

    if (*reports == NULL) {
        return;
    }

    (*reports)->idle_rate = idle_rate * 4;

    run_idle_task |= idle_rate != 0;
}

uint8_t usb_get_idle_rate(usb_fs_report_t **reports, uint8_t report_id) {
    (void)report_id;

    if (*reports == NULL) {
        return 0;
    }

    return (*reports)->idle_rate / 4;
}

bool usb_idle_timer_elapsed(usb_fs_report_t **reports, uint8_t report_id) {
    (void)report_id;

    if (*reports == NULL) {
        return false;
    }

    osalSysLock();
    time_msecs_t idle_rate   = (*reports)->idle_rate;
    systime_t    last_report = (*reports)->last_report;
    osalSysUnlock();

    if (idle_rate == 0) {
        return false;
    }

    return chTimeI2MS(chVTTimeElapsedSinceX(last_report)) >= idle_rate;
}

void usb_shared_set_idle_rate(usb_fs_report_t **reports, uint8_t report_id, uint8_t idle_rate) {
    // USB spec demands that a report_id of 0 would set the idle rate for all
    // reports of that endpoint, but this can easily lead to resource
    // exhaustion, therefore we deliberalty break the spec at this point.
    if (report_id == 0 || report_id > REPORT_ID_COUNT || reports[report_id] == NULL) {
        return;
    }

    reports[report_id]->idle_rate = idle_rate * 4;

    run_idle_task |= idle_rate != 0;
}

uint8_t usb_shared_get_idle_rate(usb_fs_report_t **reports, uint8_t report_id) {
    if (report_id > REPORT_ID_COUNT || reports[report_id] == NULL) {
        return 0;
    }

    return reports[report_id]->idle_rate / 4;
}

bool usb_shared_idle_timer_elapsed(usb_fs_report_t **reports, uint8_t report_id) {
    if (report_id > REPORT_ID_COUNT || reports[report_id] == NULL) {
        return false;
    }

    osalSysLock();
    time_msecs_t idle_rate   = reports[report_id]->idle_rate;
    systime_t    last_report = reports[report_id]->last_report;
    osalSysUnlock();

    if (idle_rate == 0) {
        return false;
    }

    return chTimeI2MS(chVTTimeElapsedSinceX(last_report)) >= idle_rate;
}

void usb_idle_task(void) {
    if (!run_idle_task) {
        return;
    }

    static usb_fs_report_t report;
    bool                   non_zero_idle_rate_found = false;

    for (int ep = 0; ep < USB_ENDPOINT_IN_COUNT; ep++) {
        usb_report_storage_t *report_storage = usb_endpoints_in[ep].report_storage;

        if (report_storage == NULL) {
            continue;
        }

#if defined(SHARED_EP_ENABLE)
        if (ep == USB_ENDPOINT_IN_SHARED) {
            for (int report_id = 1; report_id <= REPORT_ID_COUNT; report_id++) {
                osalSysLock();
                non_zero_idle_rate_found |= report_storage->get_idle(report_storage->reports, report_id) != 0;
                osalSysUnlock();

                if (usb_endpoint_in_is_inactive(&usb_endpoints_in[ep]) && report_storage->idle_timer_elasped(report_storage->reports, report_id)) {
                    osalSysLock();
                    report_storage->get_report(report_storage->reports, report_id, &report);
                    osalSysUnlock();
                    send_report(ep, &report.data, report.length);
                }
            }
            continue;
        }
#endif

        osalSysLock();
        non_zero_idle_rate_found |= report_storage->get_idle(report_storage->reports, 0) != 0;
        osalSysUnlock();

        if (usb_endpoint_in_is_inactive(&usb_endpoints_in[ep]) && report_storage->idle_timer_elasped(report_storage->reports, 0)) {
            osalSysLock();
            report_storage->get_report(report_storage->reports, 0, &report);
            osalSysUnlock();
            send_report(ep, &report.data, report.length);
        }
    }

    run_idle_task = non_zero_idle_rate_found;
}

bool usb_get_idle_cb(USBDriver *driver) {
    usb_control_request_t *setup     = (usb_control_request_t *)driver->setup;
    uint8_t                interface = setup->wIndex;
    uint8_t                report_id = setup->wValue.lbyte;

    static uint8_t _Alignas(4) idle_rate;

    if (!IS_VALID_INTERFACE(interface) || !IS_VALID_REPORT_ID(report_id)) {
        return false;
    }

    usb_endpoint_in_lut_t ep = usb_endpoint_interface_lut[interface];

    if (!IS_VALID_USB_ENDPOINT_IN_LUT(ep)) {
        return false;
    }

    usb_report_storage_t *report_storage = usb_endpoints_in[ep].report_storage;

    if (report_storage == NULL) {
        return false;
    }

    idle_rate = report_storage->get_idle(report_storage->reports, report_id);

    usbSetupTransfer(driver, &idle_rate, 1, NULL);

    return true;
}

bool usb_set_idle_cb(USBDriver *driver) {
    usb_control_request_t *setup     = (usb_control_request_t *)driver->setup;
    uint8_t                interface = setup->wIndex;
    uint8_t                report_id = setup->wValue.lbyte;
    uint8_t                idle_rate = setup->wValue.hbyte;

    if (!IS_VALID_INTERFACE(interface) || !IS_VALID_REPORT_ID(report_id)) {
        return false;
    }

    usb_endpoint_in_lut_t ep = usb_endpoint_interface_lut[interface];

    if (!IS_VALID_USB_ENDPOINT_IN_LUT(ep)) {
        return false;
    }

    usb_report_storage_t *report_storage = usb_endpoints_in[ep].report_storage;

    if (report_storage == NULL) {
        return false;
    }

    report_storage->set_idle(report_storage->reports, report_id, idle_rate);

    usbSetupTransfer(driver, NULL, 0, NULL);

    return true;
}
