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

/** \file
 *
 *  Header file for RFCOMM.c.
 */

#ifndef _RFCOMM_H_
#define _RFCOMM_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>
		#include <string.h>
		#include <stdbool.h>
		#include <stdio.h>

		#include <LUFA/Common/Common.h>
		#include <LUFA/Drivers/Peripheral/SerialStream.h>

		#include "BluetoothStack.h"
		
	/* Macros: */
		#define BT_RFCOMM_DEBUG(l, s, ...)              do { if (RFCOMM_DEBUG_LEVEL >= l) printf_P(PSTR("(RFCOMM) " s "\r\n"), ##__VA_ARGS__); } while (0)
		#define RFCOMM_DEBUG_LEVEL                      2
		
		#define FRAME_POLL_FINAL                        (1 << 4)
		
		#define RFCOMM_CONTROL_DLCI                     0
		
		#define RFCOMM_MAX_OPEN_CHANNELS                5
	
	/* Enums: */
		/** Enum for the types of RFCOMM frames which can be exchanged on a Bluetooth channel. */
		enum RFCOMM_Frame_Types_t
		{
			RFCOMM_Frame_DM    = 0x0F, /**< Disconnected Mode Field */
			RFCOMM_Frame_DISC  = 0x43, /**< Disconnect Field */
			RFCOMM_Frame_SABM  = 0x2F, /**< Set Asynchronous Balance Mode Field */
			RFCOMM_Frame_UA    = 0x63, /**< Unnumbered Acknowledgement Field */
			RFCOMM_Frame_UIH   = 0xEF, /**< Unnumbered Information with Header check Field */
		};
		
		enum RFCOMM_Control_Commands_t
		{
			RFCOMM_Control_Test                    = (0x20 >> 2),
			RFCOMM_Control_FlowControlEnable       = (0xA0 >> 2),
			RFCOMM_Control_FlowControlDisable      = (0x60 >> 2),
			RFCOMM_Control_ModemStatus             = (0xE0 >> 2),
			RFCOMM_Control_RemotePortNegotiation   = (0x90 >> 2),
			RFCOMM_Control_RemoteLineStatus        = (0x50 >> 2),
			RFCOMM_Control_DLCParameterNegotiation = (0x80 >> 2),
			RFCOMM_Control_NonSupportedCommand     = (0x10 >> 2),
		};
	
	/* Type Defines: */
		typedef struct
		{
			unsigned char EA   : 1;
			unsigned char CR   : 1;
			unsigned char DLCI : 6;
		} RFCOMM_Address_t;
	
		typedef struct
		{
			RFCOMM_Address_t Address;
			uint8_t          Control;
		} RFCOMM_Header_t;
		
		typedef struct
		{
			unsigned char EA      : 1;
			unsigned char CR      : 1;
			unsigned char Command : 6;
		} RFCOMM_Command_t;
		
		typedef struct
		{
			uint8_t DLCI;
			bool    Configured;
		} RFCOMM_Channel_t;

	/* Function Prototypes: */
		void RFCOMM_Initialize(void);
		void RFCOMM_ProcessPacket(void* Data, Bluetooth_Channel_t* const Channel);
		
		#if defined(INCLUDE_FROM_RFCOMM_C)
			static void RFCOMM_ProcessDM(const RFCOMM_Address_t* const FrameAddress, Bluetooth_Channel_t* const Channel);
			static void RFCOMM_ProcessDISC(const RFCOMM_Address_t* const FrameAddress, Bluetooth_Channel_t* const Channel);
			static void RFCOMM_ProcessSABM(const RFCOMM_Address_t* const FrameAddress, Bluetooth_Channel_t* const Channel);
			static void RFCOMM_ProcessUA(const RFCOMM_Address_t* const FrameAddress, Bluetooth_Channel_t* const Channel);
			static void RFCOMM_ProcessUIH(const RFCOMM_Address_t* const FrameAddress, const uint16_t FrameLength, 
                                          const uint8_t* FrameData, Bluetooth_Channel_t* const Channel);

			static void RFCOMM_ProcessControlCommand(const uint8_t* Command, Bluetooth_Channel_t* const Channel);
			
			static void RFCOMM_SendFrame(const uint8_t DLCI, const bool CommandResponse, const uint8_t Control,
			                             const uint16_t DataLen, const void* Data, Bluetooth_Channel_t* const Channel);
			
			static uint8_t  RFCOMM_GetFCSValue(const void* FrameStart, uint8_t Length);
			static uint16_t RFCOMM_GetFrameDataLength(const uint8_t* const BufferPos);

			RFCOMM_Channel_t* RFCOMM_GetChannelData(const uint8_t DLCI);
		#endif
		
#endif
