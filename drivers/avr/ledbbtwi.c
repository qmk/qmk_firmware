#include "ledbbtwi.h"
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

static void I2C_WriteBit(unsigned char c)
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
static void I2C_Init(void)
{
    I2C_PORT &= ~ ((1 << I2C_DAT) | (1 << I2C_CLK));

    I2C_CLOCK_HI();
    I2C_DATA_HI();

    _delay_us(I2C_DELAY);
}

// Send a START Condition
//
static void I2C_Start(void)
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
static void I2C_Stop(void)
{
    I2C_CLOCK_HI();
    _delay_us(I2C_DELAY);

    I2C_DATA_HI();
    _delay_us(I2C_DELAY);
}

// write a byte to the I2C slave device
//
static unsigned char I2C_Write(unsigned char c)
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

void inline ledbbtwi_setleds(LED_TYPE *ledarray, uint16_t leds)
{
  uint8_t sreg_prev, twcr_prev;
  sreg_prev=SREG;
  twcr_prev=TWCR;
  cli();
  TWCR &= ~(1<<TWEN);
  I2C_Init();
  I2C_Start();
  I2C_Write(0x84);
  uint16_t datlen = leds*sizeof(LED_TYPE);
  uint8_t curbyte;
  uint8_t * data = (uint8_t*)ledarray;
  while (datlen--) {
    curbyte=*data++;
    I2C_Write(curbyte);
  }
  I2C_Stop();
  SREG=sreg_prev;
  TWCR=twcr_prev;
}

#endif //RGBW_BB_TWI
