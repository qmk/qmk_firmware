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

/** \file
 *
 *  This file is the master dispatch header file for the device-specific USART driver, for AVRs containing a
 *  USART.
 *
 *  User code should include this file, which will in turn include the correct USART driver header file for
 *  the currently selected AVR model.
 */
 
/** \ingroup Group_PeripheralDrivers
 *  @defgroup Group_Serial Serial USART Driver - LUFA/Drivers/Peripheral/Serial.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/Peripheral/Serial.c
 *
 *  \section Module Description
 *  Hardware serial USART driver. This module provides an easy to use driver for
 *  the setup of and transfer of data over the AVR's USART port.
 *
 *  @{
 */
 
#ifndef __SERIAL_H__
#define __SERIAL_H__

	/* Macros: */
	#if !defined(__DOXYGEN__)
		#define __INCLUDE_FROM_SERIAL_H
	#endif

	/* Includes: */
		#include "../../Common/Common.h"		
		#include "../Misc/TerminalCodes.h"

		#if defined(__AVR32__)
			#include "AVR32/Serial.h"
		#elif defined(__AVR__)
			#include "AVR8/Serial.h"		
		#endif
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Function Prototypes: */
			/** Transmits a given string located in program space (FLASH) through the USART.
			 *
			 *  \param[in] FlashStringPtr  Pointer to a string located in program space
			 */
			void Serial_TxString_P(const char *FlashStringPtr) ATTR_NON_NULL_PTR_ARG(1);

			/** Transmits a given string located in SRAM memory through the USART.
			 *
			 *  \param[in] StringPtr  Pointer to a string located in SRAM space
			 */
			void Serial_TxString(const char *StringPtr) ATTR_NON_NULL_PTR_ARG(1);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
