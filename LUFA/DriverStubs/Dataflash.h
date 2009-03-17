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

/*
   This is a stub driver header file, for implementing custom board
   layout hardware with compatible LUFA board specific drivers. If
   the library is configured to use the BOARD_USER board mode, this
   driver file should be completed and copied into the "/Board/" folder
   inside the application's folder.

   This stub is for the board-specific component of the LUFA Dataflash
   driver.
*/

#ifndef __DATAFLASH_USER_H__
#define __DATAFLASH_USER_H__

	/* Includes: */
		// TODO: Add any required includes here

	/* Preprocessor Checks: */
		#if !defined(INCLUDE_FROM_DATAFLASH_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Dataflash.h instead.
		#endif
		
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define DATAFLASH_CHIPCS_MASK                // TODO: Replace this with a mask of all the /CS pins of all dataflashes
			#define DATAFLASH_CHIPCS_DDR                 // TODO: Replace with the DDR register name for the board's Dataflash ICs
			#define DATAFLASH_CHIPCS_PORT                // TODO: Replace with the PORT register name for the board's Dataflash ICs
	#endif
	
	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Constant indicating the total number of dataflash ICs mounted on the selected board. */
			#define DATAFLASH_TOTALCHIPS                 // TODO: Replace with the number of dataflashes on the board, max 2

			/** Mask for no dataflash chip selected. */
			#define DATAFLASH_NO_CHIP                    DATAFLASH_CHIPCS_MASK

			/** Mask for the first dataflash chip selected. */
			#define DATAFLASH_CHIP1                      // TODO: Replace with mask to select the first Dataflash chip

			/** Mask for the second dataflash chip selected. */
			#define DATAFLASH_CHIP2                      // TODO: Replace with mask to select the second Dataflash chip, if available
			
			/** Internal main memory page size for the board's dataflash ICs. */
			#define DATAFLASH_PAGE_SIZE                  // TODO: Replace with the page size for the Dataflash ICs

			/** Total number of pages inside each of the board's dataflash ICs. */
			#define DATAFLASH_PAGES                      // TODO: Replace with the total number of pages inside one of the Dataflash ICs

		/* Inline Functions: */
			/** Selects a dataflash IC from the given page number, which should range from 0 to
			 *  ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1). For boards containing only one
			 *  dataflash IC, this will select DATAFLASH_CHIP1. If the given page number is outside
			 *  the total number of pages contained in the boards dataflash ICs, all dataflash ICs
			 *  are deselected.
			 *
			 *  \param PageAddress  Address of the page to manipulate, ranging from
			 *                      ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1).
			 */
			static inline void Dataflash_SelectChipFromPage(const uint16_t PageAddress)
			{
				Dataflash_DeselectChip();
				
				if (PageAddress >= (DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS))
				  return;

				// TODO: If more than one dataflash chip, select the correct chip from the page address here
				Dataflash_SelectChip(DATAFLASH_CHIP1);
			}

			/** Sends a set of page and buffer address bytes to the currently selected dataflash IC, for use with
			 *  dataflash commands which require a complete 24-byte address.
			 *
			 *  \param PageAddress  Page address within the selected dataflash IC
			 *  \param BufferByte   Address within the dataflash's buffer
			 */
			static inline void Dataflash_SendAddressBytes(uint16_t PageAddress, const uint16_t BufferByte)
			{	
				// TODO: If more than one dataflash chip, adjust absolute page address to be correct for the current chip,
				//       also the shifts may need to be altered to suit the dataflash model being used				
				Dataflash_SendByte(PageAddress >> 5);
				Dataflash_SendByte((PageAddress << 3) | (BufferByte >> 8));
				Dataflash_SendByte(BufferByte);
			}
			
#endif
