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
 *  Main module for the Bluetooth stack. This module contains the overall Bluetooth
 *  stack state variables and the main Bluetooth stack management functions.
 */

#include "BluetoothStack.h"

/** Bluetooth device connection information structure. Once connected to a remote device, this structure tracks the
 *  connection state of the individual L2CAP channels.
 */
Bluetooth_Connection_t Bluetooth_Connection = { IsConnected: false };

/** Bluetooth device state information structure. This structure contains details on the current Bluetooth stack
 *  state.
 */
Bluetooth_Stack_State_t Bluetooth_State     = { IsInitialized: false };

/** Bluetooth stack initialization function. This function must be called once to initialize the Bluetooth stack,
 *  ready for connection to remote devices.
 *
 *  \note This function only begins the initialization process; the stack is initialized as the main Bluetooth stack
 *        management task is repeatedly called. The initialization process ends when the IsInitialized element of the
 *        \ref Bluetooth_State structure becomes true and the \ref Bluetooth_StackInitialized() callback fires.
 */
void Bluetooth_Stack_Init(void)
{
	/* Reset the HCI state machine - this will reset the adapter and stack when the Bluetooth stack task is called */
	Bluetooth_State.CurrentHCIState = Bluetooth_Init;
	Bluetooth_State.NextHCIState    = Bluetooth_Init;
}

/** Bluetooth stack management task. This task must be repeatedly called to maintain the Bluetooth stack and any connection
 *  to remote Bluetooth devices, including both the HCI control layer and the ACL channel layer.
 */
void Bluetooth_Stack_USBTask(void)
{
	if (USB_HostState != HOST_STATE_Configured)
	  return;

	Bluetooth_HCITask();
	Bluetooth_ACLTask();
}

