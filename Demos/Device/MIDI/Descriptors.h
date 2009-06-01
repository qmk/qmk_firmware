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

/** \file
 *
 *  Header file for Descriptors.c.
 */
 
#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/USB/Class/Device/MIDI.h>

		#include <avr/pgmspace.h>

	/* Macros: */
		/** Endpoint number of the MIDI streaming data IN endpoint, for device-to-host data transfers. */
		#define MIDI_STREAM_IN_EPNUM        2

		/** Endpoint number of the MIDI streaming data OUT endpoint, for host-to-device data transfers. */
		#define MIDI_STREAM_OUT_EPNUM       1

		/** Endpoint size in bytes of the Audio isochronous streaming data IN and OUT endpoints. */
		#define MIDI_STREAM_EPSIZE          64
		
	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;
			USB_Descriptor_Interface_t            AudioControlInterface;
			USB_AudioInterface_AC_t               AudioControlInterface_SPC;
			USB_Descriptor_Interface_t            AudioStreamInterface;
			USB_AudioInterface_MIDI_AS_t          AudioStreamInterface_SPC;
			USB_MIDI_In_Jack_t                    MIDI_In_Jack_Emb;
			USB_MIDI_In_Jack_t                    MIDI_In_Jack_Ext;
			USB_MIDI_Out_Jack_t                   MIDI_Out_Jack_Emb;
			USB_MIDI_Out_Jack_t                   MIDI_Out_Jack_Ext;
			USB_AudioStreamEndpoint_Std_t         MIDI_In_Jack_Endpoint;
			USB_MIDI_Jack_Endpoint_t              MIDI_In_Jack_Endpoint_SPC;
			USB_AudioStreamEndpoint_Std_t         MIDI_Out_Jack_Endpoint;
			USB_MIDI_Jack_Endpoint_t              MIDI_Out_Jack_Endpoint_SPC;
		} USB_Descriptor_Configuration_t;
		
	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, void** const DescriptorAddress)
											ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
