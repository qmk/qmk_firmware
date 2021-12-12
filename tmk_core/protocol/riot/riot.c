/*
 * Copyright (C) 2021 Nils Ollrogge
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @brief
 * @{
 *
 * @brief       Tests for USB HID
 *
 * @author      Nils Ollrogge <nils.ollrogge@fu-berlin.de>
 */

#include <stdio.h>
#include <stdlib.h>

#include "wait.h"
#include "gpio.h"

#include "host.h"
#include "report.h"
#include "host_driver.h"
#include "keyboard.h"
#include "matrix.h"
#include "debug.h"
#include "usb_device_state.h"
#include "usb_driver.h"
#include "usb_descriptor_common.h"

#include "usb/usbus.h"
#include "usb/usbus/hid.h"
#include "usb/usbus/hid_io.h"

#if defined(CONSOLE_ENABLE)
#    define RBUF_SIZE 512
#    include "ring_buffer.h"

void console_task(void);
#endif

#ifndef USB_POLLING_INTERVAL_MS
#    define USB_POLLING_INTERVAL_MS 10
#endif


/*------------------------------------------------------------------*
 * Descriptors
 *------------------------------------------------------------------*/
static const uint8_t report_desc_keyboard[] = {
    0x05, 0x01,  // Usage Page (Generic Desktop)
    0x09, 0x06,  // Usage (Keyboard)
    0xA1, 0x01,  // Collection (Application)
    // Modifiers (8 bits)
    0x05, 0x07,  //   Usage Page (Keyboard/Keypad)
    0x19, 0xE0,  //   Usage Minimum (Keyboard Left Control)
    0x29, 0xE7,  //   Usage Maximum (Keyboard Right GUI)
    0x15, 0x00,  //   Logical Minimum (0)
    0x25, 0x01,  //   Logical Maximum (1)
    0x95, 0x08,  //   Report Count (8)
    0x75, 0x01,  //   Report Size (1)
    0x81, 0x02,  //   Input (Data, Variable, Absolute)
    // Reserved (1 byte)
    0x95, 0x01,  //   Report Count (1)
    0x75, 0x08,  //   Report Size (8)
    0x81, 0x03,  //   Input (Constant)
    // Keycodes (6 bytes)
    0x05, 0x07,        //   Usage Page (Keyboard/Keypad)
    0x19, 0x00,        //   Usage Minimum (0)
    0x29, 0xFF,        //   Usage Maximum (255)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x95, 0x06,        //   Report Count (6)
    0x75, 0x08,        //   Report Size (8)
    0x81, 0x00,        //   Input (Data, Array, Absolute)

    // Status LEDs (5 bits)
    0x05, 0x08,  //   Usage Page (LED)
    0x19, 0x01,  //   Usage Minimum (Num Lock)
    0x29, 0x05,  //   Usage Maximum (Kana)
    0x95, 0x05,  //   Report Count (5)
    0x75, 0x01,  //   Report Size (1)
    0x91, 0x02,  //   Output (Data, Variable, Absolute)
    // LED padding (3 bits)
    0x95, 0x01,  //   Report Count (1)
    0x75, 0x03,  //   Report Size (3)
    0x91, 0x03,  //   Output (Constant)
    0xC0,        // End Collection
};

