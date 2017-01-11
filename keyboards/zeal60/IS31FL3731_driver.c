#include "IS31FL3731_driver.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "TWIlib.h"
#include "progmem.h"

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
#define ISSI_ADDR_DEFAULT 0x74

#define ISSI_REG_CONFIG  0x00
#define ISSI_REG_CONFIG_PICTUREMODE 0x00
#define ISSI_REG_CONFIG_AUTOPLAYMODE 0x08
#define ISSI_REG_CONFIG_AUDIOPLAYMODE 0x18

#define ISSI_CONF_PICTUREMODE 0x00
#define ISSI_CONF_AUTOFRAMEMODE 0x04
#define ISSI_CONF_AUDIOMODE 0x08

#define ISSI_REG_PICTUREFRAME  0x01

#define ISSI_REG_SHUTDOWN 0x0A
#define ISSI_REG_AUDIOSYNC 0x06

#define ISSI_COMMANDREGISTER 0xFD
#define ISSI_BANK_FUNCTIONREG 0x0B    // helpfully called 'page nine'

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[TXMAXBUFLEN];

// These buffers match the IS31FL3731 PWM registers 0x24-0xB3.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in IS31FL3731_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[2][144];
bool g_pwm_buffer_update_required = false;

uint8_t g_led_control_registers[2][18] = { { 0 }, { 0 } };
bool g_led_control_registers_update_required = false;

// map of LED index to register (matrix A and matrix B)
// i.e. this is LA0..LA17,LB0..LB17 and also LC0..LC17,LD0..LD17
// Index of LED (0..36) will map to a register.
// Subtract 0x24 to get the second index of g_pwm_buffer
const uint8_t g_red_registers[36] PROGMEM = {
	0x34, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
	0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0x9B,
	0x3C, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33,
	0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xA3 };

const uint8_t g_green_registers[36] PROGMEM = {
	0x44, 0x45, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
	0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x8A, 0x8B,
	0x4C, 0x4D, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43,
	0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0x92, 0x93 };

const uint8_t g_blue_registers[36] PROGMEM = {
	0x54, 0x55, 0x56, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B,
	0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x79, 0x7A, 0x7B,
	0x5C, 0x5D, 0x5E, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53,
	0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x81, 0x82, 0x83 };

typedef struct
{
	uint8_t red_register;
	uint8_t red_bit;
	uint8_t green_register;
	uint8_t green_bit;
	uint8_t blue_register;
	uint8_t blue_bit;
} led_control_bitmask;

// This is the bit pattern in the LED control registers
// (for matrix A, add one to register for matrix B)
//
//  reg -  b7  b6  b5  b4  b3  b2  b1  b0
// 0x00 - R08,R07,R06,R05,R04,R03,R02,R01
// 0x02 - G08,G07,G06,G05,G04,G03,G02,R00
// 0x04 - B08,B07,B06,B05,B04,B03,G01,G00
// 0x06 -  - , - , - , - , - ,B02,B01,B00
// 0x08 -  - , - , - , - , - , - , - , -
// 0x0A - B17,B16,B15, - , - , - , - , -
// 0x0C - G17,G16,B14,B13,B12,B11,B10,B09
// 0x0E - R17,G15,G14,G13,G12,G11,G10,G09
// 0x10 - R16,R15,R14,R13,R12,R11,R10,R09

