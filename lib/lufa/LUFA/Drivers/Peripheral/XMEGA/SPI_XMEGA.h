/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief SPI Peripheral Driver (XMEGA)
 *
 *  On-chip SPI driver for the XMEGA microcontrollers.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the SPI driver
 *        dispatch header located in LUFA/Drivers/Peripheral/SPI.h.
 */

/** \ingroup Group_SPI
 *  \defgroup Group_SPI_XMEGA SPI Peripheral Driver (XMEGA)
 *
 *  \section Sec_SPI_XMEGA_ModDescription Module Description
 *  Driver for the hardware SPI port(s) available on XMEGA AVR microcontroller models. This
 *  module provides an easy to use driver for the setup and transfer of data over the AVR's
 *  SPI ports.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the SPI driver
 *        dispatch header located in LUFA/Drivers/Peripheral/SPI.h.
 *
 *  \code
 *      // Initialize the SPI driver before first use
 *      SPI_Init(&SPIC,
 *               SPI_SPEED_FCPU_DIV_2 | SPI_ORDER_MSB_FIRST | SPI_SCK_LEAD_FALLING |
 *               SPI_SAMPLE_TRAILING | SPI_MODE_MASTER);
 *
 *      // Send several bytes, ignoring the returned data
 *      SPI_SendByte(&SPIC, 0x01);
 *      SPI_SendByte(&SPIC, 0x02);
 *      SPI_SendByte(&SPIC, 0x03);
 *
 *      // Receive several bytes, sending a dummy 0x00 byte each time
 *      uint8_t Byte1 = SPI_ReceiveByte(&SPIC);
 *      uint8_t Byte2 = SPI_ReceiveByte(&SPIC);
 *      uint8_t Byte3 = SPI_ReceiveByte(&SPIC);
 *
 *      // Send a byte, and store the received byte from the same transaction
 *      uint8_t ResponseByte = SPI_TransferByte(&SPIC, 0xDC);
 *  \endcode
 *
 *  @{
 */

