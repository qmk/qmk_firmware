/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Common definitions and declarations for the library USB Mass Storage Class driver.
 *
 *  Common definitions and declarations for the library USB Mass Storage Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassMS
 *  \defgroup Group_USBClassMSCommon  Common Class Definitions
 *
 *  \section Sec_USBClassMSCommon_ModDescription Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  Mass Storage Class.
 *
 *  @{
 */

#ifndef _MS_CLASS_COMMON_H_
#define _MS_CLASS_COMMON_H_

	/* Includes: */
		#include "../../Core/StdDescriptors.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_MS_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Macros: */
		/** Magic signature for a Command Block Wrapper used in the Mass Storage Bulk-Only transport protocol. */
		#define MS_CBW_SIGNATURE                               0x43425355UL

		/** Magic signature for a Command Status Wrapper used in the Mass Storage Bulk-Only transport protocol. */
		#define MS_CSW_SIGNATURE                               0x53425355UL

		/** Mask for a Command Block Wrapper's flags attribute to specify a command with data sent from host-to-device. */
		#define MS_COMMAND_DIR_DATA_OUT                        (0 << 7)

		/** Mask for a Command Block Wrapper's flags attribute to specify a command with data sent from device-to-host. */
		#define MS_COMMAND_DIR_DATA_IN                         (1 << 7)

		/** \name SCSI Commands*/
		//@{
		/** SCSI Command Code for an INQUIRY command. */
		#define SCSI_CMD_INQUIRY                               0x12

		/** SCSI Command Code for a REQUEST SENSE command. */
		#define SCSI_CMD_REQUEST_SENSE                         0x03

		/** SCSI Command Code for a TEST UNIT READY command. */
		#define SCSI_CMD_TEST_UNIT_READY                       0x00

		/** SCSI Command Code for a READ CAPACITY (10) command. */
		#define SCSI_CMD_READ_CAPACITY_10                      0x25

		/** SCSI Command Code for a START STOP UNIT command. */
		#define SCSI_CMD_START_STOP_UNIT                       0x1B

		/** SCSI Command Code for a SEND DIAGNOSTIC command. */
		#define SCSI_CMD_SEND_DIAGNOSTIC                       0x1D

		/** SCSI Command Code for a PREVENT ALLOW MEDIUM REMOVAL command. */
		#define SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL          0x1E

		/** SCSI Command Code for a WRITE (10) command. */
		#define SCSI_CMD_WRITE_10                              0x2A

		/** SCSI Command Code for a READ (10) command. */
		#define SCSI_CMD_READ_10                               0x28

		/** SCSI Command Code for a WRITE (6) command. */
		#define SCSI_CMD_WRITE_6                               0x0A

		/** SCSI Command Code for a READ (6) command. */
		#define SCSI_CMD_READ_6                                0x08

		/** SCSI Command Code for a VERIFY (10) command. */
		#define SCSI_CMD_VERIFY_10                             0x2F

		/** SCSI Command Code for a MODE SENSE (6) command. */
		#define SCSI_CMD_MODE_SENSE_6                          0x1A

		/** SCSI Command Code for a MODE SENSE (10) command. */
		#define SCSI_CMD_MODE_SENSE_10                         0x5A
		//@}

		/** \name SCSI Sense Key Values */
		//@{
		/** SCSI Sense Code to indicate no error has occurred. */
		#define SCSI_SENSE_KEY_GOOD                            0x00

		/** SCSI Sense Code to indicate that the device has recovered from an error. */
		#define SCSI_SENSE_KEY_RECOVERED_ERROR                 0x01

		/** SCSI Sense Code to indicate that the device is not ready for a new command. */
		#define SCSI_SENSE_KEY_NOT_READY                       0x02

		/** SCSI Sense Code to indicate an error whilst accessing the medium. */
		#define SCSI_SENSE_KEY_MEDIUM_ERROR                    0x03

		/** SCSI Sense Code to indicate a hardware error has occurred. */
		#define SCSI_SENSE_KEY_HARDWARE_ERROR                  0x04

		/** SCSI Sense Code to indicate that an illegal request has been issued. */
		#define SCSI_SENSE_KEY_ILLEGAL_REQUEST                 0x05

		/** SCSI Sense Code to indicate that the unit requires attention from the host to indicate
		 *  a reset event, medium removal or other condition.
		 */
		#define SCSI_SENSE_KEY_UNIT_ATTENTION                  0x06

		/** SCSI Sense Code to indicate that a write attempt on a protected block has been made. */
		#define SCSI_SENSE_KEY_DATA_PROTECT                    0x07

		/** SCSI Sense Code to indicate an error while trying to write to a write-once medium. */
		#define SCSI_SENSE_KEY_BLANK_CHECK                     0x08

		/** SCSI Sense Code to indicate a vendor specific error has occurred. */
		#define SCSI_SENSE_KEY_VENDOR_SPECIFIC                 0x09

		/** SCSI Sense Code to indicate that an EXTENDED COPY command has aborted due to an error. */
		#define SCSI_SENSE_KEY_COPY_ABORTED                    0x0A

		/** SCSI Sense Code to indicate that the device has aborted the issued command. */
		#define SCSI_SENSE_KEY_ABORTED_COMMAND                 0x0B

		/** SCSI Sense Code to indicate an attempt to write past the end of a partition has been made. */
		#define SCSI_SENSE_KEY_VOLUME_OVERFLOW                 0x0D

		/** SCSI Sense Code to indicate that the source data did not match the data read from the medium. */
		#define SCSI_SENSE_KEY_MISCOMPARE                      0x0E
		//@}

		/** \name SCSI Additional Sense Codes */
		//@{
		/** SCSI Additional Sense Code to indicate no additional sense information is available. */
		#define SCSI_ASENSE_NO_ADDITIONAL_INFORMATION          0x00

		/** SCSI Additional Sense Code to indicate that the logical unit (LUN) addressed is not ready. */
		#define SCSI_ASENSE_LOGICAL_UNIT_NOT_READY             0x04

		/** SCSI Additional Sense Code to indicate an invalid field was encountered while processing the issued command. */
		#define SCSI_ASENSE_INVALID_FIELD_IN_CDB               0x24

		/** SCSI Additional Sense Code to indicate that a medium that was previously indicated as not ready has now
		 *  become ready for use.
		 */
		#define SCSI_ASENSE_NOT_READY_TO_READY_CHANGE          0x28

		/** SCSI Additional Sense Code to indicate that an attempt to write to a protected area was made. */
		#define SCSI_ASENSE_WRITE_PROTECTED                    0x27

		/** SCSI Additional Sense Code to indicate an error whilst formatting the device medium. */
		#define SCSI_ASENSE_FORMAT_ERROR                       0x31

		/** SCSI Additional Sense Code to indicate an invalid command was issued. */
		#define SCSI_ASENSE_INVALID_COMMAND                    0x20

		/** SCSI Additional Sense Code to indicate a write to a block out outside of the medium's range was issued. */
		#define SCSI_ASENSE_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE 0x21

		/** SCSI Additional Sense Code to indicate that no removable medium is inserted into the device. */
		#define SCSI_ASENSE_MEDIUM_NOT_PRESENT                 0x3A
		//@}

		/** \name SCSI Additional Sense Key Code Qualifiers */
		//@{
		/** SCSI Additional Sense Qualifier Code to indicate no additional sense qualifier information is available. */
		#define SCSI_ASENSEQ_NO_QUALIFIER                      0x00

		/** SCSI Additional Sense Qualifier Code to indicate that a medium format command failed to complete. */
		#define SCSI_ASENSEQ_FORMAT_COMMAND_FAILED             0x01

		/** SCSI Additional Sense Qualifier Code to indicate that an initializing command must be issued before the issued
		 *  command can be executed.
		 */
		#define SCSI_ASENSEQ_INITIALIZING_COMMAND_REQUIRED     0x02

		/** SCSI Additional Sense Qualifier Code to indicate that an operation is currently in progress. */
		#define SCSI_ASENSEQ_OPERATION_IN_PROGRESS             0x07
		//@}

	/* Enums: */
		/** Enum for possible Class, Subclass and Protocol values of device and interface descriptors relating to the Mass
		 *  Storage device class.
		 */
		enum MS_Descriptor_ClassSubclassProtocol_t
		{
			MS_CSCP_MassStorageClass          = 0x08, /**< Descriptor Class value indicating that the device or interface
			                                           *   belongs to the Mass Storage class.
			                                           */
			MS_CSCP_SCSITransparentSubclass   = 0x06, /**< Descriptor Subclass value indicating that the device or interface
			                                           *   belongs to the SCSI Transparent Command Set subclass of the Mass
			                                           *   storage class.
			                                           */
			MS_CSCP_BulkOnlyTransportProtocol = 0x50, /**< Descriptor Protocol value indicating that the device or interface
			                                           *   belongs to the Bulk Only Transport protocol of the Mass Storage class.
			                                           */
		};

		/** Enum for the Mass Storage class specific control requests that can be issued by the USB bus host. */
		enum MS_ClassRequests_t
		{
			MS_REQ_GetMaxLUN                  = 0xFE, /**< Mass Storage class-specific request to retrieve the total number of Logical
			                                           *   Units (drives) in the SCSI device.
			                                           */
			MS_REQ_MassStorageReset           = 0xFF, /**< Mass Storage class-specific request to reset the Mass Storage interface,
			                                           *   ready for the next command.
		                                               */
		};

		/** Enum for the possible command status wrapper return status codes. */
		enum MS_CommandStatusCodes_t
		{
			MS_SCSI_COMMAND_Pass              = 0, /**< Command completed with no error */
			MS_SCSI_COMMAND_Fail              = 1, /**< Command failed to complete - host may check the exact error via a
			                                        *   SCSI REQUEST SENSE command.
			                                        */
			MS_SCSI_COMMAND_PhaseError        = 2, /**< Command failed due to being invalid in the current phase. */
		};

	/* Type Defines: */
		/** \brief Mass Storage Class Command Block Wrapper.
		 *
		 *  Type define for a Command Block Wrapper, used in the Mass Storage Bulk-Only Transport protocol.
		 *
		 *  \note Regardless of CPU architecture, these values should be stored as little endian.
		 */
		typedef struct
		{
			uint32_t Signature; /**< Command block signature, must be \ref MS_CBW_SIGNATURE to indicate a valid Command Block. */
			uint32_t Tag; /**< Unique command ID value, to associate a command block wrapper with its command status wrapper. */
			uint32_t DataTransferLength; /**< Length of the optional data portion of the issued command, in bytes. */
			uint8_t  Flags; /**< Command block flags, indicating command data direction. */
			uint8_t  LUN; /**< Logical Unit number this command is issued to. */
			uint8_t  SCSICommandLength; /**< Length of the issued SCSI command within the SCSI command data array. */
			uint8_t  SCSICommandData[16]; /**< Issued SCSI command in the Command Block. */
		} ATTR_PACKED MS_CommandBlockWrapper_t;

		/** \brief Mass Storage Class Command Status Wrapper.
		 *
		 *  Type define for a Command Status Wrapper, used in the Mass Storage Bulk-Only Transport protocol.
		 *
		 *  \note Regardless of CPU architecture, these values should be stored as little endian.
		 */
		typedef struct
		{
			uint32_t Signature; /**< Status block signature, must be \ref MS_CSW_SIGNATURE to indicate a valid Command Status. */
			uint32_t Tag; /**< Unique command ID value, to associate a command block wrapper with its command status wrapper. */
			uint32_t DataTransferResidue; /**< Number of bytes of data not processed in the SCSI command. */
			uint8_t  Status; /**< Status code of the issued command - a value from the \ref MS_CommandStatusCodes_t enum. */
		} ATTR_PACKED MS_CommandStatusWrapper_t;

		/** \brief Mass Storage Class SCSI Sense Structure
		 *
		 *  Type define for a SCSI Sense structure. Structures of this type are filled out by the
		 *  device via the \ref MS_Host_RequestSense() function, indicating the current sense data of the
		 *  device (giving explicit error codes for the last issued command). For details of the
		 *  structure contents, refer to the SCSI specifications.
		 */
		typedef struct
		{
			uint8_t  ResponseCode;

			uint8_t  SegmentNumber;

			unsigned SenseKey            : 4;
			unsigned Reserved            : 1;
			unsigned ILI                 : 1;
			unsigned EOM                 : 1;
			unsigned FileMark            : 1;

			uint8_t  Information[4];
			uint8_t  AdditionalLength;
			uint8_t  CmdSpecificInformation[4];
			uint8_t  AdditionalSenseCode;
			uint8_t  AdditionalSenseQualifier;
			uint8_t  FieldReplaceableUnitCode;
			uint8_t  SenseKeySpecific[3];
		} ATTR_PACKED SCSI_Request_Sense_Response_t;

		/** \brief Mass Storage Class SCSI Inquiry Structure.
		 *
		 *  Type define for a SCSI Inquiry structure. Structures of this type are filled out by the
		 *  device via the \ref MS_Host_GetInquiryData() function, retrieving the attached device's
		 *  information.
		 *
		 *  For details of the structure contents, refer to the SCSI specifications.
		 */
		typedef struct
		{
			unsigned DeviceType          : 5;
			unsigned PeripheralQualifier : 3;

			unsigned Reserved            : 7;
			unsigned Removable           : 1;

			uint8_t  Version;

			unsigned ResponseDataFormat  : 4;
			unsigned Reserved2           : 1;
			unsigned NormACA             : 1;
			unsigned TrmTsk              : 1;
			unsigned AERC                : 1;

			uint8_t  AdditionalLength;
			uint8_t  Reserved3[2];

			unsigned SoftReset           : 1;
			unsigned CmdQue              : 1;
			unsigned Reserved4           : 1;
			unsigned Linked              : 1;
			unsigned Sync                : 1;
			unsigned WideBus16Bit        : 1;
			unsigned WideBus32Bit        : 1;
			unsigned RelAddr             : 1;

			uint8_t  VendorID[8];
			uint8_t  ProductID[16];
			uint8_t  RevisionID[4];
		} ATTR_PACKED SCSI_Inquiry_Response_t;

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

