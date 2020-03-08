/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Transmission Control Protocol (TCP) packet handling routines. This protocol handles the reliable in-order transmission
 *  and reception of packets to and from devices on a network, to "ports" on the device. It is used in situations where data
 *  delivery must be reliable and correct, e.g. HTTP, TELNET and most other non-streaming protocols.
 */

#define  INCLUDE_FROM_TCP_C
#include "TCP.h"

/** Port state table array. This contains the current status of TCP ports in the device. To save on space, only open ports are
 *  stored - closed ports may be overwritten at any time, and the system will assume any ports not present in the array are closed. This
 *  allows for MAX_OPEN_TCP_PORTS to be less than the number of ports used by the application if desired.
 */
TCP_PortState_t        PortStateTable[MAX_OPEN_TCP_PORTS];

/** Connection state table array. This contains the current status of TCP connections in the device. To save on space, only active
 *  (non-closed) connections are stored - closed connections may be overwritten at any time, and the system will assume any connections
 *  not present in the array are closed.
 */
TCP_ConnectionState_t  ConnectionStateTable[MAX_TCP_CONNECTIONS];


/** Task to handle the calling of each registered application's callback function, to process and generate TCP packets at the application
 *  level. If an application produces a response, this task constructs the appropriate Ethernet frame and places it into the Ethernet OUT
 *  buffer for later transmission.
 */
