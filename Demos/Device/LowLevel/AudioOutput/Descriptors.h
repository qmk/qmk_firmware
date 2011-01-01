/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
		/** Endpoint number of the Audio isochronous streaming data endpoint. */
		#define AUDIO_STREAM_EPNUM           1

		/** Endpoint size in bytes of the Audio isochronous streaming data endpoint. The Windows audio stack requires
		 *  at least 192 bytes for correct output, thus the smaller 128 byte maximum endpoint size on some of the smaller
		 *  USB AVR models will result in unavoidable distorted output.
		 */
		#define AUDIO_STREAM_EPSIZE          ENDPOINT_MAX_SIZE(AUDIO_STREAM_EPNUM)

		/** Sample frequency of the data being transmitted through the streaming endpoint. */
		#define AUDIO_SAMPLE_FREQUENCY       48000

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t     Config;
			USB_Descriptor_Interface_t                Audio_ControlInterface;
			USB_Audio_Descriptor_Interface_AC_t       Audio_ControlInterface_SPC;
			USB_Audio_Descriptor_InputTerminal_t      Audio_InputTerminal;
			USB_Audio_Descriptor_OutputTerminal_t     Audio_OutputTerminal;
			USB_Descriptor_Interface_t                Audio_StreamInterface_Alt0;
			USB_Descriptor_Interface_t                Audio_StreamInterface_Alt1;
			USB_Audio_Descriptor_Interface_AS_t       Audio_StreamInterface_SPC;
			USB_Audio_Descriptor_Format_t             Audio_AudioFormat;
			USB_Audio_Descriptor_StreamEndpoint_Std_t Audio_StreamEndpoint;
			USB_Audio_Descriptor_StreamEndpoint_Spc_t Audio_StreamEndpoint_SPC;
		} USB_Descriptor_Configuration_t;

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint8_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
