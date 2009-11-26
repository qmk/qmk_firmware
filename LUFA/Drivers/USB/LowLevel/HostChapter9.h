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

#ifndef __HOSTCHAPTER9_H__
#define __HOSTCHAPTER9_H__

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>
		
		#include "LowLevel.h"
		#include "../HighLevel/USBMode.h"
		#include "../HighLevel/StdRequestType.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Enums: */
			/** Enum for the \ref USB_Host_SendControlRequest() return code, indicating the reason for the error
			 *  if the transfer of the request is unsuccessful.
			 *
			 *  \ingroup Group_PipeControlReq
			 */
			enum USB_Host_SendControlErrorCodes_t
			{
				HOST_SENDCONTROL_Successful         = 0, /**< No error occurred in the request transfer. */
				HOST_SENDCONTROL_DeviceDisconnected = 1, /**< The attached device was disconnected during the
				                                        *   request transfer.
				                                        */
				HOST_SENDCONTROL_PipeError          = 2, /**< An error occurred in the pipe while sending the request. */
				HOST_SENDCONTROL_SetupStalled       = 3, /**< The attached device stalled the request, usually
				                                        *   indicating that the request is unsupported on the device.
				                                        */
				HOST_SENDCONTROL_SoftwareTimeOut    = 4, /**< The request or data transfer timed out. */
			};
			
		/* Function Prototypes: */
			/** Sends the request stored in the \ref USB_ControlRequest global structure to the attached device,
			 *  and transfers the data stored in the buffer to the device, or from the device to the buffer
			 *  as requested. The transfer is made on the currently selected pipe.
			 *
			 *  \ingroup Group_PipeControlReq
			 *
			 *  \param[in] BufferPtr  Pointer to the start of the data buffer if the request has a data stage, or
			 *                        NULL if the request transfers no data to or from the device.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum to indicate the result.
			 */
			uint8_t USB_Host_SendControlRequest(void* BufferPtr);
			
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Enums: */
			enum USB_WaitForTypes_t
			{
				USB_HOST_WAITFOR_SetupSent,
				USB_HOST_WAITFOR_InReceived,
				USB_HOST_WAITFOR_OutReady,
			};
	
		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_HOSTCHAPTER9_C)
				static uint8_t USB_Host_WaitForIOS(const uint8_t WaitType);
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif
