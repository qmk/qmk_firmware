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
 *  Driver for the USART subsystem on supported USB AVRs.
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

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>
		#include <stdbool.h>
		
		#include "../../Common/Common.h"
		#include "../Misc/TerminalCodes.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Macro for calculating the baud value from a given baud rate when the U2X (double speed) bit is
			 *  not set.
			 */
			#define SERIAL_UBBRVAL(baud)    (((F_CPU / 16) / (baud)) - 1)

			/** Macro for calculating the baud value from a given baud rate when the U2X (double speed) bit is
			 *  set.
			 */
			#define SERIAL_2X_UBBRVAL(baud) (((F_CPU / 8) / (baud)) - 1)

		/* Pseudo-Function Macros: */
			#if defined(__DOXYGEN__)
				/** Indicates whether a character has been received through the USART.
				 *
				 *  \return Boolean true if a character has been received, false otherwise
				 */
				static inline bool Serial_IsCharReceived(void);
			#else
				#define Serial_IsCharReceived() ((UCSR1A & (1 << RXC1)) ? true : false)
			#endif

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

		/* Inline Functions: */
			/** Initializes the USART, ready for serial data transmission and reception. This initialises the interface to
			 *  standard 8-bit, no parity, 1 stop bit settings suitable for most applications.
			 *
			 *  \param[in] BaudRate     Serial baud rate, in bits per second
			 *  \param[in] DoubleSpeed  Enables double speed mode when set, halving the sample time to double the baud rate
			 */
			static inline void Serial_Init(const uint32_t BaudRate, const bool DoubleSpeed)
			{
				UCSR1A = (DoubleSpeed ? (1 << U2X1) : 0);
				UCSR1B = ((1 << TXEN1)  | (1 << RXEN1));
				UCSR1C = ((1 << UCSZ11) | (1 << UCSZ10));
				
				DDRD  |= (1 << 3);	
				PORTD |= (1 << 2);
				
				UBRR1  = (DoubleSpeed ? SERIAL_2X_UBBRVAL(BaudRate) : SERIAL_UBBRVAL(BaudRate));
			}

			/** Turns off the USART driver, disabling and returning used hardware to their default configuration. */
			static inline void Serial_ShutDown(void)
			{
				UCSR1A = 0;
				UCSR1B = 0;
				UCSR1C = 0;
				
				DDRD  &= ~(1 << 3);	
				PORTD &= ~(1 << 2);
				
				UBRR1  = 0;
			}
			
			/** Transmits a given byte through the USART.
			 *
			 *  \param[in] DataByte  Byte to transmit through the USART
			 */
			static inline void Serial_TxByte(const char DataByte)
			{
				while (!(UCSR1A & (1 << UDRE1)));
				UDR1 = DataByte;
			}

			/** Receives a byte from the USART.
			 *
			 *  \return Byte received from the USART
			 */
			static inline char Serial_RxByte(void)
			{
				while (!(UCSR1A & (1 << RXC1)));
				return UDR1; 
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
