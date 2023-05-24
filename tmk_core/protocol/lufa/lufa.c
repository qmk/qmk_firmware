/*
 * Copyright 2012 Jun Wako <wakojun@gmail.com>
 * This file is based on:
 *     LUFA-120219/Demos/Device/Lowlevel/KeyboardMouse
 *     LUFA-120219/Demos/Device/Lowlevel/GenericHID
 */

/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "report.h"
#include "host.h"
#include "host_driver.h"
#include "keyboard.h"
#include "action.h"
#include "led.h"
#include "sendchar.h"
#include "debug.h"
#ifdef SLEEP_LED_ENABLE
#    include "sleep_led.h"
#endif
#include "suspend.h"

#include "usb_descriptor.h"
#include "lufa.h"
#include "quantum.h"
#include "usb_device_state.h"
#include <util/atomic.h>

#ifdef NKRO_ENABLE
#    include "keycode_config.h"

extern keymap_config_t keymap_config;
#endif

#ifdef AUDIO_ENABLE
#    include "audio.h"
#endif

#ifdef BLUETOOTH_ENABLE
#    include "outputselect.h"
#    ifdef BLUETOOTH_BLUEFRUIT_LE
#        include "bluefruit_le.h"
#    elif BLUETOOTH_RN42
#        include "rn42.h"
#    endif
#endif

#ifdef VIRTSER_ENABLE
#    include "virtser.h"
#endif

#ifdef MIDI_ENABLE
#    include "qmk_midi.h"
#endif

#ifdef RAW_ENABLE
#    include "raw_hid.h"
#endif

#ifdef JOYSTICK_ENABLE
#    include "joystick.h"
#endif

uint8_t keyboard_idle = 0;
/* 0: Boot Protocol, 1: Report Protocol(default) */
uint8_t        keyboard_protocol  = 1;
static uint8_t keyboard_led_state = 0;

static report_keyboard_t keyboard_report_sent;

/* Host driver */
static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);
static void    send_programmable_button(uint32_t data);
host_driver_t  lufa_driver = {keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer, send_programmable_button};

#ifdef VIRTSER_ENABLE
// clang-format off

USB_ClassInfo_CDC_Device_t cdc_device = {
    .Config = {
        .ControlInterfaceNumber = CCI_INTERFACE,
        .DataINEndpoint = {
            .Address            = (CDC_IN_EPNUM | ENDPOINT_DIR_IN),
            .Size               = CDC_EPSIZE,
            .Banks              = 1
        },
        .DataOUTEndpoint = {
            .Address            = (CDC_OUT_EPNUM | ENDPOINT_DIR_OUT),
            .Size               = CDC_EPSIZE,
            .Banks              = 1
        },
        .NotificationEndpoint = {
            .Address            = (CDC_NOTIFICATION_EPNUM | ENDPOINT_DIR_IN),
            .Size               = CDC_NOTIFICATION_EPSIZE,
            .Banks              = 1
        }
    }
};

// clang-format on
#endif

#ifdef RAW_ENABLE

/** \brief Raw HID Send
 *
 * FIXME: Needs doc
 */
void raw_hid_send(uint8_t *data, uint8_t length) {
    // TODO: implement variable size packet
    if (length != RAW_EPSIZE) {
        return;
    }

    if (USB_DeviceState != DEVICE_STATE_Configured) {
        return;
    }

    // TODO: decide if we allow calls to raw_hid_send() in the middle
    // of other endpoint usage.
    uint8_t ep = Endpoint_GetCurrentEndpoint();

    Endpoint_SelectEndpoint(RAW_IN_EPNUM);

    // Check to see if the host is ready to accept another packet
    if (Endpoint_IsINReady()) {
        // Write data
        Endpoint_Write_Stream_LE(data, RAW_EPSIZE, NULL);
        // Finalize the stream transfer to send the last packet
        Endpoint_ClearIN();
    }

    Endpoint_SelectEndpoint(ep);
}

/** \brief Raw HID Receive
 *
 * FIXME: Needs doc
 */
__attribute__((weak)) void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Users should #include "raw_hid.h" in their own code
    // and implement this function there. Leave this as weak linkage
    // so users can opt to not handle data coming in.
}

