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

#ifndef __DEVCHAPTER9_H__
#define __DEVCHAPTER9_H__

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>
		#include <avr/eeprom.h>
		#include <avr/boot.h>
		#include <stdlib.h>
		#include <ctype.h>
		
		#include "../HighLevel/StdDescriptors.h"
		#include "../HighLevel/Events.h"
		#include "../HighLevel/StdRequestType.h"
		#include "../HighLevel/USBTask.h"
		#include "LowLevel.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */			
		/* Global Variables: */
			/** Indicates the currently set configuration number of the device. USB devices may have several
			 *  different configurations which the host can select between; this indicates the currently selected
			 *  value, or 0 if no configuration has been selected.
			 *
			 *  If a device has only one single configuration, the token USE_SINGLE_DEVICE_CONFIGURATION may be
			 *  defined in the project makefile and passed to the compiler using the -D switch. This optimize for
			 *  a single configuration, saving a small amount of space in the resulting compiled binary.
			 *
			 *  \note This variable should be treated as read-only in the user application, and never manually
			 *        changed in value.
			 *
			 *  \ingroup Group_Device
			 */
			extern uint8_t USB_ConfigurationNumber;
			
			/** Indicates if the host is currently allowing the device to issue remote wakeup events. If this
			 *  flag is cleared, the device should not issue remote wakeup events to the host.
			 *
			 *  \note This variable should be treated as read-only in the user application, and never manually
			 *        changed in value.
			 *
			 *  \ingroup Group_Device
			 */
			extern bool USB_RemoteWakeupEnabled;
			
			/** Indicates if the device is currently being powered by its own power supply, rather than being
			 *  powered by the host's USB supply. This flag should remain cleared if the device does not
			 *  support self powered mode, as indicated in the device descriptors.
			 *
			 *  \ingroup Group_Device
			 */
			extern bool USB_CurrentlySelfPowered;
	
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		#if defined(USE_RAM_DESCRIPTORS) && defined(USE_EEPROM_DESCRIPTORS)
			#error USE_RAM_DESCRIPTORS and USE_EEPROM_DESCRIPTORS are mutually exclusive.
		#endif
	
		/* Function Prototypes: */
			void USB_Device_ProcessControlPacket(void);
			
			#if defined(INCLUDE_FROM_DEVCHAPTER9_C)
				static void USB_Device_SetAddress(void);
				static void USB_Device_SetConfiguration(void);
				static void USB_Device_GetConfiguration(void);
				static void USB_Device_GetDescriptor(void);
				static void USB_Device_GetStatus(void);
				static void USB_Device_ClearSetFeature(void);
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif
