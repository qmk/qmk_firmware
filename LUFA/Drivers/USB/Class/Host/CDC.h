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

/** \ingroup Group_USBClassCDC
 *  @defgroup Group_USBClassCDCHost CDC Class Host Mode Driver
 *
 *  \section Module Description
 *  Host Mode USB Class driver framework interface, for the CDC USB Class driver.
 *
 *  @{
 */

#ifndef __CDC_CLASS_HOST_H__
#define __CDC_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/CDC.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Function Prototypes: */
		#if defined(INCLUDE_FROM_CDC_CLASS_HOST_C)
			static uint8_t CDC_Host_ProcessConfigDescriptor(void);
			static uint8_t DComp_CDC_Host_NextCDCControlInterface(void* CurrentDescriptor);
			static uint8_t DComp_CDC_Host_NextCDCDataInterface(void* CurrentDescriptor);
			static uint8_t DComp_CDC_Host_NextInterfaceCDCDataEndpoint(void* CurrentDescriptor);
		#endif
		
		void CDC_Host_Task(void);
		
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