/** \brief Raw HID Task
 *
 * FIXME: Needs doc
 */
static void raw_hid_task(void) {
    // Create a temporary buffer to hold the read in data from the host
    uint8_t data[RAW_EPSIZE];
    bool    data_read = false;

    // Device must be connected and configured for the task to run
    if (USB_DeviceState != DEVICE_STATE_Configured) return;

    Endpoint_SelectEndpoint(RAW_OUT_EPNUM);

    // Check to see if a packet has been sent from the host
    if (Endpoint_IsOUTReceived()) {
        // Check to see if the packet contains data
        if (Endpoint_IsReadWriteAllowed()) {
            /* Read data */
            Endpoint_Read_Stream_LE(data, sizeof(data), NULL);
            data_read = true;
        }

        // Finalize the stream transfer to receive the last packet
        Endpoint_ClearOUT();

        if (data_read) {
            raw_hid_receive(data, sizeof(data));
        }
    }
}
#endif

/*******************************************************************************
 * Console
 ******************************************************************************/
#ifdef CONSOLE_ENABLE
/** \brief Console Task
 *
 * FIXME: Needs doc
 */
static void Console_Task(void) {
    /* Device must be connected and configured for the task to run */
    if (USB_DeviceState != DEVICE_STATE_Configured) return;

    uint8_t ep = Endpoint_GetCurrentEndpoint();

#    if 0
    // TODO: impl receivechar()/recvchar()
    Endpoint_SelectEndpoint(CONSOLE_OUT_EPNUM);

    /* Check to see if a packet has been sent from the host */
    if (Endpoint_IsOUTReceived())
    {
        /* Check to see if the packet contains data */
        if (Endpoint_IsReadWriteAllowed())
        {
            /* Create a temporary buffer to hold the read in report from the host */
            uint8_t ConsoleData[CONSOLE_EPSIZE];

            /* Read Console Report Data */
            Endpoint_Read_Stream_LE(&ConsoleData, sizeof(ConsoleData), NULL);

            /* Process Console Report Data */
            //ProcessConsoleHIDReport(ConsoleData);
        }

        /* Finalize the stream transfer to send the last packet */
        Endpoint_ClearOUT();
    }
#    endif

    /* IN packet */
    Endpoint_SelectEndpoint(CONSOLE_IN_EPNUM);
    if (!Endpoint_IsEnabled() || !Endpoint_IsConfigured()) {
        Endpoint_SelectEndpoint(ep);
        return;
    }

    // fill empty bank
    while (Endpoint_IsReadWriteAllowed())
        Endpoint_Write_8(0);

    // flush sendchar packet
    if (Endpoint_IsINReady()) {
        Endpoint_ClearIN();
    }

    Endpoint_SelectEndpoint(ep);
}
#endif

/*******************************************************************************
 * Joystick
 ******************************************************************************/
#ifdef JOYSTICK_ENABLE
void send_joystick_packet(joystick_t *joystick) {
    uint8_t timeout = 255;

    static joystick_report_t r;
    r = (joystick_report_t) {
#    if JOYSTICK_AXES_COUNT > 0
        .axes =
        { joystick->axes[0],

#        if JOYSTICK_AXES_COUNT >= 2
          joystick->axes[1],
#        endif
#        if JOYSTICK_AXES_COUNT >= 3
          joystick->axes[2],
#        endif
#        if JOYSTICK_AXES_COUNT >= 4
          joystick->axes[3],
#        endif
#        if JOYSTICK_AXES_COUNT >= 5
          joystick->axes[4],
#        endif
#        if JOYSTICK_AXES_COUNT >= 6
          joystick->axes[5],
#        endif
        },
#    endif // JOYSTICK_AXES_COUNT>0

#    if JOYSTICK_BUTTON_COUNT > 0
        .buttons = {
            joystick->buttons[0],

#        if JOYSTICK_BUTTON_COUNT > 8
            joystick->buttons[1],
#        endif
#        if JOYSTICK_BUTTON_COUNT > 16
            joystick->buttons[2],
#        endif
#        if JOYSTICK_BUTTON_COUNT > 24
            joystick->buttons[3],
#        endif
        }
#    endif // JOYSTICK_BUTTON_COUNT>0
    };

    /* Select the Joystick Report Endpoint */
    Endpoint_SelectEndpoint(JOYSTICK_IN_EPNUM);

    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed())
        _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    /* Write Joystick Report Data */
    Endpoint_Write_Stream_LE(&r, sizeof(joystick_report_t), NULL);

    /* Finalize the stream transfer to send the last packet */
    Endpoint_ClearIN();
}
#endif

