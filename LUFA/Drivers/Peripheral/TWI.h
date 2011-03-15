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
 *  \brief Hardware Two Wire Interface (I2C) driver.
 *
 *  This file is the master dispatch header file for the device-specific SPI driver, for microcontrollers
 *  containing a hardware TWI.
 *
 *  User code should include this file, which will in turn include the correct TWI driver header file for the
 *  currently selected architecture and microcontroller model.
 */

/** \ingroup Group_PeripheralDrivers
 *  \defgroup Group_TWI TWI Driver - LUFA/Drivers/Peripheral/TWI.h
 *  \brief Hardware Two Wire Interface (I2C) driver.
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/Peripheral/<i>ARCH</i>/TWI_<i>ARCH</i>.c <i>(Makefile source module name: LUFA_SRC_TWI)</i>
 *
 *  \section Sec_ModDescription Module Description
 *  Hardware TWI driver. This module provides an easy to use driver for the setup and transfer of data over
 *  the selected architecture and microcontroller model's TWI bus port.
 *
 *  \note The exact API for this driver may vary depending on the target used - see
 *        individual target module documentation for the API specific to your target processor.
 */

#ifndef __TWI_H__
#define __TWI_H__

	/* Macros: */
		#define __INCLUDE_FROM_TWI_H

	/* Includes: */
		#include "../../Common/Common.h"

	/* Includes: */
		#if (ARCH == ARCH_AVR8)
			#include "AVR8/TWI_AVR8.h"
		#else
			#error The TWI peripheral driver is not currently available for your selected architecture.
		#endif

#endif

