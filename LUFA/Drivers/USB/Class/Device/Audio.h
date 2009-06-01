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

#ifndef _AUDIO_CLASS_H_
#define _AUDIO_CLASS_H_

	/* Includes: */
		#include "../../USB.h"

		#include <string.h>

	/* Macros: */

	/* Enums: */

	/* Type Defines: */
		typedef struct
		{
			uint8_t  InterfaceNumber;

			uint8_t  DataINEndpointNumber;
			uint16_t DataINEndpointSize;

			uint8_t  DataOUTEndpointNumber;
			uint16_t DataOUTEndpointSize;

			bool     InterfaceEnabled;
		} USB_ClassInfo_Audio_t;
		
	/* Function Prototypes: */
		bool     USB_Audio_ConfigureEndpoints(USB_ClassInfo_Audio_t* AudioInterfaceInfo);
		void     USB_Audio_ProcessControlPacket(USB_ClassInfo_Audio_t* AudioInterfaceInfo);
		void     USB_Audio_USBTask(USB_ClassInfo_Audio_t* AudioInterfaceInfo);
		
		int8_t   USB_Audio_ReadSample8(void);
		int16_t  USB_Audio_ReadSample16(void);
		int32_t  USB_Audio_ReadSample24(void);
		void     USB_Audio_WriteSample8(int8_t Sample);
		void     USB_Audio_WriteSample16(int16_t Sample);
		void     USB_Audio_WriteSample24(int32_t Sample);
		bool     USB_Audio_IsSampleReceived(USB_ClassInfo_Audio_t* AudioInterfaceInfo);
		bool     USB_Audio_IsReadyForNextSample(USB_ClassInfo_Audio_t* AudioInterfaceInfo);
#endif
