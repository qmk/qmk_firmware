/* Tone.cpp

  A Tone Generator Library

  Written by Brett Hagman

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Version Modified By Date     Comments
------- ----------- -------- --------
0001    B Hagman    09/08/02 Initial coding
0002    B Hagman    09/08/18 Multiple pins
0003    B Hagman    09/08/18 Moved initialization from constructor to begin()
0004    B Hagman    09/09/26 Fixed problems with ATmega8
0005    B Hagman    09/11/23 Scanned prescalars for best fit on 8 bit timers
                    09/11/25 Changed pin toggle method to XOR
                    09/11/25 Fixed timer0 from being excluded
0006    D Mellis    09/12/29 Replaced objects with functions
0007    M Sproul    10/08/29 Changed #ifdefs from cpu to register
*************************************************/

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "pins_arduino.h"

#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega128__)
#define TCCR2A TCCR2
#define TCCR2B TCCR2
#define COM2A1 COM21
#define COM2A0 COM20
#define OCR2A OCR2
#define TIMSK2 TIMSK
#define OCIE2A OCIE2
#define TIMER2_COMPA_vect TIMER2_COMP_vect
#define TIMSK1 TIMSK
#endif

// timerx_toggle_count:
//  > 0 - duration specified
//  = 0 - stopped
//  < 0 - infinitely (until stop() method called, or new play() called)

#if !defined(__AVR_ATmega8__)
volatile long timer0_toggle_count;
volatile uint8_t *timer0_pin_port;
volatile uint8_t timer0_pin_mask;
#endif

volatile long timer1_toggle_count;
volatile uint8_t *timer1_pin_port;
volatile uint8_t timer1_pin_mask;
volatile long timer2_toggle_count;
volatile uint8_t *timer2_pin_port;
volatile uint8_t timer2_pin_mask;

#if defined(TIMSK3)
volatile long timer3_toggle_count;
volatile uint8_t *timer3_pin_port;
volatile uint8_t timer3_pin_mask;
#endif

#if defined(TIMSK4)
volatile long timer4_toggle_count;
volatile uint8_t *timer4_pin_port;
volatile uint8_t timer4_pin_mask;
#endif

#if defined(TIMSK5)
volatile long timer5_toggle_count;
volatile uint8_t *timer5_pin_port;
volatile uint8_t timer5_pin_mask;
#endif


// MLS: This does not make sense, the 3 options are the same
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

#define AVAILABLE_TONE_PINS 1

const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 2 /*, 3, 4, 5, 1, 0 */ };
static uint8_t tone_pins[AVAILABLE_TONE_PINS] = { 255 /*, 255, 255, 255, 255, 255 */ };

#elif defined(__AVR_ATmega8__)

#define AVAILABLE_TONE_PINS 1

const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 2 /*, 1 */ };
static uint8_t tone_pins[AVAILABLE_TONE_PINS] = { 255 /*, 255 */ };

#else

#define AVAILABLE_TONE_PINS 1

// Leave timer 0 to last.
const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 2 /*, 1, 0 */ };
static uint8_t tone_pins[AVAILABLE_TONE_PINS] = { 255 /*, 255, 255 */ };

#endif



