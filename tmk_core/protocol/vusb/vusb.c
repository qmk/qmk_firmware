/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>

#include <avr/wdt.h>

#include <usbdrv/usbdrv.h>

#include "usbconfig.h"
#include "host.h"
#include "report.h"
#include "host_driver.h"
#include "vusb.h"
#include "print.h"
#include "debug.h"
#include "wait.h"
#include "usb_descriptor_common.h"

#ifdef RAW_ENABLE
#    include "raw_hid.h"
#endif

#if defined(CONSOLE_ENABLE)
#    define RBUF_SIZE 128
#    include "ring_buffer.h"
#endif

#define NEXT_INTERFACE __COUNTER__

/*
 * Interface indexes
 */
enum usb_interfaces {
#ifndef KEYBOARD_SHARED_EP
    KEYBOARD_INTERFACE = NEXT_INTERFACE,
#else
    SHARED_INTERFACE = NEXT_INTERFACE,
#    define KEYBOARD_INTERFACE SHARED_INTERFACE
#endif

// It is important that the Raw HID interface is at a constant
// interface number, to support Linux/OSX platforms and chrome.hid
// If Raw HID is enabled, let it be always 1.
#ifdef RAW_ENABLE
    RAW_INTERFACE = NEXT_INTERFACE,
#endif

#if defined(SHARED_EP_ENABLE) && !defined(KEYBOARD_SHARED_EP)
    SHARED_INTERFACE = NEXT_INTERFACE,
#endif

#ifdef CONSOLE_ENABLE
    CONSOLE_INTERFACE = NEXT_INTERFACE,
#endif

    TOTAL_INTERFACES = NEXT_INTERFACE
};

#define MAX_INTERFACES 3

#if (NEXT_INTERFACE - 1) > MAX_INTERFACES
#    error There are not enough available interfaces to support all functions. Please disable one or more of the following: Mouse Keys, Extra Keys, Raw HID, Console
#endif

#if (defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)) && CONSOLE_ENABLE
#    error Mouse/Extra Keys share an endpoint with Console. Please disable one of the two.
#endif

static uint8_t keyboard_led_state = 0;
static uint8_t vusb_idle_rate     = 0;

/* Keyboard report send buffer */
#define KBUF_SIZE 16
static report_keyboard_t kbuf[KBUF_SIZE];
static uint8_t           kbuf_head = 0;
static uint8_t           kbuf_tail = 0;

static report_keyboard_t keyboard_report_sent;

#define VUSB_TRANSFER_KEYBOARD_MAX_TRIES 10

/* transfer keyboard report from buffer */
void vusb_transfer_keyboard(void) {
    for (int i = 0; i < VUSB_TRANSFER_KEYBOARD_MAX_TRIES; i++) {
        if (usbInterruptIsReady()) {
            if (kbuf_head != kbuf_tail) {
#ifndef KEYBOARD_SHARED_EP
                usbSetInterrupt((void *)&kbuf[kbuf_tail], sizeof(report_keyboard_t));
#else
                // Ugly hack! :(
                usbSetInterrupt((void *)&kbuf[kbuf_tail], sizeof(report_keyboard_t) - 1);
                while (!usbInterruptIsReady()) {
                    usbPoll();
                }
                usbSetInterrupt((void *)(&(kbuf[kbuf_tail].keys[5])), 1);
#endif
                kbuf_tail = (kbuf_tail + 1) % KBUF_SIZE;
                if (debug_keyboard) {
                    dprintf("V-USB: kbuf[%d->%d](%02X)\n", kbuf_tail, kbuf_head, (kbuf_head < kbuf_tail) ? (KBUF_SIZE - kbuf_tail + kbuf_head) : (kbuf_head - kbuf_tail));
                }
            }
            break;
        }
        usbPoll();
        wait_ms(1);
    }
}

/*------------------------------------------------------------------*
 * RAW HID
 *------------------------------------------------------------------*/
#ifdef RAW_ENABLE
#    define RAW_BUFFER_SIZE 32
#    define RAW_EPSIZE 8

static uint8_t raw_output_buffer[RAW_BUFFER_SIZE];
static uint8_t raw_output_received_bytes = 0;

void raw_hid_send(uint8_t *data, uint8_t length) {
    if (length != RAW_BUFFER_SIZE) {
        return;
    }

    uint8_t *temp = data;
    for (uint8_t i = 0; i < 4; i++) {
        while (!usbInterruptIsReady4()) {
            usbPoll();
        }
        usbSetInterrupt4(temp, 8);
        temp += 8;
    }
    while (!usbInterruptIsReady4()) {
        usbPoll();
    }
    usbSetInterrupt4(0, 0);
}

