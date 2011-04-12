/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief USB Pipe definitions for the AVR8 microcontrollers.
 *  \copydetails Group_PipeManagement_AVR8
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_PipeRW
 *  \defgroup Group_PipeRW_AVR8 Pipe Data Reading and Writing (AVR8)
 *  \brief Pipe data read/write definitions for the Atmel AVR8 architecture.
 *
 *  Functions, macros, variables, enums and types related to data reading and writing from and to pipes.
 */

/** \ingroup Group_PipePrimitiveRW
 *  \defgroup Group_PipePrimitiveRW_AVR8 Read/Write of Primitive Data Types (AVR8)
 *  \brief Pipe primative data read/write definitions for the Atmel AVR8 architecture.
 *
 *  Functions, macros, variables, enums and types related to data reading and writing of primitive data types
 *  from and to pipes.
 */

/** \ingroup Group_PipePacketManagement
 *  \defgroup Group_PipePacketManagement_AVR8 Pipe Packet Management (AVR8)
 *  \brief Pipe packet management definitions for the Atmel AVR8 architecture.
 *
 *  Functions, macros, variables, enums and types related to packet management of pipes.
 */

/** \ingroup Group_PipeControlReq
 *  \defgroup Group_PipeControlReq_AVR8 Pipe Control Request Management (AVR8)
 *  \brief Pipe control request management definitions for the Atmel AVR8 architecture.
 *
 *  Module for host mode request processing. This module allows for the transmission of standard, class and
 *  vendor control requests to the default control endpoint of an attached device while in host mode.
 *
 *  \see Chapter 9 of the USB 2.0 specification.
 */

/** \ingroup Group_PipeManagement
 *  \defgroup Group_PipeManagement_AVR8 Pipe Management (AVR8)
 *  \brief Pipe management definitions for the Atmel AVR8 architecture.
 *
 *  This module contains functions, macros and enums related to pipe management when in USB Host mode. This
 *  module contains the pipe management macros, as well as pipe interrupt and data send/receive functions
 *  for various data types.
 *
 *  @{
 */

