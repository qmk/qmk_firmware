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
 *  Header file for ProtocolDecoders.c.
 */

#ifndef _PROTOCOL_DECODERS_H_
#define _PROTOCOL_DECODERS_H_

	/* Includes: */
		#include <avr/io.h>
		
		#include <LUFA/Drivers/USB/Class/RNDIS.h>
		#include <LUFA/Drivers/Peripheral/SerialStream.h>
		
		#include "EthernetProtocols.h"
		#include "Ethernet.h"
		
	/* Function Prototypes: */
		void DecodeEthernetFrameHeader(Ethernet_Frame_Info_t* FrameINData);
		void DecodeARPHeader(void* InDataStart);
		void DecodeIPHeader(void* InDataStart);
		void DecodeICMPHeader(void* InDataStart);
		void DecodeTCPHeader(void* InDataStart);
		void DecodeUDPHeader(void* InDataStart);
		void DecodeDHCPHeader(void* InDataStart);

#endif