/*******************************************************************************
 * USB Events
 ******************************************************************************/
/*
 * Event Order of Plug in:
 * 0) EVENT_USB_Device_Connect
 * 1) EVENT_USB_Device_Suspend
 * 2) EVENT_USB_Device_Reset
 * 3) EVENT_USB_Device_Wake
 */
/** \brief Event USB Device Connect
 *
 * FIXME: Needs doc
 */
void EVENT_USB_Device_Connect(void) {
    print("[C]");
    /* For battery powered device */
    if (!USB_IsInitialized) {
        USB_Disable();
        USB_Init();
        USB_Device_EnableSOFEvents();
    }
}

/** \brief Event USB Device Connect
 *
 * FIXME: Needs doc
 */
void EVENT_USB_Device_Disconnect(void) {
    print("[D]");
    /* For battery powered device */
    USB_IsInitialized = false;
    /* TODO: This doesn't work. After several plug in/outs can not be enumerated.
        if (USB_IsInitialized) {
            USB_Disable();  // Disable all interrupts
        USB_Controller_Enable();
            USB_INT_Enable(USB_INT_VBUSTI);
        }
    */
}

/** \brief Event USB Device Connect
 *
 * FIXME: Needs doc
 */
void EVENT_USB_Device_Reset(void) {
    print("[R]");
    usb_device_state_set_reset();
}

/** \brief Event USB Device Connect
 *
 * FIXME: Needs doc
 */
void EVENT_USB_Device_Suspend() {
    print("[S]");
    usb_device_state_set_suspend(USB_Device_ConfigurationNumber != 0, USB_Device_ConfigurationNumber);

#ifdef SLEEP_LED_ENABLE
    sleep_led_enable();
#endif
}

/** \brief Event USB Device Connect
 *
 * FIXME: Needs doc
 */
void EVENT_USB_Device_WakeUp() {
    print("[W]");
#if defined(NO_USB_STARTUP_CHECK)
    suspend_wakeup_init();
#endif

    usb_device_state_set_resume(USB_DeviceState == DEVICE_STATE_Configured, USB_Device_ConfigurationNumber);

#ifdef SLEEP_LED_ENABLE
    sleep_led_disable();
    // NOTE: converters may not accept this
    led_set(host_keyboard_leds());
#endif
}

#ifdef CONSOLE_ENABLE
static bool console_flush = false;
#    define CONSOLE_FLUSH_SET(b)                \
        do {                                    \
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { \
                console_flush = b;              \
            }                                   \
        } while (0)

/** \brief Event USB Device Start Of Frame
 *
 * FIXME: Needs doc
 * called every 1ms
 */
void EVENT_USB_Device_StartOfFrame(void) {
    static uint8_t count;
    if (++count % 50) return;
    count = 0;

    if (!console_flush) return;
    Console_Task();
    console_flush = false;
}

#endif

/** \brief Event handler for the USB_ConfigurationChanged event.
 *
 * This is fired when the host sets the current configuration of the USB device after enumeration.
 *
 * ATMega32u2 supports dual bank(ping-pong mode) only on endpoint 3 and 4,
 * it is safe to use single bank for all endpoints.
 */