static int8_t toneBegin(uint8_t _pin)
{
  int8_t _timer = -1;

  // if we're already using the pin, the timer should be configured.  
  for (int i = 0; i < AVAILABLE_TONE_PINS; i++) {
    if (tone_pins[i] == _pin) {
      return pgm_read_byte(tone_pin_to_timer_PGM + i);
    }
  }
  
  // search for an unused timer.
  for (int i = 0; i < AVAILABLE_TONE_PINS; i++) {
    if (tone_pins[i] == 255) {
      tone_pins[i] = _pin;
      _timer = pgm_read_byte(tone_pin_to_timer_PGM + i);
      break;
    }
  }
  
  if (_timer != -1)
  {
    // Set timer specific stuff
    // All timers in CTC mode
    // 8 bit timers will require changing prescalar values,
    // whereas 16 bit timers are set to either ck/1 or ck/64 prescalar
    switch (_timer)
    {
      #if defined(TCCR0A) && defined(TCCR0B)
      case 0:
        // 8 bit timer
        TCCR0A = 0;
        TCCR0B = 0;
        bitWrite(TCCR0A, WGM01, 1);
        bitWrite(TCCR0B, CS00, 1);
        timer0_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer0_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif

      #if defined(TCCR1A) && defined(TCCR1B) && defined(WGM12)
      case 1:
        // 16 bit timer
        TCCR1A = 0;
        TCCR1B = 0;
        bitWrite(TCCR1B, WGM12, 1);
        bitWrite(TCCR1B, CS10, 1);
        timer1_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer1_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif

      #if defined(TCCR2A) && defined(TCCR2B)
      case 2:
        // 8 bit timer
        TCCR2A = 0;
        TCCR2B = 0;
        bitWrite(TCCR2A, WGM21, 1);
        bitWrite(TCCR2B, CS20, 1);
        timer2_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer2_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif

      #if defined(TCCR3A) && defined(TCCR3B) &&  defined(TIMSK3)
      case 3:
        // 16 bit timer
        TCCR3A = 0;
        TCCR3B = 0;
        bitWrite(TCCR3B, WGM32, 1);
        bitWrite(TCCR3B, CS30, 1);
        timer3_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer3_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif

      #if defined(TCCR4A) && defined(TCCR4B) &&  defined(TIMSK4)
      case 4:
        // 16 bit timer
        TCCR4A = 0;
        TCCR4B = 0;
        #if defined(WGM42)
          bitWrite(TCCR4B, WGM42, 1);
        #elif defined(CS43)
          #warning this may not be correct
          // atmega32u4
          bitWrite(TCCR4B, CS43, 1);
        #endif
        bitWrite(TCCR4B, CS40, 1);
        timer4_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer4_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif

      #if defined(TCCR5A) && defined(TCCR5B) &&  defined(TIMSK5)
      case 5:
        // 16 bit timer
        TCCR5A = 0;
        TCCR5B = 0;
        bitWrite(TCCR5B, WGM52, 1);
        bitWrite(TCCR5B, CS50, 1);
        timer5_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer5_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif
    }
  }

  return _timer;
}