__attribute__((weak)) void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Users should #include "raw_hid.h" in their own code
    // and implement this function there. Leave this as weak linkage
    // so users can opt to not handle data coming in.
}

void raw_hid_task(void) {
    if (raw_output_received_bytes == RAW_BUFFER_SIZE) {
        raw_hid_receive(raw_output_buffer, RAW_BUFFER_SIZE);
        raw_output_received_bytes = 0;
    }
}
#endif

/*------------------------------------------------------------------*
 * Console
 *------------------------------------------------------------------*/
#ifdef CONSOLE_ENABLE
#    define CONSOLE_BUFFER_SIZE 32
#    define CONSOLE_EPSIZE 8

int8_t sendchar(uint8_t c) {
    rbuf_enqueue(c);
    return 0;
}

static inline bool usbSendData3(char *data, uint8_t len) {
    uint8_t retries = 5;
    while (!usbInterruptIsReady3()) {
        if (!(retries--)) {
            return false;
        }
        usbPoll();
    }

    usbSetInterrupt3((unsigned char *)data, len);
    return true;
}

void console_task(void) {
    if (!usbConfiguration) {
        return;
    }

    if (!rbuf_has_data()) {
        return;
    }

    // Send in chunks of 8 padded to 32
    char    send_buf[CONSOLE_BUFFER_SIZE] = {0};
    uint8_t send_buf_count                = 0;
    while (rbuf_has_data() && send_buf_count < CONSOLE_EPSIZE) {
        send_buf[send_buf_count++] = rbuf_dequeue();
    }

    char *temp = send_buf;
    for (uint8_t i = 0; i < 4; i++) {
        if (!usbSendData3(temp, 8)) {
            break;
        }
        temp += 8;
    }

    usbSendData3(0, 0);
    usbPoll();
}
#endif

/*------------------------------------------------------------------*
 * Host driver
 *------------------------------------------------------------------*/
static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);
static void    send_programmable_button(uint32_t data);

static host_driver_t driver = {keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer, send_programmable_button};

host_driver_t *vusb_driver(void) {
    return &driver;
}

static uint8_t keyboard_leds(void) {
    return keyboard_led_state;
}

static void send_keyboard(report_keyboard_t *report) {
    uint8_t next = (kbuf_head + 1) % KBUF_SIZE;
    if (next != kbuf_tail) {
        kbuf[kbuf_head] = *report;
        kbuf_head       = next;
    } else {
        dprint("kbuf: full\n");
    }

    // NOTE: send key strokes of Macro
    usbPoll();
    vusb_transfer_keyboard();
    keyboard_report_sent = *report;
}

#ifndef KEYBOARD_SHARED_EP
#    define usbInterruptIsReadyShared usbInterruptIsReady3
#    define usbSetInterruptShared usbSetInterrupt3
#else
#    define usbInterruptIsReadyShared usbInterruptIsReady
#    define usbSetInterruptShared usbSetInterrupt
#endif

static void send_mouse(report_mouse_t *report) {
#ifdef MOUSE_ENABLE
    if (usbInterruptIsReadyShared()) {
        usbSetInterruptShared((void *)report, sizeof(report_mouse_t));
    }
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
    if (usbInterruptIsReadyShared()) {
        usbSetInterruptShared((void *)&report, sizeof(report_extra_t));
    }
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

void send_digitizer(report_digitizer_t *report) {
#ifdef DIGITIZER_ENABLE
    if (usbInterruptIsReadyShared()) {
        usbSetInterruptShared((void *)report, sizeof(report_digitizer_t));
    }
#endif
}

static void send_programmable_button(uint32_t data) {
#ifdef PROGRAMMABLE_BUTTON_ENABLE
    static report_programmable_button_t report = {
        .report_id = REPORT_ID_PROGRAMMABLE_BUTTON,
    };

    report.usage = data;

    if (usbInterruptIsReadyShared()) {
        usbSetInterruptShared((void *)&report, sizeof(report));
    }
#endif
}

/*------------------------------------------------------------------*
 * Request from host                                                *
 *------------------------------------------------------------------*/
static struct {
    uint16_t len;
    enum { NONE, SET_LED } kind;
} last_req;

usbMsgLen_t usbFunctionSetup(uchar data[8]) {
    usbRequest_t *rq = (void *)data;

    if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) { /* class request type */
        if (rq->bRequest == USBRQ_HID_GET_REPORT) {
            dprint("GET_REPORT:");
            if (rq->wIndex.word == KEYBOARD_INTERFACE) {
                usbMsgPtr = (usbMsgPtr_t)&keyboard_report_sent;
                return sizeof(keyboard_report_sent);
            }
        } else if (rq->bRequest == USBRQ_HID_GET_IDLE) {
            dprint("GET_IDLE:");
            usbMsgPtr = (usbMsgPtr_t)&vusb_idle_rate;
            return 1;
        } else if (rq->bRequest == USBRQ_HID_SET_IDLE) {
            vusb_idle_rate = rq->wValue.bytes[1];
            dprintf("SET_IDLE: %02X", vusb_idle_rate);
        } else if (rq->bRequest == USBRQ_HID_SET_REPORT) {
            dprint("SET_REPORT:");
            // Report Type: 0x02(Out)/ReportID: 0x00(none) && Interface: 0(keyboard)
            if (rq->wValue.word == 0x0200 && rq->wIndex.word == KEYBOARD_INTERFACE) {
                dprint("SET_LED:");
                last_req.kind = SET_LED;
                last_req.len  = rq->wLength.word;
            }
            return USB_NO_MSG; // to get data in usbFunctionWrite
        } else {
            dprint("UNKNOWN:");
        }
    } else {
        dprint("VENDOR:");
        /* no vendor specific requests implemented */
    }
    dprint("\n");
    return 0; /* default for not implemented requests: return no data back to host */
}

