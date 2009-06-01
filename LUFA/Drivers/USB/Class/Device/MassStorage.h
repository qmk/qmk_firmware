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

#ifndef _MS_CLASS_H_
#define _MS_CLASS_H_

	/* Includes: */
		#include "../../USB.h"

		#include <string.h>

	/* Macros: */
		/** Mass Storage Class specific request to reset the Mass Storage interface, ready for the next command. */
		#define REQ_MassStorageReset       0xFF

		/** Mass Storage Class specific request to retrieve the total number of Logical Units (drives) in the SCSI device. */
		#define REQ_GetMaxLUN              0xFE

		/** Maximum length of a SCSI command which can be issued by the device or host in a Mass Storage bulk wrapper. */
		#define MAX_SCSI_COMMAND_LENGTH    16
		
		/** Magic signature for a Command Block Wrapper used in the Mass Storage Bulk-Only transport protocol. */
		#define CBW_SIGNATURE              0x43425355UL

		/** Magic signature for a Command Status Wrapper used in the Mass Storage Bulk-Only transport protocol. */
		#define CSW_SIGNATURE              0x53425355UL
		
		/** Mask for a Command Block Wrapper's flags attribute to specify a command with data sent from host-to-device. */
		#define COMMAND_DIRECTION_DATA_OUT (0 << 7)

		/** Mask for a Command Block Wrapper's flags attribute to specify a command with data sent from device-to-host. */
		#define COMMAND_DIRECTION_DATA_IN  (1 << 7)

	/* Type defines: */
		/** Type define for a Command Block Wrapper, used in the Mass Storage Bulk-Only Transport protocol. */
		typedef struct
		{
			uint32_t Signature; /**< Command block signature, must be CBW_SIGNATURE to indicate a valid Command Block */
			uint32_t Tag; /**< Unique command ID value, to associate a command block wrapper with its command status wrapper */
			uint32_t DataTransferLength; /** Length of the optional data portion of the issued command, in bytes */
			uint8_t  Flags; /**< Command block flags, indicating command data direction */
			uint8_t  LUN; /**< Logical Unit number this command is issued to */
			uint8_t  SCSICommandLength; /**< Length of the issued SCSI command within the SCSI command data array */
			uint8_t  SCSICommandData[MAX_SCSI_COMMAND_LENGTH]; /**< Issued SCSI command in the Command Block */
		} CommandBlockWrapper_t;
		
		/** Type define for a Command Status Wrapper, used in the Mass Storage Bulk-Only Transport protocol. */
		typedef struct
		{
			uint32_t Signature; /**< Status block signature, must be CSW_SIGNATURE to indicate a valid Command Status */
			uint32_t Tag; /**< Unique command ID value, to associate a command block wrapper with its command status wrapper */
			uint32_t DataTransferResidue; /**< Number of bytes of data not processed in the SCSI command */
			uint8_t  Status; /**< Status code of the issued command - a value from the MassStorage_CommandStatusCodes_t enum */
		} CommandStatusWrapper_t;
		
	/* Enums: */
		/** Enum for the possible command status wrapper return status codes. */
		enum MassStorage_CommandStatusCodes_t
		{
			Command_Pass = 0, /**< Command completed with no error */
			Command_Fail = 1, /**< Command failed to complete - host may check the exact error via a SCSI REQUEST SENSE command */
			Phase_Error  = 2  /**< Command failed due to being invalid in the current phase */
		};
		
	/* Type Defines: */
		/** Type define for the virtual serial port line encoding settings, for storing the current USART configuration
		 *  as set by the host via a class specific request.
		 */
		typedef struct
		{
			uint8_t  InterfaceNumber; /**< Interface number of the Mass Storage interface within the device */

			uint8_t  DataINEndpointNumber; /**< Endpoint number of the Mass Storage interface's IN data endpoint */
			uint16_t DataINEndpointSize; /**< Size in bytes of the Mass Storage interface's IN data endpoint */

			uint8_t  DataOUTEndpointNumber; /**< Endpoint number of the Mass Storage interface's OUT data endpoint */
			uint16_t DataOUTEndpointSize;  /**< Size in bytes of the Mass Storage interface's OUT data endpoint */

			uint8_t  TotalLUNs;

			CommandBlockWrapper_t  CommandBlock;
			CommandStatusWrapper_t CommandStatus;

			bool IsMassStoreReset;
		} USB_ClassInfo_MS_t;
		
	/* Function Prototypes: */
		#if defined(INCLUDE_FROM_MS_CLASS_C)
			static void    USB_MS_ReturnCommandStatus(USB_ClassInfo_MS_t* MSInterfaceInfo);
			static bool    USB_MS_ReadInCommandBlock(USB_ClassInfo_MS_t* MSInterfaceInfo);
			static uint8_t StreamCallback_AbortOnMassStoreReset(void);
		#endif
	
		void USB_MS_USBTask(USB_ClassInfo_MS_t* MSInterfaceInfo);
		bool USB_MS_ConfigureEndpoints(USB_ClassInfo_MS_t* MSInterfaceInfo);
		void USB_MS_ProcessControlPacket(USB_ClassInfo_MS_t* MSInterfaceInfo);
		
		bool CALLBACK_USB_MS_SCSICommandReceived(USB_ClassInfo_MS_t* MSInterfaceInfo);
		
#endif