void TCP_Task(void)
{
	/* Run each application in sequence, to process incoming and generate outgoing packets */
	for (uint8_t CSTableEntry = 0; CSTableEntry < MAX_TCP_CONNECTIONS; CSTableEntry++)
	{
		/* Find the corresponding port entry in the port table */
		for (uint8_t PTableEntry = 0; PTableEntry < MAX_OPEN_TCP_PORTS; PTableEntry++)
		{
			/* Run the application handler for the port */
			if ((PortStateTable[PTableEntry].Port  == ConnectionStateTable[CSTableEntry].Port) &&
			    (PortStateTable[PTableEntry].State == TCP_Port_Open))
			{
				PortStateTable[PTableEntry].ApplicationHandler(&ConnectionStateTable[CSTableEntry],
				                                               &ConnectionStateTable[CSTableEntry].Info.Buffer);
			}
		}
	}

	/* Bail out early if there is already a frame waiting to be sent in the Ethernet OUT buffer */
	if (FrameOUT.FrameLength)
	  return;

	/* Send response packets from each application as the TCP packet buffers are filled by the applications */
	for (uint8_t CSTableEntry = 0; CSTableEntry < MAX_TCP_CONNECTIONS; CSTableEntry++)
	{
		/* For each completely received packet, pass it along to the listening application */
		if ((ConnectionStateTable[CSTableEntry].Info.Buffer.Direction == TCP_PACKETDIR_OUT) &&
		    (ConnectionStateTable[CSTableEntry].Info.Buffer.Ready))
		{
			Ethernet_Frame_Header_t* FrameOUTHeader = (Ethernet_Frame_Header_t*)&FrameOUT.FrameData;
			IP_Header_t*             IPHeaderOUT    = (IP_Header_t*)&FrameOUT.FrameData[sizeof(Ethernet_Frame_Header_t)];
			TCP_Header_t*            TCPHeaderOUT   = (TCP_Header_t*)&FrameOUT.FrameData[sizeof(Ethernet_Frame_Header_t) +
			                                                                             sizeof(IP_Header_t)];
			void*                    TCPDataOUT     = &FrameOUT.FrameData[sizeof(Ethernet_Frame_Header_t) +
			                                                              sizeof(IP_Header_t) +
			                                                              sizeof(TCP_Header_t)];

			uint16_t PacketSize = ConnectionStateTable[CSTableEntry].Info.Buffer.Length;

			/* Fill out the TCP data */
			TCPHeaderOUT->SourcePort           = ConnectionStateTable[CSTableEntry].Port;
			TCPHeaderOUT->DestinationPort      = ConnectionStateTable[CSTableEntry].RemotePort;
			TCPHeaderOUT->SequenceNumber       = SwapEndian_32(ConnectionStateTable[CSTableEntry].Info.SequenceNumberOut);
			TCPHeaderOUT->AcknowledgmentNumber = SwapEndian_32(ConnectionStateTable[CSTableEntry].Info.SequenceNumberIn);
			TCPHeaderOUT->DataOffset           = (sizeof(TCP_Header_t) / sizeof(uint32_t));
			TCPHeaderOUT->WindowSize           = SwapEndian_16(TCP_WINDOW_SIZE);

			TCPHeaderOUT->Flags                = TCP_FLAG_ACK;
			TCPHeaderOUT->UrgentPointer        = 0;
			TCPHeaderOUT->Checksum             = 0;
			TCPHeaderOUT->Reserved             = 0;

			memcpy(TCPDataOUT, ConnectionStateTable[CSTableEntry].Info.Buffer.Data, PacketSize);

			ConnectionStateTable[CSTableEntry].Info.SequenceNumberOut += PacketSize;

			TCPHeaderOUT->Checksum             = TCP_Checksum16(TCPHeaderOUT, &ServerIPAddress,
			                                                    &ConnectionStateTable[CSTableEntry].RemoteAddress,
			                                                    (sizeof(TCP_Header_t) + PacketSize));

			PacketSize += sizeof(TCP_Header_t);

			/* Fill out the response IP header */
			IPHeaderOUT->TotalLength        = SwapEndian_16(sizeof(IP_Header_t) + PacketSize);
			IPHeaderOUT->TypeOfService      = 0;
			IPHeaderOUT->HeaderLength       = (sizeof(IP_Header_t) / sizeof(uint32_t));
			IPHeaderOUT->Version            = 4;
			IPHeaderOUT->Flags              = 0;
			IPHeaderOUT->FragmentOffset     = 0;
			IPHeaderOUT->Identification     = 0;
			IPHeaderOUT->HeaderChecksum     = 0;
			IPHeaderOUT->Protocol           = PROTOCOL_TCP;
			IPHeaderOUT->TTL                = DEFAULT_TTL;
			IPHeaderOUT->SourceAddress      = ServerIPAddress;
			IPHeaderOUT->DestinationAddress = ConnectionStateTable[CSTableEntry].RemoteAddress;

			IPHeaderOUT->HeaderChecksum     = Ethernet_Checksum16(IPHeaderOUT, sizeof(IP_Header_t));

			PacketSize += sizeof(IP_Header_t);

			/* Fill out the response Ethernet frame header */
			FrameOUTHeader->Source          = ServerMACAddress;
			FrameOUTHeader->Destination     = (MAC_Address_t){{0x02, 0x00, 0x02, 0x00, 0x02, 0x00}};
			FrameOUTHeader->EtherType       = SwapEndian_16(ETHERTYPE_IPV4);

			PacketSize += sizeof(Ethernet_Frame_Header_t);

			/* Set the response length in the buffer and indicate that a response is ready to be sent */
			FrameOUT.FrameLength            = PacketSize;

			ConnectionStateTable[CSTableEntry].Info.Buffer.Ready = false;

			break;
		}
	}
}

/** Initializes the TCP protocol handler, clearing the port and connection state tables. This must be called before TCP packets are
 *  processed.
 */
void TCP_Init(void)
{
	/* Initialize the port state table with all CLOSED entries */
	for (uint8_t PTableEntry = 0; PTableEntry < MAX_OPEN_TCP_PORTS; PTableEntry++)
	  PortStateTable[PTableEntry].State = TCP_Port_Closed;

	/* Initialize the connection table with all CLOSED entries */
	for (uint8_t CSTableEntry = 0; CSTableEntry < MAX_TCP_CONNECTIONS; CSTableEntry++)
	  ConnectionStateTable[CSTableEntry].State = TCP_Connection_Closed;
}

