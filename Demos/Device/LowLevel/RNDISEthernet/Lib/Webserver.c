/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Simple webserver application for demonstrating the RNDIS demo and TCP/IP stack. This
 *  application will serve up a static HTTP webpage when requested by the host.
 */

#include "Webserver.h"

/** HTTP server response header, for transmission before the page contents. This indicates to the host that a page exists at the
 *  given location, and gives extra connection information.
 */
const char PROGMEM HTTP200Header[] = "HTTP/1.1 200 OK\r\n"
                                     "Server: LUFA RNDIS\r\n"
                                     "Content-type: text/html\r\n"
                                     "Connection: close\r\n\r\n";

/** HTTP server response header, for transmission before a resource not found error. This indicates to the host that the given
 *  given URL is invalid, and gives extra error information.
 */
const char PROGMEM HTTP404Header[] = "HTTP/1.1 404 Not Found\r\n"
                                     "Server: LUFA RNDIS\r\n"
                                     "Connection: close\r\n\r\n";

/** HTTP page to serve to the host when a HTTP request is made. This page is too long for a single response, thus it is automatically
 *  broken up into smaller blocks and sent as a series of packets each time the webserver application callback is run.
 */
const char PROGMEM HTTPPage[]   =
		"<html>"
		"	<head>"
		"		<title>"
		"			LUFA Webserver Demo"
		"		</title>"
		"	</head>"
		"	<body>"
		"		<h1>Hello from your USB AVR!</h1>"
		"		<p>"
		"			Hello! Welcome to the LUFA RNDIS Demo Webserver test page, running on your USB AVR via the LUFA library. This demonstrates the HTTP webserver, TCP/IP stack and RNDIS demo all running atop the LUFA USB stack."
		"			<br /><br />"
		"			<small>Project Information: <a href=\"http://www.lufa-lib.org\">http://www.lufa-lib.org</a>.</small>"
		"			<hr />"
		"			<i>LUFA Version: </i>" LUFA_VERSION_STRING
		"		</p>"
		"	</body>"
		"</html>";


/** Initializes the Webserver application, opening the appropriate HTTP port in the TCP handler and registering the application
 *  callback routine for packets sent to the HTTP protocol port.
 */
void Webserver_Init(void)
{
	/* Open the HTTP port in the TCP protocol so that HTTP connections to the device can be established */
	TCP_SetPortState(TCP_PORT_HTTP, TCP_Port_Open, Webserver_ApplicationCallback);
}

/** Indicates if a given request equals the given HTTP command.
 *
 *  \param[in] RequestHeader  HTTP request made by the host
 *  \param[in] Command        HTTP command to compare the request to
 *
 *  \return Boolean \c true if the command matches the request, \c false otherwise
 */
static bool IsHTTPCommand(uint8_t* RequestHeader,
                          char* Command)
{
	/* Returns true if the non null terminated string in RequestHeader matches the null terminated string Command */
	return (strncmp((char*)RequestHeader, Command, strlen(Command)) == 0);
}

/** Application callback routine, executed each time the TCP processing task runs. This callback determines what request
 *  has been made (if any), and serves up appropriate responses.
 *
 *  \param[in] ConnectionState  Pointer to a TCP Connection State structure giving connection information
 *  \param[in,out] Buffer       Pointer to the application's send/receive packet buffer
 */
void Webserver_ApplicationCallback(TCP_ConnectionState_t* const ConnectionState,
                                   TCP_ConnectionBuffer_t* const Buffer)
{
	char*          BufferDataStr = (char*)Buffer->Data;
	static uint8_t PageBlock     = 0;

	/* Check to see if a packet has been received on the HTTP port from a remote host */
	if (TCP_APP_HAS_RECEIVED_PACKET(Buffer))
	{
		if (IsHTTPCommand(Buffer->Data, "GET"))
		{
			if (IsHTTPCommand(Buffer->Data, "GET / "))
			{
				PageBlock = 0;

				/* Copy the HTTP 200 response header into the packet buffer */
				strcpy_P(BufferDataStr, HTTP200Header);

				/* Send the buffer contents to the host */
				TCP_APP_SEND_BUFFER(Buffer, strlen(BufferDataStr));

				/* Lock the buffer to Device->Host transmissions only while we send the page contents */
				TCP_APP_CAPTURE_BUFFER(Buffer);
			}
			else
			{
				/* Copy the HTTP 404 response header into the packet buffer */
				strcpy_P(BufferDataStr, HTTP404Header);

				/* Send the buffer contents to the host */
				TCP_APP_SEND_BUFFER(Buffer, strlen(BufferDataStr));

				/* All data sent, close the connection */
				TCP_APP_CLOSECONNECTION(ConnectionState);
			}
		}
		else if (IsHTTPCommand(Buffer->Data, "HEAD"))
		{
			if (IsHTTPCommand(Buffer->Data, "HEAD / "))
			{
				/* Copy the HTTP response header into the packet buffer */
				strcpy_P(BufferDataStr, HTTP200Header);

				/* Send the buffer contents to the host */
				TCP_APP_SEND_BUFFER(Buffer, strlen(BufferDataStr));
			}
			else
			{
				/* Copy the HTTP response header into the packet buffer */
				strcpy_P(BufferDataStr, HTTP404Header);

				/* Send the buffer contents to the host */
				TCP_APP_SEND_BUFFER(Buffer, strlen(BufferDataStr));
			}

			/* All data sent, close the connection */
			TCP_APP_CLOSECONNECTION(ConnectionState);
		}
		else if (IsHTTPCommand(Buffer->Data, "TRACE"))
		{
			/* Echo the host's query back to the host */
			TCP_APP_SEND_BUFFER(Buffer, Buffer->Length);

			/* All data sent, close the connection */
			TCP_APP_CLOSECONNECTION(ConnectionState);
		}
		else
		{
			/* Unknown request, just clear the buffer (drop the packet) */
			TCP_APP_CLEAR_BUFFER(Buffer);
		}
	}
	else if (TCP_APP_HAVE_CAPTURED_BUFFER(Buffer))
	{
		uint16_t RemLength = strlen_P(&HTTPPage[PageBlock * HTTP_REPLY_BLOCK_SIZE]);
		uint16_t Length;

		/* Determine the length of the loaded block */
		Length = MIN(RemLength, HTTP_REPLY_BLOCK_SIZE);

		/* Copy the next buffer sized block of the page to the packet buffer */
		strncpy_P(BufferDataStr, &HTTPPage[PageBlock * HTTP_REPLY_BLOCK_SIZE], Length);

		/* Send the buffer contents to the host */
		TCP_APP_SEND_BUFFER(Buffer, Length);

		/* Check to see if the entire page has been sent */
		if (PageBlock++ == (sizeof(HTTPPage) / HTTP_REPLY_BLOCK_SIZE))
		{
			/* Unlock the buffer so that the host can fill it with future packets */
			TCP_APP_RELEASE_BUFFER(Buffer);

			/* Close the connection to the host */
			TCP_APP_CLOSECONNECTION(ConnectionState);
		}
	}
}

