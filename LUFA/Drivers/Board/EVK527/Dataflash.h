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
 *  \brief Board specific Dataflash driver header for the EVK527.
 *
 *  Board specific Dataflash driver header for the EVK527.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the dataflash driver
 *        dispatch header located in LUFA/Drivers/Board/Dataflash.h.
 */

/** \ingroup Group_Dataflash
 *  @defgroup Group_Dataflash_EVK527 EVK527
 *
 *  Board specific Dataflash driver header for the EVK527.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the dataflash driver
 *        dispatch header located in LUFA/Drivers/Board/Dataflash.h.
 *
 *  @{
 */

#ifndef __DATAFLASH_EVK527_H__
#define __DATAFLASH_EVK527_H__

	/* Includes: */
		#include "AT45DB321C.h"		

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_DATAFLASH_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Dataflash.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define DATAFLASH_CHIPCS_MASK                (1 << 6)
			#define DATAFLASH_CHIPCS_DDR                 DDRE
			#define DATAFLASH_CHIPCS_PORT                PORTE
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Constant indicating the total number of dataflash ICs mounted on the selected board. */
			#define DATAFLASH_TOTALCHIPS                 1

			/** Mask for no dataflash chip selected. */
			#define DATAFLASH_NO_CHIP                    DATAFLASH_CHIPCS_MASK

			/** Mask for the first dataflash chip selected. */
			#define DATAFLASH_CHIP1                      0
			
			/** Internal main memory page size for the board's dataflash IC. */
			#define DATAFLASH_PAGE_SIZE                  512

			/** Total number of pages inside the board's dataflash IC. */
			#define DATAFLASH_PAGES                      8192

		/* Inline Functions: */
			/** Selects a dataflash IC from the given page number, which should range from 0 to
			 *  ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1). For boards containing only one
			 *  dataflash IC, this will select DATAFLASH_CHIP1. If the given page number is outside
			 *  the total number of pages contained in the boards dataflash ICs, all dataflash ICs
			 *  are deselected.
			 *
			 *  \param[in] PageAddress  Address of the page to manipulate, ranging from
			 *                          ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1).
			 */
			static inline void Dataflash_SelectChipFromPage(const uint16_t PageAddress)
			{
				Dataflash_DeselectChip();
				
				if (PageAddress >= DATAFLASH_PAGES)
				  return;

				Dataflash_SelectChip(DATAFLASH_CHIP1);
			}

			/** Sends a set of page and buffer address bytes to the currently selected dataflash IC, for use with
			 *  dataflash commands which require a complete 24-byte address.
			 *
			 *  \param[in] PageAddress  Page address within the selected dataflash IC
			 *  \param[in] BufferByte   Address within the dataflash's buffer
			 */
			static inline void Dataflash_SendAddressBytes(uint16_t PageAddress, const uint16_t BufferByte)
			{	
				Dataflash_SendByte(PageAddress >> 5);
				Dataflash_SendByte((PageAddress << 3) | (BufferByte >> 8));
				Dataflash_SendByte(BufferByte);
			}
			
#endif

/** @} */
