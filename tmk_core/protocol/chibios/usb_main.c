// Copyright 2023 Stefan Kerkmann
// Copyright 2020-2021 Ryan (@fauxpark)
// Copyright 2020 Nick Brassel (@tzarc)
// Copyright 2020 a-chol
// Copyright 2020 xyzz
// Copyright 2020 Joel Challis (@zvecr)
// Copyright 2020 George (@goshdarnharris)
// Copyright 2018 James Laird-Wah
// Copyright 2018 Drashna Jaelre (@drashna)
// Copyright 2016 Fredizzimo
// Copyright 2016 Giovanni Di Sirio
// SPDX-License-Identifier: GPL-3.0-or-later OR Apache-2.0

#include <ch.h>
#include <hal.h>
#include <string.h>

#include "usb_main.h"
#include "usb_report_handling.h"

#include "host.h"
#include "suspend.h"
#include "timer.h"
#ifdef SLEEP_LED_ENABLE
#    include "sleep_led.h"
#    include "led.h"
#endif
#include "wait.h"
#include "usb_endpoints.h"
#include "usb_device_state.h"
#include "usb_descriptor.h"
#include "usb_driver.h"
#include "usb_types.h"

#ifdef NKRO_ENABLE
#    include "keycode_config.h"

extern keymap_config_t keymap_config;
#endif

/* ---------------------------------------------------------
 *       Global interface variables and declarations
 * ---------------------------------------------------------
 */

#ifndef usb_lld_connect_bus
#    define usb_lld_connect_bus(usbp)
#endif

#ifndef usb_lld_disconnect_bus
#    define usb_lld_disconnect_bus(usbp)
#endif

extern usb_endpoint_in_t  usb_endpoints_in[USB_ENDPOINT_IN_COUNT];
extern usb_endpoint_out_t usb_endpoints_out[USB_ENDPOINT_OUT_COUNT];

uint8_t _Alignas(2) keyboard_idle     = 0;
uint8_t _Alignas(2) keyboard_protocol = 1;
uint8_t keyboard_led_state            = 0;

static bool __attribute__((__unused__)) send_report_buffered(usb_endpoint_in_lut_t endpoint, void *report, size_t size);
static void __attribute__((__unused__)) flush_report_buffered(usb_endpoint_in_lut_t endpoint, bool padded);
static bool __attribute__((__unused__)) receive_report(usb_endpoint_out_lut_t endpoint, void *report, size_t size);

/* ---------------------------------------------------------
 *            Descriptors and USB driver objects
 * ---------------------------------------------------------
 */

/* USB Low Level driver specific endpoint fields */
#if !defined(usb_lld_endpoint_fields)
#    define usb_lld_endpoint_fields   \
        2,        /* IN multiplier */ \
            NULL, /* SETUP buffer (not a SETUP endpoint) */
#endif

/*
 * Handles the GET_DESCRIPTOR callback
 *
 * Returns the proper descriptor
 */
static const USBDescriptor *usb_get_descriptor_cb(USBDriver *usbp, uint8_t dtype, uint8_t dindex, uint16_t wIndex) {
    usb_control_request_t *setup = (usb_control_request_t *)usbp->setup;

    static USBDescriptor descriptor;
    descriptor.ud_string = NULL;
    descriptor.ud_size   = get_usb_descriptor(setup->wValue.word, setup->wIndex, setup->wLength, (const void **const) & descriptor.ud_string);

    if (descriptor.ud_string == NULL) {
        return NULL;
    }

    return &descriptor;
}

/* ---------------------------------------------------------
 *                  USB driver functions
 * ---------------------------------------------------------
 */

#define USB_EVENT_QUEUE_SIZE 16
usbevent_t event_queue[USB_EVENT_QUEUE_SIZE];
uint8_t    event_queue_head;
uint8_t    event_queue_tail;

void usb_event_queue_init(void) {
    // Initialise the event queue
    memset(&event_queue, 0, sizeof(event_queue));
    event_queue_head = 0;
    event_queue_tail = 0;
}

