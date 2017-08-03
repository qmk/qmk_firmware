/*
* light weight WS2812 lib V2.0b
*
* Controls WS2811/WS2812/WS2812B RGB-LEDs
* Author: Tim (cpldcpu@gmail.com)
*
* Jan 18th, 2014  v2.0b Initial Version
* Nov 29th, 2015  v2.3  Added SK6812RGBW support
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ws2812.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

#ifdef RGBW_BB_TWI

// Port for the I2C
#define I2C_DDR DDRD
#define I2C_PIN PIND
#define I2C_PORT PORTD

// Pins to be used in the bit banging
#define I2C_CLK 0
#define I2C_DAT 1

#define I2C_DATA_HI()\
I2C_DDR &= ~ (1 << I2C_DAT);\
I2C_PORT |= (1 << I2C_DAT);
#define I2C_DATA_LO()\
I2C_DDR |= (1 << I2C_DAT);\
I2C_PORT &= ~ (1 << I2C_DAT);

#define I2C_CLOCK_HI()\
I2C_DDR &= ~ (1 << I2C_CLK);\
I2C_PORT |= (1 << I2C_CLK);
#define I2C_CLOCK_LO()\
I2C_DDR |= (1 << I2C_CLK);\
I2C_PORT &= ~ (1 << I2C_CLK);

#define I2C_DELAY 1

void I2C_WriteBit(unsigned char c)
{
    if (c > 0)
    {
        I2C_DATA_HI();
    }
    else
    {
        I2C_DATA_LO();
    }

    I2C_CLOCK_HI();
    _delay_us(I2C_DELAY);

    I2C_CLOCK_LO();
    _delay_us(I2C_DELAY);

    if (c > 0)
    {
        I2C_DATA_LO();
    }

    _delay_us(I2C_DELAY);
}

// Inits bitbanging port, must be called before using the functions below
//
void I2C_Init(void)
{
    I2C_PORT &= ~ ((1 << I2C_DAT) | (1 << I2C_CLK));

    I2C_CLOCK_HI();
    I2C_DATA_HI();

    _delay_us(I2C_DELAY);
}

// Send a START Condition
//
void I2C_Start(void)
{
    // set both to high at the same time
    I2C_DDR &= ~ ((1 << I2C_DAT) | (1 << I2C_CLK));
    _delay_us(I2C_DELAY);

    I2C_DATA_LO();
    _delay_us(I2C_DELAY);

    I2C_CLOCK_LO();
    _delay_us(I2C_DELAY);
}

// Send a STOP Condition
//
void I2C_Stop(void)
{
    I2C_CLOCK_HI();
    _delay_us(I2C_DELAY);

    I2C_DATA_HI();
    _delay_us(I2C_DELAY);
}

// write a byte to the I2C slave device
//
unsigned char I2C_Write(unsigned char c)
{
    for (char i = 0; i < 8; i++)
    {
        I2C_WriteBit(c & 128);

        c <<= 1;
    }

    
    I2C_WriteBit(0);
    _delay_us(I2C_DELAY);
    _delay_us(I2C_DELAY);
  
    // _delay_us(I2C_DELAY);
    //return I2C_ReadBit();
    return 0;
}


#endif

// Setleds for standard RGB
void inline ws2812_setleds(LED_TYPE *ledarray, uint16_t leds)
{
   // ws2812_setleds_pin(ledarray,leds, _BV(ws2812_pin));
   ws2812_setleds_pin(ledarray,leds, _BV(RGB_DI_PIN & 0xF));
}

void inline ws2812_setleds_pin(LED_TYPE *ledarray, uint16_t leds, uint8_t pinmask)
{
  // ws2812_DDRREG |= pinmask; // Enable DDR
  // new universal format (DDR)
  _SFR_IO8((RGB_DI_PIN >> 4) + 1) |= pinmask;

  ws2812_sendarray_mask((uint8_t*)ledarray,leds+leds+leds,pinmask);
  _delay_us(50);
}

// Setleds for SK6812RGBW
void inline ws2812_setleds_rgbw(LED_TYPE *ledarray, uint16_t leds)
{

  #ifdef RGBW_BB_TWI
    uint8_t sreg_prev, twcr_prev;
    sreg_prev=SREG;
    twcr_prev=TWCR;
    cli();
    TWCR &= ~(1<<TWEN);
    I2C_Init();
    I2C_Start();
    I2C_Write(0x84);
    uint16_t datlen = leds<<2;
    uint8_t curbyte;
    uint8_t * data = (uint8_t*)ledarray;
    while (datlen--) {
      curbyte=*data++;
      I2C_Write(curbyte);
    }
    I2C_Stop();
    SREG=sreg_prev;
    TWCR=twcr_prev;
  #endif


  // ws2812_DDRREG |= _BV(ws2812_pin); // Enable DDR
  // new universal format (DDR)
  _SFR_IO8((RGB_DI_PIN >> 4) + 1) |= _BV(RGB_DI_PIN & 0xF);

  ws2812_sendarray_mask((uint8_t*)ledarray,leds<<2,_BV(RGB_DI_PIN & 0xF));


  #ifndef RGBW_BB_TWI
    _delay_us(80);
  #endif
}

void ws2812_sendarray(uint8_t *data,uint16_t datlen)
{
  ws2812_sendarray_mask(data,datlen,_BV(RGB_DI_PIN & 0xF));
}

/*
  This routine writes an array of bytes with RGB values to the Dataout pin
  using the fast 800kHz clockless WS2811/2812 protocol.
*/

