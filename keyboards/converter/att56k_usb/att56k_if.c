/*
Copyright (C) 2019 by engicoder (engicoder@engicoder.com)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without l> imitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdbool.h>
#include "att56k_if.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "print.h"


/* Pin definitions */
#define CLK_PIN PD0
#define CLK_PORT PORTD
#define CLK_DDR DDRD
#define DATA_PINS  PIND
#define DATA_PIN PD1
#define DATA_PORT PORTD
#define DATA_DDR DDRD
#define PIEZO_PIN PC6
#define PIEZO_PORT PORTC
#define PIEZO_DDR DDRC
#define ENABLE_PIN PD4
#define ENABLE_PORT PORTD
#define ENABLE_DDR DDRD

#define CLK_INT INT0_vect
#define DATA_INT INT1_vect
#define TIMER_INT TIMER3_COMPB_vect

#define TIMER_PERIOD 210


static inline uint8_t pbuf_dequeue(void);
static inline void pbuf_enqueue(uint8_t data);
static inline bool pbuf_empty(void);
static inline void pbuf_clear(void);

typedef enum
{
    IDLE,
    RECV,
    CLICK,
} ScanState;


static volatile att56k_click_mode_e click_mode = ATT56K_CLICK_MODE_OFF;
static volatile uint8_t scanState = IDLE;
static bool device_detected = false;

static void enable_off(void)
{
#if defined (ATT56K_USE_ENABLE)
    /* Set ENABLE pin as input */
    ENABLE_DDR |= (1 << ENABLE_PIN);
#endif
}

static void enable_on(void)
{
#if defined (ATT56K_USE_ENABLE)

    /* Set ENABLE pin as output */
    ENABLE_DDR |= (1 << ENABLE_PIN);

    /* Pull ENABLE pin low */
    ENABLE_PORT &=  ~(1 << ENABLE_PIN);
#endif
}

static void clock_config(void)
{
    // Set as input
    CLK_DDR &= ~(1 << CLK_PIN);

    // Enable pullup resistors to avoid floating input
    CLK_PORT |= (1 << CLK_PIN);
}


static void data_config(void)
{
    // Set as input
    DATA_DDR &= ~(1 << DATA_PIN);

    // Enable pullup resistors to avoid floating input
    DATA_PORT |= (1 << DATA_PIN);
}

static inline uint8_t data_read(void)
{
    return (DATA_PINS & (1 << DATA_PIN));
}

void att56k_click_cycle(void)
{
    click_mode++;
    if (click_mode == ATT56K_CLICK_MODE_COUNT)
        click_mode = ATT56K_CLICK_MODE_OFF;
}

void click_low(void)
{
    /* Set PIEZO pin as output */
    PIEZO_DDR |= (1 << PIEZO_PIN);

    /* Pull PIEZO pin low */
    PIEZO_PORT &=  ~(1 << PIEZO_PIN);

}
void click_release(void)
{
    /* Set PIEZO pin as input */
    PIEZO_DDR &= ~(1 << PIEZO_PIN);
}

static inline void clk_int_init(void)
{
    /* Disable interrupt via mask register */
    EIFR = (1 << INTF0);

    /* Set INT1 to trigger on falling edge */
    EICRA &= ~((1 << ISC01) | (1 << ISC00));
    EICRA |= (1 << ISC01);

    /* Clear any outstanding flag */
    EIFR &= ~(1 << INTF0);
}

static inline void clk_int_enable(void)
{
    /* Clear any outstanding flag */
    EIFR = (1 << INTF0);
    /* Enable interrupt in mask register */
    EIMSK |= (1 << INT0);
}

static inline void clk_int_disable(void)
{
    /* Disable interrupt via mask register */
    EIMSK &= ~(1 << INT0);
}


static inline void data_int_init(void)
{
    /* Disable interrupt via mask register */
    EIFR = (1 << INTF1);

    /* Set INT1 to trigger on falling edge */
    EICRA &= ~((1 << ISC11) | (1 << ISC10));
    EICRA |= (1 << ISC11);

    /* Clear any outstanding flag */
    EIFR &= ~(1 << INTF1);
}

static inline void data_int_enable(void)
{
    /* Clear any outstanding flag */
    EIFR = (1 << INTF1);
    /* Enable interrupt in mask register */
    EIMSK |= (1 << INT1);
}

static inline void data_int_disable(void)
{
    /* Disable interrupt via mask register */
    EIMSK &= ~(1 << INT1);
}

#ifdef ATT56K_USE_ASYNC

static void timer_init(void)
{
    /* Configure Timer3 */
    TCCR3A = 0;

	/* Enable CTC mode and stop timer by selecting no clock source*/
    TCCR3A = 0x00;
    TCCR3B = (1 << WGM32);

    OCR3A = TIMER_PERIOD;
    OCR3B = TIMER_PERIOD/2;

	/* Reset counter */
    TCNT3 = 0;
}