/** Sets the state and callback handler of the given port, specified in big endian to the given state.
 *
 *  \param[in] Port     Port whose state and callback function to set, specified in big endian
 *  \param[in] State    New state of the port, a value from the \ref TCP_PortStates_t enum
 *  \param[in] Handler  Application callback handler for the port
 *
 *  \return Boolean \c true if the port state was set, \c false otherwise (no more space in the port state table)
 */
bool TCP_SetPortState(const uint16_t Port,
                      const uint8_t State,
                      void (*Handler)(TCP_ConnectionState_t*, TCP_ConnectionBuffer_t*))
{
	/* Note, Port number should be specified in BIG endian to simplify network code */

	/* Check to see if the port entry is already in the port state table */
	for (uint8_t PTableEntry = 0; PTableEntry < MAX_OPEN_TCP_PORTS; PTableEntry++)
	{
		/* Find existing entry for the port in the table, update it if found */
		if (PortStateTable[PTableEntry].Port == Port)
		{
			PortStateTable[PTableEntry].State = State;
			PortStateTable[PTableEntry].ApplicationHandler = Handler;
			return true;
		}
	}

	/* Check if trying to open the port -- if so we need to find an unused (closed) entry and replace it */
	if (State == TCP_Port_Open)
	{
		for (uint8_t PTableEntry = 0; PTableEntry < MAX_OPEN_TCP_PORTS; PTableEntry++)
		{
			/* Find a closed port entry in the table, change it to the given port and state */
			if (PortStateTable[PTableEntry].State == TCP_Port_Closed)
			{
				PortStateTable[PTableEntry].Port  = Port;
				PortStateTable[PTableEntry].State = State;
				PortStateTable[PTableEntry].ApplicationHandler = Handler;
				return true;
			}
		}

		/* Port not in table and no room to add it, return failure */
		return false;
	}
	else
	{
		/* Port not in table but trying to close it, so operation successful */
		return true;
	}
}

/** Retrieves the current state of a given TCP port, specified in big endian.
 *
 *  \param[in] Port  TCP port whose state is to be retrieved, given in big-endian
 *
 *  \return A value from the \ref TCP_PortStates_t enum
 */
uint8_t TCP_GetPortState(const uint16_t Port)
{
	/* Note, Port number should be specified in BIG endian to simplify network code */

	for (uint8_t PTableEntry = 0; PTableEntry < MAX_OPEN_TCP_PORTS; PTableEntry++)
	{
		/* Find existing entry for the port in the table, return the port status if found */
		if (PortStateTable[PTableEntry].Port == Port)
		  return PortStateTable[PTableEntry].State;
	}

	/* Port not in table, assume closed */
	return TCP_Port_Closed;
}

/** Sets the connection state of the given port, remote address and remote port to the given TCP connection state. If the
 *  connection exists in the connection state table it is updated, otherwise it is created if possible.
 *
 *  \param[in] Port           TCP port of the connection on the device, specified in big endian
 *  \param[in] RemoteAddress  Remote protocol IP address of the connected device
 *  \param[in] RemotePort     TCP port of the remote device in the connection, specified in big endian
 *  \param[in] State          TCP connection state, a value from the \ref TCP_ConnectionStates_t enum
 *
 *  \return Boolean \c true if the connection was updated or created, \c false otherwise (no more space in the connection state table)
 */
