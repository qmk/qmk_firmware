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
 *  \defgroup Group_SerialSPI_XMEGA Master SPI Mode Serial USART Peripheral Driver (XMEGA)
 *
 *  \section Sec_SerialSPI_XMEGA_ModDescription Module Description
 *  On-chip serial USART driver for the XMEGA AVR microcontrollers.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the ADC driver
 *        dispatch header located in LUFA/Drivers/Peripheral/SerialSPI.h.
 *
 *  \section Sec_SerialSPI_XMEGA_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      // Initialize the Master SPI mode USART driver before first use, with 1Mbit baud
 *      SerialSPI_Init(&USARTD0, (USART_SPI_SCK_LEAD_RISING | USART_SPI_SAMPLE_LEADING | USART_SPI_ORDER_MSB_FIRST), 1000000);
 *
 *      // Send several bytes, ignoring the returned data
 *      SerialSPI_SendByte(&USARTD0, 0x01);
 *      SerialSPI_SendByte(&USARTD0, 0x02);
 *      SerialSPI_SendByte(&USARTD0, 0x03);
 *
 *      // Receive several bytes, sending a dummy 0x00 byte each time
 *      uint8_t Byte1 = SerialSPI_ReceiveByte(&USARTD);
 *      uint8_t Byte2 = SerialSPI_ReceiveByte(&USARTD);
 *      uint8_t Byte3 = SerialSPI_ReceiveByte(&USARTD);
 *
 *      // Send a byte, and store the received byte from the same transaction
 *      uint8_t ResponseByte = SerialSPI_TransferByte(&USARTD0, 0xDC);
 *  \endcode
 *
 *  @{
 */

#ifndef __SERIAL_SPI_XMEGA_H__
#define __SERIAL_SPI_XMEGA_H__

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
			#define SERIAL_SPI_UBBRVAL(Baud)       ((Baud < (F_CPU / 2)) ? ((F_CPU / (2 * Baud)) - 1) : 0)
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** \name SPI SCK Polarity Configuration Masks */
			//@{
			/** SPI clock polarity mask for \ref SerialSPI_Init(). Indicates that the SCK should lead on the rising edge. */
			#define USART_SPI_SCK_LEAD_RISING      0
			//@}

			/** \name SPI Sample Edge Configuration Masks */
			//@{
			/** SPI data sample mode mask for \ref SerialSPI_Init(). Indicates that the data should sampled on the leading edge. */
			#define USART_SPI_SAMPLE_LEADING       0

			/** SPI data sample mode mask for \ref SerialSPI_Init(). Indicates that the data should be sampled on the trailing edge. */
			#define USART_SPI_SAMPLE_TRAILING      (1 << 1)
			//@}

			/** \name SPI Data Ordering Configuration Masks */
			//@{
			/** SPI data order mask for \ref SerialSPI_Init(). Indicates that data should be shifted out MSB first. */
			#define USART_SPI_ORDER_MSB_FIRST      0

			/** SPI data order mask for \ref SerialSPI_Init(). Indicates that data should be shifted out LSB first. */
			#define USART_SPI_ORDER_LSB_FIRST      (1 << 2)
			//@}

		/* Inline Functions: */
			/** Initialize the USART module in Master SPI mode.
			 *
			 *  \param[in,out] USART        Pointer to the base of the USART peripheral within the device.
			 *  \param[in]     SPIOptions   USART SPI Options, a mask consisting of one of each of the \c USART_SPI_SCK_*,
			 *                              \c USART_SPI_SAMPLE_* and \c USART_SPI_ORDER_* masks.
			 *  \param[in]     BaudRate     SPI baud rate, in bits per second.
			 */
			static inline void SerialSPI_Init(USART_t* const USART,
			                                  const uint8_t SPIOptions,
			                                  const uint32_t BaudRate) ATTR_NON_NULL_PTR_ARG(1);
			static inline void SerialSPI_Init(USART_t* const USART,
			                                  const uint8_t SPIOptions,
			                                  const uint32_t BaudRate)
			{
				uint16_t BaudValue = SERIAL_SPI_UBBRVAL(BaudRate);

				USART->BAUDCTRLB = (BaudValue >> 8);
				USART->BAUDCTRLA = (BaudValue & 0xFF);

				USART->CTRLC = (USART_CMODE_MSPI_gc | SPIOptions);
				USART->CTRLB = (USART_RXEN_bm | USART_TXEN_bm);
			}

			/** Turns off the USART driver, disabling and returning used hardware to their default configuration.
			 *
			 *  \param[in,out] USART  Pointer to the base of the USART peripheral within the device.
			 */
			static inline void SerialSPI_Disable(USART_t* const USART) ATTR_ALWAYS_INLINE ATTR_NON_NULL_PTR_ARG(1);
			static inline void SerialSPI_Disable(USART_t* const USART)
			{
				USART->CTRLA = 0;
				USART->CTRLB = 0;
				USART->CTRLC = 0;
			}

			/** Sends and receives a byte through the USART SPI interface, blocking until the transfer is complete.
			 *
			 *  \param[in,out] USART     Pointer to the base of the USART peripheral within the device.
			 *  \param[in]     DataByte  Byte to send through the USART SPI interface.
			 *
			 *  \return Response byte from the attached SPI device.
			 */
			static inline uint8_t SerialSPI_TransferByte(USART_t* const USART,
			                                             const uint8_t DataByte) ATTR_ALWAYS_INLINE ATTR_NON_NULL_PTR_ARG(1);
			static inline uint8_t SerialSPI_TransferByte(USART_t* const USART,
			                                             const uint8_t DataByte)
			{
				USART->DATA   = DataByte;
				while (!(USART->STATUS & USART_TXCIF_bm));
				USART->STATUS = USART_TXCIF_bm;
				return USART->DATA;
			}

			/** Sends a byte through the USART SPI interface, blocking until the transfer is complete. The response
			 *  byte sent to from the attached SPI device is ignored.
			 *
			 *  \param[in,out] USART     Pointer to the base of the USART peripheral within the device.
			 *  \param[in]     DataByte  Byte to send through the USART SPI interface.
			 */
			static inline void SerialSPI_SendByte(USART_t* const USART,
			                                      const uint8_t DataByte) ATTR_ALWAYS_INLINE ATTR_NON_NULL_PTR_ARG(1);
			static inline void SerialSPI_SendByte(USART_t* const USART,
			                                      const uint8_t DataByte)
			{
				SerialSPI_TransferByte(USART, DataByte);
			}

			/** Sends a dummy byte through the USART SPI interface, blocking until the transfer is complete. The response
			 *  byte from the attached SPI device is returned.
			 *
			 *  \param[in,out] USART  Pointer to the base of the USART peripheral within the device.
			 *
			 *  \return The response byte from the attached SPI device.
			 */
			static inline uint8_t SerialSPI_ReceiveByte(USART_t* const USART) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
			static inline uint8_t SerialSPI_ReceiveByte(USART_t* const USART)
			{
				return SerialSPI_TransferByte(USART, 0);
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