void EVENT_USB_Device_ConfigurationChanged(void) {
    bool ConfigSuccess = true;

#ifndef KEYBOARD_SHARED_EP
    /* Setup keyboard report endpoint */
    ConfigSuccess &= Endpoint_ConfigureEndpoint((KEYBOARD_IN_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_INTERRUPT, KEYBOARD_EPSIZE, 1);
#endif

#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
    /* Setup mouse report endpoint */
    ConfigSuccess &= Endpoint_ConfigureEndpoint((MOUSE_IN_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_INTERRUPT, MOUSE_EPSIZE, 1);
#endif

#ifdef SHARED_EP_ENABLE
    /* Setup shared report endpoint */
    ConfigSuccess &= Endpoint_ConfigureEndpoint((SHARED_IN_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_INTERRUPT, SHARED_EPSIZE, 1);
#endif

#ifdef RAW_ENABLE
    /* Setup raw HID endpoints */
    ConfigSuccess &= Endpoint_ConfigureEndpoint((RAW_IN_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_INTERRUPT, RAW_EPSIZE, 1);
    ConfigSuccess &= Endpoint_ConfigureEndpoint((RAW_OUT_EPNUM | ENDPOINT_DIR_OUT), EP_TYPE_INTERRUPT, RAW_EPSIZE, 1);
#endif

#ifdef CONSOLE_ENABLE
    /* Setup console endpoint */
    ConfigSuccess &= Endpoint_ConfigureEndpoint((CONSOLE_IN_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_INTERRUPT, CONSOLE_EPSIZE, 1);
#    if 0
    ConfigSuccess &= Endpoint_ConfigureEndpoint((CONSOLE_OUT_EPNUM | ENDPOINT_DIR_OUT), EP_TYPE_INTERRUPT, CONSOLE_EPSIZE, 1);
#    endif
#endif

#ifdef MIDI_ENABLE
    /* Setup MIDI stream endpoints */
    ConfigSuccess &= Endpoint_ConfigureEndpoint((MIDI_STREAM_IN_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_BULK, MIDI_STREAM_EPSIZE, 1);
    ConfigSuccess &= Endpoint_ConfigureEndpoint((MIDI_STREAM_OUT_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_BULK, MIDI_STREAM_EPSIZE, 1);
#endif

#ifdef VIRTSER_ENABLE
    /* Setup virtual serial endpoints */
    ConfigSuccess &= Endpoint_ConfigureEndpoint((CDC_NOTIFICATION_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_INTERRUPT, CDC_NOTIFICATION_EPSIZE, 1);
    ConfigSuccess &= Endpoint_ConfigureEndpoint((CDC_OUT_EPNUM | ENDPOINT_DIR_OUT), EP_TYPE_BULK, CDC_EPSIZE, 1);
    ConfigSuccess &= Endpoint_ConfigureEndpoint((CDC_IN_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_BULK, CDC_EPSIZE, 1);
#endif

#ifdef JOYSTICK_ENABLE
    /* Setup joystick endpoint */
    ConfigSuccess &= Endpoint_ConfigureEndpoint((JOYSTICK_IN_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
#endif

#if defined(DIGITIZER_ENABLE) && !defined(DIGITIZER_SHARED_EP)
    /* Setup digitizer endpoint */
    ConfigSuccess &= Endpoint_ConfigureEndpoint((DIGITIZER_IN_EPNUM | ENDPOINT_DIR_IN), EP_TYPE_INTERRUPT, DIGITIZER_EPSIZE, 1);
#endif

    usb_device_state_set_configuration(USB_DeviceState == DEVICE_STATE_Configured, USB_Device_ConfigurationNumber);
}

/* FIXME: Expose this table in the docs somehow
Appendix G: HID Request Support Requirements

The following table enumerates the requests that need to be supported by various types of HID class devices.

Device type     GetReport   SetReport   GetIdle     SetIdle     GetProtocol SetProtocol
------------------------------------------------------------------------------------------
Boot Mouse      Required    Optional    Optional    Optional    Required    Required
Non-Boot Mouse  Required    Optional    Optional    Optional    Optional    Optional
Boot Keyboard   Required    Optional    Required    Required    Required    Required
Non-Boot Keybrd Required    Optional    Required    Required    Optional    Optional
Other Device    Required    Optional    Optional    Optional    Optional    Optional
*/
/** \brief Event handler for the USB_ControlRequest event.
 *
 *  This is fired before passing along unhandled control requests to the library for processing internally.
 */
void EVENT_USB_Device_ControlRequest(void) {
    uint8_t *ReportData = NULL;
    uint8_t  ReportSize = 0;

    /* Handle HID Class specific requests */
    switch (USB_ControlRequest.bRequest) {
        case HID_REQ_GetReport:
            if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE)) {
                Endpoint_ClearSETUP();

                // Interface
                switch (USB_ControlRequest.wIndex) {
                    case KEYBOARD_INTERFACE:
                        // TODO: test/check
                        ReportData = (uint8_t *)&keyboard_report_sent;
                        ReportSize = sizeof(keyboard_report_sent);
                        break;
                }

                /* Write the report data to the control endpoint */
                Endpoint_Write_Control_Stream_LE(ReportData, ReportSize);
                Endpoint_ClearOUT();
            }

            break;
        case HID_REQ_SetReport:
            if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE)) {
                // Interface
                switch (USB_ControlRequest.wIndex) {
                    case KEYBOARD_INTERFACE:
#if defined(SHARED_EP_ENABLE) && !defined(KEYBOARD_SHARED_EP)
                    case SHARED_INTERFACE:
#endif
                        Endpoint_ClearSETUP();

                        while (!(Endpoint_IsOUTReceived())) {
                            if (USB_DeviceState == DEVICE_STATE_Unattached) return;
                        }

                        if (Endpoint_BytesInEndpoint() == 2) {
                            uint8_t report_id = Endpoint_Read_8();

                            if (report_id == REPORT_ID_KEYBOARD || report_id == REPORT_ID_NKRO) {
                                keyboard_led_state = Endpoint_Read_8();
                            }
                        } else {
                            keyboard_led_state = Endpoint_Read_8();
                        }

                        Endpoint_ClearOUT();
                        Endpoint_ClearStatusStage();
                        break;
                }
            }

            break;

        case HID_REQ_GetProtocol:
            if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE)) {
                if (USB_ControlRequest.wIndex == KEYBOARD_INTERFACE) {
                    Endpoint_ClearSETUP();
                    while (!(Endpoint_IsINReady()))
                        ;
                    Endpoint_Write_8(keyboard_protocol);
                    Endpoint_ClearIN();
                    Endpoint_ClearStatusStage();
                }
            }

            break;
        case HID_REQ_SetProtocol:
            if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE)) {
                if (USB_ControlRequest.wIndex == KEYBOARD_INTERFACE) {
                    Endpoint_ClearSETUP();
                    Endpoint_ClearStatusStage();

                    keyboard_protocol = (USB_ControlRequest.wValue & 0xFF);
                    clear_keyboard();
                }
            }

            break;
        case HID_REQ_SetIdle:
            if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE)) {
                Endpoint_ClearSETUP();
                Endpoint_ClearStatusStage();

                keyboard_idle = ((USB_ControlRequest.wValue & 0xFF00) >> 8);
            }

            break;
        case HID_REQ_GetIdle:
            if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE)) {
                Endpoint_ClearSETUP();
                while (!(Endpoint_IsINReady()))
                    ;
                Endpoint_Write_8(keyboard_idle);
                Endpoint_ClearIN();
                Endpoint_ClearStatusStage();
            }

            break;
    }

