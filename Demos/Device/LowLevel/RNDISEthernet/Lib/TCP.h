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
 *  Header file for TCP.c.
 */

#ifndef _TCP_H_
#define _TCP_H_

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>

		#include "EthernetProtocols.h"
		#include "Ethernet.h"
		#include "ProtocolDecoders.h"

	/* Macros: */
		/** Maximum number of TCP ports which can be open at the one time. */
		#define MAX_OPEN_TCP_PORTS              1

		/** Maximum number of TCP connections which can be sustained at the one time. */
		#define MAX_TCP_CONNECTIONS             3

		/** TCP window size, giving the maximum number of bytes which can be buffered at the one time. */
		#define TCP_WINDOW_SIZE                 512

		/** Port number for HTTP transmissions. */
		#define TCP_PORT_HTTP                   SwapEndian_16(80)

		/** Data direction indicator for a TCP application buffer, indicating data from host-to-device. */
		#define TCP_PACKETDIR_IN                false

		/** Data direction indicator for a TCP application buffer, indicating data from device-to-host. */
		#define TCP_PACKETDIR_OUT               true

		/** Congestion Window Reduced TCP flag mask. */
		#define TCP_FLAG_CWR                    (1 << 7)

		/** Explicit Congestion Notification TCP flag mask. */
		#define TCP_FLAG_ECE                    (1 << 6)

		/** Urgent TCP flag mask. */
		#define TCP_FLAG_URG                    (1 << 5)

		/** Data Acknowledge TCP flag mask. */
		#define TCP_FLAG_ACK                    (1 << 4)

		/** Data Push TCP flag mask. */
		#define TCP_FLAG_PSH                    (1 << 3)

		/** Reset TCP flag mask. */
		#define TCP_FLAG_RST                    (1 << 2)

		/** Synchronize TCP flag mask. */
		#define TCP_FLAG_SYN                    (1 << 1)

		/** Connection Finalize TCP flag mask. */
		#define TCP_FLAG_FIN                    (1 << 0)

		/** Application macro: Determines if the given application buffer contains a packet received from the host
		 *
		 *  \param[in] Buffer  Application buffer to check
		 *
		 *  \return Boolean \c true if the buffer contains a packet from the host, \c false otherwise
		 */
		#define TCP_APP_HAS_RECEIVED_PACKET(Buffer)  (Buffer->Ready && (Buffer->Direction == TCP_PACKETDIR_IN))

		/** Application macro: Indicates if the application buffer is currently locked by the application for device-to-host transfers.
		 *
		 *  \param[in] Buffer  Application buffer to check
		 *
		 *  \return Boolean \c true if the buffer has been captured by the application for device-to-host transmissions, \c false otherwise
		 */
		#define TCP_APP_HAVE_CAPTURED_BUFFER(Buffer) (!(Buffer->Ready) && Buffer->InUse && \
		                                              (Buffer->Direction == TCP_PACKETDIR_OUT))

		/** Application macro: Indicates if the application can lock the buffer for multiple continued device-to-host transmissions.
		 *
		 *  \param[in] Buffer  Application buffer to check
		 *
		 *  \return Boolean \c true if the buffer may be captured by the application for device-to-host transmissions, \c false otherwise
		 */
		#define TCP_APP_CAN_CAPTURE_BUFFER(Buffer)   Buffer->InUse

		/** Application macro: Captures the application buffer, locking it for device-to-host transmissions only. This should be
		 *  performed when the application needs to transmit several packets worth of data in succession with no interruptions from the host.
		 *
		 *  \pre The application must check that the buffer can be locked first using TCP_APP_CAN_CAPTURE_BUFFER().
		 *
		 *  \param[in] Buffer  Application buffer to lock
		 */
		#define TCP_APP_CAPTURE_BUFFER(Buffer)       MACROS{ Buffer->Direction = TCP_PACKETDIR_OUT; Buffer->InUse = true; }MACROE

		/** Application macro: Releases a captured application buffer, allowing for host-to-device packets to be received.
		 *
		 *  \param[in] Buffer  Application buffer to release
		 */
		#define TCP_APP_RELEASE_BUFFER(Buffer)       MACROS{ Buffer->InUse = false; }MACROE

		/** Application macro: Sends the contents of the given application buffer to the host.
		 *
		 *  \param[in] Buffer  Application buffer to send
		 *  \param[in] Len     Length of data contained in the buffer
		 */
		#define TCP_APP_SEND_BUFFER(Buffer, Len)     MACROS{ Buffer->Direction = TCP_PACKETDIR_OUT; Buffer->Length = Len; Buffer->Ready = true; }MACROE

		/** Application macro: Clears the application buffer, ready for a packet to be written to it.
		 *
		 *  \param[in] Buffer  Application buffer to clear
		 */
		#define TCP_APP_CLEAR_BUFFER(Buffer)         MACROS{ Buffer->Ready = false; Buffer->Length = 0; }MACROE

		/** Application macro: Closes an open connection to a host.
		 *
		 *  \param[in] Connection  Open TCP connection to close
		 */
		#define TCP_APP_CLOSECONNECTION(Connection)  MACROS{ Connection->State = TCP_Connection_Closing;  }MACROE

	/* Enums: */
		/** Enum for possible TCP port states. */
		enum TCP_PortStates_t
		{
			TCP_Port_Closed            = 0, /**< TCP port closed, no connections to a host may be made on this port. */
			TCP_Port_Open              = 1, /**< TCP port open, connections to a host may be made on this port. */
		};

		/** Enum for possible TCP connection states. */
		enum TCP_ConnectionStates_t
		{
			TCP_Connection_Listen      = 0, /**< Listening for a connection from a host */
			TCP_Connection_SYNSent     = 1, /**< Unused */
			TCP_Connection_SYNReceived = 2, /**< SYN received, waiting for ACK */
			TCP_Connection_Established = 3, /**< Connection established in both directions */
			TCP_Connection_FINWait1    = 4, /**< Closing, waiting for ACK */
			TCP_Connection_FINWait2    = 5, /**< Closing, waiting for FIN ACK */
			TCP_Connection_CloseWait   = 6, /**< Closing, waiting for ACK */
			TCP_Connection_Closing     = 7, /**< Unused */
			TCP_Connection_LastACK     = 8, /**< Unused */
			TCP_Connection_TimeWait    = 9, /**< Unused */
			TCP_Connection_Closed      = 10, /**< Connection closed in both directions */
		};

	/* Type Defines: */
		/** Type define for a TCP connection buffer structure, including size, data and direction. */
		typedef struct
		{
			uint16_t               Length; /**< Length of data in the TCP application buffer */
			uint8_t                Data[TCP_WINDOW_SIZE]; /**< TCP application data buffer */
			bool                   Direction; /**< Buffer transmission direction, either TCP_PACKETDIR_IN  or TCP_PACKETDIR_OUT */
			bool                   Ready; /**< If data from host, indicates buffer ready to be read, otherwise indicates
			                               *   buffer ready to be sent to the host
			                               */
			bool                   InUse; /**< Indicates if the buffer is locked to to the current direction, and cannot be changed */
		} TCP_ConnectionBuffer_t;

		/** Type define for a TCP connection information structure. */
		typedef struct
		{
			uint32_t               SequenceNumberIn; /**< Current TCP sequence number for host-to-device */
			uint32_t               SequenceNumberOut; /**< Current TCP sequence number for device-to-host */
			TCP_ConnectionBuffer_t Buffer; /**< Connection application data buffer */
		} TCP_ConnectionInfo_t;

		/** Type define for a complete TCP connection state. */
		typedef struct
		{
			uint16_t               Port; /**< Connection port number on the device */
			uint16_t               RemotePort; /**< Connection port number on the host */
			IP_Address_t           RemoteAddress; /**< Connection protocol IP address of the host */
			TCP_ConnectionInfo_t   Info; /**< Connection information, including application buffer */
			uint8_t                State; /**< Current connection state, a value from the \ref TCP_ConnectionStates_t enum */
		} TCP_ConnectionState_t;

		/** Type define for a TCP port state. */
		typedef struct
		{
			uint16_t               Port; /**< TCP port number on the device */
			uint8_t                State; /**< Current port state, a value from the \ref TCP_PortStates_t enum */
			void                   (*ApplicationHandler) (TCP_ConnectionState_t* ConnectionState,
			                                              TCP_ConnectionBuffer_t* Buffer); /**< Port application handler */
		} TCP_PortState_t;

		/** Type define for a TCP packet header. */
		typedef struct
		{
			uint16_t               SourcePort; /**< Source port of the TCP packet */
			uint16_t               DestinationPort; /**< Destination port of the TCP packet */

			uint32_t               SequenceNumber; /**< Data sequence number of the packet */
			uint32_t               AcknowledgmentNumber; /**< Data acknowledgment number of the packet */

			unsigned               Reserved   : 4; /**< Reserved, must be all 0 */
			unsigned               DataOffset : 4; /**< Offset of the data from the start of the header, in 4 byte chunks */
			uint8_t                Flags; /**< TCP packet flags */
			uint16_t               WindowSize; /**< Current data window size (bytes remaining in reception buffer) */

			uint16_t               Checksum; /**< TCP checksum */
			uint16_t               UrgentPointer; /**< Urgent data pointer */
		} TCP_Header_t;

	/* Function Prototypes: */
		void                  TCP_Init(void);
		void                  TCP_Task(void);
		bool                  TCP_SetPortState(const uint16_t Port,
		                                       const uint8_t State,
		                                       void (*Handler)(TCP_ConnectionState_t*, TCP_ConnectionBuffer_t*));
		uint8_t               TCP_GetPortState(const uint16_t Port);
		bool                  TCP_SetConnectionState(const uint16_t Port,
		                                             const IP_Address_t* RemoteAddress,
		                                             const uint16_t RemotePort,
		                                             const uint8_t State);
		uint8_t               TCP_GetConnectionState(const uint16_t Port,
		                                             const IP_Address_t* RemoteAddress,
		                                             const uint16_t RemotePort);
		TCP_ConnectionInfo_t* TCP_GetConnectionInfo(const uint16_t Port,
		                                            const IP_Address_t* RemoteAddress,
		                                            const uint16_t RemotePort);
		int16_t               TCP_ProcessTCPPacket(void* IPHeaderInStart,
		                                           void* TCPHeaderInStart,
		                                           void* TCPHeaderOutStart);

		#if defined(INCLUDE_FROM_TCP_C)
			static uint16_t TCP_Checksum16(void* TCPHeaderOutStart,
			                               const IP_Address_t* SourceAddress,
			                               const IP_Address_t* DestinationAddress,
			                               uint16_t TCPOutSize);
		#endif

#endif

