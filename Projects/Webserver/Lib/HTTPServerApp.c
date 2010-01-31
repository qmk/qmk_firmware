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
                               "Connection: close\r\n"
							   "MIME-version: 1.0\r\n"
							   "Content-Type: ";

/** HTTP server response header, for transmission before a resource not found error. This indicates to the host that the given
 *  given URL is invalid, and gives extra error information.
 */
char PROGMEM HTTP404Header[] = "HTTP/1.1 404 Not Found\r\n"
                               "Server: LUFA RNDIS\r\n"
                               "Connection: close\r\n"
							   "MIME-version: 1.0\r\n"
							   "Content-Type: text/plain\r\n\r\n"
							   "Error 404: File Not Found";

/** Default MIME type sent if no other MIME type can be determined */
char PROGMEM DefaultMIMEType[] = "text/plain";

/** List of MIME types for each supported file extension - must be terminated with \ref END_OF_MIME_LIST entry. */
MIME_Type_t PROGMEM MIMETypes[] =
	{
		{.Extension = "htm", .MIMEType = "text/html"},
		{.Extension = "jpg", .MIMEType = "image/jpeg"},
		{.Extension = "gif", .MIMEType = "image/gif"},
		{.Extension = "bmp", .MIMEType = "image/bmp"},
		{.Extension = "png", .MIMEType = "image/png"},
		{.Extension = "exe", .MIMEType = "application/octet-stream"},
		{.Extension = "gz",  .MIMEType = "application/x-gzip"},
		{.Extension = "ico", .MIMEType = "image/x-icon"},
		{.Extension = "zip", .MIMEType = "application/zip"},
		{.Extension = "pdf", .MIMEType = "application/pdf"},
	};

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

	if (uip_aborted() || uip_timedout() || uip_closed())
	{
		/* Check if the open file needs to be closed */
		if (AppState->FileOpen)
		{
			f_close(&AppState->FileHandle);
			AppState->FileOpen = false;
		}

		AppState->PrevState    = WEBSERVER_STATE_Closed;
		AppState->CurrentState = WEBSERVER_STATE_Closed;

		return;
	}
	else if (uip_connected())
	{
		/* New connection - initialize connection state values */
		AppState->PrevState    = WEBSERVER_STATE_OpenRequestedFile;
		AppState->CurrentState = WEBSERVER_STATE_OpenRequestedFile;
		AppState->FileOpen     = false;
	}
	else if (uip_rexmit())
	{
		/* Re-try last state */
		AppState->CurrentState = AppState->PrevState;
	}
	
	switch (AppState->CurrentState)
	{
		case WEBSERVER_STATE_OpenRequestedFile:
			/* Wait for the packet containing the request header */
			if (uip_newdata())
			{
				char* RequestToken = strtok(AppData, " ");
			
				/* Must be a GET request, abort otherwise */
				if (strcmp(RequestToken, "GET") != 0)
				{
					uip_abort();
					break;
				}
		
				char* RequestedFileName = strtok(NULL, " ");
				
				/* If the requested filename has more that just the leading '/' path in it, copy it over */
				if (strlen(RequestedFileName) > 1)
				  strncpy(AppState->FileName, &RequestedFileName[1], (sizeof(AppState->FileName) - 1));
				else
				  strcpy(AppState->FileName, "index.htm");

				/* Ensure filename is null-terminated */
				AppState->FileName[(sizeof(AppState->FileName) - 1)] = 0x00;
				
				/* Try to open the file from the Dataflash disk */
				AppState->FileOpen       = (f_open(&AppState->FileHandle, AppState->FileName, FA_OPEN_EXISTING | FA_READ) == FR_OK);
				AppState->CurrentFilePos = 0;

				AppState->PrevState    = WEBSERVER_STATE_OpenRequestedFile;
				AppState->CurrentState = WEBSERVER_STATE_SendResponseHeader;
			}

			break;
		case WEBSERVER_STATE_SendResponseHeader:
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
			
			AppState->PrevState    = WEBSERVER_STATE_SendResponseHeader;
			AppState->CurrentState = WEBSERVER_STATE_SendMIMETypeHeader;
			break;
		case WEBSERVER_STATE_SendMIMETypeHeader:
			/* File must have been found and opened for MIME header to be sent */
			if (AppState->FileOpen)
			{
				char* Extension = strpbrk(AppState->FileName, ".");
				
				/* Check to see if a file extension was found for the requested filename */
				if (Extension != NULL)
				{
					/* Look through the MIME type list, copy over the required MIME type if found */
					for (int i = 0; i < (sizeof(MIMETypes) / sizeof(MIMETypes[0])); i++)
					{
						if (strcmp_P(&Extension[1], MIMETypes[i].Extension) == 0)
						{
							AppDataSize = strlen_P(MIMETypes[i].MIMEType);
							strncpy_P(AppData, MIMETypes[i].MIMEType, AppDataSize);						
							break;
						}
					} 
				}

				/* Check if a MIME type was found and copied to the output buffer */
				if (!(AppDataSize))
				{
					/* MIME type not found - copy over the default MIME type */
					AppDataSize = strlen_P(DefaultMIMEType);
					strncpy_P(AppData, DefaultMIMEType, AppDataSize);				
				}
				
				/* Add the end-of line terminator and end-of-headers terminator after the MIME type */
				strncpy(&AppData[AppDataSize], "\r\n\r\n", sizeof("\r\n\r\n"));
				AppDataSize += (sizeof("\r\n\r\n") - 1);
			}
				
			AppState->PrevState    = WEBSERVER_STATE_SendMIMETypeHeader;
			AppState->CurrentState = WEBSERVER_STATE_SendData;				
			break;
		case WEBSERVER_STATE_SendData:
			/* If end of file/file not open, progress to the close state */
			if (!(AppState->FileOpen) && !(uip_rexmit()))
			{
				f_close(&AppState->FileHandle);
				uip_close();

				AppState->PrevState    = WEBSERVER_STATE_Closed;
				AppState->CurrentState = WEBSERVER_STATE_Closed;
				break;
			}

			uint16_t MaxSegSize = uip_mss();
			
			/* Return file pointer to the last ACKed position */
			f_lseek(&AppState->FileHandle, AppState->CurrentFilePos);

			/* Read the next chunk of data from the open file */
			f_read(&AppState->FileHandle, AppData, MaxSegSize, &AppDataSize);

			/* If we are not re-transmitting a lost segment, advance file position */
			if (uip_acked() && !(uip_rexmit()))
			{
				AppState->FileOpen = (AppDataSize > 0);
				AppState->CurrentFilePos += AppDataSize;
			}
			
			/* Stay in the SendData state if retransmission is required until all data sent */
			AppState->PrevState = WEBSERVER_STATE_SendData;

			break;
	}

	/* If data has been loaded into the application buffer by the server, send it to the client */
	if (AppDataSize)
	  uip_send(AppData, AppDataSize);
}
