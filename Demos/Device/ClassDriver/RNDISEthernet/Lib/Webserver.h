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
 *  Header file for Webserver.c.
 */

#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>

		#include <LUFA/Version.h>

		#include "TCP.h"

	/* Macros: */
		/** Maximum size of a HTTP response per transmission */
		#define HTTP_REPLY_BLOCK_SIZE     128

	/* Function Prototypes: */
		void Webserver_Init(void);
		void Webserver_ApplicationCallback(TCP_ConnectionState_t* const ConnectionState,
		                                   TCP_ConnectionBuffer_t* const Buffer);

#endif