// Timing in ns
#define w_zeropulse   350
#define w_onepulse    900
#define w_totalperiod 1250

// Fixed cycles used by the inner loop
#define w_fixedlow    2
#define w_fixedhigh   4
#define w_fixedtotal  8

// Insert NOPs to match the timing, if possible
#define w_zerocycles    (((F_CPU/1000)*w_zeropulse          )/1000000)
#define w_onecycles     (((F_CPU/1000)*w_onepulse    +500000)/1000000)
#define w_totalcycles   (((F_CPU/1000)*w_totalperiod +500000)/1000000)

// w1 - nops between rising edge and falling edge - low
#define w1 (w_zerocycles-w_fixedlow)
// w2   nops between fe low and fe high
#define w2 (w_onecycles-w_fixedhigh-w1)
// w3   nops to complete loop
#define w3 (w_totalcycles-w_fixedtotal-w1-w2)

#if w1>0
  #define w1_nops w1
#else
  #define w1_nops  0
#endif

// The only critical timing parameter is the minimum pulse length of the "0"
// Warn or throw error if this timing can not be met with current F_CPU settings.
#define w_lowtime ((w1_nops+w_fixedlow)*1000000)/(F_CPU/1000)
#if w_lowtime>550
   #error "Light_ws2812: Sorry, the clock speed is too low. Did you set F_CPU correctly?"
#elif w_lowtime>450
   #warning "Light_ws2812: The timing is critical and may only work on WS2812B, not on WS2812(S)."
   #warning "Please consider a higher clockspeed, if possible"
#endif

#if w2>0
#define w2_nops w2
#else
#define w2_nops  0
#endif

#if w3>0
#define w3_nops w3
#else
#define w3_nops  0
#endif

#define w_nop1  "nop      \n\t"
#define w_nop2  "rjmp .+0 \n\t"
#define w_nop4  w_nop2 w_nop2
#define w_nop8  w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8

void inline ws2812_sendarray_mask(uint8_t *data,uint16_t datlen,uint8_t maskhi)
{
  uint8_t curbyte,ctr,masklo;
  uint8_t sreg_prev;

  // masklo  =~maskhi&ws2812_PORTREG;
  // maskhi |=        ws2812_PORTREG;
  masklo  =~maskhi&_SFR_IO8((RGB_DI_PIN >> 4) + 2);
  maskhi |=        _SFR_IO8((RGB_DI_PIN >> 4) + 2);
  sreg_prev=SREG;
  cli();

  while (datlen--) {
    curbyte=(*data++);

    asm volatile(
    "       ldi   %0,8  \n\t"
    "loop%=:            \n\t"
    "       out   %2,%3 \n\t"    //  '1' [01] '0' [01] - re
#if (w1_nops&1)
w_nop1
#endif
#if (w1_nops&2)
w_nop2
#endif
#if (w1_nops&4)
w_nop4
#endif
#if (w1_nops&8)
w_nop8
#endif
#if (w1_nops&16)
w_nop16
#endif
    "       sbrs  %1,7  \n\t"    //  '1' [03] '0' [02]
    "       out   %2,%4 \n\t"    //  '1' [--] '0' [03] - fe-low
    "       lsl   %1    \n\t"    //  '1' [04] '0' [04]
#if (w2_nops&1)
  w_nop1
#endif
#if (w2_nops&2)
  w_nop2
#endif
#if (w2_nops&4)
  w_nop4
#endif
#if (w2_nops&8)
  w_nop8
#endif
#if (w2_nops&16)
  w_nop16
#endif
    "       out   %2,%4 \n\t"    //  '1' [+1] '0' [+1] - fe-high
#if (w3_nops&1)
w_nop1
#endif
#if (w3_nops&2)
w_nop2
#endif
#if (w3_nops&4)
w_nop4
#endif
#if (w3_nops&8)
w_nop8
#endif
#if (w3_nops&16)
w_nop16
#endif

    "       dec   %0    \n\t"    //  '1' [+2] '0' [+2]
    "       brne  loop%=\n\t"    //  '1' [+3] '0' [+4]
    :	"=&d" (ctr)
    :	"r" (curbyte), "I" (_SFR_IO_ADDR(_SFR_IO8((RGB_DI_PIN >> 4) + 2))), "r" (maskhi), "r" (masklo)
    );
  }

  SREG=sreg_prev;
}
