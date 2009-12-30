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
 *  Header file for Descriptors.c.
 */
 
#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include <avr/pgmspace.h>

	/* Macros: */
		/** Descriptor header constant to indicate a Audio class interface descriptor. */
		#define DTYPE_AudioInterface        0x24

		/** Descriptor header constant to indicate a Audio class endpoint descriptor. */
		#define DTYPE_AudioEndpoint         0x25

		/** Audio class descriptor subtype value for a Audio class specific header descriptor. */
		#define DSUBTYPE_Header             0x01

		/** Audio class descriptor subtype value for a Audio class specific MIDI input jack descriptor. */
		#define DSUBTYPE_InputJack          0x02

		/** Audio class descriptor subtype value for a Audio class specific MIDI output jack descriptor. */
		#define DSUBTYPE_OutputJack         0x03

		/** Audio class descriptor subtype value for a general Audio class specific descriptor. */
		#define DSUBTYPE_General            0x01

		/** Audio class descriptor jack type value for an embedded (logical) MIDI input or output jack. */
		#define JACKTYPE_EMBEDDED           0x01

		/** Audio class descriptor jack type value for an external (physical) MIDI input or output jack. */
		#define JACKTYPE_EXTERNAL           0x02
		
		/** Endpoint number of the MIDI streaming data OUT endpoint, for host-to-device data transfers. */
		#define MIDI_STREAM_OUT_EPNUM       1

		/** Endpoint number of the MIDI streaming data IN endpoint, for device-to-host data transfers. */
		#define MIDI_STREAM_IN_EPNUM        2

		/** Endpoint size in bytes of the Audio isochronous streaming data IN and OUT endpoints. */
		#define MIDI_STREAM_EPSIZE          64
		
	/* Type Defines: */
		/** Type define for an Audio class specific interface descriptor. This follows a regular interface descriptor to
		 *  supply extra information about the audio device's layout to the host. See the USB Audio specification for more
		 *  details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */

			uint16_t                  ACSpecification; /** Binary coded decimal value, indicating the supported Audio Class specification version */
			uint16_t                  TotalLength; /** Total length of the Audio class specific control descriptors, including this descriptor */
			
			uint8_t                   InCollection; /** Total number of audio class interfaces within this device */
			uint8_t                   InterfaceNumbers[1]; /** Interface numbers of each audio interface */
		} USB_Audio_Interface_AC_t;
		
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
		} USB_Audio_Interface_MIDI_AS_t;
		
		/** Type define for an Audio class specific endpoint descriptor. This contains a regular endpoint 
		 *  descriptor with a few Audio-class specific extensions. See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Endpoint_t Endpoint; /**< Standard endpoint descriptor describing the audio endpoint */

			uint8_t                   Refresh; /**< Always set to zero */
			uint8_t                   SyncEndpointNumber; /**< Endpoint address to send synchronization information to, if needed (zero otherwise) */
		} USB_Audio_StreamEndpoint_Std_t;

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

		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;
			USB_Descriptor_Interface_t            AudioControlInterface;
			USB_Audio_Interface_AC_t              AudioControlInterface_SPC;
			USB_Descriptor_Interface_t            AudioStreamInterface;
			USB_Audio_Interface_MIDI_AS_t         AudioStreamInterface_SPC;
			USB_MIDI_In_Jack_t                    MIDI_In_Jack_Emb;
			USB_MIDI_In_Jack_t                    MIDI_In_Jack_Ext;
			USB_MIDI_Out_Jack_t                   MIDI_Out_Jack_Emb;
			USB_MIDI_Out_Jack_t                   MIDI_Out_Jack_Ext;
			USB_Audio_StreamEndpoint_Std_t        MIDI_In_Jack_Endpoint;
			USB_MIDI_Jack_Endpoint_t              MIDI_In_Jack_Endpoint_SPC;
			USB_Audio_StreamEndpoint_Std_t        MIDI_Out_Jack_Endpoint;
			USB_MIDI_Jack_Endpoint_t              MIDI_Out_Jack_Endpoint_SPC;
		} USB_Descriptor_Configuration_t;
		
	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, void** const DescriptorAddress)
											ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
