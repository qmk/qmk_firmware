/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Host mode driver for the library USB Audio 1.0 Class driver.
 *
 *  Host mode driver for the library USB Audio 1.0 Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassAudio
 *  \defgroup Group_USBClassAudioHost Audio 1.0 Class Host Mode Driver
 *
 *  \section Sec_USBClassAudioHost_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/AudioClassHost.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_USBClassAudioHost_ModDescription Module Description
 *  Host Mode USB Class driver framework interface, for the Audio 1.0 USB Class driver.
 *
 *  @{
 */

#ifndef __AUDIO_CLASS_HOST_H__
#define __AUDIO_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/AudioClassCommon.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_AUDIO_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** \brief Audio Class Host Mode Configuration and State Structure.
			 *
			 *  Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the Audio class driver functions as the \c AudioInterfaceInfo parameter. This
			 *  stores each Audio interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					USB_Pipe_Table_t DataINPipe; /**< Data IN Pipe configuration table. */
					USB_Pipe_Table_t DataOUTPipe; /**< Data OUT Pipe configuration table. */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                *   after \ref Audio_Host_ConfigurePipes() is called and the Host state machine is in the
					                *   Configured state.
					                */
					uint8_t ControlInterfaceNumber; /**< Interface index of the Audio Control interface within the attached device. */
					uint8_t StreamingInterfaceNumber; /**< Interface index of the Audio Streaming interface within the attached device. */

					uint8_t EnabledStreamingAltIndex; /**< Alternative setting index of the Audio Streaming interface when the stream is enabled. */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_Audio_Host_t;

		/* Enums: */
			/** Enum for the possible error codes returned by the \ref Audio_Host_ConfigurePipes() function. */
			enum AUDIO_Host_EnumerationFailure_ErrorCodes_t
			{
				AUDIO_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully. */
				AUDIO_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor. */
				AUDIO_ENUMERROR_NoCompatibleInterfaceFound = 2, /**< A compatible AUDIO interface was not found in the device's Configuration Descriptor. */
				AUDIO_ENUMERROR_PipeConfigurationFailed    = 3, /**< One or more pipes for the specified interface could not be configured correctly. */
			};

		/* Function Prototypes: */
			/** Host interface configuration routine, to configure a given Audio host interface instance using the Configuration
			 *  Descriptor read from an attached USB device. This function automatically updates the given Audio Host instance's
			 *  state values and configures the pipes required to communicate with the interface if it is found within the
			 *  device. This should be called once after the stack has enumerated the attached device, while the host state
			 *  machine is in the Addressed state.
			 *
			 *  \param[in,out] AudioInterfaceInfo    Pointer to a structure containing an Audio Class host configuration and state.
			 *  \param[in]     ConfigDescriptorSize  Length of the attached device's Configuration Descriptor.
			 *  \param[in]     ConfigDescriptorData  Pointer to a buffer containing the attached device's Configuration Descriptor.
			 *
			 *  \return A value from the \ref AUDIO_Host_EnumerationFailure_ErrorCodes_t enum.
			 */
			uint8_t Audio_Host_ConfigurePipes(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo,
			                                  uint16_t ConfigDescriptorSize,
			                                  void* ConfigDescriptorData) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);

			/** Starts or stops the audio streaming for the given configured Audio Host interface, allowing for audio samples to be
			 *  send and/or received.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class host configuration and state.
			 *  \param[in]     EnableStreaming     Boolean true to enable streaming of the specified interface, \c false to disable
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum.
			 */
			uint8_t Audio_Host_StartStopStreaming(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo,
			                                      const bool EnableStreaming) ATTR_NON_NULL_PTR_ARG(1);

			/** Gets or sets the specified property of a streaming audio class endpoint that is bound to a pipe in the given
			 *  class instance.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class host configuration and state.
			 *  \param[in]     DataPipeIndex       Index of the data pipe whose bound endpoint is to be altered.
			 *  \param[in]     EndpointProperty    Property of the endpoint to get or set, a value from \ref Audio_ClassRequests_t.
			 *  \param[in]     EndpointControl     Parameter of the endpoint to get or set, a value from \ref Audio_EndpointControls_t.
			 *  \param[in,out] DataLength          For SET operations, the length of the parameter data to set. For GET operations, the maximum
			 *                                     length of the retrieved data.
			 *  \param[in,out] Data                Pointer to a location where the parameter data is stored for SET operations, or where
			 *                                     the retrieved data is to be stored for GET operations.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum.
			 */
			uint8_t Audio_Host_GetSetEndpointProperty(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo,
			                                          const uint8_t DataPipeIndex,
			                                          const uint8_t EndpointProperty,
			                                          const uint8_t EndpointControl,
			                                          const uint16_t DataLength,
			                                          void* const Data) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(6);

		/* Inline Functions: */
			/** General management task for a given Audio host class interface, required for the correct operation of
			 *  the interface. This should be called frequently in the main program loop, before the master USB management task
			 *  \ref USB_USBTask().
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class host configuration and state.
			 */
			static inline void Audio_Host_USBTask(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			                                      ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline void Audio_Host_USBTask(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			{
				(void)AudioInterfaceInfo;
			}

			/** Determines if the given audio interface is ready for a sample to be read from it, and selects the streaming
			 *  IN pipe ready for reading.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *
			 *  \return Boolean \c true if the given Audio interface has a sample to be read, \c false otherwise.
			 */
			static inline bool Audio_Host_IsSampleReceived(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			                                               ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline bool Audio_Host_IsSampleReceived(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			{
				if ((USB_HostState != HOST_STATE_Configured) || !(AudioInterfaceInfo->State.IsActive))
				  return false;

				bool SampleReceived = false;

				Pipe_SelectPipe(AudioInterfaceInfo->Config.DataINPipe.Address);
				Pipe_Unfreeze();
				SampleReceived = Pipe_IsINReceived();
				Pipe_Freeze();

				return SampleReceived;
			}

			/** Determines if the given audio interface is ready to accept the next sample to be written to it, and selects
			 *  the streaming OUT pipe ready for writing.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *
			 *  \return Boolean \c true if the given Audio interface is ready to accept the next sample, \c false otherwise.
			 */
			static inline bool Audio_Host_IsReadyForNextSample(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			                                                   ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline bool Audio_Host_IsReadyForNextSample(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			{
				if ((USB_HostState != HOST_STATE_Configured) || !(AudioInterfaceInfo->State.IsActive))
				  return false;

				Pipe_SelectPipe(AudioInterfaceInfo->Config.DataOUTPipe.Address);
				return Pipe_IsOUTReady();
			}

			/** Reads the next 8-bit audio sample from the current audio interface.
			 *
			 *  \pre This should be preceded immediately by a call to the \ref Audio_Host_IsSampleReceived() function to ensure
			 *       that the correct pipe is selected and ready for data.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *
			 *  \return  Signed 8-bit audio sample from the audio interface.
			 */
			static inline int8_t Audio_Host_ReadSample8(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			                                            ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline int8_t Audio_Host_ReadSample8(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			{
				int8_t Sample;

				(void)AudioInterfaceInfo;

				Sample = Pipe_Read_8();

				if (!(Pipe_BytesInPipe()))
				{
					Pipe_Unfreeze();
					Pipe_ClearIN();
					Pipe_Freeze();
				}

				return Sample;
			}

			/** Reads the next 16-bit audio sample from the current audio interface.
			 *
			 *  \pre This should be preceded immediately by a call to the \ref Audio_Host_IsSampleReceived() function to ensure
			 *       that the correct pipe is selected and ready for data.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *
			 *  \return  Signed 16-bit audio sample from the audio interface.
			 */
			static inline int16_t Audio_Host_ReadSample16(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			                                              ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline int16_t Audio_Host_ReadSample16(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			{
				int16_t Sample;

				(void)AudioInterfaceInfo;

				Sample = (int16_t)Pipe_Read_16_LE();

				if (!(Pipe_BytesInPipe()))
				{
					Pipe_Unfreeze();
					Pipe_ClearIN();
					Pipe_Freeze();
				}

				return Sample;
			}

			/** Reads the next 24-bit audio sample from the current audio interface.
			 *
			 *  \pre This should be preceded immediately by a call to the \ref Audio_Host_IsSampleReceived() function to ensure
			 *       that the correct pipe is selected and ready for data.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *
			 *  \return Signed 24-bit audio sample from the audio interface.
			 */
			static inline int32_t Audio_Host_ReadSample24(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			                                              ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline int32_t Audio_Host_ReadSample24(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo)
			{
				int32_t Sample;

				(void)AudioInterfaceInfo;

				Sample = (((uint32_t)Pipe_Read_8() << 16) | Pipe_Read_16_LE());

				if (!(Pipe_BytesInPipe()))
				{
					Pipe_Unfreeze();
					Pipe_ClearIN();
					Pipe_Freeze();
				}

				return Sample;
			}

			/** Writes the next 8-bit audio sample to the current audio interface.
			 *
			 *  \pre This should be preceded immediately by a call to the \ref Audio_Host_IsReadyForNextSample() function to
			 *       ensure that the correct pipe is selected and ready for data.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *  \param[in]     Sample              Signed 8-bit audio sample.
			 */
			static inline void Audio_Host_WriteSample8(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo,
			                                           const int8_t Sample) ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline void Audio_Host_WriteSample8(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo,
			                                           const int8_t Sample)
			{
				(void)AudioInterfaceInfo;

				Pipe_Write_8(Sample);

				if (!(Pipe_IsReadWriteAllowed()))
				{
					Pipe_Unfreeze();
					Pipe_ClearOUT();
					Pipe_WaitUntilReady();
					Pipe_Freeze();
				}
			}

			/** Writes the next 16-bit audio sample to the current audio interface.
			 *
			 *  \pre This should be preceded immediately by a call to the \ref Audio_Host_IsReadyForNextSample() function to
			 *       ensure that the correct pipe is selected and ready for data.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *  \param[in]     Sample              Signed 16-bit audio sample.
			 */
			static inline void Audio_Host_WriteSample16(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo,
			                                            const int16_t Sample) ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline void Audio_Host_WriteSample16(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo,
			                                            const int16_t Sample)
			{
				(void)AudioInterfaceInfo;

				Pipe_Write_16_LE(Sample);

				if (!(Pipe_IsReadWriteAllowed()))
				{
					Pipe_Unfreeze();
					Pipe_ClearOUT();
					Pipe_WaitUntilReady();
					Pipe_Freeze();
				}
			}

			/** Writes the next 24-bit audio sample to the current audio interface.
			 *
			 *  \pre This should be preceded immediately by a call to the \ref Audio_Host_IsReadyForNextSample() function to
			 *       ensure that the correct pipe is selected and ready for data.
			 *
			 *  \param[in,out] AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
			 *  \param[in]     Sample              Signed 24-bit audio sample.
			 */
			static inline void Audio_Host_WriteSample24(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo,
			                                            const int32_t Sample) ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline void Audio_Host_WriteSample24(USB_ClassInfo_Audio_Host_t* const AudioInterfaceInfo,
			                                            const int32_t Sample)
			{
				(void)AudioInterfaceInfo;

				Pipe_Write_16_LE(Sample);
				Pipe_Write_8(Sample >> 16);

				if (!(Pipe_IsReadWriteAllowed()))
				{
					Pipe_Unfreeze();
					Pipe_ClearOUT();
					Pipe_WaitUntilReady();
					Pipe_Freeze();
				}
			}

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_AUDIO_HOST_C)
				static uint8_t DCOMP_Audio_Host_NextAudioControlInterface(void* CurrentDescriptor)
				                                                          ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DCOMP_Audio_Host_NextAudioStreamInterface(void* CurrentDescriptor)
				                                                         ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DCOMP_Audio_Host_NextAudioInterfaceDataEndpoint(void* CurrentDescriptor)
				                                                               ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

