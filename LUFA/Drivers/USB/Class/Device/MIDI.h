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

/** \ingroup Group_USBDeviceClassDrivers
 *  @defgroup Group_USBClassMIDIDevice MIDI Device Class Driver - LUFA/Drivers/Class/Device/MIDI.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/MIDI.c
 *
 *  \section Module Description
 *  Functions, macros, variables, enums and types related to the management of USB MIDI Class interfaces
 *  within a USB device. Note that the MIDI class is actually a special case of the regular Audio class,
 *  thus this module depends on structure definitions from the \ref Group_USBClassAudioDevice class driver module.
 *
 *  @{
 */

#ifndef _MIDI_CLASS_H_
#define _MIDI_CLASS_H_

	/* Includes: */
		#include "../../USB.h"
		#include "Audio.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Macros: */
		/** Audio class descriptor subtype value for a Audio class specific MIDI input jack descriptor. */
		#define DSUBTYPE_InputJack          0x02

		/** Audio class descriptor subtype value for a Audio class specific MIDI output jack descriptor. */
		#define DSUBTYPE_OutputJack         0x03
		
		/** Audio class descriptor jack type value for an embedded (logical) MIDI input or output jack. */
		#define MIDI_JACKTYPE_EMBEDDED      0x01

		/** Audio class descriptor jack type value for an external (physical) MIDI input or output jack. */
		#define MIDI_JACKTYPE_EXTERNAL      0x02

		/** MIDI command for a note on (activation) event */
		#define MIDI_COMMAND_NOTE_ON        0x09

		/** MIDI command for a note off (deactivation) event */
		#define MIDI_COMMAND_NOTE_OFF       0x08

		/** Standard key press velocity value used for all note events */
		#define MIDI_STANDARD_VELOCITY      64
		
		/** Convenience macro. MIDI channels are numbered from 1-10 (natural numbers) however the logical channel
		 *  addresses are zero-indexed. This converts a natural MIDI channel number into the logical channel address.
		 *
		 *  \param channel  MIDI channel number to address
		 */
		#define MIDI_CHANNEL(channel)        (channel - 1)
		
	/* Type Defines: */
		/** Type define for an Audio class specific MIDI streaming interface descriptor. This indicates to the host
		 *  how MIDI the specification compliance of the device and the total length of the Audio class specific descriptors.
		 *  See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */
			
			uint16_t                  AudioSpecification; /**< Binary coded decimal value, indicating the supported Audio Class specification version */
			uint16_t                  TotalLength; /**< Total length of the Audio class specific descriptors, including this descriptor */
		} USB_AudioInterface_MIDI_AS_t;
		
		/** Type define for an Audio class specific MIDI IN jack. This gives information to the host on a MIDI input, either
		 *  a physical input jack, or a logical jack (receiving input data internally, or from the host via an endpoint).
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */

			uint8_t                   JackType; /**< Type of jack, one of the JACKTYPE_* mask values */
			uint8_t                   JackID; /**< ID value of this jack - must be a unique value within the device */
			
			uint8_t                   JackStrIndex; /**< Index of a string descriptor describing this descriptor within the device */
		} USB_MIDI_In_Jack_t;

		/** Type define for an Audio class specific MIDI OUT jack. This gives information to the host on a MIDI output, either
		 *  a physical output jack, or a logical jack (sending output data internally, or to the host via an endpoint).
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */

			uint8_t                   JackType; /**< Type of jack, one of the JACKTYPE_* mask values */
			uint8_t                   JackID; /**< ID value of this jack - must be a unique value within the device */
			
			uint8_t                   NumberOfPins; /**< Number of output channels within the jack, either physical or logical */
			uint8_t                   SourceJackID[1]; /**< ID of each output pin's source data jack */
			uint8_t                   SourcePinID[1]; /**< Pin number in the input jack of each output pin's source data */
			
			uint8_t                   JackStrIndex; /**< Index of a string descriptor describing this descriptor within the device */
		} USB_MIDI_Out_Jack_t;
		
		/** Type define for an Audio class specific extended MIDI jack endpoint descriptor. This contains extra information
		 *  on the usage of MIDI endpoints used to stream MIDI events in and out of the USB Audio device, and follows an Audio
		 *  class specific extended MIDI endpoint descriptor. See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */

			uint8_t                   TotalEmbeddedJacks; /**< Total number of jacks inside this endpoint */
			uint8_t                   AssociatedJackID[1]; /**< IDs of each jack inside the endpoint */
		} USB_MIDI_Jack_Endpoint_t;

		/** Type define for a USB MIDI event packet, used to encapsulate sent and received MIDI messages from a USB MIDI interface. */
		typedef struct
		{
			unsigned char Command     : 4; /**< MIDI command being sent or received in the event packet */
			unsigned char CableNumber : 4; /**< Virtual cable number of the event being sent or received in the given MIDI interface */
			
			uint8_t Data1; /**< First byte of data in the MIDI event */
			uint8_t Data2; /**< Second byte of data in the MIDI event */
			uint8_t Data3; /**< Third byte of data in the MIDI event */		
		} USB_MIDI_EventPacket_t;

		/** Class state structure. An instance of this structure should be made for each MIDI interface
		 *  within the user application, and passed to each of the MIDI class driver functions as the
		 *  MIDIInterfaceInfo parameter. The contents of this structure should be set to their correct
		 *  values when used, or ommitted to force the library to use default values.
		 */
		typedef struct
		{
			uint8_t  StreamingInterfaceNumber; /**< Index of the Audio Streaming interface within the device this structure controls */

			uint8_t  DataINEndpointNumber; /**< Endpoint number of the incomming MIDI data, if available (zero if unused) */
			uint16_t DataINEndpointSize; /**< Size in bytes of the incomming MIDI data endpoint, if available (zero if unused) */

			uint8_t  DataOUTEndpointNumber; /**< Endpoint number of the outgoing MIDI data, if available (zero if unused) */
			uint16_t DataOUTEndpointSize; /**< Size in bytes of the outgoing MIDI data endpoint, if available (zero if unused) */
		} USB_ClassInfo_MIDI_t;
		
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