static const uint8_t shared_hid_report[] = {
#ifdef MOUSE_ENABLE
    // Mouse report descriptor
    0x05, 0x01,             // Usage Page (Generic Desktop)
    0x09, 0x02,             // Usage (Mouse)
    0xA1, 0x01,             // Collection (Application)
    0x85, REPORT_ID_MOUSE,  //   Report ID
    0x09, 0x01,             //   Usage (Pointer)
    0xA1, 0x00,             //   Collection (Physical)
    // Buttons (8 bits)
    0x05, 0x09,  //     Usage Page (Button)
    0x19, 0x01,  //     Usage Minimum (Button 1)
    0x29, 0x08,  //     Usage Maximum (Button 8)
    0x15, 0x00,  //     Logical Minimum (0)
    0x25, 0x01,  //     Logical Maximum (1)
    0x95, 0x08,  //     Report Count (8)
    0x75, 0x01,  //     Report Size (1)
    0x81, 0x02,  //     Input (Data, Variable, Absolute)

    // X/Y position (2 bytes)
    0x05, 0x01,  //     Usage Page (Generic Desktop)
    0x09, 0x30,  //     Usage (X)
    0x09, 0x31,  //     Usage (Y)
    0x15, 0x81,  //     Logical Minimum (-127)
    0x25, 0x7F,  //     Logical Maximum (127)
    0x95, 0x02,  //     Report Count (2)
    0x75, 0x08,  //     Report Size (8)
    0x81, 0x06,  //     Input (Data, Variable, Relative)

    // Vertical wheel (1 byte)
    0x09, 0x38,  //     Usage (Wheel)
    0x15, 0x81,  //     Logical Minimum (-127)
    0x25, 0x7F,  //     Logical Maximum (127)
    0x95, 0x01,  //     Report Count (1)
    0x75, 0x08,  //     Report Size (8)
    0x81, 0x06,  //     Input (Data, Variable, Relative)
    // Horizontal wheel (1 byte)
    0x05, 0x0C,        //     Usage Page (Consumer)
    0x0A, 0x38, 0x02,  //     Usage (AC Pan)
    0x15, 0x81,        //     Logical Minimum (-127)
    0x25, 0x7F,        //     Logical Maximum (127)
    0x95, 0x01,        //     Report Count (1)
    0x75, 0x08,        //     Report Size (8)
    0x81, 0x06,        //     Input (Data, Variable, Relative)
    0xC0,              //   End Collection
    0xC0,              // End Collection
#endif

#ifdef EXTRAKEY_ENABLE
    // Extrakeys report descriptor
    0x05, 0x01,              // Usage Page (Generic Desktop)
    0x09, 0x80,              // Usage (System Control)
    0xA1, 0x01,              // Collection (Application)
    0x85, REPORT_ID_SYSTEM,  //   Report ID
    0x19, 0x01,              //   Usage Minimum (Pointer)
    0x2A, 0xB7, 0x00,        //   Usage Maximum (System Display LCD Autoscale)
    0x15, 0x01,              //   Logical Minimum
    0x26, 0xB7, 0x00,        //   Logical Maximum
    0x95, 0x01,              //   Report Count (1)
    0x75, 0x10,              //   Report Size (16)
    0x81, 0x00,              //   Input (Data, Array, Absolute)
    0xC0,                    // End Collection

    0x05, 0x0C,                // Usage Page (Consumer)
    0x09, 0x01,                // Usage (Consumer Control)
    0xA1, 0x01,                // Collection (Application)
    0x85, REPORT_ID_CONSUMER,  //   Report ID
    0x19, 0x01,                //   Usage Minimum (Consumer Control)
    0x2A, 0xA0, 0x02,          //   Usage Maximum (AC Desktop Show All Applications)
    0x15, 0x01,                //   Logical Minimum
    0x26, 0xA0, 0x02,          //   Logical Maximum
    0x95, 0x01,                //   Report Count (1)
    0x75, 0x10,                //   Report Size (16)
    0x81, 0x00,                //   Input (Data, Array, Absolute)
    0xC0,                      // End Collection
#endif
};

#ifdef CONSOLE_ENABLE
static const uint8_t console_hid_report[] = {
    0x06, 0x31, 0xFF,  // Usage Page (Vendor Defined - PJRC Teensy compatible)
    0x09, 0x74,        // Usage (Vendor Defined - PJRC Teensy compatible)
    0xA1, 0x01,        // Collection (Application)
    // Data to host
    0x09, 0x75,            //   Usage (Vendor Defined)
    0x15, 0x00,            //   Logical Minimum (0x00)
    0x26, 0xFF, 0x00,      //   Logical Maximum (0x00FF)
    0x95, CONSOLE_EPSIZE,  //   Report Count
    0x75, 0x08,            //   Report Size (8)
    0x81, 0x02,            //   Input (Data, Variable, Absolute)
    // Data from host
    0x09, 0x76,            //   Usage (Vendor Defined)
    0x15, 0x00,            //   Logical Minimum (0x00)
    0x26, 0xFF, 0x00,      //   Logical Maximum (0x00FF)
    0x95, CONSOLE_EPSIZE,  //   Report Count
    0x75, 0x08,            //   Report Size (8)
    0x91, 0x02,            //   Output (Data)
    0xC0                   // End Collection
};
#endif

#ifdef RAW_ENABLE
static const uint8_t raw_hid_report[] = {
    0x06, RAW_USAGE_PAGE_LO, RAW_USAGE_PAGE_HI,  // Usage Page (Vendor Defined)
    0x09, RAW_USAGE_ID,                          // Usage (Vendor Defined)
    0xA1, 0x01,                                  // Collection (Application)
    // Data to host
    0x09, 0x62,             //   Usage (Vendor Defined)
    0x15, 0x00,             //   Logical Minimum (0)
    0x26, 0xFF, 0x00,       //   Logical Maximum (255)
    0x95, RAW_EPSIZE,       //   Report Count
    0x75, 0x08,             //   Report Size (8)
    0x81, 0x02,             //   Input (Data, Variable, Absolute)
    // Data from host
    0x09, 0x63,             //   Usage (Vendor Defined)
    0x15, 0x00,             //   Logical Minimum (0)
    0x26, 0xFF, 0x00,       //   Logical Maximum (255)
    0x95, RAW_EPSIZE,       //   Report Count
    0x75, 0x08,             //   Report Size (8)
    0x91, 0x02,             //   Output (Data, Variable, Absolute)
    0xC0                    // End Collection
};
#endif

/*------------------------------------------------------------------*
 * Host driver
 *------------------------------------------------------------------*/
static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);

static host_driver_t driver = {keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer};

static uint8_t keyboard_leds(void) { return usbdrv_keyboard_leds(); }

