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
 
/** \ingroup Group_USB
 *  @defgroup Group_StreamCallbacks Endpoint and Pipe Stream Callbacks
 *
 *  Macros and enums for the stream callback routines. This module contains the code required to easily set up
 *  stream callback functions which can be used to force early abort of a stream read/write process. Each callback
 *  should take no arguments, and return a value from the \ref StreamCallback_Return_ErrorCodes_t enum.
 *
 *  @{
 */
 
#ifndef __STREAMCALLBACK_H__
#define __STREAMCALLBACK_H__

	/* Public Interface - May be used in end-application: */
		/* Macros: */
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

		/* Type Defines: */
			/** Type define for a Stream Callback function (function taking no arguments and retuning a
			 *  uint8_t value).
			 *
			 *  \see \ref STREAM_CALLBACK macro for more details
			 */
			typedef uint8_t (* const StreamCallbackPtr_t)(void);
		
#endif

/** @} */
