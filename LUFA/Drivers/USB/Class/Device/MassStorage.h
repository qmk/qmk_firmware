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

/** \ingroup Group_USBClassMS
 *  @defgroup Group_USBClassMSDevice Mass Storage Class Device Mode Driver
 *
 *  \section Module Description
 *  Device Mode USB Class driver framework interface, for the Mass Storage USB Class driver.
 *
 *  @{
 */

#ifndef _MS_CLASS_DEVICE_H_
#define _MS_CLASS_DEVICE_H_

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/MassStorage.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Function Prototypes: */
			/** Configures the endpoints of a given Mass Storage interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_ConfigurationChanged() event so that the endpoints are configured when the configuration
			 *  containing the given Mass Storage interface is selected.
			 *
			 *  \param MSInterfaceInfo  Pointer to a structure containing a Mass Storage Class configuration and state.
			 *
			 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
			 */
			bool MS_Device_ConfigureEndpoints(USB_ClassInfo_MS_t* MSInterfaceInfo);
			
			/** Processes incomming control requests from the host, that are directed to the given Mass Storage class interface. This should be
			 *  linked to the library \ref EVENT_USB_UnhandledControlPacket() event.
			 *
			 *  \param MSInterfaceInfo  Pointer to a structure containing a Mass Storage Class configuration and state.
			 */		
			void MS_Device_ProcessControlPacket(USB_ClassInfo_MS_t* MSInterfaceInfo);

			/** General management task for a given Mass Storage class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param MSInterfaceInfo  Pointer to a structure containing a Mass Storage configuration and state.
			 */
			void MS_Device_USBTask(USB_ClassInfo_MS_t* MSInterfaceInfo);
			
			/** Mass Storage class driver callback for the user processing of a received SCSI command. This callback will fire each time the
			 *  host sends a SCSI command which requires processing by the user application. Inside this callback the user is responsible
			 *  for the processing of the received SCSI command from the host. The SCSI command is available in the CommandBlock structure
			 *  inside the Mass Storage class state structure passed as a parameter to the callback function.
			 *
			 *  \param MSInterfaceInfo  Pointer to a structure containing a Mass Storage Class configuration and state.
			 *
			 *  \return Boolean true if the SCSI command was successfully processed, false otherwise
			 */
			bool CALLBACK_MS_Device_SCSICommandReceived(USB_ClassInfo_MS_t* MSInterfaceInfo);
		
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_MS_CLASS_DEVICE_C)
				static void    MS_Device_ReturnCommandStatus(USB_ClassInfo_MS_t* MSInterfaceInfo);
				static bool    MS_Device_ReadInCommandBlock(USB_ClassInfo_MS_t* MSInterfaceInfo);
				static uint8_t StreamCallback_MS_Device_AbortOnMassStoreReset(void);
			#endif
		
	#endif
		
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
