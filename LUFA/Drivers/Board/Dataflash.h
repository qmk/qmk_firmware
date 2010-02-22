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
 *  This file is the master dispatch header file for the board-specific dataflash driver, for boards containing
 *  dataflash ICs for external non-volatile storage.
 *
 *  User code should include this file, which will in turn include the correct dataflash driver header file for
 *  the currently selected board.
 *
 *  If the BOARD value is set to BOARD_USER, this will include the /Board/Dataflash.h file in the user project
 *  directory.
 */
 
/** \ingroup Group_BoardDrivers
 *  @defgroup Group_Dataflash Dataflash Driver - LUFA/Drivers/Board/Dataflash.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Module Description
 *  Dataflash driver. This module provides an easy to use interface for the Dataflash ICs located on many boards,
 *  for the storage of large amounts of data into the Dataflash's non-volatile memory.
 *
 *  If the BOARD value is set to BOARD_USER, this will include the /Board/Dataflash.h file in the user project
 *  directory. Otherwise, it will include the appropriate built in board driver header file.
 *
 *  @{
 */
 
#ifndef __DATAFLASH_H__
#define __DATAFLASH_H__

	/* Macros: */
	#if !defined(__DOXYGEN__)
		#define __INCLUDE_FROM_DATAFLASH_H
		#define INCLUDE_FROM_DATAFLASH_H
	#endif

	/* Includes: */
	#include "../Peripheral/SPI.h"
	#include "../../Common/Common.h"
		
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
			
		/* Pseudo-Function Macros: */
			#if defined(__DOXYGEN__)
				/** Determines the currently selected dataflash chip.
				 *
				 *  \return Mask of the currently selected Dataflash chip, either \ref DATAFLASH_NO_CHIP if no chip is selected
				 *  or a DATAFLASH_CHIPn mask (where n is the chip number).
				 */
				static inline uint8_t Dataflash_GetSelectedChip(void);

				/** Selects the given dataflash chip.
				 *
				 *  \param[in]  ChipMask  Mask of the Dataflash IC to select, in the form of DATAFLASH_CHIPn mask (where n is
				 *              the chip number).
				 */
				static inline void Dataflash_SelectChip(uint8_t ChipMask);

				/** Deselects the current dataflash chip, so that no dataflash is selected. */
				static inline void Dataflash_DeselectChip(void);
			#else
				#define Dataflash_GetSelectedChip()          (DATAFLASH_CHIPCS_PORT & DATAFLASH_CHIPCS_MASK)

				#define Dataflash_SelectChip(mask)   MACROS{ DATAFLASH_CHIPCS_PORT = ((DATAFLASH_CHIPCS_PORT \
															 & ~DATAFLASH_CHIPCS_MASK) | (mask));            }MACROE
				
				#define Dataflash_DeselectChip()             Dataflash_SelectChip(DATAFLASH_NO_CHIP)
			#endif
			
		/* Inline Functions: */
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
				#error The Board Buttons driver cannot be used if the makefile BOARD option is not set.
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
			#elif (BOARD == BOARD_USER)
				#include "Board/Dataflash.h"
			#elif (BOARD = BOARD_EVK1101)
				#include "EVK1101/Dataflash.h"
			#else
				#error The selected board does not contain a dataflash IC.
			#endif
		
		/* Inline Functions: */
			/** Initializes the dataflash driver so that commands and data may be sent to an attached dataflash IC.
			 *  The AVR's SPI driver MUST be initialized before any of the dataflash commands are used.
			 */
			static inline void Dataflash_Init(void)
			{
				DATAFLASH_CHIPCS_DDR  |= DATAFLASH_CHIPCS_MASK;
				DATAFLASH_CHIPCS_PORT |= DATAFLASH_CHIPCS_MASK;
			}
			
			/** Toggles the select line of the currently selected dataflash IC, so that it is ready to receive
			 *  a new command.
			 */
			static inline void Dataflash_ToggleSelectedChipCS(void)
			{
				uint8_t SelectedChipMask = Dataflash_GetSelectedChip();
					
				Dataflash_DeselectChip();
				Dataflash_SelectChip(SelectedChipMask);
			}

			/** Spin-loops while the currently selected dataflash is busy executing a command, such as a main
			 *  memory page program or main memory to buffer transfer.
			 */
			static inline void Dataflash_WaitWhileBusy(void)
			{
				Dataflash_ToggleSelectedChipCS();
				Dataflash_SendByte(DF_CMD_GETSTATUS);
				while (!(Dataflash_ReceiveByte() & DF_STATUS_READY));
				Dataflash_ToggleSelectedChipCS();				
			}

			/** Selects a dataflash IC from the given page number, which should range from 0 to
			 *  ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1). For boards containing only one
			 *  dataflash IC, this will select DATAFLASH_CHIP1. If the given page number is outside
			 *  the total number of pages contained in the boards dataflash ICs, all dataflash ICs
			 *  are deselected.
			 *
			 *  \param[in] PageAddress  Address of the page to manipulate, ranging from
			 *                          ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1).
			 */
			static inline void Dataflash_SelectChipFromPage(const uint16_t PageAddress);

			/** Sends a set of page and buffer address bytes to the currently selected dataflash IC, for use with
			 *  dataflash commands which require a complete 24-byte address.
			 *
			 *  \param[in] PageAddress  Page address within the selected dataflash IC
			 *  \param[in] BufferByte   Address within the dataflash's buffer
			 */
			static inline void Dataflash_SendAddressBytes(uint16_t PageAddress, const uint16_t BufferByte);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
	
#endif

/** @} */
