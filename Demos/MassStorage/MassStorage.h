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
 *  Header file for MassStorage.c.
 */

#ifndef _MASS_STORAGE_H_
#define _MASS_STORAGE_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>

		#include "Descriptors.h"
		#include "SCSI.h"
		#include "DataflashManager.h"

		#include <LUFA/Version.h>                    // Library Version Information
		#include <LUFA/Common/ButtLoadTag.h>         // PROGMEM tags readable by the ButtLoad project
		#include <LUFA/Drivers/USB/USB.h>            // USB Functionality
		#include <LUFA/Drivers/Board/LEDs.h>         // LEDs driver
		#include <LUFA/Drivers/Board/Dataflash.h>    // Dataflash chip driver
		#include <LUFA/Scheduler/Scheduler.h>        // Simple scheduler for task management

	/* Macros: */
		/** Mass Storage Class specific request to reset the Mass Storage interface, ready for the next command. */
		#define REQ_MassStorageReset       0xFF

		/** Mass Storage Class specific request to retrieve the total number of Logical Units (drives) in the SCSI device. */
		#define REQ_GetMaxLUN              0xFE

		/** Maximum length of a SCSI command which can be issued by the device or host in a Mass Storage bulk wrapper. */
		#define MAX_SCSI_COMMAND_LENGTH    16
		
		/** Total number of Logical Units (drives) in the device. By default, the total device capacity is shared equally between
		 *  each drive - this can be set to any positive non-zero amount. */
		#define TOTAL_LUNS                 2
		
		/** Blocks in each LUN, calculated from the total capacity divided by the total number of Logical Units in the device. */
		#define LUN_MEDIA_BLOCKS           (VIRTUAL_MEMORY_BLOCKS / TOTAL_LUNS)    
		
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

		/** Enum for the possible status codes for passing to the UpdateStatus() function. */
		enum MassStorage_StatusCodes_t
		{
			Status_USBNotReady            = 0, /**< USB is not ready (disconnected from a USB host) */
			Status_USBEnumerating         = 1, /**< USB interface is enumerating */
			Status_USBReady               = 2, /**< USB interface is connected and ready */
			Status_CommandBlockError      = 3, /**< Processing a SCSI command block from the host */
			Status_ProcessingCommandBlock = 4, /**< Error during the processing of a SCSI command block from the host */
		};
		
	/* Global Variables: */
		extern CommandBlockWrapper_t  CommandBlock;
		extern CommandStatusWrapper_t CommandStatus;
		extern volatile bool          IsMassStoreReset;

	/* Task Definitions: */
		TASK(USB_MassStorage);
		
	/* Stream Callbacks: */
		STREAM_CALLBACK(AbortOnMassStoreReset);

	/* Event Handlers: */
		/** Indicates that this module will catch the USB_Reset event when thrown by the library. */
		HANDLES_EVENT(USB_Reset);

		/** Indicates that this module will catch the USB_Connect event when thrown by the library. */
		HANDLES_EVENT(USB_Connect);

		/** Indicates that this module will catch the USB_Disconnect event when thrown by the library. */
		HANDLES_EVENT(USB_Disconnect);

		/** Indicates that this module will catch the USB_ConfigurationChanged event when thrown by the library. */
		HANDLES_EVENT(USB_ConfigurationChanged);

		/** Indicates that this module will catch the USB_UnhandledControlPacket event when thrown by the library. */
		HANDLES_EVENT(USB_UnhandledControlPacket);

	/* Function Prototypes: */
		void UpdateStatus(uint8_t CurrentStatus);

		#if defined(INCLUDE_FROM_MASSSTORAGE_C)
			static bool ReadInCommandBlock(void);
			static void ReturnCommandStatus(void);
		#endif

#endif