static inline bool usb_event_queue_enqueue(usbevent_t event) {
    uint8_t next = (event_queue_head + 1) % USB_EVENT_QUEUE_SIZE;
    if (next == event_queue_tail) {
        return false;
    }
    event_queue[event_queue_head] = event;
    event_queue_head              = next;
    return true;
}

static inline bool usb_event_queue_dequeue(usbevent_t *event) {
    if (event_queue_head == event_queue_tail) {
        return false;
    }
    *event           = event_queue[event_queue_tail];
    event_queue_tail = (event_queue_tail + 1) % USB_EVENT_QUEUE_SIZE;
    return true;
}

static inline void usb_event_suspend_handler(void) {
    usb_device_state_set_suspend(USB_DRIVER.configuration != 0, USB_DRIVER.configuration);
#ifdef SLEEP_LED_ENABLE
    sleep_led_enable();
#endif /* SLEEP_LED_ENABLE */
}

static inline void usb_event_wakeup_handler(void) {
    suspend_wakeup_init();
    usb_device_state_set_resume(USB_DRIVER.configuration != 0, USB_DRIVER.configuration);
#ifdef SLEEP_LED_ENABLE
    sleep_led_disable();
    // NOTE: converters may not accept this
    led_set(host_keyboard_leds());
#endif /* SLEEP_LED_ENABLE */
}

bool last_suspend_state = false;

void usb_event_queue_task(void) {
    usbevent_t event;
    while (usb_event_queue_dequeue(&event)) {
        switch (event) {
            case USB_EVENT_SUSPEND:
                last_suspend_state = true;
                usb_event_suspend_handler();
                break;
            case USB_EVENT_WAKEUP:
                last_suspend_state = false;
                usb_event_wakeup_handler();
                break;
            case USB_EVENT_CONFIGURED:
                usb_device_state_set_configuration(USB_DRIVER.configuration != 0, USB_DRIVER.configuration);
                break;
            case USB_EVENT_UNCONFIGURED:
                usb_device_state_set_configuration(false, 0);
                break;
            case USB_EVENT_RESET:
                usb_device_state_set_reset();
                break;
            default:
                // Nothing to do, we don't handle it.
                break;
        }
    }
}

/* Handles the USB driver global events. */
static void usb_event_cb(USBDriver *usbp, usbevent_t event) {
    switch (event) {
        case USB_EVENT_ADDRESS:
            return;

        case USB_EVENT_CONFIGURED:
            osalSysLockFromISR();
            for (int i = 0; i < USB_ENDPOINT_IN_COUNT; i++) {
                usb_endpoint_in_configure_cb(&usb_endpoints_in[i]);
            }
            for (int i = 0; i < USB_ENDPOINT_OUT_COUNT; i++) {
                usb_endpoint_out_configure_cb(&usb_endpoints_out[i]);
            }
            osalSysUnlockFromISR();
            if (last_suspend_state) {
                usb_event_queue_enqueue(USB_EVENT_WAKEUP);
            }
            usb_event_queue_enqueue(USB_EVENT_CONFIGURED);
            return;
        case USB_EVENT_SUSPEND:
            /* Falls into.*/
        case USB_EVENT_UNCONFIGURED:
            /* Falls into.*/
        case USB_EVENT_RESET:
            usb_event_queue_enqueue(event);
            chSysLockFromISR();
            for (int i = 0; i < USB_ENDPOINT_IN_COUNT; i++) {
                usb_endpoint_in_suspend_cb(&usb_endpoints_in[i]);
            }
            for (int i = 0; i < USB_ENDPOINT_OUT_COUNT; i++) {
                usb_endpoint_out_suspend_cb(&usb_endpoints_out[i]);
            }
            chSysUnlockFromISR();
            return;

        case USB_EVENT_WAKEUP:
            chSysLockFromISR();
            for (int i = 0; i < USB_ENDPOINT_IN_COUNT; i++) {
                usb_endpoint_in_wakeup_cb(&usb_endpoints_in[i]);
            }
            for (int i = 0; i < USB_ENDPOINT_OUT_COUNT; i++) {
                usb_endpoint_out_wakeup_cb(&usb_endpoints_out[i]);
            }
            chSysUnlockFromISR();
            usb_event_queue_enqueue(USB_EVENT_WAKEUP);
            return;

        case USB_EVENT_STALLED:
            return;
    }
}

