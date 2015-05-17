/*
             LUFA Library
     Copyright (C) Dean Camera, 2015.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2015  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Common definitions and declarations for the library USB Android Open Accessory Class driver.
 *
 *  Common definitions and declarations for the library USB Android Open Accessory Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassAOA
 *  \defgroup Group_USBClassAOACommon  Common Class Definitions
 *
 *  \section Sec_USBClassAOACommon_ModDescription Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  Android Open Accessory Class.
 *
 *  @{
 */

#ifndef _AOA_CLASS_COMMON_H_
#define _AOA_CLASS_COMMON_H_

	/* Includes: */
		#include "../../Core/StdDescriptors.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_AOA_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Macros: */
		/** Product ID value in a Device Descriptor to indicate an Android device in Open Accessory mode. */
		#define ANDROID_ACCESSORY_PRODUCT_ID        0x2D00

		/** Product ID value in a Device Descriptor to indicate an Android device in Open Accessory and Android Debug mode. */
		#define ANDROID_ACCESSORY_ADB_PRODUCT_ID    0x2D01

	/* Enums: */
		/** Enum for possible Class, Subclass and Protocol values of device and interface descriptors relating to the
		 *  Android Open Accessory class.
		 */
		enum AOA_Descriptor_ClassSubclassProtocol_t
		{
			AOA_CSCP_AOADataClass    = 0xFF, /**< Descriptor Class value indicating that the device or interface
			                                  *   belongs to the AOA data class.
			                                  */
			AOA_CSCP_AOADataSubclass = 0xFF, /**< Descriptor Subclass value indicating that the device or interface
			                                  *   belongs to AOA data subclass.
			                                  */
			AOA_CSCP_AOADataProtocol = 0x00, /**< Descriptor Protocol value indicating that the device or interface
			                                  *   belongs to the AOA data class protocol.
			                                  */
		};

		/** Enum for the Android Open Accessory class specific control requests that can be issued by the USB bus host. */
		enum AOA_ClassRequests_t
		{
			AOA_REQ_GetAccessoryProtocol    = 0x33, /**< Android Open Accessory control request to retrieve the device's supported Accessory Protocol version. */
			AOA_REQ_SendString              = 0x34, /**< Android Open Accessory control request to set an accessory property string in the device. */
			AOA_REQ_StartAccessoryMode      = 0x35, /**< Android Open Accessory control request to switch the device into Accessory mode. */
		};

		/** Enum for the possible Android Open Accessory property string indexes. */
		enum AOA_Strings_t
		{
			AOA_STRING_Manufacturer         = 0, /**< Index of the Manufacturer property string. */
			AOA_STRING_Model                = 1, /**< Index of the Model Name property string. */
			AOA_STRING_Description          = 2, /**< Index of the Description property string. */
			AOA_STRING_Version              = 3, /**< Index of the Version Number property string. */
			AOA_STRING_URI                  = 4, /**< Index of the URI Information property string. */
			AOA_STRING_Serial               = 5, /**< Index of the Serial Number property string. */

			#if !defined(__DOXYGEN__)
			AOA_STRING_TOTAL_STRINGS
			#endif
		};

		/** Enum for the possible Android Open Accessory protocol versions. */
		enum AOA_Protocols_t
		{
			AOA_PROTOCOL_AccessoryV1        = 0x0001, /**< Android Open Accessory version 1. */
			AOA_PROTOCOL_AccessoryV2        = 0x0002, /**< Android Open Accessory version 2. */
		};

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */


