/*
             LUFA Library
     Copyright (C) Dean Camera, 2015.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2015  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  \brief Master include file for the library USB Printer Class driver.
 *
 *  Master include file for the library USB Printer Class driver, for both host and device modes, where available.
 *
 *  This file should be included in all user projects making use of this optional class driver, instead of
 *  including any headers in the USB/ClassDriver/Device, USB/ClassDriver/Host or USB/ClassDriver/Common subdirectories.
 */

/** \ingroup Group_USBClassDrivers
 *  \defgroup Group_USBClassPrinter Printer Class Driver
 *  \brief USB class driver for the USB-IF Printer class standard.
 *
 *  \section Sec_USBClassPrinter_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/PrinterClassDevice.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *    - LUFA/Drivers/USB/Class/Host/PrinterClassHost.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_USBClassPrinter_ModDescription Module Description
 *  Printer Class Driver module. This module contains an internal implementation of the USB Printer Class, for the base
 *  USB Printer transport layer for USB Host mode only. Note that printers are free to implement whatever printer language
 *  they choose on top of this (e.g. Postscript), and so this driver exposes low level data transport functions only rather
 *  than high level raster or text functions. User applications can use this class driver instead of implementing the Printer
 *  class manually via the low-level LUFA APIs.
 *
 *  This module is designed to simplify the user code by exposing only the required interface needed to interface with
 *  Devices using the USB Printer Class.
 *
 *  @{
 */

#ifndef _PRINTER_CLASS_H_
#define _PRINTER_CLASS_H_

	/* Macros: */
		#define __INCLUDE_FROM_USB_DRIVER
		#define __INCLUDE_FROM_PRINTER_DRIVER

	/* Includes: */
		#include "../Core/USBMode.h"

		#if defined(USB_CAN_BE_DEVICE)
			#include "Device/PrinterClassDevice.h"
		#endif

		#if defined(USB_CAN_BE_HOST)
			#include "Host/PrinterClassHost.h"
		#endif

#endif

/** @} */

