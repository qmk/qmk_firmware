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
 *  Simple HTTP Webserver Application. When connected to the uIP stack,
 *  this will serve out files to HTTP clients.
 */
 
#include "WebserverApp.h"

/** HTTP server response header, for transmission before the page contents. This indicates to the host that a page exists at the
 *  given location, and gives extra connection information.
 */
char PROGMEM HTTP200Header[] = "HTTP/1.1 200 OK\r\n"
                               "Server: LUFA RNDIS\r\n"
                               "Content-type: text/html\r\n"
                               "Connection: close\r\n\r\n";

/** HTTP server response header, for transmission before a resource not found error. This indicates to the host that the given
 *  given URL is invalid, and gives extra error information.
 */
char PROGMEM HTTP404Header[] = "HTTP/1.1 404 Not Found\r\n"
                               "Server: LUFA RNDIS\r\n"
                               "Connection: close\r\n\r\n";

/** HTTP page to serve to the host when a HTTP request is made. This page is too long for a single response, thus it is automatically
 *  broken up into smaller blocks and sent as a series of packets each time the webserver application callback is run.
 */
char PROGMEM HTTPPage[]   = 
		"<html>"
		"	<head>"
		"		<title>"
		"			LUFA Webserver Demo"
		"		</title>"
		"	</head>"
		"	<body>"
		"		<h1>Hello from your USB AVR!</h1>"
		"		<p>"
		"			Hello! Welcome to the LUFA RNDIS Demo Webserver test page, running on your USB AVR via the LUFA library and uIP TCP/IP network stack. This"
		"           demonstrates a simple HTTP webserver serving out pages to HTTP clients."
		"			<br /><br />"
		"			<small>Project Information: <a href=\"http://www.fourwalledcubicle.com/LUFA.php\">http://www.fourwalledcubicle.com/LUFA.php</a>.</small>"
		"			<hr />"
		"			<i>LUFA Version: </i>" LUFA_VERSION_STRING
		"		</p>"
		"	</body>"
		"</html>";

/** Initialization function for the simple HTTP webserver. */
void WebserverApp_Init(void)
{
	/* Listen on port 80 for HTTP connections from hosts */
	uip_listen(HTONS(80));
}

/** uIP stack application callback for the simple HTTP webserver. This function must be called each time the
 *  TCP/IP stack needs a TCP packet to be processed.
 */
void WebserverApp_Callback(void)
{
	char*    AppDataPtr  = (char*)uip_appdata;
	uint16_t AppDataSize = 0;

	if (uip_closed() || uip_aborted() || uip_timedout())
	{
		/* Terminated or completed connection - don't send any new data */
		return;
	}
	else if (uip_connected())
	{
		/* New connection - initialize connection state and data pointer to the appropriate HTTP header */
		uip_conn->appstate.SendPos      = HTTP200Header;
		uip_conn->appstate.CurrentState = WEBSERVER_STATE_SendHeaders;
	}

	/* Calculate the maximum segment size and remaining data size */
	uint16_t BytesRemaining = strlen_P(uip_conn->appstate.SendPos);
	uint16_t MaxSegSize     = uip_mss();

	/* No more bytes remaining in the current data being sent - progress to next data chunk or
	 * terminate the connection once all chunks are sent */
	if (!(BytesRemaining))
	{
		/* Check which data chunk we are currently sending (header or data) */
		if (uip_conn->appstate.CurrentState == WEBSERVER_STATE_SendHeaders)
		{
			uip_conn->appstate.SendPos = HTTPPage;
			uip_conn->appstate.CurrentState = WEBSERVER_STATE_SendData;			
		}
		else if (uip_conn->appstate.CurrentState == WEBSERVER_STATE_SendData)
		{
			uip_close();
			uip_conn->appstate.CurrentState = WEBSERVER_STATE_Closed;
		}
		  
		return;
	}
	else if (BytesRemaining > MaxSegSize)
	{
		/* More bytes remaining to send than the maximum segment size, send next chunk */
		AppDataSize = MaxSegSize;
	}
	else
	{
		/* Less bytes than the segment size remaining, send all remaining bytes in the one packet */
		AppDataSize = BytesRemaining;
	}

	/* Copy over the next data segment to the application buffer, advance send position pointer */
	strncpy_P(uip_appdata, uip_conn->appstate.SendPos, AppDataSize);
	uip_conn->appstate.SendPos += AppDataSize;

	/* Send the data to the requesting host */
	uip_send(AppDataPtr, AppDataSize);
}