static void send_keyboard(report_keyboard_t *report) {
    if (g_usbus.state != USBUS_STATE_CONFIGURED) {
        return;
    }
    usbdrv_write(KEYBOARD_INTERFACE, report, sizeof(report_keyboard_t));
}

static void send_mouse(report_mouse_t *report) {
#ifdef MOUSE_ENABLE
    uprintf("send_mouse\n");
    if (g_usbus.state != USBUS_STATE_CONFIGURED) {
        return;
    }
    usbdrv_write(SHARED_INTERFACE, report, sizeof(report_mouse_t));
#endif
}

#ifdef EXTRAKEY_ENABLE
static void send_extra(uint8_t report_id, uint16_t data) {
    static uint8_t  last_id   = 0;
    static uint16_t last_data = 0;
    if ((report_id == last_id) && (data == last_data)) return;
    last_id   = report_id;
    last_data = data;

    static report_extra_t report;
    report = (report_extra_t){.report_id = report_id, .usage = data};

    if (g_usbus.state != USBUS_STATE_CONFIGURED) {
        return;
    }
    usbdrv_write(SHARED_INTERFACE, &report, sizeof(report_extra_t));
}
#endif

static void send_system(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    send_extra(REPORT_ID_SYSTEM, data);
#endif
}

static void send_consumer(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    send_extra(REPORT_ID_CONSUMER, data);
#endif
}

/*------------------------------------------------------------------*
 * RAW HID
 *------------------------------------------------------------------*/
#ifdef RAW_ENABLE

static uint8_t raw_output_buffer[RAW_EPSIZE];
static uint8_t raw_output_received_bytes = 0;

void raw_hid_send(uint8_t *data, uint8_t length) {
    if (length != RAW_EPSIZE) {
        return;
    }
    // TODO: send data...
}

__attribute__((weak)) void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Users should #include "raw_hid.h" in their own code
    // and implement this function there. Leave this as weak linkage
    // so users can opt to not handle data coming in.
}

void raw_hid_task(void) {
    if (raw_output_received_bytes == RAW_EPSIZE) {
        raw_hid_receive(raw_output_buffer, RAW_EPSIZE);
        raw_output_received_bytes = 0;
    }
}
#endif

/*------------------------------------------------------------------*
 * Console
 *------------------------------------------------------------------*/
#ifdef CONSOLE_ENABLE

int8_t sendchar(uint8_t c) {
    rbuf_enqueue(c);
    return 0;
}

void console_task(void) {
    if (!rbuf_has_data()) {
        return;
    }

    char    send_buf[CONSOLE_EPSIZE] = {0};
    uint8_t send_buf_count           = 0;
    while (rbuf_has_data() && send_buf_count < CONSOLE_EPSIZE) {
        send_buf[send_buf_count++] = rbuf_dequeue();
    }

    usbdrv_write(CONSOLE_INTERFACE, send_buf, sizeof(send_buf));
    usbdrv_write(CONSOLE_INTERFACE, 0, 0);
}
#endif

/*------------------------------------------------------------------*
 * Protocol bindings
 *------------------------------------------------------------------*/
void protocol_setup(void) { usb_device_state_init(); }

void protocol_pre_init(void) {
    // clang-format off
    comp_hid_device_conf_t config[TOTAL_INTERFACES] = {
        {
            .id               = KEYBOARD_INTERFACE,
            .report_desc      = report_desc_keyboard,
            .report_desc_size = sizeof(report_desc_keyboard),
            .ep_size          = 8,
            .interval         = USB_POLLING_INTERVAL_MS
        },
#ifdef RAW_ENABLE
        {
            .id               = RAW_INTERFACE,
            .report_desc      = raw_hid_report,
            .report_desc_size = sizeof(raw_hid_report),
            .ep_size          = RAW_EPSIZE,
            .interval         = 1
        },
#endif
        {
            .id               = SHARED_INTERFACE,
            .report_desc      = shared_hid_report,
            .report_desc_size = sizeof(shared_hid_report),
            .ep_size          = 8,
            .interval         = USB_POLLING_INTERVAL_MS
        },
#ifdef CONSOLE_ENABLE
        {
            .id               = CONSOLE_INTERFACE,
            .report_desc      = console_hid_report,
            .report_desc_size = sizeof(console_hid_report),
            .ep_size          = CONSOLE_EPSIZE,
            .interval         = 1
        },
#endif
    };
    // clang-format on
    usbdrv_init(config, TOTAL_INTERFACES);
}

void protocol_post_init(void) {
    host_set_driver(&driver);
    wait_ms(50);
}

void protocol_pre_task(void) {
    // TODO: better suspend stuffs
    if (g_usbus.state == USBUS_STATE_SUSPEND) {
        while (g_usbus.state == USBUS_STATE_SUSPEND) {
            wait_ms(15);
        }
    }
}

void protocol_post_task(void) {
#ifdef RAW_ENABLE
    raw_hid_task();
#endif
#ifdef CONSOLE_ENABLE
    console_task();
#endif
}
