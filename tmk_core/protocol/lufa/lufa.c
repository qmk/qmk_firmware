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
#include "sleep_led.h"
#endif
#include "suspend.h"

#include "descriptor.h"
#include "lufa.h"
#include "quantum.h"
#include <util/atomic.h>

#ifdef NKRO_ENABLE
  #include "keycode_config.h"

  extern keymap_config_t keymap_config;
#endif


#ifdef AUDIO_ENABLE
    #include <audio.h>
#endif

#ifdef BLUETOOTH_ENABLE
    #include "bluetooth.h"
#endif
#ifdef ADAFRUIT_BLE_ENABLE
    #include "adafruit_ble.h"
#endif

#ifdef VIRTSER_ENABLE
    #include "virtser.h"
#endif

#if (defined(RGB_MIDI) | defined(RGBLIGHT_ANIMATIONS)) & defined(RGBLIGHT_ENABLE)
    #include "rgblight.h"
#endif

#ifdef MIDI_ENABLE
  #include "sysex_tools.h"
#endif

#ifdef RAW_ENABLE
	#include "raw_hid.h"
#endif

uint8_t keyboard_idle = 0;
/* 0: Boot Protocol, 1: Report Protocol(default) */
uint8_t keyboard_protocol = 1;
static uint8_t keyboard_led_stats = 0;

static report_keyboard_t keyboard_report_sent;

#ifdef MIDI_ENABLE
static void usb_send_func(MidiDevice * device, uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2);
static void usb_get_midi(MidiDevice * device);
static void midi_usb_init(MidiDevice * device);
#endif

/* Host driver */
static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);
host_driver_t lufa_driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer,
#ifdef MIDI_ENABLE
    usb_send_func,
    usb_get_midi,
    midi_usb_init
#endif
};

/*******************************************************************************
 * MIDI
 ******************************************************************************/

#ifdef MIDI_ENABLE
USB_ClassInfo_MIDI_Device_t USB_MIDI_Interface =
{
  .Config =
  {
    .StreamingInterfaceNumber = AS_INTERFACE,
    .DataINEndpoint           =
    {
      .Address          = MIDI_STREAM_IN_EPADDR,
      .Size             = MIDI_STREAM_EPSIZE,
      .Banks            = 1,
    },
    .DataOUTEndpoint          =
    {
      .Address          = MIDI_STREAM_OUT_EPADDR,
      .Size             = MIDI_STREAM_EPSIZE,
      .Banks            = 1,
    },
  },
};

#define SYSEX_START_OR_CONT 0x40
#define SYSEX_ENDS_IN_1 0x50
#define SYSEX_ENDS_IN_2 0x60
#define SYSEX_ENDS_IN_3 0x70

#define SYS_COMMON_1 0x50
#define SYS_COMMON_2 0x20
#define SYS_COMMON_3 0x30
#endif

#ifdef VIRTSER_ENABLE
USB_ClassInfo_CDC_Device_t cdc_device =
{
  .Config =
  {
    .ControlInterfaceNumber = CCI_INTERFACE,
    .DataINEndpoint         =
    {
      .Address		= CDC_IN_EPADDR,
      .Size		= CDC_EPSIZE,
      .Banks		= 1,
    },
    .DataOUTEndpoint	    =
    {
      .Address		= CDC_OUT_EPADDR,
      .Size		= CDC_EPSIZE,
      .Banks		= 1,
    },
    .NotificationEndpoint   =
    {
      .Address		= CDC_NOTIFICATION_EPADDR,
      .Size		= CDC_NOTIFICATION_EPSIZE,
      .Banks		= 1,
    },
  },
};
#endif

#ifdef RAW_ENABLE

