/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Master include file for the board dataflash IC driver.
 *  \brief Atmel Dataflash storage IC board hardware driver.
 *
 *  This file is the master dispatch header file for the board-specific Atmel dataflash driver, for boards containing
 *  Atmel Dataflash ICs for external non-volatile storage.
 *
 *  User code should include this file, which will in turn include the correct dataflash driver header file for
 *  the currently selected board.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/Dataflash.h file in the user project
 *  directory.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 */

/** \ingroup Group_BoardDrivers
 *  \defgroup Group_Dataflash Dataflash Driver - LUFA/Drivers/Board/Dataflash.h
 *  \brief Atmel Dataflash storage IC board hardware driver.
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_ModDescription Module Description
 *  Dataflash driver. This module provides an easy to use interface for the Dataflash ICs located on many boards,
 *  for the storage of large amounts of data into the Dataflash's non-volatile memory.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/Dataflash.h file in the user project
 *  directory. Otherwise, it will include the appropriate built in board driver header file.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 *
 *  \section Sec_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      // Initialise the SPI and board Dataflash drivers before first use
 *      SPI_Init(SPI_SPEED_FCPU_DIV_2 | SPI_ORDER_MSB_FIRST | SPI_SCK_LEAD_FALLING |
 *               SPI_SAMPLE_TRAILING | SPI_MODE_MASTER);
 *      Dataflash_Init();
 *
 *      uint8_t WriteBuffer[DATAFLASH_PAGE_SIZE];
 *      uint8_t ReadBuffer[DATAFLASH_PAGE_SIZE];
 *
 *      // Fill page write buffer with a repeating pattern
 *      for (uint16_t i = 0; i < DATAFLASH_PAGE_SIZE; i++)
 *        WriteBuffer[i] = (i & 0xFF);
 *
 *      // Must select the chip of interest first before operating on it
 *      Dataflash_SelectChip(DATAFLASH_CHIP1);
 *
 *      // Write to the Dataflash's first internal memory buffer
 *      printf("Writing data to first dataflash buffer:\r\n");
 *      Dataflash_SendByte(DF_CMD_BUFF1WRITE);
 *      Dataflash_SendAddressBytes(0, 0);
 *
 *      for (uint16_t i = 0; i < DATAFLASH_PAGE_SIZE; i++)
 *        Dataflash_SendByte(WriteBuffer[i]);
 *
 *      // Commit the Dataflash's first memory buffer to the non-volatile FLASH memory
 *      printf("Committing page to non-volatile memory page index 5:\r\n");
 *      Dataflash_SendByte(DF_CMD_BUFF1TOMAINMEMWITHERASE);
 *      Dataflash_SendAddressBytes(5, 0);
 *      Dataflash_WaitWhileBusy();
 *
 *      // Read the page from non-volatile FLASH memory into the Dataflash's second memory buffer
 *      printf("Reading data into second dataflash buffer:\r\n");
 *      Dataflash_SendByte(DF_CMD_MAINMEMTOBUFF2);
 *      Dataflash_SendAddressBytes(5, 0);
 *      Dataflash_WaitWhileBusy();
 *
 *      // Read the Dataflash's second internal memory buffer
 *      Dataflash_SendByte(DF_CMD_BUFF2READ);
 *      Dataflash_SendAddressBytes(0, 0);
 *
 *      for (uint16_t i = 0; i < DATAFLASH_PAGE_SIZE; i++)
 *        ReadBuffer[i] = Dataflash_ReceiveByte();
 *
 *      // Deselect the chip after use
 *      Dataflash_DeselectChip();
 *  \endcode
 *
 *  @{
 */

