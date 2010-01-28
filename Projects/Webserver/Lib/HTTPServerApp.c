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
 
#include "HTTPServerApp.h"

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
                               "Connection: close\r\n\r\n"
							   "The requested file was not found.";

/** FAT Fs structure to hold the internal state of the FAT driver for the dataflash contents. */
FATFS DiskFATState;

/** Initialization function for the simple HTTP webserver. */
void WebserverApp_Init(void)
{
	/* Listen on port 80 for HTTP connections from hosts */
	uip_listen(HTONS(HTTP_SERVER_PORT));
	
	/* Mount the dataflash disk via FatFS */
	f_mount(0, &DiskFATState);
}

/** uIP stack application callback for the simple HTTP webserver. This function must be called each time the
 *  TCP/IP stack needs a TCP packet to be processed.
 */
void WebserverApp_Callback(void)
{
	uip_tcp_appstate_t* const AppState    = &uip_conn->appstate;
	char*                     AppData     = (char*)uip_appdata;
	uint16_t                  AppDataSize = 0;

	if (uip_aborted() || uip_timedout())
	{
		/* Close the file before terminating, if it is open */
		f_close(&AppState->FileToSend);

		AppState->CurrentState = WEBSERVER_STATE_Closed;

		return;
	}
	else if (uip_closed())
	{
		/* Completed connection, just return */
		return;
	}
	else if (uip_connected())
	{
		/* New connection - initialize connection state and data pointer to the appropriate HTTP header */
		AppState->CurrentState = WEBSERVER_STATE_OpenRequestedFile;
	}
	
	switch (AppState->CurrentState)
	{
		case WEBSERVER_STATE_OpenRequestedFile:
			/* Wait for the packet containing the request header */
			if (uip_datalen())
			{
				/* Must be a GET request, abort otherwise */
				if (strncmp(AppData, "GET ", (sizeof("GET ") - 1)) != 0)
				{
					uip_abort();
					break;
				}
		
				char FileName[13];

				/* Copy over the requested filename from the GET request */
				for (uint8_t i = 0; i < (sizeof(FileName) - 1); i++)
				{
					FileName[i] = AppData[sizeof("GET ") + i];
					
					if (FileName[i] == ' ')
					{
						FileName[i] = 0x00;
						break;
					}
				}
				
				/* Ensure requested filename is null-terminated */
				FileName[(sizeof(FileName) - 1)] = 0x00;
				
				/* If no filename specified, assume the default of INDEX.HTM */
				if (FileName[0] == 0x00)
				  strcpy(FileName, "INDEX.HTM");
				
				/* Try to open the file from the Dataflash disk */
				AppState->FileOpen = (f_open(&AppState->FileToSend, FileName, FA_OPEN_EXISTING | FA_READ) == FR_OK);

				AppState->CurrentState = WEBSERVER_STATE_SendHeaders;
			}

			break;
		case WEBSERVER_STATE_SendHeaders:
			/* Determine what HTTP header should be sent to the client */
			if (AppState->FileOpen)
			{
				AppDataSize = strlen_P(HTTP200Header);
				strncpy_P(AppData, HTTP200Header, AppDataSize);				
			}
			else
			{
				AppDataSize = strlen_P(HTTP404Header);
				strncpy_P(AppData, HTTP404Header, AppDataSize);				
			}
			
			uip_send(AppData, AppDataSize);
			
			AppState->CurrentState = WEBSERVER_STATE_SendData;
			break;
		case WEBSERVER_STATE_SendData:
			/* If end of file/file not open, progress to the close state */
			if (!(AppState->FileOpen))
			{
				f_close(&AppState->FileToSend);
				uip_close();
				AppState->CurrentState = WEBSERVER_STATE_Closed;
				break;
			}

			uint16_t MaxSegSize = uip_mss();
			
			/* Read the next chunk of data from the open file */
			f_read(&AppState->FileToSend, AppData, MaxSegSize, &AppDataSize);
			AppState->FileOpen = (MaxSegSize == AppDataSize);

			/* If data was read, send it to the client */
			if (AppDataSize)
			  uip_send(AppData, AppDataSize);
					
			break;
	}
}
