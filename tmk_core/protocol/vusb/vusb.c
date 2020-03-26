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

#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <stdint.h>
#include "usbdrv.h"
#include "usbconfig.h"
#include "host.h"
#include "report.h"
#include "print.h"
#include "debug.h"
#include "host_driver.h"
#include "vusb.h"
#include <util/delay.h>

static uint8_t vusb_keyboard_leds = 0;
static uint8_t vusb_idle_rate     = 0;

/* Keyboard report send buffer */
#define KBUF_SIZE 16
static report_keyboard_t kbuf[KBUF_SIZE];
static uint8_t           kbuf_head = 0;
static uint8_t           kbuf_tail = 0;

typedef struct {
    uint8_t modifier;
    uint8_t reserved;
    uint8_t keycode[6];
} keyboard_report_t;

static keyboard_report_t keyboard_report;  // sent to PC

#define VUSB_TRANSFER_KEYBOARD_MAX_TRIES 10

/* transfer keyboard report from buffer */
void vusb_transfer_keyboard(void) {
    for (int i = 0; i < VUSB_TRANSFER_KEYBOARD_MAX_TRIES; i++) {
        if (usbInterruptIsReady()) {
            if (kbuf_head != kbuf_tail) {
                usbSetInterrupt((void *)&kbuf[kbuf_tail], sizeof(report_keyboard_t));
                kbuf_tail = (kbuf_tail + 1) % KBUF_SIZE;
                if (debug_keyboard) {
                    print("V-USB: kbuf[");
                    pdec(kbuf_tail);
                    print("->");
                    pdec(kbuf_head);
                    print("](");
                    phex((kbuf_head < kbuf_tail) ? (KBUF_SIZE - kbuf_tail + kbuf_head) : (kbuf_head - kbuf_tail));
                    print(")\n");
                }
            }
            break;
        }
        usbPoll();
        _delay_ms(1);
    }
}

/*------------------------------------------------------------------*
 * Host driver
 *------------------------------------------------------------------*/
static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);

static host_driver_t driver = {keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer};

host_driver_t *vusb_driver(void) { return &driver; }

static uint8_t keyboard_leds(void) { return vusb_keyboard_leds; }

static void send_keyboard(report_keyboard_t *report) {
    uint8_t next = (kbuf_head + 1) % KBUF_SIZE;
    if (next != kbuf_tail) {
        kbuf[kbuf_head] = *report;
        kbuf_head       = next;
    } else {
        debug("kbuf: full\n");
    }

    // NOTE: send key strokes of Macro
    usbPoll();
    vusb_transfer_keyboard();
}

typedef struct {
    uint8_t        report_id;
    report_mouse_t report;
} __attribute__((packed)) vusb_mouse_report_t;

static void send_mouse(report_mouse_t *report) {
    vusb_mouse_report_t r = {.report_id = REPORT_ID_MOUSE, .report = *report};
    if (usbInterruptIsReady3()) {
        usbSetInterrupt3((void *)&r, sizeof(vusb_mouse_report_t));
    }
}

#ifdef EXTRAKEY_ENABLE
static void send_extra(uint8_t report_id, uint16_t data) {
    static uint8_t  last_id   = 0;
    static uint16_t last_data = 0;
    if ((report_id == last_id) && (data == last_data)) return;
    last_id   = report_id;
    last_data = data;

    report_extra_t report = {.report_id = report_id, .usage = data};
    if (usbInterruptIsReady3()) {
        usbSetInterrupt3((void *)&report, sizeof(report));
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
            debug("GET_REPORT:");
            /* we only have one report type, so don't look at wValue */
            usbMsgPtr = (void *)&keyboard_report;
            return sizeof(keyboard_report);
        } else if (rq->bRequest == USBRQ_HID_GET_IDLE) {
            debug("GET_IDLE: ");
            // debug_hex(vusb_idle_rate);
            usbMsgPtr = &vusb_idle_rate;
            return 1;
        } else if (rq->bRequest == USBRQ_HID_SET_IDLE) {
            vusb_idle_rate = rq->wValue.bytes[1];
            debug("SET_IDLE: ");
            debug_hex(vusb_idle_rate);
        } else if (rq->bRequest == USBRQ_HID_SET_REPORT) {
            debug("SET_REPORT: ");
            // Report Type: 0x02(Out)/ReportID: 0x00(none) && Interface: 0(keyboard)
            if (rq->wValue.word == 0x0200 && rq->wIndex.word == 0) {
                debug("SET_LED: ");
                last_req.kind = SET_LED;
                last_req.len  = rq->wLength.word;
            }
            return USB_NO_MSG;  // to get data in usbFunctionWrite
        } else {
            debug("UNKNOWN:");
        }
    } else {
        debug("VENDOR:");
        /* no vendor specific requests implemented */
    }
    debug("\n");
    return 0; /* default for not implemented requests: return no data back to host */
}

