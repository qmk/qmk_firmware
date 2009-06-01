/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Denver Gingerich (denver [at] ossguy [dot] com)
      Based on code by Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 
#include "Keyboard.h"

USB_ClassInfo_HID_t Keyboard_HID_Interface =
    {
        .InterfaceNumber         = 0,

        .ReportINEndpointNumber  = KEYBOARD_EPNUM,
        .ReportINEndpointSize    = KEYBOARD_EPSIZE,

        .ReportOUTEndpointNumber = KEYBOARD_LEDS_EPNUM,
        .ReportOUTEndpointSize   = KEYBOARD_EPSIZE,
        
		.ReportBufferSize        = sizeof(USB_KeyboardReport_Data_t),

        .IdleCount               = 500,
    };

int main(void)
{
    SetupHardware();

    LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
    
    for (;;)
    {
        USB_HID_USBTask(&Keyboard_HID_Interface);
        USB_USBTask();
    }
}

void SetupHardware()
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    /* Hardware Initialization */
    Joystick_Init();
    LEDs_Init();
    Buttons_Init();
    USB_Init();
}

void EVENT_USB_Connect(void)
{
    LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

void EVENT_USB_Disconnect(void)
{
    LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

void EVENT_USB_ConfigurationChanged(void)
{
    LEDs_SetAllLEDs(LEDMASK_USB_READY);

    if (!(USB_HID_ConfigureEndpoints(&Keyboard_HID_Interface)))
      LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

void EVENT_USB_UnhandledControlPacket(void)
{
    USB_HID_ProcessControlPacket(&Keyboard_HID_Interface);
}

void EVENT_USB_StartOfFrame(void)
{
    USB_HID_RegisterStartOfFrame(&Keyboard_HID_Interface);
}

uint16_t CALLBACK_USB_HID_CreateNextHIDReport(USB_ClassInfo_HID_t* HIDInterfaceInfo, void* ReportData)
{
    USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;
    
    uint8_t JoyStatus_LCL    = Joystick_GetStatus();
    uint8_t ButtonStatus_LCL = Buttons_GetStatus();

    if (JoyStatus_LCL & JOY_UP)
      KeyboardReport->KeyCode[0] = 0x04; // A
    else if (JoyStatus_LCL & JOY_DOWN)
      KeyboardReport->KeyCode[0] = 0x05; // B

    if (JoyStatus_LCL & JOY_LEFT)
      KeyboardReport->KeyCode[0] = 0x06; // C
    else if (JoyStatus_LCL & JOY_RIGHT)
      KeyboardReport->KeyCode[0] = 0x07; // D

    if (JoyStatus_LCL & JOY_PRESS)
      KeyboardReport->KeyCode[0] = 0x08; // E
      
    if (ButtonStatus_LCL & BUTTONS_BUTTON1)
      KeyboardReport->KeyCode[0] = 0x09; // F
      
    return sizeof(USB_KeyboardReport_Data_t);
}

void CALLBACK_USB_HID_ProcessReceivedHIDReport(USB_ClassInfo_HID_t* HIDInterfaceInfo, void* ReportData, uint16_t ReportSize)
{
    uint8_t  LEDMask   = LEDS_NO_LEDS;
    uint8_t* LEDReport = (uint8_t*)ReportData;

    if (*LEDReport & 0x01) // NUM Lock
      LEDMask |= LEDS_LED1;
    
    if (*LEDReport & 0x02) // CAPS Lock
      LEDMask |= LEDS_LED3;

    if (*LEDReport & 0x04) // SCROLL Lock
      LEDMask |= LEDS_LED4;
      
    LEDs_SetAllLEDs(LEDMask);
}
