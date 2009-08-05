/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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

/** \file
 *
 *  Header file for RNDISEthernet.c.
 */
 
#ifndef _RNDISETHERNET_H_
#define _RNDISETHERNET_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/pgmspace.h>
		#include <avr/power.h>
		#include <string.h>
		#include <stdio.h>

		#include "Descriptors.h"

		#include "Lib/RNDIS.h"
		#include "Lib/Ethernet.h"
		#include "Lib/TCP.h"
		#include "Lib/ARP.h"
		#include "Lib/Webserver.h"

		#include <LUFA/Version.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/Peripheral/SerialStream.h>
	
	/* Macros: */
		/** Notification value to indicate that a frame is ready to be read by the host. */
		#define NOTIF_RESPONSE_AVAILABLE  0x01

		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY      LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is busy. */
		#define LEDMASK_USB_BUSY         (LEDS_LED2)
		
	/* Type Defines: */
		/** Type define for a RNDIS notification message, for transmission to the RNDIS host via the notification
		 *  Endpoint.
		 */
		typedef struct
		{
			uint8_t  bmRequestType; /**< Notification type, a mask of values from SrdRequestType.h */
			uint8_t  bNotification; /**< Notification index, indicating what the RNDIS notification relates to */
			uint16_t wValue; /**< Two byte notification value parameter */
			uint16_t wIndex; /**< Two byte notification index parameter */
			uint16_t wLength; /**< Size of data payload following the notification header */
		} USB_Notification_t;
		
	/* Function Prototypes: */
		void SetupHardware(void);
		void RNDIS_Task(void);
		void Ethernet_Task(void);

		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_UnhandledControlRequest(void);
	
#endif
