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

/** \file
 *
 *  Functions, macros and enums related to endpoint management when in USB Device mode. This
 *  module contains the endpoint management macros, as well as endpoint interrupt and data
 *  send/recieve functions for various data types.
 */

/** \ingroup Group_USB
 *  @defgroup Group_EndpointManagement Endpoint Management
 *
 *  Functions, macros, variables, enums and types related to the setup and management of endpoints while in USB Device mode.
 *
 *  @{
 */

/** @defgroup Group_EndpointRW Endpoint Data Reading and Writing
 *
 *  Functions, macros, variables, enums and types related to data reading and writing from and to endpoints.
 */
 
/** @defgroup Group_EndpointPacketManagement Endpoint Packet Management
 *
 *  Functions, macros, variables, enums and types related to packet management of endpoints.
 */

#ifndef __ENDPOINT_H__
#define __ENDPOINT_H__

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>

		#include "../../../Common/Common.h"
		#include "../HighLevel/USBTask.h"

		#if !defined(NO_STREAM_CALLBACKS) || defined(__DOXYGEN__)
			#include "../HighLevel/StreamCallbacks.h"
		#endif
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Endpoint data direction mask for Endpoint_ConfigureEndpoint(). This indicates that the endpoint
			 *  should be initialized in the OUT direction - i.e. data flows from host to device.
			 */
			#define ENDPOINT_DIR_OUT                      (0 << EPDIR)

			/** Endpoint data direction mask for Endpoint_ConfigureEndpoint(). This indicates that the endpoint
			 *  should be initialized in the IN direction - i.e. data flows from device to host.
			 */
			#define ENDPOINT_DIR_IN                       (1 << EPDIR)

			/** Mask for the bank mode selection for the Endpoint_ConfigureEndpoint() macro. This indicates
			 *  that the endpoint should have one single bank, which requires less USB FIFO memory but results
			 *  in slower transfers as only one USB device (the AVR or the host) can access the endpoint's
			 *  bank at the one time.
			 */
			#define ENDPOINT_BANK_SINGLE                  (0 << EPBK0)

			/** Mask for the bank mode selection for the Endpoint_ConfigureEndpoint() macro. This indicates
			 *  that the endpoint should have two banks, which requires more USB FIFO memory but results
			 *  in faster transfers as one USB device (the AVR or the host) can access one bank while the other
			 *  accesses the second bank.
			 */
			#define ENDPOINT_BANK_DOUBLE                  (1 << EPBK0)
			
			/** Endpoint address for the default control endpoint, which always resides in address 0. This is
			 *  defined for convenience to give more readable code when used with the endpoint macros.
			 */
			#define ENDPOINT_CONTROLEP                    0

			#if (!defined(FIXED_CONTROL_ENDPOINT_SIZE) || defined(__DOXYGEN__))
				/** Default size of the default control endpoint's bank, until altered by the Endpoint0Size value 
				 *  in the device descriptor. Not available if the FIXED_CONTROL_ENDPOINT_SIZE token is defined.
				 */
				#define ENDPOINT_CONTROLEP_DEFAULT_SIZE   8
			#endif
			
			/** Endpoint number mask, for masking against endpoint addresses to retrieve the endpoint's
			 *  numerical address in the device.
			 */
			#define ENDPOINT_EPNUM_MASK                   0x03

			/** Endpoint bank size mask, for masking against endpoint addresses to retrieve the endpoint's
			 *  bank size in the device.
			 */
			#define ENDPOINT_EPSIZE_MASK                  0x7FF
			
			/** Maximum size in bytes of a given endpoint.
			 *
			 *  \param n  Endpoint number, a value between 0 and (ENDPOINT_TOTAL_ENDPOINTS - 1)
			 */				
			#define ENDPOINT_MAX_SIZE(n)                  _ENDPOINT_GET_MAXSIZE(n)

			/** Indicates if the given endpoint supports double banking.
			 *
			 *  \param n  Endpoint number, a value between 0 and (ENDPOINT_TOTAL_ENDPOINTS - 1)
			 */				
			#define ENDPOINT_DOUBLEBANK_SUPPORTED(n)      _ENDPOINT_GET_DOUBLEBANK(n)

			#if defined(USB_FULL_CONTROLLER) || defined(USB_MODIFIED_FULL_CONTROLLER) || defined(__DOXYGEN__)
				/** Total number of endpoints (including the default control endpoint at address 0) which may
				 *  be used in the device. Different USB AVR models support different amounts of endpoints,
				 *  this value reflects the maximum number of endpoints for the currently selected AVR model.
				 */
				#define ENDPOINT_TOTAL_ENDPOINTS          7
			#else
				#define ENDPOINT_TOTAL_ENDPOINTS          5			
			#endif

			/** Interrupt definition for the endpoint SETUP interrupt (for CONTROL type endpoints). Should be
			 *  used with the USB_INT_* macros located in USBInterrupt.h.
			 *
			 *  This interrupt will fire if enabled on a CONTROL type endpoint if a new control packet is
			 *  received from the host.
			 *
			 *  \note This interrupt must be enabled and cleared on *each* endpoint which requires it (after the
			 *        endpoint is selected), and will fire the common endpoint interrupt vector.
			 *
			 *  \see ENDPOINT_PIPE_vect for more information on the common pipe and endpoint interrupt vector.
			 */
			#define ENDPOINT_INT_SETUP                    UEIENX, (1 << RXSTPE), UEINTX, (1 << RXSTPI)

			/** Interrupt definition for the endpoint IN interrupt (for INTERRUPT type endpoints). Should be
			 *  used with the USB_INT_* macros located in USBInterrupt.h.
			 *
			 *  This interrupt will fire if enabled on an INTERRUPT type endpoint if a the endpoint interrupt
			 *  period has elapsed and the endpoint is ready for a new packet to be written to its FIFO buffer
			 *  (if required).
			 *
			 *  \note This interrupt must be enabled and cleared on *each* endpoint which requires it (after the
			 *        endpoint is selected), and will fire the common endpoint interrupt vector.
			 *
			 *  \see ENDPOINT_PIPE_vect for more information on the common pipe and endpoint interrupt vector.
			 */
			#define ENDPOINT_INT_IN                       UEIENX, (1 << TXINE) , UEINTX, (1 << TXINI)

			/** Interrupt definition for the endpoint OUT interrupt (for INTERRUPT type endpoints). Should be
			 *  used with the USB_INT_* macros located in USBInterrupt.h.
			 *
			 *  This interrupt will fire if enabled on an INTERRUPT type endpoint if a the endpoint interrupt
			 *  period has elapsed and the endpoint is ready for a packet from the host to be read from its
			 *  FIFO buffer (if received).
			 *
			 *  \note This interrupt must be enabled and cleared on *each* endpoint which requires it (after the
			 *        endpoint is selected), and will fire the common endpoint interrupt vector.
			 *
			 *  \see ENDPOINT_PIPE_vect for more information on the common pipe and endpoint interrupt vector.
			 */
			#define ENDPOINT_INT_OUT                      UEIENX, (1 << RXOUTE), UEINTX, (1 << RXOUTI)
			
		/* Psuedo-Function Macros: */
			#if defined(__DOXYGEN__)
				/** Indicates the number of bytes currently stored in the current endpoint's selected bank.
				 *
				 *  \note The return width of this function may differ, depending on the maximum endpoint bank size
				 *        of the selected AVR model.
				 *
				 *  \ingroup Group_EndpointRW
				 *
				 *  \return Total number of bytes in the currently selected Endpoint's FIFO buffer
				 */
				static inline uint16_t Endpoint_BytesInEndpoint(void);
			
				/** Get the endpoint address of the currently selected endpoint. This is typically used to save
				 *  the currently selected endpoint number so that it can be restored after another endpoint has
				 *  been manipulated.
				 *
				 *  \return Index of the currently selected endpoint
				 */
				static inline uint8_t Endpoint_GetCurrentEndpoint(void);
				
				/** Selects the given endpoint number. If the address from the device descriptors is used, the
				 *  value should be masked with the ENDPOINT_EPNUM_MASK constant to extract only the endpoint
				 *  number (and discarding the endpoint direction bit).
				 *
				 *  Any endpoint operations which do not require the endpoint number to be indicated will operate on
				 *  the currently selected endpoint.
				 *
				 *  \param EndpointNumber Endpoint number to select
				 */
				static inline void Endpoint_SelectEndpoint(uint8_t EndpointNumber);
				
				/** Resets the endpoint bank FIFO. This clears all the endpoint banks and resets the USB controller's
				 *  In and Out pointers to the bank's contents.
				 *
				 *  \param EndpointNumber Endpoint number whose FIFO buffers are to be reset
				 */
				static inline void Endpoint_ResetFIFO(uint8_t EndpointNumber);
				
				/** Enables the currently selected endpoint so that data can be sent and received through it to
				 *  and from a host.
				 *
				 *  \note Endpoints must first be configured properly rather than just being enabled via the
				 *        Endpoint_ConfigureEndpoint() macro, which calls Endpoint_EnableEndpoint() automatically.
				 */
				static inline void Endpoint_EnableEndpoint(void);

				/** Disables the currently selected endpoint so that data cannot be sent and received through it
				 *  to and from a host.
				 */
				static inline void Endpoint_DisableEndpoint(void);
				
				/** Determines if the currently selected endpoint is enabled, but not necessarily configured.
				 *
				 * \return Boolean True if the currently selected endpoint is enabled, false otherwise
				 */
				static inline bool Endpoint_IsEnabled(void);
				
				/** Determines if the currently selected endpoint may be read from (if data is waiting in the endpoint
				 *  bank and the endpoint is an OUT direction, or if the bank is not yet full if the endpoint is an IN
				 *  direction). This function will return false if an error has occurred in the endpoint, if the endpoint
				 *  is an OUT direction and no packet (or an empty packet) has been received, or if the endpoint is an IN
				 *  direction and the endpoint bank is full.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 *
				 *  \return Boolean true if the currently selected endpoint may be read from or written to, depending on its direction
				 */
				static inline bool Endpoint_IsReadWriteAllowed(void);
				
				/** Determines if the currently selected endpoint is configured.
				 *
				 *  \return Boolean true if the currently selected endpoint has been configured, false otherwise
				 */
				static inline bool Endpoint_IsConfigured(void);
				
				/** Returns a mask indicating which INTERRUPT type endpoints have interrupted - i.e. their
				 *  interrupt duration has elapsed. Which endpoints have interrupted can be determined by
				 *  masking the return value against (1 << {Endpoint Number}).
				 *
				 *  \return Mask whose bits indicate which endpoints have interrupted
				 */
				static inline uint8_t Endpoint_GetEndpointInterrupts(void);
				
				/** Clears the endpoint interrupt flag. This clears the specified endpoint number's interrupt
				 *  mask in the endpoint interrupt flag register.
				 *
				 *  \param EndpointNumber  Index of the endpoint whose interrupt flag should be cleared
				 */
				static inline void Endpoint_ClearEndpointInterrupt(uint8_t EndpointNumber);
				
				/** Determines if the specified endpoint number has interrupted (valid only for INTERRUPT type
				 *  endpoints).
				 *
				 *  \param EndpointNumber  Index of the endpoint whose interrupt flag should be tested
				 *
				 *  \return Boolean true if the specified endpoint has interrupted, false otherwise
				 */
				static inline bool Endpoint_HasEndpointInterrupted(uint8_t EndpointNumber);
				
				/** Determines if the selected IN endpoint is ready for a new packet.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 *
				 *  \return Boolean true if the current endpoint is ready for an IN packet, false otherwise.
				 */
				static inline bool Endpoint_IsINReady(void);
				
				/** Determines if the selected OUT endpoint has received new packet.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 *
				 *  \return Boolean true if current endpoint is has received an OUT packet, false otherwise.
				 */
				static inline bool Endpoint_IsOUTReceived(void);
				
				/** Determines if the current CONTROL type endpoint has received a SETUP packet.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 *
				 *  \return Boolean true if the selected endpoint has received a SETUP packet, false otherwise.
				 */
				static inline bool Endpoint_IsSETUPReceived(void);
				
				/** Clears a received SETUP packet on the currently selected CONTROL type endpoint, freeing up the
				 *  endpoint for the next packet.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 *
				 *  \note This is not applicable for non CONTROL type endpoints.			 
				 */
				static inline void Endpoint_ClearControlSETUP(void);
				
				/** Sends an IN packet to the host on the currently selected CONTROL type endpoint, freeing up the
				 *  endpoint for the next packet.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 *
				 *  \note For non CONTROL type endpoints, use Endpoint_ClearIN() instead.			 
				 */
				static inline void Endpoint_ClearControlIN(void);
				
				/** Acknowledges an OUT packet to the host on the currently selected CONTROL type endpoint, freeing
				 *  up the endpoint for the next packet.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 *
				 *  \note For non CONTROL type endpoints, use Endpoint_ClearOUT() instead.
				 */
				static inline void Endpoint_ClearControlOUT(void);
				
				/** Sends an IN packet to the host on the currently selected non CONTROL type endpoint, freeing
				 *  up the endpoint for the next packet and switching to the alternative endpoint bank if double banked.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 *
				 *  \note For CONTROL type endpoints, use Endpoint_ClearControlIN() instead.
				 */
				static inline void Endpoint_ClearIN(void);
				
				/** Acknowledges an OUT packet to the host on the currently selected non CONTROL type endpoint, freeing
				 *  up the endpoint for the next packet and switching to the alternative endpoint bank if double banked.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 *
				 *  \note For CONTROL type endpoints, use Endpoint_ClearControlOUT() instead.
				 */
				static inline void Endpoint_ClearOUT(void);
				
				/** Stalls the current endpoint, indicating to the host that a logical problem occurred with the
				 *  indicated endpoint and that the current transfer sequence should be aborted. This provides a
				 *  way for devices to indicate invalid commands to the host so that the current transfer can be
				 *  aborted and the host can begin its own recovery sequence.
				 *
				 *  The currently selected endpoint remains stalled until either the Endpoint_ClearStall() macro
				 *  is called, or the host issues a CLEAR FEATURE request to the device for the currently selected
				 *  endpoint.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 */
				static inline void Endpoint_StallTransaction(void);
				
				/** Clears the STALL condition on the currently selected endpoint.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 */
				static inline void Endpoint_ClearStall(void);
				
				/** Determines if the currently selected endpoint is stalled, false otherwise.
				 *
				 *  \ingroup Group_EndpointPacketManagement
				 *
				 *  \return Boolean true if the currently selected endpoint is stalled, false otherwise
				 */
				static inline bool Endpoint_IsStalled(void);
				
				/** Resets the data toggle of the currently selected endpoint. */
				static inline void Endpoint_ResetDataToggle(void);
				
				/** Determines the currently selected endpoint's direction.
				 *
				 *  \return The currently selected endpoint's direction, as a ENDPOINT_DIR_* mask.
				 */
				static inline uint8_t Endpoint_GetEndpointDirection(void);
			#else
				#if defined(USB_FULL_CONTROLLER) || defined(USB_MODIFIED_FULL_CONTROLLER) || defined(__DOXYGEN__)
					#define Endpoint_BytesInEndpoint()        UEBCX
				#else
					#define Endpoint_BytesInEndpoint()        UEBCLX
				#endif
				
				#define Endpoint_GetCurrentEndpoint()         (UENUM & ENDPOINT_EPNUM_MASK)
				
				#define Endpoint_SelectEndpoint(epnum)        MACROS{ UENUM = epnum; }MACROE

				#define Endpoint_ResetFIFO(epnum)             MACROS{ UERST = (1 << epnum); UERST = 0; }MACROE

				#define Endpoint_EnableEndpoint()             MACROS{ UECONX |= (1 << EPEN); }MACROE

				#define Endpoint_DisableEndpoint()            MACROS{ UECONX &= ~(1 << EPEN); }MACROE

				#define Endpoint_IsEnabled()                  ((UECONX & (1 << EPEN)) ? true : false)

				#define Endpoint_IsReadWriteAllowed()         ((UEINTX & (1 << RWAL)) ? true : false)

				#define Endpoint_IsConfigured()               ((UESTA0X & (1 << CFGOK)) ? true : false)

				#define Endpoint_GetEndpointInterrupts()      UEINT

				#define Endpoint_ClearEndpointInterrupt(n)    MACROS{ UEINT &= ~(1 << n); }MACROE

				#define Endpoint_HasEndpointInterrupted(n)    ((UEINT & (1 << n)) ? true : false)
				
				#define Endpoint_IsINReady()                 ((UEINTX & (1 << TXINI))  ? true : false)
				
				#define Endpoint_IsOUTReceived()             ((UEINTX & (1 << RXOUTI)) ? true : false)

				#define Endpoint_IsSETUPReceived()            ((UEINTX & (1 << RXSTPI)) ? true : false)

				#define Endpoint_ClearControlSETUP()          MACROS{ UEINTX &= ~(1 << RXSTPI); }MACROE

				#define Endpoint_ClearControlIN()             MACROS{ UEINTX &= ~(1 << TXINI); }MACROE

				#define Endpoint_ClearControlOUT()            MACROS{ UEINTX &= ~(1 << RXOUTI); }MACROE

				#define Endpoint_ClearIN()                    MACROS{ UEINTX &= ~(1 << TXINI); UEINTX &= ~(1 << FIFOCON); }MACROE

				#define Endpoint_ClearOUT()                   MACROS{ UEINTX &= ~(1 << RXOUTI); UEINTX &= ~(1 << FIFOCON); }MACROE

				#define Endpoint_StallTransaction()           MACROS{ UECONX |= (1 << STALLRQ); }MACROE

				#define Endpoint_ClearStall()                 MACROS{ UECONX |= (1 << STALLRQC); }MACROE

				#define Endpoint_IsStalled()                  ((UECONX & (1 << STALLRQ)) ? true : false)

				#define Endpoint_ResetDataToggle()            MACROS{ UECONX |= (1 << RSTDT); }MACROE
				
				#define Endpoint_GetEndpointDirection()       (UECFG0X & ENDPOINT_DIR_IN)
			#endif

		/* Enums: */
			/** Enum for the possible error return codes of the Endpoint_WaitUntilReady function.
			 *
			 *  \ingroup Group_EndpointRW
			 */
			enum Endpoint_WaitUntilReady_ErrorCodes_t
			{
				ENDPOINT_READYWAIT_NoError                 = 0, /**< Endpoint is ready for next packet, no error. */
				ENDPOINT_READYWAIT_EndpointStalled         = 1, /**< The endpoint was stalled during the stream
				                                                 *   transfer by the host or device.
				                                                 */
				ENDPOINT_READYWAIT_DeviceDisconnected      = 2,	/**< Device was disconnected from the host while
				                                                 *   waiting for the endpoint to become ready.
				                                                 */	
				ENDPOINT_READYWAIT_Timeout                 = 3, /**< The host failed to accept or send the next packet
				                                                 *   within the software timeout period set by the
				                                                 *   USB_STREAM_TIMEOUT_MS macro.
				                                                 */
			};
		
			/** Enum for the possible error return codes of the Endpoint_*_Stream_* functions.
			 *
			 *  \ingroup Group_EndpointRW
			 */
			enum Endpoint_Stream_RW_ErrorCodes_t
			{
				ENDPOINT_RWSTREAM_ERROR_NoError            = 0, /**< Command completed successfully, no error. */
				ENDPOINT_RWSTREAM_ERROR_EndpointStalled    = 1, /**< The endpoint was stalled during the stream
				                                                 *   transfer by the host or device.
				                                                 */
				ENDPOINT_RWSTREAM_ERROR_DeviceDisconnected = 1, /**< Device was disconnected from the host during
				                                                 *   the transfer.
				                                                 */
				ENDPOINT_RWSTREAM_ERROR_Timeout            = 2, /**< The host failed to accept or send the next packet
				                                                 *   within the software timeout period set by the
				                                                 *   USB_STREAM_TIMEOUT_MS macro.
				                                                 */
				ENDPOINT_RWSTREAM_ERROR_CallbackAborted    = 3, /**< Indicates that the stream's callback function
			                                                     *   aborted the transfer early.
				                                                 */
			};
			
			/** Enum for the possible error return codes of the Endpoint_*_Control_Stream_* functions..
			 *
			 *  \ingroup Group_EndpointRW
			 */
			enum Endpoint_ControlStream_RW_ErrorCodes_t
			{
				ENDPOINT_RWCSTREAM_ERROR_NoError            = 0, /**< Command completed successfully, no error. */
				ENDPOINT_RWCSTREAM_ERROR_HostAborted        = 1, /**< The aborted the transfer prematurely. */
			};

		/* Inline Functions: */
			/** Reads one byte from the currently selected endpoint's bank, for OUT direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \return Next byte in the currently selected endpoint's FIFO buffer
			 */
			static inline uint8_t Endpoint_Read_Byte(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint8_t Endpoint_Read_Byte(void)
			{
				return UEDATX;
			}

			/** Writes one byte from the currently selected endpoint's bank, for IN direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Byte  Next byte to write into the the currently selected endpoint's FIFO buffer
			 */
			static inline void Endpoint_Write_Byte(const uint8_t Byte) ATTR_ALWAYS_INLINE;
			static inline void Endpoint_Write_Byte(const uint8_t Byte)
			{
				UEDATX = Byte;
			}

			/** Discards one byte from the currently selected endpoint's bank, for OUT direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 */
			static inline void Endpoint_Discard_Byte(void) ATTR_ALWAYS_INLINE;
			static inline void Endpoint_Discard_Byte(void)
			{
				uint8_t Dummy;
				
				Dummy = UEDATX;
			}
			
			/** Reads two bytes from the currently selected endpoint's bank in little endian format, for OUT
			 *  direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \return Next word in the currently selected endpoint's FIFO buffer
			 */
			static inline uint16_t Endpoint_Read_Word_LE(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint16_t Endpoint_Read_Word_LE(void)
			{
				uint16_t Data;
				
				Data  = UEDATX;
				Data |= (((uint16_t)UEDATX) << 8);
			
				return Data;
			}

			/** Reads two bytes from the currently selected endpoint's bank in big endian format, for OUT
			 *  direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \return Next word in the currently selected endpoint's FIFO buffer
			 */
			static inline uint16_t Endpoint_Read_Word_BE(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint16_t Endpoint_Read_Word_BE(void)
			{
				uint16_t Data;
				
				Data  = (((uint16_t)UEDATX) << 8);
				Data |= UEDATX;
			
				return Data;
			}

			/** Writes two bytes to the currently selected endpoint's bank in little endian format, for IN
			 *  direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Word  Next word to write to the currently selected endpoint's FIFO buffer
			 */
			static inline void Endpoint_Write_Word_LE(const uint16_t Word) ATTR_ALWAYS_INLINE;
			static inline void Endpoint_Write_Word_LE(const uint16_t Word)
			{
				UEDATX = (Word & 0xFF);
				UEDATX = (Word >> 8);
			}
			
			/** Writes two bytes to the currently selected endpoint's bank in big endian format, for IN
			 *  direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Word  Next word to write to the currently selected endpoint's FIFO buffer
			 */
			static inline void Endpoint_Write_Word_BE(const uint16_t Word) ATTR_ALWAYS_INLINE;
			static inline void Endpoint_Write_Word_BE(const uint16_t Word)
			{
				UEDATX = (Word >> 8);
				UEDATX = (Word & 0xFF);
			}

			/** Discards two bytes from the currently selected endpoint's bank, for OUT direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 */
			static inline void Endpoint_Discard_Word(void) ATTR_ALWAYS_INLINE;
			static inline void Endpoint_Discard_Word(void)
			{
				uint8_t Dummy;
				
				Dummy = UEDATX;
				Dummy = UEDATX;
			}

			/** Reads four bytes from the currently selected endpoint's bank in little endian format, for OUT
			 *  direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \return Next double word in the currently selected endpoint's FIFO buffer
			 */
			static inline uint32_t Endpoint_Read_DWord_LE(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint32_t Endpoint_Read_DWord_LE(void)
			{
				union
				{
					uint32_t DWord;
					uint8_t  Bytes[4];
				} Data;
				
				Data.Bytes[0] = UEDATX;
				Data.Bytes[1] = UEDATX;
				Data.Bytes[2] = UEDATX;
				Data.Bytes[3] = UEDATX;
			
				return Data.DWord;
			}

			/** Reads four bytes from the currently selected endpoint's bank in big endian format, for OUT
			 *  direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \return Next double word in the currently selected endpoint's FIFO buffer
			 */
			static inline uint32_t Endpoint_Read_DWord_BE(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint32_t Endpoint_Read_DWord_BE(void)
			{
				union
				{
					uint32_t DWord;
					uint8_t  Bytes[4];
				} Data;
				
				Data.Bytes[3] = UEDATX;
				Data.Bytes[2] = UEDATX;
				Data.Bytes[1] = UEDATX;
				Data.Bytes[0] = UEDATX;
			
				return Data.DWord;
			}

			/** Writes four bytes to the currently selected endpoint's bank in little endian format, for IN
			 *  direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param DWord  Next double word to write to the currently selected endpoint's FIFO buffer
			 */
			static inline void Endpoint_Write_DWord_LE(const uint32_t DWord) ATTR_ALWAYS_INLINE;
			static inline void Endpoint_Write_DWord_LE(const uint32_t DWord)
			{
				UEDATX = (DWord &  0xFF);
				UEDATX = (DWord >> 8);
				UEDATX = (DWord >> 16);
				UEDATX = (DWord >> 24);
			}
			
			/** Writes four bytes to the currently selected endpoint's bank in big endian format, for IN
			 *  direction endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param DWord  Next double word to write to the currently selected endpoint's FIFO buffer
			 */
			static inline void Endpoint_Write_DWord_BE(const uint32_t DWord) ATTR_ALWAYS_INLINE;
			static inline void Endpoint_Write_DWord_BE(const uint32_t DWord)
			{
				UEDATX = (DWord >> 24);
				UEDATX = (DWord >> 16);
				UEDATX = (DWord >> 8);
				UEDATX = (DWord &  0xFF);
			}

			/** Discards four bytes from the currently selected endpoint's bank, for OUT direction endpoints.	
			 *
			 *  \ingroup Group_EndpointRW
			 */
			static inline void Endpoint_Discard_DWord(void) ATTR_ALWAYS_INLINE;
			static inline void Endpoint_Discard_DWord(void)
			{
				uint8_t Dummy;
				
				Dummy = UEDATX;
				Dummy = UEDATX;
				Dummy = UEDATX;
				Dummy = UEDATX;
			}

		/* External Variables: */
			/** Global indicating the maximum packet size of the default control endpoint located at address
			 *  0 in the device. This value is set to the value indicated in the device descriptor in the user
			 *  project once the USB interface is initialized into device mode.
			 *
			 *  If space is an issue, it is possible to fix this to a static value by defining the control
			 *  endpoint size in the FIXED_CONTROL_ENDPOINT_SIZE token passed to the compiler in the makefile
			 *  via the -D switch. When a fixed control endpoint size is used, the size is no longer dynamically
			 *  read from the descriptors at runtime and instead fixed to the given value. When used, it is
			 *  important that the descriptor control endpoint size value matches the size given as the
			 *  FIXED_CONTROL_ENDPOINT_SIZE token - it is recommended that the FIXED_CONTROL_ENDPOINT_SIZE token
			 *  be used in the descriptors to ensure this.
			 *
			 *  \note This variable should be treated as read-only in the user application, and never manually
			 *        changed in value.
			 */
			#if (!defined(FIXED_CONTROL_ENDPOINT_SIZE) || defined(__DOXYGEN__))
				extern uint8_t USB_ControlEndpointSize;
			#else
				#define USB_ControlEndpointSize FIXED_CONTROL_ENDPOINT_SIZE
			#endif

		/* Function Prototypes: */
			/** Configures the specified endpoint number with the given endpoint type, direction, bank size
			 *  and banking mode. Endpoints should be allocated in ascending order by their address in the
			 *  device (i.e. endpoint 1 should be configured before endpoint 2 and so on).
			 *
			 *  The endpoint type may be one of the EP_TYPE_* macros listed in LowLevel.h and the direction
			 *  may be either ENDPOINT_DIR_OUT or ENDPOINT_DIR_IN.
			 *
			 *  The bank size must indicate the maximum packet size that the endpoint can handle. Different
			 *  endpoint numbers can handle different maximum packet sizes - refer to the chosen USB AVR's
			 *  datasheet to determine the maximum bank size for each endpoint.
			 *
			 *  The banking mode may be either ENDPOINT_BANK_SINGLE or ENDPOINT_BANK_DOUBLE.
			 *
			 *  The success of this routine can be determined via the Endpoint_IsConfigured() macro.
			 *
			 *  By default, the routine is entirely dynamic, and will accept both constant and variable inputs.
			 *  If dynamic configuration is unused, a small space savings can be made by defining the
			 *  STATIC_ENDPOINT_CONFIGURATION macro via the -D switch to the compiler, to optimize for constant
			 *  input values.
			 *
			 *  \note This routine will select the specified endpoint, and the endpoint will remain selected
			 *        once the routine completes regardless of if the endpoint configuration succeeds.
			 *
			 *  \return Boolean true if the configuration succeeded, false otherwise
			 */
			bool Endpoint_ConfigureEndpoint(const uint8_t  Number, const uint8_t Type, const uint8_t Direction,
			                                const uint16_t Size, const uint8_t Banks);

			/** Spinloops until the currently selected non-control endpoint is ready for the next packet of data
			 *  to be read or written to it.
			 *
			 *  \note This routine should not be called on CONTROL type endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \return A value from the Endpoint_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_WaitUntilReady(void);

			/** Reads and discards the given number of bytes from the endpoint from the given buffer,
			 *  discarding fully read packets from the host as needed. The last packet is not automatically
			 *  discarded once the remaining bytes has been read; the user is responsible for manually
			 *  discarding the last packet from the host via the Endpoint_ClearOUT() macro. Between
			 *  each USB packet, the given stream callback function is executed repeatedly until the next
			 *  packet is ready, allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created using the STREAM_CALLBACK() macro. If the token
			 *  NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are disabled
			 *  and this function has the Callback parameter omitted.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Length    Number of bytes to send via the currently selected endpoint.
			 *  \param Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback
			 *
			 *  \return A value from the Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Discard_Stream(uint16_t Length
			#if !defined(NO_STREAM_CALLBACKS) || defined(__DOXYGEN__)
			                                , uint8_t (* const Callback)(void)
			#endif
			                                );

			/** Writes the given number of bytes to the endpoint from the given buffer in little endian,
			 *  sending full packets to the host as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  Endpoint_ClearIN() macro. Between each USB packet, the given stream callback function
			 *  is executed repeatedly until the endpoint is ready to accept the next packet, allowing for early
			 *  aborts of stream transfers.
			 *
			 *	The callback routine should be created using the STREAM_CALLBACK() macro. If the token
			 *  NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are disabled
			 *  and this function has the Callback parameter omitted.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Buffer    Pointer to the source data buffer to read from.
			 *  \param Length    Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback
			 *
			 *  \return A value from the Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Stream_LE(const void* Buffer, uint16_t Length
			#if !defined(NO_STREAM_CALLBACKS) || defined(__DOXYGEN__)
			                                 , uint8_t (* const Callback)(void)
			#endif
			                                 ) ATTR_NON_NULL_PTR_ARG(1);

			/** Writes the given number of bytes to the endpoint from the given buffer in big endian,
			 *  sending full packets to the host as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  Endpoint_ClearIN() macro. Between each USB packet, the given stream callback function
			 *  is executed repeatedly until the endpoint is ready to accept the next packet, allowing for early
			 *  aborts of stream transfers.
			 *
			 *	The callback routine should be created using the STREAM_CALLBACK() macro. If the token
			 *  NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are disabled
			 *  and this function has the Callback parameter omitted.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Buffer    Pointer to the source data buffer to read from.
			 *  \param Length    Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback
			 *
			 *  \return A value from the Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Stream_BE(const void* Buffer, uint16_t Length
			#if !defined(NO_STREAM_CALLBACKS) || defined(__DOXYGEN__)
			                                 , uint8_t (* const Callback)(void)
			#endif
			                                 ) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the endpoint from the given buffer in little endian,
			 *  discarding fully read packets from the host as needed. The last packet is not automatically
			 *  discarded once the remaining bytes has been read; the user is responsible for manually
			 *  discarding the last packet from the host via the Endpoint_ClearOUT() macro. Between
			 *  each USB packet, the given stream callback function is executed repeatedly until the endpoint
			 *  is ready to accept the next packet, allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created using the STREAM_CALLBACK() macro. If the token
			 *  NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are disabled
			 *  and this function has the Callback parameter omitted.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Buffer    Pointer to the destination data buffer to write to.
			 *  \param Length    Number of bytes to send via the currently selected endpoint.
			 *  \param Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback
			 *
			 *  \return A value from the Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Stream_LE(void* Buffer, uint16_t Length
			#if !defined(NO_STREAM_CALLBACKS) || defined(__DOXYGEN__)
			                                , uint8_t (* const Callback)(void)
			#endif
			                                ) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the endpoint from the given buffer in big endian,
			 *  discarding fully read packets from the host as needed. The last packet is not automatically
			 *  discarded once the remaining bytes has been read; the user is responsible for manually
			 *  discarding the last packet from the host via the Endpoint_ClearOUT() macro. Between
			 *  each USB packet, the given stream callback function is executed repeatedly until the endpoint
			 *  is ready to accept the next packet, allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created using the STREAM_CALLBACK() macro. If the token
			 *  NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are disabled
			 *  and this function has the Callback parameter omitted.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Buffer    Pointer to the destination data buffer to write to.
			 *  \param Length    Number of bytes to send via the currently selected endpoint.
			 *  \param Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback
			 *
			 *  \return A value from the Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Stream_BE(void* Buffer, uint16_t Length
			#if !defined(NO_STREAM_CALLBACKS) || defined(__DOXYGEN__)
			                                , uint8_t (* const Callback)(void)
			#endif
			                                ) ATTR_NON_NULL_PTR_ARG(1);

			/** Writes the given number of bytes to the CONTROL type endpoint from the given buffer in little endian,
			 *  sending full packets to the host as needed. The host OUT acknowledgement is not automatically cleared
			 *  in both failure and success states; the user is responsible for manually clearing the setup OUT to
			 *  finalize the transfer via the Endpoint_ClearControlOUT() macro.
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Buffer  Pointer to the source data buffer to read from.
			 *  \param Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_Stream_LE(const void* Buffer, uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** Writes the given number of bytes to the CONTROL type endpoint from the given buffer in big endian,
			 *  sending full packets to the host as needed. The host OUT acknowledgement is not automatically cleared
			 *  in both failure and success states; the user is responsible for manually clearing the setup OUT to
			 *  finalize the transfer via the Endpoint_ClearControlOUT() macro.
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Buffer  Pointer to the source data buffer to read from.
			 *  \param Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_Stream_BE(const void* Buffer, uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the CONTROL endpoint from the given buffer in little endian,
			 *  discarding fully read packets from the host as needed. The device IN acknowledgement is not
			 *  automatically sent after success or failure states; the user is responsible for manually sending the
			 *  setup IN to finalize the transfer via the Endpoint_ClearControlIN() macro.
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Buffer  Pointer to the destination data buffer to write to.
			 *  \param Length  Number of bytes to send via the currently selected endpoint.
			 *
			 *  \return A value from the Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Control_Stream_LE(void* Buffer, uint16_t Length)  ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the CONTROL endpoint from the given buffer in big endian,
			 *  discarding fully read packets from the host as needed. The device IN acknowledgement is not
			 *  automatically sent after success or failure states; the user is responsible for manually sending the
			 *  setup IN to finalize the transfer via the Endpoint_ClearControlIN() macro.
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \ingroup Group_EndpointRW
			 *
			 *  \param Buffer  Pointer to the destination data buffer to write to.
			 *  \param Length  Number of bytes to send via the currently selected endpoint.
			 *
			 *  \return A value from the Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Control_Stream_BE(void* Buffer, uint16_t Length)  ATTR_NON_NULL_PTR_ARG(1);		
			
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define Endpoint_AllocateMemory()              MACROS{ UECFG1X |=  (1 << ALLOC); }MACROE
			#define Endpoint_DeallocateMemory()            MACROS{ UECFG1X &= ~(1 << ALLOC); }MACROE
			
			#define _ENDPOINT_GET_MAXSIZE(n)               _ENDPOINT_GET_MAXSIZE2(ENDPOINT_DETAILS_EP ## n)
			#define _ENDPOINT_GET_MAXSIZE2(details)        _ENDPOINT_GET_MAXSIZE3(details)
			#define _ENDPOINT_GET_MAXSIZE3(maxsize, db)    maxsize

			#define _ENDPOINT_GET_DOUBLEBANK(n)            _ENDPOINT_GET_DOUBLEBANK2(ENDPOINT_DETAILS_EP ## n)
			#define _ENDPOINT_GET_DOUBLEBANK2(details)     _ENDPOINT_GET_DOUBLEBANK3(details)
			#define _ENDPOINT_GET_DOUBLEBANK3(maxsize, db) db
			
			#if defined(USB_FULL_CONTROLLER) || defined(USB_MODIFIED_FULL_CONTROLLER)
				#define ENDPOINT_DETAILS_EP0               64,  true
				#define ENDPOINT_DETAILS_EP1               256, true
				#define ENDPOINT_DETAILS_EP2               64,  true
				#define ENDPOINT_DETAILS_EP3               64,  true
				#define ENDPOINT_DETAILS_EP4               64,  true
				#define ENDPOINT_DETAILS_EP5               64,  true
				#define ENDPOINT_DETAILS_EP6               64,  true
			#else
				#define ENDPOINT_DETAILS_EP0               64,  true
				#define ENDPOINT_DETAILS_EP1               64,  false
				#define ENDPOINT_DETAILS_EP2               64,  false
				#define ENDPOINT_DETAILS_EP3               64,  true
				#define ENDPOINT_DETAILS_EP4               64,  true			
			#endif

			#if defined(STATIC_ENDPOINT_CONFIGURATION)
				#define Endpoint_ConfigureEndpoint(Number, Type, Direction, Size, Banks)        \
				                                     Endpoint_ConfigureEndpointStatic(Number,   \
				                                              ((Type << EPTYPE0) | Direction),  \
				                                              ((1 << ALLOC) | Banks | Endpoint_BytesToEPSizeMask(Size)));
			#endif

		/* Function Prototypes: */
			void Endpoint_ClearEndpoints(void);
			bool Endpoint_ConfigureEndpointStatic(const uint8_t Number, const uint8_t UECFG0XData, const uint8_t UECFG1XData);
			
		/* Inline Functions: */
			static inline uint8_t Endpoint_BytesToEPSizeMask(const uint16_t Bytes) ATTR_WARN_UNUSED_RESULT ATTR_CONST ATTR_ALWAYS_INLINE;
			static inline uint8_t Endpoint_BytesToEPSizeMask(const uint16_t Bytes)
			{
				if (Bytes <= 8)
				  return (0 << EPSIZE0);
				else if (Bytes <= 16)
				  return (1 << EPSIZE0);
				else if (Bytes <= 32)
				  return (2 << EPSIZE0);
				#if defined(USB_LIMITED_CONTROLLER)
				else
				  return (3 << EPSIZE0);
				#else
				else if (Bytes <= 64)
				  return (3 << EPSIZE0);
				else if (Bytes <= 128)
				  return (4 << EPSIZE0);
				else
				  return (5 << EPSIZE0);
				#endif
			};

	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