void raw_hid_send( uint8_t *data, uint8_t length )
{
	// TODO: implement variable size packet
	if ( length != RAW_EPSIZE )
	{
		return;
	}

	if (USB_DeviceState != DEVICE_STATE_Configured)
	{
		return;
	}

	// TODO: decide if we allow calls to raw_hid_send() in the middle
	// of other endpoint usage.
	uint8_t ep = Endpoint_GetCurrentEndpoint();

	Endpoint_SelectEndpoint(RAW_IN_EPNUM);

	// Check to see if the host is ready to accept another packet
	if (Endpoint_IsINReady())
	{
		// Write data
		Endpoint_Write_Stream_LE(data, RAW_EPSIZE, NULL);
		// Finalize the stream transfer to send the last packet
		Endpoint_ClearIN();
	}

	Endpoint_SelectEndpoint(ep);
}

__attribute__ ((weak))
void raw_hid_receive( uint8_t *data, uint8_t length )
{
	// Users should #include "raw_hid.h" in their own code
	// and implement this function there. Leave this as weak linkage
	// so users can opt to not handle data coming in.
}

static void raw_hid_task(void)
{
	// Create a temporary buffer to hold the read in data from the host
	uint8_t data[RAW_EPSIZE];
	bool data_read = false;

	// Device must be connected and configured for the task to run
	if (USB_DeviceState != DEVICE_STATE_Configured)
	return;

	Endpoint_SelectEndpoint(RAW_OUT_EPNUM);

	// Check to see if a packet has been sent from the host
	if (Endpoint_IsOUTReceived())
	{
		// Check to see if the packet contains data
		if (Endpoint_IsReadWriteAllowed())
		{
			/* Read data */
			Endpoint_Read_Stream_LE(data, sizeof(data), NULL);
			data_read = true;
		}

		// Finalize the stream transfer to receive the last packet
		Endpoint_ClearOUT();

		if ( data_read )
		{
			raw_hid_receive( data, sizeof(data) );
		}
	}
}
#endif

/*******************************************************************************
 * Console
 ******************************************************************************/
#ifdef CONSOLE_ENABLE
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
    if (!Endpoint_IsEnabled() || !Endpoint_IsConfigured()) {
        Endpoint_SelectEndpoint(ep);
        return;
    }

    // fill empty bank
    while (Endpoint_IsReadWriteAllowed())
        Endpoint_Write_8(0);

    // flash senchar packet
    if (Endpoint_IsINReady()) {
        Endpoint_ClearIN();
    }

    Endpoint_SelectEndpoint(ep);
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
void EVENT_USB_Device_Connect(void)
{
    print("[C]");
    /* For battery powered device */
    if (!USB_IsInitialized) {
        USB_Disable();
        USB_Init();
        USB_Device_EnableSOFEvents();
    }
}

void EVENT_USB_Device_Disconnect(void)
{
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

void EVENT_USB_Device_Reset(void)
{
    print("[R]");
}

void EVENT_USB_Device_Suspend()
{
    print("[S]");
#ifdef SLEEP_LED_ENABLE
    sleep_led_enable();
#endif
}

void EVENT_USB_Device_WakeUp()
{
    print("[W]");
    suspend_wakeup_init();

#ifdef SLEEP_LED_ENABLE
    sleep_led_disable();
    // NOTE: converters may not accept this
    led_set(host_keyboard_leds());
#endif
}



#ifdef CONSOLE_ENABLE
static bool console_flush = false;
#define CONSOLE_FLUSH_SET(b)   do { \
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {\
    console_flush = b; \
  } \
} while (0)

// called every 1ms
void EVENT_USB_Device_StartOfFrame(void)
{
    static uint8_t count;
    if (++count % 50) return;
    count = 0;

    if (!console_flush) return;
    Console_Task();
    console_flush = false;
}

#endif

/** Event handler for the USB_ConfigurationChanged event.
 * This is fired when the host sets the current configuration of the USB device after enumeration.
 *
 * ATMega32u2 supports dual bank(ping-pong mode) only on endpoint 3 and 4,
 * it is safe to use singl bank for all endpoints.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    /* Setup Keyboard HID Report Endpoints */
    ConfigSuccess &= ENDPOINT_CONFIG(KEYBOARD_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                     KEYBOARD_EPSIZE, ENDPOINT_BANK_SINGLE);

