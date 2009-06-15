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

/** \ingroup Group_USBClassRNDIS
 *  @defgroup Group_USBClassRNDISDevice RNDIS Class Device Mode Driver
 *
 *  \section Module Description
 *  Device Mode USB Class driver framework interface, for the RNDIS USB Class driver.
 *
 *  @{
 */

#ifndef _RNDIS_CLASS_DEVICE_H_
#define _RNDIS_CLASS_DEVICE_H_

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/RNDIS.h"
		#include "RNDISConstants.h"
		
		#include <string.h>
	
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Function Prototypes: */
			/** Configures the endpoints of a given RNDIS interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_ConfigurationChanged() event so that the endpoints are configured when the configuration
			 *  containing the given HID interface is selected.
			 *
			 *  \param RNDISInterfaceInfo  Pointer to a structure containing a RNDIS Class configuration and state.
			 *
			 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
			 */
			bool RNDIS_Device_ConfigureEndpoints(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo);

			/** Processes incomming control requests from the host, that are directed to the given RNDIS class interface. This should be
			 *  linked to the library \ref EVENT_USB_UnhandledControlPacket() event.
			 *
			 *  \param RNDISInterfaceInfo  Pointer to a structure containing a RNDIS Class configuration and state.
			 */		
			void RNDIS_Device_ProcessControlPacket(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo);
			
			/** General management task for a given HID class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param RNDISInterfaceInfo  Pointer to a structure containing a RNDIS Class configuration and state.
			 */
			void RNDIS_Device_USBTask(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo);
		
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
		#if defined(INCLUDE_FROM_RNDIS_CLASS_DEVICE_C)
			static void RNDIS_Device_ProcessRNDISControlMessage(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo);
			static bool RNDIS_Device_ProcessNDISQuery(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo, 
			                                          uint32_t OId, void* QueryData, uint16_t QuerySize,
										              void* ResponseData, uint16_t* ResponseSize);
			static bool RNDIS_Device_ProcessNDISSet(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo, uint32_t OId,
			                                        void* SetData, uint16_t SetSize);	
		#endif
		
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