#ifndef __PIPE_AVR8_H__
#define __PIPE_AVR8_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include "../USBTask.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** \name Pipe Error Flag Masks */
			//@{
			/** Mask for \ref Pipe_GetErrorFlags(), indicating that an overflow error occurred in the pipe on the received data. */
			#define PIPE_ERRORFLAG_OVERFLOW         (1 << 6)

			/** Mask for \ref Pipe_GetErrorFlags(), indicating that an underflow error occurred in the pipe on the received data. */
			#define PIPE_ERRORFLAG_UNDERFLOW        (1 << 5)

			/** Mask for \ref Pipe_GetErrorFlags(), indicating that a CRC error occurred in the pipe on the received data. */
			#define PIPE_ERRORFLAG_CRC16            (1 << 4)

			/** Mask for \ref Pipe_GetErrorFlags(), indicating that a hardware timeout error occurred in the pipe. */
			#define PIPE_ERRORFLAG_TIMEOUT          (1 << 3)

			/** Mask for \ref Pipe_GetErrorFlags(), indicating that a hardware PID error occurred in the pipe. */
			#define PIPE_ERRORFLAG_PID              (1 << 2)

			/** Mask for \ref Pipe_GetErrorFlags(), indicating that a hardware data PID error occurred in the pipe. */
			#define PIPE_ERRORFLAG_DATAPID          (1 << 1)

			/** Mask for \ref Pipe_GetErrorFlags(), indicating that a hardware data toggle error occurred in the pipe. */
			#define PIPE_ERRORFLAG_DATATGL          (1 << 0)
			//@}

			/** \name Pipe Token Masks */
			//@{
			/** Token mask for \ref Pipe_ConfigurePipe(). This sets the pipe as a SETUP token (for CONTROL type pipes),
			 *  which will trigger a control request on the attached device when data is written to the pipe.
			 */
			#define PIPE_TOKEN_SETUP                (0 << PTOKEN0)

			/** Token mask for \ref Pipe_ConfigurePipe(). This sets the pipe as a IN token (for non-CONTROL type pipes),
			 *  indicating that the pipe data will flow from device to host.
			 */
			#define PIPE_TOKEN_IN                   (1 << PTOKEN0)

			/** Token mask for \ref Pipe_ConfigurePipe(). This sets the pipe as a OUT token (for non-CONTROL type pipes),
			 *  indicating that the pipe data will flow from host to device.
			 */
			#define PIPE_TOKEN_OUT                  (2 << PTOKEN0)
			//@}
			
			/** \name Pipe Bank Mode Masks */
			//@{
			/** Mask for the bank mode selection for the \ref Pipe_ConfigurePipe() macro. This indicates that the pipe
			 *  should have one single bank, which requires less USB FIFO memory but results in slower transfers as
			 *  only one USB device (the AVR or the attached device) can access the pipe's bank at the one time.
			 */
			#define PIPE_BANK_SINGLE                (0 << EPBK0)

			/** Mask for the bank mode selection for the \ref Pipe_ConfigurePipe() macro. This indicates that the pipe
			 *  should have two banks, which requires more USB FIFO memory but results in faster transfers as one
			 *  USB device (the AVR or the attached device) can access one bank while the other accesses the second
			 *  bank.
			 */
			#define PIPE_BANK_DOUBLE                (1 << EPBK0)
			//@}

			/** Default size of the default control pipe's bank, until altered by the Endpoint0Size value
			 *  in the device descriptor of the attached device.
			 */
			#define PIPE_CONTROLPIPE_DEFAULT_SIZE   64

			/** Total number of pipes (including the default control pipe at address 0) which may be used in
			 *  the device. Different USB AVR models support different amounts of pipes, this value reflects
			 *  the maximum number of pipes for the currently selected AVR model.
			 */
			#define PIPE_TOTAL_PIPES                7

			/** Size in bytes of the largest pipe bank size possible in the device. Not all banks on each AVR
			 *  model supports the largest bank size possible on the device; different pipe numbers support
			 *  different maximum bank sizes. This value reflects the largest possible bank of any pipe on the
			 *  currently selected USB AVR model.
			 */
			#define PIPE_MAX_SIZE                   256

		/* Enums: */
			/** Enum for the possible error return codes of the \ref Pipe_WaitUntilReady() function.
			 *
			 *  \ingroup Group_PipeRW_AVR8
			 */
			enum Pipe_WaitUntilReady_ErrorCodes_t
			{
				PIPE_READYWAIT_NoError                 = 0, /**< Pipe ready for next packet, no error. */
				PIPE_READYWAIT_PipeStalled             = 1,	/**< The device stalled the pipe while waiting. */
				PIPE_READYWAIT_DeviceDisconnected      = 2,	/**< Device was disconnected from the host while waiting. */
				PIPE_READYWAIT_Timeout                 = 3, /**< The device failed to accept or send the next packet
				                                             *   within the software timeout period set by the
				                                             *   \ref USB_STREAM_TIMEOUT_MS macro.
				                                             */
			};

		/* Inline Functions: */
			/** Indicates the number of bytes currently stored in the current pipes's selected bank.
			 *
			 *  \note The return width of this function may differ, depending on the maximum pipe bank size
			 *        of the selected AVR model.
			 *
			 *  \ingroup Group_PipeRW_AVR8
			 *
			 *  \return Total number of bytes in the currently selected pipe's FIFO buffer.
			 */
			static inline uint16_t Pipe_BytesInPipe(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint16_t Pipe_BytesInPipe(void)
			{
				return UPBCX;
			}

			/** Returns the pipe address of the currently selected pipe. This is typically used to save the
			 *  currently selected pipe number so that it can be restored after another pipe has been manipulated.
			 *
			 *  \return Index of the currently selected pipe.
			 */
			static inline uint8_t Pipe_GetCurrentPipe(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint8_t Pipe_GetCurrentPipe(void)
			{
				return (UPNUM & PIPE_PIPENUM_MASK);
			}

			/** Selects the given pipe number. Any pipe operations which do not require the pipe number to be
			 *  indicated will operate on the currently selected pipe.
			 *
			 *  \param[in] PipeNumber  Index of the pipe to select.
			 */
			static inline void Pipe_SelectPipe(const uint8_t PipeNumber) ATTR_ALWAYS_INLINE;
			static inline void Pipe_SelectPipe(const uint8_t PipeNumber)
			{
				UPNUM = PipeNumber;
			}

			/** Resets the desired pipe, including the pipe banks and flags.
			 *
			 *  \param[in] PipeNumber  Index of the pipe to reset.
			 */
			static inline void Pipe_ResetPipe(const uint8_t PipeNumber) ATTR_ALWAYS_INLINE;
			static inline void Pipe_ResetPipe(const uint8_t PipeNumber)
			{
				UPRST = (1 << PipeNumber);
				UPRST = 0;
			}

			/** Enables the currently selected pipe so that data can be sent and received through it to and from
			 *  an attached device.
			 *
			 *  \pre The currently selected pipe must first be configured properly via \ref Pipe_ConfigurePipe().
			 */
			static inline void Pipe_EnablePipe(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_EnablePipe(void)
			{
				UPCONX |= (1 << PEN);
			}

			/** Disables the currently selected pipe so that data cannot be sent and received through it to and
			 *  from an attached device.
			 */
			static inline void Pipe_DisablePipe(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_DisablePipe(void)
			{
				UPCONX &= ~(1 << PEN);
			}

			/** Determines if the currently selected pipe is enabled, but not necessarily configured.
			 *
			 * \return Boolean \c true if the currently selected pipe is enabled, \c false otherwise.
			 */
			static inline bool Pipe_IsEnabled(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_IsEnabled(void)
			{
				return ((UPCONX & (1 << PEN)) ? true : false);
			}

			/** Gets the current pipe token, indicating the pipe's data direction and type.
			 *
			 *  \return The current pipe token, as a \c PIPE_TOKEN_* mask.
			 */
			static inline uint8_t Pipe_GetPipeToken(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint8_t Pipe_GetPipeToken(void)
			{
				return (UPCFG0X & (0x03 << PTOKEN0));
			}

			/** Sets the token for the currently selected pipe to one of the tokens specified by the \c PIPE_TOKEN_*
			 *  masks. This can be used on CONTROL type pipes, to allow for bidirectional transfer of data during
			 *  control requests, or on regular pipes to allow for half-duplex bidirectional data transfer to devices
			 *  which have two endpoints of opposite direction sharing the same endpoint address within the device.
			 *
			 *  \param[in] Token  New pipe token to set the selected pipe to, as a \c PIPE_TOKEN_* mask.
			 */
			static inline void Pipe_SetPipeToken(const uint8_t Token) ATTR_ALWAYS_INLINE;
			static inline void Pipe_SetPipeToken(const uint8_t Token)
			{
				UPCFG0X = ((UPCFG0X & ~(0x03 << PTOKEN0)) | Token);
			}

			/** Configures the currently selected pipe to allow for an unlimited number of IN requests. */
			static inline void Pipe_SetInfiniteINRequests(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_SetInfiniteINRequests(void)
			{
				UPCONX |= (1 << INMODE);
			}

			/** Configures the currently selected pipe to only allow the specified number of IN requests to be
			 *  accepted by the pipe before it is automatically frozen.
			 *
			 *  \param[in] TotalINRequests  Total number of IN requests that the pipe may receive before freezing.
			 */
			static inline void Pipe_SetFiniteINRequests(const uint8_t TotalINRequests) ATTR_ALWAYS_INLINE;
			static inline void Pipe_SetFiniteINRequests(const uint8_t TotalINRequests)
			{
				UPCONX &= ~(1 << INMODE);
				UPINRQX = TotalINRequests;
			}

			/** Determines if the currently selected pipe is configured.
			 *
			 *  \return Boolean \c true if the selected pipe is configured, \c false otherwise.
			 */
			static inline bool Pipe_IsConfigured(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_IsConfigured(void)
			{
				return ((UPSTAX & (1 << CFGOK)) ? true : false);
			}

			/** Retrieves the endpoint number of the endpoint within the attached device that the currently selected
			 *  pipe is bound to.
			 *
			 *  \return Endpoint number the currently selected pipe is bound to.
			 */
			static inline uint8_t Pipe_BoundEndpointNumber(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint8_t Pipe_BoundEndpointNumber(void)
			{
				return ((UPCFG0X >> PEPNUM0) & PIPE_EPNUM_MASK);
			}

			/** Sets the period between interrupts for an INTERRUPT type pipe to a specified number of milliseconds.
			 *
			 *  \param[in] Milliseconds  Number of milliseconds between each pipe poll.
			 */
			static inline void Pipe_SetInterruptPeriod(const uint8_t Milliseconds) ATTR_ALWAYS_INLINE;
			static inline void Pipe_SetInterruptPeriod(const uint8_t Milliseconds)
			{
				UPCFG2X = Milliseconds;
			}

			/** Returns a mask indicating which pipe's interrupt periods have elapsed, indicating that the pipe should
			 *  be serviced.
			 *
			 *  \return Mask whose bits indicate which pipes have interrupted.
			 */
			static inline uint8_t Pipe_GetPipeInterrupts(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint8_t Pipe_GetPipeInterrupts(void)
			{
				return UPINT;
			}

			/** Determines if the specified pipe number has interrupted (valid only for INTERRUPT type
			 *  pipes).
			 *
			 *  \param[in] PipeNumber  Index of the pipe whose interrupt flag should be tested.
			 *
			 *  \return Boolean \c true if the specified pipe has interrupted, \c false otherwise.
			 */
			static inline bool Pipe_HasPipeInterrupted(const uint8_t PipeNumber) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_HasPipeInterrupted(const uint8_t PipeNumber)
			{
				return ((UPINT & (1 << PipeNumber)) ? true : false);
			}

			/** Unfreezes the selected pipe, allowing it to communicate with an attached device. */
			static inline void Pipe_Unfreeze(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_Unfreeze(void)
			{
				UPCONX &= ~(1 << PFREEZE);
			}

			/** Freezes the selected pipe, preventing it from communicating with an attached device. */
			static inline void Pipe_Freeze(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_Freeze(void)
			{
				UPCONX |= (1 << PFREEZE);
			}

			/** Determines if the currently selected pipe is frozen, and not able to accept data.
			 *
			 *  \return Boolean \c true if the currently selected pipe is frozen, \c false otherwise.
			 */
			static inline bool Pipe_IsFrozen(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_IsFrozen(void)
			{
				return ((UPCONX & (1 << PFREEZE)) ? true : false);
			}

			/** Clears the error flags for the currently selected pipe. */
			static inline void Pipe_ClearError(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_ClearError(void)
			{
				UPERRX = 0;
				UPINTX &= ~(1 << PERRI);
			}

			/** Determines if the master pipe error flag is set for the currently selected pipe, indicating that
			 *  some sort of hardware error has occurred on the pipe.
			 *
			 *  \see \ref Pipe_GetErrorFlags() macro for information on retrieving the exact error flag.
			 *
			 *  \return Boolean \c true if an error has occurred on the selected pipe, \c false otherwise.
			 */
			static inline bool Pipe_IsError(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_IsError(void)
			{
				return ((UPINTX & (1 << PERRI)) ? true : false);
			}

			/** Gets a mask of the hardware error flags which have occurred on the currently selected pipe. This
			 *  value can then be masked against the \c PIPE_ERRORFLAG_* masks to determine what error has occurred.
			 *
			 *  \return  Mask comprising of \c PIPE_ERRORFLAG_* bits indicating what error has occurred on the selected pipe.
			 */
			static inline uint8_t Pipe_GetErrorFlags(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint8_t Pipe_GetErrorFlags(void)
			{
				return ((UPERRX & (PIPE_ERRORFLAG_CRC16 | PIPE_ERRORFLAG_TIMEOUT |
				                   PIPE_ERRORFLAG_PID   | PIPE_ERRORFLAG_DATAPID |
				                   PIPE_ERRORFLAG_DATATGL)) |
				        (UPSTAX & (PIPE_ERRORFLAG_OVERFLOW | PIPE_ERRORFLAG_UNDERFLOW)));
			}
			
			/** Retrieves the number of busy banks in the currently selected pipe, which have been queued for
			 *  transmission via the \ref Pipe_ClearOUT() command, or are awaiting acknowledgement via the
			 *  \ref Pipe_ClearIN() command.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 *
			 *  \return Total number of busy banks in the selected pipe.
			 */
			static inline uint8_t Pipe_GetBusyBanks(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint8_t Pipe_GetBusyBanks(void)
			{
				return (UPSTAX & (0x03 << NBUSYBK0));
			}

			/** Determines if the currently selected pipe may be read from (if data is waiting in the pipe
			 *  bank and the pipe is an IN direction, or if the bank is not yet full if the pipe is an OUT
			 *  direction). This function will return false if an error has occurred in the pipe, or if the pipe
			 *  is an IN direction and no packet (or an empty packet) has been received, or if the pipe is an OUT
			 *  direction and the pipe bank is full.
			 *
			 *  \note This function is not valid on CONTROL type pipes.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 *
			 *  \return Boolean \c true if the currently selected pipe may be read from or written to, depending
			 *          on its direction.
			 */
			static inline bool Pipe_IsReadWriteAllowed(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_IsReadWriteAllowed(void)
			{
				return ((UPINTX & (1 << RWAL)) ? true : false);
			}

			/** Determines if a packet has been received on the currently selected IN pipe from the attached device.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 *
			 *  \return Boolean \c true if the current pipe has received an IN packet, \c false otherwise.
			 */
			static inline bool Pipe_IsINReceived(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_IsINReceived(void)
			{
				return ((UPINTX & (1 << RXINI)) ? true : false);
			}

			/** Determines if the currently selected OUT pipe is ready to send an OUT packet to the attached device.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 *
			 *  \return Boolean \c true if the current pipe is ready for an OUT packet, \c false otherwise.
			 */
			static inline bool Pipe_IsOUTReady(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_IsOUTReady(void)
			{
				return ((UPINTX & (1 << TXOUTI)) ? true : false);
			}

			/** Determines if no SETUP request is currently being sent to the attached device on the selected
			 *  CONTROL type pipe.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 *
			 *  \return Boolean \c true if the current pipe is ready for a SETUP packet, \c false otherwise.
			 */
			static inline bool Pipe_IsSETUPSent(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_IsSETUPSent(void)
			{
				return ((UPINTX & (1 << TXSTPI)) ? true : false);
			}

			/** Sends the currently selected CONTROL type pipe's contents to the device as a SETUP packet.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 */
			static inline void Pipe_ClearSETUP(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_ClearSETUP(void)
			{
				UPINTX &= ~((1 << TXSTPI) | (1 << FIFOCON));
			}

			/** Acknowledges the reception of a setup IN request from the attached device on the currently selected
			 *  pipe, freeing the bank ready for the next packet.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 */
			static inline void Pipe_ClearIN(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_ClearIN(void)
			{
				UPINTX &= ~((1 << RXINI) | (1 << FIFOCON));
			}

			/** Sends the currently selected pipe's contents to the device as an OUT packet on the selected pipe, freeing
			 *  the bank ready for the next packet.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 */
			static inline void Pipe_ClearOUT(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_ClearOUT(void)
			{
				UPINTX &= ~((1 << TXOUTI) | (1 << FIFOCON));
			}

			/** Determines if the device sent a NAK (Negative Acknowledge) in response to the last sent packet on
			 *  the currently selected pipe. This occurs when the host sends a packet to the device, but the device
			 *  is not currently ready to handle the packet (i.e. its endpoint banks are full). Once a NAK has been
			 *  received, it must be cleared using \ref Pipe_ClearNAKReceived() before the previous (or any other) packet
			 *  can be re-sent.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 *
			 *  \return Boolean \c true if an NAK has been received on the current pipe, \c false otherwise.
			 */
			static inline bool Pipe_IsNAKReceived(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_IsNAKReceived(void)
			{
				return ((UPINTX & (1 << NAKEDI)) ? true : false);
			}

			/** Clears the NAK condition on the currently selected pipe.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 *
			 *  \see \ref Pipe_IsNAKReceived() for more details.
			 */
			static inline void Pipe_ClearNAKReceived(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_ClearNAKReceived(void)
			{
				UPINTX &= ~(1 << NAKEDI);
			}

			/** Determines if the currently selected pipe has had the STALL condition set by the attached device.
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 *
			 *  \return Boolean \c true if the current pipe has been stalled by the attached device, \c false otherwise.
			 */
			static inline bool Pipe_IsStalled(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool Pipe_IsStalled(void)
			{
				return ((UPINTX & (1 << RXSTALLI)) ? true : false);
			}

			/** Clears the STALL condition detection flag on the currently selected pipe, but does not clear the
			 *  STALL condition itself (this must be done via a ClearFeature control request to the device).
			 *
			 *  \ingroup Group_PipePacketManagement_AVR8
			 */
			static inline void Pipe_ClearStall(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_ClearStall(void)
			{
				UPINTX &= ~(1 << RXSTALLI);
			}

			/** Reads one byte from the currently selected pipe's bank, for OUT direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 *
			 *  \return Next byte in the currently selected pipe's FIFO buffer.
			 */
			static inline uint8_t Pipe_Read_8(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint8_t Pipe_Read_8(void)
			{
				return UPDATX;
			}

			/** Writes one byte from the currently selected pipe's bank, for IN direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 *
			 *  \param[in] Data  Data to write into the the currently selected pipe's FIFO buffer.
			 */
			static inline void Pipe_Write_8(const uint8_t Data) ATTR_ALWAYS_INLINE;
			static inline void Pipe_Write_8(const uint8_t Data)
			{
				UPDATX = Data;
			}

			/** Discards one byte from the currently selected pipe's bank, for OUT direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 */
			static inline void Pipe_Discard_8(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_Discard_8(void)
			{
				uint8_t Dummy;

				Dummy = UPDATX;
			}

			/** Reads two bytes from the currently selected pipe's bank in little endian format, for OUT
			 *  direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 *
			 *  \return Next two bytes in the currently selected pipe's FIFO buffer.
			 */
			static inline uint16_t Pipe_Read_16_LE(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint16_t Pipe_Read_16_LE(void)
			{
				union
				{
					uint16_t Value;
					uint8_t  Bytes[2];
				} Data;

				Data.Bytes[0] = UPDATX;
				Data.Bytes[1] = UPDATX;

				return Data.Value;
			}

			/** Reads two bytes from the currently selected pipe's bank in big endian format, for OUT
			 *  direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 *
			 *  \return Next two bytes in the currently selected pipe's FIFO buffer.
			 */
			static inline uint16_t Pipe_Read_16_BE(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint16_t Pipe_Read_16_BE(void)
			{
				union
				{
					uint16_t Value;
					uint8_t  Bytes[2];
				} Data;

				Data.Bytes[1] = UPDATX;
				Data.Bytes[0] = UPDATX;

				return Data.Value;
			}

			/** Writes two bytes to the currently selected pipe's bank in little endian format, for IN
			 *  direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 *
			 *  \param[in] Data  Data to write to the currently selected pipe's FIFO buffer.
			 */
			static inline void Pipe_Write_16_LE(const uint16_t Data) ATTR_ALWAYS_INLINE;
			static inline void Pipe_Write_16_LE(const uint16_t Data)
			{
				UPDATX = (Data & 0xFF);
				UPDATX = (Data >> 8);
			}

			/** Writes two bytes to the currently selected pipe's bank in big endian format, for IN
			 *  direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 *
			 *  \param[in] Data  Data to write to the currently selected pipe's FIFO buffer.
			 */
			static inline void Pipe_Write_16_BE(const uint16_t Data) ATTR_ALWAYS_INLINE;
			static inline void Pipe_Write_16_BE(const uint16_t Data)
			{
				UPDATX = (Data >> 8);
				UPDATX = (Data & 0xFF);
			}

			/** Discards two bytes from the currently selected pipe's bank, for OUT direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 */
			static inline void Pipe_Discard_16(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_Discard_16(void)
			{
				uint8_t Dummy;

				Dummy = UPDATX;
				Dummy = UPDATX;
			}

			/** Reads four bytes from the currently selected pipe's bank in little endian format, for OUT
			 *  direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 *
			 *  \return Next four bytes in the currently selected pipe's FIFO buffer.
			 */
			static inline uint32_t Pipe_Read_32_LE(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint32_t Pipe_Read_32_LE(void)
			{
				union
				{
					uint32_t Value;
					uint8_t  Bytes[4];
				} Data;

				Data.Bytes[0] = UPDATX;
				Data.Bytes[1] = UPDATX;
				Data.Bytes[2] = UPDATX;
				Data.Bytes[3] = UPDATX;

				return Data.Value;
			}

			/** Reads four bytes from the currently selected pipe's bank in big endian format, for OUT
			 *  direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 *
			 *  \return Next four bytes in the currently selected pipe's FIFO buffer.
			 */
			static inline uint32_t Pipe_Read_32_BE(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint32_t Pipe_Read_32_BE(void)
			{
				union
				{
					uint32_t DWord;
					uint8_t  Bytes[4];
				} Data;

				Data.Bytes[3] = UPDATX;
				Data.Bytes[2] = UPDATX;
				Data.Bytes[1] = UPDATX;
				Data.Bytes[0] = UPDATX;

				return Data.DWord;
			}

			/** Writes four bytes to the currently selected pipe's bank in little endian format, for IN
			 *  direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 *
			 *  \param[in] Data  Data to write to the currently selected pipe's FIFO buffer.
			 */
			static inline void Pipe_Write_32_LE(const uint32_t Data) ATTR_ALWAYS_INLINE;
			static inline void Pipe_Write_32_LE(const uint32_t Data)
			{
				UPDATX = (Data &  0xFF);
				UPDATX = (Data >> 8);
				UPDATX = (Data >> 16);
				UPDATX = (Data >> 24);
			}

			/** Writes four bytes to the currently selected pipe's bank in big endian format, for IN
			 *  direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 *
			 *  \param[in] Data  Data to write to the currently selected pipe's FIFO buffer.
			 */
			static inline void Pipe_Write_32_BE(const uint32_t Data) ATTR_ALWAYS_INLINE;
			static inline void Pipe_Write_32_BE(const uint32_t Data)
			{
				UPDATX = (Data >> 24);
				UPDATX = (Data >> 16);
				UPDATX = (Data >> 8);
				UPDATX = (Data &  0xFF);
			}

			/** Discards four bytes from the currently selected pipe's bank, for OUT direction pipes.
			 *
			 *  \ingroup Group_PipePrimitiveRW_AVR8
			 */
			static inline void Pipe_Discard_32(void) ATTR_ALWAYS_INLINE;
			static inline void Pipe_Discard_32(void)
			{
				uint8_t Dummy;

				Dummy = UPDATX;
				Dummy = UPDATX;
				Dummy = UPDATX;
				Dummy = UPDATX;
			}

		/* External Variables: */
			/** Global indicating the maximum packet size of the default control pipe located at address
			 *  0 in the device. This value is set to the value indicated in the attached device's device
		     *  descriptor once the USB interface is initialized into host mode and a device is attached
			 *  to the USB bus.
			 *
			 *  \note This variable should be treated as read-only in the user application, and never manually
			 *        changed in value.
			 */
			extern uint8_t USB_ControlPipeSize;

		/* Function Prototypes: */
			/** Configures the specified pipe number with the given pipe type, token, target endpoint number in the
			 *  attached device, bank size and banking mode.
			 *
			 *  A newly configured pipe is frozen by default, and must be unfrozen before use via the \ref Pipe_Unfreeze()
			 *  before being used. Pipes should be kept frozen unless waiting for data from a device while in IN mode, or
			 *  sending data to the device in OUT mode. IN type pipes are also automatically configured to accept infinite
			 *  numbers of IN requests without automatic freezing - this can be overridden by a call to
			 *  \ref Pipe_SetFiniteINRequests().
			 *
			 *  \param[in] Number          Pipe number to configure. This must be more than 0 and less than \ref PIPE_TOTAL_PIPES.
			 *
			 *  \param[in] Type            Type of pipe to configure, an \c EP_TYPE_* mask. Not all pipe types are available on Low
			 *                             Speed USB devices - refer to the USB 2.0 specification.
			 *
			 *  \param[in] Token           Pipe data token, either \ref PIPE_TOKEN_SETUP, \ref PIPE_TOKEN_OUT or \ref PIPE_TOKEN_IN.
			 *                             All pipes (except Control type) are unidirectional - data may only be read from or
			 *                             written to the pipe bank based on its direction, not both.
			 *
			 *  \param[in] EndpointNumber  Endpoint index within the attached device that the pipe should interface to.
			 *
			 *  \param[in] Size            Size of the pipe's bank, where packets are stored before they are transmitted to
			 *                             the USB device, or after they have been received from the USB device (depending on
			 *                             the pipe's data direction). The bank size must indicate the maximum packet size that
			 *                             the pipe can handle.
			 *
			 *  \param[in] Banks           Number of banks to use for the pipe being configured, a \c PIPE_BANK_* mask. More banks
			 *                             uses more USB DPRAM, but offers better performance. Isochronous type pipes <b>must</b>
			 *                             have at least two banks.
			 *
			 *  \note When the \c ORDERED_EP_CONFIG compile time option is used, Pipes <b>must</b> be configured in ascending order,
			 *        or bank corruption will occur.
			 *        \n\n
			 *
			 *  \note Certain microcontroller model's pipes may have different maximum packet sizes based on the pipe's
			 *        index - refer to the chosen microcontroller's datasheet to determine the maximum bank size for each pipe.
			 *        \n\n
			 *
			 *  \note The default control pipe should not be manually configured by the user application, as it is
			 *        automatically configured by the library internally.
			 *        \n\n
			 *
			 *  \note This routine will automatically select the specified pipe upon success. Upon failure, the pipe which
			 *        failed to reconfigure correctly will be selected.
			 *
			 *  \return Boolean \c true if the configuration succeeded, \c false otherwise.
			 */
			bool Pipe_ConfigurePipe(const uint8_t Number,
			                        const uint8_t Type,
			                        const uint8_t Token,
			                        const uint8_t EndpointNumber,
			                        const uint16_t Size,
			                        const uint8_t Banks);

			/** Spin-loops until the currently selected non-control pipe is ready for the next packed of data to be read
			 *  or written to it, aborting in the case of an error condition (such as a timeout or device disconnect).
			 *
			 *  \ingroup Group_PipeRW_AVR8
			 *
			 *  \return A value from the \ref Pipe_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t Pipe_WaitUntilReady(void);

			/** Determines if a pipe has been bound to the given device endpoint address. If a pipe which is bound to the given
			 *  endpoint is found, it is automatically selected.
			 *
			 *  \param[in] EndpointAddress Address and direction mask of the endpoint within the attached device to check.
			 *
			 *  \return Boolean \c true if a pipe bound to the given endpoint address of the specified direction is found,
			 *          \c false otherwise.
			 */
			bool Pipe_IsEndpointBound(const uint8_t EndpointAddress);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#if !defined(ENDPOINT_CONTROLEP)
				#define ENDPOINT_CONTROLEP          0
			#endif

		/* Inline Functions: */
			static inline uint8_t Pipe_BytesToEPSizeMask(const uint16_t Bytes) ATTR_WARN_UNUSED_RESULT ATTR_CONST ATTR_ALWAYS_INLINE;
			static inline uint8_t Pipe_BytesToEPSizeMask(const uint16_t Bytes)
			{
				uint8_t  MaskVal    = 0;
				uint16_t CheckBytes = 8;

				while ((CheckBytes < Bytes) && (CheckBytes < PIPE_MAX_SIZE))
				{
					MaskVal++;
					CheckBytes <<= 1;
				}

				return (MaskVal << EPSIZE0);
			}

		/* Function Prototypes: */
			void Pipe_ClearPipes(void);
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