// frequency (in hertz) and duration (in milliseconds).

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
  uint8_t prescalarbits = 0b001;
  long toggle_count = 0;
  uint32_t ocr = 0;
  int8_t _timer;

  _timer = toneBegin(_pin);

  if (_timer >= 0)
  {
    // Set the pinMode as OUTPUT
    pinMode(_pin, OUTPUT);
    
    // if we are using an 8 bit timer, scan through prescalars to find the best fit
    if (_timer == 0 || _timer == 2)
    {
      ocr = F_CPU / frequency / 2 - 1;
      prescalarbits = 0b001;  // ck/1: same for both timers
      if (ocr > 255)
      {
        ocr = F_CPU / frequency / 2 / 8 - 1;
        prescalarbits = 0b010;  // ck/8: same for both timers

        if (_timer == 2 && ocr > 255)
        {
          ocr = F_CPU / frequency / 2 / 32 - 1;
          prescalarbits = 0b011;
        }

        if (ocr > 255)
        {
          ocr = F_CPU / frequency / 2 / 64 - 1;
          prescalarbits = _timer == 0 ? 0b011 : 0b100;

          if (_timer == 2 && ocr > 255)
          {
            ocr = F_CPU / frequency / 2 / 128 - 1;
            prescalarbits = 0b101;
          }

          if (ocr > 255)
          {
            ocr = F_CPU / frequency / 2 / 256 - 1;
            prescalarbits = _timer == 0 ? 0b100 : 0b110;
            if (ocr > 255)
            {
              // can't do any better than /1024
              ocr = F_CPU / frequency / 2 / 1024 - 1;
              prescalarbits = _timer == 0 ? 0b101 : 0b111;
            }
          }
        }
      }

#if defined(TCCR0B)
      if (_timer == 0)
      {
        TCCR0B = prescalarbits;
      }
      else
#endif
#if defined(TCCR2B)
      {
        TCCR2B = prescalarbits;
      }
#else
      {
        // dummy place holder to make the above ifdefs work
      }
#endif
    }
    else
    {
      // two choices for the 16 bit timers: ck/1 or ck/64
      ocr = F_CPU / frequency / 2 - 1;

      prescalarbits = 0b001;
      if (ocr > 0xffff)
      {
        ocr = F_CPU / frequency / 2 / 64 - 1;
        prescalarbits = 0b011;
      }

      if (_timer == 1)
      {
#if defined(TCCR1B)
        TCCR1B = (TCCR1B & 0b11111000) | prescalarbits;
#endif
      }
#if defined(TCCR3B)
      else if (_timer == 3)
        TCCR3B = (TCCR3B & 0b11111000) | prescalarbits;
#endif
#if defined(TCCR4B)
      else if (_timer == 4)
        TCCR4B = (TCCR4B & 0b11111000) | prescalarbits;
#endif
#if defined(TCCR5B)
      else if (_timer == 5)
        TCCR5B = (TCCR5B & 0b11111000) | prescalarbits;
#endif

    }
    

    // Calculate the toggle count
    if (duration > 0)
    {
      toggle_count = 2 * frequency * duration / 1000;
    }
    else
    {
      toggle_count = -1;
    }

    // Set the OCR for the given timer,
    // set the toggle count,
    // then turn on the interrupts
    switch (_timer)
    {

#if defined(OCR0A) && defined(TIMSK0) && defined(OCIE0A)
      case 0:
        OCR0A = ocr;
        timer0_toggle_count = toggle_count;
        bitWrite(TIMSK0, OCIE0A, 1);
        break;
#endif

      case 1:
#if defined(OCR1A) && defined(TIMSK1) && defined(OCIE1A)
        OCR1A = ocr;
        timer1_toggle_count = toggle_count;
        bitWrite(TIMSK1, OCIE1A, 1);
#elif defined(OCR1A) && defined(TIMSK) && defined(OCIE1A)
        // this combination is for at least the ATmega32
        OCR1A = ocr;
        timer1_toggle_count = toggle_count;
        bitWrite(TIMSK, OCIE1A, 1);
#endif
        break;

#if defined(OCR2A) && defined(TIMSK2) && defined(OCIE2A)
      case 2:
        OCR2A = ocr;
        timer2_toggle_count = toggle_count;
        bitWrite(TIMSK2, OCIE2A, 1);
        break;
#endif

#if defined(TIMSK3)
      case 3:
        OCR3A = ocr;
        timer3_toggle_count = toggle_count;
        bitWrite(TIMSK3, OCIE3A, 1);
        break;
#endif

#if defined(TIMSK4)
      case 4:
        OCR4A = ocr;
        timer4_toggle_count = toggle_count;
        bitWrite(TIMSK4, OCIE4A, 1);
        break;
#endif

#if defined(OCR5A) && defined(TIMSK5) && defined(OCIE5A)
      case 5:
        OCR5A = ocr;
        timer5_toggle_count = toggle_count;
        bitWrite(TIMSK5, OCIE5A, 1);
        break;
#endif

    }
  }
}


