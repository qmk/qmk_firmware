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
 *  Master mode TWI driver for the AT90USB1287, AT90USB1286, AT90USB647, AT90USB646, ATMEGA16U4 and ATMEGA32U4 AVRs.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the TWI driver
 *        dispatch header located in LUFA/Drivers/Peripheral/TWI.h.
 */

/** \ingroup Group_TWI
 *  @defgroup Group_TWI_AVRU4U6U7 Series U4, U6 and U7 Model TWI Driver
 *
 *  Master mode TWI driver for the AT90USB1287, AT90USB1286, AT90USB647, AT90USB646, ATMEGA16U4 and ATMEGA32U4 AVRs.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the TWI driver
 *        dispatch header located in LUFA/Drivers/Peripheral/TWI.h.
 *
 *  @{
 */

#ifndef __TWI_AVRU4U6U7_H__
#define __TWI_AVRU4U6U7_H__

	/* Includes: */
		#include "../../../Common/Common.h"
		
		#include <avr/io.h>
		#include <stdbool.h>
		#include <util/twi.h>
		#include <util/delay.h>
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_TWI_H)
			#error Do not include this file directly. Include LUFA/Drivers/Peripheral/TWI.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Pseudo-Function Macros: */
			#if defined(__DOXYGEN__)
				/** Initializes the TWI hardware into master mode, ready for data transmission and reception. This must be
				 *  before any other TWI operations.
				 */
				static inline void TWI_Init(void);
				
				/** Turns off the TWI driver hardware. If this is called, any further TWI operations will require a call to
				 *  \ref TWI_Init() before the TWI can be used again.
				 */				
				static inline void TWI_ShutDown(void);
			#else
				#define TWI_Init()        MACROS{ TWCR |=  (1 << TWEN); }MACROE
				#define TWI_ShutDown()    MACROS{ TWCR &= ~(1 << TWEN); }MACROE
			#endif

		/* Inline Functions: */
			/** Sends a TWI STOP onto the TWI bus, terminating communication with the currently addressed device. */
			static inline void TWI_StopTransmission(void)
			{
				TWCR = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
			}

			/** Sends a byte to the currently addressed device on the TWI bus.
			 *
			 *  \param[in] Byte  Byte to send to the currently addressed device
			 *
			 *  \return Boolean true if the recipient ACKed the byte, false otherwise
			 */
			static inline bool TWI_SendByte(uint8_t Byte)
			{
				TWDR = Byte;
				TWCR = ((1 << TWINT) | (1 << TWEN));	
				while (!(TWCR & (1 << TWINT)));

				return ((TWSR & TW_STATUS_MASK) == TW_MT_DATA_ACK);
			}

			/** Receives a byte from the currently addressed device on the TWI bus.
			 *
			 *  \param[in] Byte  Location where the read byte is to be stored
			 *  \param[in] LastByte  Indicates if the byte should be ACKed if false, NAKed if true
			 *
			 *  \return Boolean true if the byte reception sucessfully completed, false otherwise
			 */
			static inline bool TWI_ReceiveByte(uint8_t* Byte, bool LastByte)
			{
				uint8_t TWCRMask = ((1 << TWINT) | (1 << TWEN));
				
				if (!(LastByte))
				  TWCRMask |= (1 << TWEA);

				TWCR = TWCRMask;
				while (!(TWCR & (1 << TWINT)));
				*Byte = TWDR;

				return ((TWSR & TW_STATUS_MASK) == TW_MR_DATA_ACK);
			}

		/* Function Prototypes: */
			/** Begins a master mode TWI bus communication with the given slave device address.
			 *
			 *  \param[in] SlaveAddress  Address of the slave TWI device to communicate with
			 *  \param[in] TimeoutMS     Timeout period within which the slave must respond, in milliseconds
			 *
			 *  \return Boolean true if the device is ready for data, false otherwise
			 */
			bool TWI_StartTransmission(uint8_t SlaveAddress, uint8_t TimeoutMS);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
