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
 *  Header file for StillImageCommands.c.
 */
 
#ifndef _STILL_IMAGE_COMMANDS_H_
#define _STILL_IMAGE_COMMANDS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>                        // USB Functionality
		
		#include "PIMACodes.h"

	/* Macros: */
		/** Pipe number of the Still Image data IN pipe */
		#define SIMAGE_DATA_IN_PIPE            0x01

		/** Pipe number of the Still Image data OUT pipe */
		#define SIMAGE_DATA_OUT_PIPE           0x02

		/** Pipe number of the Still Image events pipe */
		#define SIMAGE_EVENTS_PIPE             0x03

		/** Timeout period between the issuing of a command to a device, and the reception of the first packet */
		#define COMMAND_DATA_TIMEOUT_MS        5000
		
		/** Used in the DataLength field of a PIMA container, to give the total container size in bytes for
		 *  a command container.
		 *
		 *  \param[in] params  Number of parameters which are to be sent in the Param field of the container
		 */
		#define PIMA_COMMAND_SIZE(params)      ((sizeof(PIMA_SendBlock) - sizeof(PIMA_SendBlock.Params)) + \
		                                        (params * sizeof(PIMA_SendBlock.Params[0])))

		/** Used in the DataLength field of a PIMA container, to give the total container size in bytes for
		 *  a data container.
		 *
		 *  \param[in] datalen  Length in bytes of the data in the container
		 */
		#define PIMA_DATA_SIZE(datalen)        ((sizeof(PIMA_SendBlock) - sizeof(PIMA_SendBlock.Params)) + datalen)

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
			uint32_t Params[4]; /**< Block parameters to be issued along with the block code (command blocks only) */
		} PIMA_Container_t;
	
	/* Enums: */
		/** Enum for the possible PIMA contains types. */
		enum PIMA_Container_Types_t
		{
			CType_Undefined         = 0, /**< Undefined container type */
			CType_CommandBlock      = 1, /**< Command Block container type */
			CType_DataBlock         = 2, /**< Data Block container type */
			CType_ResponseBlock     = 3, /**< Response container type */
			CType_EventBlock        = 4, /**< Event Block container type */
		};
	
	/* External Variables: */
		extern PIMA_Container_t PIMA_SendBlock;
		extern PIMA_Container_t PIMA_ReceivedBlock;
		extern PIMA_Container_t PIMA_EventBlock;
	
	/* Function Prototypes: */
		void    SImage_SendBlockHeader(void);
		uint8_t SImage_RecieveBlockHeader(void);
		void    SImage_RecieveEventHeader(void);
		void    SImage_SendData(void* Buffer, uint16_t Bytes);
		uint8_t SImage_ReadData(void* Buffer, uint16_t Bytes);
		bool    SImage_IsEventReceived(void);
		uint8_t SImage_ClearPipeStall(const uint8_t EndpointNum);

#endif