// XXX: this function only works properly for timer 2 (the only one we use
// currently).  for the others, it should end the tone, but won't restore
// proper PWM functionality for the timer.
void disableTimer(uint8_t _timer)
{
  switch (_timer)
  {
    case 0:
      #if defined(TIMSK0)
        TIMSK0 = 0;
      #elif defined(TIMSK)
        TIMSK = 0; // atmega32
      #endif
      break;

#if defined(TIMSK1) && defined(OCIE1A)
    case 1:
      bitWrite(TIMSK1, OCIE1A, 0);
      break;
#endif

    case 2:
      #if defined(TIMSK2) && defined(OCIE2A)
        bitWrite(TIMSK2, OCIE2A, 0); // disable interrupt
      #endif
      #if defined(TCCR2A) && defined(WGM20)
        TCCR2A = (1 << WGM20);
      #endif
      #if defined(TCCR2B) && defined(CS22)
        TCCR2B = (TCCR2B & 0b11111000) | (1 << CS22);
      #endif
      #if defined(OCR2A)
        OCR2A = 0;
      #endif
      break;

#if defined(TIMSK3)
    case 3:
      TIMSK3 = 0;
      break;
#endif

#if defined(TIMSK4)
    case 4:
      TIMSK4 = 0;
      break;
#endif

#if defined(TIMSK5)
    case 5:
      TIMSK5 = 0;
      break;
#endif
  }
}


void noTone(uint8_t _pin)
{
  int8_t _timer = -1;
  
  for (int i = 0; i < AVAILABLE_TONE_PINS; i++) {
    if (tone_pins[i] == _pin) {
      _timer = pgm_read_byte(tone_pin_to_timer_PGM + i);
      tone_pins[i] = 255;
    }
  }
  
  disableTimer(_timer);

  digitalWrite(_pin, 0);
}

#if 0
#if !defined(__AVR_ATmega8__)
ISR(TIMER0_COMPA_vect)
{
  if (timer0_toggle_count != 0)
  {
    // toggle the pin
    *timer0_pin_port ^= timer0_pin_mask;

    if (timer0_toggle_count > 0)
      timer0_toggle_count--;
  }
  else
  {
    disableTimer(0);
    *timer0_pin_port &= ~(timer0_pin_mask);  // keep pin low after stop
  }
}
#endif


ISR(TIMER1_COMPA_vect)
{
  if (timer1_toggle_count != 0)
  {
    // toggle the pin
    *timer1_pin_port ^= timer1_pin_mask;

    if (timer1_toggle_count > 0)
      timer1_toggle_count--;
  }
  else
  {
    disableTimer(1);
    *timer1_pin_port &= ~(timer1_pin_mask);  // keep pin low after stop
  }
}
#endif


ISR(TIMER2_COMPA_vect)
{

  if (timer2_toggle_count != 0)
  {
    // toggle the pin
    *timer2_pin_port ^= timer2_pin_mask;

    if (timer2_toggle_count > 0)
      timer2_toggle_count--;
  }
  else
  {
    // need to call noTone() so that the tone_pins[] entry is reset, so the
    // timer gets initialized next time we call tone().
    // XXX: this assumes timer 2 is always the first one used.
    noTone(tone_pins[0]);
//    disableTimer(2);
//    *timer2_pin_port &= ~(timer2_pin_mask);  // keep pin low after stop
  }
}



//#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#if 0

ISR(TIMER3_COMPA_vect)
{
  if (timer3_toggle_count != 0)
  {
    // toggle the pin
    *timer3_pin_port ^= timer3_pin_mask;

    if (timer3_toggle_count > 0)
      timer3_toggle_count--;
  }
  else
  {
    disableTimer(3);
    *timer3_pin_port &= ~(timer3_pin_mask);  // keep pin low after stop
  }
}

ISR(TIMER4_COMPA_vect)
{
  if (timer4_toggle_count != 0)
  {
    // toggle the pin
    *timer4_pin_port ^= timer4_pin_mask;

    if (timer4_toggle_count > 0)
      timer4_toggle_count--;
  }
  else
  {
    disableTimer(4);
    *timer4_pin_port &= ~(timer4_pin_mask);  // keep pin low after stop
  }
}

ISR(TIMER5_COMPA_vect)
{
  if (timer5_toggle_count != 0)
  {
    // toggle the pin
    *timer5_pin_port ^= timer5_pin_mask;

    if (timer5_toggle_count > 0)
      timer5_toggle_count--;
  }
  else
  {
    disableTimer(5);
    *timer5_pin_port &= ~(timer5_pin_mask);  // keep pin low after stop
  }
}

#endif