/*
 * Appendix G: HID Request Support Requirements
 *
 * The following table enumerates the requests that need to be supported by various types of HID class devices.
 * Device type     GetReport   SetReport   GetIdle     SetIdle     GetProtocol SetProtocol
 * ------------------------------------------------------------------------------------------
 * Boot Mouse      Required    Optional    Optional    Optional    Required    Required
 * Non-Boot Mouse  Required    Optional    Optional    Optional    Optional    Optional
 * Boot Keyboard   Required    Optional    Required    Required    Required    Required
 * Non-Boot Keybrd Required    Optional    Required    Required    Optional    Optional
 * Other Device    Required    Optional    Optional    Optional    Optional    Optional
 */

static uint8_t _Alignas(4) set_report_buf[2];

static void set_led_transfer_cb(USBDriver *usbp) {
    usb_control_request_t *setup = (usb_control_request_t *)usbp->setup;

    if (setup->wLength == 2) {
        uint8_t report_id = set_report_buf[0];
        if ((report_id == REPORT_ID_KEYBOARD) || (report_id == REPORT_ID_NKRO)) {
            keyboard_led_state = set_report_buf[1];
        }
    } else {
        keyboard_led_state = set_report_buf[0];
    }
}

static bool usb_requests_hook_cb(USBDriver *usbp) {
    usb_control_request_t *setup = (usb_control_request_t *)usbp->setup;

    /* Handle HID class specific requests */
    if ((setup->bmRequestType & (USB_RTYPE_TYPE_MASK | USB_RTYPE_RECIPIENT_MASK)) == (USB_RTYPE_TYPE_CLASS | USB_RTYPE_RECIPIENT_INTERFACE)) {
        switch (setup->bmRequestType & USB_RTYPE_DIR_MASK) {
            case USB_RTYPE_DIR_DEV2HOST:
                switch (setup->bRequest) {
                    case HID_REQ_GetReport:
                        return usb_get_report_cb(usbp);
                    case HID_REQ_GetProtocol:
                        if (setup->wIndex == KEYBOARD_INTERFACE) {
                            usbSetupTransfer(usbp, &keyboard_protocol, sizeof(uint8_t), NULL);
                            return true;
                        }
                        break;

                    case HID_REQ_GetIdle:
                        return usb_get_idle_cb(usbp);
                }

            case USB_RTYPE_DIR_HOST2DEV:
                switch (setup->bRequest) {
                    case HID_REQ_SetReport:
                        switch (setup->wIndex) {
                            case KEYBOARD_INTERFACE:
#if defined(SHARED_EP_ENABLE) && !defined(KEYBOARD_SHARED_EP)
                            case SHARED_INTERFACE:
#endif
                                usbSetupTransfer(usbp, set_report_buf, sizeof(set_report_buf), set_led_transfer_cb);
                                return true;
                        }
                        break;
                    case HID_REQ_SetProtocol:
                        if (setup->wIndex == KEYBOARD_INTERFACE) {
                            keyboard_protocol = setup->wValue.word;
                        }
                        usbSetupTransfer(usbp, NULL, 0, NULL);
                        return true;
                    case HID_REQ_SetIdle:
                        keyboard_idle = setup->wValue.hbyte;
                        return usb_set_idle_cb(usbp);
                }
                break;
        }
    }

    /* Handle the Get_Descriptor Request for HID class, which is not handled by
     * the ChibiOS USB driver */
    if (((setup->bmRequestType & (USB_RTYPE_DIR_MASK | USB_RTYPE_RECIPIENT_MASK)) == (USB_RTYPE_DIR_DEV2HOST | USB_RTYPE_RECIPIENT_INTERFACE)) && (setup->bRequest == USB_REQ_GET_DESCRIPTOR)) {
        const USBDescriptor *descriptor = usbp->config->get_descriptor_cb(usbp, setup->wValue.lbyte, setup->wValue.hbyte, setup->wIndex);
        if (descriptor == NULL) {
            return false;
        }
        usbSetupTransfer(usbp, (uint8_t *)descriptor->ud_string, descriptor->ud_size, NULL);
        return true;
    }

    for (int i = 0; i < USB_ENDPOINT_IN_COUNT; i++) {
        if (usb_endpoints_in[i].usb_requests_cb != NULL) {
            if (usb_endpoints_in[i].usb_requests_cb(usbp)) {
                return true;
            }
        }
    }

    return false;
}

