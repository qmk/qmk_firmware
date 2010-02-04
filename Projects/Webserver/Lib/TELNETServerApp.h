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
 *  Header file for TELNETServerApp.c.
 */

#ifndef _TELNETSERVER_APP_H_
#define _TELNETSERVER_APP_H_

	/* Includes: */
		#include <avr/pgmspace.h>
		#include <string.h>
		#include <stdio.h>
		
		#include <uip.h>
	
	/* Macros: */
		/** TCP listen port for incoming TELNET traffic */
		#define TELNET_SERVER_PORT  23
		
	/* Enums: */
		/** States for each TELNET connection to the server. */
		enum TELNET_States_t
		{
			TELNET_STATE_SendHeader, /**< Currently sending welcome header to the client */
			TELNET_STATE_SendMenu, /**< Currently sending the command list menu to the client */
			TELNET_STATE_GetCommand, /**< Currently waiting for a command from the client */
			TELNET_STATE_SendResponse, /**< Processing the issued command and sending a response */
		};	

	/* Function Prototypes: */
		void TELNETServerApp_Init(void);
		void TELNETServerApp_Callback(void);
		
		#if defined(INCLUDE_FROM_TELNETSERVERAPP_C)
			static void TELNETServerApp_DisplayTCPConnections(void);
		#endif
		
#endif