uchar usbFunctionWrite(uchar *data, uchar len) {
    if (last_req.len == 0) {
        return -1;
    }
    switch (last_req.kind) {
        case SET_LED:
            dprintf("SET_LED: %02X\n", data[0]);
            keyboard_led_state = data[0];
            last_req.len       = 0;
            return 1;
            break;
        case NONE:
        default:
            return -1;
            break;
    }
    return 1;
}

void usbFunctionWriteOut(uchar *data, uchar len) {
#ifdef RAW_ENABLE
    // Data from host must be divided every 8bytes
    if (len != 8) {
        dprint("RAW: invalid length\n");
        raw_output_received_bytes = 0;
        return;
    }

    if (raw_output_received_bytes + len > RAW_BUFFER_SIZE) {
        dprint("RAW: buffer full\n");
        raw_output_received_bytes = 0;
    } else {
        for (uint8_t i = 0; i < 8; i++) {
            raw_output_buffer[raw_output_received_bytes + i] = data[i];
        }
        raw_output_received_bytes += len;
    }
#endif
}

/*------------------------------------------------------------------*
 * Descriptors                                                      *
 *------------------------------------------------------------------*/

#ifdef KEYBOARD_SHARED_EP
const PROGMEM uchar shared_hid_report[] = {
#    define SHARED_REPORT_STARTED
#else
const PROGMEM uchar keyboard_hid_report[] = {
#endif
    0x05, 0x01, // Usage Page (Generic Desktop)
    0x09, 0x06, // Usage (Keyboard)
    0xA1, 0x01, // Collection (Application)
#ifdef KEYBOARD_SHARED_EP
    0x85, REPORT_ID_KEYBOARD, // Report ID
#endif
    // Modifiers (8 bits)
    0x05, 0x07, //   Usage Page (Keyboard/Keypad)
    0x19, 0xE0, //   Usage Minimum (Keyboard Left Control)
    0x29, 0xE7, //   Usage Maximum (Keyboard Right GUI)
    0x15, 0x00, //   Logical Minimum (0)
    0x25, 0x01, //   Logical Maximum (1)
    0x95, 0x08, //   Report Count (8)
    0x75, 0x01, //   Report Size (1)
    0x81, 0x02, //   Input (Data, Variable, Absolute)
    // Reserved (1 byte)
    0x95, 0x01, //   Report Count (1)
    0x75, 0x08, //   Report Size (8)
    0x81, 0x03, //   Input (Constant)
    // Keycodes (6 bytes)
    0x05, 0x07,       //   Usage Page (Keyboard/Keypad)
    0x19, 0x00,       //   Usage Minimum (0)
    0x29, 0xFF,       //   Usage Maximum (255)
    0x15, 0x00,       //   Logical Minimum (0)
    0x26, 0xFF, 0x00, //   Logical Maximum (255)
    0x95, 0x06,       //   Report Count (6)
    0x75, 0x08,       //   Report Size (8)
    0x81, 0x00,       //   Input (Data, Array, Absolute)

    // Status LEDs (5 bits)
    0x05, 0x08, //   Usage Page (LED)
    0x19, 0x01, //   Usage Minimum (Num Lock)
    0x29, 0x05, //   Usage Maximum (Kana)
    0x95, 0x05, //   Report Count (5)
    0x75, 0x01, //   Report Size (1)
    0x91, 0x02, //   Output (Data, Variable, Absolute)
    // LED padding (3 bits)
    0x95, 0x01, //   Report Count (1)
    0x75, 0x03, //   Report Size (3)
    0x91, 0x03, //   Output (Constant)
    0xC0,       // End Collection
#ifndef KEYBOARD_SHARED_EP
};
#endif

#if defined(SHARED_EP_ENABLE) && !defined(SHARED_REPORT_STARTED)
const PROGMEM uchar shared_hid_report[] = {
#    define SHARED_REPORT_STARTED
#endif

#ifdef MOUSE_ENABLE
    // Mouse report descriptor
    0x05, 0x01,            // Usage Page (Generic Desktop)
    0x09, 0x02,            // Usage (Mouse)
    0xA1, 0x01,            // Collection (Application)
    0x85, REPORT_ID_MOUSE, //   Report ID
    0x09, 0x01,            //   Usage (Pointer)
    0xA1, 0x00,            //   Collection (Physical)
    // Buttons (8 bits)
    0x05, 0x09, //     Usage Page (Button)
    0x19, 0x01, //     Usage Minimum (Button 1)
    0x29, 0x08, //     Usage Maximum (Button 8)
    0x15, 0x00, //     Logical Minimum (0)
    0x25, 0x01, //     Logical Maximum (1)
    0x95, 0x08, //     Report Count (8)
    0x75, 0x01, //     Report Size (1)
    0x81, 0x02, //     Input (Data, Variable, Absolute)

    // X/Y position (2 bytes)
    0x05, 0x01, //     Usage Page (Generic Desktop)
    0x09, 0x30, //     Usage (X)
    0x09, 0x31, //     Usage (Y)
    0x15, 0x81, //     Logical Minimum (-127)
    0x25, 0x7F, //     Logical Maximum (127)
    0x95, 0x02, //     Report Count (2)
    0x75, 0x08, //     Report Size (8)
    0x81, 0x06, //     Input (Data, Variable, Relative)

    // Vertical wheel (1 byte)
    0x09, 0x38, //     Usage (Wheel)
    0x15, 0x81, //     Logical Minimum (-127)
    0x25, 0x7F, //     Logical Maximum (127)
    0x95, 0x01, //     Report Count (1)
    0x75, 0x08, //     Report Size (8)
    0x81, 0x06, //     Input (Data, Variable, Relative)
    // Horizontal wheel (1 byte)
    0x05, 0x0C,       //     Usage Page (Consumer)
    0x0A, 0x38, 0x02, //     Usage (AC Pan)
    0x15, 0x81,       //     Logical Minimum (-127)
    0x25, 0x7F,       //     Logical Maximum (127)
    0x95, 0x01,       //     Report Count (1)
    0x75, 0x08,       //     Report Size (8)
    0x81, 0x06,       //     Input (Data, Variable, Relative)
    0xC0,             //   End Collection
    0xC0,             // End Collection
#endif

#ifdef EXTRAKEY_ENABLE
    // Extrakeys report descriptor
    0x05, 0x01,             // Usage Page (Generic Desktop)
    0x09, 0x80,             // Usage (System Control)
    0xA1, 0x01,             // Collection (Application)
    0x85, REPORT_ID_SYSTEM, //   Report ID
    0x19, 0x01,             //   Usage Minimum (Pointer)
    0x2A, 0xB7, 0x00,       //   Usage Maximum (System Display LCD Autoscale)
    0x15, 0x01,             //   Logical Minimum
    0x26, 0xB7, 0x00,       //   Logical Maximum
    0x95, 0x01,             //   Report Count (1)
    0x75, 0x10,             //   Report Size (16)
    0x81, 0x00,             //   Input (Data, Array, Absolute)
    0xC0,                   // End Collection

    0x05, 0x0C,               // Usage Page (Consumer)
    0x09, 0x01,               // Usage (Consumer Control)
    0xA1, 0x01,               // Collection (Application)
    0x85, REPORT_ID_CONSUMER, //   Report ID
    0x19, 0x01,               //   Usage Minimum (Consumer Control)
    0x2A, 0xA0, 0x02,         //   Usage Maximum (AC Desktop Show All Applications)
    0x15, 0x01,               //   Logical Minimum
    0x26, 0xA0, 0x02,         //   Logical Maximum
    0x95, 0x01,               //   Report Count (1)
    0x75, 0x10,               //   Report Size (16)
    0x81, 0x00,               //   Input (Data, Array, Absolute)
    0xC0,                     // End Collection
#endif

#ifdef DIGITIZER_ENABLE
    // Digitizer report descriptor
    0x05, 0x0D,                // Usage Page (Digitizers)
    0x09, 0x01,                // Usage (Digitizer)
    0xA1, 0x01,                // Collection (Application)
    0x85, REPORT_ID_DIGITIZER, //   Report ID
    0x09, 0x22,                //   Usage (Finger)
    0xA1, 0x00,                //   Collection (Physical)
    // Tip Switch (1 bit)
    0x09, 0x42, //     Usage (Tip Switch)
    0x15, 0x00, //     Logical Minimum
    0x25, 0x01, //     Logical Maximum
    0x95, 0x01, //     Report Count (1)
    0x75, 0x01, //     Report Size (16)
    0x81, 0x02, //     Input (Data, Variable, Absolute)
    // In Range (1 bit)
    0x09, 0x32, //     Usage (In Range)
    0x81, 0x02, //     Input (Data, Variable, Absolute)
    // Padding (6 bits)
    0x95, 0x06, //     Report Count (6)
    0x81, 0x03, //     Input (Constant)

    // X/Y Position (4 bytes)
    0x05, 0x01,       //     Usage Page (Generic Desktop)
    0x26, 0xFF, 0x7F, //     Logical Maximum (32767)
    0x95, 0x01,       //     Report Count (1)
    0x75, 0x10,       //     Report Size (16)
    0x65, 0x33,       //     Unit (Inch, English Linear)
    0x55, 0x0E,       //     Unit Exponent (-2)
    0x09, 0x30,       //     Usage (X)
    0x81, 0x02,       //     Input (Data, Variable, Absolute)
    0x09, 0x31,       //     Usage (Y)
    0x81, 0x02,       //     Input (Data, Variable, Absolute)
    0xC0,             //   End Collection
    0xC0,             // End Collection
#endif

#ifdef PROGRAMMABLE_BUTTON_ENABLE
    // Programmable buttons report descriptor
    0x05, 0x0C,                          // Usage Page (Consumer)
    0x09, 0x01,                          // Usage (Consumer Control)
    0xA1, 0x01,                          // Collection (Application)
    0x85, REPORT_ID_PROGRAMMABLE_BUTTON, //   Report ID
    0x09, 0x03,                          //   Usage (Programmable Buttons)
    0xA1, 0x04,                          //   Collection (Named Array)
    0x05, 0x09,                          //     Usage Page (Button)
    0x19, 0x01,                          //     Usage Minimum (Button 1)
    0x29, 0x20,                          //     Usage Maximum (Button 32)
    0x15, 0x00,                          //     Logical Minimum (0)
    0x25, 0x01,                          //     Logical Maximum (1)
    0x95, 0x20,                          //     Report Count (32)
    0x75, 0x01,                          //     Report Size (1)
    0x81, 0x02,                          //     Input (Data, Variable, Absolute)
    0xC0,                                //   End Collection
    0xC0,                                // End Collection
#endif

#ifdef SHARED_EP_ENABLE
};
#endif

#ifdef RAW_ENABLE
const PROGMEM uchar raw_hid_report[] = {
    0x06, RAW_USAGE_PAGE_LO, RAW_USAGE_PAGE_HI, // Usage Page (Vendor Defined)
    0x09, RAW_USAGE_ID,                         // Usage (Vendor Defined)
    0xA1, 0x01,                                 // Collection (Application)
    // Data to host
    0x09, 0x62,            //   Usage (Vendor Defined)
    0x15, 0x00,            //   Logical Minimum (0)
    0x26, 0xFF, 0x00,      //   Logical Maximum (255)
    0x95, RAW_BUFFER_SIZE, //   Report Count
    0x75, 0x08,            //   Report Size (8)
    0x81, 0x02,            //   Input (Data, Variable, Absolute)
    // Data from host
    0x09, 0x63,            //   Usage (Vendor Defined)
    0x15, 0x00,            //   Logical Minimum (0)
    0x26, 0xFF, 0x00,      //   Logical Maximum (255)
    0x95, RAW_BUFFER_SIZE, //   Report Count
    0x75, 0x08,            //   Report Size (8)
    0x91, 0x02,            //   Output (Data, Variable, Absolute)
    0xC0                   // End Collection
};
#endif

#if defined(CONSOLE_ENABLE)
const PROGMEM uchar console_hid_report[] = {
    0x06, 0x31, 0xFF, // Usage Page (Vendor Defined - PJRC Teensy compatible)
    0x09, 0x74,       // Usage (Vendor Defined - PJRC Teensy compatible)
    0xA1, 0x01,       // Collection (Application)
    // Data to host
    0x09, 0x75,                //   Usage (Vendor Defined)
    0x15, 0x00,                //   Logical Minimum (0x00)
    0x26, 0xFF, 0x00,          //   Logical Maximum (0x00FF)
    0x95, CONSOLE_BUFFER_SIZE, //   Report Count
    0x75, 0x08,                //   Report Size (8)
    0x81, 0x02,                //   Input (Data, Variable, Absolute)
    // Data from host
    0x09, 0x76,                //   Usage (Vendor Defined)
    0x15, 0x00,                //   Logical Minimum (0x00)
    0x26, 0xFF, 0x00,          //   Logical Maximum (0x00FF)
    0x95, CONSOLE_BUFFER_SIZE, //   Report Count
    0x75, 0x08,                //   Report Size (8)
    0x91, 0x02,                //   Output (Data)
    0xC0                       // End Collection
};
#endif

#ifndef USB_MAX_POWER_CONSUMPTION
#    define USB_MAX_POWER_CONSUMPTION 500
#endif

#ifndef USB_POLLING_INTERVAL_MS
#    define USB_POLLING_INTERVAL_MS 1
#endif

// clang-format off
const PROGMEM usbStringDescriptor_t usbStringDescriptorZero = {
    .header = {
        .bLength         = USB_STRING_LEN(1),
        .bDescriptorType = USBDESCR_STRING
    },
    .bString             = {0x0409} // US English
};

const PROGMEM usbStringDescriptor_t usbStringDescriptorManufacturer = {
    .header = {
        .bLength         = USB_STRING_LEN(sizeof(STR(MANUFACTURER)) - 1),
        .bDescriptorType = USBDESCR_STRING
    },
    .bString             = LSTR(MANUFACTURER)
};

const PROGMEM usbStringDescriptor_t usbStringDescriptorProduct = {
    .header = {
        .bLength         = USB_STRING_LEN(sizeof(STR(PRODUCT)) - 1),
        .bDescriptorType = USBDESCR_STRING
    },
    .bString             = LSTR(PRODUCT)
};

#if defined(SERIAL_NUMBER)
const PROGMEM usbStringDescriptor_t usbStringDescriptorSerial = {
    .header = {
        .bLength         = USB_STRING_LEN(sizeof(SERIAL_NUMBER) - 1),
        .bDescriptorType = USBDESCR_STRING
    },
    .bString             = USBSTR(SERIAL_NUMBER)
};
#endif

/*
 * Device descriptor
 */
const PROGMEM usbDeviceDescriptor_t usbDeviceDescriptor = {
    .header = {
        .bLength         = sizeof(usbDeviceDescriptor_t),
        .bDescriptorType = USBDESCR_DEVICE
    },
    .bcdUSB              = 0x0110,
    .bDeviceClass        = 0x00,
    .bDeviceSubClass     = 0x00,
    .bDeviceProtocol     = 0x00,
    .bMaxPacketSize0     = 8,
    .idVendor            = VENDOR_ID,
    .idProduct           = PRODUCT_ID,
    .bcdDevice           = DEVICE_VER,
    .iManufacturer       = 0x01,
    .iProduct            = 0x02,
#if defined(SERIAL_NUMBER)
    .iSerialNumber       = 0x03,
#else
    .iSerialNumber       = 0x00,
#endif
    .bNumConfigurations  = 1
};

/*
 * Configuration descriptors
 */
const PROGMEM usbConfigurationDescriptor_t usbConfigurationDescriptor = {
    .header = {
        .header = {
            .bLength         = sizeof(usbConfigurationDescriptorHeader_t),
            .bDescriptorType = USBDESCR_CONFIG
        },
        .wTotalLength        = sizeof(usbConfigurationDescriptor_t),
        .bNumInterfaces      = TOTAL_INTERFACES,
        .bConfigurationValue = 0x01,
        .iConfiguration      = 0x00,
        .bmAttributes        = (1 << 7) | USBATTR_REMOTEWAKE,
        .bMaxPower           = USB_MAX_POWER_CONSUMPTION / 2
    },

#    ifndef KEYBOARD_SHARED_EP
    /*
     * Keyboard
     */
    .keyboardInterface = {
        .header = {
            .bLength         = sizeof(usbInterfaceDescriptor_t),
            .bDescriptorType = USBDESCR_INTERFACE
        },
        .bInterfaceNumber    = KEYBOARD_INTERFACE,
        .bAlternateSetting   = 0x00,
        .bNumEndpoints       = 1,
        .bInterfaceClass     = 0x03,
        .bInterfaceSubClass  = 0x01,
        .bInterfaceProtocol  = 0x01,
        .iInterface          = 0x00
    },
    .keyboardHID = {
        .header = {
            .bLength         = sizeof(usbHIDDescriptor_t),
            .bDescriptorType = USBDESCR_HID
        },
        .bcdHID              = 0x0101,
        .bCountryCode        = 0x00,
        .bNumDescriptors     = 1,
        .bDescriptorType     = USBDESCR_HID_REPORT,
        .wDescriptorLength   = sizeof(keyboard_hid_report)
    },
    .keyboardINEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_DEVICE_TO_HOST | 1),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = 8,
        .bInterval           = USB_POLLING_INTERVAL_MS
    },