static __attribute__((unused)) void dummy_cb(USBDriver *usbp) {
    (void)usbp;
}

static const USBConfig usbcfg = {
    usb_event_cb,          /* USB events callback */
    usb_get_descriptor_cb, /* Device GET_DESCRIPTOR request callback */
    usb_requests_hook_cb,  /* Requests hook callback */
#if STM32_USB_USE_OTG1 == TRUE || STM32_USB_USE_OTG2 == TRUE
    dummy_cb, /* Workaround for OTG Peripherals not servicing new interrupts
    after resuming from suspend. */
#endif
};

void init_usb_driver(USBDriver *usbp) {
    for (int i = 0; i < USB_ENDPOINT_IN_COUNT; i++) {
        usb_endpoint_in_init(&usb_endpoints_in[i]);
        usb_endpoint_in_start(&usb_endpoints_in[i]);
    }

    for (int i = 0; i < USB_ENDPOINT_OUT_COUNT; i++) {
        usb_endpoint_out_init(&usb_endpoints_out[i]);
        usb_endpoint_out_start(&usb_endpoints_out[i]);
    }

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(usbp);
    usbStop(usbp);
    wait_ms(50);
    usbStart(usbp, &usbcfg);
    usbConnectBus(usbp);
}

__attribute__((weak)) void restart_usb_driver(USBDriver *usbp) {
    usbDisconnectBus(usbp);
    usbStop(usbp);

    for (int i = 0; i < USB_ENDPOINT_IN_COUNT; i++) {
        usb_endpoint_in_stop(&usb_endpoints_in[i]);
    }

    for (int i = 0; i < USB_ENDPOINT_OUT_COUNT; i++) {
        usb_endpoint_out_stop(&usb_endpoints_out[i]);
    }

    wait_ms(50);

    for (int i = 0; i < USB_ENDPOINT_IN_COUNT; i++) {
        usb_endpoint_in_init(&usb_endpoints_in[i]);
        usb_endpoint_in_start(&usb_endpoints_in[i]);
    }

    for (int i = 0; i < USB_ENDPOINT_OUT_COUNT; i++) {
        usb_endpoint_out_init(&usb_endpoints_out[i]);
        usb_endpoint_out_start(&usb_endpoints_out[i]);
    }

    usbStart(usbp, &usbcfg);
    usbConnectBus(usbp);
}

/* ---------------------------------------------------------
 *                  Keyboard functions
 * ---------------------------------------------------------
 */

/* LED status */
uint8_t keyboard_leds(void) {
    return keyboard_led_state;
}

/**
 * @brief Send a report to the host, the report is enqueued into an output
 * queue and send once the USB endpoint becomes empty.
 *
 * @param endpoint USB IN endpoint to send the report from
 * @param report pointer to the report
 * @param size size of the report
 * @return true Success
 * @return false Failure
 */
bool send_report(usb_endpoint_in_lut_t endpoint, void *report, size_t size) {
    return usb_endpoint_in_send(&usb_endpoints_in[endpoint], (uint8_t *)report, size, TIME_MS2I(100), false);
}

