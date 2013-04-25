/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief LUFA Custom Board Dataflash Hardware Driver (Template)
 *
 *  This is a stub driver header file, for implementing custom board
 *  layout hardware with compatible LUFA board specific drivers. If
 *  the library is configured to use the BOARD_USER board mode, this
 *  driver file should be completed and copied into the "/Board/" folder
 *  inside the application's folder.
 *
 *  This stub is for the board-specific component of the LUFA Dataflash
 *  driver.
*/

#ifndef __DATAFLASH_USER_H__
#define __DATAFLASH_USER_H__

	/* Includes: */
		// TODO: Add any required includes here

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_DATAFLASH_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Dataflash.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define DATAFLASH_CHIPCS_MASK                // TODO: Replace this with a mask of all the /CS pins of all Dataflashes
			#define DATAFLASH_CHIPCS_DDR                 // TODO: Replace with the DDR register name for the board's Dataflash ICs
			#define DATAFLASH_CHIPCS_PORT                // TODO: Replace with the PORT register name for the board's Dataflash ICs
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Constant indicating the total number of dataflash ICs mounted on the selected board. */
			#define DATAFLASH_TOTALCHIPS                 1 // TODO: Replace with the number of Dataflashes on the board, max 2

			/** Mask for no dataflash chip selected. */
			#define DATAFLASH_NO_CHIP                    0

			/** Mask for the first dataflash chip selected. */
			#define DATAFLASH_CHIP1                      // TODO: Replace with mask with the pin attached to the first Dataflash /CS set

			/** Mask for the second dataflash chip selected. */
			#define DATAFLASH_CHIP2                      // TODO: Replace with mask with the pin attached to the second Dataflash /CS set

			/** Internal main memory page size for the board's dataflash ICs. */
			#define DATAFLASH_PAGE_SIZE                  // TODO: Replace with the page size for the Dataflash ICs

			/** Total number of pages inside each of the board's dataflash ICs. */
			#define DATAFLASH_PAGES                      // TODO: Replace with the total number of pages inside one of the Dataflash ICs

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			/** Initializes the dataflash driver so that commands and data may be sent to an attached dataflash IC.
			 *  The microcontroller's SPI driver MUST be initialized before any of the dataflash commands are used.
			 */
			static inline void Dataflash_Init(void)
			{
				DATAFLASH_CHIPCS_DDR  |= DATAFLASH_CHIPCS_MASK;
				DATAFLASH_CHIPCS_PORT |= DATAFLASH_CHIPCS_MASK;
			}

			/** Sends a byte to the currently selected dataflash IC, and returns a byte from the dataflash.
			 *
			 *  \param[in] Byte  Byte of data to send to the dataflash
			 *
			 *  \return Last response byte from the dataflash
			 */
			static inline uint8_t Dataflash_TransferByte(const uint8_t Byte) ATTR_ALWAYS_INLINE;
			static inline uint8_t Dataflash_TransferByte(const uint8_t Byte)
			{
				// TODO
			}

			/** Sends a byte to the currently selected dataflash IC, and ignores the next byte from the dataflash.
			 *
			 *  \param[in] Byte  Byte of data to send to the dataflash
			 */
			static inline void Dataflash_SendByte(const uint8_t Byte) ATTR_ALWAYS_INLINE;
			static inline void Dataflash_SendByte(const uint8_t Byte)
			{
				// TODO
			}

			/** Sends a dummy byte to the currently selected dataflash IC, and returns the next byte from the dataflash.
			 *
			 *  \return Last response byte from the dataflash
			 */
			static inline uint8_t Dataflash_ReceiveByte(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Dataflash_ReceiveByte(void)
			{
				// TODO
			}

			/** Determines the currently selected dataflash chip.
			 *
			 *  \return Mask of the currently selected Dataflash chip, either \ref DATAFLASH_NO_CHIP if no chip is selected
			 *          or a DATAFLASH_CHIPn mask (where n is the chip number).
			 */
			static inline uint8_t Dataflash_GetSelectedChip(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Dataflash_GetSelectedChip(void)
			{
				return (~DATAFLASH_CHIPCS_PORT & DATAFLASH_CHIPCS_MASK);
			}

			/** Selects the given dataflash chip.
			 *
			 *  \param[in]  ChipMask  Mask of the Dataflash IC to select, in the form of a \c DATAFLASH_CHIPn mask (where n is
			 *              the chip number).
			 */
			static inline void Dataflash_SelectChip(const uint8_t ChipMask) ATTR_ALWAYS_INLINE;
			static inline void Dataflash_SelectChip(const uint8_t ChipMask)
			{
				DATAFLASH_CHIPCS_PORT = ((DATAFLASH_CHIPCS_PORT | DATAFLASH_CHIPCS_MASK) & ~ChipMask);
			}

			/** Deselects the current dataflash chip, so that no dataflash is selected. */
			static inline void Dataflash_DeselectChip(void) ATTR_ALWAYS_INLINE;
			static inline void Dataflash_DeselectChip(void)
			{
				Dataflash_SelectChip(DATAFLASH_NO_CHIP);
			}

			/** Selects a dataflash IC from the given page number, which should range from 0 to
			 *  ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1). For boards containing only one
			 *  dataflash IC, this will select DATAFLASH_CHIP1. If the given page number is outside
			 *  the total number of pages contained in the boards dataflash ICs, all dataflash ICs
			 *  are deselected.
			 *
			 *  \param[in] PageAddress  Address of the page to manipulate, ranging from
			 *                          0 to ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1).
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

			/** Sends a set of page and buffer address bytes to the currently selected dataflash IC, for use with
			 *  dataflash commands which require a complete 24-bit address.
			 *
			 *  \param[in] PageAddress  Page address within the selected dataflash IC
			 *  \param[in] BufferByte   Address within the dataflash's buffer
			 */
			static inline void Dataflash_SendAddressBytes(uint16_t PageAddress,
			                                              const uint16_t BufferByte)
			{
				#if (DATAFLASH_TOTALCHIPS == 2)
					PageAddress >>= 1;
				#endif

				Dataflash_SendByte(PageAddress >> 5);
				Dataflash_SendByte((PageAddress << 3) | (BufferByte >> 8));
				Dataflash_SendByte(BufferByte);
			}
		#endif

#endif

