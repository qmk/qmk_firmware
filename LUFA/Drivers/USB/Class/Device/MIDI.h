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

/** \ingroup Group_USBClassMIDI
 *  @defgroup Group_USBClassMIDIDevice MIDI Class Device Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/MIDI.c
 *
 *  \section Module Description
 *  Device Mode USB Class driver framework interface, for the MIDI USB Class driver.
 *
 *  @{
 */

#ifndef _MIDI_CLASS_DEVICE_H_
#define _MIDI_CLASS_DEVICE_H_

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/MIDI.h"
		#include "Audio.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Type Define: */
			/** Class state structure. An instance of this structure should be made for each MIDI interface
			 *  within the user application, and passed to each of the MIDI class driver functions as the
			 *  MIDIInterfaceInfo parameter. This stores each MIDI interface's configuration and state information.
			 */
			typedef struct
			{
				const struct
				{
					uint8_t  StreamingInterfaceNumber; /**< Index of the Audio Streaming interface within the device this structure controls */

					uint8_t  DataINEndpointNumber; /**< Endpoint number of the incomming MIDI data, if available (zero if unused) */
					uint16_t DataINEndpointSize; /**< Size in bytes of the incomming MIDI data endpoint, if available (zero if unused) */

					uint8_t  DataOUTEndpointNumber; /**< Endpoint number of the outgoing MIDI data, if available (zero if unused) */
					uint16_t DataOUTEndpointSize; /**< Size in bytes of the outgoing MIDI data endpoint, if available (zero if unused) */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */									 
				struct
				{
					// No state information for this class yet
				} State; /**< State data for the USB class interface within the device. All elements in this section
				          *   are reset to their defaults when the interface is enumerated.
				          */
			} USB_ClassInfo_MIDI_Device_t;	
	
		/* Function Prototypes: */
			/** Configures the endpoints of a given MIDI interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_Device_ConfigurationChanged() event so that the endpoints are configured when the configuration
			 *  containing the given MIDI interface is selected.
			 *
			 *  \param[in,out] MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state.
			 *
			 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
			 */
			bool MIDI_Device_ConfigureEndpoints(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Processes incomming control requests from the host, that are directed to the given MIDI class interface. This should be
			 *  linked to the library \ref EVENT_USB_Device_UnhandledControlRequest() event.
			 *
			 *  \param[in,out] MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state.
			 */		
			void MIDI_Device_ProcessControlRequest(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** General management task for a given MIDI class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state.
			 */
			void MIDI_Device_USBTask(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a MIDI event packet to the host. If no host is connected, the event packet is discarded.
			 *
			 *  \param[in,out] MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state.
			 *  \param[in] Event  Pointer to a populated USB_MIDI_EventPacket_t structure containing the MIDI event to send
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum			 
			 */
			uint8_t MIDI_Device_SendEventPacket(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo,
			                                    MIDI_EventPacket_t* const Event) ATTR_NON_NULL_PTR_ARG(1, 2);

			/** Receives a MIDI event packet from the host.
			 *
			 *  \param[in,out] MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state.
			 *  \param[out] Event  Pointer to a USB_MIDI_EventPacket_t structure where the received MIDI event is to be placed
			 *
			 *  \return Boolean true if a MIDI event packet was received, false otherwise
			 */
			bool MIDI_Device_ReceiveEventPacket(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo,
			                                    MIDI_EventPacket_t* const Event) ATTR_NON_NULL_PTR_ARG(1, 2);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
