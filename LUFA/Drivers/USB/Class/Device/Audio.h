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

/** \ingroup Group_USBClassAudio
 *  @defgroup Group_USBClassAudioDevice Audio Class Device Mode Driver
 *
 *  \section Module Description
 *  Device Mode USB Class driver framework interface, for the Audio USB Class driver.
 *
 *  @{
 */

#ifndef _AUDIO_CLASS_DEVICE_H_
#define _AUDIO_CLASS_DEVICE_H_

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/Audio.h"
		
		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */		
			/** Class state structure. An instance of this structure should be made for each Audio interface
			 *  within the user application, and passed to each of the Audio class driver functions as the
			 *  AudioInterfaceInfo parameter. This stores each Audio interface's configuration and state information.
			 */
			typedef struct
			{
				const struct
				{
					uint8_t  StreamingInterfaceNumber; /**< Index of the Audio Streaming interface within the device this
														*   structure controls.
														*/

					uint8_t  DataINEndpointNumber; /**< Endpoint number of the incomming Audio Streaming data, if available
													*   (zero if unused).
													*/
					uint16_t DataINEndpointSize; /**< Size in bytes of the incomming Audio Streaming data endpoint, if available
												  *   (zero if unused).
												  */

					uint8_t  DataOUTEndpointNumber; /**< Endpoint number of the outgoing Audio Streaming data, if available
													 *   (zero if unused).
													 */
					uint16_t DataOUTEndpointSize; /**< Size in bytes of the outgoing Audio Streaming data endpoint, if available
												   *   (zero if unused).
												   */			
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool     InterfaceEnabled; /**< Set and cleared by the class driver to indicate if the host has enabled the streaming endpoints
												*   of the Audio Streaming interface.
												*/
				} State; /**< State data for the USB class interface within the device. All elements in this section
				          *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
				          *   the interface is enumerated.
				          */				
			} USB_ClassInfo_Audio_Device_t;
		
		/* Function Prototypes: */
			/** Configures the endpoints of a given Audio interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_ConfigurationChanged() event so that the endpoints are configured when the configuration containing the
			 *  given Audio interface is selected.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *
			 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
			 */
			bool Audio_Device_ConfigureEndpoints(USB_ClassInfo_Audio_Device_t* const AudioInterfaceInfo);

			/** Processes incomming control requests from the host, that are directed to the given Audio class interface. This should be
			 *  linked to the library \ref EVENT_USB_UnhandledControlPacket() event.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 */
			void Audio_Device_ProcessControlPacket(USB_ClassInfo_Audio_Device_t* const AudioInterfaceInfo);

			/** General management task for a given Audio class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 */
			void Audio_Device_USBTask(USB_ClassInfo_Audio_Device_t* const AudioInterfaceInfo);
			
			/** Reads the next 8-bit audio sample from the current audio interface.
			 *
			 *  \note This should be preceeded immediately by a call to the USB_Audio_IsSampleReceived() function to ensure that
			 *        the correct endpoint is selected and ready for data.
			 *
			 *  \return  Signed 8-bit audio sample from the audio interface
			 */
			int8_t Audio_Device_ReadSample8(void);

			/** Reads the next 16-bit audio sample from the current audio interface.
			 *
			 *  \note This should be preceeded immediately by a call to the USB_Audio_IsSampleReceived() function to ensure that
			 *        the correct endpoint is selected and ready for data.
			 *
			 *  \return  Signed 16-bit audio sample from the audio interface
			 */
			int16_t Audio_Device_ReadSample16(void);

			/** Reads the next 24-bit audio sample from the current audio interface.
			 *
			 *  \note This should be preceeded immediately by a call to the USB_Audio_IsSampleReceived() function to ensure that
			 *        the correct endpoint is selected and ready for data.
			 *
			 *  \return  Signed 24-bit audio sample from the audio interface
			 */
			int32_t Audio_Device_ReadSample24(void);

			/** Writes the next 8-bit audio sample to the current audio interface.
			 *
			 *  \note This should be preceeded immediately by a call to the USB_Audio_IsReadyForNextSample() function to ensure that
			 *        the correct endpoint is selected and ready for data.
			 *
			 *  \param[in] Sample  Signed 8-bit audio sample
			 */
			void Audio_Device_WriteSample8(const int8_t Sample);

			/** Writes the next 16-bit audio sample to the current audio interface.
			 *
			 *  \note This should be preceeded immediately by a call to the USB_Audio_IsReadyForNextSample() function to ensure that
			 *        the correct endpoint is selected and ready for data.
			 *
			 *  \param[in] Sample  Signed 16-bit audio sample
			 */
			void Audio_Device_WriteSample16(const int16_t Sample);

			/** Writes the next 24-bit audio sample to the current audio interface.
			 *
			 *  \note This should be preceeded immediately by a call to the USB_Audio_IsReadyForNextSample() function to ensure that
			 *        the correct endpoint is selected and ready for data.
			 *
			 *  \param[in] Sample  Signed 24-bit audio sample
			 */
			void Audio_Device_WriteSample24(const int32_t Sample);

			/** Determines if the given audio interface is ready for a sample to be read from it.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *
			 *  \return Boolean true if the given Audio interface has a sample to be read, false otherwise
			 */
			bool Audio_Device_IsSampleReceived(USB_ClassInfo_Audio_Device_t* const AudioInterfaceInfo);

			/** Determines if the given audio interface is ready to accept the next sample to be written to it.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *
			 *  \return Boolean true if the given Audio interface is ready to accept the next sample, false otherwise
			 */
			bool Audio_Device_IsReadyForNextSample(USB_ClassInfo_Audio_Device_t* const AudioInterfaceInfo);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
