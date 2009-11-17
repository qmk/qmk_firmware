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
 *  Header file for SCSI.c.
 */
 
#ifndef _SCSI_H_
#define _SCSI_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/USB/Class/MassStorage.h>

		#include "Descriptors.h"
		#include "DataflashManager.h"
	
	/* Macros: */
		/** Macro to set the current SCSI sense data to the given key, additional sense code and additional sense qualifier. This
		 *  is for convenience, as it allows for all three sense values (returned upon request to the host to give information about
		 *  the last command failure) in a quick and easy manner.
		 *
		 *  \param[in] key    New SCSI sense key to set the sense code to
		 *  \param[in] acode  New SCSI additional sense key to set the additional sense code to
		 *  \param[in] aqual  New SCSI additional sense key qualifier to set the additional sense qualifier code to
		 */
		#define SCSI_SET_SENSE(key, acode, aqual)  MACROS{ SenseData.SenseKey = key;              \
		                                                   SenseData.AdditionalSenseCode = acode; \
		                                                   SenseData.AdditionalSenseQualifier = aqual; }MACROE

		/** Macro for the SCSI_Command_ReadWrite_10() function, to indicate that data is to be read from the storage medium. */
		#define DATA_READ           true

		/** Macro for the SCSI_Command_ReadWrite_10() function, to indicate that data is to be written to the storage medium. */
		#define DATA_WRITE          false

		/** Value for the DeviceType entry in the SCSI_Inquiry_Response_t enum, indicating a Block Media device. */
		#define DEVICE_TYPE_BLOCK   0x00
		
		/** Value for the DeviceType entry in the SCSI_Inquiry_Response_t enum, indicating a CD-ROM device. */
		#define DEVICE_TYPE_CDROM   0x05

	/* Type Defines: */
		/** Type define for a SCSI response structure to a SCSI INQUIRY command. For details of the
		 *  structure contents, refer to the SCSI specifications.
		 */
		typedef struct
		{
			unsigned char DeviceType          : 5;
			unsigned char PeripheralQualifier : 3;
			
			unsigned char _RESERVED1          : 7;
			unsigned char Removable           : 1;
			
			uint8_t      Version;
			
			unsigned char ResponseDataFormat  : 4;
			unsigned char _RESERVED2          : 1;
			unsigned char NormACA             : 1;
			unsigned char TrmTsk              : 1;
			unsigned char AERC                : 1;

			uint8_t      AdditionalLength;
			uint8_t      _RESERVED3[2];

			unsigned char SoftReset           : 1;
			unsigned char CmdQue              : 1;
			unsigned char _RESERVED4          : 1;
			unsigned char Linked              : 1;
			unsigned char Sync                : 1;
			unsigned char WideBus16Bit        : 1;
			unsigned char WideBus32Bit        : 1;
			unsigned char RelAddr             : 1;
			
			uint8_t      VendorID[8];
			uint8_t      ProductID[16];
			uint8_t      RevisionID[4];
		} SCSI_Inquiry_Response_t;
		
		/** Type define for a SCSI sense structure to a SCSI REQUEST SENSE command. For details of the
		 *  structure contents, refer to the SCSI specifications.
		 */
		typedef struct
		{
			uint8_t       ResponseCode;
			
			uint8_t       SegmentNumber;
			
			unsigned char SenseKey            : 4;
			unsigned char _RESERVED1          : 1;
			unsigned char ILI                 : 1;
			unsigned char EOM                 : 1;
			unsigned char FileMark            : 1;
			
			uint8_t      Information[4];
			uint8_t      AdditionalLength;
			uint8_t      CmdSpecificInformation[4];
			uint8_t      AdditionalSenseCode;
			uint8_t      AdditionalSenseQualifier;
			uint8_t      FieldReplaceableUnitCode;
			uint8_t      SenseKeySpecific[3];
		} SCSI_Request_Sense_Response_t;
		
	/* Function Prototypes: */
		bool SCSI_DecodeSCSICommand(USB_ClassInfo_MS_Device_t* MSInterfaceInfo);
		
		#if defined(INCLUDE_FROM_SCSI_C)
			static void SCSI_Command_Inquiry(USB_ClassInfo_MS_Device_t* MSInterfaceInfo);
			static void SCSI_Command_Request_Sense(USB_ClassInfo_MS_Device_t* MSInterfaceInfo);
			static void SCSI_Command_Read_Capacity_10(USB_ClassInfo_MS_Device_t* MSInterfaceInfo);
			static void SCSI_Command_Send_Diagnostic(USB_ClassInfo_MS_Device_t* MSInterfaceInfo);
			static void SCSI_Command_ReadWrite_10(USB_ClassInfo_MS_Device_t* MSInterfaceInfo, const bool IsDataRead);
		#endif
		
#endif
