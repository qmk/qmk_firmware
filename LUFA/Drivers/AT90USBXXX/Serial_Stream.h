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
 *  Serial stream driver for the USART subsystem on supported USB AVRs. This makes use of the functions in the
 *  regular USART driver, but allows the avr-libc standard stream functions (printf, puts, etc.) to work with the
 *  USART.
 **/

/** \ingroup Group_SubsystemDrivers
 *  @defgroup Group_SerialStream Serial Stream Driver - LUFA/Drivers/Peripheral/Serial_Stream.h
 *
 *  Functions, macros, variables, enums and types related to the setup of a serial stream, so that standard printf and other
 *  C stream functions can be used on the serial port.
 *
 *  @{
 */

#ifndef __SERIAL_STREAM_H__
#define __SERIAL_STREAM_H__

	/* Includes: */
		#include <avr/io.h>
		#include <stdio.h>
		
		#include "Serial.h"
	
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Private Interface - For use in library only: */	
	#if !defined(__DOXYGEN__)
		/* External Variables: */
			extern FILE USARTStream;

		/* Function Prototypes: */
			int SerialStream_TxByte(char DataByte, FILE *Stream) ATTR_NON_NULL_PTR_ARG(2);
			int SerialStream_RxByte(FILE *Stream) ATTR_NON_NULL_PTR_ARG(1);
	#endif

	/* Public Interface - May be used in end-application: */
		/* Inline Functions: */
			/** Initializes the serial stream (and regular USART driver) so that both the stream and regular
			 *  USART driver functions can be used. Must be called before any stream or regular USART functions.
			 *
			 *  \param BaudRate     Baud rate to configure the USART to
			 *  \param DoubleSpeed  Enables double speed mode when set, halving the sample time to double the baud rate
			 */
			static inline void SerialStream_Init(const uint32_t BaudRate, const bool DoubleSpeed)
			{
				Serial_Init(BaudRate, DoubleSpeed);
				
				stdout = &USARTStream;
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
