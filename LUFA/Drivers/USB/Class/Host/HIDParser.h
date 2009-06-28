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
 *  USB Human Interface Device (HID) Class report descriptor processing routines. This file allows for the easy
 *  parsing of the complex HID report descriptor, which describes the data that the device transmits to the host.
 *
 */
 
/** \ingroup Group_USB
 *  @defgroup Group_HIDParser HID Report Parser
 *
 *  Functions, macros, variables, enums and types related to the parsing of HID class device report descriptors.
 *
 *  The processed HID report is presented back to the user application as a flat structure containing each report
 *  item's IN, OUT and FEATURE (if desired) items along with each item's attributes.
 *
 *  This library portion also allows for easy setting and retrieval of data from a HID report, including devices
 *  with multiple reports on the one HID interface.
 *
 *  By default, FEATURE reports and IN/OUT reports with constant data are ignored in the HID report when processed
 *  to save on memory. This can be overridden by defining the HID_ENABLE_FEATURE_PROCESSING or
 *  HID_INCLUDE_CONSTANT_DATA_ITEMS tokens in the user project makefile, passing them to the compiler via the -D
 *  switch.
 *
 *  @{
 */

#ifndef __HIDPARSER_H__
#define __HIDPARSER_H__

	/* Includes: */
		#include <string.h>
		#include <stdbool.h>

		#include "HIDReportData.h"

		#include "../../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor checks and defines: */
		#if !defined(HID_STATETABLE_STACK_DEPTH) || defined(__DOXYGEN__)
			/** Constant indicating the maximum stack depth of the state table. A larger state table
			 *  allows for more PUSH/POP report items to be nested, but consumes more memory. By default
			 *  this is set to 3 levels (allowing for two PUSHes to be nested) but this can be overridden by
			 *  defining HID_STATETABLE_STACK_DEPTH to another value in the user project makefile, passing the
			 *  define to the compiler using the -D compiler switch.
			 */
			#define HID_STATETABLE_STACK_DEPTH    3
		#endif
		
		#if !defined(HID_USAGE_STACK_DEPTH) || defined(__DOXYGEN__)
			/** Constant indicating the maximum stack depth of the usage table. A larger usage table
			 *  allows for more USAGE items to be indicated sequentially for REPORT COUNT entries of more than
			 *  one, but requires more stack space. By default this is set to 8 levels (allowing for a report
			 *  item with a count of 8) but this can be overridden by defining HID_USAGE_STACK_DEPTH to another
			 *  value in the user project makefile, passing the define to the compiler using the -D compiler
			 *  switch.
			 */
			#define HID_USAGE_STACK_DEPTH         8
		#endif

		#if !defined(HID_MAX_COLLECTIONS) || defined(__DOXYGEN__)
			/** Constant indicating the maximum number of COLLECTION items (nested or unnested) that can be
			 *  processed in the report item descriptor. A large value allows for more COLLECTION items to be
			 *  processed, but consumes more memory. By default this is set to 5 collections, but this can be
			 *  overridden by defining HID_MAX_COLLECTIONS to another value in the user project makefile, passing
			 *  the define to the compiler using the -D compiler switch.
			 */
			#define HID_MAX_COLLECTIONS           5
		#endif
		
		#if !defined(HID_MAX_REPORTITEMS) || defined(__DOXYGEN__)
			/** Constant indicating the maximum number of report items (IN, OUT or FEATURE if enabled) that can be
			 *  processed in the report item descriptor. A large value allows for more report items to be
			 *  processed, but consumes more memory. By default this is set to 30 items, but this can be
			 *  overridden by defining HID_MAX_REPORTITEMS to another value in the user project makefile, passing
			 *  the define to the compiler using the -D compiler switch.
			 */
			#define HID_MAX_REPORTITEMS           30
		#endif

	/* Public Interface - May be used in end-application: */
		/* Enums: */
			/** Enum for indicating what type of report item an entry in a \ref HID_ReportInfo_t ReportItem array is */
			enum HID_ReportItemTypes_t
			{
				REPORT_ITEM_TYPE_In                   = 0, /**< Indicates that the item is an IN report type. */
				REPORT_ITEM_TYPE_Out                  = 1, /**< Indicates that the item is an OUT report type. */
				REPORT_ITEM_TYPE_Feature              = 2, /**< Indicates that the item is a FEATURE report type. */
			};
			
			/** Enum for the possible error codes in the return value of the \ref USB_ProcessHIDReport() function */
			enum HID_Parse_ErrorCodes_t
			{
				HID_PARSE_Successful                  = 0, /**< Successful parse of the HID report descriptor, no error. */
				HID_PARSE_HIDStackOverflow            = 1, /**< More than \ref HID_STATETABLE_STACK_DEPTH nested PUSHes in the report. */ 
				HID_PARSE_HIDStackUnderflow           = 2, /**< A POP was found when the state table stack was empty. */
				HID_PARSE_InsufficientReportItems     = 3, /**< More than \ref HID_MAX_REPORTITEMS report items in the report. */
				HID_PARSE_UnexpectedEndCollection     = 4, /**< END COLLECTION found without matching COLLECTION item. */
				HID_PARSE_InsufficientCollectionPaths = 5, /**< More than \ref HID_MAX_COLLECTIONS collections in the report. */
				HID_PARSE_UsageStackOverflow          = 6, /**< More than \ref HID_USAGE_STACK_DEPTH usages listed in a row. */
			};
		
		/* Type Defines: */		
			/** Type define for an attribute with both minimum and maximum values (e.g. Logical Min/Max). */
			typedef struct
			{
				uint32_t                     Minimum; /**< Minimum value for the attribute. */
				uint32_t                     Maximum; /**< Maximum value for the attribute. */
			} HID_MinMax_t;

			/** Type define for the Unit attributes of a report item. */
			typedef struct
			{
				uint32_t                     Type;     /**< Unit type (refer to HID specifications for details). */
				uint8_t                      Exponent; /**< Unit exponent (refer to HID specifications for details). */
			} HID_Unit_t;
			
			/** Type define for the Usage attributes of a report item. */
			typedef struct
			{
				uint16_t                     Page;   /**< Usage page of the report item. */
				uint16_t                     Usage;  /**< Usage of the report item. */
				HID_MinMax_t                 MinMax; /**< Usage minimum and maximum of the report item. */
			} HID_Usage_t;

			/** Type define for a COLLECTION object. Contains the collection attributes and a reference to the
			 *  parent collection if any.
			 */
			typedef struct CollectionPath
			{
				uint8_t                      Type;   /**< Collection type (e.g. "Generic Desktop"). */
				HID_Usage_t                  Usage;  /**< Collection usage. */
				struct CollectionPath*       Parent; /**< Reference to parent collection, or NULL if root collection. */
			} HID_CollectionPath_t;

			/** Type define for all the data attributes of a report item, except flags. */
			typedef struct
			{
				uint8_t                      BitSize;  /**< Size in bits of the report item's data. */
				
				HID_Usage_t                  Usage;    /**< Usage of the report item. */
				HID_Unit_t                   Unit;     /**< Unit type and exponent of the report item. */
				HID_MinMax_t                 Logical;  /**< Logical minimum and maximum of the report item. */
				HID_MinMax_t                 Physical; /**< Physical minimum and maximum of the report item. */
			} HID_ReportItem_Attributes_t;
			
			/** Type define for a report item (IN, OUT or FEATURE) attributes and other details. */
			typedef struct
			{
				uint16_t                     BitOffset;      /**< Bit offset in the IN, OUT or FEATURE report of the item. */
				uint8_t                      ItemType;       /**< Report item type, a value in HID_Types_t. */
				uint16_t                     ItemFlags;      /**< Item data flags, such as constant/variable, etc. */
				uint8_t                      ReportID;       /**< Report ID this item belongs to, or 0x00 if device has only one report */
				HID_CollectionPath_t*        CollectionPath; /**< Collection path of the item. */

				HID_ReportItem_Attributes_t  Attributes;     /**< Report item attributes. */
							
				uint32_t                     Value;          /**< Current value of the report item. */
			} HID_ReportItem_t;

			/** Type define for a complete processed HID report, including all report item data and collections. */
			typedef struct
			{
				uint8_t                      TotalReportItems; /**< Total number of report items stored in the
				                                                *   ReportItems array. */

				HID_ReportItem_t             ReportItems[HID_MAX_REPORTITEMS]; /**< Report items array, including
			                                                                    *   all IN, OUT and FEATURE items. */

				HID_CollectionPath_t         CollectionPaths[HID_MAX_COLLECTIONS]; /**< All collection items, referenced
				                                                                    *   by the report items. */
			} HID_ReportInfo_t;
			
		/* Function Prototypes: */
			/** Function to process a given HID report returned from an attached device, and store it into a given
			 *  \ref HID_ReportInfo_t structure.
			 *
			 *  \param[in] ReportData  Buffer containing the device's HID report table
			 *  \param[in] ReportSize  Size in bytes of the HID report table
			 *  \param[out] ParserData  Pointer to a \ref HID_ReportInfo_t instance for the parser output
			 *
			 *  \return A value in the \ref HID_Parse_ErrorCodes_t enum
			 */
			uint8_t USB_ProcessHIDReport(const uint8_t* ReportData, uint16_t ReportSize, HID_ReportInfo_t* const ParserData)
			                             ATTR_NON_NULL_PTR_ARG(1, 3);

			/** Extracts the given report item's value out of the given HID report and places it into the Value
			 *  member of the report item's \ref HID_ReportItem_t structure.
			 *
			 *  \param[in] ReportData  Buffer containing an IN or FEATURE report from an attached device
			 *  \param[in,out] ReportItem  Pointer to the report item of interest in a \ref HID_ReportInfo_t ReportItem array
			 *
			 *  \returns Boolean true if the item to retrieve was located in the given report, false otherwise
			 */
			bool USB_GetHIDReportItemInfo(const uint8_t* ReportData, HID_ReportItem_t* const ReportItem)
			                              ATTR_NON_NULL_PTR_ARG(1, 2);

			/** Retrieves the given report item's value out of the Value member of the report item's
			 *  \ref HID_ReportItem_t structure and places it into the correct position in the HID report
			 *  buffer. The report buffer is assumed to have the appropriate bits cleared before calling
			 *  this function (i.e., the buffer should be explicitly cleared before report values are added).
			 *
			 *  If the device has multiple HID reports, the report ID is set to the report ID of the given item.
			 *
			 *  \param[out] ReportData  Buffer holding the current OUT report data
			 *  \param[in] ReportItem  Pointer to the report item of interest in a \ref HID_ReportInfo_t ReportItem array
			 */
			void USB_SetHIDReportItemInfo(uint8_t* ReportData, const HID_ReportItem_t* ReportItem)
			                              ATTR_NON_NULL_PTR_ARG(1, 2);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Type Defines: */
			typedef struct
			{
				 HID_ReportItem_Attributes_t Attributes;
				 uint8_t                     ReportCount;
				 uint8_t                     ReportID;
			} HID_StateTable_t;
	#endif
			
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
