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
#include "sendchar.h"
#include "debug.h"

#include "descriptor.h"
#include "lufa.h"

static uint8_t idle_duration = 0;
static uint8_t protocol_report = 1;
static uint8_t keyboard_led_stats = 0;

static report_keyboard_t keyboard_report_sent;


/* Host driver */
static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);
static host_driver_t lufa_driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer
};


static void SetupHardware(void);
static void Console_Task(void);

int main(void)
{
    SetupHardware();
    sei();

    print_enable = true;
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
    debug_mouse = true;

    // TODO: can't print here
    debug("LUFA init\n");

    keyboard_init();
    host_set_driver(&lufa_driver);
    while (1) {
        keyboard_proc();

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        USB_USBTask();
#endif
    }
}

void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
}

static void Console_Task(void)
{
    /* Device must be connected and configured for the task to run */
    if (USB_DeviceState != DEVICE_STATE_Configured)
      return;

    uint8_t ep = Endpoint_GetCurrentEndpoint();

#if 0
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
#endif

    /* IN packet */
    Endpoint_SelectEndpoint(CONSOLE_IN_EPNUM);
    // flash senchar packet
    if (Endpoint_IsINReady()) {
        Endpoint_ClearIN();
    }

    Endpoint_SelectEndpoint(ep);
}


/*******************************************************************************
 * USB Events
 ******************************************************************************/
/** Event handler for the USB_Connect event. */
void EVENT_USB_Device_Connect(void)
{
}

/** Event handler for the USB_Disconnect event. */
void EVENT_USB_Device_Disconnect(void)
{
}

#define CONSOLE_TASK_INTERVAL 50
void EVENT_USB_Device_StartOfFrame(void)
{
    static uint8_t interval;
    if (++interval == CONSOLE_TASK_INTERVAL) {
        Console_Task();
        interval = 0;
    }
}

/** Event handler for the USB_ConfigurationChanged event.
 * This is fired when the host sets the current configuration of the USB device after enumeration.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    /* Setup Keyboard HID Report Endpoints */
    ConfigSuccess &= Endpoint_ConfigureEndpoint(KEYBOARD_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                                KEYBOARD_EPSIZE, ENDPOINT_BANK_SINGLE);

