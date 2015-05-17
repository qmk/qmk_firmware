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
 *  \brief SPI Peripheral Driver (AVR8)
 *
 *  On-chip SPI driver for the 8-bit AVR microcontrollers.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the SPI driver
 *        dispatch header located in LUFA/Drivers/Peripheral/SPI.h.
 */

/** \ingroup Group_SPI
 *  \defgroup Group_SPI_AVR8 SPI Peripheral Driver (AVR8)
 *
 *  \section Sec_SPI_AVR8_ModDescription Module Description
 *  Driver for the hardware SPI port available on most 8-bit AVR microcontroller models. This
 *  module provides an easy to use driver for the setup and transfer of data over the
 *  AVR's SPI port.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the SPI driver
 *        dispatch header located in LUFA/Drivers/Peripheral/SPI.h.
 *
 *  \section Sec_SPI_AVR8_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      // Initialize the SPI driver before first use
 *      SPI_Init(SPI_SPEED_FCPU_DIV_2 | SPI_ORDER_MSB_FIRST | SPI_SCK_LEAD_FALLING |
 *               SPI_SAMPLE_TRAILING | SPI_MODE_MASTER);
 *
 *      // Send several bytes, ignoring the returned data
 *      SPI_SendByte(0x01);
 *      SPI_SendByte(0x02);
 *      SPI_SendByte(0x03);
 *
 *      // Receive several bytes, sending a dummy 0x00 byte each time
 *      uint8_t Byte1 = SPI_ReceiveByte();
 *      uint8_t Byte2 = SPI_ReceiveByte();
 *      uint8_t Byte3 = SPI_ReceiveByte();
 *
 *      // Send a byte, and store the received byte from the same transaction
 *      uint8_t ResponseByte = SPI_TransferByte(0xDC);
 *  \endcode
 *
 *  @{
 */

