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
#include "lufa.h"

static uint8_t keyboard_led_stats = 0;
report_keyboard_t keyboard_report_sent;
report_mouse_t mouse_report_sent;

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


int main(void)
{
    SetupHardware();
    sei();

    print_enable = true;
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
    debug_mouse = true;

    _delay_ms(3000);
    print("abcdefg\n");

    keyboard_init();
    host_set_driver(&lufa_driver);
    while (1) {
        keyboard_proc();
        Keyboard_HID_Task();
        Generic_HID_Task();
        USB_USBTask();
    }
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    USB_Init();
}

/** Event handler for the USB_Connect event. */
void EVENT_USB_Device_Connect(void)
{
}

/** Event handler for the USB_Disconnect event. */
void EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the USB_ConfigurationChanged event.
 * This is fired when the host sets the current configuration of the USB device after enumeration.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    /* Setup Keyboard HID Report Endpoints */
    ConfigSuccess &= Endpoint_ConfigureEndpoint(KEYBOARD_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                                HID_EPSIZE, ENDPOINT_BANK_SINGLE);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(KEYBOARD_OUT_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_OUT,
                                                HID_EPSIZE, ENDPOINT_BANK_SINGLE);

    /* Setup Mouse HID Report Endpoint */
    ConfigSuccess &= Endpoint_ConfigureEndpoint(MOUSE_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                                HID_EPSIZE, ENDPOINT_BANK_SINGLE);

	/* Setup Generic HID Report Endpoints */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(GENERIC_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
	                                            GENERIC_EPSIZE, ENDPOINT_BANK_SINGLE);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(GENERIC_OUT_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_OUT,
	                                            GENERIC_EPSIZE, ENDPOINT_BANK_SINGLE);
}

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
                case 1: // Keyboard
                    ReportData = (uint8_t*)&keyboard_report_sent;
                    ReportSize = sizeof(keyboard_report_sent);
                    break;
                case 2: // Mouse
                    ReportData = (uint8_t*)&mouse_report_sent;
                    ReportSize = sizeof(mouse_report_sent);
                    break;
                case 3: // Generic
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
                Endpoint_ClearSETUP();

                /* Wait until the LED report has been sent by the host */
                while (!(Endpoint_IsOUTReceived()))
                {
                    if (USB_DeviceState == DEVICE_STATE_Unattached)
                      return;
                }

                // Interface
                switch (USB_ControlRequest.wIndex) {
                case 1: // Keyboard
                    /* Read in the LED report from the host */
                    keyboard_led_stats = Endpoint_Read_8();
                    break;
                case 2: // Mouse
                    break;
                case 3: // Generic
                    break;
                }

                Endpoint_ClearOUT();
                Endpoint_ClearStatusStage();
            }

            break;
    }
}

/** Keyboard task.
 *  This processes host LED status reports sent to the device via the keyboard OUT reporting endpoint.
 */
void Keyboard_HID_Task(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

    /* Select the Keyboard LED Report Endpoint */
    Endpoint_SelectEndpoint(KEYBOARD_OUT_EPNUM);

    /* Check if Keyboard LED Endpoint Ready for Read/Write */
    if (Endpoint_IsReadWriteAllowed())
    {
        /* Read in the LED report from the host */
        keyboard_led_stats = Endpoint_Read_8();

        /* Handshake the OUT Endpoint - clear endpoint and ready for next report */
        Endpoint_ClearOUT();
    }
}

void Generic_HID_Task(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	Endpoint_SelectEndpoint(GENERIC_OUT_EPNUM);

	/* Check to see if a packet has been sent from the host */
	if (Endpoint_IsOUTReceived())
	{
		/* Check to see if the packet contains data */
		if (Endpoint_IsReadWriteAllowed())
		{
			/* Create a temporary buffer to hold the read in report from the host */
			uint8_t GenericData[GENERIC_REPORT_SIZE];

			/* Read Generic Report Data */
			Endpoint_Read_Stream_LE(&GenericData, sizeof(GenericData), NULL);

			/* Process Generic Report Data */
			//TODO: ProcessGenericHIDReport(GenericData);
		}

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearOUT();
	}

        /* IN packet */
	Endpoint_SelectEndpoint(GENERIC_IN_EPNUM);
        // send IN packet
	if (Endpoint_IsINReady())
            Endpoint_ClearIN();
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
    mouse_report_sent = *report;
}

static void send_system(uint16_t data)
{
}

static void send_consumer(uint16_t data)
{
}


/*******************************************************************************
 * sendchar
 ******************************************************************************/
int8_t sendchar(uint8_t c)
{
    if (USB_DeviceState != DEVICE_STATE_Configured)
      return -1;

    Endpoint_SelectEndpoint(GENERIC_IN_EPNUM);

    uint8_t timeout = 10;
    uint16_t prevFN = USB_Device_GetFrameNumber();
    while (!Endpoint_IsINReady()) {
        switch (USB_DeviceState) {
        case DEVICE_STATE_Unattached:
        case DEVICE_STATE_Suspended:
            return -1;
        }
        if (Endpoint_IsStalled())
            return -1;
        uint16_t currFN = USB_Device_GetFrameNumber();
        if (prevFN != USB_Device_GetFrameNumber()) {
            if (!(timeout--))
                return -1;
            prevFN = USB_Device_GetFrameNumber();
        }
    }

    Endpoint_Write_8(c);

    // send when packet is full
    if (!Endpoint_IsReadWriteAllowed())
        Endpoint_ClearIN();

    return 0;
}
