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
 *  \brief Constants for HID report item attributes.
 *
 *  HID report item constants for report item attributes. Refer to the HID specification for
 *  details on each flag's meaning when applied to an IN, OUT or FEATURE item.
 */

/** \ingroup Group_HIDParser
 *  @defgroup Group_HIDReportItemConst HID Report Descriptor Item Constants
 *
 *  General HID constant definitions for HID Report Descriptor elements.
 *
 *  @{
 */

#ifndef __HIDREPORTDATA_H__
#define __HIDREPORTDATA_H__

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define HID_RI_DATA_SIZE_MASK        0x03
			#define HID_RI_TYPE_MASK             0x0C
			#define HID_RI_TAG_MASK              0xF0

			#define HID_RI_TYPE_MAIN             0x00
			#define HID_RI_TYPE_GLOBAL           0x04
			#define HID_RI_TYPE_LOCAL            0x08

			#define HID_RI_DATA_BITS_0           0x00
			#define HID_RI_DATA_BITS_8           0x01
			#define HID_RI_DATA_BITS_16          0x02
			#define HID_RI_DATA_BITS_32          0x03
			#define HID_RI_DATA_BITS(DataBits)   HID_RI_DATA_BITS_ ## DataBits
	#endif
	
	/* Public Interface - May be used in end-application: */
		/* Macros: */
		/** \name HID Input, Output and Feature Report Descriptor Item Flags */
		//@{
			#define HID_IOF_CONSTANT                   (1 << 0)
			#define HID_IOF_DATA                       (0 << 0)
			#define HID_IOF_VARIABLE                   (1 << 1)
			#define HID_IOF_ARRAY                      (0 << 1)
			#define HID_IOF_RELATIVE                   (1 << 2)
			#define HID_IOF_ABSOLUTE                   (0 << 2)
			#define HID_IOF_WRAP                       (1 << 3)
			#define HID_IOF_NO_WRAP                    (0 << 3)
			#define HID_IOF_NON_LINEAR                 (1 << 4)
			#define HID_IOF_LINEAR                     (0 << 4)
			#define HID_IOF_NO_PREFERRED_STATE         (1 << 5)
			#define HID_IOF_PREFERRED_STATE            (0 << 5)
			#define HID_IOF_NULLSTATE                  (1 << 6)
			#define HID_IOF_NO_NULL_POSITION           (0 << 6)
			#define HID_IOF_VOLATILE                   (1 << 7)
			#define HID_IOF_NON_VOLATILE               (0 << 7)
			#define HID_IOF_BUFFERED_BYTES             (1 << 8)
			#define HID_IOF_BITFIELD                   (0 << 8)
		//@}
		
		/** \name HID Report Descriptor Item Macros */
		//@{
			#define HID_RI_INPUT(DataBits)              (HID_RI_TYPE_MAIN   | 0x80 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_OUTPUT(DataBits)             (HID_RI_TYPE_MAIN   | 0x90 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_COLLECTION(DataBits)         (HID_RI_TYPE_MAIN   | 0xA0 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_FEATURE(DataBits)            (HID_RI_TYPE_MAIN   | 0xB0 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_END_COLLECTION(DataBits)     (HID_RI_TYPE_MAIN   | 0xC0 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_USAGE_PAGE(DataBits)         (HID_RI_TYPE_GLOBAL | 0x00 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_LOGICAL_MINIMUM(DataBits)    (HID_RI_TYPE_GLOBAL | 0x10 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_LOGICAL_MAXIMUM(DataBits)    (HID_RI_TYPE_GLOBAL | 0x20 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_PHYSICAL_MINIMUM(DataBits)   (HID_RI_TYPE_GLOBAL | 0x30 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_PHYSICAL_MAXIMUM(DataBits)   (HID_RI_TYPE_GLOBAL | 0x40 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_UNIT_EXPONENT(DataBits)      (HID_RI_TYPE_GLOBAL | 0x50 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_UNIT(DataBits)               (HID_RI_TYPE_GLOBAL | 0x60 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_REPORT_SIZE(DataBits)        (HID_RI_TYPE_GLOBAL | 0x70 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_REPORT_ID(DataBits)          (HID_RI_TYPE_GLOBAL | 0x80 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_REPORT_COUNT(DataBits)       (HID_RI_TYPE_GLOBAL | 0x90 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_PUSH(DataBits)               (HID_RI_TYPE_GLOBAL | 0xA0 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_POP(DataBits)                (HID_RI_TYPE_GLOBAL | 0xB0 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_USAGE(DataBits)              (HID_RI_TYPE_LOCAL  | 0x00 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_USAGE_MINIMUM(DataBits)      (HID_RI_TYPE_LOCAL  | 0x10 | HID_RI_DATA_BITS(DataBits))
			#define HID_RI_USAGE_MAXIMUM(DataBits)      (HID_RI_TYPE_LOCAL  | 0x20 | HID_RI_DATA_BITS(DataBits))
		//@}
		
/** @} */

#endif

