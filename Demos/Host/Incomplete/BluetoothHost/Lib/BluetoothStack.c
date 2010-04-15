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

#include "BluetoothStack.h"

/** Bluetooth device connection information structure. Once connected to a remote device, this structure tracks the
 *  connection state of the individual L2CAP channels.
 */
Bluetooth_Connection_t Bluetooth_Connection = {IsConnected: false};

/** Bluetooth configuration structure. This structure configures the bluetooth stack's user alterable settings. */
Bluetooth_Device_t Bluetooth_DeviceConfiguration =
	{
		Class:   (DEVICE_CLASS_SERVICE_CAPTURING | DEVICE_CLASS_MAJOR_COMPUTER | DEVICE_CLASS_MINOR_COMPUTER_PALM),
		PINCode: "0000",
		Name:    "LUFA Bluetooth Demo"
	};

/** Bluetooth stack initialization function. This function must be called once to initialize the Bluetooth stack,
 *  ready for connection to remote devices.
 *
 *  \note This function only begins the initialization process; the stack is initialized as the main Bluetooth stack
 *        management task is repeatedly called. The initialization process ends when the \ref Bluetooth_HCIProcessingState
 *        global enters the Bluetooth_ProcessEvents state.
 */
void Bluetooth_Stack_Init(void)
{
	/* Reset the HCI state machine - this will eventually reset the adapter and stack when the Bluetooth stack task is called */
	Bluetooth_HCIProcessingState = Bluetooth_Init;
}

/** Bluetooth stack management task. This task must be repeatedly called to maintain the Bluetooth stack and any connection
 *  to remote Bluetooth devices, including both the HCI control layer and the ACL channel layer.
 */
void Bluetooth_Stack_USBTask(void)
{
	Bluetooth_HCITask();
	Bluetooth_ACLTask();
}

/** Retrieves the channel information structure with the given local or remote channel number from the channel list.
 *
 *  \param[in] ChannelNumber          Channel number to search for in the channel list
 *  \param[in] SearchByRemoteChannel  Indicated whether to search for a channel information structure by the given remote channel
 *                                    or local channel number
 *
 *  \return Pointer to the matching channel information structure in the channel table if found, NULL otherwise
 */
Bluetooth_Channel_t* Bluetooth_GetChannelData(uint16_t ChannelNumber, bool SearchByRemoteChannel)
{
	for (uint8_t i = 0; i < BLUETOOTH_MAX_OPEN_CHANNELS; i++)
	{
		Bluetooth_Channel_t* ChannelData = &Bluetooth_Connection.Channels[i];
	
		/* Fetch the channel number that is to be matched against from the current channel information struct */
		uint16_t SearchChannelNumber = (SearchByRemoteChannel) ? ChannelData->RemoteNumber : ChannelData->LocalNumber;
	
		if (SearchChannelNumber == ChannelNumber)
		  return ChannelData;
	}

	return NULL;
}