#ifdef MOUSE_ENABLE
    /* Setup Mouse HID Report Endpoint */
    ConfigSuccess &= ENDPOINT_CONFIG(MOUSE_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                     MOUSE_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#ifdef EXTRAKEY_ENABLE
    /* Setup Extra HID Report Endpoint */
    ConfigSuccess &= ENDPOINT_CONFIG(EXTRAKEY_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                     EXTRAKEY_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#ifdef RAW_ENABLE
    /* Setup Raw HID Report Endpoints */
    ConfigSuccess &= ENDPOINT_CONFIG(RAW_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
									 RAW_EPSIZE, ENDPOINT_BANK_SINGLE);
    ConfigSuccess &= ENDPOINT_CONFIG(RAW_OUT_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_OUT,
									 RAW_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#ifdef CONSOLE_ENABLE
    /* Setup Console HID Report Endpoints */
    ConfigSuccess &= ENDPOINT_CONFIG(CONSOLE_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                     CONSOLE_EPSIZE, ENDPOINT_BANK_SINGLE);
#if 0
    ConfigSuccess &= ENDPOINT_CONFIG(CONSOLE_OUT_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_OUT,
                                     CONSOLE_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif
#endif

#ifdef NKRO_ENABLE
    /* Setup NKRO HID Report Endpoints */
    ConfigSuccess &= ENDPOINT_CONFIG(NKRO_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                     NKRO_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#ifdef MIDI_ENABLE
    ConfigSuccess &= Endpoint_ConfigureEndpoint(MIDI_STREAM_IN_EPADDR, EP_TYPE_BULK, MIDI_STREAM_EPSIZE, ENDPOINT_BANK_SINGLE);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(MIDI_STREAM_OUT_EPADDR, EP_TYPE_BULK, MIDI_STREAM_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#ifdef VIRTSER_ENABLE
    ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_NOTIFICATION_EPADDR, EP_TYPE_INTERRUPT, CDC_NOTIFICATION_EPSIZE, ENDPOINT_BANK_SINGLE);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_OUT_EPADDR, EP_TYPE_BULK, CDC_EPSIZE, ENDPOINT_BANK_SINGLE);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_IN_EPADDR, EP_TYPE_BULK, CDC_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif
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
#ifdef NKRO_ENABLE
                case NKRO_INTERFACE:
#endif
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
                if (USB_ControlRequest.wIndex == KEYBOARD_INTERFACE) {
                    Endpoint_ClearSETUP();
                    while (!(Endpoint_IsINReady()));
                    Endpoint_Write_8(keyboard_protocol);
                    Endpoint_ClearIN();
                    Endpoint_ClearStatusStage();
                }
            }

            break;
        case HID_REQ_SetProtocol:
            if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
            {
                if (USB_ControlRequest.wIndex == KEYBOARD_INTERFACE) {
                    Endpoint_ClearSETUP();
                    Endpoint_ClearStatusStage();

                    keyboard_protocol = (USB_ControlRequest.wValue & 0xFF);
                    clear_keyboard();
                }
            }

            break;
        case HID_REQ_SetIdle:
            if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
            {
                Endpoint_ClearSETUP();
                Endpoint_ClearStatusStage();

                keyboard_idle = ((USB_ControlRequest.wValue & 0xFF00) >> 8);
            }

            break;
        case HID_REQ_GetIdle:
            if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
            {
                Endpoint_ClearSETUP();
                while (!(Endpoint_IsINReady()));
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
p
 ******************************************************************************/
static uint8_t keyboard_leds(void)
{
    return keyboard_led_stats;
}

#define SendToUSB 1
#define SendToBT  2
#define SendToBLE 4

static inline uint8_t where_to_send(void) {
#ifdef ADAFRUIT_BLE_ENABLE
#if 0
  if (adafruit_ble_is_connected()) {
    // For testing, send to BLE as a priority
    return SendToBLE;
  }
#endif

  // This is the real policy
  if (USB_DeviceState != DEVICE_STATE_Configured) {
    if (adafruit_ble_is_connected()) {
      return SendToBLE;
    }
  }
#endif
  return ((USB_DeviceState == DEVICE_STATE_Configured) ? SendToUSB : 0)
#ifdef BLUETOOTH_ENABLE
    || SendToBT
#endif
    ;
}

static void send_keyboard(report_keyboard_t *report)
{
#ifdef BLUETOOTH_ENABLE
    bluefruit_serial_send(0xFD);
    for (uint8_t i = 0; i < KEYBOARD_EPSIZE; i++) {
        bluefruit_serial_send(report->raw[i]);
    }
#endif

    uint8_t timeout = 255;
    uint8_t where = where_to_send();

#ifdef ADAFRUIT_BLE_ENABLE
    if (where & SendToBLE) {
      adafruit_ble_send_keys(report->mods, report->keys, sizeof(report->keys));
    }
#endif

    if (!(where & SendToUSB)) {
      return;
    }

    /* Select the Keyboard Report Endpoint */
#ifdef NKRO_ENABLE
    if (keyboard_protocol && keymap_config.nkro) {
        /* Report protocol - NKRO */
        Endpoint_SelectEndpoint(NKRO_IN_EPNUM);

        /* Check if write ready for a polling interval around 1ms */
        while (timeout-- && !Endpoint_IsReadWriteAllowed()) _delay_us(4);
        if (!Endpoint_IsReadWriteAllowed()) return;

        /* Write Keyboard Report Data */
        Endpoint_Write_Stream_LE(report, NKRO_EPSIZE, NULL);
    }
    else
#endif
    {
        /* Boot protocol */
        Endpoint_SelectEndpoint(KEYBOARD_IN_EPNUM);

        /* Check if write ready for a polling interval around 10ms */
        while (timeout-- && !Endpoint_IsReadWriteAllowed()) _delay_us(40);
        if (!Endpoint_IsReadWriteAllowed()) return;

        /* Write Keyboard Report Data */
        Endpoint_Write_Stream_LE(report, KEYBOARD_EPSIZE, NULL);
    }

    /* Finalize the stream transfer to send the last packet */
    Endpoint_ClearIN();

    keyboard_report_sent = *report;
}

static void send_mouse(report_mouse_t *report)
{
#ifdef MOUSE_ENABLE

#ifdef BLUETOOTH_ENABLE
    bluefruit_serial_send(0xFD);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x03);
    bluefruit_serial_send(report->buttons);
    bluefruit_serial_send(report->x);
    bluefruit_serial_send(report->y);
    bluefruit_serial_send(report->v); // should try sending the wheel v here
    bluefruit_serial_send(report->h); // should try sending the wheel h here
    bluefruit_serial_send(0x00);
#endif

    uint8_t timeout = 255;

    uint8_t where = where_to_send();

#ifdef ADAFRUIT_BLE_ENABLE
    if (where & SendToBLE) {
      // FIXME: mouse buttons
      adafruit_ble_send_mouse_move(report->x, report->y, report->v, report->h);
    }
#endif
    if (!(where & SendToUSB)) {
      return;
    }

    /* Select the Mouse Report Endpoint */
    Endpoint_SelectEndpoint(MOUSE_IN_EPNUM);

    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed()) _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    /* Write Mouse Report Data */
    Endpoint_Write_Stream_LE(report, sizeof(report_mouse_t), NULL);

    /* Finalize the stream transfer to send the last packet */
    Endpoint_ClearIN();
#endif
}

static void send_system(uint16_t data)
{
    uint8_t timeout = 255;

    if (USB_DeviceState != DEVICE_STATE_Configured)
        return;

    report_extra_t r = {
        .report_id = REPORT_ID_SYSTEM,
        .usage = data - SYSTEM_POWER_DOWN + 1
    };
    Endpoint_SelectEndpoint(EXTRAKEY_IN_EPNUM);

    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed()) _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    Endpoint_Write_Stream_LE(&r, sizeof(report_extra_t), NULL);
    Endpoint_ClearIN();
}

static void send_consumer(uint16_t data)
{

#ifdef BLUETOOTH_ENABLE
    static uint16_t last_data = 0;
    if (data == last_data) return;
    last_data = data;
    uint16_t bitmap = CONSUMER2BLUEFRUIT(data);
    bluefruit_serial_send(0xFD);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x02);
    bluefruit_serial_send((bitmap>>8)&0xFF);
    bluefruit_serial_send(bitmap&0xFF);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x00);