uchar usbFunctionWrite(uchar *data, uchar len) {
    if (last_req.len == 0) {
        return -1;
    }
    switch (last_req.kind) {
        case SET_LED:
            debug("SET_LED: ");
            debug_hex(data[0]);
            debug("\n");
            vusb_keyboard_leds = data[0];
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

/*------------------------------------------------------------------*
 * Descriptors                                                      *
 *------------------------------------------------------------------*/

const PROGMEM uchar keyboard_hid_report[] = {
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
    0xC0         // End Collection
};

#if defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)
const PROGMEM uchar mouse_extra_hid_report[] = {
#    ifdef MOUSE_ENABLE
    // Mouse report descriptor
    0x05, 0x01,             // Usage Page (Generic Desktop)
    0x09, 0x02,             // Usage (Mouse)
    0xA1, 0x01,             // Collection (Application)
    0x85, REPORT_ID_MOUSE,  //   Report ID
    0x09, 0x01,             //   Usage (Pointer)
    0xA1, 0x00,             //   Collection (Physical)
    // Buttons (5 bits)
    0x05, 0x09,  //     Usage Page (Button)
    0x19, 0x01,  //     Usage Minimum (Button 1)
    0x29, 0x05,  //     Usage Maximum (Button 5)
    0x15, 0x00,  //     Logical Minimum (0)
    0x25, 0x01,  //     Logical Maximum (1)
    0x95, 0x05,  //     Report Count (5)
    0x75, 0x01,  //     Report Size (1)
    0x81, 0x02,  //     Input (Data, Variable, Absolute)
    // Button padding (3 bits)
    0x95, 0x01,  //     Report Count (1)
    0x75, 0x03,  //     Report Size (3)
    0x81, 0x03,  //     Input (Constant)

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
#    endif

#    ifdef EXTRAKEY_ENABLE
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
    0xC0                       // End Collection
#    endif
};
#endif

#ifndef USB_MAX_POWER_CONSUMPTION
#    define USB_MAX_POWER_CONSUMPTION 500
#endif

// TODO: change this to 10ms to match LUFA
#ifndef USB_POLLING_INTERVAL_MS
#    define USB_POLLING_INTERVAL_MS 1
#endif

/*
 * Descriptor for compite device: Keyboard + Mouse
 *
 * contains: device, interface, HID and endpoint descriptors
 */
#if USB_CFG_DESCR_PROPS_CONFIGURATION
const PROGMEM char usbDescriptorConfiguration[] = {
    /* USB configuration descriptor */
    9,               /* sizeof(usbDescriptorConfiguration): length of descriptor in bytes */
    USBDESCR_CONFIG, /* descriptor type */
#    if defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)
    59,  // 9 + (9 + 9 + 7) + (9 + 9 + 7)
#    else
    34,  // 9 + (9 + 9 + 7)
#    endif
    0,
// 18 + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT3 + 9, 0,
/* total length of data returned (including inlined descriptors) */
#    if defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)
    2, /* number of interfaces in this configuration */
#    else
    1,
#    endif
    1, /* index of this configuration */
    0, /* configuration name string index */
#    if USB_CFG_IS_SELF_POWERED
    (1 << 7) | USBATTR_SELFPOWER, /* attributes */
#    else
    (1 << 7), /* attributes */
#    endif
    USB_MAX_POWER_CONSUMPTION / 2, /* max USB current in 2mA units */

    /*
     * Keyboard interface
     */
    /* Interface descriptor */
    9,                                                                                  /* sizeof(usbDescrInterface): length of descriptor in bytes */
    USBDESCR_INTERFACE,                                                                 /* descriptor type */
    0,                                                                                  /* index of this interface */
    0,                                                                                  /* alternate setting for this interface */
    USB_CFG_HAVE_INTRIN_ENDPOINT,                                                       /* endpoints excl 0: number of endpoint descriptors to follow */
    USB_CFG_INTERFACE_CLASS, USB_CFG_INTERFACE_SUBCLASS, USB_CFG_INTERFACE_PROTOCOL, 0, /* string index for interface */
    /* HID descriptor */
    9,                              /* sizeof(usbDescrHID): length of descriptor in bytes */
    USBDESCR_HID,                   /* descriptor type: HID */
    0x01, 0x01,                     /* BCD representation of HID version */
    0x00,                           /* target country code */
    0x01,                           /* number of HID Report (or other HID class) Descriptor infos to follow */
    0x22,                           /* descriptor type: report */
    sizeof(keyboard_hid_report), 0, /* total length of report descriptor */
/* Endpoint descriptor */
#    if USB_CFG_HAVE_INTRIN_ENDPOINT /* endpoint descriptor for endpoint 1 */
    7,                               /* sizeof(usbDescrEndpoint) */
    USBDESCR_ENDPOINT,               /* descriptor type = endpoint */
    (char)0x81,                      /* IN endpoint number 1 */
    0x03,                            /* attrib: Interrupt endpoint */
    8, 0,                            /* maximum packet size */
    USB_POLLING_INTERVAL_MS,         /* in ms */
#    endif

#    if defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)
    /*
     * Mouse/extrakeys interface
     */
    /* Interface descriptor */
    9,                             /* sizeof(usbDescrInterface): length of descriptor in bytes */
    USBDESCR_INTERFACE,            /* descriptor type */
    1,                             /* index of this interface */
    0,                             /* alternate setting for this interface */
    USB_CFG_HAVE_INTRIN_ENDPOINT3, /* endpoints excl 0: number of endpoint descriptors to follow */
    0x03,                          /* CLASS: HID */
    0,                             /* SUBCLASS: none */
    0,                             /* PROTOCOL: none */
    0,                             /* string index for interface */
    /* HID descriptor */
    9,                                    /* sizeof(usbDescrHID): length of descriptor in bytes */
    USBDESCR_HID,                         /* descriptor type: HID */
    0x01, 0x01,                           /* BCD representation of HID version */
    0x00,                                 /* target country code */
    0x01,                                 /* number of HID Report (or other HID class) Descriptor infos to follow */
    0x22,                                 /* descriptor type: report */
    sizeof(mouse_extra_hid_report), 0,    /* total length of report descriptor */
#        if USB_CFG_HAVE_INTRIN_ENDPOINT3 /* endpoint descriptor for endpoint 3 */
    /* Endpoint descriptor */
    7,                                 /* sizeof(usbDescrEndpoint) */
    USBDESCR_ENDPOINT,                 /* descriptor type = endpoint */
    (char)(0x80 | USB_CFG_EP3_NUMBER), /* IN endpoint number 3 */
    0x03,                              /* attrib: Interrupt endpoint */
    8, 0,                              /* maximum packet size */
    USB_POLLING_INTERVAL_MS,           /* in ms */
#        endif
#    endif
};
#endif

USB_PUBLIC usbMsgLen_t usbFunctionDescriptor(struct usbRequest *rq) {
    usbMsgLen_t len = 0;

    /*
        debug("usbFunctionDescriptor: ");
        debug_hex(rq->bmRequestType); debug(" ");
        debug_hex(rq->bRequest); debug(" ");
        debug_hex16(rq->wValue.word); debug(" ");
        debug_hex16(rq->wIndex.word); debug(" ");
        debug_hex16(rq->wLength.word); debug("\n");
    */
    switch (rq->wValue.bytes[1]) {
#if USB_CFG_DESCR_PROPS_CONFIGURATION
        case USBDESCR_CONFIG:
            usbMsgPtr = (unsigned char *)usbDescriptorConfiguration;
            len       = sizeof(usbDescriptorConfiguration);
            break;
#endif
        case USBDESCR_HID:
            switch (rq->wValue.bytes[0]) {
                case 0:
                    usbMsgPtr = (unsigned char *)(usbDescriptorConfiguration + 9 + 9);
                    len       = 9;
                    break;
#if defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)
                case 1:
                    usbMsgPtr = (unsigned char *)(usbDescriptorConfiguration + 9 + (9 + 9 + 7) + 9);
                    len       = 9;
                    break;
#endif
            }
            break;
        case USBDESCR_HID_REPORT:
            /* interface index */
            switch (rq->wIndex.word) {
                case 0:
                    usbMsgPtr = (unsigned char *)keyboard_hid_report;
                    len       = sizeof(keyboard_hid_report);
                    break;
#if defined(MOUSE_ENABLE) || defined(EXTRAKEY_ENABLE)
                case 1:
                    usbMsgPtr = (unsigned char *)mouse_extra_hid_report;
                    len       = sizeof(mouse_extra_hid_report);
                    break;
#endif
            }
            break;
    }
    // debug("desc len: "); debug_hex(len); debug("\n");
    return len;
}