const led_control_bitmask g_led_control_bitmask[18] =
{
	{ 0x02, 0, 0x04, 0, 0x06, 0 }, // R00,G00,B00
	{ 0x00, 0, 0x04, 1, 0x06, 1 }, // R01,G01,B01
	{ 0x00, 1, 0x02, 1, 0x06, 2 }, // R02,G02,B02
	{ 0x00, 2, 0x02, 2, 0x04, 2 }, // R03,G03,B03
	{ 0x00, 3, 0x02, 3, 0x04, 3 }, // R04,G04,B04
	{ 0x00, 4, 0x02, 4, 0x04, 4 }, // R05,G05,B05
	{ 0x00, 5, 0x02, 5, 0x04, 5 }, // R06,G06,B06
	{ 0x00, 6, 0x02, 6, 0x04, 6 }, // R07,G07,B07
	{ 0x00, 7, 0x02, 7, 0x04, 7 }, // R08,G08,B08

	{ 0x10, 0, 0x0E, 0, 0x0C, 0 }, // R09,G09,B09
	{ 0x10, 1, 0x0E, 1, 0x0C, 1 }, // R10,G10,B10
	{ 0x10, 2, 0x0E, 2, 0x0C, 2 }, // R11,G11,B11
	{ 0x10, 3, 0x0E, 3, 0x0C, 3 }, // R12,G12,B12
	{ 0x10, 4, 0x0E, 4, 0x0C, 4 }, // R13,G13,B13
	{ 0x10, 5, 0x0E, 5, 0x0C, 5 }, // R14,G14,B14
	{ 0x10, 6, 0x0E, 6, 0x0A, 5 }, // R15,G15,B15
	{ 0x10, 7, 0x0C, 6, 0x0A, 6 }, // R16,G16,B16
	{ 0x0E, 7, 0x0C, 7, 0x0A, 7 }, // R17,G17,B17
};

void IS31FL3731_write_register( uint8_t addr, uint8_t reg, uint8_t data )
{
	g_twi_transfer_buffer[0] = (addr << 1) | 0x00;
	g_twi_transfer_buffer[1] = reg;
	g_twi_transfer_buffer[2] = data;

	// Set the error code to have no relevant information
	TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
	// Continuously attempt to transmit data until a successful transmission occurs
	while ( TWIInfo.errorCode != 0xFF )
	{
		TWITransmitData( g_twi_transfer_buffer, 3, 0 );
	}
}

void IS31FL3731_write_pwm_buffer( uint8_t addr, uint8_t *pwm_buffer )
{
	// assumes bank is already selected

	// transmit PWM registers in 9 transfers of 16 bytes
	// g_twi_transfer_buffer[] is 20 bytes

	// set the I2C address
	g_twi_transfer_buffer[0] = (addr << 1) | 0x00;

	// iterate over the pwm_buffer contents at 16 byte intervals
	for ( int i = 0; i < 144; i += 16 )
	{
		// set the first register, e.g. 0x24, 0x34, 0x44, etc.
		g_twi_transfer_buffer[1] = 0x24 + i;
		// copy the data from i to i+15
		// device will auto-increment register for data after the first byte
		// thus this sets registers 0x24-0x33, 0x34-0x43, etc. in one transfer
		for ( int j = 0; j < 16; j++ )
		{
			g_twi_transfer_buffer[2 + j] = pwm_buffer[i + j];
		}

		// Set the error code to have no relevant information
		TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
		// Continuously attempt to transmit data until a successful transmission occurs
		while ( TWIInfo.errorCode != 0xFF )
		{
			TWITransmitData( g_twi_transfer_buffer, 16 + 2, 0 );
		}
	}
}

void IS31FL3731_init( uint8_t addr )
{
	// In order to avoid the LEDs being driven with garbage data
	// in the LED driver's PWM registers, first enable software shutdown,
	// then set up the mode and other settings, clear the PWM registers,
	// then disable software shutdown.

	// select "function register" bank
	IS31FL3731_write_register( addr, ISSI_COMMANDREGISTER, ISSI_BANK_FUNCTIONREG );

	// enable software shutdown
	IS31FL3731_write_register( addr, ISSI_REG_SHUTDOWN, 0x00 );
	// this delay was copied from other drivers, might not be needed
	_delay_ms( 10 );

	// picture mode
	IS31FL3731_write_register( addr, ISSI_REG_CONFIG, ISSI_REG_CONFIG_PICTUREMODE );
	// display frame 0
	IS31FL3731_write_register( addr, ISSI_REG_PICTUREFRAME, 0x00 );
	// audio sync off
	IS31FL3731_write_register( addr, ISSI_REG_AUDIOSYNC, 0x00 );

	// select bank 0
	IS31FL3731_write_register( addr, ISSI_COMMANDREGISTER, 0 );

	// turn off all LEDs in the LED control register
	for ( int i = 0x00; i <= 0x11; i++ )
	{
		IS31FL3731_write_register( addr, i, 0x00 );
	}

	// turn off all LEDs in the blink control register (not really needed)
	for ( int i = 0x12; i <= 0x23; i++ )
	{
		IS31FL3731_write_register( addr, i, 0x00 );
	}

	// set PWM on all LEDs to 0
	for ( int i = 0x24; i <= 0xB3; i++ )
	{
		IS31FL3731_write_register( addr, i, 0x00 );
	}

	// select "function register" bank
	IS31FL3731_write_register( addr, ISSI_COMMANDREGISTER, ISSI_BANK_FUNCTIONREG );

	// disable software shutdown
	IS31FL3731_write_register( addr, ISSI_REG_SHUTDOWN, 0x01 );

	// select bank 0 and leave it selected.
	// most usage after initialization is just writing PWM buffers in bank 0
	// as there's not much point in double-buffering
	IS31FL3731_write_register( addr, ISSI_COMMANDREGISTER, 0 );
}