bool TCP_SetConnectionState(const uint16_t Port,
                            const IP_Address_t* RemoteAddress,
                            const uint16_t RemotePort,
                            const uint8_t State)
{
	/* Note, Port number should be specified in BIG endian to simplify network code */

	for (uint8_t CSTableEntry = 0; CSTableEntry < MAX_TCP_CONNECTIONS; CSTableEntry++)
	{
		/* Find port entry in the table */
		if ((ConnectionStateTable[CSTableEntry].Port == Port) &&
		     IP_COMPARE(&ConnectionStateTable[CSTableEntry].RemoteAddress, RemoteAddress) &&
			 ConnectionStateTable[CSTableEntry].RemotePort == RemotePort)
		{
			ConnectionStateTable[CSTableEntry].State = State;
			return true;
		}
	}

	for (uint8_t CSTableEntry = 0; CSTableEntry < MAX_TCP_CONNECTIONS; CSTableEntry++)
	{
		/* Find empty entry in the table */
		if (ConnectionStateTable[CSTableEntry].State == TCP_Connection_Closed)
		{
			ConnectionStateTable[CSTableEntry].Port          = Port;
			ConnectionStateTable[CSTableEntry].RemoteAddress = *RemoteAddress;
			ConnectionStateTable[CSTableEntry].RemotePort    = RemotePort;
			ConnectionStateTable[CSTableEntry].State         = State;
			return true;
		}
	}

	return false;
}

/** Retrieves the current state of a given TCP connection to a host.
 *
 *  \param[in] Port           TCP port on the device in the connection, specified in big endian
 *  \param[in] RemoteAddress  Remote protocol IP address of the connected host
 *  \param[in] RemotePort     Remote TCP port of the connected host, specified in big endian
 *
 *  \return A value from the \ref TCP_ConnectionStates_t enum
 */
uint8_t TCP_GetConnectionState(const uint16_t Port,
                               const IP_Address_t* RemoteAddress,
                               const uint16_t RemotePort)
{
	/* Note, Port number should be specified in BIG endian to simplify network code */

	for (uint8_t CSTableEntry = 0; CSTableEntry < MAX_TCP_CONNECTIONS; CSTableEntry++)
	{
		/* Find port entry in the table */
		if ((ConnectionStateTable[CSTableEntry].Port == Port) &&
		     IP_COMPARE(&ConnectionStateTable[CSTableEntry].RemoteAddress, RemoteAddress) &&
			 ConnectionStateTable[CSTableEntry].RemotePort == RemotePort)

		{
			return ConnectionStateTable[CSTableEntry].State;
		}
	}

	return TCP_Connection_Closed;
}

/** Retrieves the connection info structure of a given connection to a host.
 *
 *  \param[in] Port           TCP port on the device in the connection, specified in big endian
 *  \param[in] RemoteAddress  Remote protocol IP address of the connected host
 *  \param[in] RemotePort     Remote TCP port of the connected host, specified in big endian
 *
 *  \return ConnectionInfo structure of the connection if found, NULL otherwise
 */
TCP_ConnectionInfo_t* TCP_GetConnectionInfo(const uint16_t Port,
                                            const IP_Address_t* RemoteAddress,
                                            const uint16_t RemotePort)
{
	/* Note, Port number should be specified in BIG endian to simplify network code */

	for (uint8_t CSTableEntry = 0; CSTableEntry < MAX_TCP_CONNECTIONS; CSTableEntry++)
	{
		/* Find port entry in the table */
		if ((ConnectionStateTable[CSTableEntry].Port == Port) &&
		     IP_COMPARE(&ConnectionStateTable[CSTableEntry].RemoteAddress, RemoteAddress) &&
			 ConnectionStateTable[CSTableEntry].RemotePort == RemotePort)
		{
			return &ConnectionStateTable[CSTableEntry].Info;
		}
	}

	return NULL;
}

/** Processes a TCP packet inside an Ethernet frame, and writes the appropriate response
 *  to the output Ethernet frame if one is created by a application handler.
 *
 *  \param[in] IPHeaderInStart     Pointer to the start of the incoming packet's IP header
 *  \param[in] TCPHeaderInStart    Pointer to the start of the incoming packet's TCP header
 *  \param[out] TCPHeaderOutStart  Pointer to the start of the outgoing packet's TCP header
 *
 *  \return The number of bytes written to the out Ethernet frame if any, NO_RESPONSE if no
 *           response was generated, NO_PROCESS if the packet processing was deferred until the
 *           next Ethernet packet handler iteration
 */
