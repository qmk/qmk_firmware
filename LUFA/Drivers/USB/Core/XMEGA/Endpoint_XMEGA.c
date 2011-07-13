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

#define  __INCLUDE_FROM_USB_DRIVER
#include "../USBMode.h"

#if defined(USB_CAN_BE_DEVICE)

#include "../Endpoint.h"

#if !defined(FIXED_CONTROL_ENDPOINT_SIZE)
uint8_t USB_Device_ControlEndpointSize = ENDPOINT_CONTROLEP_DEFAULT_SIZE;
#endif

bool Endpoint_ConfigureEndpoint_Prv(const uint8_t Number,
                                    const uint8_t UECFG0XData,
                                    const uint8_t UECFG1XData)
{
	// TODO
}

void Endpoint_ClearEndpoints(void)
{
	// TODO
}

void Endpoint_ClearStatusStage(void)
{
	// TODO
}

#if !defined(CONTROL_ONLY_DEVICE)
uint8_t Endpoint_WaitUntilReady(void)
{
	return 0; // TODO
}
#endif

#endif

