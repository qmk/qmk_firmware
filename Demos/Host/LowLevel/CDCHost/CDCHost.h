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
 *  Header file for CDCHost.c.
 */

#ifndef _CDC_HOST_H_
#define _CDC_HOST_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/pgmspace.h>
		#include <avr/power.h>
		#include <stdio.h>

		#include <LUFA/Version.h>
		#include <LUFA/Drivers/Misc/TerminalCodes.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Peripheral/SerialStream.h>
		#include <LUFA/Drivers/Board/LEDs.h>
		
		#include "ConfigDescriptor.h"
		
	/* Macros: */
		/** Pipe number for the CDC data IN pipe */
		#define CDC_DATAPIPE_IN                1

		/** Pipe number for the CDC data OUT pipe */
		#define CDC_DATAPIPE_OUT               2

		/** Pipe number for the CDC notification pipe */
		#define CDC_NOTIFICATIONPIPE           3

		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY      LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)
		
	/* Type Defines: */
		/** Class state structure. An instance of this structure should be made for each CDC interface
		 *  within the user application, and passed to each of the CDC class driver functions as the
		 *  CDCInterfaceInfo parameter. The contents of this structure should be set to their correct
		 *  values when used, or ommitted to force the library to use default values.
		 */
		typedef struct
		{
			const struct
			{
				uint8_t  ControlInterfaceNumber; /**< Interface number of the CDC control interface within the device */

				uint8_t  DataINEndpointNumber; /**< Endpoint number of the CDC interface's IN data endpoint */
				uint16_t DataINEndpointSize; /**< Size in bytes of the CDC interface's IN data endpoint */

				uint8_t  DataOUTEndpointNumber; /**< Endpoint number of the CDC interface's OUT data endpoint */
				uint16_t DataOUTEndpointSize;  /**< Size in bytes of the CDC interface's OUT data endpoint */

				uint8_t  NotificationEndpointNumber; /**< Endpoint number of the CDC interface's IN notification endpoint, if used */
				uint16_t NotificationEndpointSize;  /**< Size in bytes of the CDC interface's IN notification endpoint, if used */
			} Config;
			
			struct
			{
				uint8_t  ControlLineState; /**< Current control line states, as set by the host */

				struct
				{
					uint32_t BaudRateBPS; /**< Baud rate of the virtual serial port, in bits per second */
					uint8_t  CharFormat; /**< Character format of the virtual serial port, a value from the
										  *   CDCDevice_CDC_LineCodingFormats_t enum
										  */
					uint8_t  ParityType; /**< Parity setting of the virtual serial port, a value from the
										  *   CDCDevice_LineCodingParity_t enum
										  */
					uint8_t  DataBits; /**< Bits of data per character of the virtual serial port */
				} LineEncoding;
			} State;
		} USB_ClassInfo_CDC_Host_t;
		
	/* Function Prototypes: */
		void SetupHardware(void);
		void CDC_Host_Task(void);
	
		void EVENT_USB_Host_HostError(const uint8_t ErrorCode);
		void EVENT_USB_Host_DeviceAttached(void);
		void EVENT_USB_Host_DeviceUnattached(void);
		void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode);
		void EVENT_USB_Host_DeviceEnumerationComplete(void);
		
#endif