#ifdef VIRTSER_ENABLE
    CDC_Device_ProcessControlRequest(&cdc_device);
#endif
}

/*******************************************************************************
 * Host driver
 ******************************************************************************/
/** \brief Keyboard LEDs
 *
 * FIXME: Needs doc
 */
static uint8_t keyboard_leds(void) {
    return keyboard_led_state;
}

/** \brief Send Keyboard
 *
 * FIXME: Needs doc
 */
static void send_keyboard(report_keyboard_t *report) {
    uint8_t timeout = 255;

#ifdef BLUETOOTH_ENABLE
    if (where_to_send() == OUTPUT_BLUETOOTH) {
#    ifdef BLUETOOTH_BLUEFRUIT_LE
        bluefruit_le_send_keys(report->mods, report->keys, sizeof(report->keys));
#    elif BLUETOOTH_RN42
        rn42_send_keyboard(report);
#    endif
        return;
    }
#endif

    /* Select the Keyboard Report Endpoint */
    uint8_t ep   = KEYBOARD_IN_EPNUM;
    uint8_t size = KEYBOARD_REPORT_SIZE;
#ifdef NKRO_ENABLE
    if (keyboard_protocol && keymap_config.nkro) {
        ep   = SHARED_IN_EPNUM;
        size = sizeof(struct nkro_report);
    }
#endif
    Endpoint_SelectEndpoint(ep);
    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed())
        _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    /* If we're in Boot Protocol, don't send any report ID or other funky fields */
    if (!keyboard_protocol) {
        Endpoint_Write_Stream_LE(&report->mods, 8, NULL);
    } else {
        Endpoint_Write_Stream_LE(report, size, NULL);
    }

    /* Finalize the stream transfer to send the last packet */
    Endpoint_ClearIN();

    keyboard_report_sent = *report;
}

