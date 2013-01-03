/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Architecture Specific Hardware Platform Drivers.
 *
 *  This file is the master dispatch header file for the device-specific hardware platform drivers, for low level
 *  hardware configuration and management. The platform drivers are a set of drivers which are designed to provide
 *  a high level management layer for the various low level system functions such as clock control and interrupt
 *  management.
 *
 *  User code may choose to either include this master dispatch header file to include all available platform
 *  driver header files for the current architecture, or may choose to only include the specific platform driver
 *  modules required for a particular application.
 */

/** \defgroup Group_PlatformDrivers System Platform Drivers - LUFA/Platform/Platform.h
 *  \brief Hardware platform drivers.
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - <b>UC3 Architecture Only:</b> LUFA/Platform/UC3/InterruptManagement.c <i>(Makefile source module name: LUFA_SRC_PLATFORM)</i> 
 *    - <b>UC3 Architecture Only:</b> LUFA/Platform/UC3/Exception.S <i>(Makefile source module name: LUFA_SRC_PLATFORM)</i>
 *
 *  \section Sec_ModDescription Module Description
 *  Device-specific hardware platform drivers, for low level hardware configuration and management. The platform
 *  drivers are a set of drivers which are designed to provide a high level management layer for the various low level
 *  system functions such as clock control and interrupt management.
 *
 *  User code may choose to either include this master dispatch header file to include all available platform
 *  driver header files for the current architecture, or may choose to only include the specific platform driver
 *  modules required for a particular application.
 *
 *  \note The exact APIs and availability of sub-modules within the platform driver group may vary depending on the
 *        target used - see individual target module documentation for the API specific to your target processor.
 */

#ifndef __LUFA_PLATFORM_H__
#define __LUFA_PLATFORM_H__

	/* Includes: */
		#include "../Common/Common.h"

	/* Includes: */
		#if (ARCH == ARCH_UC3)
			#include "UC3/ClockManagement.h"
			#include "UC3/InterruptManagement.h"
		#elif (ARCH == ARCH_XMEGA)
			#include "XMEGA/ClockManagement.h"
		#endif

#endif