#    endif

#    if defined(RAW_ENABLE)
    /*
     * RAW HID
     */
    .rawInterface = {
        .header = {
            .bLength         = sizeof(usbInterfaceDescriptor_t),
            .bDescriptorType = USBDESCR_INTERFACE
        },
        .bInterfaceNumber    = RAW_INTERFACE,
        .bAlternateSetting   = 0x00,
        .bNumEndpoints       = 2,
        .bInterfaceClass     = 0x03,
        .bInterfaceSubClass  = 0x00,
        .bInterfaceProtocol  = 0x00,
        .iInterface          = 0x00
    },
    .rawHID = {
        .header = {
            .bLength         = sizeof(usbHIDDescriptor_t),
            .bDescriptorType = USBDESCR_HID
        },
        .bcdHID              = 0x0101,
        .bCountryCode        = 0x00,
        .bNumDescriptors     = 1,
        .bDescriptorType     = USBDESCR_HID_REPORT,
        .wDescriptorLength   = sizeof(raw_hid_report)
    },
    .rawINEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_DEVICE_TO_HOST | USB_CFG_EP4_NUMBER),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = RAW_EPSIZE,
        .bInterval           = USB_POLLING_INTERVAL_MS
    },
    .rawOUTEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_HOST_TO_DEVICE | USB_CFG_EP4_NUMBER),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = RAW_EPSIZE,
        .bInterval           = USB_POLLING_INTERVAL_MS
    },
