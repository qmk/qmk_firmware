/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief TWI Peripheral Driver (XMEGA)
 *
 *  On-chip TWI driver for the XMEGA Family of AVR microcontrollers.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the TWI driver
 *        dispatch header located in LUFA/Drivers/Peripheral/TWI.h.
 */

/** \ingroup Group_TWI
 *  \defgroup Group_TWI_XMEGA TWI Peripheral Driver (XMEGA)
 *
 *  \section Sec_TWI_XMEGA_ModDescription Module Description
 *  Master mode TWI driver for the 8-bit AVR microcontrollers which contain a hardware TWI module.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the TWI driver
 *        dispatch header located in LUFA/Drivers/Peripheral/TWI.h.
 *
 *  \section Sec_TWI_XMEGA_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  <b>Low Level API Example:</b>
 *  \code
 *      // Initialize the TWI driver before first use at 200KHz
 *      TWI_Init(&TWIC, TWI_BAUD_FROM_FREQ(200000));
 *
 *      // Start a write session to device at device address 0xA0, internal address 0xDC with a 10ms timeout
 *      if (TWI_StartTransmission(&TWIC, 0xA0 | TWI_ADDRESS_WRITE, 10) == TWI_ERROR_NoError)
 *      {
 *          TWI_SendByte(&TWIC, 0xDC);
 *
 *          TWI_SendByte(&TWIC, 0x01);
 *          TWI_SendByte(&TWIC, 0x02);
 *          TWI_SendByte(&TWIC, 0x03);
 *
 *          // Must stop transmission afterwards to release the bus
 *          TWI_StopTransmission(&TWIC);
 *      }
 *
 *      // Start a read session to device at address 0xA0, internal address 0xDC with a 10ms timeout
 *      if (TWI_StartTransmission(&TWIC, 0xA0 | TWI_ADDRESS_WRITE, 10) == TWI_ERROR_NoError)
 *      {
 *          TWI_SendByte(&TWIC, 0xDC);
 *          TWI_StopTransmission(&TWIC);
 *
 *          if (TWI_StartTransmission(&TWIC, 0xA0 | TWI_ADDRESS_READ, 10) == TWI_ERROR_NoError)
 *          {
 *              uint8_t Byte1, Byte2, Byte3;
 *
 *              // Read three bytes, acknowledge after the third byte is received
 *              TWI_ReceiveByte(&TWIC, &Byte1, false);
 *              TWI_ReceiveByte(&TWIC, &Byte2, false);
 *              TWI_ReceiveByte(&TWIC, &Byte3, true);
 *
 *              // Must stop transmission afterwards to release the bus
 *              TWI_StopTransmission(&TWIC);
 *          }
 *      }
 *  \endcode
 *
 *  <b>High Level API Example:</b>
 *  \code
 *      // Initialize the TWI driver before first use at 200KHz
 *      TWI_Init(&TWIC, TWI_BAUD_FROM_FREQ(200000));
 *
 *      // Start a write session to device at device address 0xA0, internal address 0xDC with a 10ms timeout
 *      uint8_t InternalWriteAddress = 0xDC;
 *      uint8_t WritePacket[3] = {0x01, 0x02, 0x03};
 *
 *      TWI_WritePacket(&TWIC, 0xA0, 10, &InternalWriteAddress, sizeof(InternalWriteAddress),
 *                      &WritePacket, sizeof(WritePacket);
 *
 *      // Start a read session to device at address 0xA0, internal address 0xDC with a 10ms timeout
 *      uint8_t InternalReadAddress = 0xDC;
 *      uint8_t ReadPacket[3];
 *
 *      TWI_ReadPacket(&TWIC, 0xA0, 10, &InternalReadAddress, sizeof(InternalReadAddress),
 *                     &ReadPacket, sizeof(ReadPacket);
 *  \endcode
 *
 *  @{
 */

