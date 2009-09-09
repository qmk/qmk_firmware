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

/** \ingroup Group_USBClassSI
 *  @defgroup Group_USBClassSICommon  Common Class Definitions
 *
 *  \section Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  Still Image Class.
 *
 *  @{
 */

#ifndef _SI_CLASS_COMMON_H_
#define _SI_CLASS_COMMON_H_

	/* Includes: */
		#include "../../USB.h"

		#include <string.h>
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Macros: */
		/** Length in bytes of a given Unicode string's character length
		 *
		 *  \param[in] chars  Total number of Unicode characters in the string
		 *
		 *  \return Number of bytes of the given unicode string
		 */
		#define UNICODE_STRING_LENGTH(chars)   (chars << 1)
		
		/** Used in the DataLength field of a PIMA container, to give the total container size in bytes for
		 *  a command container.
		 *
		 *  \param[in] params  Number of parameters which are to be sent in the Param field of the container
		 */
		#define PIMA_COMMAND_SIZE(params)      ((sizeof(SI_PIMA_Container_t) - sizeof(((SI_PIMA_Container_t*)NULL)->Params)) + \
		                                        (params * sizeof(uint32_t)))

		/** Used in the DataLength field of a PIMA container, to give the total container size in bytes for
		 *  a data container.
		 *
		 *  \param[in] datalen  Length in bytes of the data in the container
		 */
		#define PIMA_DATA_SIZE(datalen)        ((sizeof(SI_PIMA_Container_t) - sizeof(((SI_PIMA_Container_t*)NULL)->Params)) + \
		                                        datalen)

	/* Enums: */
		/** Enum for the possible PIMA contains types. */
		enum SI_PIMA_Container_Types_t
		{
			CType_Undefined         = 0, /**< Undefined container type */
			CType_CommandBlock      = 1, /**< Command Block container type */
			CType_DataBlock         = 2, /**< Data Block container type */
			CType_ResponseBlock     = 3, /**< Response container type */
			CType_EventBlock        = 4, /**< Event Block container type */
		};	
		
	/* Enums: */
		/** Enums for the possible status codes of a returned Response Block from an attached PIMA compliant Still Image device. */
		enum SI_PIMA_ResponseCodes_t
		{
			PIMA_RESPONSE_OK                     = 1, /**< Response code indicating no error in the issued command */
			PIMA_RESPONSE_GeneralError           = 2, /**< Response code indicating a general error while processing the
			                                            *  issued command
			                                            */
			PIMA_RESPONSE_SessionNotOpen         = 3, /**< Response code indicating that the sent command requires an open
			                                           *   session before being issued
			                                           */
			PIMA_RESPONSE_InvalidTransaction     = 4, /**< Response code indicating an invalid transaction occurred */
			PIMA_RESPONSE_OperationNotSupported  = 5, /**< Response code indicating that the issued command is not supported
			                                           *   by the attached device
			                                           */
			PIMA_RESPONSE_ParameterNotSupported  = 6, /**< Response code indicating that one or more of the issued command's
			                                           *   parameters are not supported by the device
			                                           */
		};
	
	/* Type Defines: */
		/** Type define for a PIMA container, use to send commands and receive responses to and from an
		 *  attached Still Image device.
		 */
		typedef struct
		{
			uint32_t DataLength; /**< Length of the container and data, in bytes */
			uint16_t Type; /**< Container type, a value from the PIMA_Container_Types_t enum */
			uint16_t Code; /**< Command, event or response code of the container */
			uint32_t TransactionID; /**< Unique container ID to link blocks together */
			uint32_t Params[5]; /**< Block parameters to be issued along with the block code (command blocks only) */
		} SI_PIMA_Container_t;
		
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