void IS31FL3731_set_color( int index, uint8_t red, uint8_t green, uint8_t blue )
{
	if ( index >= 0 && index < 72 )
	{
		int driver = 0;
		if ( index >= 36 )
		{
			driver = 1;
			index -= 36;
		}
		// Index of LED (0..36) will map to a register.
		// Subtract 0x24 to get the second index of g_pwm_buffer
		g_pwm_buffer[driver][ pgm_read_byte(&g_red_registers[index]) - 0x24] = red;
		g_pwm_buffer[driver][ pgm_read_byte(&g_green_registers[index]) - 0x24] = green;
		g_pwm_buffer[driver][ pgm_read_byte(&g_blue_registers[index]) - 0x24] = blue;
		g_pwm_buffer_update_required = true;
	}
}

void IS31FL3731_set_color_all( uint8_t red, uint8_t green, uint8_t blue )
{
	for ( int i = 0; i < 72; i++ )
	{
		IS31FL3731_set_color( i, red, green, blue );
	}
}

void IS31FL3731_set_led_control_register( uint8_t index, bool red, bool green, bool blue )
{
	uint8_t driver = 0;
	if ( index >= 36 )
	{
		driver = 1;
		index -= 36;
	}

	// index now in range 0..35
	uint8_t matrix = 0; // Matrix A
	if ( index >= 18 )
	{
		matrix = 1; // Matrix B
		index -= 18;
	}

	led_control_bitmask bitmask = g_led_control_bitmask[index];

	// Matrix A and B registers are interleaved.
	// Add 1 to Matrix A register to get Matrix B register
	if ( red )
	{
		g_led_control_registers[driver][bitmask.red_register+matrix] |= (1<<bitmask.red_bit);
	}
	else
	{
		g_led_control_registers[driver][bitmask.red_register+matrix] &= ~(1<<bitmask.red_bit);
	}
	if ( green )
	{
		g_led_control_registers[driver][bitmask.green_register+matrix] |= (1<<bitmask.green_bit);
	}
	else
	{
		g_led_control_registers[driver][bitmask.green_register+matrix] &= ~(1<<bitmask.green_bit);
	}
	if ( blue )
	{
		g_led_control_registers[driver][bitmask.blue_register+matrix] |= (1<<bitmask.blue_bit);
	}
	else
	{
		g_led_control_registers[driver][bitmask.blue_register+matrix] &= ~(1<<bitmask.blue_bit);
	}

	g_led_control_registers_update_required = true;


}

void IS31FL3731_update_pwm_buffers( uint8_t addr1, uint8_t addr2 )
{
	if ( g_pwm_buffer_update_required )
	{
		IS31FL3731_write_pwm_buffer( addr1, g_pwm_buffer[0] );
		IS31FL3731_write_pwm_buffer( addr2, g_pwm_buffer[1] );
	}
	g_pwm_buffer_update_required = false;
}

void IS31FL3731_update_led_control_registers( uint8_t addr1, uint8_t addr2 )
{
	if ( g_led_control_registers_update_required )
	{
		for ( int i=0; i<18; i++ )
		{
			IS31FL3731_write_register(addr1, i, g_led_control_registers[0][i] );
			IS31FL3731_write_register(addr2, i, g_led_control_registers[1][i] );
		}
	}
}