/** \brief Send Mouse
 *
 * FIXME: Needs doc
 */
static void send_mouse(report_mouse_t *report) {
#ifdef MOUSE_ENABLE
    uint8_t timeout = 255;

#    ifdef BLUETOOTH_ENABLE
    if (where_to_send() == OUTPUT_BLUETOOTH) {
#        ifdef BLUETOOTH_BLUEFRUIT_LE
        // FIXME: mouse buttons
        bluefruit_le_send_mouse_move(report->x, report->y, report->v, report->h, report->buttons);
#        elif BLUETOOTH_RN42
        rn42_send_mouse(report);
#        endif
        return;
    }
#    endif

    /* Select the Mouse Report Endpoint */
    Endpoint_SelectEndpoint(MOUSE_IN_EPNUM);

    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed())
        _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    /* Write Mouse Report Data */
    Endpoint_Write_Stream_LE(report, sizeof(report_mouse_t), NULL);

    /* Finalize the stream transfer to send the last packet */
    Endpoint_ClearIN();
#endif
}

#if defined(EXTRAKEY_ENABLE) || defined(PROGRAMMABLE_BUTTON_ENABLE)
static void send_report(void *report, size_t size) {
    uint8_t timeout = 255;

    if (USB_DeviceState != DEVICE_STATE_Configured) return;

    Endpoint_SelectEndpoint(SHARED_IN_EPNUM);

    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed())
        _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    Endpoint_Write_Stream_LE(report, size, NULL);
    Endpoint_ClearIN();
}
#endif

/** \brief Send Extra
 *
 * FIXME: Needs doc
 */
#ifdef EXTRAKEY_ENABLE
static void send_extra(uint8_t report_id, uint16_t data) {
    static report_extra_t r;
    r = (report_extra_t){.report_id = report_id, .usage = data};
    send_report(&r, sizeof(r));
}
#endif

/** \brief Send System
 *
 * FIXME: Needs doc
 */
static void send_system(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    send_extra(REPORT_ID_SYSTEM, data);
#endif
}

/** \brief Send Consumer
 *
 * FIXME: Needs doc
 */
static void send_consumer(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
#    ifdef BLUETOOTH_ENABLE
    if (where_to_send() == OUTPUT_BLUETOOTH) {
#        ifdef BLUETOOTH_BLUEFRUIT_LE
        bluefruit_le_send_consumer_key(data);
#        elif BLUETOOTH_RN42
        rn42_send_consumer(data);
#        endif
        return;
    }
#    endif

    send_extra(REPORT_ID_CONSUMER, data);
#endif
}

static void send_programmable_button(uint32_t data) {
#ifdef PROGRAMMABLE_BUTTON_ENABLE
    static report_programmable_button_t r;
    r = (report_programmable_button_t){.report_id = REPORT_ID_PROGRAMMABLE_BUTTON, .usage = data};
    send_report(&r, sizeof(r));
#endif
}

/*******************************************************************************
 * sendchar
 ******************************************************************************/
#ifdef CONSOLE_ENABLE
#    define SEND_TIMEOUT 5
/** \brief Send Char
 *
 * FIXME: Needs doc
 */
