/*
Copyright 2013 Mathias Andersson <wraul@dbox.se>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/* Breathing Sleep LED brighness(PWM On period) table
 * (64[steps] * 4[duration]) / 64[PWM periods/s] = 4 second breath cycle
 *
 * http://www.wolframalpha.com/input/?i=%28sin%28+x%2F64*pi%29**8+*+255%2C+x%3D0+to+63
 * (0..63).each {|x| p ((sin(x/64.0*PI)**8)*255).to_i }
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "backlight.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif



#define DEFAULT_ACCURACY  256
#define PWM_LED_TIMER_TOP F_CPU/(256*64)

static const uint8_t breathing_table[][256] PROGMEM = {{0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,17,18,20,21,23,25,27,29,31,33,35,37,40,42,44,47,49,52,54,57,59,62,65,67,70,73,76,79,82,85,88,90,93,97,100,103,106,109,112,115,118,121,124,127,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,176,179,182,185,188,190,193,196,198,201,203,206,208,211,213,215,218,220,222,224,226,228,230,232,234,235,237,238,240,241,243,244,245,246,248,249,250,250,251,252,253,253,254,254,254,255,255,255,255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,245,244,243,241,240,238,237,235,234,232,230,228,226,224,222,220,218,215,213,211,208,206,203,201,198,196,193,190,188,185,182,179,176,173,170,167,165,162,158,155,152,149,146,143,140,137,134,131,128,124,121,118,115,112,109,106,103,100,97,93,90,88,85,82,79,76,73,70,67,65,62,59,57,54,52,49,47,44,42,40,37,35,33,31,29,27,25,23,21,20,18,17,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0
}};



uint8_t acc = 0;
bool is_init = false;
uint8_t accuracy = 0xff;
uint8_t speed = 1;
uint8_t current_level = 0;
uint8_t duty_cycle = 0;
uint8_t pos = 0;


void pwm_led_init(void)
{
    if(is_init){
        return;
    }
    is_init = true;
    /* Timer1 setup */
    /* CTC mode */
    TCCR1B |= _BV(WGM12);
    /* Clock selelct: clk/1 */
    TCCR1B |= _BV(CS10);
    /* Set TOP value */
    uint8_t sreg = SREG;
    cli();
    OCR1AH = (PWM_LED_TIMER_TOP>>8)&0xff;
    OCR1AL = PWM_LED_TIMER_TOP&0xff;
    SREG = sreg;
}
void open_led(void)
{
    PORTB |= (1<<6);
}
void close_led(void)
{
    PORTB &= ~(1<<6);
}
void pwm_led_enable(void)
{
    /* Enable Compare Match Interrupt */
    TIMSK1 |= _BV(OCIE1A);
}

void pwm_led_disable(void)
{
    /* Disable Compare Match Interrupt */
    TIMSK1 &= ~_BV(OCIE1A);
}
void backlight_set(uint8_t level)
{
    //uart_transmit(level);
    current_level = level;
    DDRB |= (1<<6);
    //PORTB |= (1<<6);
    //pwm_led_init();
   // pwm_led_enable();

    if(level > 0)
    {
        pwm_led_enable();
    }
    else
    {

        pwm_led_disable();
        close_led();
    }

}


void tick(void)
{
    if(current_level == 1)
    {
        duty_cycle = 85;
    }
    else if(current_level == 2)
    {
        duty_cycle = 130;
    }
    else if(current_level == 3)
    {
        duty_cycle = 190;
    }
    else if(current_level == 4)
    {
        duty_cycle = 255;
    }
    else if(current_level == 5)
    {
        pos++;
        duty_cycle = pgm_read_byte(&breathing_table[0][pos]);
        if(pos >= 0xff){
            pos = 0;
        }
    }
}

ISR(TIMER1_COMPA_vect)
{
    acc++;
    if(acc == accuracy)
    {
        acc=0;
        open_led();
        tick();
    }
    if (acc == duty_cycle)
    {
        close_led();
    }
}