#ifndef __SPI_XMEGA_H__
#define __SPI_XMEGA_H__

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
			#define SPI_USE_DOUBLESPEED            SPI_CLK2X_bm
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
			#define SPI_SPEED_FCPU_DIV_8           (SPI_USE_DOUBLESPEED | (1 << SPI_PRESCALER_gp))

			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 16. */
			#define SPI_SPEED_FCPU_DIV_16          (1 << SPI_PRESCALER_gp)

			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 32. */
			#define SPI_SPEED_FCPU_DIV_32          (SPI_USE_DOUBLESPEED | (2 << SPI_PRESCALER_gp))

			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 64. */
			#define SPI_SPEED_FCPU_DIV_64          (2 << SPI_PRESCALER_gp)

			/** SPI prescaler mask for \ref SPI_Init(). Divides the system clock by a factor of 128. */
			#define SPI_SPEED_FCPU_DIV_128         (3 << SPI_PRESCALER_gp)
			//@}

			/** \name SPI SCK Polarity Configuration Masks */
			//@{
			/** SPI clock polarity mask for \ref SPI_Init(). Indicates that the SCK should lead on the rising edge. */
			#define SPI_SCK_LEAD_RISING            0

			/** SPI clock polarity mask for \ref SPI_Init(). Indicates that the SCK should lead on the falling edge. */
			#define SPI_SCK_LEAD_FALLING           SPI_MODE1_bm
			//@}

			/** \name SPI Sample Edge Configuration Masks */
			//@{
			/** SPI data sample mode mask for \ref SPI_Init(). Indicates that the data should sampled on the leading edge. */
			#define SPI_SAMPLE_LEADING             0

			/** SPI data sample mode mask for \ref SPI_Init(). Indicates that the data should be sampled on the trailing edge. */
			#define SPI_SAMPLE_TRAILING            SPI_MODE0_bm
			//@}

			/** \name SPI Data Ordering Configuration Masks */
			//@{
			/** SPI data order mask for \ref SPI_Init(). Indicates that data should be shifted out MSB first. */
			#define SPI_ORDER_MSB_FIRST            0

			/** SPI data order mask for \ref SPI_Init(). Indicates that data should be shifted out LSB first. */
			#define SPI_ORDER_LSB_FIRST            SPI_DORD_bm
			//@}

			/** \name SPI Mode Configuration Masks */
			//@{
			/** SPI mode mask for \ref SPI_Init(). Indicates that the SPI interface should be initialized into slave mode. */
			#define SPI_MODE_SLAVE                 0

			/** SPI mode mask for \ref SPI_Init(). Indicates that the SPI interface should be initialized into master mode. */
			#define SPI_MODE_MASTER                SPI_MASTER_bm
			//@}

		/* Inline Functions: */
			/** Initializes the SPI subsystem, ready for transfers. Must be called before calling any other
			 *  SPI routines.
			 *
			 *  \param[in,out] SPI         Pointer to the base of the SPI peripheral within the device.
			 *  \param[in]     SPIOptions  SPI Options, a mask consisting of one of each of the \c SPI_SPEED_*,
			 *                             \c SPI_SCK_*, \c SPI_SAMPLE_*, \c SPI_ORDER_* and \c SPI_MODE_* masks.
			 */
			static inline void SPI_Init(SPI_t* const SPI,
			                            const uint8_t SPIOptions) ATTR_NON_NULL_PTR_ARG(1);
			static inline void SPI_Init(SPI_t* const SPI,
			                            const uint8_t SPIOptions)
			{
				SPI->CTRL = (SPIOptions | SPI_ENABLE_bm);
			}

			/** Turns off the SPI driver, disabling and returning used hardware to their default configuration.
			 *
			 *  \param[in,out] SPI   Pointer to the base of the SPI peripheral within the device.
			 */
			static inline void SPI_Disable(SPI_t* const SPI) ATTR_NON_NULL_PTR_ARG(1);
			static inline void SPI_Disable(SPI_t* const SPI)
			{
				SPI->CTRL &= ~SPI_ENABLE_bm;
			}

			/** Retrieves the currently selected SPI mode, once the SPI interface has been configured.
			 *
			 *  \param[in,out] SPI  Pointer to the base of the SPI peripheral within the device.
			 *
			 *  \return \ref SPI_MODE_MASTER if the interface is currently in SPI Master mode, \ref SPI_MODE_SLAVE otherwise
			 */
			static inline uint8_t SPI_GetCurrentMode(SPI_t* const SPI) ATTR_ALWAYS_INLINE ATTR_NON_NULL_PTR_ARG(1);
			static inline uint8_t SPI_GetCurrentMode(SPI_t* const SPI)
			{
				return (SPI->CTRL & SPI_MASTER_bm);
			}

			/** Sends and receives a byte through the SPI interface, blocking until the transfer is complete.
			 *
			 *  \param[in,out] SPI   Pointer to the base of the SPI peripheral within the device.
			 *  \param[in]     Byte  Byte to send through the SPI interface.
			 *
			 *  \return Response byte from the attached SPI device.
			 */
			static inline uint8_t SPI_TransferByte(SPI_t* const SPI,
			                                       const uint8_t Byte) ATTR_ALWAYS_INLINE ATTR_NON_NULL_PTR_ARG(1);
			static inline uint8_t SPI_TransferByte(SPI_t* const SPI,
			                                       const uint8_t Byte)
			{
				SPI->DATA = Byte;
				while (!(SPI->STATUS & SPI_IF_bm));
				return SPI->DATA;
			}

			/** Sends a byte through the SPI interface, blocking until the transfer is complete. The response
			 *  byte sent to from the attached SPI device is ignored.
			 *
			 *  \param[in,out] SPI   Pointer to the base of the SPI peripheral within the device.
			 *  \param[in]     Byte  Byte to send through the SPI interface.
			 */
			static inline void SPI_SendByte(SPI_t* const SPI,
			                                const uint8_t Byte) ATTR_ALWAYS_INLINE ATTR_NON_NULL_PTR_ARG(1);
			static inline void SPI_SendByte(SPI_t* const SPI,
			                                const uint8_t Byte)
			{
				SPI->DATA = Byte;
				while (!(SPI->STATUS & SPI_IF_bm));
			}

			/** Sends a dummy byte through the SPI interface, blocking until the transfer is complete. The response
			 *  byte from the attached SPI device is returned.
			 *
			 *  \param[in,out] SPI  Pointer to the base of the SPI peripheral within the device.
			 *
			 *  \return The response byte from the attached SPI device.
			 */
			static inline uint8_t SPI_ReceiveByte(SPI_t* const SPI) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
			static inline uint8_t SPI_ReceiveByte(SPI_t* const SPI)
			{
				SPI->DATA = 0;
				while (!(SPI->STATUS & SPI_IF_bm));
				return SPI->DATA;
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

