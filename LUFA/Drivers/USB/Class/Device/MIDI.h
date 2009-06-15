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
		/* Function Prototypes: */
			/** Configures the endpoints of a given MIDI interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_ConfigurationChanged() event so that the endpoints are configured when the configuration
			 *  containing the given MIDI interface is selected.
			 *
			 *  \param MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state.
			 *
			 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
			 */
			bool MIDI_Device_ConfigureEndpoints(USB_ClassInfo_MIDI_t* MIDIInterfaceInfo);
			
			/** Processes incomming control requests from the host, that are directed to the given MIDI class interface. This should be
			 *  linked to the library \ref EVENT_USB_UnhandledControlPacket() event.
			 *
			 *  \param MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state.
			 */		
			void MIDI_Device_ProcessControlPacket(USB_ClassInfo_MIDI_t* MIDIInterfaceInfo);

			/** General management task for a given MIDI class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state.
			 */
			void MIDI_Device_USBTask(USB_ClassInfo_MIDI_t* MIDIInterfaceInfo);

			/** Sends a MIDI event packet to the host. If no host is connected, the event packet is discarded.
			 *
			 *  \param MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state.
			 *  \param Event  Pointer to a populated USB_MIDI_EventPacket_t structure containing the MIDI event to send
			 */
			void MIDI_Device_SendEventPacket(USB_ClassInfo_MIDI_t* MIDIInterfaceInfo, USB_MIDI_EventPacket_t* Event);

			/** Receives a MIDI event packet from the host.
			 *
			 *  \param MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state.
			 *  \param Event  Pointer to a USB_MIDI_EventPacket_t structure where the received MIDI event is to be placed
			 *
			 *  \return Boolean true if a MIDI event packet was received, false otherwise
			 */
			bool MIDI_Device_ReceiveEventPacket(USB_ClassInfo_MIDI_t* MIDIInterfaceInfo, USB_MIDI_EventPacket_t* Event);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