/**
 * @brief Send a report to the host, but delay the sending until the size of
 * endpoint report is reached or the incompletely filled buffer is flushed with
 * a call to `flush_report_buffered`. This is useful if the report is being
 * updated frequently. The complete report is then enqueued into an output
 * queue and send once the USB endpoint becomes empty.
 *
 * @param endpoint USB IN endpoint to send the report from
 * @param report pointer to the report
 * @param size size of the report
 * @return true Success
 * @return false Failure
 */
static bool send_report_buffered(usb_endpoint_in_lut_t endpoint, void *report, size_t size) {
    return usb_endpoint_in_send(&usb_endpoints_in[endpoint], (uint8_t *)report, size, TIME_MS2I(100), true);
}

/** @brief Flush all buffered reports which were enqueued with a call to
 * `send_report_buffered` that haven't been send. If necessary the buffered
 * report can be padded with zeros up to the endpoints maximum size.
 *
 * @param endpoint USB IN endpoint to flush the reports from
 * @param padded Pad the buffered report with zeros up to the endpoints maximum size
 */
static void flush_report_buffered(usb_endpoint_in_lut_t endpoint, bool padded) {
    usb_endpoint_in_flush(&usb_endpoints_in[endpoint], padded);
}

/**
 * @brief Receive a report from the host.
 *
 * @param endpoint USB OUT endpoint to receive the report from
 * @param report pointer to the report
 * @param size size of the report
 * @return true Success
 * @return false Failure
 */
static bool receive_report(usb_endpoint_out_lut_t endpoint, void *report, size_t size) {
    return usb_endpoint_out_receive(&usb_endpoints_out[endpoint], (uint8_t *)report, size, TIME_IMMEDIATE);
}

void send_keyboard(report_keyboard_t *report) {
    /* If we're in Boot Protocol, don't send any report ID or other funky fields */
    if (!keyboard_protocol) {
        send_report(USB_ENDPOINT_IN_KEYBOARD, &report->mods, 8);
    } else {
        send_report(USB_ENDPOINT_IN_KEYBOARD, report, KEYBOARD_REPORT_SIZE);
    }
}

void send_nkro(report_nkro_t *report) {
#ifdef NKRO_ENABLE
    send_report(USB_ENDPOINT_IN_SHARED, report, sizeof(report_nkro_t));
#endif
}

/* ---------------------------------------------------------
 *                     Mouse functions
 * ---------------------------------------------------------
 */

void send_mouse(report_mouse_t *report) {
#ifdef MOUSE_ENABLE
    send_report(USB_ENDPOINT_IN_MOUSE, report, sizeof(report_mouse_t));
#endif
}

/* ---------------------------------------------------------
 *                   Extrakey functions
 * ---------------------------------------------------------
 */

void send_extra(report_extra_t *report) {
#ifdef EXTRAKEY_ENABLE
    send_report(USB_ENDPOINT_IN_SHARED, report, sizeof(report_extra_t));
#endif
}

void send_programmable_button(report_programmable_button_t *report) {
#ifdef PROGRAMMABLE_BUTTON_ENABLE
    send_report(USB_ENDPOINT_IN_SHARED, report, sizeof(report_programmable_button_t));
#endif
}

void send_joystick(report_joystick_t *report) {
#ifdef JOYSTICK_ENABLE
    send_report(USB_ENDPOINT_IN_JOYSTICK, report, sizeof(report_joystick_t));
#endif
}

void send_digitizer(report_digitizer_t *report) {
#ifdef DIGITIZER_ENABLE
    send_report(USB_ENDPOINT_IN_DIGITIZER, report, sizeof(report_digitizer_t));
#endif
}

/* ---------------------------------------------------------
 *                   Console functions
 * ---------------------------------------------------------
 */

#ifdef CONSOLE_ENABLE