#    endif

#    ifdef SHARED_EP_ENABLE
    /*
     * Shared
     */
    .sharedInterface = {
        .header = {
            .bLength         = sizeof(usbInterfaceDescriptor_t),
            .bDescriptorType = USBDESCR_INTERFACE
        },
        .bInterfaceNumber    = SHARED_INTERFACE,
        .bAlternateSetting   = 0x00,
        .bNumEndpoints       = 1,
        .bInterfaceClass     = 0x03,
#        ifdef KEYBOARD_SHARED_EP
        .bInterfaceSubClass  = 0x01,
        .bInterfaceProtocol  = 0x01,
#        else
        .bInterfaceSubClass  = 0x00,
        .bInterfaceProtocol  = 0x00,
#        endif
        .iInterface          = 0x00
    },
    .sharedHID = {
        .header = {
            .bLength         = sizeof(usbHIDDescriptor_t),
            .bDescriptorType = USBDESCR_HID
        },
        .bcdHID              = 0x0101,
        .bCountryCode        = 0x00,
        .bNumDescriptors     = 1,
        .bDescriptorType     = USBDESCR_HID_REPORT,
        .wDescriptorLength   = sizeof(shared_hid_report)
    },
    .sharedINEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
#        ifdef KEYBOARD_SHARED_EP
        .bEndpointAddress    = (USBRQ_DIR_DEVICE_TO_HOST | 1),