int16_t TCP_ProcessTCPPacket(void* IPHeaderInStart,
                             void* TCPHeaderInStart,
                             void* TCPHeaderOutStart)
{
	IP_Header_t*  IPHeaderIN   = (IP_Header_t*)IPHeaderInStart;
	TCP_Header_t* TCPHeaderIN  = (TCP_Header_t*)TCPHeaderInStart;
	TCP_Header_t* TCPHeaderOUT = (TCP_Header_t*)TCPHeaderOutStart;

	TCP_ConnectionInfo_t* ConnectionInfo;

	DecodeTCPHeader(TCPHeaderInStart);

	bool PacketResponse = false;

	/* Check if the destination port is open and allows incoming connections */
	if (TCP_GetPortState(TCPHeaderIN->DestinationPort) == TCP_Port_Open)
	{
		/* Detect SYN from host to start a connection */
		if (TCPHeaderIN->Flags & TCP_FLAG_SYN)
		  TCP_SetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress, TCPHeaderIN->SourcePort, TCP_Connection_Listen);

		/* Detect RST from host to abort existing connection */
		if (TCPHeaderIN->Flags & TCP_FLAG_RST)
		{
			if (TCP_SetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
			                           TCPHeaderIN->SourcePort, TCP_Connection_Closed))
			{
				TCPHeaderOUT->Flags = (TCP_FLAG_RST | TCP_FLAG_ACK);
				PacketResponse = true;
			}
		}
		else
		{
			/* Process the incoming TCP packet based on the current connection state for the sender and port */
			switch (TCP_GetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress, TCPHeaderIN->SourcePort))
			{
				case TCP_Connection_Listen:
					if (TCPHeaderIN->Flags == TCP_FLAG_SYN)
					{
						/* SYN connection starts a connection with a peer */
						if (TCP_SetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
						                           TCPHeaderIN->SourcePort, TCP_Connection_SYNReceived))
						{
							TCPHeaderOUT->Flags = (TCP_FLAG_SYN | TCP_FLAG_ACK);

							ConnectionInfo = TCP_GetConnectionInfo(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress, TCPHeaderIN->SourcePort);

							ConnectionInfo->SequenceNumberIn  = (SwapEndian_32(TCPHeaderIN->SequenceNumber) + 1);
							ConnectionInfo->SequenceNumberOut = 0;
							ConnectionInfo->Buffer.InUse      = false;
						}
						else
						{
							TCPHeaderOUT->Flags = TCP_FLAG_RST;
						}

						PacketResponse      = true;
					}

					break;
				case TCP_Connection_SYNReceived:
					if (TCPHeaderIN->Flags == TCP_FLAG_ACK)
					{
						/* ACK during the connection process completes the connection to a peer */

						TCP_SetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
											   TCPHeaderIN->SourcePort, TCP_Connection_Established);

						ConnectionInfo = TCP_GetConnectionInfo(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
															   TCPHeaderIN->SourcePort);

						ConnectionInfo->SequenceNumberOut++;
					}

					break;
				case TCP_Connection_Established:
					if (TCPHeaderIN->Flags == (TCP_FLAG_FIN | TCP_FLAG_ACK))
					{
						/* FIN ACK when connected to a peer starts the finalization process */

						TCPHeaderOUT->Flags = (TCP_FLAG_FIN | TCP_FLAG_ACK);
						PacketResponse      = true;

						TCP_SetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
											   TCPHeaderIN->SourcePort, TCP_Connection_CloseWait);

						ConnectionInfo = TCP_GetConnectionInfo(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
															   TCPHeaderIN->SourcePort);

						ConnectionInfo->SequenceNumberIn++;
						ConnectionInfo->SequenceNumberOut++;
					}
					else if ((TCPHeaderIN->Flags == TCP_FLAG_ACK) || (TCPHeaderIN->Flags == (TCP_FLAG_ACK | TCP_FLAG_PSH)))
					{
						ConnectionInfo = TCP_GetConnectionInfo(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
															   TCPHeaderIN->SourcePort);

						/* Check if the buffer is currently in use either by a buffered data to send, or receive */
						if ((ConnectionInfo->Buffer.InUse == false) && (ConnectionInfo->Buffer.Ready == false))
						{
							ConnectionInfo->Buffer.Direction = TCP_PACKETDIR_IN;
							ConnectionInfo->Buffer.InUse     = true;
							ConnectionInfo->Buffer.Length    = 0;
						}

						/* Check if the buffer has been claimed by us to read in data from the peer */
						if ((ConnectionInfo->Buffer.Direction == TCP_PACKETDIR_IN) &&
							(ConnectionInfo->Buffer.Length != TCP_WINDOW_SIZE))
						{
							uint16_t IPOffset   = (IPHeaderIN->HeaderLength * sizeof(uint32_t));
							uint16_t TCPOffset  = (TCPHeaderIN->DataOffset * sizeof(uint32_t));
							uint16_t DataLength = (SwapEndian_16(IPHeaderIN->TotalLength) - IPOffset - TCPOffset);

							/* Copy the packet data into the buffer */
							memcpy(&ConnectionInfo->Buffer.Data[ConnectionInfo->Buffer.Length],
								   &((uint8_t*)TCPHeaderInStart)[TCPOffset],
								   DataLength);

							ConnectionInfo->SequenceNumberIn += DataLength;
							ConnectionInfo->Buffer.Length    += DataLength;

							/* Check if the buffer is full or if the PSH flag is set, if so indicate buffer ready */
							if ((!(TCP_WINDOW_SIZE - ConnectionInfo->Buffer.Length)) || (TCPHeaderIN->Flags & TCP_FLAG_PSH))
							{
								ConnectionInfo->Buffer.InUse = false;
								ConnectionInfo->Buffer.Ready = true;

								TCPHeaderOUT->Flags = TCP_FLAG_ACK;
								PacketResponse      = true;
							}
						}
						else
						{
							/* Buffer is currently in use by the application, defer processing of the incoming packet */
							return NO_PROCESS;
						}
					}

					break;
				case TCP_Connection_Closing:
						ConnectionInfo = TCP_GetConnectionInfo(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
															   TCPHeaderIN->SourcePort);

						TCPHeaderOUT->Flags = (TCP_FLAG_ACK | TCP_FLAG_FIN);
						PacketResponse      = true;

						ConnectionInfo->Buffer.InUse = false;

						TCP_SetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
											   TCPHeaderIN->SourcePort, TCP_Connection_FINWait1);

					break;
				case TCP_Connection_FINWait1:
					if (TCPHeaderIN->Flags == (TCP_FLAG_FIN | TCP_FLAG_ACK))
					{
						ConnectionInfo = TCP_GetConnectionInfo(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
															   TCPHeaderIN->SourcePort);

						TCPHeaderOUT->Flags = TCP_FLAG_ACK;
						PacketResponse      = true;

						ConnectionInfo->SequenceNumberIn++;
						ConnectionInfo->SequenceNumberOut++;

						TCP_SetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
											   TCPHeaderIN->SourcePort, TCP_Connection_Closed);
					}
					else if (TCPHeaderIN->Flags == TCP_FLAG_ACK)
					{
						TCP_SetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
											   TCPHeaderIN->SourcePort, TCP_Connection_FINWait2);
					}

					break;
				case TCP_Connection_FINWait2:
					if (TCPHeaderIN->Flags == (TCP_FLAG_FIN | TCP_FLAG_ACK))
					{
						ConnectionInfo = TCP_GetConnectionInfo(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
															   TCPHeaderIN->SourcePort);

						TCPHeaderOUT->Flags = TCP_FLAG_ACK;
						PacketResponse      = true;

						ConnectionInfo->SequenceNumberIn++;
						ConnectionInfo->SequenceNumberOut++;

						TCP_SetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
											   TCPHeaderIN->SourcePort, TCP_Connection_Closed);
					}

					break;
				case TCP_Connection_CloseWait:
					if (TCPHeaderIN->Flags == TCP_FLAG_ACK)
					{
						TCP_SetConnectionState(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
											   TCPHeaderIN->SourcePort, TCP_Connection_Closed);
					}

					break;
			}
		}
	}
	else
	{
		/* Port is not open, indicate via a RST/ACK response to the sender */
		TCPHeaderOUT->Flags = (TCP_FLAG_RST | TCP_FLAG_ACK);
		PacketResponse      = true;
	}

	/* Check if we need to respond to the sent packet */
	if (PacketResponse)
	{
		ConnectionInfo = TCP_GetConnectionInfo(TCPHeaderIN->DestinationPort, &IPHeaderIN->SourceAddress,
		                                       TCPHeaderIN->SourcePort);

		TCPHeaderOUT->SourcePort           = TCPHeaderIN->DestinationPort;
		TCPHeaderOUT->DestinationPort      = TCPHeaderIN->SourcePort;
		TCPHeaderOUT->SequenceNumber       = SwapEndian_32(ConnectionInfo->SequenceNumberOut);
		TCPHeaderOUT->AcknowledgmentNumber = SwapEndian_32(ConnectionInfo->SequenceNumberIn);
		TCPHeaderOUT->DataOffset           = (sizeof(TCP_Header_t) / sizeof(uint32_t));

		if (!(ConnectionInfo->Buffer.InUse))
		  TCPHeaderOUT->WindowSize         = SwapEndian_16(TCP_WINDOW_SIZE);
		else
		  TCPHeaderOUT->WindowSize         = SwapEndian_16(TCP_WINDOW_SIZE - ConnectionInfo->Buffer.Length);

		TCPHeaderOUT->UrgentPointer        = 0;
		TCPHeaderOUT->Checksum             = 0;
		TCPHeaderOUT->Reserved             = 0;

		TCPHeaderOUT->Checksum             = TCP_Checksum16(TCPHeaderOUT, &IPHeaderIN->DestinationAddress,
		                                                    &IPHeaderIN->SourceAddress, sizeof(TCP_Header_t));

		return sizeof(TCP_Header_t);
	}

	return NO_RESPONSE;
}

