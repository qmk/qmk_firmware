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
 
#define  INCLUDE_FROM_HTTPSERVERAPP_C
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

/** List of MIME types for each supported file extension. */
MIME_Type_t PROGMEM MIMETypes[] =
	{
		{.Extension = "htm", .MIMEType = "text/html"},
		{.Extension = "jpg", .MIMEType = "image/jpeg"},
		{.Extension = "gif", .MIMEType = "image/gif"},
		{.Extension = "bmp", .MIMEType = "image/bmp"},
		{.Extension = "png", .MIMEType = "image/png"},
		{.Extension = "ico", .MIMEType = "image/x-icon"},
		{.Extension = "exe", .MIMEType = "application/octet-stream"},
		{.Extension = "gz",  .MIMEType = "application/x-gzip"},
		{.Extension = "zip", .MIMEType = "application/zip"},
		{.Extension = "pdf", .MIMEType = "application/pdf"},
	};

/** FAT Fs structure to hold the internal state of the FAT driver for the dataflash contents. */
FATFS DiskFATState;


/** Initialization function for the simple HTTP webserver. */
void HTTPServerApp_Init(void)
{
	/* Listen on port 80 for HTTP connections from hosts */
	uip_listen(HTONS(HTTP_SERVER_PORT));
	
	/* Mount the dataflash disk via FatFS */
	f_mount(0, &DiskFATState);
}

/** uIP stack application callback for the simple HTTP webserver. This function must be called each time the
 *  TCP/IP stack needs a TCP packet to be processed.
 */
void HTTPServerApp_Callback(void)
{
	uip_tcp_appstate_t* const AppState = &uip_conn->appstate;

	if (uip_aborted() || uip_timedout() || uip_closed())
	{
		/* Connection is being terminated for some reason - close file handle */
		f_close(&AppState->FileHandle);
		AppState->FileOpen = false;
		
		/* Lock to the closed state so that no further processing will occur on the connection */
		AppState->CurrentState  = WEBSERVER_STATE_Closed;
		AppState->NextState     = WEBSERVER_STATE_Closed;
	}

	if (uip_connected())
	{
		/* New connection - initialize connection state values */
		AppState->CurrentState  = WEBSERVER_STATE_OpenRequestedFile;
		AppState->NextState     = WEBSERVER_STATE_OpenRequestedFile;
		AppState->FileOpen      = false;
		AppState->ACKedFilePos  = 0;
		AppState->SentChunkSize = 0;
	}

	if (uip_acked())
	{
		/* Add the amount of ACKed file data to the total sent file bytes counter */
		AppState->ACKedFilePos += AppState->SentChunkSize;

		/* Progress to the next state once the current state's data has been ACKed */
		AppState->CurrentState = AppState->NextState;
	}

	if (uip_rexmit() || uip_acked() || uip_newdata() || uip_connected() || uip_poll())
	{
		switch (AppState->CurrentState)
		{
			case WEBSERVER_STATE_OpenRequestedFile:
				HTTPServerApp_OpenRequestedFile();
				break;
			case WEBSERVER_STATE_SendResponseHeader:
				HTTPServerApp_SendResponseHeader();
				break;
			case WEBSERVER_STATE_SendMIMETypeHeader:
				HTTPServerApp_SendMIMETypeHeader();	
				break;
			case WEBSERVER_STATE_SendData:
				HTTPServerApp_SendData();
				break;
			case WEBSERVER_STATE_Closing:
				uip_close();
				
				AppState->NextState = WEBSERVER_STATE_Closed;
				break;
		}		  
	}		
}

/** HTTP Server State handler for the Request Process state. This state manages the processing of incomming HTTP
 *  GET requests to the server from the receiving HTTP client.
 */