#        else
        .bEndpointAddress    = (USBRQ_DIR_DEVICE_TO_HOST | USB_CFG_EP3_NUMBER),
#        endif
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = 8,
        .bInterval           = USB_POLLING_INTERVAL_MS
    },
#    endif

#    if defined(CONSOLE_ENABLE)
    /*
     * Console
     */
    .consoleInterface = {
        .header = {
            .bLength         = sizeof(usbInterfaceDescriptor_t),
            .bDescriptorType = USBDESCR_INTERFACE
        },
        .bInterfaceNumber    = CONSOLE_INTERFACE,
        .bAlternateSetting   = 0x00,
        .bNumEndpoints       = 2,
        .bInterfaceClass     = 0x03,
        .bInterfaceSubClass  = 0x00,
        .bInterfaceProtocol  = 0x00,
        .iInterface          = 0x00
    },
    .consoleHID = {
        .header = {
            .bLength         = sizeof(usbHIDDescriptor_t),
            .bDescriptorType = USBDESCR_HID
        },
        .bcdHID              = 0x0111,
        .bCountryCode        = 0x00,
        .bNumDescriptors     = 1,
        .bDescriptorType     = USBDESCR_HID_REPORT,
        .wDescriptorLength   = sizeof(console_hid_report)
    },
    .consoleINEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_DEVICE_TO_HOST | USB_CFG_EP3_NUMBER),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = CONSOLE_EPSIZE,
        .bInterval           = 0x01
    },
    .consoleOUTEndpoint = {
        .header = {
            .bLength         = sizeof(usbEndpointDescriptor_t),
            .bDescriptorType = USBDESCR_ENDPOINT
        },
        .bEndpointAddress    = (USBRQ_DIR_HOST_TO_DEVICE | USB_CFG_EP3_NUMBER),
        .bmAttributes        = 0x03,
        .wMaxPacketSize      = CONSOLE_EPSIZE,
        .bInterval           = 0x01
    }
