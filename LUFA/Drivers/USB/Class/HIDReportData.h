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
 *  Constants for HID report item attributes. Refer to the HID specification for details on each
 *  flag's meaning when applied to an IN, OUT or FEATURE item.
 */

#ifndef __HIDREPORTDATA_H__
#define __HIDREPORTDATA_H__

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** HID_ReportItem_t.ItemFlags flag for constant data. */
			#define IOF_CONSTANT             (1 << 0)

			/** HID_ReportItem_t.ItemFlags flag for data. */
			#define IOF_DATA                 (0 << 0)

			/** HID_ReportItem_t.ItemFlags flag for variable data. */
			#define IOF_VARIABLE             (1 << 1)

			/** HID_ReportItem_t.ItemFlags flag for array data. */
			#define IOF_ARRAY                (0 << 1)

			/** HID_ReportItem_t.ItemFlags flag for relative data. */
			#define IOF_RELATIVE             (1 << 2)

			/** HID_ReportItem_t.ItemFlags flag for absolute data. */
			#define IOF_ABSOLUTE             (0 << 2)

			/** HID_ReportItem_t.ItemFlags flag for wrapped value data. */
			#define IOF_WRAP                 (1 << 3)

			/** HID_ReportItem_t.ItemFlags flag for non-wrapped value data. */
			#define IOF_NOWRAP               (0 << 3)

			/** HID_ReportItem_t.ItemFlags flag for non linear data. */
			#define IOF_NONLINEAR            (1 << 4)

			/** HID_ReportItem_t.ItemFlags flag for linear data. */
			#define IOF_LINEAR               (0 << 4)

			/** HID_ReportItem_t.ItemFlags flag for no preferred state. */
			#define IOF_NOPREFERRED          (1 << 5)

			/** HID_ReportItem_t.ItemFlags flag for preferred state items. */
			#define IOF_PREFERREDSTATE       (0 << 5)

			/** HID_ReportItem_t.ItemFlags flag for null state items. */
			#define IOF_NULLSTATE            (1 << 6)

			/** HID_ReportItem_t.ItemFlags flag for no null position data. */
			#define IOF_NONULLPOSITION       (0 << 6)

			/** HID_ReportItem_t.ItemFlags flag for buffered bytes. */
			#define IOF_BUFFEREDBYTES        (1 << 8)

			/** HID_ReportItem_t.ItemFlags flag for bit field data. */
			#define IOF_BITFIELD             (0 << 8)

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define DATA_SIZE_MASK           0b00000011
			#define TYPE_MASK                0b00001100
			#define TAG_MASK                 0b11110000

			#define DATA_SIZE_0              0b00000000
			#define DATA_SIZE_1              0b00000001
			#define DATA_SIZE_2              0b00000010
			#define DATA_SIZE_4              0b00000011
			
			#define TYPE_MAIN                0b00000000
			#define TYPE_GLOBAL              0b00000100
			#define TYPE_LOCAL               0b00001000
			
			#define TAG_MAIN_INPUT           0b10000000
			#define TAG_MAIN_OUTPUT          0b10010000
			#define TAG_MAIN_COLLECTION      0b10100000
			#define TAG_MAIN_FEATURE         0b10110000
			#define TAG_MAIN_ENDCOLLECTION   0b11000000
			#define TAG_GLOBAL_USAGEPAGE     0b00000000
			#define TAG_GLOBAL_LOGICALMIN    0b00010000
			#define TAG_GLOBAL_LOGICALMAX    0b00100000
			#define TAG_GLOBAL_PHYSMIN       0b00110000
			#define TAG_GLOBAL_PHYSMAX       0b01000000
			#define TAG_GLOBAL_UNITEXP       0b01010000
			#define TAG_GLOBAL_UNIT          0b01100000
			#define TAG_GLOBAL_REPORTSIZE    0b01110000
			#define TAG_GLOBAL_REPORTID      0b10000000
			#define TAG_GLOBAL_REPORTCOUNT   0b10010000
			#define TAG_GLOBAL_PUSH          0b10100000
			#define TAG_GLOBAL_POP           0b10110000
			#define TAG_LOCAL_USAGE          0b00000000
			#define TAG_LOCAL_USAGEMIN       0b00010000
			#define TAG_LOCAL_USAGEMAX       0b00100000
	#endif
		
#endif
