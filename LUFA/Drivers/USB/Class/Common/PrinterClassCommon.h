/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Common definitions and declarations for the library USB Printer Class driver.
 *
 *  Common definitions and declarations for the library USB Printer Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassPrinter
 *  \defgroup Group_USBClassPrinterCommon  Common Class Definitions
 *
 *  \section Sec_ModDescription Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  Printer Class.
 *
 *  @{
 */

#ifndef _PRINTER_CLASS_COMMON_H_
#define _PRINTER_CLASS_COMMON_H_

	/* Includes: */
		#include "../../Core/StdDescriptors.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_PRINTER_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Macros: */
		/** \name Virtual Printer Status Line Masks */
		//@{
		/** Port status mask for a printer device, indicating that an error has *not* occurred. */
		#define PRNT_PORTSTATUS_NOTERROR    (1 << 3)

		/** Port status mask for a printer device, indicating that the device is currently selected. */
		#define PRNT_PORTSTATUS_SELECT      (1 << 4)

		/** Port status mask for a printer device, indicating that the device is currently out of paper. */
		#define PRNT_PORTSTATUS_PAPEREMPTY  (1 << 5)
		//@}

	/* Enums: */
		/** Enum for possible Class, Subclass and Protocol values of device and interface descriptors relating to the Printer
		 *  device class.
		 */
		enum PRNT_Descriptor_ClassSubclassProtocol_t
		{
			PRNT_CSCP_PrinterClass          = 0x07, /**< Descriptor Class value indicating that the device or interface
			                                         *   belongs to the Printer class.
			                                         */
			PRNT_CSCP_PrinterSubclass       = 0x01, /**< Descriptor Subclass value indicating that the device or interface
			                                         *   belongs to the Printer subclass.
			                                         */
			PRNT_CSCP_BidirectionalProtocol = 0x02, /**< Descriptor Protocol value indicating that the device or interface
			                                         *   belongs to the Bidirectional protocol of the Printer class.
			                                         */
		};

		/** Enum for the Printer class specific control requests that can be issued by the USB bus host. */
		enum PRNT_ClassRequests_t
		{
			PRNT_REQ_GetDeviceID            = 0x00, /**< Printer class-specific request to retrieve the Unicode ID
			                                         *   string of the device, containing the device's name, manufacturer
			                                         *   and supported printer languages.
			                                         */
			PRNT_REQ_GetPortStatus          = 0x01, /**< Printer class-specific request to get the current status of the
			                                         *   virtual printer port, for device selection and ready states.
			                                         */
			PRNT_REQ_SoftReset              = 0x02, /**< Printer class-specific request to reset the device, ready for new
			                                         *   printer commands.
			                                         */
		};

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

