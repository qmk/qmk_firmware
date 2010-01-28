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
			WEBSERVER_STATE_OpenRequestedFile, /** Currently opening requested file */
			WEBSERVER_STATE_SendHeaders, /**< Currently sending HTTP headers to the client */
			WEBSERVER_STATE_SendData,    /**< Currently sending HTTP page data to the client */
			WEBSERVER_STATE_Closed,      /**< Connection closed after all data sent */
		};
	
	/* Macros: */
		/** TCP listen port for incomming HTTP traffic */
		#define HTTP_SERVER_PORT  80

	/* Function Prototypes: */
		void WebserverApp_Init(void);
		void WebserverApp_Callback(void);
		
#endif
