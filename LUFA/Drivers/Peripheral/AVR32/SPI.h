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
 *  SPI driver for the 32-bit AVRs.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the SPI driver
 *        dispatch header located in LUFA/Drivers/Peripheral/SPI.h.
 */
 
/** \ingroup Group_SPI
 *  @defgroup Group_SPI_AVR32 32-Bit AVR SPI Driver
 *
 *  SPI driver for the 32-bit AVRs.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the ADC driver
 *        dispatch header located in LUFA/Drivers/Peripheral/SPI.h.
 *
 *  @{
 */

#ifndef __SPI_AVR32_H__
#define __SPI_AVR32_H__

	/* Includes: */
		#include <avr32/io.h>
		#include <stdbool.h>

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_SPI_H)
			#error Do not include this file directly. Include LUFA/Drivers/Peripheral/SPI.h instead.
		#endif

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif
	
	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** SPI prescaler mask for SPI_Init(). Divides the system clock by a factor of 1. */
			#define SPI_SPEED_FCPU_DIV_1           0

			/** SPI prescaler mask for SPI_Init(). Divides the system clock by a factor of 32. */
			#define SPI_SPEED_FCPU_DIV_32          AVR32_SPI_MR_FDIV_MASK
			
			/** SPI mode mask for SPI_Init(). Indicates that the SPI interface should be initialized into slave mode. */
			#define SPI_MODE_SLAVE                 0

			/** SPI mode mask for SPI_Init(). Indicates that the SPI interface should be initialized into master mode. */
			#define SPI_MODE_MASTER                AVR32_SPI_MR_MSTR_MASK

		/* Inline Functions: */
			/** Initialises the SPI subsystem, ready for transfers. Must be called before calling any other
			 *  SPI routines.
			 *
			 *  \param[in] SPIOptions  SPI Options, a mask consisting of one of each of the SPI_SPEED_*
			 *                         and SPI_MODE_* masks
			 */
			static inline void SPI_Init(const uint8_t SPIOptions)
			{
				AVR32_SPI.cr = AVR32_SPI_CR_SPIEN_MASK | AVR32_SPI_CR_SWRST_MASK;
				AVR32_SPI.mr = SPIOptions;
			}
			
			/** Turns off the SPI driver, disabling and returning used hardware to their default configuration. */
			static inline void SPI_ShutDown(void)
			{
				AVR32_SPI.cr = AVR32_SPI_CR_SPIDIS_MASK;
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
				AVR32_SPI.tdr = Byte;
				// TODO: Wait for receive
				return AVR32_SPI.rdr;
			}

			/** Sends a byte through the SPI interface, blocking until the transfer is complete. The response
			 *  byte sent to from the attached SPI device is ignored.
			 *
			 *  \param[in] Byte Byte to send through the SPI interface
			 */
			static inline void SPI_SendByte(const uint8_t Byte) ATTR_ALWAYS_INLINE;
			static inline void SPI_SendByte(const uint8_t Byte)
			{
				AVR32_SPI.tdr = Byte;
				// TODO: Wait for receive				
			}

			/** Sends a dummy byte through the SPI interface, blocking until the transfer is complete. The response
			 *  byte from the attached SPI device is returned.
			 *
			 *  \return The response byte from the attached SPI device
			 */
			static inline uint8_t SPI_ReceiveByte(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t SPI_ReceiveByte(void)
			{
				AVR32_SPI.tdr = 0x00;
				// TODO: Wait for receive				
				return AVR32_SPI.rdr;
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
