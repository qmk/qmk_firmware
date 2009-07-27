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
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/RNDIS.c
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
		/* Type Defines: */					 
			/** Class state structure. An instance of this structure should be made for each RNDIS interface
			 *  within the user application, and passed to each of the RNDIS class driver functions as the
			 *  RNDISInterfaceInfo parameter. This stores each RNDIS interface's configuration and state information.
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
					
					char*         AdapterVendorDescription; /**< String description of the adapter vendor */
					MAC_Address_t AdapterMACAddress; /**< MAC address of the adapter */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					uint8_t  RNDISMessageBuffer[RNDIS_MESSAGE_BUFFER_SIZE]; /**< Buffer to hold RNDIS messages to and from the host,
																			 *   managed by the class driver
																			 */
					bool     ResponseReady; /**< Internal flag indicating if a RNDIS message is waiting to be returned to the host */
					uint8_t  CurrRNDISState; /**< Current RNDIS state of the adapter, a value from the RNDIS_States_t enum */
					uint32_t CurrPacketFilter; /**< Current packet filter mode, used internally by the class driver */
					Ethernet_Frame_Info_t FrameIN; /**< Structure holding the last received Ethernet frame from the host, for user
													*   processing
													*/
					Ethernet_Frame_Info_t FrameOUT; /**< Structure holding the next Ethernet frame to send to the host, populated by the
													 *   user application
													 */
				} State; /**< State data for the USB class interface within the device. All elements in this section
				          *   are reset to their defaults when the interface is enumerated.
				          */
			} USB_ClassInfo_RNDIS_Device_t;
	
		/* Function Prototypes: */
			/** Configures the endpoints of a given RNDIS interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_ConfigurationChanged() event so that the endpoints are configured when the configuration
			 *  containing the given HID interface is selected.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing a RNDIS Class configuration and state.
			 *
			 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
			 */
			bool RNDIS_Device_ConfigureEndpoints(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo);

			/** Processes incomming control requests from the host, that are directed to the given RNDIS class interface. This should be
			 *  linked to the library \ref EVENT_USB_UnhandledControlPacket() event.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing a RNDIS Class configuration and state.
			 */		
			void RNDIS_Device_ProcessControlPacket(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo);
			
			/** General management task for a given HID class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing a RNDIS Class configuration and state.
			 */
			void RNDIS_Device_USBTask(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo);
		
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
		#if defined(INCLUDE_FROM_RNDIS_CLASS_DEVICE_C)
			static void RNDIS_Device_ProcessRNDISControlMessage(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo);
			static bool RNDIS_Device_ProcessNDISQuery(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo, 
			                                          const uint32_t OId, void* const QueryData, const uint16_t QuerySize,
										              void* ResponseData, uint16_t* const ResponseSize);
			static bool RNDIS_Device_ProcessNDISSet(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo, const uint32_t OId,
			                                        void* SetData, const uint16_t SetSize);	
		#endif
		
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