#    endif
};

// clang-format on

USB_PUBLIC usbMsgLen_t usbFunctionDescriptor(struct usbRequest *rq) {
    usbMsgLen_t len = 0;

    switch (rq->wValue.bytes[1]) {
        case USBDESCR_DEVICE:
            usbMsgPtr = (usbMsgPtr_t)&usbDeviceDescriptor;
            len       = sizeof(usbDeviceDescriptor_t);
            break;
        case USBDESCR_CONFIG:
            usbMsgPtr = (usbMsgPtr_t)&usbConfigurationDescriptor;
            len       = sizeof(usbConfigurationDescriptor_t);
            break;
        case USBDESCR_STRING:
            switch (rq->wValue.bytes[0]) {
                case 0:
                    usbMsgPtr = (usbMsgPtr_t)&usbStringDescriptorZero;
                    len       = usbStringDescriptorZero.header.bLength;
                    break;
                case 1: // iManufacturer
                    usbMsgPtr = (usbMsgPtr_t)&usbStringDescriptorManufacturer;
                    len       = usbStringDescriptorManufacturer.header.bLength;
                    break;
                case 2: // iProduct
                    usbMsgPtr = (usbMsgPtr_t)&usbStringDescriptorProduct;
                    len       = usbStringDescriptorProduct.header.bLength;
                    break;
#if defined(SERIAL_NUMBER)
                case 3: // iSerialNumber
                    usbMsgPtr = (usbMsgPtr_t)&usbStringDescriptorSerial;
                    len       = usbStringDescriptorSerial.header.bLength;
                    break;
#endif
            }
            break;
        case USBDESCR_HID:
            switch (rq->wValue.bytes[0]) {
#ifndef KEYBOARD_SHARED_EP
                case KEYBOARD_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)&usbConfigurationDescriptor.keyboardHID;
                    len       = sizeof(usbHIDDescriptor_t);
                    break;
#endif

#if defined(RAW_ENABLE)
                case RAW_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)&usbConfigurationDescriptor.rawHID;
                    len       = sizeof(usbHIDDescriptor_t);
                    break;
#endif

#ifdef SHARED_EP_ENABLE
                case SHARED_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)&usbConfigurationDescriptor.sharedHID;
                    len       = sizeof(usbHIDDescriptor_t);
                    break;
#endif

#if defined(CONSOLE_ENABLE)
                case CONSOLE_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)&usbConfigurationDescriptor.consoleHID;
                    len       = sizeof(usbHIDDescriptor_t);
                    break;
#endif
            }
            break;
        case USBDESCR_HID_REPORT:
            /* interface index */
            switch (rq->wIndex.word) {
#ifndef KEYBOARD_SHARED_EP
                case KEYBOARD_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)keyboard_hid_report;
                    len       = sizeof(keyboard_hid_report);
                    break;
#endif

#if defined(RAW_ENABLE)
                case RAW_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)raw_hid_report;
                    len       = sizeof(raw_hid_report);
                    break;
#endif

#ifdef SHARED_EP_ENABLE
                case SHARED_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)shared_hid_report;
                    len       = sizeof(shared_hid_report);
                    break;
#endif

#if defined(CONSOLE_ENABLE)
                case CONSOLE_INTERFACE:
                    usbMsgPtr = (usbMsgPtr_t)console_hid_report;
                    len       = sizeof(console_hid_report);
                    break;
#endif
            }
            break;
    }
    return len;
}
