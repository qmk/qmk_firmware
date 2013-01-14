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
 *  Header file for ISPTarget.c.
 */

#ifndef _ISP_TARGET_
#define _ISP_TARGET_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>
		#include <util/delay.h>

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Peripheral/SPI.h>

		#include "../V2Protocol.h"
		#include "ISPProtocol.h"
		#include "Config/AppConfig.h"

	/* Preprocessor Checks: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#undef ENABLE_ISP_PROTOCOL

			#if !defined(ENABLE_XPROG_PROTOCOL)
				#define ENABLE_XPROG_PROTOCOL
			#endif
		#endif

	/* Macros: */
		/** Low level device command to issue an extended FLASH address, for devices with over 128KB of FLASH. */
		#define LOAD_EXTENDED_ADDRESS_CMD     0x4D

		/** Macro to convert an ISP frequency to a number of timer clock cycles for the software SPI driver. */
		#define TIMER_COMP(freq)              (((F_CPU / 8) / 2 / freq) - 1)

		/** ISP rescue clock speed in Hz, for clocking targets with incorrectly set fuses. */
		#define ISP_RESCUE_CLOCK_SPEED        4000000

	/* External Variables: */
		extern bool HardwareSPIMode;

	/* Function Prototypes: */
		void    ISPTarget_EnableTargetISP(void);
		void    ISPTarget_DisableTargetISP(void);
		void    ISPTarget_ConfigureRescueClock(void);
		void    ISPTarget_ConfigureSoftwareSPI(const uint8_t SCKDuration);
		uint8_t ISPTarget_TransferSoftSPIByte(const uint8_t Byte);
		void    ISPTarget_ChangeTargetResetLine(const bool ResetTarget);
		uint8_t ISPTarget_WaitWhileTargetBusy(void);
		void    ISPTarget_LoadExtendedAddress(void);
		uint8_t ISPTarget_WaitForProgComplete(const uint8_t ProgrammingMode,
		                                      const uint16_t PollAddress,
		                                      const uint8_t PollValue,
		                                      const uint8_t DelayMS,
		                                      const uint8_t ReadMemCommand);

	/* Inline Functions: */
		/** Sends a byte of ISP data to the attached target, using the appropriate SPI hardware or
		 *  software routines depending on the selected ISP speed.
		 *
		 *  \param[in] Byte  Byte of data to send to the attached target
		 */
		static inline void ISPTarget_SendByte(const uint8_t Byte)
		{
			if (HardwareSPIMode)
			  SPI_SendByte(Byte);
			else
			  ISPTarget_TransferSoftSPIByte(Byte);
		}

		/** Receives a byte of ISP data from the attached target, using the appropriate
		 *  SPI hardware or software routines depending on the selected ISP speed.
		 *
		 *  \return Received byte of data from the attached target
		 */
		static inline uint8_t ISPTarget_ReceiveByte(void)
		{
			uint8_t ReceivedByte;

			if (HardwareSPIMode)
			  ReceivedByte = SPI_ReceiveByte();
			else
			  ReceivedByte = ISPTarget_TransferSoftSPIByte(0x00);

			#if defined(INVERTED_ISP_MISO)
			return ~ReceivedByte;
			#else
			return  ReceivedByte;
			#endif
		}

		/** Sends and receives a byte of ISP data to and from the attached target, using the
		 *  appropriate SPI hardware or software routines depending on the selected ISP speed.
		 *
		 *  \param[in] Byte  Byte of data to send to the attached target
		 *
		 *  \return Received byte of data from the attached target
		 */
		static inline uint8_t ISPTarget_TransferByte(const uint8_t Byte)
		{
			uint8_t ReceivedByte;

			if (HardwareSPIMode)
			  ReceivedByte = SPI_TransferByte(Byte);
			else
			  ReceivedByte = ISPTarget_TransferSoftSPIByte(Byte);

			#if defined(INVERTED_ISP_MISO)
			return ~ReceivedByte;
			#else
			return  ReceivedByte;
			#endif
		}

#endif

