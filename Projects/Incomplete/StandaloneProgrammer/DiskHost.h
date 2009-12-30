/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** \file
 *
 *  Header file for DiskHost.c.
 */

#ifndef _DISK_HOST_H_
#define _DISK_HOST_H_

	/* Includes: */
		#include <avr/io.h>
		
		#include "Descriptors.h"
		#include "StandaloneProgrammer.h"

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/USB/Class/MassStorage.h>

	/* External Variables: */
		#if defined(USB_CAN_BE_HOST)
		extern USB_ClassInfo_MS_Host_t DiskHost_MS_Interface;
		#endif

	/* Function Prototypes: */
		#if defined(USB_CAN_BE_HOST)
			void DiskHost_USBTask(void);
			
			void EVENT_USB_Host_DeviceAttached(void);
			void EVENT_USB_Host_DeviceUnattached(void);
		#endif

#endif
