/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
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

/** \ingroup Group_USBClassPrinter
 *  @defgroup Group_USBClassPrinterHost Printer Class Host Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/Printer.c
 *
 *  \section Module Description
 *  Host Mode USB Class driver framework interface, for the Printer USB Class driver.
 *
 *  @{
 */

#ifndef __PRINTER_CLASS_HOST_H__
#define __PRINTER_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/Printer.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
	
		/* Type Defines: */
			/** Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the Printer class driver functions as the PRNTInterfaceInfo parameter. This
			 *  stores each Printer interface's configuration and state information.
			 */
			typedef struct
			{
				const struct
				{
					uint8_t  DataINPipeNumber; /**< Pipe number of the Printer interface's IN data pipe */
					bool     DataINPipeDoubleBank; /** Indicates if the Printer interface's IN data pipe should use double banking */

					uint8_t  DataOUTPipeNumber; /**< Pipe number of the Printer interface's OUT data pipe */
					bool     DataOUTPipeDoubleBank; /** Indicates if the Printer interface's OUT data pipe should use double banking */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                *   after \ref PRNT_Host_ConfigurePipes() is called and the Host state machine is in the
					                *   Configured state
					                */
					uint8_t InterfaceNumber; /**< Interface index of the Printer interface within the attached device */
					uint8_t AlternateSetting; /**< Alternate setting within the Printer Interface in the attached device */

					uint16_t DataINPipeSize; /**< Size in bytes of the Printer interface's IN data pipe */
					uint16_t DataOUTPipeSize;  /**< Size in bytes of the Printer interface's OUT data pipe */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_PRNT_Host_t;

		/* Enums: */
			enum PRNTHost_EnumerationFailure_ErrorCodes_t
			{
				PRNT_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully */
				PRNT_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor */
				PRNT_ENUMERROR_NoPrinterInterfaceFound    = 2, /**< A compatible Printer interface was not found in the device's Configuration Descriptor */
				PRNT_ENUMERROR_EndpointsNotFound          = 3, /**< Compatible Printer endpoints were not found in the device's interfaces */
			};
	
		/* Function Prototypes: */
			/** General management task for a given Printer host class interface, required for the correct operation of
			 *  the interface. This should be called frequently in the main program loop, before the master USB management task
			 *  \ref USB_USBTask().
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state
			 */
			void PRNT_Host_USBTask(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			

			/** Host interface configuration routine, to configure a given Printer host interface instance using the
			 *  Configuration Descriptor read from an attached USB device. This function automatically updates the given Printer
			 *  instance's state values and configures the pipes required to communicate with the interface if it is found within
			 *  the device. This should be called once after the stack has enumerated the attached device, while the host state
			 *  machine is in the Addressed state.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state
			 *  \param[in] ConfigDescriptorSize  Length of the attached device's Configuration Descriptor
			 *  \param[in] DeviceConfigDescriptor  Pointer to a buffer containing the attached device's Configuration Descriptor
			 *
			 *  \return A value from the \ref PRNTHost_EnumerationFailure_ErrorCodes_t enum
			 */
			uint8_t PRNT_Host_ConfigurePipes(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo, uint16_t ConfigDescriptorSize,
			                                 void* DeviceConfigDescriptor) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);
			
			/** Configures the printer to enable Bidirectional mode, if it is not already in this mode. This should be called
			 *  once the connected device's configuration has been set, to ensure the printer is ready to accept commands.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum
			 */
			uint8_t PRNT_Host_SetBidirectionalMode(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Retrieves the status of the virtual Printer port's inbound status lines. The result can then be masked against the
			 *  PRNT_PORTSTATUS_* macros to determine the printer port's status.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state
			 *  \param[out]  PortStatus  Location where the retrieved port status should be stored
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum
			 */
			uint8_t PRNT_Host_GetPortStatus(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo, uint8_t* const PortStatus)
			                                ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Soft-resets the attached printer, readying it for new commands.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum
			 */
			uint8_t PRNT_Host_SoftReset(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends the given raw data stream to the attached printer's input endpoint. This should contain commands that the
			 *  printer is able to understand - for example, PCL data. Not all printers accept all printer languages; see
			 *  \ref PRNT_Host_GetDeviceID() for details on determining acceptable languages for an attached printer.
			 *
			 *  \note This function must only be called when the Host state machine is in the HOST_STATE_Configured state or the
			 *        call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state
			 *  \param[in] PrinterCommands  Pointer to a buffer containing the raw command stream to send to the printer
			 *  \param[in] CommandSize  Size in bytes of the command stream to be sent
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum
			 */
			uint8_t PRNT_Host_SendData(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo, void* PrinterCommands, 
			                           uint16_t CommandSize) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Retrieves the attached printer device's ID string, formatted according to IEEE 1284. This string is sent as a
			 *  Unicode string from the device and is automatically converted to an ASCII encoded C string by this function, thus
			 *  the maximum reportable string length is two less than the size given (to accommodate the Unicode string length
			 *  bytes which are removed).
			 *
			 *  This string, when supported, contains the model, manufacturer and acceptable printer languages for the attached device.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state
			 *  \param[out] DeviceIDString  Pointer to a buffer where the Device ID string should be stored, in ASCII format
			 *  \param[in] BufferSize  Size in bytes of the buffer allocated for the Device ID string
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum
			 */
			uint8_t PRNT_Host_GetDeviceID(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo, char* DeviceIDString,
			                              uint16_t BufferSize) ATTR_NON_NULL_PTR_ARG(1);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define PRINTER_CLASS                  0x07
			#define PRINTER_SUBCLASS               0x01
			#define PRINTER_PROTOCOL               0x02

			#define REQ_GetDeviceID                0
			#define REQ_GetPortStatus              1
			#define REQ_SoftReset                  2
		
			#define PRNT_FOUND_DATAPIPE_IN         (1 << 0)
			#define PRNT_FOUND_DATAPIPE_OUT        (1 << 1)
			
		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_PRINTER_CLASS_HOST_C)		
				static uint8_t DComp_NextPRNTInterface(void* const CurrentDescriptor);
				static uint8_t DComp_NextPRNTInterfaceEndpoint(void* const CurrentDescriptor);
			#endif
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
