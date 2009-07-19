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
 *  Main source file for the TestApp demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "TestApp.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	SetupHardware();
	
	puts_P(PSTR(ESC_FG_CYAN "LUFA Demo running.\r\n" ESC_FG_WHITE));

	for (;;)
	{
		CheckJoystick();
		CheckButton();
		CheckTemperature();

		/* Clear output-compare flag (logic 1 clears the flag) */
		TIFR0 |= (1 << OCF0A);
		
		USB_USBTask();
	}
}

void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
	
	/* Hardware initialization */
	SerialStream_Init(9600, false);
	ADC_Init(ADC_SINGLE_CONVERSION | ADC_PRESCALE_64);
	Temperature_Init();
	Joystick_Init();
	LEDs_Init();
	Buttons_Init();
	
	/* Millisecond timer initialization */
	OCR0A  = 0x7D;
	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS01) | (1 << CS00));
}

/** Task responsible for checking the joystick position, and displaying the joystick position onto the
 *  board LEDs.
 */
void CheckJoystick(void)
{
	uint8_t JoyStatus_LCL = Joystick_GetStatus();
	uint8_t LEDMask       = LEDS_NO_LEDS;
		
	if (JoyStatus_LCL & JOY_UP)
	  LEDMask |= LEDS_LED1;
		
	if (JoyStatus_LCL & JOY_DOWN)
	  LEDMask |= LEDS_LED2;

	if (JoyStatus_LCL & JOY_LEFT)
	  LEDMask |= LEDS_LED3;

	if (JoyStatus_LCL & JOY_RIGHT)
	  LEDMask |= LEDS_LED4;
			
	if (JoyStatus_LCL & JOY_PRESS)
	  LEDMask  = LEDS_ALL_LEDS;

	LEDs_SetAllLEDs(LEDMask);
}

/** Task responsible for checking the current temperature via the temperature sensor mounted on the
 *  board, and displaying it through the serial USART.
 */
void CheckTemperature(void)
{
	static uint16_t MSElapsed = 0;

	if (TIFR0 & (1 << OCF0A))
	  MSElapsed++;

	/* Task runs every 10000 ticks, 10 seconds for this demo */
	if (MSElapsed == 1000)
	{
		printf_P(PSTR("Current temperature: %d Degrees Celcius\r\n\r\n"),
		         (int8_t)Temperature_GetTemperature());

		MSElapsed = 0;
	}	
}

/** Task responsible for checking the board's first button' position, and start-stopping other tasks and the USB
 *  interface in response to user joystick movements.
 */
void CheckButton(void)
{
	static uint16_t DebounceMSElapsed = 0;
	static bool     IsPressed;
	
	if (TIFR0 & (1 << OCF0A))
	  DebounceMSElapsed++;

	if (Buttons_GetStatus() & BUTTONS_BUTTON1)
	{
		if (!(IsPressed) && (DebounceMSElapsed == 100))
		{
			IsPressed = true;

			if (USB_IsInitialized == true)
			{
				USB_ShutDown();
				puts_P(PSTR(ESC_FG_YELLOW "USB Power Off.\r\n" ESC_FG_WHITE));
			}
			else
			{
				puts_P(PSTR(ESC_FG_YELLOW "USB Power On.\r\n" ESC_FG_WHITE));				
				USB_Init(USB_MODE_UID, USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL);
			}
		}
	}
    else
    {
		DebounceMSElapsed = 0;
		IsPressed = false;
	}
}
