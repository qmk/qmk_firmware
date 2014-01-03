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
 *
 *  TELNET Webserver Application. When connected to the uIP stack,
 *  this will serve out raw TELNET to the client on port 23.
 */

#define  INCLUDE_FROM_TELNETSERVERAPP_C
#include "TELNETServerApp.h"

#if defined(ENABLE_TELNET_SERVER) || defined(__DOXYGEN__)

/** Welcome message to send to a TELNET client when a connection is first made. */
const char PROGMEM WelcomeHeader[] = "********************************************\r\n"
                                     "*       LUFA uIP Webserver (TELNET)        *\r\n"
                                     "********************************************\r\n";

/** Main TELNET menu, giving the user the list of available commands they may issue */
const char PROGMEM TELNETMenu[] = "\r\n"
                                  "  == Available Commands: ==\r\n"
                                  "     c) List Active TCP Connections\r\n"
                                  "  =========================\r\n"
                                  "\r\n>";

/** Header to print before the current connections are printed to the client */
const char PROGMEM CurrentConnectionsHeader[] = "\r\n* Current TCP Connections: *\r\n";

/** Initialization function for the simple TELNET webserver. */
void TELNETServerApp_Init(void)
{
	/* Listen on port 23 for TELNET connections from hosts */
	uip_listen(HTONS(TELNET_SERVER_PORT));
}

/** uIP stack application callback for the TELNET server. This function must be called each time the
 *  TCP/IP stack needs a TCP packet to be processed.
 */
void TELNETServerApp_Callback(void)
{
	uip_tcp_appstate_t* const AppState   = &uip_conn->appstate;
	char*               const AppData    = (char*)uip_appdata;

	if (uip_connected())
	{
		/* New connection - initialize connection state values */
		AppState->TELNETServer.CurrentState = TELNET_STATE_SendHeader;
	}

	if (uip_acked())
	{
		/* Progress to the next state once the current state's data has been ACKed */
		AppState->TELNETServer.CurrentState = AppState->TELNETServer.NextState;
	}

	if (uip_rexmit() || uip_acked() || uip_newdata() || uip_connected() || uip_poll())
	{
		switch (AppState->TELNETServer.CurrentState)
		{
			case TELNET_STATE_SendHeader:
				/* Copy over and send the TELNET welcome message upon first connection */
				strcpy_P(AppData, WelcomeHeader);
				uip_send(AppData, strlen(AppData));

				AppState->TELNETServer.NextState = TELNET_STATE_SendMenu;
				break;
			case TELNET_STATE_SendMenu:
				/* Copy over and send the TELNET menu to the client */
				strcpy_P(AppData, TELNETMenu);
				uip_send(AppData, strlen(AppData));

				AppState->TELNETServer.NextState = TELNET_STATE_GetCommand;
				break;
			case TELNET_STATE_GetCommand:
				if (!(uip_datalen()))
				  break;

				/* Save the issued command for later processing */
				AppState->TELNETServer.IssuedCommand = AppData[0];

				AppState->TELNETServer.CurrentState  = TELNET_STATE_SendResponse;
				break;
			case TELNET_STATE_SendResponse:
				/* Determine which command was issued, perform command processing */
				switch (AppState->TELNETServer.IssuedCommand)
				{
					case 'c':
						TELNETServerApp_DisplayTCPConnections();
						break;
					default:
						strcpy_P(AppData, PSTR("Invalid Command.\r\n"));
						uip_send(AppData, strlen(AppData));
						break;
				}

				AppState->TELNETServer.NextState = TELNET_STATE_SendMenu;
				break;
		}
	}
}

/** Sends a list of active TCP connections to the TELNET client. */
static void TELNETServerApp_DisplayTCPConnections(void)
{
	char* const AppData    = (char*)uip_appdata;

	strcpy_P(AppData, CurrentConnectionsHeader);

	uint16_t ResponseLen     = strlen(AppData);
	uint8_t  ActiveConnCount = 0;

	/* Loop through the complete uIP TCP connections list, looking for active connections */
	for (uint8_t i = 0; i < UIP_CONNS; i++)
	{
		struct uip_conn* CurrConnection = &uip_conns[i];

		/* If the connection is not closed, it is active and must be added to the out buffer */
		if (CurrConnection->tcpstateflags != UIP_CLOSED)
		{
			/* Add the current connection's details to the out buffer */
			ResponseLen += sprintf_P(&AppData[ResponseLen], PSTR("%u) %d.%d.%d.%d (Local Port %u <=> Remote Port %u)\r\n"),
			                         ++ActiveConnCount,
			                         CurrConnection->ripaddr.u8[0],
			                         CurrConnection->ripaddr.u8[1],
			                         CurrConnection->ripaddr.u8[2],
			                         CurrConnection->ripaddr.u8[3],
			                         HTONS(CurrConnection->lport), HTONS(CurrConnection->rport));
		}
	}

	uip_send(AppData, ResponseLen);
}

#endif

