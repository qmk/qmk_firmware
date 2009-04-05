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
 *  Master include file for the library USB functionality. This file should be included in all user projects making
 *  use of the USB portions of the library, instead of including any headers in the USB/LowLevel or USB/HighLevel
 *  directories.
 *
 *  Class specific utility files in USB/Class/ must still be included manually, as they are not normally part of
 *  the USB library unless desired by the library user.
 */

#ifndef __USB_H__
#define __USB_H__

	/* Preprocessor Checks: */
		#if (!(defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB647__)) && defined(USB_HOST_ONLY))
			#error USB_HOST_ONLY is not available for the currently selected USB AVR model.
		#endif
		
		#if (!(defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB647__) ||  \
		       defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) ||  \
			   defined(__AVR_AT90USB162__)  || defined(__AVR_AT90USB82__)  ||  \
			   defined(__AVR_ATmega16U4__)  || defined(__AVR_ATmega32U4__) ||  \
			   defined(__AVR_ATmega32U6__)))
			#error The currently selected AVR model is not supported under the USB component of the LUFA library.
		#endif
		
	/* Includes: */
		#include "Highlevel/USBMode.h"
		#include "HighLevel/USBTask.h"
		#include "HighLevel/USBInterrupt.h"
		#include "HighLevel/Events.h"
		#include "HighLevel/StdDescriptors.h"

		#include "LowLevel/LowLevel.h"
	
		#if defined(USB_CAN_BE_HOST) || defined(__DOXYGEN__)
			#include "LowLevel/Host.h"
			#include "LowLevel/HostChapter9.h"
			#include "LowLevel/Pipe.h"
		#endif
		
		#if defined(USB_CAN_BE_DEVICE) || defined(__DOXYGEN__)
			#include "LowLevel/Device.h"
			#include "LowLevel/DevChapter9.h"
			#include "LowLevel/Endpoint.h"
		#endif
		
		#if defined(USB_CAN_BE_BOTH) || defined(__DOXYGEN__)
			#include "LowLevel/OTG.h"
		#endif
		
#endif