static void timer_int_enable(void)
{
    /* Reset counter */
    TCNT3 = 0;

    /* Clear the Compare Match flags*/
    TIFR3 = (1<<OCF3B);
    /* Enable interrupt on Compare Match */
    TIMSK3 |= 1 << OCIE3B;

    /* Start timer by selecting CLk/8 source */
    TCCR3B |= (1 << CS31);
}


static void timer_int_disable(void)
{
    /* Stop timer by selecting no clock source but leaving CTC mode*/
    TCCR3B = (1 << WGM32);

    /* Disable Compare Match interrupts */
    TIMSK3 &= ~(1 << OCIE3B);

    /* Clear the Compare Match flags*/
    TIFR3 = (1<<OCF3B);

}
#endif


void att56k_init(void)
{
    enable_off();

    clock_config();
    data_config();

    click_release();

#ifdef ATT56K_USE_ASYNC
    timer_init();
    data_int_init();
    data_int_enable();
#elif defined ATT56K_USE_SYNC
    clk_int_init();
    clk_int_enable();
#else
    #error ATT56K must define ATT56K_USE_SYNC or ATT56K_USE_ASYNC
#endif

    pbuf_clear();

    enable_on();
}


uint8_t att56k_recv(void)
{
    uint8_t data = 0;

    if (!pbuf_empty())
    {
        data = pbuf_dequeue();
    }

    return data;
}

bool att56k_has_data(void)
{
    return !pbuf_empty();
}

bool att56k_device_detected(void)
{
    return device_detected;
}


// /* Interrupt handler
//  * This interrupt handler is invoked on the falling edge of the CLK line.
//  * ------------------------------------------------------------------------- */
ISR(CLK_INT)
{
    static uint8_t bit;
    static uint16_t data;

    switch (scanState)
    {
        case IDLE:
            bit = 16;
            data = 0;
            scanState = RECV;
        case RECV:
            bit--;
            if (data_read() != 0)
                data |= (1 << bit);
            if (bit == 0)
            {
                /* Detect 0x7F SOF designator.
                    - if found, queue data
                    - else, keep reading until we do */
                if ((data >> 8) == 0x7F)
                {
                    pbuf_enqueue(data & 0xFF);
                    scanState = IDLE;
                }
                else
                {
                    bit++;
                }
            }
            break;
    }

 }

/* Asynchronous data reception
 *  Interrupt on data start bit (falling edge)
 *   - Deactivate falling edge interrupt
 *   - Start timer with 105us period and compare match at 52.5us (half period)
 *  Interrupt on timer match (half clock period)
 *   - Read data as with synchronous clock method
 *   - After 16 bits read stop timer interrupt
 *   - Enable falling edge interrupt
 * ------------------------------------------------------------------------- */

ISR(DATA_INT)
{
    data_int_disable();
    timer_int_enable();
}



ISR(TIMER_INT)
{
    static uint8_t bit;
    static uint16_t data;
    static uint8_t click_count;

    switch (scanState)
    {
        case IDLE:
            bit = 16;
            data = 0;
            scanState = RECV;
        case RECV:
            bit--;
            if (data_read() != 0)
                data |= (1 << bit);
            if (bit == 0)
            {
                if ((data >> 8) == 0x7F)
                {
                    pbuf_enqueue(data & 0xFF);
                    bool is_make = ((data & (1 << 7)) == 0);
                    if ((is_make && click_mode == ATT56K_CLICK_MODE_MAKE)
                        || (click_mode == ATT56K_CLICK_MODE_MAKE_BREAK))
                    {
                        scanState = CLICK;
                        click_count = 0;
                    }
                }
                else if (data == 0x770F)
                {
                    device_detected = true;
                }

                if (scanState == RECV)
                {
                    scanState = IDLE;
                    timer_int_disable();
                    data_int_enable();
                }
            }

            break;
        case CLICK:
            if (click_count == 0)
                click_low();
            else if (click_count >= 3)
            {
                click_release();
                scanState = IDLE;
                timer_int_disable();
                data_int_enable();
            }
            click_count++;
            break;
    }
}

#define PBUF_SIZE 32
static uint8_t pbuf[PBUF_SIZE];

uint8_t pbuf_front = 0;
uint8_t pbuf_rear = 0;

static uint8_t pbuf_size(void)
{
    return pbuf_rear - pbuf_front;
}

static bool pbuf_empty(void)
{
    return pbuf_front == pbuf_rear;
}

static bool pbuf_full(void)
{
    return pbuf_size() == PBUF_SIZE;
}

static void pbuf_clear(void)
{
    pbuf_front = pbuf_rear = 0;
}

static uint8_t pbuf_mask(uint8_t val)
{
    return val & (PBUF_SIZE - 1);
}

static void pbuf_enqueue(uint8_t val)
{
    if (!pbuf_full())
        pbuf[pbuf_mask(pbuf_rear++)] = val;
}

static uint8_t pbuf_dequeue(void)
{
    uint8_t val = 0;
    if (!pbuf_empty())
        val = pbuf[pbuf_mask(pbuf_front++)];

    return val;
}