#ifdef MOUSE_ENABLE
    /* Setup Mouse HID Report Endpoint */
    ConfigSuccess &= Endpoint_ConfigureEndpoint(MOUSE_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                                MOUSE_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#ifdef EXTRAKEY_ENABLE
    /* Setup Extra HID Report Endpoint */
    ConfigSuccess &= Endpoint_ConfigureEndpoint(EXTRA_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                                EXTRA_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

    /* Setup Console HID Report Endpoints */
    ConfigSuccess &= Endpoint_ConfigureEndpoint(CONSOLE_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                                CONSOLE_EPSIZE, ENDPOINT_BANK_DOUBLE);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(CONSOLE_OUT_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_OUT,
                                                CONSOLE_EPSIZE, ENDPOINT_BANK_SINGLE);
}

/*
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
/** Event handler for the USB_ControlRequest event.
 *  This is fired before passing along unhandled control requests to the library for processing internally.
 */
void EVENT_USB_Device_ControlRequest(void)
{
    uint8_t* ReportData = NULL;
    uint8_t  ReportSize = 0;

    /* Handle HID Class specific requests */
    switch (USB_ControlRequest.bRequest)
    {
        case HID_REQ_GetReport:
            if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
            {
                Endpoint_ClearSETUP();

                // Interface
                switch (USB_ControlRequest.wIndex) {
                case KEYBOARD_INTERFACE:
                    // TODO: test/check
                    ReportData = (uint8_t*)&keyboard_report_sent;
                    ReportSize = sizeof(keyboard_report_sent);
                    break;
                }

                /* Write the report data to the control endpoint */
                Endpoint_Write_Control_Stream_LE(ReportData, ReportSize);
                Endpoint_ClearOUT();
            }

            break;
        case HID_REQ_SetReport:
            if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
            {

                // Interface
                switch (USB_ControlRequest.wIndex) {
                case KEYBOARD_INTERFACE:
                    Endpoint_ClearSETUP();

                    while (!(Endpoint_IsOUTReceived())) {
                        if (USB_DeviceState == DEVICE_STATE_Unattached)
                          return;
                    }
                    keyboard_led_stats = Endpoint_Read_8();

                    Endpoint_ClearOUT();
                    Endpoint_ClearStatusStage();
                    break;
                }

            }

            break;

        case HID_REQ_GetProtocol:
            if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
            {
                Endpoint_ClearSETUP();
                while (!(Endpoint_IsINReady()));
                Endpoint_Write_8(protocol_report);
                Endpoint_ClearIN();
                Endpoint_ClearStatusStage();
            }

            break;
        case HID_REQ_SetProtocol:
            if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
            {
                Endpoint_ClearSETUP();
                Endpoint_ClearStatusStage();

                protocol_report = ((USB_ControlRequest.wValue & 0xFF) != 0x00);
            }

            break;
        case HID_REQ_SetIdle:
            if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
            {
                Endpoint_ClearSETUP();
                Endpoint_ClearStatusStage();

                idle_duration = ((USB_ControlRequest.wValue & 0xFF00) >> 8);
            }

            break;
        case HID_REQ_GetIdle:
            if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
            {
                Endpoint_ClearSETUP();
                while (!(Endpoint_IsINReady()));
                Endpoint_Write_8(idle_duration);
                Endpoint_ClearIN();
                Endpoint_ClearStatusStage();
            }

            break;
    }
}

/*******************************************************************************
 * Host driver 
 ******************************************************************************/
static uint8_t keyboard_leds(void)
{
    return keyboard_led_stats;
}

static void send_keyboard(report_keyboard_t *report)
{
    // TODO: handle NKRO report
    /* Select the Keyboard Report Endpoint */
    Endpoint_SelectEndpoint(KEYBOARD_IN_EPNUM);

    /* Check if Keyboard Endpoint Ready for Read/Write */
    if (Endpoint_IsReadWriteAllowed())
    {
        /* Write Keyboard Report Data */
        Endpoint_Write_Stream_LE(report, sizeof(report_keyboard_t), NULL);

        /* Finalize the stream transfer to send the last packet */
        Endpoint_ClearIN();
    }
    keyboard_report_sent = *report;
}

static void send_mouse(report_mouse_t *report)
{
#ifdef MOUSE_ENABLE
    /* Select the Mouse Report Endpoint */
    Endpoint_SelectEndpoint(MOUSE_IN_EPNUM);

    /* Check if Mouse Endpoint Ready for Read/Write */
    if (Endpoint_IsReadWriteAllowed())
    {
        /* Write Mouse Report Data */
        Endpoint_Write_Stream_LE(report, sizeof(report_mouse_t), NULL);

        /* Finalize the stream transfer to send the last packet */
        Endpoint_ClearIN();
    }
#endif
}

static void send_system(uint16_t data)
{
    report_extra_t r = {
        .report_id = REPORT_ID_SYSTEM,
        .usage = data
    };
    Endpoint_SelectEndpoint(EXTRA_IN_EPNUM);
    if (Endpoint_IsReadWriteAllowed()) {
        Endpoint_Write_Stream_LE(&r, sizeof(report_extra_t), NULL);
        Endpoint_ClearIN();
    }
}

static void send_consumer(uint16_t data)
{
    report_extra_t r = {
        .report_id = REPORT_ID_CONSUMER,
        .usage = data
    };
    Endpoint_SelectEndpoint(EXTRA_IN_EPNUM);
    if (Endpoint_IsReadWriteAllowed()) {
        Endpoint_Write_Stream_LE(&r, sizeof(report_extra_t), NULL);
        Endpoint_ClearIN();
    }
}


/*******************************************************************************
 * sendchar
 ******************************************************************************/
#define SEND_TIMEOUT 10
int8_t sendchar(uint8_t c)
{
    if (USB_DeviceState != DEVICE_STATE_Configured)
      return -1;

    Endpoint_SelectEndpoint(CONSOLE_IN_EPNUM);

    uint8_t timeout = SEND_TIMEOUT;
    uint16_t prevFN = USB_Device_GetFrameNumber();
    while (!Endpoint_IsReadWriteAllowed()) {
        switch (USB_DeviceState) {
        case DEVICE_STATE_Unattached:
        case DEVICE_STATE_Suspended:
            return -1;
        }
        if (Endpoint_IsStalled())
            return -1;
        if (prevFN != USB_Device_GetFrameNumber()) {
            if (!(timeout--))
                return -1;
            prevFN = USB_Device_GetFrameNumber();
        }
    }

    Endpoint_Write_8(c);

    // send when bank is full
    if (!Endpoint_IsReadWriteAllowed())
        Endpoint_ClearIN();

    return 0;
}