#ifndef __SPI_AVR8_H__
#define __SPI_AVR8_H__

	/* Includes: */
		#include "../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_SPI_H)
			#error Do not include this file directly. Include LUFA/Drivers/Peripheral/SPI.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define SPI_USE_DOUBLESPEED            (1 << SPE)
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** \name SPI Prescaler Configuration Masks */
			//@{
			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 2. */
			#define SPI_SPEED_FCPU_DIV_2           SPI_USE_DOUBLESPEED

			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 4. */
			#define SPI_SPEED_FCPU_DIV_4           0

			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 8. */
			#define SPI_SPEED_FCPU_DIV_8           (SPI_USE_DOUBLESPEED | (1 << SPR0))

			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 16. */
			#define SPI_SPEED_FCPU_DIV_16          (1 << SPR0)

			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 32. */
			#define SPI_SPEED_FCPU_DIV_32          (SPI_USE_DOUBLESPEED | (1 << SPR1))

			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 64. */
			#define SPI_SPEED_FCPU_DIV_64          (SPI_USE_DOUBLESPEED | (1 << SPR1) | (1 << SPR0))

			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 128. */
			#define SPI_SPEED_FCPU_DIV_128         ((1 << SPR1) | (1 << SPR0))
			//@}

			/** \name SPI SCK Polarity Configuration Masks */
			//@{
			/** SPI clock polarity mask for \ref SPI_Init(). Indicates that the SCK should lead on the rising edge. */
			#define SPI_SCK_LEAD_RISING            (0 << CPOL)

			/** SPI clock polarity mask for \ref SPI_Init(). Indicates that the SCK should lead on the falling edge. */
			#define SPI_SCK_LEAD_FALLING           (1 << CPOL)
			//@}

			/** \name SPI Sample Edge Configuration Masks */
			//@{
			/** SPI data sample mode mask for \ref SPI_Init(). Indicates that the data should sampled on the leading edge. */
			#define SPI_SAMPLE_LEADING             (0 << CPHA)

			/** SPI data sample mode mask for \ref SPI_Init(). Indicates that the data should be sampled on the trailing edge. */
			#define SPI_SAMPLE_TRAILING            (1 << CPHA)
			//@}

			/** \name SPI Data Ordering Configuration Masks */
			//@{
			/** SPI data order mask for \ref SPI_Init(). Indicates that data should be shifted out MSB first. */
			#define SPI_ORDER_MSB_FIRST            (0 << DORD)

			/** SPI data order mask for \ref SPI_Init(). Indicates that data should be shifted out LSB first. */
			#define SPI_ORDER_LSB_FIRST            (1 << DORD)
			//@}

			/** \name SPI Mode Configuration Masks */
			//@{
			/** SPI mode mask for \ref SPI_Init(). Indicates that the SPI interface should be initialized into slave mode. */
			#define SPI_MODE_SLAVE                 (0 << MSTR)

			/** SPI mode mask for \ref SPI_Init(). Indicates that the SPI interface should be initialized into master mode. */
			#define SPI_MODE_MASTER                (1 << MSTR)
			//@}

		/* Inline Functions: */
			/** Initializes the SPI subsystem, ready for transfers. Must be called before calling any other
			 *  SPI routines.
			 *
			 *  \param[in] SPIOptions  SPI Options, a mask consisting of one of each of the \c SPI_SPEED_*,
			 *                         \c SPI_SCK_*, \c SPI_SAMPLE_*, \c SPI_ORDER_* and \c SPI_MODE_* masks.
			 */
			static inline void SPI_Init(const uint8_t SPIOptions);
			static inline void SPI_Init(const uint8_t SPIOptions)
			{
				/* Prevent high rise times on PB.0 (/SS) from forcing a change to SPI slave mode */
				DDRB  |= (1 << 0);
				PORTB |= (1 << 0);

				DDRB  |=  ((1 << 1) | (1 << 2));
				DDRB  &= ~(1 << 3);
				PORTB |=  (1 << 3);

				if (SPIOptions & SPI_USE_DOUBLESPEED)
				  SPSR |= (1 << SPI2X);
				else
				  SPSR &= ~(1 << SPI2X);

				/* Switch /SS to input mode after configuration to allow for forced mode changes */
				DDRB &= ~(1 << 0);

				SPCR  = ((1 << SPE) | SPIOptions);
			}

			/** Turns off the SPI driver, disabling and returning used hardware to their default configuration. */
			static inline void SPI_Disable(void);
			static inline void SPI_Disable(void)
			{
				DDRB  &= ~((1 << 1) | (1 << 2));
				PORTB &= ~((1 << 0) | (1 << 3));

				SPCR   = 0;
				SPSR   = 0;
			}

			/** Retrieves the currently selected SPI mode, once the SPI interface has been configured.
			 *
			 *  \return \ref SPI_MODE_MASTER if the interface is currently in SPI Master mode, \ref SPI_MODE_SLAVE otherwise
			 */
			static inline uint8_t SPI_GetCurrentMode(void) ATTR_ALWAYS_INLINE;
			static inline uint8_t SPI_GetCurrentMode(void)
			{
				return (SPCR & SPI_MODE_MASTER);
			}

			/** Sends and receives a byte through the SPI interface, blocking until the transfer is complete.
			 *
			 *  \param[in] Byte  Byte to send through the SPI interface.
			 *
			 *  \return Response byte from the attached SPI device.
			 */
			static inline uint8_t SPI_TransferByte(const uint8_t Byte) ATTR_ALWAYS_INLINE;
			static inline uint8_t SPI_TransferByte(const uint8_t Byte)
			{
				SPDR = Byte;
				while (!(SPSR & (1 << SPIF)));
				return SPDR;
			}

			/** Sends a byte through the SPI interface, blocking until the transfer is complete. The response
			 *  byte sent to from the attached SPI device is ignored.
			 *
			 *  \param[in] Byte  Byte to send through the SPI interface.
			 */
			static inline void SPI_SendByte(const uint8_t Byte) ATTR_ALWAYS_INLINE;
			static inline void SPI_SendByte(const uint8_t Byte)
			{
				SPDR = Byte;
				while (!(SPSR & (1 << SPIF)));
			}

			/** Sends a dummy byte through the SPI interface, blocking until the transfer is complete. The response
			 *  byte from the attached SPI device is returned.
			 *
			 *  \return The response byte from the attached SPI device.
			 */
			static inline uint8_t SPI_ReceiveByte(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t SPI_ReceiveByte(void)
			{
				SPDR = 0x00;
				while (!(SPSR & (1 << SPIF)));
				return SPDR;
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

