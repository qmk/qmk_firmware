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
 *  Header containing macros for possible PIMA commands. Refer to the PIMA standard
 *  documentation for more information on each PIMA command.
 */

#ifndef _PIMA_CODES_H_

	/* Macros: */
		#define PIMA_OPERATION_GETDEVICEINFO         0x1001
		#define PIMA_OPERATION_OPENSESSION           0x1002
		#define PIMA_OPERATION_CLOSESESSION          0x1003
		
		#define PIMA_RESPONSE_OK                     0x2001
		#define PIMA_RESPONSE_GENERALERROR           0x2002
		#define PIMA_RESPONSE_SESSIONNOTOPEN         0x2003
		#define PIMA_RESPONSE_INVALIDTRANSACTIONID   0x2004
		#define PIMA_RESPONSE_OPERATIONNOTSUPPORTED  0x2005
		#define PIMA_RESPONSE_PARAMETERNOTSUPPORTED  0x2006

#endif
