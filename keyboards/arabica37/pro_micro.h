/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/
#pragma once

#include <avr/pgmspace.h>

// Workaround for wrong definitions in "iom32u4.h".
// This should be fixed in the AVR toolchain.
#undef UHCON
#undef UHINT
#undef UHIEN
#undef UHADDR
#undef UHFNUM
#undef UHFNUML
#undef UHFNUMH
#undef UHFLEN
#undef UPINRQX
#undef UPINTX
#undef UPNUM
#undef UPRST
#undef UPCONX
#undef UPCFG0X
#undef UPCFG1X
#undef UPSTAX
#undef UPCFG2X
#undef UPIENX
#undef UPDATX
#undef TCCR2A
#undef WGM20
#undef WGM21
#undef COM2B0
#undef COM2B1
#undef COM2A0
#undef COM2A1
#undef TCCR2B
#undef CS20
#undef CS21
#undef CS22
#undef WGM22
#undef FOC2B
#undef FOC2A
#undef TCNT2
#undef TCNT2_0
#undef TCNT2_1
#undef TCNT2_2
#undef TCNT2_3
#undef TCNT2_4
#undef TCNT2_5
#undef TCNT2_6
#undef TCNT2_7
#undef OCR2A
#undef OCR2_0
#undef OCR2_1
#undef OCR2_2
#undef OCR2_3
#undef OCR2_4
#undef OCR2_5
#undef OCR2_6
#undef OCR2_7
#undef OCR2B
#undef OCR2_0
#undef OCR2_1
#undef OCR2_2
#undef OCR2_3
#undef OCR2_4
#undef OCR2_5
#undef OCR2_6
#undef OCR2_7

#define NUM_DIGITAL_PINS  30
#define NUM_ANALOG_INPUTS 12

#define TX_RX_LED_INIT  DDRD |= (1<<5), DDRB |= (1<<0)
#define TXLED0          PORTD |= (1<<5)
#define TXLED1          PORTD &= ~(1<<5)
#define RXLED0          PORTB |= (1<<0)
#define RXLED1          PORTB &= ~(1<<0)

static const uint8_t SDA = 2;
static const uint8_t SCL = 3;
#define LED_BUILTIN 13

// Map SPI port to 'new' pins D14..D17
static const uint8_t SS   = 17;
static const uint8_t MOSI = 16;
static const uint8_t MISO = 14;
static const uint8_t SCK  = 15;

// Mapping of analog pins as digital I/O
// A6-A11 share with digital pins
static const uint8_t ADC0 = 18;
static const uint8_t ADC1 = 19;
static const uint8_t ADC2 = 20;
static const uint8_t ADC3 = 21;
static const uint8_t ADC4 = 22;
static const uint8_t ADC5 = 23;
static const uint8_t ADC6 = 24;   // D4
static const uint8_t ADC7 = 25;   // D6
static const uint8_t ADC8 = 26;   // D8
static const uint8_t ADC9 = 27;   // D9
static const uint8_t ADC10 = 28;  // D10
static const uint8_t ADC11 = 29;  // D12

#define digitalPinToPCICR(p)    ((((p) >= 8 && (p) <= 11) || ((p) >= 14 && (p) <= 17) || ((p) >= A8 && (p) <= A10)) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) 0
#define digitalPinToPCMSK(p)    ((((p) >= 8 && (p) <= 11) || ((p) >= 14 && (p) <= 17) || ((p) >= A8 && (p) <= A10)) ? (&PCMSK0) : ((uint8_t *)0))
#define digitalPinToPCMSKbit(p) ( ((p) >= 8 && (p) <= 11) ? (p) - 4 : ((p) == 14 ? 3 : ((p) == 15 ? 1 : ((p) == 16 ? 2 : ((p) == 17 ? 0 : (p - A8 + 4))))))

//  __AVR_ATmega32U4__ has an unusual mapping of pins to channels
extern const uint8_t PROGMEM analog_pin_to_channel_PGM[];
#define analogPinToChannel(P)  ( pgm_read_byte( analog_pin_to_channel_PGM + (P) ) )

#define digitalPinToInterrupt(p) ((p) == 0 ? 2 : ((p) == 1 ? 3 : ((p) == 2 ? 1 : ((p) == 3 ? 0 : ((p) == 7 ? 4 : NOT_AN_INTERRUPT)))))

#ifdef ARDUINO_MAIN

// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEL ATMEGA32U4 / ARDUINO LEONARDO
//
// D0               PD2                 RXD1/INT2
// D1               PD3                 TXD1/INT3
// D2               PD1     SDA         SDA/INT1
// D3#              PD0     PWM8/SCL    OC0B/SCL/INT0
// D4       A6      PD4                 ADC8
// D5#              PC6     ???         OC3A/#OC4A
// D6#      A7      PD7     FastPWM     #OC4D/ADC10
// D7               PE6                 INT6/AIN0
//
// D8       A8      PB4                 ADC11/PCINT4
// D9#      A9      PB5     PWM16       OC1A/#OC4B/ADC12/PCINT5
// D10#     A10     PB6     PWM16       OC1B/0c4B/ADC13/PCINT6
// D11#             PB7     PWM8/16     0C0A/OC1C/#RTS/PCINT7
// D12      A11     PD6                 T1/#OC4D/ADC9
// D13#             PC7     PWM10       CLK0/OC4A
//
// A0       D18     PF7                 ADC7
// A1       D19     PF6                 ADC6
// A2       D20     PF5                 ADC5
// A3       D21     PF4                 ADC4
// A4       D22     PF1                 ADC1
// A5       D23     PF0                 ADC0
//
// New pins D14..D17 to map SPI port to digital pins
//
// MISO     D14     PB3                 MISO,PCINT3
// SCK      D15     PB1                 SCK,PCINT1
// MOSI     D16     PB2                 MOSI,PCINT2
// SS       D17     PB0                 RXLED,SS/PCINT0
//
// Connected LEDs on board for TX and RX
// TXLED    D24     PD5                 XCK1
// RXLED    D17     PB0
// HWB              PE2                 HWB

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    (uint16_t) &DDRB,
    (uint16_t) &DDRC,
    (uint16_t) &DDRD,
    (uint16_t) &DDRE,
    (uint16_t) &DDRF,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    (uint16_t) &PORTB,
    (uint16_t) &PORTC,
    (uint16_t) &PORTD,
    (uint16_t) &PORTE,
    (uint16_t) &PORTF,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    (uint16_t) &PINB,
    (uint16_t) &PINC,
    (uint16_t) &PIND,
    (uint16_t) &PINE,
    (uint16_t) &PINF,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
    PD, // D0 - PD2
    PD, // D1 - PD3
    PD, // D2 - PD1
    PD, // D3 - PD0
    PD, // D4 - PD4
    PC, // D5 - PC6
    PD, // D6 - PD7
    PE, // D7 - PE6

    PB, // D8 - PB4
    PB, // D9 - PB5
    PB, // D10 - PB6
    PB, // D11 - PB7
    PD, // D12 - PD6
    PC, // D13 - PC7

    PB, // D14 - MISO - PB3
    PB, // D15 - SCK - PB1
    PB, // D16 - MOSI - PB2
    PB, // D17 - SS - PB0

    PF, // D18 - A0 - PF7
    PF, // D19 - A1 - PF6
    PF, // D20 - A2 - PF5
    PF, // D21 - A3 - PF4
    PF, // D22 - A4 - PF1
    PF, // D23 - A5 - PF0

    PD, // D24 - PD5
    PD, // D25 / D6 - A7 - PD7
    PB, // D26 / D8 - A8 - PB4
    PB, // D27 / D9 - A9 - PB5
    PB, // D28 / D10 - A10 - PB6
    PD, // D29 / D12 - A11 - PD6
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
    _BV(2), // D0 - PD2
    _BV(3), // D1 - PD3
    _BV(1), // D2 - PD1
    _BV(0), // D3 - PD0
    _BV(4), // D4 - PD4
    _BV(6), // D5 - PC6
    _BV(7), // D6 - PD7
    _BV(6), // D7 - PE6

    _BV(4), // D8 - PB4
    _BV(5), // D9 - PB5
    _BV(6), // D10 - PB6
    _BV(7), // D11 - PB7
    _BV(6), // D12 - PD6
    _BV(7), // D13 - PC7

    _BV(3), // D14 - MISO - PB3
    _BV(1), // D15 - SCK - PB1
    _BV(2), // D16 - MOSI - PB2
    _BV(0), // D17 - SS - PB0

    _BV(7), // D18 - A0 - PF7
    _BV(6), // D19 - A1 - PF6
    _BV(5), // D20 - A2 - PF5
    _BV(4), // D21 - A3 - PF4
    _BV(1), // D22 - A4 - PF1
    _BV(0), // D23 - A5 - PF0

    _BV(5), // D24 - PD5
    _BV(7), // D25 / D6 - A7 - PD7
    _BV(4), // D26 / D8 - A8 - PB4
    _BV(5), // D27 / D9 - A9 - PB5
    _BV(6), // D28 / D10 - A10 - PB6
    _BV(6), // D29 / D12 - A11 - PD6
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    TIMER0B,        /* 3 */
    NOT_ON_TIMER,
    TIMER3A,        /* 5 */
    TIMER4D,        /* 6 */
    NOT_ON_TIMER,

    NOT_ON_TIMER,
    TIMER1A,        /* 9 */
    TIMER1B,        /* 10 */
    TIMER0A,        /* 11 */

    NOT_ON_TIMER,
    TIMER4A,        /* 13 */

    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,

    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
};

const uint8_t PROGMEM analog_pin_to_channel_PGM[] = {
    7,  // A0               PF7                 ADC7
    6,  // A1               PF6                 ADC6
    5,  // A2               PF5                 ADC5
    4,  // A3               PF4                 ADC4
    1,  // A4               PF1                 ADC1
    0,  // A5               PF0                 ADC0
    8,  // A6       D4      PD4                 ADC8
    10, // A7       D6      PD7                 ADC10
    11, // A8       D8      PB4                 ADC11
    12, // A9       D9      PB5                 ADC12
    13, // A10      D10     PB6                 ADC13
    9   // A11      D12     PD6                 ADC9
};

#endif /* ARDUINO_MAIN */

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR        Serial
#define SERIAL_PORT_USBVIRTUAL     Serial
#define SERIAL_PORT_HARDWARE       Serial1
#define SERIAL_PORT_HARDWARE_OPEN  Serial1
