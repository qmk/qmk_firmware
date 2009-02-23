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
 *  This file is the master dispatch header file for the board-specific dataflash driver, for boards containing
 *  dataflash ICs for external non-volatile storage.
 *
 *  User code should include this file, which will in turn include the correct dataflash driver header file for
 *  the currently selected board.
 *
 *  If the BOARD value is set to BOARD_USER, this will include the /Board/Dataflash.h file in the user project
 *  directory.
 */
 
#ifndef __DATAFLASH_H__
#define __DATAFLASH_H__

	/* Macros: */
	#if !defined(__DOXYGEN__)
		#define INCLUDE_FROM_DATAFLASH_H
		#define INCLUDE_FROM_BOARD_DRIVER
	#endif

	/* Includes: */
	#include "../AT90USBXXX/SPI.h"
	#include "../../Common/Common.h"
	
	#if !defined(BOARD)
		#error BOARD must be set in makefile to a value specified in BoardTypes.h.
	#elif (BOARD == BOARD_USBKEY)
		#include "USBKEY/Dataflash.h"
	#elif (BOARD == BOARD_STK525)
		#include "STK525/Dataflash.h"
	#elif (BOARD == BOARD_STK526)
		#include "STK526/Dataflash.h"
	#elif (BOARD == BOARD_USER)
		#include "Board/Dataflash.h"
	#else
		#error The selected board does not contain a dataflash IC.
	#endif
	
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Returns the mask of the currently selected Dataflash chip, either DATAFLASH_NO_CHIP or a
			 *  DATAFLASH_CHIPn mask (where n is the chip number).
			 */
			#define Dataflash_GetSelectedChip()          (DATAFLASH_CHIPCS_PORT & DATAFLASH_CHIPCS_MASK)

			/** Selects the dataflash chip given as a chip mask, in the form of DATAFLASH_CHIPn (where n
			 *  is the chip number).
			 */
			#define Dataflash_SelectChip(mask)   MACROS{ DATAFLASH_CHIPCS_PORT = ((DATAFLASH_CHIPCS_PORT \
			                                             & ~DATAFLASH_CHIPCS_MASK) | mask);              }MACROE
			
			/** Deselects the current dataflash chip, so that no dataflash is selected. */
			#define Dataflash_DeselectChip()             Dataflash_SelectChip(DATAFLASH_NO_CHIP)

		/* Inline Functions: */
			/** Initializes the dataflash driver (including the SPI driver) so that commands and data may be
			 *  sent to an attached dataflash IC.
			 *
			 *  \param PrescalerMask  SPI prescaler mask, see SPI.h documentation
			 */
			static inline void Dataflash_Init(const uint8_t PrescalerMask)
			{
				DATAFLASH_CHIPCS_DDR  |= DATAFLASH_CHIPCS_MASK;
				DATAFLASH_CHIPCS_PORT |= DATAFLASH_CHIPCS_MASK;

				SPI_Init(PrescalerMask, true);
			}

			/** Sends a byte to the currently selected dataflash IC, and returns a byte from the dataflash.
			 *
			 *  \param Byte of data to send to the dataflash
			 *
			 *  \return Last response byte from the dataflash
			 */
			static inline uint8_t Dataflash_TransferByte(const uint8_t Byte) ATTR_ALWAYSINLINE;
			static inline uint8_t Dataflash_TransferByte(const uint8_t Byte)
			{
				return SPI_TransferByte(Byte);
			}

			/** Sends a byte to the currently selected dataflash IC, and ignores the next byte from the dataflash.
			 *
			 *  \param Byte of data to send to the dataflash
			 */
			static inline void Dataflash_SendByte(const uint8_t Byte) ATTR_ALWAYSINLINE;
			static inline void Dataflash_SendByte(const uint8_t Byte)
			{
				SPI_SendByte(Byte);
			}
			
			/** Sends a dummy byte to the currently selected dataflash IC, and returns the next byte from the dataflash.
			 *
			 *  \return Last response byte from the dataflash
			 */
			static inline uint8_t Dataflash_ReceiveByte(void) ATTR_ALWAYSINLINE ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Dataflash_ReceiveByte(void)
			{
				return SPI_ReceiveByte();
			}
			
			/** Toggles the select line of the currently selected dataflash IC, so that it is ready to receive
			 *  a new command.
			 */
			static inline void Dataflash_ToggleSelectedChipCS(void)
			{
				#if (DATAFLASH_TOTALCHIPS == 2)
					uint8_t SelectedChipMask = Dataflash_GetSelectedChip();
					
					Dataflash_DeselectChip();
					Dataflash_SelectChip(SelectedChipMask);
				#else
					Dataflash_DeselectChip();
					Dataflash_SelectChip(DATAFLASH_CHIP1);	
				#endif
			}

			/** Spinloops while the currently selected dataflash is busy executing a command, such as a main
			 *  memory page program or main memory to buffer transfer.
			 */
			static inline void Dataflash_WaitWhileBusy(void)
			{
				Dataflash_ToggleSelectedChipCS();
				Dataflash_SendByte(DF_CMD_GETSTATUS);
				while (!(Dataflash_ReceiveByte() & DF_STATUS_READY));
			}

			/** Selects a dataflash IC from the given page number, which should range from 0 to
			 *  ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1). For boards containing only one
			 *  dataflash IC, this will select DATAFLASH_CHIP1. If the given page number is outside the total number
			 *  of pages contained in the boards dataflash ICs, all dataflash ICs are deselected.
			 *
			 *  \param PageAddress  Address of the page to manipulate, ranging from
			 *                      ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1).
			 */
			static inline void Dataflash_SelectChipFromPage(const uint16_t PageAddress)
			{
				Dataflash_DeselectChip();
				
				if (PageAddress >= (DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS))
				  return;

				#if (DATAFLASH_TOTALCHIPS == 2)
					if (PageAddress & 0x01)
					  Dataflash_SelectChip(DATAFLASH_CHIP2);
					else
					  Dataflash_SelectChip(DATAFLASH_CHIP1);
				#else
					Dataflash_SelectChip(DATAFLASH_CHIP1);
				#endif
			}

			/** Sends a set of page and buffer address bytes to the currently selected dataflash IC, for use with
			 *  dataflash commands which require a complete 24-byte address.
			 *
			 *  \param PageAddress  Page address within the selected dataflash IC
			 *  \param BufferByte   Address within the dataflash's buffer
			 */
			static inline void Dataflash_SendAddressBytes(uint16_t PageAddress, const uint16_t BufferByte)
			{	
				#if (DATAFLASH_TOTALCHIPS == 2)
					PageAddress >>= 1;
				#endif

				Dataflash_SendByte(PageAddress >> 5);
				Dataflash_SendByte((PageAddress << 3) | (BufferByte >> 8));
				Dataflash_SendByte(BufferByte);
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
	
#endif