int8_t sendchar(uint8_t c) {
    return (int8_t)send_report_buffered(USB_ENDPOINT_IN_CONSOLE, &c, sizeof(uint8_t));
}

void console_task(void) {
    flush_report_buffered(USB_ENDPOINT_IN_CONSOLE, true);
}

#endif /* CONSOLE_ENABLE */

#ifdef RAW_ENABLE
void raw_hid_send(uint8_t *data, uint8_t length) {
    if (length != RAW_EPSIZE) {
        return;
    }
    send_report(USB_ENDPOINT_IN_RAW, data, length);
}

__attribute__((weak)) void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Users should #include "raw_hid.h" in their own code
    // and implement this function there. Leave this as weak linkage
    // so users can opt to not handle data coming in.
}

void raw_hid_task(void) {
    uint8_t buffer[RAW_EPSIZE];
    while (receive_report(USB_ENDPOINT_OUT_RAW, buffer, sizeof(buffer))) {
        raw_hid_receive(buffer, sizeof(buffer));
    }
}

#endif

#ifdef MIDI_ENABLE

void send_midi_packet(MIDI_EventPacket_t *event) {
    send_report(USB_ENDPOINT_IN_MIDI, (uint8_t *)event, sizeof(MIDI_EventPacket_t));
}

bool recv_midi_packet(MIDI_EventPacket_t *const event) {
    return receive_report(USB_ENDPOINT_OUT_MIDI, (uint8_t *)event, sizeof(MIDI_EventPacket_t));
}

void midi_ep_task(void) {
    uint8_t buffer[MIDI_STREAM_EPSIZE];
    while (receive_report(USB_ENDPOINT_OUT_MIDI, buffer, sizeof(buffer))) {
        MIDI_EventPacket_t event;
        // TODO: this seems totally wrong? The midi task will never see any
        // packets if we consume them here
        recv_midi_packet(&event);
    }
}
#endif

#ifdef VIRTSER_ENABLE

#    include "hal_usb_cdc.h"
/**
 * @brief CDC serial driver configuration structure. Set to 9600 baud, 1 stop bit, no parity, 8 data bits.
 */
static cdc_linecoding_t linecoding = {{0x00, 0x96, 0x00, 0x00}, LC_STOP_1, LC_PARITY_NONE, 8};

bool virtser_usb_request_cb(USBDriver *usbp) {
    if ((usbp->setup[0] & USB_RTYPE_TYPE_MASK) == USB_RTYPE_TYPE_CLASS) { /* bmRequestType */
        if (usbp->setup[4] == CCI_INTERFACE) {                            /* wIndex (LSB) */
            switch (usbp->setup[1]) {                                     /* bRequest */
                case CDC_GET_LINE_CODING:
                    usbSetupTransfer(usbp, (uint8_t *)&linecoding, sizeof(linecoding), NULL);
                    return true;
                case CDC_SET_LINE_CODING:
                    usbSetupTransfer(usbp, (uint8_t *)&linecoding, sizeof(linecoding), NULL);
                    return true;
                case CDC_SET_CONTROL_LINE_STATE:
                    /* Nothing to do, there are no control lines.*/
                    usbSetupTransfer(usbp, NULL, 0, NULL);
                    return true;
                default:
                    return false;
            }
        }
    }

    return false;
}

void virtser_init(void) {}

void virtser_send(const uint8_t byte) {
    send_report_buffered(USB_ENDPOINT_IN_CDC_DATA, (void *)&byte, sizeof(byte));
}

__attribute__((weak)) void virtser_recv(uint8_t c) {
    // Ignore by default
}

void virtser_task(void) {
    uint8_t buffer[CDC_EPSIZE];
    while (receive_report(USB_ENDPOINT_OUT_CDC_DATA, buffer, sizeof(buffer))) {
        for (int i = 0; i < sizeof(buffer); i++) {
            virtser_recv(buffer[i]);
        }
    }

    flush_report_buffered(USB_ENDPOINT_IN_CDC_DATA, false);
}

#endif