static void HTTPServerApp_OpenRequestedFile(void)
{
	uip_tcp_appstate_t* const AppState    = &uip_conn->appstate;
	char*               const AppData     = (char*)uip_appdata;
	
	/* No HTTP header received from the client, abort processing */
	if (!(uip_newdata()))
	  return;
	  
	char* RequestToken = strtok(AppData, " ");
			
	/* Must be a GET request, abort otherwise */
	if (strcmp(RequestToken, "GET") != 0)
	{
		uip_abort();
		return;
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
	AppState->FileOpen     = (f_open(&AppState->FileHandle, AppState->FileName, FA_OPEN_EXISTING | FA_READ) == FR_OK);

	/* Lock to the SendResponseHeader state until connection terminated */
	AppState->CurrentState = WEBSERVER_STATE_SendResponseHeader;
	AppState->NextState    = WEBSERVER_STATE_SendResponseHeader;
}

/** HTTP Server State handler for the HTTP Response Header Send state. This state manages the transmission of
 *  the HTTP response header to the receiving HTTP client.
 */
static void HTTPServerApp_SendResponseHeader(void)
{
	uip_tcp_appstate_t* const AppState    = &uip_conn->appstate;
	char*               const AppData     = (char*)uip_appdata;

	char*    HeaderToSend;
	uint16_t HeaderLength;

	/* Determine which HTTP header should be sent to the client */
	if (AppState->FileOpen)
	{
		HeaderToSend = HTTP200Header;
		AppState->NextState = WEBSERVER_STATE_SendMIMETypeHeader;
	}
	else
	{
		HeaderToSend = HTTP404Header;
		AppState->NextState = WEBSERVER_STATE_Closing;
	}

	/* Copy over the HTTP response header and send it to the receiving client */
	HeaderLength = strlen_P(HeaderToSend);
	strncpy_P(AppData, HeaderToSend, HeaderLength);
	uip_send(AppData, HeaderLength);
}

/** HTTP Server State handler for the MIME Header Send state. This state manages the transmission of the file
 *  MIME type header for the requested file to the receiving HTTP client.
 */
static void HTTPServerApp_SendMIMETypeHeader(void)
{
	uip_tcp_appstate_t* const AppState    = &uip_conn->appstate;
	char*               const AppData     = (char*)uip_appdata;

	char*    Extension        = strpbrk(AppState->FileName, ".");
	uint16_t MIMEHeaderLength = 0;

	/* Check to see if a file extension was found for the requested filename */
	if (Extension != NULL)
	{
		/* Look through the MIME type list, copy over the required MIME type if found */
		for (int i = 0; i < (sizeof(MIMETypes) / sizeof(MIMETypes[0])); i++)
		{
			if (strcmp_P(&Extension[1], MIMETypes[i].Extension) == 0)
			{
				MIMEHeaderLength = strlen_P(MIMETypes[i].MIMEType);
				strncpy_P(AppData, MIMETypes[i].MIMEType, MIMEHeaderLength);						
				break;
			}
		} 
	}

	/* Check if a MIME type was found and copied to the output buffer */
	if (!(MIMEHeaderLength))
	{
		/* MIME type not found - copy over the default MIME type */
		MIMEHeaderLength = strlen_P(DefaultMIMEType);
		strncpy_P(AppData, DefaultMIMEType, MIMEHeaderLength);
	}
	
	/* Add the end-of line terminator and end-of-headers terminator after the MIME type */
	strncpy(&AppData[MIMEHeaderLength], "\r\n\r\n", sizeof("\r\n\r\n"));
	MIMEHeaderLength += (sizeof("\r\n\r\n") - 1);
	
	/* Send the MIME header to the receiving client */
	uip_send(AppData, MIMEHeaderLength);
	
	/* When the MIME header is ACKed, progress to the data send stage */
	AppState->NextState = WEBSERVER_STATE_SendData;
}

/** HTTP Server State handler for the Data Send state. This state manages the transmission of file chunks
 *  to the receiving HTTP client.
 */
static void HTTPServerApp_SendData(void)
{
	uip_tcp_appstate_t* const AppState    = &uip_conn->appstate;
	char*               const AppData     = (char*)uip_appdata;

	/* Must determine the maximum segment size to determine maximum file chunk size */
	uint16_t MaxSegmentSize = uip_mss();

	/* Return file pointer to the last ACKed position */
	f_lseek(&AppState->FileHandle, AppState->ACKedFilePos);
	
	/* Read the next chunk of data from the open file */
	f_read(&AppState->FileHandle, AppData, MaxSegmentSize, &AppState->SentChunkSize);
	
	/* Send the next file chunk to the receiving client */
	uip_send(AppData, AppState->SentChunkSize);
			
	/* Check if we are at the last chunk of the file, if so next ACK should close the connection */
	AppState->NextState = (MaxSegmentSize != AppState->SentChunkSize) ? WEBSERVER_STATE_Closing : WEBSERVER_STATE_SendData;
}