int8_t sendchar(uint8_t c) {
    // Do not wait if the previous write has timed_out.
    // Because sendchar() is called so many times, waiting each call causes big lag.
    // The `timed_out` state is an approximation of the ideal `is_listener_disconnected?` state.
    static bool timed_out = false;

    // prevents Console_Task() from running during sendchar() runs.
    // or char will be lost. These two function is mutually exclusive.
    CONSOLE_FLUSH_SET(false);

    if (USB_DeviceState != DEVICE_STATE_Configured) return -1;

    uint8_t ep = Endpoint_GetCurrentEndpoint();
    Endpoint_SelectEndpoint(CONSOLE_IN_EPNUM);
    if (!Endpoint_IsEnabled() || !Endpoint_IsConfigured()) {
        goto ERROR_EXIT;
    }

    if (timed_out && !Endpoint_IsReadWriteAllowed()) {
        goto ERROR_EXIT;
    }

    timed_out = false;

    uint8_t timeout = SEND_TIMEOUT;
    while (!Endpoint_IsReadWriteAllowed()) {
        if (USB_DeviceState != DEVICE_STATE_Configured) {
            goto ERROR_EXIT;
        }
        if (Endpoint_IsStalled()) {
            goto ERROR_EXIT;
        }
        if (!(timeout--)) {
            timed_out = true;
            goto ERROR_EXIT;
        }
        _delay_ms(1);
    }

    Endpoint_Write_8(c);

    // send when bank is full
    if (!Endpoint_IsReadWriteAllowed()) {
        while (!(Endpoint_IsINReady()))
            ;
        Endpoint_ClearIN();
    } else {
        CONSOLE_FLUSH_SET(true);
    }

    Endpoint_SelectEndpoint(ep);
    return 0;
ERROR_EXIT:
    Endpoint_SelectEndpoint(ep);
    return -1;
}
#endif

/*******************************************************************************
 * MIDI
 ******************************************************************************/

#ifdef MIDI_ENABLE
// clang-format off

USB_ClassInfo_MIDI_Device_t USB_MIDI_Interface = {
    .Config = {
        .StreamingInterfaceNumber = AS_INTERFACE,
        .DataINEndpoint = {
            .Address              = (MIDI_STREAM_IN_EPNUM | ENDPOINT_DIR_IN),
            .Size                 = MIDI_STREAM_EPSIZE,
            .Banks                = 1
        },
        .DataOUTEndpoint = {
            .Address              = (MIDI_STREAM_OUT_EPNUM | ENDPOINT_DIR_OUT),
            .Size                 = MIDI_STREAM_EPSIZE,
            .Banks                = 1
        }
    }
};

// clang-format on

void send_midi_packet(MIDI_EventPacket_t *event) {
    MIDI_Device_SendEventPacket(&USB_MIDI_Interface, event);
}

bool recv_midi_packet(MIDI_EventPacket_t *const event) {
    return MIDI_Device_ReceiveEventPacket(&USB_MIDI_Interface, event);
}

#endif

/*******************************************************************************
 * VIRTUAL SERIAL
 ******************************************************************************/

#ifdef VIRTSER_ENABLE
/** \brief Virtual Serial Init
 *
 * FIXME: Needs doc
 */
void virtser_init(void) {
    cdc_device.State.ControlLineStates.DeviceToHost = CDC_CONTROL_LINE_IN_DSR;
    CDC_Device_SendControlLineStateChange(&cdc_device);
}

/** \brief Virtual Serial Receive
 *
 * FIXME: Needs doc
 */
void virtser_recv(uint8_t c) __attribute__((weak));
void virtser_recv(uint8_t c) {
    // Ignore by default
}

/** \brief Virtual Serial Task
 *
 * FIXME: Needs doc
 */
void virtser_task(void) {
    uint16_t count = CDC_Device_BytesReceived(&cdc_device);
    uint8_t  ch;
    for (; count; --count) {
        ch = CDC_Device_ReceiveByte(&cdc_device);
        virtser_recv(ch);
    }
}
/** \brief Virtual Serial Send
 *
 * FIXME: Needs doc
 */
