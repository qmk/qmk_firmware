/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Master SPI Mode Serial USART Peripheral Driver (XMEGA)
 *
 *  On-chip Master SPI mode USART driver for the XMEGA AVR microcontrollers.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the SPI Master
 *        Mode USART driver dispatch header located in LUFA/Drivers/Peripheral/Serial.h.
 */

/** \ingroup Group_SerialSPI
 *  \defgroup Group_SerialSPI_AVR8 Master SPI Mode Serial USART Peripheral Driver (AVR8)
 *
 *  \section Sec_SerialSPI_AVR8_ModDescription Module Description
 *  On-chip serial USART driver for the 8-bit AVR8 microcontrollers.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the SPI Master
 *        driver dispatch header located in LUFA/Drivers/Peripheral/SerialSPI.h.
 *
 *  \section Sec_SerialSPI_AVR8_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      // Initialize the Master SPI mode USART driver before first use, with 1Mbit baud
 *      SerialSPI_Init((USART_SPI_SCK_LEAD_RISING | USART_SPI_SAMPLE_LEADING | USART_SPI_ORDER_MSB_FIRST), 1000000);
 *
 *      // Send several bytes, ignoring the returned data
 *      SerialSPI_SendByte(0x01);
 *      SerialSPI_SendByte(0x02);
 *      SerialSPI_SendByte(0x03);
 *
 *      // Receive several bytes, sending a dummy 0x00 byte each time
 *      uint8_t Byte1 = SerialSPI_ReceiveByte();
 *      uint8_t Byte2 = SerialSPI_ReceiveByte();
 *      uint8_t Byte3 = SerialSPI_ReceiveByte();
 *
 *      // Send a byte, and store the received byte from the same transaction
 *      uint8_t ResponseByte = SerialSPI_TransferByte(0xDC);
 *  \endcode
 *
 *  @{
 */

#ifndef __SERIAL_SPI_AVR8_H__
#define __SERIAL_SPI_AVR8_H__

	/* Includes: */
		#include "../../../Common/Common.h"

		#include <stdio.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_SERIAL_SPI_H)
			#error Do not include this file directly. Include LUFA/Drivers/Peripheral/Serial.h instead.
		#endif

	/* Private Interface - For use in library only: */
		#if !defined(__DOXYGEN__)
			#define SERIAL_SPI_UBBRVAL(Baud)             ((Baud < (F_CPU / 2)) ? ((F_CPU / (2 * Baud)) - 1) : 0)

			/* Master USART SPI mode flag definitions missing in the AVR8 toolchain */
			#if !defined(UCPHA1)
				#define UCPHA1                           1
			#endif
			#if !defined(UDORD1)
				#define UDORD1                           2
			#endif
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** \name SPI SCK Polarity Configuration Masks */
			//@{
			/** SPI clock polarity mask for \ref SPI_Init(). Indicates that the SCK should lead on the rising edge. */
			#define USART_SPI_SCK_LEAD_RISING            (0 << UCPOL1)

			/** SPI clock polarity mask for \ref SPI_Init(). Indicates that the SCK should lead on the falling edge. */
			#define USART_SPI_SCK_LEAD_FALLING           (1 << UCPOL1)
			//@}

			/** \name SPI Sample Edge Configuration Masks */
			//@{
			/** SPI data sample mode mask for \ref SerialSPI_Init(). Indicates that the data should sampled on the leading edge. */
			#define USART_SPI_SAMPLE_LEADING             (0 << UCPHA1)

			/** SPI data sample mode mask for \ref SerialSPI_Init(). Indicates that the data should be sampled on the trailing edge. */
			#define USART_SPI_SAMPLE_TRAILING            (1 << UCPHA1)
			//@}

			/** \name SPI Data Ordering Configuration Masks */
			//@{
			/** SPI data order mask for \ref SerialSPI_Init(). Indicates that data should be shifted out MSB first. */
			#define USART_SPI_ORDER_MSB_FIRST            (0 << UDORD1)

			/** SPI data order mask for \ref SerialSPI_Init(). Indicates that data should be shifted out LSB first. */
			#define USART_SPI_ORDER_LSB_FIRST            (1 << UDORD1)
			//@}

		/* Inline Functions: */
			/** Initialize the USART module in Master SPI mode.
			 *
			 *  \param[in]     SPIOptions   USART SPI Options, a mask consisting of one of each of the \c USART_SPI_SCK_*,
			 *                              \c USART_SPI_SAMPLE_* and \c USART_SPI_ORDER_* masks.
			 *  \param[in]     BaudRate     SPI baud rate, in bits per second.
			 */
			static inline void SerialSPI_Init(const uint8_t SPIOptions,
			                                  const uint32_t BaudRate)
			{
				DDRD  |= ((1 << 3) | (1 << 5));
				PORTD |= (1 << 2);

				UCSR1C = ((1 << UMSEL11) | (1 << UMSEL10) | SPIOptions);
				UCSR1B = ((1 << TXEN1)  | (1 << RXEN1));

				UBRR1  = SERIAL_SPI_UBBRVAL(BaudRate);
			}

			/** Turns off the USART driver, disabling and returning used hardware to their default configuration. */
			static inline void SerialSPI_Disable(void)
			{
				UCSR1B = 0;
				UCSR1A = 0;
				UCSR1C = 0;

				UBRR1  = 0;

				DDRD  &= ~((1 << 3) | (1 << 5));
				PORTD &= ~(1 << 2);
			}

			/** Sends and receives a byte through the USART SPI interface, blocking until the transfer is complete.
			 *
			 *  \param[in] DataByte  Byte to send through the USART SPI interface.
			 *
			 *  \return Response byte from the attached SPI device.
			 */
			static inline uint8_t SerialSPI_TransferByte(const uint8_t DataByte)
			{
				UDR1 = DataByte;
				while (!(UCSR1A & (1 << TXC1)));
				UCSR1A = (1 << TXC1);
				return UDR1;
			}

			/** Sends a byte through the USART SPI interface, blocking until the transfer is complete. The response
			 *  byte sent to from the attached SPI device is ignored.
			 *
			 *  \param[in] DataByte  Byte to send through the USART SPI interface.
			 */
			static inline void SerialSPI_SendByte(const uint8_t DataByte)
			{
				SerialSPI_TransferByte(DataByte);
			}

			/** Sends a dummy byte through the USART SPI interface, blocking until the transfer is complete. The response
			 *  byte from the attached SPI device is returned.
			 *
			 *  \return The response byte from the attached SPI device.
			 */
			static inline uint8_t SerialSPI_ReceiveByte(void)
			{
				return SerialSPI_TransferByte(0);
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

