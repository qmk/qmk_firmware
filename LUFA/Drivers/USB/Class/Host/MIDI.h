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

/** \ingroup Group_USBClassMIDI
 *  @defgroup Group_USBClassMIDIHost MIDI Class Host Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/MIDI.c
 *
 *  \section Module Description
 *  Host Mode USB Class driver framework interface, for the MIDI USB Class driver.
 *
 *  @{
 */

#ifndef __MIDI_CLASS_HOST_H__
#define __MIDI_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/MIDI.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_MIDI_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/Class/MIDI.h instead.
		#endif
		
	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the MIDI class driver functions as the MIDIInterfaceInfo parameter. This
			 *  stores each MIDI interface's configuration and state information.
			 */
			typedef struct
			{
				const struct
				{
					uint8_t  DataINPipeNumber; /**< Pipe number of the MIDI interface's streaming IN data pipe */
					bool     DataINPipeDoubleBank; /** Indicates if the MIDI interface's IN data pipe should use double banking */
					
					uint8_t  DataOUTPipeNumber; /**< Pipe number of the MIDI interface's streaming OUT data pipe */
					bool     DataOUTPipeDoubleBank; /** Indicates if the MIDI interface's OUT data pipe should use double banking */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                *   after \ref MIDI_Host_ConfigurePipes() is called and the Host state machine is in the
					                *   Configured state
					                */

					uint16_t DataINPipeSize; /**< Size in bytes of the MIDI Streaming Data interface's IN data pipe */
					uint16_t DataOUTPipeSize;  /**< Size in bytes of the MIDI Streaming Data interface's OUT data pipe */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_MIDI_Host_t;
			
		/* Enums: */
			/** Enum for the possible error codes returned by the \ref MIDI_Host_ConfigurePipes() function. */
			enum MIDIHost_EnumerationFailure_ErrorCodes_t
			{
				MIDI_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully */
				MIDI_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor */
				MIDI_ENUMERROR_NoStreamingInterfaceFound  = 2, /**< A compatible MIDI interface was not found in the device's Configuration Descriptor */
				MIDI_ENUMERROR_EndpointsNotFound          = 3, /**< Compatible MIDI data endpoints were not found in the device's MIDI interface */
			};
	
		/* Function Prototypes: */
			/** Host interface configuration routine, to configure a given MIDI host interface instance using the Configuration
			 *  Descriptor read from an attached USB device. This function automatically updates the given MIDI Host instance's
			 *  state values and configures the pipes required to communicate with the interface if it is found within the device.
			 *  This should be called once after the stack has enumerated the attached device, while the host state machine is in
			 *  the Addressed state.
			 *
			 *  \param[in,out] MIDIInterfaceInfo  Pointer to a structure containing an MIDI Class host configuration and state
			 *  \param[in] ConfigDescriptorSize  Length of the attached device's Configuration Descriptor
			 *  \param[in] DeviceConfigDescriptor  Pointer to a buffer containing the attached device's Configuration Descriptor
			 *
			 *  \return A value from the \ref MIDIHost_EnumerationFailure_ErrorCodes_t enum
			 */
			uint8_t MIDI_Host_ConfigurePipes(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo, uint16_t ConfigDescriptorSize,
			                                 void* DeviceConfigDescriptor) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);

			/** Sends a MIDI event packet to the device. If no device is connected, the event packet is discarded.
			 *
			 *  \note This function must only be called when the Host state machine is in the HOST_STATE_Configured state or the
			 *        call will fail.
			 *
			 *  \param[in,out] MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state
			 *  \param[in] Event  Pointer to a populated USB_MIDI_EventPacket_t structure containing the MIDI event to send
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum			 
			 */
			uint8_t MIDI_Host_SendEventPacket(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo,
			                                  MIDI_EventPacket_t* const Event) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Flushes the MIDI send buffer, sending any queued MIDI events to the device. This should be called to override the
			 *  \ref MIDI_Host_SendEventPacket() function's packing behaviour, to flush queued events. Events are queued into the
			 *  pipe bank until either the pipe bank is full, or \ref MIDI_Host_Flush() is called. This allows for multiple MIDI
			 *  events to be packed into a single pipe packet, increasing data throughput.
			 *
			 *  \param[in,out] MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state
			 *
			 *  \return A value from the \ref Pipe_WaitUntilReady_ErrorCodes_t enum
			 */
			 uint8_t MIDI_Host_Flush(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo);
			 
			/** Receives a MIDI event packet from the device.
			 *
			 *  \note This function must only be called when the Host state machine is in the HOST_STATE_Configured state or the
			 *        call will fail.
			 *
			 *  \param[in,out] MIDIInterfaceInfo  Pointer to a structure containing a MIDI Class configuration and state
			 *  \param[out] Event  Pointer to a USB_MIDI_EventPacket_t structure where the received MIDI event is to be placed
			 *
			 *  \return Boolean true if a MIDI event packet was received, false otherwise
			 */
			bool MIDI_Host_ReceiveEventPacket(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo,
			                                  MIDI_EventPacket_t* const Event) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

		/* Inline Functions: */
			/** General management task for a given MIDI host class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] MIDIInterfaceInfo  Pointer to a structure containing an MIDI Class host configuration and state
			 */
			static inline void MIDI_Host_USBTask(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo);
			static inline void MIDI_Host_USBTask(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo)
			{
				(void)MIDIInterfaceInfo;
			}

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define MIDI_STREAMING_CLASS           0x01
			#define MIDI_STREAMING_SUBCLASS        0x03
			#define MIDI_STREAMING_PROTOCOL        0x00
			
			#define MIDI_FOUND_DATAPIPE_IN           (1 << 0)
			#define MIDI_FOUND_DATAPIPE_OUT          (1 << 1)

		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_MIDI_CLASS_HOST_C)
				static uint8_t DComp_MIDI_Host_NextMIDIStreamingInterface(void* const CurrentDescriptor) ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DComp_MIDI_Host_NextMIDIStreamingDataEndpoint(void* const CurrentDescriptor) ATTR_NON_NULL_PTR_ARG(1);
			#endif	
	#endif
				
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
