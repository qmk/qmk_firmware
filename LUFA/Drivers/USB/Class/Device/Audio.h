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

/** \ingroup Group_USBDeviceClassDrivers
 *  @defgroup Group_USBClassAudioDevice Audio Device Class Driver - LUFA/Drivers/Class/Device/Audio.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/Audio.c
 *
 *  \section Module Description
 *  Functions, macros, variables, enums and types related to the management of USB Audio Class interfaces
 *  within a USB device.
 *
 *  @{
 */

#ifndef _AUDIO_CLASS_H_
#define _AUDIO_CLASS_H_

	/* Includes: */
		#include "../../USB.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Macros: */
		/** Descriptor header constant to indicate a Audio class interface descriptor. */
		#define DTYPE_AudioInterface         0x24

		/** Descriptor header constant to indicate a Audio class endpoint descriptor. */
		#define DTYPE_AudioEndpoint          0x25

		/** Audio class descriptor subtype value for a Audio class specific header descriptor. */
		#define DSUBTYPE_Header              0x01

		/** Audio class descriptor subtype value for an Output Terminal Audio class specific descriptor. */
		#define DSUBTYPE_InputTerminal       0x02

		/** Audio class descriptor subtype value for an Input Terminal Audio class specific descriptor. */
		#define DSUBTYPE_OutputTerminal      0x03

		/** Audio class descriptor subtype value for a Feature Unit Audio class specific descriptor. */
		#define DSUBTYPE_FeatureUnit         0x06

		/** Audio class descriptor subtype value for a general Audio class specific descriptor. */
		#define DSUBTYPE_General             0x01

		/** Audio class descriptor subtype value for an Audio class specific descriptor indicating the format of an audio stream. */
		#define DSUBTYPE_Format              0x02
		
		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_LEFT_FRONT           (1 << 0)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_RIGHT_FRONT          (1 << 1)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_CENTER_FRONT         (1 << 2)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_LOW_FREQ_ENHANCE     (1 << 3)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_LEFT_SURROUND        (1 << 4)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_RIGHT_SURROUND       (1 << 5)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_LEFT_OF_CENTER       (1 << 6)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_RIGHT_OF_CENTER      (1 << 7)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_SURROUND             (1 << 8)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_SIDE_LEFT            (1 << 9)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_SIDE_RIGHT           (1 << 10)

		/** Supported channel mask for an Audio class terminal descriptor. See the Audio class specification for more details. */
		#define CHANNEL_TOP                  (1 << 11)

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */
		#define FEATURE_MUTE                 (1 << 0)

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */
		#define FEATURE_VOLUME               (1 << 1)

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */
		#define FEATURE_BASS                 (1 << 2)

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */
		#define FEATURE_MID                  (1 << 3)

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */
		#define FEATURE_TREBLE               (1 << 4)

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */
		#define FEATURE_GRAPHIC_EQUALIZER    (1 << 5)

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */
		#define FEATURE_AUTOMATIC_GAIN       (1 << 6)

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */
		#define FEATURE_DELAY                (1 << 7)

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */
		#define FEATURE_BASS_BOOST           (1 << 8)

		/** Supported feature mask for an Audio class feature unit descriptor. See the Audio class specification for more details. */
		#define FEATURE_BASS_LOUDNESS        (1 << 9)

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_UNDEFINED           0x0100

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_STREAMING           0x0101

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_VENDOR              0x01FF

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_IN_UNDEFINED        0x0200

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_IN_MIC              0x0201

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_IN_DESKTOP_MIC      0x0202

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_IN_PERSONAL_MIC     0x0203

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_IN_OMNIDIR_MIC      0x0204

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_IN_MIC_ARRAY        0x0205

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_IN_PROCESSING_MIC   0x0206

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_IN_OUT_UNDEFINED    0x0300

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_OUT_SPEAKER         0x0301

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_OUT_HEADPHONES      0x0302

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_OUT_HEAD_MOUNTED    0x0303

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_OUT_DESKTOP         0x0304

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_OUT_ROOM            0x0305

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_OUT_COMMUNICATION   0x0306

		/** Terminal type constant for an Audio class terminal descriptor. See the Audio class specification for more details. */		
		#define TERMINAL_OUT_LOWFREQ         0x0307

		/** Convenience macro, to fill a 24-bit AudioSampleFreq_t structure with the given sample rate as a 24-bit number.
		 *
		 *  \param freq  Required audio sampling frequency in HZ
		 */
		#define AUDIO_SAMPLE_FREQ(freq)  {LowWord: ((uint32_t)freq & 0x00FFFF), HighByte: (((uint32_t)freq >> 16) & 0x0000FF)}
		
		/** Mask for the attributes parameter of an Audio class specific Endpoint descriptor, indicating that the endpoint
		 *  accepts only filled endpoint packets of audio samples.
		 */
		#define EP_ACCEPTS_ONLY_FULL_PACKETS (1 << 7)

		/** Mask for the attributes parameter of an Audio class specific Endpoint descriptor, indicating that the endpoint
		 *  will accept partially filled endpoint packets of audio samples.
		 */
		#define EP_ACCEPTS_SMALL_PACKETS     (0 << 7)
		
	/* Type Defines: */
		/** Type define for an Audio class specific interface descriptor. This follows a regular interface descriptor to
		 *  supply extra information about the audio device's layout to the host. See the USB Audio specification for more
		 *  details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */

			uint16_t                  ACSpecification; /**< Binary coded decimal value, indicating the supported Audio Class specification version */
			uint16_t                  TotalLength; /**< Total length of the Audio class specific descriptors, including this descriptor */
			
			uint8_t                   InCollection; /**< Total number of audio class interfaces within this device */
			uint8_t                   InterfaceNumbers[1]; /**< Interface numbers of each audio interface */
		} USB_AudioInterface_AC_t;
		
		/** Type define for an Audio class specific Feature Unit descriptor. This indicates to the host what features
		 *  are present in the device's audio stream for basic control, such as per-channel volume. See the USB Audio
		 *  specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */
			
			uint8_t                   UnitID; /**< ID value of this feature unit - must be a unique value within the device */
			uint8_t                   SourceID; /**< Source ID value of the audio source input into this feature unit */
			
			uint8_t                   ControlSize; /**< Size of each element in the ChanelControlls array */
			uint8_t                   ChannelControls[3]; /**< Feature masks for the control channel, and each separate audio channel */
			
			uint8_t                   FeatureUnitStrIndex; /**< Index of a string descriptor describing this descriptor within the device */
		} USB_AudioFeatureUnit_t;

		/** Type define for an Audio class specific input terminal descriptor. This indicates to the host that the device
		 *  contains an input audio source, either from a physical terminal on the device, or a logical terminal (for example,
		 *  a USB endpoint). See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */
		
			uint8_t                   TerminalID; /**< ID value of this terminal unit - must be a unique value within the device */
			uint16_t                  TerminalType; /**< Type of terminal, a TERMINAL_* mask */
			uint8_t                   AssociatedOutputTerminal; /**< ID of associated output terminal, for physically grouped terminals
			                                                     *   such as the speaker and microphone of a phone handset
			                                                     */
			uint8_t                   TotalChannels; /**< Total number of separate audio channels within this interface (right, left, etc.) */
			uint16_t                  ChannelConfig; /**< CHANNEL_* masks indicating what channel layout is supported by this terminal */
			
			uint8_t                   ChannelStrIndex; /**< Index of a string descriptor describing this channel within the device */
			uint8_t                   TerminalStrIndex; /**< Index of a string descriptor describing this descriptor within the device */
		} USB_AudioInputTerminal_t;

		/** Type define for an Audio class specific output terminal descriptor. This indicates to the host that the device
		 *  contains an output audio sink, either to a physical terminal on the device, or a logical terminal (for example,
		 *  a USB endpoint). See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */
		
			uint8_t                   TerminalID; /**< ID value of this terminal unit - must be a unique value within the device */
			uint16_t                  TerminalType; /**< Type of terminal, a TERMINAL_* mask */
			uint8_t                   AssociatedInputTerminal; /**< ID of associated input terminal, for physically grouped terminals
			                                                    *   such as the speaker and microphone of a phone handset
			                                                    */
			uint8_t                   SourceID; /**< ID value of the unit this terminal's audio is sourced from */
			
			uint8_t                   TerminalStrIndex; /**< Index of a string descriptor describing this descriptor within the device */
		} USB_AudioOutputTerminal_t;
		
		/** Type define for an Audio class specific streaming interface descriptor. This indicates to the host
		 *  how audio streams within the device are formatted. See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */
			
			uint8_t                   TerminalLink; /**< ID value of the output terminal this descriptor is describing */
			
			uint8_t                   FrameDelay; /**< Delay in frames resulting from the complete sample processing from input to output */
			uint16_t                  AudioFormat; /**< Format of the audio stream, see Audio Device Formats specification */
		} USB_AudioInterface_AS_t;
		
		/** Type define for a 24bit audio sample frequency structure. GCC does not contain a built in 24bit datatype,
		 *  this this structure is used to build up the value instead. Fill this structure with the SAMPLE_FREQ() macro.
		 */
		typedef struct
		{
			uint16_t                  LowWord; /**< Low 16 bits of the 24-bit value */
			uint8_t                   HighByte; /**< Upper 8 bits of the 24-bit value */
		} AudioSampleFreq_t;

		/** Type define for an Audio class specific audio format descriptor. This is used to give the host full details
		 *  about the number of channels, the sample resolution, acceptable sample frequencies and encoding method used
		 *  in the device's audio streams. See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */

			uint8_t                   FormatType; /**< Format of the audio stream, see Audio Device Formats specification */
			uint8_t                   Channels; /**< Total number of discrete channels in the stream */
			
			uint8_t                   SubFrameSize; /**< Size in bytes of each channel's sample data in the stream */
			uint8_t                   BitResolution; /**< Bits of resolution of each channel's samples in the stream */

			uint8_t                   SampleFrequencyType; /**< Total number of sample frequencies supported by the device */			
			AudioSampleFreq_t         SampleFrequencies[1]; /**< Sample frequencies supported by the device */
		} USB_AudioFormat_t;
		
		/** Type define for an Audio class specific endpoint descriptor. This contains a regular endpoint 
		 *  descriptor with a few Audio-class specific extensions. See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Endpoint_t Endpoint; /**< Standard endpoint descriptor describing the audio endpoint */

			uint8_t                   Refresh; /**< Always set to zero */
			uint8_t                   SyncEndpointNumber; /**< Endpoint address to send synchronisation information to, if needed (zero otherwise) */
		} USB_AudioStreamEndpoint_Std_t;
					
		/** Type define for an Audio class specific extended endpoint descriptor. This contains extra information
		 *  on the usage of endpoints used to stream audio in and out of the USB Audio device, and follows an Audio
		 *  class specific extended endpoint descriptor. See the USB Audio specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t   Header; /**< Regular descriptor header containing the descriptor's type and length */
			uint8_t                   Subtype; /**< Sub type value used to distinguish between audio class specific descriptors */
			
			uint8_t                   Attributes; /**< Audio class specific endpoint attributes, such as ACCEPTS_SMALL_PACKETS */

			uint8_t                   LockDelayUnits; /**< Units used for the LockDelay field, see Audio class specification */
			uint16_t                  LockDelay; /**< Time required to internally lock endpoint's internal clock recovery circuitry */
		} USB_AudioStreamEndpoint_Spc_t;	

		/** Type define for an Audio Class interface configuration and state structure. This structure should be used for each Audio
		 *  Class unit within the device, and passed (per-interface) to the Audio Class driver functions so that each Audio interface
		 *  has seperate state and configuration data and can be controlled seperately.
		 */
		typedef struct
		{
			uint8_t  StreamingInterfaceNumber; /**< Index of the Audio Streaming interface within the device this structure controls */

			uint8_t  DataINEndpointNumber; /**< Endpoint number of the incomming Audio Streaming data, if available (zero if unused) */
			uint16_t DataINEndpointSize; /**< Size in bytes of the incomming Audio Streaming data endpoint, if available (zero if unused) */

			uint8_t  DataOUTEndpointNumber; /**< Endpoint number of the outgoing Audio Streaming data, if available (zero if unused) */
			uint16_t DataOUTEndpointSize; /**< Size in bytes of the outgoing Audio Streaming data endpoint, if available (zero if unused) */

			bool     InterfaceEnabled; /**< Set and cleared by the class driver to indicate if the host has enabled the streaming endpoints
			                            *   of the Audio Streaming interface
			                            */
		} USB_ClassInfo_Audio_t;
		
	/* Function Prototypes: */
		/** Configures the endpoints of a given Audio interface, ready for use. This should be linked to the library
		 *  \ref EVENT_USB_ConfigurationChanged() event so that the endpoints are configured when the configuration containing the
		 *  given Audio interface is selected.
		 *
		 *  \param AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
		 *
		 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
		 */
		bool     USB_Audio_ConfigureEndpoints(USB_ClassInfo_Audio_t* AudioInterfaceInfo);

		/** Processes incomming control requests from the host, that are directed to the given Audio class interface. This should be
		 *  linked to the library \ref EVENT_USB_UnhandledControlPacket() event.
		 *
		 *  \param AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
		 */
		void     USB_Audio_ProcessControlPacket(USB_ClassInfo_Audio_t* AudioInterfaceInfo);

		/** General management task for a given Audio class interface, required for the correct operation of the interface. This should
		 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
		 *
		 *  \param AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
		 */
		void     USB_Audio_USBTask(USB_ClassInfo_Audio_t* AudioInterfaceInfo);
		
		/** Reads the next 8-bit audio sample from the current audio interface.
		 *
		 *  \note This should be preceeded immediately by a call to the USB_Audio_IsSampleReceived() function to ensure that
		 *        the correct endpoint is selected and ready for data.
		 *
		 *  \return  Signed 8-bit audio sample from the audio interface
		 */
		int8_t   USB_Audio_ReadSample8(void);

		/** Reads the next 16-bit audio sample from the current audio interface.
		 *
		 *  \note This should be preceeded immediately by a call to the USB_Audio_IsSampleReceived() function to ensure that
		 *        the correct endpoint is selected and ready for data.
		 *
		 *  \return  Signed 16-bit audio sample from the audio interface
		 */
		int16_t  USB_Audio_ReadSample16(void);

		/** Reads the next 24-bit audio sample from the current audio interface.
		 *
		 *  \note This should be preceeded immediately by a call to the USB_Audio_IsSampleReceived() function to ensure that
		 *        the correct endpoint is selected and ready for data.
		 *
		 *  \return  Signed 24-bit audio sample from the audio interface
		 */
		int32_t  USB_Audio_ReadSample24(void);

		/** Writes the next 8-bit audio sample to the current audio interface.
		 *
		 *  \note This should be preceeded immediately by a call to the USB_Audio_IsReadyForNextSample() function to ensure that
		 *        the correct endpoint is selected and ready for data.
		 *
		 *  \param Sample  Signed 8-bit audio sample
		 */
		void     USB_Audio_WriteSample8(int8_t Sample);

		/** Writes the next 16-bit audio sample to the current audio interface.
		 *
		 *  \note This should be preceeded immediately by a call to the USB_Audio_IsReadyForNextSample() function to ensure that
		 *        the correct endpoint is selected and ready for data.
		 *
		 *  \param Sample  Signed 16-bit audio sample
		 */
		void     USB_Audio_WriteSample16(int16_t Sample);

		/** Writes the next 24-bit audio sample to the current audio interface.
		 *
		 *  \note This should be preceeded immediately by a call to the USB_Audio_IsReadyForNextSample() function to ensure that
		 *        the correct endpoint is selected and ready for data.
		 *
		 *  \param Sample  Signed 24-bit audio sample
		 */
		void     USB_Audio_WriteSample24(int32_t Sample);

		/** Determines if the given audio interface is ready for a sample to be read from it.
		 *
		 *  \param AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
		 *
		 *  \return Boolean true if the given Audio interface has a sample to be read, false otherwise
		 */
		bool     USB_Audio_IsSampleReceived(USB_ClassInfo_Audio_t* AudioInterfaceInfo);

		/** Determines if the given audio interface is ready to accept the next sample to be written to it.
		 *
		 *  \param AudioInterfaceInfo  Pointer to a structure containing an Audio Class configuration and state.
		 *
		 *  \return Boolean true if the given Audio interface is ready to accept the next sample, false otherwise
		 */
		bool     USB_Audio_IsReadyForNextSample(USB_ClassInfo_Audio_t* AudioInterfaceInfo);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