/** Calculates the appropriate TCP checksum, consisting of the addition of the one's compliment of each word,
 *  complimented.
 *
 *  \param[in] TCPHeaderOutStart   Pointer to the start of the packet's outgoing TCP header
 *  \param[in] SourceAddress       Source protocol IP address of the outgoing IP header
 *  \param[in] DestinationAddress  Destination protocol IP address of the outgoing IP header
 *  \param[in] TCPOutSize          Size in bytes of the TCP data header and payload
 *
 *  \return A 16-bit TCP checksum value
 */
static uint16_t TCP_Checksum16(void* TCPHeaderOutStart,
                               const IP_Address_t* SourceAddress,
                               const IP_Address_t* DestinationAddress,
                               uint16_t TCPOutSize)
{
	uint32_t Checksum = 0;

	/* TCP/IP checksums are the addition of the one's compliment of each word including the IP pseudo-header,
	   complimented */

	Checksum += ((uint16_t*)SourceAddress)[0];
	Checksum += ((uint16_t*)SourceAddress)[1];
	Checksum += ((uint16_t*)DestinationAddress)[0];
	Checksum += ((uint16_t*)DestinationAddress)[1];
	Checksum += SwapEndian_16(PROTOCOL_TCP);
	Checksum += SwapEndian_16(TCPOutSize);

	for (uint16_t CurrWord = 0; CurrWord < (TCPOutSize >> 1); CurrWord++)
	  Checksum += ((uint16_t*)TCPHeaderOutStart)[CurrWord];

	if (TCPOutSize & 0x01)
	  Checksum += (((uint16_t*)TCPHeaderOutStart)[TCPOutSize >> 1] & 0x00FF);

	while (Checksum & 0xFFFF0000)
	  Checksum = ((Checksum & 0xFFFF) + (Checksum >> 16));

	return ~Checksum;
}

