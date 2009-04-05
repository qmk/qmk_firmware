/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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
 *  Macros and enums for the stream callback routines in Endpoint.h and Pipe.c. This module contains the
 *  code required to easily set up stream callback functions which can be used to force early abort of a
 *  stream read/write process.
 */
 
#ifndef __STREAMCALLBACK_H__
#define __STREAMCALLBACK_H__

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Creates a prototype for or begins a stream callback routine. Stream callback routines are small
			 *  routines which are executed during stream read or writes (if the callback-enabled versions of
			 *  these functions are used) which allow the user application to abort the transfer when certain
			 *  arbitrary conditions are met.
			 *
			 *  Stream callback functions should return a value from the StreamCallback_Return_ErrorCodes_t
			 *  enum.
			 *
			 *  Usage Example (Device Endpoint, but applicable for Host Pipes also):
			 *  \code
			 *  STREAM_CALLBACK(GlobalNotSet); // Callback Prototype
			 *
			 *  STREAM_CALLBACK(GlobalNotSet)
			 *  {
			 *     if (MyGlobal == false)
			 *         return ENDPOINT_STREAMCALLBACK_Continue;
			 *     else
			 *         return ENDPOINT_STREAMCALLBACK_Abort;
			 *  }
			 *
			 *  //...
			 *  // Inside some routine:
			 *  if (Endpoint_Write_Stream_LE(DataBuffer, sizeof(DataBuffer), GlobalNotSet) == 
			 *                               ENDPOINT_RWSTREAM_ERROR_CallbackAborted)
			 *  {
			 *      // Do something when the callback aborted the transfer early
			 *  }
			 *  \endcode
			 */
			#define STREAM_CALLBACK(name) uint8_t name (void)

			/** Used with the Endpoint and Pipe stream functions as the callback function parameter, indicating that the stream
			 *  call has no callback function to be called between USB packets.
			 */
			#define NO_STREAM_CALLBACK    NULL
			
		/* Enums: */
			/** Enum for the possible error return codes of a stream callback function */
			enum StreamCallback_Return_ErrorCodes_t
			{
				STREAMCALLBACK_Continue            = 0, /**< Continue sending or receiving the stream. */
				STREAMCALLBACK_Abort               = 1, /**< Abort the stream send or receiving process. */
			};
			
#endif