#ifndef __TWI_XMEGA_H__
#define __TWI_XMEGA_H__

	/* Includes: */
		#include "../../../Common/Common.h"

		#include <stdio.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_TWI_H) && !defined(__INCLUDE_FROM_TWI_C)
			#error Do not include this file directly. Include LUFA/Drivers/Peripheral/TWI.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** TWI slave device address mask for a read session. Mask with a slave device base address to obtain
			 *  the correct TWI bus address for the slave device when reading data from it.
			 */
			#define TWI_ADDRESS_READ         0x01

			/** TWI slave device address mask for a write session. Mask with a slave device base address to obtain
			 *  the correct TWI bus address for the slave device when writing data to it.
			 */
			#define TWI_ADDRESS_WRITE        0x00

			/** Mask to retrieve the base address for a TWI device, which can then be ORed with \ref TWI_ADDRESS_READ
			 *  or \ref TWI_ADDRESS_WRITE to obtain the device's read and write address respectively.
			 */
			#define TWI_DEVICE_ADDRESS_MASK  0xFE

			/** Calculates the length of each bit on the TWI bus for a given target frequency. This may be used with
			 *  the \ref TWI_Init() function to convert a bus frequency to a number of clocks for the \c BitLength
			 *  parameter.
			 *
			 *  \param[in] Frequency  Desired TWI bus frequency in Hz.
			 *
			 *  \return Bit length in clocks for the given TWI bus frequency at the given prescaler value.
			 */
			#define TWI_BAUD_FROM_FREQ(Frequency) ((F_CPU / (2 * Frequency)) - 5)

		/* Enums: */
			/** Enum for the possible return codes of the TWI transfer start routine and other dependant TWI functions. */
			enum TWI_ErrorCodes_t
			{
				TWI_ERROR_NoError              = 0, /**< Indicates that the command completed successfully. */
				TWI_ERROR_BusFault             = 1, /**< A TWI bus fault occurred while attempting to capture the bus. */
				TWI_ERROR_BusCaptureTimeout    = 2, /**< A timeout occurred whilst waiting for the bus to be ready. */
				TWI_ERROR_SlaveResponseTimeout = 3, /**< No ACK received at the nominated slave address within the timeout period. */
				TWI_ERROR_SlaveNotReady        = 4, /**< Slave NAKed the TWI bus START condition. */
				TWI_ERROR_SlaveNAK             = 5, /**< Slave NAKed whilst attempting to send data to the device. */
			};

		/* Inline Functions: */
			/** Initializes the TWI hardware into master mode, ready for data transmission and reception. This must be
			 *  before any other TWI operations.
			 *
			 *  The generated SCL frequency will be according to the formula <pre>F_CPU / (2 * (5 + (BAUD)))</pre>.
			 *
			 *  \attention The value of the \c BitLength parameter should not be set below 10 or invalid bus conditions may
			 *             occur, as indicated in the XMEGA microcontroller datasheet.
			 *
			 *  \param[in] TWI   Pointer to the base of the TWI peripheral within the device.
			 *  \param[in] Baud  Value of the BAUD register of the TWI Master.
			 */
			static inline void TWI_Init(TWI_t* const TWI,
			                            const uint8_t Baud) ATTR_ALWAYS_INLINE ATTR_NON_NULL_PTR_ARG(1);
			static inline void TWI_Init(TWI_t* const TWI,
			                            const uint8_t Baud)
			{
				TWI->CTRL          = 0x00;
				TWI->MASTER.BAUD   = Baud;
				TWI->MASTER.CTRLA  = TWI_MASTER_ENABLE_bm;
				TWI->MASTER.CTRLB  = 0;
				TWI->MASTER.STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;
			}

			/** Turns off the TWI driver hardware. If this is called, any further TWI operations will require a call to
			 *  \ref TWI_Init() before the TWI can be used again.
	   		 *
			 *  \param[in] TWI  Pointer to the base of the TWI peripheral within the device.
			 */
			static inline void TWI_Disable(TWI_t* const TWI) ATTR_ALWAYS_INLINE ATTR_NON_NULL_PTR_ARG(1);
			static inline void TWI_Disable(TWI_t* const TWI)
			{
				TWI->MASTER.CTRLA &= ~TWI_MASTER_ENABLE_bm;
			}

			/** Sends a TWI STOP onto the TWI bus, terminating communication with the currently addressed device.
			 *
			 *  \param[in] TWI  Pointer to the base of the TWI peripheral within the device.
			 */
			static inline void TWI_StopTransmission(TWI_t* const TWI) ATTR_ALWAYS_INLINE ATTR_NON_NULL_PTR_ARG(1);
			static inline void TWI_StopTransmission(TWI_t* const TWI)
			{
				TWI->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
			}

		/* Function Prototypes: */
			/** Begins a master mode TWI bus communication with the given slave device address.
			 *
			 *  \param[in] TWI           Pointer to the base of the TWI peripheral within the device.
			 *  \param[in] SlaveAddress  Address of the slave TWI device to communicate with.
			 *  \param[in] TimeoutMS     Timeout period within which the slave must respond, in milliseconds.
			 *
			 *  \return A value from the \ref TWI_ErrorCodes_t enum.
			 */
			uint8_t TWI_StartTransmission(TWI_t* const TWI,
			                              const uint8_t SlaveAddress,
			                              const uint8_t TimeoutMS) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a byte to the currently addressed device on the TWI bus.
			 *
			 *  \param[in] TWI   Pointer to the base of the TWI peripheral within the device.
			 *  \param[in] Byte  Byte to send to the currently addressed device
			 *
			 *  \return Boolean \c true if the recipient ACKed the byte, \c false otherwise
			 */
			bool TWI_SendByte(TWI_t* const TWI,
			                  const uint8_t Byte) ATTR_NON_NULL_PTR_ARG(1);

			/** Receives a byte from the currently addressed device on the TWI bus.
			 *
			 *  \param[in] TWI       Pointer to the base of the TWI peripheral within the device.
			 *  \param[in] Byte      Location where the read byte is to be stored.
			 *  \param[in] LastByte  Indicates if the byte should be ACKed if false, NAKed if true.
			 *
			 *  \return Boolean \c true if the byte reception successfully completed, \c false otherwise.
			 */
			bool TWI_ReceiveByte(TWI_t* const TWI,
			                     uint8_t* const Byte,
			                     const bool LastByte) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** High level function to perform a complete packet transfer over the TWI bus to the specified
			 *  device.
			 *
			 *  \param[in] TWI                 Pointer to the base of the TWI peripheral within the device.
			 *  \param[in] SlaveAddress        Base address of the TWI slave device to communicate with.
			 *  \param[in] TimeoutMS           Timeout for bus capture and slave START ACK, in milliseconds.
			 *  \param[in] InternalAddress     Pointer to a location where the internal slave read start address is stored.
			 *  \param[in] InternalAddressLen  Size of the internal device address, in bytes.
			 *  \param[in] Buffer              Pointer to a buffer where the read packet data is to be stored.
			 *  \param[in] Length              Size of the packet to read, in bytes.
			 *
			 *  \return A value from the \ref TWI_ErrorCodes_t enum.
			 */
			uint8_t TWI_ReadPacket(TWI_t* const TWI,
			                       const uint8_t SlaveAddress,
			                       const uint8_t TimeoutMS,
			                       const uint8_t* InternalAddress,
			                       uint8_t InternalAddressLen,
			                       uint8_t* Buffer,
			                       uint8_t Length) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(4);

			/** High level function to perform a complete packet transfer over the TWI bus from the specified
			 *  device.
			 *
			 *  \param[in] TWI                 Pointer to the base of the TWI peripheral within the device.
			 *  \param[in] SlaveAddress        Base address of the TWI slave device to communicate with
			 *  \param[in] TimeoutMS           Timeout for bus capture and slave START ACK, in milliseconds
			 *  \param[in] InternalAddress     Pointer to a location where the internal slave write start address is stored
			 *  \param[in] InternalAddressLen  Size of the internal device address, in bytes
			 *  \param[in] Buffer              Pointer to a buffer where the packet data to send is stored
			 *  \param[in] Length              Size of the packet to send, in bytes
			 *
			 *  \return A value from the \ref TWI_ErrorCodes_t enum.
			 */
			uint8_t TWI_WritePacket(TWI_t* const TWI,
			                        const uint8_t SlaveAddress,
			                        const uint8_t TimeoutMS,
			                        const uint8_t* InternalAddress,
			                        uint8_t InternalAddressLen,
			                        const uint8_t* Buffer,
			                        uint8_t Length) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(4);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

