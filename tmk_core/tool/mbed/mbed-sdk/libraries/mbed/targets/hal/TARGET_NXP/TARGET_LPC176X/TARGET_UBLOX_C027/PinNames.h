/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

#define PORT_SHIFT  5

typedef enum {
    // LPC Pin Names
    P0_0 = LPC_GPIO0_BASE,
          P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, P0_8, P0_9, P0_10, P0_11, P0_12, P0_13, P0_14, P0_15, P0_16, P0_17, P0_18, P0_19, P0_20, P0_21, P0_22, P0_23, P0_24, P0_25, P0_26, P0_27, P0_28, P0_29, P0_30, P0_31,
    P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, P1_8, P1_9, P1_10, P1_11, P1_12, P1_13, P1_14, P1_15, P1_16, P1_17, P1_18, P1_19, P1_20, P1_21, P1_22, P1_23, P1_24, P1_25, P1_26, P1_27, P1_28, P1_29, P1_30, P1_31,
    P2_0, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7, P2_8, P2_9, P2_10, P2_11, P2_12, P2_13, P2_14, P2_15, P2_16, P2_17, P2_18, P2_19, P2_20, P2_21, P2_22, P2_23, P2_24, P2_25, P2_26, P2_27, P2_28, P2_29, P2_30, P2_31,
    P3_0, P3_1, P3_2, P3_3, P3_4, P3_5, P3_6, P3_7, P3_8, P3_9, P3_10, P3_11, P3_12, P3_13, P3_14, P3_15, P3_16, P3_17, P3_18, P3_19, P3_20, P3_21, P3_22, P3_23, P3_24, P3_25, P3_26, P3_27, P3_28, P3_29, P3_30, P3_31,
    P4_0, P4_1, P4_2, P4_3, P4_4, P4_5, P4_6, P4_7, P4_8, P4_9, P4_10, P4_11, P4_12, P4_13, P4_14, P4_15, P4_16, P4_17, P4_18, P4_19, P4_20, P4_21, P4_22, P4_23, P4_24, P4_25, P4_26, P4_27, P4_28, P4_29, P4_30, P4_31,

    // Arduino Pin Names
    
    // PIN header connector
	// for standard-based form factor with expansion board
	// -----------------------------------------------------------
	// PMW  = Pulswidth Modulator
	// EINT = External Interrupt
	// AOUT = Analog Output
 
	// Analog Ports (A0-A5)
	A0 = P0_23, // I2S_CLK
	A1 = P0_24, // I2S_WS
	A2 = P0_25, // I2S_SDA
	A3 = P0_26, // AOUT
	A4 = P1_30, //
	A5 = P1_31, //
	// Digital Port (D0-D7)
	D0 = P4_29, // TXD
	D1 = P4_28, // RXD
	D2 = P2_13, // EINT
	D3 = P2_0,  // PWM
	D4 = P2_12, // EINT
	D5 = P2_1,  // PWM
	D6 = P2_2,  // PWM
	D7 = P2_11, // EINT
	// Digital Port (D8-D13)
	D8 = P2_4,   // PWM  
	D9 = P2_3,   // PWM
	D10 = P1_21, // PWM  SSEL
	D11 = P1_24, // PWM  MOSI
	D12 = P1_23, // PWM  MISO
	D13 = P1_20, // PWM  SCK
	// GND
	// AREF
	SDA = P0_0,
	D14 = SDA,
	SCL = P0_1,
	D15 = SCL,
    
	// I2C (shared with LISA/SARA)
	GPSSDA = P0_27,
	GPSSCL = P0_28,
	// UART 
	GPSTXD = P0_10,
	GPSRXD = P0_11,
	// Control
	GPSRST = P1_18, // Reset (input to GPS, active low)
	GPSPPS = P1_19, // 1PPS Timepulse (output from GPS)
	GPSINT = P1_22, // Interrupt (input to GPS)
	GPSEN  = P1_29, // Supply Control (high = enabled)
 
	// u-blox LISA/SARA cellular modem
	// http://www.u-blox.com/wireless-modules.html
	// -----------------------------------------------------------
	// UART (LPC1768 = DTE, LISA/SARA = DCE)
	MDMTXD = P0_15, // Transmit Data
	MDMRXD = P0_16, // Receive Data
	MDMCTS = P0_17, // Clear to Send
	MDMDCD = P0_18, // Data Carrier Detect
	MDMDSR = P0_19, // Data Set Ready
	MDMDTR = P0_20, // Data Terminal Ready (set high or use handshake)
	MDMRI  = P0_21, // Ring Indicator
	MDMRTS = P0_22, // Request to Send (set high or use handshake)
	
	// USB (not available on C27-G35)
	MDMUSBDP  = P0_29, // USB D+
	MDMUSBDN  = P0_30, // USB D-
	MDMUSBCON = P2_9,  // USB Connect
	MDMUSBDET = P0_7,  // USB Detect (n/a on REV.A board)
	// Control 
	MDMEN     = P2_5,  // Supply Control (high = enabled)
	MDMPWRON  = P2_6,  // 
	MDMGPIO1  = P2_7,  // GPIO1, Network status
	MDMRST    = P2_8,  // Reset (active low, set as open drain!)
	MDMLVLOE  = P0_9,  // Serial/GPIO Level Shifter Output Enable (n/a on REV.A board)
	MDMILVLOE = P0_8,  // I2C Level Shifter Output Enable (n/a on REV.A board)
 
	// CAN (TJA1040)
	// -----------------------------------------------------------
	CANRD = P0_4,
	CANTD = P0_5,
	CANS  = P0_6,  // standby (low=normal, high=standby/rxonly)
 
	// Ethernet (DP83848)
	// -----------------------------------------------------------
	ETHTXD0   = P1_0,
	ETHTXD1   = P1_1,
	ETHTXEN   = P1_4,
	ETHCRS    = P1_8,
	ETHRXD0   = P1_9,
	ETHRXD1   = P1_10,
	ETHRXEN   = P1_14,
	ETHREFCLK = P1_15,
	ETHMDC    = P1_16,
	ETHMDIO   = P1_17,
	ETHOSCEN  = P1_27,
	ETHRST    = P1_28,
	ETHLINK   = P1_25, // LED_LINK 
	ETHSPEED  = P1_26, // LED_SPEED
 
	// ISP port
	// -----------------------------------------------------------
	ISP = P2_10,
    
    // Other mbed Pin Names
    LED     = P3_25,
    LED1    = LED,
    LED2    = LED,
    LED3    = LED,
    LED4    = LED,
    LED_RED = LED,
    
   	// mbed / debug IF (LPC11)
	// -----------------------------------------------------------
	// Serial Port
	USBTX  = P0_2,
    USBRX  = P0_3,
	USBTXD = USBTX, // identical USBTX
	USBRXD = USBRX, // identical USBRX

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

typedef enum {
    PullUp = 0,
    PullDown = 3,
    PullNone = 2,
    Repeater = 1,
    OpenDrain = 4,
    PullDefault = PullDown
} PinMode;

// version of PINCON_TypeDef using register arrays
typedef struct {
  __IO uint32_t PINSEL[11];
       uint32_t RESERVED0[5];
  __IO uint32_t PINMODE[10];
  __IO uint32_t PINMODE_OD[5];
} PINCONARRAY_TypeDef;

#define PINCONARRAY ((PINCONARRAY_TypeDef *)LPC_PINCON_BASE)

//Additional C027 stuff
#define GPSADR      (66<<1) // GPS I2C Address
#define GPSBAUD     9600    // Default GPS Baud Rate
#define MDMBAUD     115200  // Default Modem Baud Rate

#ifdef __cplusplus
}
#endif

#endif
