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
 *  \brief Common definitions and declarations for the library USB MIDI Class driver.
 *
 *  Common definitions and declarations for the library USB MIDI Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the class driver
 *        dispatch header located in LUFA/Drivers/USB/Class/MIDI.h.
 */

/** \ingroup Group_USBClassMIDI
 *  @defgroup Group_USBClassMIDICommon  Common Class Definitions
 *
 *  \section Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  MIDI Class.
 *
 *  @{
 */

#ifndef _MIDI_CLASS_COMMON_H_
#define _MIDI_CLASS_COMMON_H_

	/* Macros: */
		#define __INCLUDE_FROM_AUDIO_DRIVER

	/* Includes: */
		#include "../../USB.h"
		#include "Audio.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_MIDI_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/Class/MIDI.h instead.
		#endif
		
	/* Macros: */
		/** Audio class descriptor subtype value for a Audio class-specific MIDI input jack descriptor. */
		#define DSUBTYPE_InputJack          0x02

		/** Audio class descriptor subtype value for a Audio class-specific MIDI output jack descriptor. */
		#define DSUBTYPE_OutputJack         0x03
		
		/** Audio class descriptor jack type value for an embedded (logical) MIDI input or output jack. */
		#define MIDI_JACKTYPE_EMBEDDED      0x01

		/** Audio class descriptor jack type value for an external (physical) MIDI input or output jack. */
		#define MIDI_JACKTYPE_EXTERNAL      0x02

		/** MIDI command for a note on (activation) event. */
		#define MIDI_COMMAND_NOTE_ON        0x90

		/** MIDI command for a note off (deactivation) event. */
		#define MIDI_COMMAND_NOTE_OFF       0x80

		/** Standard key press velocity value used for all note events. */
		#define MIDI_STANDARD_VELOCITY      64
		
		/** Convenience macro. MIDI channels are numbered from 1-10 (natural numbers) however the logical channel
		 *  addresses are zero-indexed. This converts a natural MIDI channel number into the logical channel address.
		 *
		 *  \param[in] channel  MIDI channel number to address.
		 */
		#define MIDI_CHANNEL(channel)        ((channel) - 1)
		
	/* Type Defines: */
		/** \brief MIDI class-specific Streaming Interface Descriptor.
		 *
		 *  Type define for an Audio class-specific MIDI streaming interface descriptor. This indicates to the host
		 *  how MIDI the specification compliance of the device and the total length of the Audio class-specific descriptors.
		 *  See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors. */
			
			uint16_t                  AudioSpecification; /**< Binary coded decimal value, indicating the supported Audio Class
			                                               *   specification version.
			                                               */
			uint16_t                  TotalLength; /**< Total length of the Audio class-specific descriptors, including this descriptor. */
		} USB_MIDI_AudioInterface_AS_t;
		
		/** \brief MIDI class-specific Input Jack Descriptor.
		 *
		 *  Type define for an Audio class-specific MIDI IN jack. This gives information to the host on a MIDI input, either
		 *  a physical input jack, or a logical jack (receiving input data internally, or from the host via an endpoint).
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors. */

			uint8_t                   JackType; /**< Type of jack, one of the JACKTYPE_* mask values. */
			uint8_t                   JackID; /**< ID value of this jack - must be a unique value within the device. */
			
			uint8_t                   JackStrIndex; /**< Index of a string descriptor describing this descriptor within the device. */
		} USB_MIDI_In_Jack_t;

		/** \brief MIDI class-specific Output Jack Descriptor.
		 *
		 *  Type define for an Audio class-specific MIDI OUT jack. This gives information to the host on a MIDI output, either
		 *  a physical output jack, or a logical jack (sending output data internally, or to the host via an endpoint).
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors. */

			uint8_t                   JackType; /**< Type of jack, one of the JACKTYPE_* mask values. */
			uint8_t                   JackID; /**< ID value of this jack - must be a unique value within the device. */
			
			uint8_t                   NumberOfPins; /**< Number of output channels within the jack, either physical or logical. */
			uint8_t                   SourceJackID[1]; /**< ID of each output pin's source data jack. */
			uint8_t                   SourcePinID[1]; /**< Pin number in the input jack of each output pin's source data. */
			
			uint8_t                   JackStrIndex; /**< Index of a string descriptor describing this descriptor within the device. */
		} USB_MIDI_Out_Jack_t;
		
		/** \brief Audio class-specific Jack Endpoint Descriptor.
		 *
		 *  Type define for an Audio class-specific extended MIDI jack endpoint descriptor. This contains extra information
		 *  on the usage of MIDI endpoints used to stream MIDI events in and out of the USB Audio device, and follows an Audio
		 *  class-specific extended MIDI endpoint descriptor. See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors. */

			uint8_t                   TotalEmbeddedJacks; /**< Total number of jacks inside this endpoint. */
			uint8_t                   AssociatedJackID[1]; /**< IDs of each jack inside the endpoint. */
		} USB_MIDI_Jack_Endpoint_t;

		/** \brief MIDI Class Driver Event Packet.
		 *
		 *  Type define for a USB MIDI event packet, used to encapsulate sent and received MIDI messages from a USB MIDI interface.
		 */
		typedef struct
		{
			unsigned char Command     : 4; /**< Upper nibble of the MIDI command being sent or received in the event packet. */
			unsigned char CableNumber : 4; /**< Virtual cable number of the event being sent or received in the given MIDI interface. */
			
			uint8_t Data1; /**< First byte of data in the MIDI event. */
			uint8_t Data2; /**< Second byte of data in the MIDI event. */
			uint8_t Data3; /**< Third byte of data in the MIDI event. */		
		} MIDI_EventPacket_t;

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