void virtser_send(const uint8_t byte) {
    uint8_t timeout = 255;
    uint8_t ep      = Endpoint_GetCurrentEndpoint();

    if (cdc_device.State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR) {
        /* IN packet */
        Endpoint_SelectEndpoint(cdc_device.Config.DataINEndpoint.Address);

        if (!Endpoint_IsEnabled() || !Endpoint_IsConfigured()) {
            Endpoint_SelectEndpoint(ep);
            return;
        }

        while (timeout-- && !Endpoint_IsReadWriteAllowed())
            _delay_us(40);

        Endpoint_Write_8(byte);
        CDC_Device_Flush(&cdc_device);

        if (Endpoint_IsINReady()) {
            Endpoint_ClearIN();
        }

        Endpoint_SelectEndpoint(ep);
    }
}
#endif

void send_digitizer(report_digitizer_t *report) {
#ifdef DIGITIZER_ENABLE
    uint8_t timeout = 255;

    if (USB_DeviceState != DEVICE_STATE_Configured) return;

    Endpoint_SelectEndpoint(DIGITIZER_IN_EPNUM);

    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed())
        _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    Endpoint_Write_Stream_LE(report, sizeof(report_digitizer_t), NULL);
    Endpoint_ClearIN();
#endif
}

/*******************************************************************************
 * main
 ******************************************************************************/
/** \brief Setup MCU
 *
 * FIXME: Needs doc
 */
static void setup_mcu(void) {
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~_BV(WDRF);
    wdt_disable();

// For boards running at 3.3V and crystal at 16 MHz
#if (F_CPU == 8000000 && F_USB == 16000000)
    /* Divide clock by 2 */
    clock_prescale_set(clock_div_2);
#else /* Disable clock division */
    clock_prescale_set(clock_div_1);
#endif
}

/** \brief Setup USB
 *
 * FIXME: Needs doc
 */
static void setup_usb(void) {
    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
}

void protocol_setup(void) {
#ifdef MIDI_ENABLE
    setup_midi();
#endif

    setup_mcu();
    usb_device_state_init();
}

void protocol_pre_init(void) {
    setup_usb();
    sei();

#if defined(BLUETOOTH_RN42)
    rn42_init();
#endif

    /* wait for USB startup & debug output */

#ifdef WAIT_FOR_USB
    while (USB_DeviceState != DEVICE_STATE_Configured) {
#    if defined(INTERRUPT_CONTROL_ENDPOINT)
        ;
#    else
        USB_USBTask();
#    endif
    }
    print("USB configured.\n");
#else
    USB_USBTask();
#endif
}

void protocol_post_init(void) {
    host_set_driver(&lufa_driver);
}

void protocol_pre_task(void) {
#if !defined(NO_USB_STARTUP_CHECK)
    if (USB_DeviceState == DEVICE_STATE_Suspended) {
        print("[s]");
        while (USB_DeviceState == DEVICE_STATE_Suspended) {
            suspend_power_down();
            if (USB_Device_RemoteWakeupEnabled && suspend_wakeup_condition()) {
                USB_Device_SendRemoteWakeup();
                clear_keyboard();

#    if USB_SUSPEND_WAKEUP_DELAY > 0
                // Some hubs, kvm switches, and monitors do
                // weird things, with USB device state bouncing
                // around wildly on wakeup, yielding race
                // conditions that can corrupt the keyboard state.
                //
                // Pause for a while to let things settle...
                wait_ms(USB_SUSPEND_WAKEUP_DELAY);
#    endif
            }
        }
        suspend_wakeup_init();
    }
#endif
}

void protocol_post_task(void) {
#ifdef MIDI_ENABLE
    MIDI_Device_USBTask(&USB_MIDI_Interface);
#endif

#ifdef BLUETOOTH_BLUEFRUIT_LE
    bluefruit_le_task();
#endif

#ifdef VIRTSER_ENABLE
    virtser_task();
    CDC_Device_USBTask(&cdc_device);
#endif

#ifdef RAW_ENABLE
    raw_hid_task();
#endif

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
    USB_USBTask();
#endif
}

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint16_t wIndex, const void **const DescriptorAddress) {
    return get_usb_descriptor(wValue, wIndex, DescriptorAddress);
}