#endif

    uint8_t timeout = 255;
    uint8_t where = where_to_send();

#ifdef ADAFRUIT_BLE_ENABLE
    if (where & SendToBLE) {
      adafruit_ble_send_consumer_key(data, 0);
    }
#endif
    if (!(where & SendToUSB)) {
      return;
    }

    report_extra_t r = {
        .report_id = REPORT_ID_CONSUMER,
        .usage = data
    };
    Endpoint_SelectEndpoint(EXTRAKEY_IN_EPNUM);

    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed()) _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    Endpoint_Write_Stream_LE(&r, sizeof(report_extra_t), NULL);
    Endpoint_ClearIN();
}


/*******************************************************************************
 * sendchar
 ******************************************************************************/
#ifdef CONSOLE_ENABLE
#define SEND_TIMEOUT 5
int8_t sendchar(uint8_t c)
{
    // Not wait once timeouted.
    // Because sendchar() is called so many times, waiting each call causes big lag.
    static bool timeouted = false;

    // prevents Console_Task() from running during sendchar() runs.
    // or char will be lost. These two function is mutually exclusive.
    CONSOLE_FLUSH_SET(false);

    if (USB_DeviceState != DEVICE_STATE_Configured)
        return -1;

    uint8_t ep = Endpoint_GetCurrentEndpoint();
    Endpoint_SelectEndpoint(CONSOLE_IN_EPNUM);
    if (!Endpoint_IsEnabled() || !Endpoint_IsConfigured()) {
        goto ERROR_EXIT;
    }

    if (timeouted && !Endpoint_IsReadWriteAllowed()) {
        goto ERROR_EXIT;
    }

    timeouted = false;

    uint8_t timeout = SEND_TIMEOUT;
    while (!Endpoint_IsReadWriteAllowed()) {
        if (USB_DeviceState != DEVICE_STATE_Configured) {
            goto ERROR_EXIT;
        }
        if (Endpoint_IsStalled()) {
            goto ERROR_EXIT;
        }
        if (!(timeout--)) {
            timeouted = true;
            goto ERROR_EXIT;
        }
        _delay_ms(1);
    }

    Endpoint_Write_8(c);

    // send when bank is full
    if (!Endpoint_IsReadWriteAllowed()) {
        while (!(Endpoint_IsINReady()));
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
#else
int8_t sendchar(uint8_t c)
{
    return 0;
}
#endif

/*******************************************************************************
 * MIDI
 ******************************************************************************/

#ifdef MIDI_ENABLE
static void usb_send_func(MidiDevice * device, uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2) {
  MIDI_EventPacket_t event;
  event.Data1 = byte0;
  event.Data2 = byte1;
  event.Data3 = byte2;

  uint8_t cable = 0;

// Endpoint_SelectEndpoint(MIDI_STREAM_IN_EPNUM);

  //if the length is undefined we assume it is a SYSEX message
  if (midi_packet_length(byte0) == UNDEFINED) {
    switch(cnt) {
      case 3:
        if (byte2 == SYSEX_END)
          event.Event = MIDI_EVENT(cable, SYSEX_ENDS_IN_3);
        else
          event.Event = MIDI_EVENT(cable, SYSEX_START_OR_CONT);
        break;
      case 2:
        if (byte1 == SYSEX_END)
          event.Event = MIDI_EVENT(cable, SYSEX_ENDS_IN_2);
        else
          event.Event = MIDI_EVENT(cable, SYSEX_START_OR_CONT);
        break;
      case 1:
        if (byte0 == SYSEX_END)
          event.Event = MIDI_EVENT(cable, SYSEX_ENDS_IN_1);
        else
          event.Event = MIDI_EVENT(cable, SYSEX_START_OR_CONT);
        break;
      default:
        return; //invalid cnt
    }
  } else {
    //deal with 'system common' messages
    //TODO are there any more?
    switch(byte0 & 0xF0){
      case MIDI_SONGPOSITION:
        event.Event = MIDI_EVENT(cable, SYS_COMMON_3);
        break;
      case MIDI_SONGSELECT:
      case MIDI_TC_QUARTERFRAME:
        event.Event = MIDI_EVENT(cable, SYS_COMMON_2);
        break;
      default:
        event.Event = MIDI_EVENT(cable, byte0);
        break;
    }
  }

// Endpoint_Write_Stream_LE(&event, sizeof(event), NULL);
// Endpoint_ClearIN();

  MIDI_Device_SendEventPacket(&USB_MIDI_Interface, &event);
  MIDI_Device_Flush(&USB_MIDI_Interface);
  MIDI_Device_USBTask(&USB_MIDI_Interface);
  USB_USBTask();
}

static void usb_get_midi(MidiDevice * device) {
  MIDI_EventPacket_t event;
  while (MIDI_Device_ReceiveEventPacket(&USB_MIDI_Interface, &event)) {

    midi_packet_length_t length = midi_packet_length(event.Data1);
    uint8_t input[3];
    input[0] = event.Data1;
    input[1] = event.Data2;
    input[2] = event.Data3;
    if (length == UNDEFINED) {
      //sysex
      if (event.Event == MIDI_EVENT(0, SYSEX_START_OR_CONT) || event.Event == MIDI_EVENT(0, SYSEX_ENDS_IN_3)) {
        length = 3;
      } else if (event.Event == MIDI_EVENT(0, SYSEX_ENDS_IN_2)) {
        length = 2;
      } else if(event.Event ==  MIDI_EVENT(0, SYSEX_ENDS_IN_1)) {
        length = 1;
      } else {
        //XXX what to do?
      }
    }

    //pass the data to the device input function
    if (length != UNDEFINED)
      midi_device_input(device, length, input);
  }
  MIDI_Device_USBTask(&USB_MIDI_Interface);
  USB_USBTask();
}

static void midi_usb_init(MidiDevice * device){
  midi_device_init(device);
  midi_device_set_send_func(device, usb_send_func);
  midi_device_set_pre_input_process_func(device, usb_get_midi);

  // SetupHardware();
  sei();
}

void MIDI_Task(void)
{

    /* Device must be connected and configured for the task to run */
    dprint("in MIDI_TASK\n");
    if (USB_DeviceState != DEVICE_STATE_Configured)
      return;
    dprint("continuing in MIDI_TASK\n");

    Endpoint_SelectEndpoint(MIDI_STREAM_IN_EPADDR);

    if (Endpoint_IsINReady())
    {

        dprint("Endpoint is ready\n");

        uint8_t MIDICommand = 0;
        uint8_t MIDIPitch;

        /* Get board button status - if pressed use channel 10 (percussion), otherwise use channel 1 */
        uint8_t Channel = MIDI_CHANNEL(1);

        MIDICommand = MIDI_COMMAND_NOTE_ON;
        MIDIPitch   = 0x3E;

        /* Check if a MIDI command is to be sent */
        if (MIDICommand)
        {
            dprint("Command exists\n");
            MIDI_EventPacket_t MIDIEvent = (MIDI_EventPacket_t)
                {
                    .Event       = MIDI_EVENT(0, MIDICommand),

                    .Data1       = MIDICommand | Channel,
                    .Data2       = MIDIPitch,
                    .Data3       = MIDI_STANDARD_VELOCITY,
                };

            /* Write the MIDI event packet to the endpoint */
            Endpoint_Write_Stream_LE(&MIDIEvent, sizeof(MIDIEvent), NULL);

            /* Send the data in the endpoint to the host */
            Endpoint_ClearIN();
        }
    }


    /* Select the MIDI OUT stream */
    Endpoint_SelectEndpoint(MIDI_STREAM_OUT_EPADDR);

    /* Check if a MIDI command has been received */
    if (Endpoint_IsOUTReceived())
    {
        MIDI_EventPacket_t MIDIEvent;

        /* Read the MIDI event packet from the endpoint */
        Endpoint_Read_Stream_LE(&MIDIEvent, sizeof(MIDIEvent), NULL);

        /* If the endpoint is now empty, clear the bank */
        if (!(Endpoint_BytesInEndpoint()))
        {
            /* Clear the endpoint ready for new packet */
            Endpoint_ClearOUT();
        }
    }
}

#endif

/*******************************************************************************
 * VIRTUAL SERIAL
 ******************************************************************************/

#ifdef VIRTSER_ENABLE
void virtser_init(void)
{
  cdc_device.State.ControlLineStates.DeviceToHost = CDC_CONTROL_LINE_IN_DSR ;
  CDC_Device_SendControlLineStateChange(&cdc_device);
}

void virtser_recv(uint8_t c) __attribute__ ((weak));
void virtser_recv(uint8_t c)
{
  // Ignore by default
}

void virtser_task(void)
{
  uint16_t count = CDC_Device_BytesReceived(&cdc_device);
  uint8_t ch;
  if (count)
  {
    ch = CDC_Device_ReceiveByte(&cdc_device);
    virtser_recv(ch);
  }
}
void virtser_send(const uint8_t byte)
{
  uint8_t timeout = 255;
  uint8_t ep = Endpoint_GetCurrentEndpoint();

  if (cdc_device.State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR)
  {
    /* IN packet */
    Endpoint_SelectEndpoint(cdc_device.Config.DataINEndpoint.Address);

    if (!Endpoint_IsEnabled() || !Endpoint_IsConfigured()) {
        Endpoint_SelectEndpoint(ep);
        return;
    }

    while (timeout-- && !Endpoint_IsReadWriteAllowed()) _delay_us(40);

    Endpoint_Write_8(byte);
    CDC_Device_Flush(&cdc_device);

    if (Endpoint_IsINReady()) {
      Endpoint_ClearIN();
    }

    Endpoint_SelectEndpoint(ep);
  }
}
#endif

/*******************************************************************************
 * main
 ******************************************************************************/
static void setup_mcu(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    // clock_prescale_set(clock_div_1);

    CLKPR = (1 << CLKPCE);
    CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
}

static void setup_usb(void)
{
    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
    print_set_sendchar(sendchar);
}


#ifdef MIDI_ENABLE
void fallthrough_callback(MidiDevice * device,
    uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2);
void cc_callback(MidiDevice * device,
    uint8_t chan, uint8_t num, uint8_t val);
void sysex_callback(MidiDevice * device,
    uint16_t start, uint8_t length, uint8_t * data);
#endif

int main(void)  __attribute__ ((weak));
int main(void)
{

#ifdef MIDI_ENABLE
    midi_device_init(&midi_device);
    midi_device_set_send_func(&midi_device, usb_send_func);
    midi_device_set_pre_input_process_func(&midi_device, usb_get_midi);
#endif

    setup_mcu();
    keyboard_setup();
    setup_usb();
    sei();

#ifdef MIDI_ENABLE
    midi_register_fallthrough_callback(&midi_device, fallthrough_callback);
    midi_register_cc_callback(&midi_device, cc_callback);
    midi_register_sysex_callback(&midi_device, sysex_callback);

    // init_notes();
    // midi_send_cc(&midi_device, 0, 1, 2);
    // midi_send_cc(&midi_device, 15, 1, 0);
    // midi_send_noteon(&midi_device, 0, 64, 127);
    // midi_send_noteoff(&midi_device, 0, 64, 127);
#endif

#ifdef BLUETOOTH_ENABLE
    serial_init();
#endif

    /* wait for USB startup & debug output */

#ifdef WAIT_FOR_USB
    while (USB_DeviceState != DEVICE_STATE_Configured) {
    #if defined(INTERRUPT_CONTROL_ENDPOINT)
            ;
    #else
            USB_USBTask();
    #endif
    }
    print("USB configured.\n");
#else
    USB_USBTask();
#endif
    /* init modules */
    keyboard_init();
    host_set_driver(&lufa_driver);
#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

#ifdef VIRTSER_ENABLE
    virtser_init();
#endif

    print("Keyboard start.\n");
    while (1) {
        #if !defined(BLUETOOTH_ENABLE) && !defined(ADAFRUIT_BLE_ENABLE)
        while (USB_DeviceState == DEVICE_STATE_Suspended) {
            print("[s]");
            suspend_power_down();
            if (USB_Device_RemoteWakeupEnabled && suspend_wakeup_condition()) {
                    USB_Device_SendRemoteWakeup();
            }
        }
        #endif

        keyboard_task();

#ifdef MIDI_ENABLE
        midi_device_process(&midi_device);
        // MIDI_Task();
#endif

#if defined(RGBLIGHT_ANIMATIONS) & defined(RGBLIGHT_ENABLE)
        rgblight_task();
#endif

#ifdef ADAFRUIT_BLE_ENABLE
        adafruit_ble_task();
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
}

#ifdef MIDI_ENABLE
void fallthrough_callback(MidiDevice * device,
    uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2){

#ifdef AUDIO_ENABLE
  if (cnt == 3) {
    switch (byte0 & 0xF0) {
        case MIDI_NOTEON:
            play_note(((double)261.6)*pow(2.0, -4.0)*pow(2.0,(byte1 & 0x7F)/12.0), (byte2 & 0x7F) / 8);
            break;
        case MIDI_NOTEOFF:
            stop_note(((double)261.6)*pow(2.0, -4.0)*pow(2.0,(byte1 & 0x7F)/12.0));
            break;
    }
  }
  if (byte0 == MIDI_STOP) {
    stop_all_notes();
  }
#endif
}


void cc_callback(MidiDevice * device,
    uint8_t chan, uint8_t num, uint8_t val) {
  //sending it back on the next channel
  // midi_send_cc(device, (chan + 1) % 16, num, val);
}

#ifdef API_SYSEX_ENABLE
uint8_t midi_buffer[MIDI_SYSEX_BUFFER] = {0};
#endif

void sysex_callback(MidiDevice * device, uint16_t start, uint8_t length, uint8_t * data) {
    #ifdef API_SYSEX_ENABLE
        // SEND_STRING("\n");
        // send_word(start);
        // SEND_STRING(": ");
        // Don't store the header
        int16_t pos = start - 4;
        for (uint8_t place = 0; place < length; place++) {
            // send_byte(*data);
            if (pos >= 0) {
                if (*data == 0xF7) {
                    // SEND_STRING("\nRD: ");
                    // for (uint8_t i = 0; i < start + place + 1; i++){
                    //     send_byte(midi_buffer[i]);
                    // SEND_STRING(" ");
                    // }
                    const unsigned decoded_length = sysex_decoded_length(pos);
                    uint8_t decoded[API_SYSEX_MAX_SIZE];
                    sysex_decode(decoded, midi_buffer, pos);
                    process_api(decoded_length, decoded);
                    return;
                }
                else if (pos >= MIDI_SYSEX_BUFFER) {
                    return;
                }
                midi_buffer[pos] = *data;
            }
            // SEND_STRING(" ");
            data++;
            pos++;
        }
    #endif
}


#endif
