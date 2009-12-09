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
 *  @defgroup Group_USBClassStillImageHost Still Image Class Host Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/StillImage.c
 *
 *  \section Module Description
 *  Host Mode USB Class driver framework interface, for the Still Image USB Class driver.
 *
 *  @{
 */

#ifndef __SI_CLASS_HOST_H__
#define __SI_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/StillImage.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Error code for some Still Image Host functions, indicating a logical (and not hardware) error */
			#define SI_ERROR_LOGICAL_CMD_FAILED              0x80

		/* Type Defines: */
			typedef struct
			{
				const struct
				{
					uint8_t  DataINPipeNumber; /**< Pipe number of the Still Image interface's IN data pipe */
					bool     DataINPipeDoubleBank; /** Indicates if the Still Image interface's IN data pipe should use double banking */

					uint8_t  DataOUTPipeNumber; /**< Pipe number of the Still Image interface's OUT data pipe */
					bool     DataOUTPipeDoubleBank; /** Indicates if the Still Image interface's OUT data pipe should use double banking */

					uint8_t  EventsPipeNumber; /**< Pipe number of the Still Image interface's IN events endpoint, if used */			
					bool     EventsPipeDoubleBank; /** Indicates if the Still Image interface's events data pipe should use double banking */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                *   after \ref SImage_Host_ConfigurePipes() is called and the Host state machine is in the
					                *   Configured state
					                */

					uint16_t DataINPipeSize; /**< Size in bytes of the Still Image interface's IN data pipe */
					uint16_t DataOUTPipeSize;  /**< Size in bytes of the Still Image interface's OUT data pipe */
					uint16_t EventsPipeSize;  /**< Size in bytes of the Still Image interface's IN events pipe */
					
					bool IsSessionOpen; /**< Indicates if a PIMA session is currently open with the attached device */
					uint32_t TransactionID; /**< Transaction ID for the next transaction to send to the device */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_SI_Host_t;
	
		/* Enums: */
			/** Enum for the possible error codes returned by the \ref SImage_Host_ConfigurePipes() function. */
			enum SIHost_EnumerationFailure_ErrorCodes_t
			{
				SI_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully */
				SI_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor */
				SI_ENUMERROR_NoSIInterfaceFound         = 2, /**< A compatible Still Image interface was not found in the device's
				                                             *   Configuration Descriptor
				                                             */
				SI_ENUMERROR_EndpointsNotFound          = 3, /**< Compatible Still Image data endpoints were not found in the
				                                              *   device's Still Image interface
				                                              */
			};

		/* Function Prototypes: */
			/** General management task for a given Still Image host class interface, required for the correct operation of the
			 *  interface. This should be called frequently in the main program loop, before the master USB management task
			 *  \ref USB_USBTask().
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state
			 */
			void SImage_Host_USBTask(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);


			/** Host interface configuration routine, to configure a given Still Image host interface instance using the
			 *  Configuration Descriptor read from an attached USB device. This function automatically updates the given Still
			 *  Image Host instance's state values and configures the pipes required to communicate with the interface if it is
			 *  found within the device. This should be called once after the stack has enumerated the attached device, while
			 *  the host state machine is in the Addressed state.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state
			 *  \param[in] ConfigDescriptorSize  Length of the attached device's Configuration Descriptor
			 *  \param[in] DeviceConfigDescriptor  Pointer to a buffer containing the attached device's Configuration Descriptor
			 *
			 *  \return A value from the \ref SIHost_EnumerationFailure_ErrorCodes_t enum
			 */
			uint8_t SImage_Host_ConfigurePipes(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, uint16_t ConfigDescriptorSize,
                                               void* DeviceConfigDescriptor) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);

			/** Opens a new PIMA session with the attached device. This should be used before any session-orientated PIMA commands
			 *  are issued to the device. Only one session can be open at the one time.
			 *			 
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum, or \ref SI_ERROR_LOGICAL_CMD_FAILED if the device
			 *          returned a logical command failure
			 */
			uint8_t SImage_Host_OpenSession(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Closes an already opened PIMA session with the attached device. This should be used after all session-orientated
			 *  PIMA commands have been issued to the device.
			 *			 
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum, or \ref SI_ERROR_LOGICAL_CMD_FAILED if the device
			 *          returned a logical command failure
			 */
			uint8_t SImage_Host_CloseSession(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a given PIMA command to the attached device, filling out the PIMA command header's Transaction ID automatically.
			 *			 
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state
			 *  \param[in] Operation  PIMA operation code to issue to the device
			 *  \param[in] TotalParams  Total number of 32-bit parameters to send to the device in the issued command block
			 *  \param[in] Params  Pointer to an array of 32-bit values containing the parameters to send in the command block
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum, or \ref SI_ERROR_LOGICAL_CMD_FAILED if the device
			 *          returned a logical command failure
			 */
			uint8_t SImage_Host_SendCommand(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, const uint16_t Operation,
			                                const uint8_t TotalParams, uint32_t* Params) ATTR_NON_NULL_PTR_ARG(1);

			/** Receives and checks a response block from the attached PIMA device, once a command has been issued and all data
			 *  associated with the command has been transferred.
			 *			 
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum, or \ref SI_ERROR_LOGICAL_CMD_FAILED if the device
			 *          returned a logical command failure
			 */
			uint8_t SImage_Host_ReceiveResponse(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Indicates if the device has issued a PIMA event block to the host via the asynchronous events pipe.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state
			 *
			 *  \return Boolean true if an event is waiting to be read, false otherwise
			 */
			bool SImage_Host_IsEventReceived(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Receives an asynchronous event block from the device via the asynchronous events pipe.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state
			 *  \param[out] PIMAHeader  Pointer to a PIMA container structure where the event should be stored
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum, or \ref SI_ERROR_LOGICAL_CMD_FAILED if the device
			 *          returned a logical command failure
			 */
			uint8_t SImage_Host_ReceiveEventHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
				                                   SI_PIMA_Container_t* const PIMAHeader) ATTR_NON_NULL_PTR_ARG(1)
			                                       ATTR_NON_NULL_PTR_ARG(2);
			
			/** Sends arbitrary data to the attached device, for use in the data phase of PIMA commands which require data
			 *  transfer beyond the regular PIMA command block parameters.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state
			 *  \param[in] Buffer  Pointer to a buffer where the data to send has been stored
			 *  \param[in] Bytes  Length in bytes of the data in the buffer to send to the attached device
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum
			 */
			uint8_t SImage_Host_SendData(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, void* Buffer,
			                             const uint16_t Bytes) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Receives arbitrary data from the attached device, for use in the data phase of PIMA commands which require data
			 *  transfer beyond the regular PIMA command block parameters.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state
			 *  \param[out] Buffer  Pointer to a buffer where the received data is to be stored
			 *  \param[in] Bytes  Length in bytes of the data to read
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum
			 */
			uint8_t SImage_Host_ReadData(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo, void* Buffer,
			                             const uint16_t Bytes) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);
			
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define STILL_IMAGE_CLASS              0x06
			#define STILL_IMAGE_SUBCLASS           0x01
			#define STILL_IMAGE_PROTOCOL           0x01

			#define SI_FOUND_EVENTS_IN             (1 << 0)
			#define SI_FOUND_DATAPIPE_IN           (1 << 1)
			#define SI_FOUND_DATAPIPE_OUT          (1 << 2)

			#define COMMAND_DATA_TIMEOUT_MS        10000
		
		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_SI_CLASS_HOST_C)
				static uint8_t DComp_SI_Host_NextSIInterface(void* const CurrentDescriptor) ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DComp_SI_Host_NextSIInterfaceEndpoint(void* const CurrentDescriptor) ATTR_NON_NULL_PTR_ARG(1);

				static uint8_t SImage_Host_SendBlockHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
				                                           SI_PIMA_Container_t* const PIMAHeader);
				static uint8_t SImage_Host_ReceiveBlockHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
				                                              SI_PIMA_Container_t* const PIMAHeader);
			#endif
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
