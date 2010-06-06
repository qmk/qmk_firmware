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
	
	/* Enums: */
		/** Enum for the types of RFCOMM frames which can be exchanged on a Bluetooth channel. */
		enum RFCOMM_Frame_Types_t
		{
			RFCOMM_Frame_SABM  = 0x2F, /**< Set Asynchronous Balance Mode Field */
			RFCOMM_Frame_UA    = 0x63, /**< Unnumbered Acknowledgement Field */
			RFCOMM_Frame_DM    = 0x0F, /**< Disconnected Mode Field */
			RFCOMM_Frame_DISC  = 0x43, /**< Disconnect Field */
			RFCOMM_Frame_UIH   = 0xEF, /**< Unnumbered Information with Header check Field */
		};
	
	/* Type Defines: */
		typedef struct
		{
			struct
			{
				unsigned char LogicalChannel   : 6;
				unsigned char PollResponse     : 1;
				unsigned char LastAddressOctet : 1;
			} Address;
			
			uint8_t Control;
		} RFCOMM_Header_t;

	/* Function Prototypes: */
		void RFCOMM_Initialize(void);
		void RFCOMM_ProcessPacket(void* Data, Bluetooth_Channel_t* const Channel);
		
		#if defined(INCLUDE_FROM_RFCOMM_C)
			static void RFCOMM_ProcessSABM(const RFCOMM_Header_t* const FrameHeader, Bluetooth_Channel_t* const Channel);
			static void RFCOMM_ProcessUA(const RFCOMM_Header_t* const FrameHeader, Bluetooth_Channel_t* const Channel);
			static void RFCOMM_ProcessDM(const RFCOMM_Header_t* const FrameHeader, Bluetooth_Channel_t* const Channel);
			static void RFCOMM_ProcessDISC(const RFCOMM_Header_t* const FrameHeader, Bluetooth_Channel_t* const Channel);
			static void RFCOMM_ProcessUIH(const RFCOMM_Header_t* const FrameHeader, Bluetooth_Channel_t* const Channel);

			static uint8_t  RFCOMM_GetFCSValue(const void* FrameStart, uint16_t Length);
			static uint16_t RFCOMM_GetFrameDataLength(const uint8_t** BufferPos);
		#endif
		
#endif