#ifndef __DATAFLASH_H__
#define __DATAFLASH_H__

	/* Macros: */
		#define __INCLUDE_FROM_DATAFLASH_H

	/* Includes: */
	#include "../../Common/Common.h"
	#include "../Peripheral/SPI.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#if !defined(__DOXYGEN__)
				#define __GET_DATAFLASH_MASK2(x, y) x ## y
				#define __GET_DATAFLASH_MASK(x)     __GET_DATAFLASH_MASK2(DATAFLASH_CHIP,x)
			#endif

			/** Retrieves the Dataflash chip select mask for the given Dataflash chip index.
			 *
			 *  \param[in] index  Index of the dataflash chip mask to retrieve
			 *
			 *  \return Mask for the given Dataflash chip's /CS pin
			 */
			#define DATAFLASH_CHIP_MASK(index)      __GET_DATAFLASH_MASK(index)

		/* Inline Functions: */
			/** Initialises the dataflash driver so that commands and data may be sent to an attached dataflash IC.
			 *
			 *  \note The microcontroller's SPI driver must be initialized before any of the dataflash commands are used.
			 */
			static inline void Dataflash_Init(void);

			/** Determines the currently selected dataflash chip.
			 *
			 *  \return Mask of the currently selected Dataflash chip, either \ref DATAFLASH_NO_CHIP if no chip is selected
			 *  or a \c DATAFLASH_CHIPn mask (where n is the chip number).
			 */
			static inline uint8_t Dataflash_GetSelectedChip(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;

			/** Selects the given dataflash chip.
			 *
			 *  \param[in]  ChipMask  Mask of the Dataflash IC to select, in the form of \c DATAFLASH_CHIPn mask (where n is
			 *              the chip number).
			 */
			static inline void Dataflash_SelectChip(const uint8_t ChipMask) ATTR_ALWAYS_INLINE;

			/** Deselects the current dataflash chip, so that no dataflash is selected. */
			static inline void Dataflash_DeselectChip(void) ATTR_ALWAYS_INLINE;

			/** Selects a dataflash IC from the given page number, which should range from 0 to
			 *  ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1). For boards containing only one
			 *  dataflash IC, this will select \ref DATAFLASH_CHIP1. If the given page number is outside
			 *  the total number of pages contained in the boards dataflash ICs, all dataflash ICs
			 *  are deselected.
			 *
			 *  \param[in] PageAddress  Address of the page to manipulate, ranging from
			 *                          ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1).
			 */
			static inline void Dataflash_SelectChipFromPage(const uint16_t PageAddress);

			/** Toggles the select line of the currently selected dataflash IC, so that it is ready to receive
			 *  a new command.
			 */
			static inline void Dataflash_ToggleSelectedChipCS(void);

			/** Spin-loops while the currently selected dataflash is busy executing a command, such as a main
			 *  memory page program or main memory to buffer transfer.
			 */
			static inline void Dataflash_WaitWhileBusy(void);

			/** Sends a set of page and buffer address bytes to the currently selected dataflash IC, for use with
			 *  dataflash commands which require a complete 24-byte address.
			 *
			 *  \param[in] PageAddress  Page address within the selected dataflash IC
			 *  \param[in] BufferByte   Address within the dataflash's buffer
			 */
			static inline void Dataflash_SendAddressBytes(uint16_t PageAddress,
			                                              const uint16_t BufferByte);

			/** Sends a byte to the currently selected dataflash IC, and returns a byte from the dataflash.
			 *
			 *  \param[in] Byte of data to send to the dataflash
			 *
			 *  \return Last response byte from the dataflash
			 */
			static inline uint8_t Dataflash_TransferByte(const uint8_t Byte) ATTR_ALWAYS_INLINE;
			static inline uint8_t Dataflash_TransferByte(const uint8_t Byte)
			{
				return SPI_TransferByte(Byte);
			}

			/** Sends a byte to the currently selected dataflash IC, and ignores the next byte from the dataflash.
			 *
			 *  \param[in] Byte of data to send to the dataflash
			 */
			static inline void Dataflash_SendByte(const uint8_t Byte) ATTR_ALWAYS_INLINE;
			static inline void Dataflash_SendByte(const uint8_t Byte)
			{
				SPI_SendByte(Byte);
			}

			/** Sends a dummy byte to the currently selected dataflash IC, and returns the next byte from the dataflash.
			 *
			 *  \return Last response byte from the dataflash
			 */
			static inline uint8_t Dataflash_ReceiveByte(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Dataflash_ReceiveByte(void)
			{
				return SPI_ReceiveByte();
			}

		/* Includes: */
			#if (BOARD == BOARD_NONE)
				#error The Board Dataflash driver cannot be used if the makefile BOARD option is not set.
			#elif (BOARD == BOARD_USBKEY)
				#include "USBKEY/Dataflash.h"
			#elif (BOARD == BOARD_STK525)
				#include "STK525/Dataflash.h"
			#elif (BOARD == BOARD_STK526)
				#include "STK526/Dataflash.h"
			#elif (BOARD == BOARD_XPLAIN)
				#include "XPLAIN/Dataflash.h"
			#elif (BOARD == BOARD_XPLAIN_REV1)
				#include "XPLAIN/Dataflash.h"
			#elif (BOARD == BOARD_EVK527)
				#include "EVK527/Dataflash.h"
			#else
				#include "Board/Dataflash.h"
			#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

