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
 *
 *  Header file for V2Protocol.c.
 */

#ifndef _V2_PROTOCOL_
#define _V2_PROTOCOL_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/interrupt.h>
		#include <avr/wdt.h>

		#include <LUFA/Drivers/USB/USB.h>

		#include "../AVRISPDescriptors.h"
		#include "V2ProtocolConstants.h"
		#include "V2ProtocolParams.h"
		#include "ISP/ISPProtocol.h"
		#include "XPROG/XPROGProtocol.h"
		#include "Config/AppConfig.h"
		
	/* Preprocessor Checks: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#undef ENABLE_ISP_PROTOCOL

			#if !defined(ENABLE_XPROG_PROTOCOL)
				#define ENABLE_XPROG_PROTOCOL
			#endif
		#endif

		#if defined(USB_SERIES_4_AVR) && ((VTARGET_ADC_CHANNEL == 2) || (VTARGET_ADC_CHANNEL == 3)) && !defined(NO_VTARGET_DETECT)
			#error The U4 AVR chips do not contain ADC channels 2 or 3. Please change VTARGET_ADC_CHANNEL or define NO_VTARGET_DETECT in the makefile.
		#endif

		#if defined(VTARGET_USE_INTERNAL_REF)
			#undef  VTARGET_REF_VOLTS
			#define VTARGET_REF_VOLTS 2.56

			#define VTARGET_REF_MASK ADC_REFERENCE_INT2560MV
		#else
			#define VTARGET_REF_MASK ADC_REFERENCE_AVCC
		#endif

	/* Macros: */
		/** Programmer ID string, returned to the host during the CMD_SIGN_ON command processing. */
		#define PROGRAMMER_ID              "AVRISP_MK2"

		/** Timeout period for each issued command from the host before it is aborted (in 10ms ticks). */
		#define COMMAND_TIMEOUT_TICKS      100

		/** Command timeout ticks remaining counter, GPIOR for speed. */
		#define TimeoutTicksRemaining      GPIOR1

		/** MUX mask for the VTARGET ADC channel number. */
		#define VTARGET_ADC_CHANNEL_MASK   ADC_GET_CHANNEL_MASK(VTARGET_ADC_CHANNEL)

	/* External Variables: */
		extern uint32_t CurrentAddress;
		extern bool     MustLoadExtendedAddress;

	/* Function Prototypes: */
		void V2Protocol_Init(void);
		void V2Protocol_ProcessCommand(void);

		#if defined(INCLUDE_FROM_V2PROTOCOL_C)
			static void V2Protocol_UnknownCommand(const uint8_t V2Command);
			static void V2Protocol_SignOn(void);
			static void V2Protocol_GetSetParam(const uint8_t V2Command);
			static void V2Protocol_ResetProtection(void);
			static void V2Protocol_LoadAddress(void);
		#endif

#endif

