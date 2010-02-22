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
 *  Hardware SPI subsystem driver for the supported USB AVRs models.
 */

/** \ingroup Group_PeripheralDrivers
 *  @defgroup Group_SPI SPI Driver - LUFA/Drivers/Peripheral/SPI.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Module Description
 *  Driver for the hardware SPI port available on most AVR models. This module provides
 *  an easy to use driver for the setup of and transfer of data over the AVR's SPI port.
 *
 *  @{
 */

#ifndef __SPI_H__
#define __SPI_H__

	/* Includes: */
		#include <stdbool.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define SPI_USE_DOUBLESPEED            (1 << SPE)
	#endif
	
	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** SPI prescaler mask for SPI_Init(). Divides the system clock by a factor of 2. */
			#define SPI_SPEED_FCPU_DIV_2           SPI_USE_DOUBLESPEED

			/** SPI prescaler mask for SPI_Init(). Divides the system clock by a factor of 4. */
			#define SPI_SPEED_FCPU_DIV_4           0

			/** SPI prescaler mask for SPI_Init(). Divides the system clock by a factor of 8. */
			#define SPI_SPEED_FCPU_DIV_8           (SPI_USE_DOUBLESPEED | (1 << SPR0))

			/** SPI prescaler mask for SPI_Init(). Divides the system clock by a factor of 16. */
			#define SPI_SPEED_FCPU_DIV_16          (1 << SPR0)

			/** SPI prescaler mask for SPI_Init(). Divides the system clock by a factor of 32. */
			#define SPI_SPEED_FCPU_DIV_32          (SPI_USE_DOUBLESPEED | (1 << SPR1))

			/** SPI prescaler mask for SPI_Init(). Divides the system clock by a factor of 64. */
			#define SPI_SPEED_FCPU_DIV_64          (SPI_USE_DOUBLESPEED | (1 << SPR1) | (1 << SPR0))

			/** SPI prescaler mask for SPI_Init(). Divides the system clock by a factor of 128. */
			#define SPI_SPEED_FCPU_DIV_128         ((1 << SPR1) | (1 << SPR0))
			
			/** SPI clock polarity mask for SPI_Init(). Indicates that the SCK should lead on the rising edge. */
			#define SPI_SCK_LEAD_RISING            (0 << CPOL)

			/** SPI clock polarity mask for SPI_Init(). Indicates that the SCK should lead on the falling edge. */
			#define SPI_SCK_LEAD_FALLING           (1 << CPOL)

			/** SPI data sample mode mask for SPI_Init(). Indicates that the data should sampled on the leading edge. */
			#define SPI_SAMPLE_LEADING             (0 << CPHA)

			/** SPI data sample mode mask for SPI_Init(). Indicates that the data should be sampled on the trailing edge. */
			#define SPI_SAMPLE_TRAILING            (1 << CPHA)
			
			/** SPI mode mask for SPI_Init(). Indicates that the SPI interface should be initialized into slave mode. */
			#define SPI_MODE_SLAVE                 (0 << MSTR)

			/** SPI mode mask for SPI_Init(). Indicates that the SPI interface should be initialized into master mode. */
			#define SPI_MODE_MASTER                (1 << MSTR)

		/* Inline Functions: */
			/** Initialises the SPI subsystem, ready for transfers. Must be called before calling any other
			 *  SPI routines.
			 *
			 *  \param[in] SPIOptions  SPI Options, a mask consisting of one of each of the SPI_SPEED_*,
			 *                         SPI_SCK_*, SPI_SAMPLE_* and SPI_MODE_* masks
			 */
			static inline void SPI_Init(const uint8_t SPIOptions)
			{
				DDRB  |= ((1 << 1) | (1 << 2));
				PORTB |= ((1 << 0) | (1 << 3));
				
				SPCR   = ((1 << SPE) | SPIOptions);
				
				if (SPIOptions & SPI_USE_DOUBLESPEED)
				  SPSR |= (1 << SPI2X);
				else
				  SPSR &= ~(1 << SPI2X);
			}
			
			/** Turns off the SPI driver, disabling and returning used hardware to their default configuration. */
			static inline void SPI_ShutDown(void)
			{
				DDRB  &= ~((1 << 1) | (1 << 2));
				PORTB &= ~((1 << 0) | (1 << 3));
				
				SPCR   = 0;
				SPSR   = 0;
			}
			
			/** Sends and receives a byte through the SPI interface, blocking until the transfer is complete.
			 *
			 *  \param[in] Byte  Byte to send through the SPI interface
			 *
			 *  \return Response byte from the attached SPI device
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
			 *  \param[in] Byte Byte to send through the SPI interface
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
			 *  \return The response byte from the attached SPI device
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
