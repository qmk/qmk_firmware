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

/** \ingroup Group_USBClassMS
 *  @defgroup Group_USBClassMassStorageHost Mass Storage Class Host Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/MassStorage.c
 *
 *  \section Module Description
 *  Host Mode USB Class driver framework interface, for the Mass Storage USB Class driver.
 *
 *  @{
 */

#ifndef __MS_CLASS_HOST_H__
#define __MS_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/MassStorage.h"
		#include "../Common/SCSICodes.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#define MS_ERROR_LOGICAL_CMD_FAILED              0xC0
	
		/* Type Defines: */
			/** Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the HID class driver functions as the HIDInterfaceInfo parameter. This
			 *  stores each HID interface's configuration and state information.
			 */
			typedef struct
			{
				const struct
				{
					uint8_t  DataINPipeNumber; /**< Pipe number of the MS interface's IN data pipe */
					uint8_t  DataOUTPipeNumber; /**< Pipe number of the MS interface's OUT data pipe */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool Active; /**< Indicates if the current interface instance is connected to an attached device, valid
					              *   after \ref HID_Host_ConfigurePipes() is called and the Host state machine is in the
					              *   Configured state
					              */
					uint8_t InterfaceNumber; /**< Interface index of the HID interface within the attached device */

					uint16_t DataINPipeSize; /**< Size in bytes of the MS interface's IN data pipe */
					uint16_t DataOUTPipeSize;  /**< Size in bytes of the MS interface's OUT data pipe */
					
					uint32_t TransactionTag; /**< Current transaction tag for data synchronising of packets */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_MS_Host_t;

			/** Type define for a SCSI Sense structure. Structures of this type are filled out by the
			 *  device via the MassStore_RequestSense() function, indicating the current sense data of the
			 *  device (giving explicit error codes for the last issued command). For details of the
			 *  structure contents, refer to the SCSI specifications.
			 */
			typedef struct
			{
				uint8_t       ReponseCode;

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

			/** Type define for a SCSI Inquiry structure. Structures of this type are filled out by the
			 *  device via the MassStore_Inquiry() function, retrieving the attached device's information.
			 *  For details of the structure contents, refer to the SCSI specifications.
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
			
			/** SCSI capacity structure, to hold the total capacity of the device in both the number
			 *  of blocks in the current LUN, and the size of each block. This structure is filled by
			 *  the device when the MassStore_ReadCapacity() function is called.
			 */
			typedef struct
			{
				uint32_t Blocks; /**< Number of blocks in the addressed LUN of the device */
				uint32_t BlockSize; /**< Number of bytes in each block in the addressed LUN */
			} SCSI_Capacity_t;

		/* Enums: */
			enum
			{
				MS_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully */
				MS_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor */
				MS_ENUMERROR_NoMSInterfaceFound         = 2, /**< A compatible Mass Storage interface was not found in the device's Configuration Descriptor */
				MS_ENUMERROR_EndpointsNotFound          = 3, /**< Compatible Mass Storage endpoints were not found in the device's interfaces */
			} MSHost_EnumerationFailure_ErrorCodes_t;
	
		/* Function Prototypes: */
			/** General management task for a given Mass Storage host class interface, required for the correct operation of
			 *  the interface. This should be called frequently in the main program loop, before the master USB management task
			 *  \ref USB_USBTask().
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing an MS Class host configuration and state
			 */
			void MS_Host_USBTask(USB_ClassInfo_MS_Host_t* MSInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Host interface configuration routine, to configure a given Mass Storage host interface instance using the
			 *  Configuration Descriptor read from an attached USB device. This function automatically updates the given Mass
			 *  Storage Host instance's state values and configures the pipes required to communicate with the interface if it
			 *  is found within the device. This should be called once after the stack has enumerated the attached device, while
			 *  the host state machine is in the Addressed state.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing an MS Class host configuration and state
			 *  \param[in] ConfigDescriptorLength  Length of the attached device's Configuration Descriptor
			 *  \param[in] DeviceConfigDescriptor  Pointer to a buffer containing the attached device's Configuration Descriptor
			 */
			uint8_t MS_Host_ConfigurePipes(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint16_t ConfigDescriptorLength,
			                               uint8_t* DeviceConfigDescriptor) ATTR_NON_NULL_PTR_ARG(1, 3);

			/** Sends a MASS STORAGE RESET control request to the attached device, resetting the Mass Storage Interface
			 *  and readying it for the next Mass Storage command.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a MS Class host configuration and state
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum
			 */
			uint8_t MS_Host_ResetMSInterface(USB_ClassInfo_MS_Host_t* MSInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a GET MAX LUN control request to the attached device, retrieving the index of the highest LUN (Logical
			 *  UNit, a logical drive) in the device. This value can then be used in the other functions of the Mass Storage
			 *  Host mode Class driver to address a specific LUN within the device.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a MS Class host configuration and state
			 *  \param[out] MaxLUNIndex  Pointer to a location where the highest LUN index value should be stored
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum
			 */
			uint8_t MS_Host_GetMaxLUN(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t* MaxLUNIndex) ATTR_NON_NULL_PTR_ARG(1, 2);

			/** Retrieves the Mass Storage device's inquiry data for the specified LUN, indicating the device characteristics and
			 *  properties.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a MS Class host configuration and state
			 *  \param[in] LUNIndex  LUN index within the device the command is being issued to
			 *  \param[out] InquiryData  Location where the read inquiry data should be stored
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum or MS_ERROR_LOGICAL_CMD_FAILED
			 */
			uint8_t MS_Host_GetInquiryData(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t LUNIndex,
			                               SCSI_Inquiry_Response_t* InquiryData) ATTR_NON_NULL_PTR_ARG(1, 3);

			/** Sends a TEST UNIT READY command to the device, to determine if it is ready to accept other SCSI commands.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a MS Class host configuration and state
			 *  \param[in] LUNIndex  LUN index within the device the command is being issued to
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum or MS_ERROR_LOGICAL_CMD_FAILED if not ready
			 */
			uint8_t MS_Host_TestUnitReady(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t LUNIndex) ATTR_NON_NULL_PTR_ARG(1);

			/** Retrieves the total capacity of the attached USB Mass Storage device, in blocks, and block size.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a MS Class host configuration and state
			 *  \param[in] LUNIndex  LUN index within the device the command is being issued to
			 *  \param[out] DeviceCapacity  Pointer to the location where the capacity information should be stored
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum or MS_ERROR_LOGICAL_CMD_FAILED if not ready
			 */
			uint8_t MS_Host_ReadDeviceCapacity(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t LUNIndex,
			                                   SCSI_Capacity_t* DeviceCapacity) ATTR_NON_NULL_PTR_ARG(1, 3);
		
			/** Retrieves the device sense data, indicating the current device state and error codes for the previously
			 *  issued command.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a MS Class host configuration and state
			 *  \param[in] LUNIndex  LUN index within the device the command is being issued to
			 *  \param[out] SenseData  Pointer to the location where the sense information should be stored
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum or MS_ERROR_LOGICAL_CMD_FAILED if not ready
			 */
			uint8_t MS_Host_RequestSense(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t LUNIndex,
			                             SCSI_Request_Sense_Response_t* SenseData) ATTR_NON_NULL_PTR_ARG(1, 3);
		
			/** Issues a PREVENT MEDIUM REMOVAL command, to logically (or, depending on the type of device, physically) lock
			 *  the device from removal so that blocks of data on the medium can be read or altered.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a MS Class host configuration and state
			 *  \param[in] LUNIndex  LUN index within the device the command is being issued to
			 *  \param[in] PreventRemoval  Boolean true if the device should be locked from removal, false otherwise
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum or MS_ERROR_LOGICAL_CMD_FAILED if not ready
			 */
			uint8_t MS_Host_PreventAllowMediumRemoval(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t LUNIndex,
			                                          bool PreventRemoval) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Reads blocks of data from the attached Mass Storage device's medium.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a MS Class host configuration and state
			 *  \param[in] LUNIndex  LUN index within the device the command is being issued to
			 *  \param[in] BlockAddress  Starting block address within the device to read from
			 *  \param[in] Blocks  Total number of blocks to read
			 *  \param[out] BlockBuffer  Pointer to where the read data from the device should be stored
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum or MS_ERROR_LOGICAL_CMD_FAILED if not ready
			 */
			uint8_t MS_Host_ReadDeviceBlocks(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t LUNIndex, uint32_t BlockAddress,
			                                 uint8_t Blocks, uint16_t BlockSize, void* BlockBuffer) ATTR_NON_NULL_PTR_ARG(1, 6);
		
			/** Writes blocks of data to the attached Mass Storage device's medium.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a MS Class host configuration and state
			 *  \param[in] LUNIndex  LUN index within the device the command is being issued to
			 *  \param[in] BlockAddress  Starting block address within the device to write to
			 *  \param[in] Blocks  Total number of blocks to read
			 *  \param[in] BlockBuffer  Pointer to where the data to write should be sourced from
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum or MS_ERROR_LOGICAL_CMD_FAILED if not ready
			 */
			uint8_t MS_Host_WriteDeviceBlocks(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, uint8_t LUNIndex, uint32_t BlockAddress,
			                                  uint8_t Blocks, uint16_t BlockSize, void* BlockBuffer) ATTR_NON_NULL_PTR_ARG(1, 6);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define MASS_STORE_CLASS               0x08
			#define MASS_STORE_SUBCLASS            0x06
			#define MASS_STORE_PROTOCOL            0x50

			#define REQ_MassStorageReset           0xFF
			#define REQ_GetMaxLUN                  0xFE

			#define CBW_SIGNATURE                  0x43425355UL
			#define CSW_SIGNATURE                  0x53425355UL
			
			#define COMMAND_DIRECTION_DATA_OUT     (0 << 7)
			#define COMMAND_DIRECTION_DATA_IN      (1 << 7)
			
			#define COMMAND_DATA_TIMEOUT_MS        2000

			#define MS_FOUND_DATAPIPE_IN           (1 << 0)
			#define MS_FOUND_DATAPIPE_OUT          (1 << 1)
			
		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_MS_CLASS_HOST_C)		
				static uint8_t DComp_NextMassStorageInterface(void* CurrentDescriptor);
				static uint8_t DComp_NextInterfaceBulkDataEndpoint(void* CurrentDescriptor);
				
				static uint8_t MS_Host_SendCommand(USB_ClassInfo_MS_Host_t* MSInterfaceInfo,
				                                   MS_CommandBlockWrapper_t* SCSICommandBlock);
				static uint8_t MS_Host_WaitForDataReceived(USB_ClassInfo_MS_Host_t* MSInterfaceInfo);
				static uint8_t MS_Host_SendReceiveData(USB_ClassInfo_MS_Host_t* MSInterfaceInfo, 
                                                       MS_CommandBlockWrapper_t* SCSICommandBlock, void* BufferPtr);
				static uint8_t MS_Host_GetReturnedStatus(USB_ClassInfo_MS_Host_t* MSInterfaceInfo,
				                                         MS_CommandStatusWrapper_t* SCSICommandStatus);
			#endif
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
