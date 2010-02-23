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
 *  Serial stream driver for the USART subsystem on supported USB AVRs. This makes use of the functions in the
 *  regular USART driver, but allows the avr-libc standard stream functions (printf, puts, etc.) to work with the
 *  USART.
 **/

/** \ingroup Group_PeripheralDrivers
 *  @defgroup Group_SerialStream Serial Stream Driver - LUFA/Drivers/Peripheral/SerialStream.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/Peripheral/SerialStream.c
 *
 *  \section Module Description
 *  Serial stream driver for the USART subsystem on supported USB AVRs. This makes use of the functions in the
 *  regular USART driver, but allows the avr-libc standard stream functions (printf, puts, etc.) to work with the
 *  USART.
 *
 *  @{
 */

#ifndef __SERIAL_STREAM_H__
#define __SERIAL_STREAM_H__

	/* Includes: */
		#include <avr/io.h>
		#include <stdio.h>
		
		#include "../../Common/Common.h"		

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
		#if defined(__INCLUDE_FROM_SERIALSTREAM_C)
			static int SerialStream_TxByte(char DataByte, FILE *Stream) ATTR_NON_NULL_PTR_ARG(2);
			static int SerialStream_RxByte(FILE *Stream) ATTR_NON_NULL_PTR_ARG(1);
		#endif
	#endif

	/* Public Interface - May be used in end-application: */
		/* Inline Functions: */
			/** Initializes the serial stream (and regular USART driver) so that both the stream and regular
			 *  USART driver functions can be used. Must be called before any stream or regular USART functions.
			 *
			 *  \param[in] BaudRate     Baud rate to configure the USART to
			 *  \param[in] DoubleSpeed  Enables double speed mode when set, halving the sample time to double the baud rate
			 */
			static inline void SerialStream_Init(const uint32_t BaudRate, const bool DoubleSpeed)
			{
				Serial_Init(BaudRate, DoubleSpeed);
				
				stdout = &USARTStream;
				stdin  = &USARTStream;
			}
			
			/** Turns off the serial stream (and regular USART driver), disabling and returning used hardware to
			 *  their default configuration.
			 */
			static inline void SerialStream_ShutDown(void)
			{
				Serial_ShutDown();
			}			

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
