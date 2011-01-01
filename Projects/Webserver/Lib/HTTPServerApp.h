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
 *
 *  Header file for HTTPServerApp.c.
 */

#ifndef _HTTPSERVER_APP_H_
#define _HTTPSERVER_APP_H_

	/* Includes: */
		#include <avr/pgmspace.h>
		#include <string.h>

		#include <LUFA/Version.h>

		#include <uip.h>
		#include <ff.h>

	/* Enums: */
		/** States for each HTTP connection to the webserver. */
		enum Webserver_States_t
		{
			WEBSERVER_STATE_OpenRequestedFile, /**< Currently opening requested file */
			WEBSERVER_STATE_SendResponseHeader, /**< Currently sending HTTP response headers to the client */
			WEBSERVER_STATE_SendData, /**< Currently sending HTTP page data to the client */
			WEBSERVER_STATE_Closing, /**< Ready to close the connection to the client */
			WEBSERVER_STATE_Closed, /**< Connection closed after all data sent */
		};

	/* Type Defines: */
		/** Type define for a MIME type handler. */
		typedef struct
		{
			char* Extension; /**< File extension (no leading '.' character) */
			char* MIMEType;  /**< Appropriate MIME type to send when the extension is encountered */
		} MIME_Type_t;

	/* Macros: */
		/** TCP listen port for incoming HTTP traffic. */
		#define HTTP_SERVER_PORT  80

	/* Function Prototypes: */
		void HTTPServerApp_Init(void);
		void HTTPServerApp_Callback(void);

		#if defined(INCLUDE_FROM_HTTPSERVERAPP_C)
			static void HTTPServerApp_OpenRequestedFile(void);
			static void HTTPServerApp_SendResponseHeader(void);
			static void HTTPServerApp_SendData(void);
		#endif

#endif

