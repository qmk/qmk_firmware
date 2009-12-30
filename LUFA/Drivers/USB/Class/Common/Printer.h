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

/** \ingroup Group_USBClassMS
 *  @defgroup Group_USBClassPrinterCommon  Common Class Definitions
 *
 *  \section Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  Printer Class.
 *
 *  @{
 */

#ifndef _PRINTER_CLASS_COMMON_H_
#define _PRINTER_CLASS_COMMON_H_

	/* Includes: */
		#include "../../USB.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Macros: */
		/** Port status mask for a printer device, indicating that an error has *not* occurred. */
		#define PRNT_PORTSTATUS_NOTERROR    (1 << 3)

		/** Port status mask for a printer device, indicating that the device is currently selected. */
		#define PRNT_PORTSTATUS_SELECT      (1 << 4)

		/** Port status mask for a printer device, indicating that the device is currently out of paper. */
		#define PRNT_PORTSTATUS_PAPEREMPTY  (1 << 5)
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
