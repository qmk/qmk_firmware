#include "zeal_backlight.h"

#include <avr/io.h>
#include "TWIlib.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "progmem.h"
#include "config.h"
#include "zeal_eeprom.h"
#include "zeal_color.h"
#include "IS31FL3731_driver.h"

#define BACKLIGHT_EFFECT_MAX 7

zeal_backlight_config g_config = {
	.use_split_backspace = USE_SPLIT_BACKSPACE,
	.use_split_left_shift = USE_SPLIT_LEFT_SHIFT,
    .use_split_right_shift = USE_SPLIT_RIGHT_SHIFT,
    .use_7u_spacebar = USE_7U_SPACEBAR,
    .use_iso_enter = USE_ISO_ENTER,
	.alphas_mods = {	ALPHAS_MODS_ROW_0,
						ALPHAS_MODS_ROW_1,
						ALPHAS_MODS_ROW_2,
						ALPHAS_MODS_ROW_3,
						ALPHAS_MODS_ROW_4 },
	.brightness = 255,
	.effect = 0,
	.color_1 = { .h = 0, .s = 255, .v = 0 },
	.color_2 = { .h = 127, .s = 255, .v = 0 }
};

// Global tick at 20 Hz
uint32_t g_tick = 0;

// Ticks since this key was last hit.
uint8_t g_key_hit[72];

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
#define ISSI_ADDR_1 0x74
#define ISSI_ADDR_2 0x76

typedef struct Point {
	uint8_t x;
	uint8_t y;
} Point;

// index in range 0..71 (LA0..LA17, LB0..LB17, LC0..LC17, LD0..LD17)
// point values in range x=0..224 y=0..64
// origin is center of top-left key (i.e Esc)
const Point g_map_led_to_point[72] PROGMEM = {
	// LA0..LA17
	{120,16}, {104,16}, {88,16}, {72,16}, {56,16}, {40,16}, {24,16}, {4,16}, {4,32},
	{128,0}, {112,0}, {96,0}, {80,0}, {64,0}, {48,0}, {32,0}, {16,0}, {0,0},
	// LB0..LB17
	{144,0}, {160,0}, {176,0}, {192,0}, {216,0}, {224,0}, {255,255}, {255,255}, {255,255},
	{136,16}, {152,16}, {168,16}, {184,16}, {200,16}, {220,16}, {255,255}, {255,255}, {255,255},
	// LC0..LC17
	{102,64}, {100,48}, {84,48}, {68,48}, {52,48}, {36,48}, {60,48}, {43,64}, {23,64},
	{108,32}, {92,32}, {76,32}, {60,32}, {44,32}, {28,32}, {20,48}, {2,48}, {3,64},
	// LD0..LD17
	{124,32}, {140,32}, {156,32}, {172,32}, {188,32}, {214,32}, {180,48}, {210,48}, {224,48},
	{116,48}, {132,48}, {148,48}, {164,48}, {144,64}, {161,64}, {181,64}, {201,64}, {221,64}
};

// This may seem counter-intuitive, but it's quite flexible.
// For each LED, get it's position to decide what color to make it.
// This solves the issue of LEDs (and switches) not aligning to a grid,
// or having a large "bitmap" and sampling them.
void map_led_to_point( uint8_t index, Point *point )
{
	// Slightly messy way to get Point structs out of progmem.
	uint8_t *addr = (uint8_t*)&g_map_led_to_point[index];
	point->x = pgm_read_byte(addr);
	point->y = pgm_read_byte(addr+1);

	switch (index)
	{
		case 18+4: // LB4A
			if ( g_config.use_split_backspace )
				point->x -= 8;
			break;
		case 18+14: // LB14A
			if ( g_config.use_iso_enter )
				point->y += 8; // extremely pedantic
			break;
		case 36+0: // LC0A
			if ( g_config.use_7u_spacebar )
				point->x += 10;
			break;
		case 36+6: // LC6A
			if ( g_config.use_7u_spacebar )
				point->x += 4;
			break;			
		case 36+16: // LC16A
			if ( !g_config.use_split_left_shift )
				point->x += 8;
			break;
		case 54+5: // LD5A
			if ( !g_config.use_iso_enter )
				point->x -= 10;
			break;
		case 54+7: // LD7A
			if ( !g_config.use_split_right_shift )
				point->x -= 8;
			break;
	}
}

//
// Maps switch matrix coordinate (row,col) to LED index
//
// Note: Left spacebar stab is at 4,3 (LC6)
// Right spacebar stab is at 4,9 (LD13) or 4,10 (LD14)
//
// A17, A16, A15, A14, A13, A12, A11, A10,  A9,  B0,  B1,  B2,  B3,  B4,
//  A7,  A6,  A5,  A4,  A3,  A2,  A1,  A0,  B9, B10, B11, B12, B13, B14,
//  A8, C14, C13, C12, C11, C10,  C9,  D0,  D1,  D2,  D3,  D4,  D5,  B5,
// C16, C15,  C5,  C4,  C3,  C2,  C1,  D9, D10, D11, D12,  D6,  D7,  D8,
// C17,  C8,  C7,  C6, ---, ---, ---,  C0, ---, D13, D14, D15, D16, D17,
//
const uint8_t g_map_row_col_to_led[5][14] PROGMEM = {
	{  0+17,  0+16,  0+15,  0+14,  0+13,  0+12,  0+11,  0+10,   0+9,  18+0,  18+1,  18+2,  18+3,  18+4 },
	{   0+7,   0+6,   0+5,   0+4,   0+3,   0+2,   0+1,   0+0,  18+9, 18+10, 18+11, 18+12, 18+13, 18+14 },
	{   0+8, 36+14, 36+13, 36+12, 36+11, 36+10,  36+9,  54+0,  54+1,  54+2,  54+3,  54+4,  54+5,  18+5 },
	{ 36+16, 36+15,  36+5,  36+4,  36+3,  36+2,  36+1,  54+9, 54+10, 54+11, 54+12,  54+6,  54+7,  54+8 },
	{ 36+17,  36+8,  36+7,  36+6,   255,   255,   255,  36+0,  255,  54+13, 54+14, 54+15, 54+16, 54+17 }
};


void map_row_col_to_led( uint8_t row, uint8_t col, uint8_t *led )
{
	*led = 255;
	if ( row < MATRIX_ROWS && col < MATRIX_COLS )
	{
		*led = pgm_read_byte(&g_map_row_col_to_led[row][col]);
	}
}

void backlight_update_pwm_buffers(void)
{
	IS31FL3731_update_pwm_buffers( ISSI_ADDR_1, ISSI_ADDR_2 );
}

void backlight_set_color( int index, uint8_t red, uint8_t green, uint8_t blue )
{
	IS31FL3731_set_color( index, red, green, blue );
}

void backlight_set_color_all( uint8_t red, uint8_t green, uint8_t blue )
{
	IS31FL3731_set_color_all( red, green, blue );
}

void backlight_set_key_hit(uint8_t row, uint8_t col)
{
	uint8_t led;
	map_row_col_to_led(row,col,&led);
	g_key_hit[led] = 0;
}

// This is (F_CPU/1024) / 20 Hz
// = 15625 Hz / 20 Hz
// = 781
#define TIMER3_TOP 781

void backlight_timer_init(void)
{
	static uint8_t backlight_timer_is_init = 0;
	if ( backlight_timer_is_init )
	{
		return;
	}
	backlight_timer_is_init = 1;

	// Timer 3 setup
	TCCR3B = _BV(WGM32) | 			// CTC mode OCR3A as TOP
			 _BV(CS32) | _BV(CS30); // prescale by /1024
	// Set TOP value
	uint8_t sreg = SREG;
	cli();

	OCR3AH = (TIMER3_TOP >> 8) & 0xff;
	OCR3AL = TIMER3_TOP & 0xff;
	SREG = sreg;
}

void backlight_timer_enable(void)
{
	TIMSK3 |= _BV(OCIE3A);
}

void backlight_timer_disable(void)
{
	TIMSK3 &= ~_BV(OCIE3A);
}

void backlight_effect_test(void)
{
	uint8_t offset = (g_tick<<3) & 0xFF;
	// Relies on hue being 8-bit and wrapping
	HSV hsv = { .h = offset, .s = 255, .v = 127 };
	RGB rgb = hsv_to_rgb( hsv );

	backlight_set_color_all( rgb.r, rgb.g, rgb.b );
 }

// All LEDs off
void backlight_effect_all_off(void)
{
	backlight_set_color_all( 0, 0, 0 );
}

// Solid color
void backlight_effect_solid_color(void)
{
	HSV hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
	RGB rgb = hsv_to_rgb( hsv );
	backlight_set_color_all( rgb.r, rgb.g, rgb.b );
}

// alphas = color1, mods = color2
void backlight_effect_alphas_mods(void)
{
	RGB rgb1 = hsv_to_rgb( (HSV){ .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness } );
	RGB rgb2 = hsv_to_rgb( (HSV){ .h = g_config.color_2.h, .s = g_config.color_2.s, .v = g_config.brightness } );

	for ( int row = 0; row < MATRIX_ROWS; row++ )
	{
		for ( int col = 0; col < MATRIX_COLS; col++ )
		{
			uint8_t index;
			map_row_col_to_led( row, col, &index );
			if ( index < 72 )
			{
				if ( ( g_config.alphas_mods[row] & (0b0010000000000000>>col) ) == 0 )
				{
					backlight_set_color( index, rgb1.r, rgb1.g, rgb1.b );
				}
				else
				{
					backlight_set_color( index, rgb2.r, rgb2.g, rgb2.b );
				}
			}
		}
	}
}

void backlight_effect_gradient_up_down(void)
{
	int16_t h1 = g_config.color_1.h;
	int16_t h2 = g_config.color_2.h;
	int16_t delta = h2 - h1;

	// Take the shortest path between hues
	if ( delta > 127 )
	{
		delta -= 256;
	}
	else if ( delta < -127 )
	{
		delta += 256;
	}
	// Divide delta by 4, this gives the delta per row
	delta /= 4;

	HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
	RGB rgb;
	Point point;
	for ( int i=0; i<72; i++ )
	{
		map_led_to_point( i, &point );
		// The y range will be 0..64, map this to 0..4
		int16_t offset = delta * (point.y>>4);
		// Relies on hue being 8-bit and wrapping
		hsv.h = g_config.color_1.h + offset;
		rgb = hsv_to_rgb( hsv );
		backlight_set_color( i, rgb.r, rgb.g, rgb.b );
	}
}

void backlight_effect_cycle_all(void)
{
	uint8_t offset = g_tick & 0xFF;

	// Relies on hue being 8-bit and wrapping
	for ( int i=0; i<72; i++ )
	{
		uint16_t offset2 = g_key_hit[i]<<2;
		offset2 = (offset2<=63) ? (63-offset2) : 0;
		HSV hsv = { .h = offset+offset2, .s = 255, .v = g_config.brightness };
		RGB rgb = hsv_to_rgb( hsv );
		backlight_set_color( i, rgb.r, rgb.g, rgb.b );
	}
}

 void backlight_effect_cycle_left_right(void)
 {
	uint8_t offset = g_tick & 0xFF;
	HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
	RGB rgb;
	Point point;
	for ( int i=0; i<72; i++ )
	{
		map_led_to_point( i, &point );
		// Relies on hue being 8-bit and wrapping
		hsv.h = point.x + offset;
		rgb = hsv_to_rgb( hsv );
		backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}
 
void backlight_effect_cycle_up_down(void)
{
	uint8_t offset = g_tick & 0xFF;
	HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
	RGB rgb;
	Point point;
	for ( int i=0; i<72; i++ )
	{
		map_led_to_point( i, &point );
		// Relies on hue being 8-bit and wrapping
		hsv.h = point.y + offset;
		rgb = hsv_to_rgb( hsv );
		backlight_set_color( i, rgb.r, rgb.g, rgb.b );
	}
}

void backlight_effect_custom(void)
{
	HSV hsv;
	RGB rgb;
	for ( int i=0; i<72; i++ )
	{
		backlight_get_key_color(i, &hsv);
		// Override brightness with global brightness control
		hsv.v = g_config.brightness;
		rgb = hsv_to_rgb( hsv );
		backlight_set_color( i, rgb.r, rgb.g, rgb.b );
	}
}

ISR(TIMER3_COMPA_vect)
{
	g_tick++;

	// delay 1 second before driving LEDs
	if ( g_tick < 20 )
	{
		return;
	}

	for ( int led=0; led<72; led++ )
	{
		if ( g_key_hit[led] < 255 )
		{
			g_key_hit[led]++;
		}
	}

	// Store backlight config to EEPROM every 6.4 seconds
	// A slightly hacky way of reducing the number of EEPROM writes
	// should the user be hammering away on backlight changes
	// Paranoid? Probably...
	// Note this will only write if it's different, so it's safe to
	// call often.
	if ( ( g_tick & 0x7F ) == 0 )
	{
		backlight_config_save();
	}

#ifdef ZEAL60_TEST
	backlight_effect_test();
    return;
#endif

	// this gets ticked at 20 Hz.
	// each effect can opt to do calculations
	// and/or request PWM buffer updates.
	if ( g_config.effect == 0 )
	{
		backlight_effect_all_off();
	}
	else if ( g_config.effect == 1 )
	{
		backlight_effect_solid_color();
	}
	else if ( g_config.effect == 2 )
	{
		backlight_effect_alphas_mods();
	}
	else if ( g_config.effect == 3 )
	{
		backlight_effect_gradient_up_down();
	}
	else if ( g_config.effect == 4 )
	{
		backlight_effect_cycle_all();
	}
	else if ( g_config.effect == 5 )
	{
		backlight_effect_cycle_left_right();
	}
	else if ( g_config.effect == 6 )
	{
		backlight_effect_cycle_up_down();
	}
	else if ( g_config.effect >= 7 )
	{
		backlight_effect_custom();
	}
}

void backlight_config_set_flags(uint8_t flags)
{
	// TODO: replace with #define bitmasks
	g_config.use_split_backspace = ( flags&(1<<0) ? true : false );
	g_config.use_split_left_shift = ( flags&(1<<1) ? true : false );
	g_config.use_split_right_shift = ( flags&(1<<2) ? true : false );
	g_config.use_7u_spacebar = ( flags&(1<<3) ? true : false );
	g_config.use_iso_enter = ( flags&(1<<4) ? true : false );
}

void backlight_config_set_alphas_mods( uint16_t *alphas_mods )
{
	g_config.alphas_mods[0] = alphas_mods[0];
	g_config.alphas_mods[1] = alphas_mods[1];
	g_config.alphas_mods[2] = alphas_mods[2];
	g_config.alphas_mods[3] = alphas_mods[3];
	g_config.alphas_mods[4] = alphas_mods[4];
}

void backlight_config_load(void)
{
	void *addr = EEPROM_BACKLIGHT_CONFIG_ADDR;
	uint8_t flags = eeprom_read_byte(addr++);
	backlight_config_set_flags(flags);

	g_config.alphas_mods[0] = eeprom_read_byte( addr++ ) << 8;
	g_config.alphas_mods[0] |= eeprom_read_byte( addr++ );
	g_config.alphas_mods[1] = eeprom_read_byte( addr++ ) << 8;
	g_config.alphas_mods[1] |= eeprom_read_byte( addr++ );
	g_config.alphas_mods[2] = eeprom_read_byte( addr++ ) << 8;
	g_config.alphas_mods[2] |= eeprom_read_byte( addr++ );
	g_config.alphas_mods[3] = eeprom_read_byte( addr++ ) << 8;
	g_config.alphas_mods[3] |= eeprom_read_byte( addr++ );
	g_config.alphas_mods[4] = eeprom_read_byte( addr++ ) << 8;
	g_config.alphas_mods[4] |= eeprom_read_byte( addr++ );

	g_config.brightness = eeprom_read_byte( EEPROM_BACKLIGHT_CONFIG_ADDR+11 );
	g_config.effect = eeprom_read_byte( EEPROM_BACKLIGHT_CONFIG_ADDR+12 );
	g_config.color_1.h = eeprom_read_byte( EEPROM_BACKLIGHT_CONFIG_ADDR+13 );
	g_config.color_1.s = eeprom_read_byte( EEPROM_BACKLIGHT_CONFIG_ADDR+14 );
	g_config.color_1.v = eeprom_read_byte( EEPROM_BACKLIGHT_CONFIG_ADDR+15 );
	g_config.color_2.h = eeprom_read_byte( EEPROM_BACKLIGHT_CONFIG_ADDR+16 );
	g_config.color_2.s = eeprom_read_byte( EEPROM_BACKLIGHT_CONFIG_ADDR+17 );
	g_config.color_2.v = eeprom_read_byte( EEPROM_BACKLIGHT_CONFIG_ADDR+18 );
}

void backlight_config_save(void)
{
	// TODO: replace with #define bitmasks
	uint8_t flags = ( g_config.use_split_backspace ? (1<<0) : 0 ) |
					( g_config.use_split_left_shift ? (1<<1) : 0 ) |
					( g_config.use_split_right_shift ? (1<<2) : 0 ) |
					( g_config.use_7u_spacebar ? (1<<3) : 0 ) |
					( g_config.use_iso_enter ? (1<<4) : 0 );

	void *addr = EEPROM_BACKLIGHT_CONFIG_ADDR;
	eeprom_update_byte( addr++, flags );

	eeprom_update_byte( addr++, (uint8_t)(g_config.alphas_mods[0] >> 8) );
	eeprom_update_byte( addr++, (uint8_t)(g_config.alphas_mods[0] & 0xFF) );
	eeprom_update_byte( addr++, (uint8_t)(g_config.alphas_mods[1] >> 8) );
	eeprom_update_byte( addr++, (uint8_t)(g_config.alphas_mods[1] & 0xFF) );
	eeprom_update_byte( addr++, (uint8_t)(g_config.alphas_mods[2] >> 8) );
	eeprom_update_byte( addr++, (uint8_t)(g_config.alphas_mods[2] & 0xFF) );
	eeprom_update_byte( addr++, (uint8_t)(g_config.alphas_mods[3] >> 8) );
	eeprom_update_byte( addr++, (uint8_t)(g_config.alphas_mods[3] & 0xFF) );
	eeprom_update_byte( addr++, (uint8_t)(g_config.alphas_mods[4] >> 8) );
	eeprom_update_byte( addr++, (uint8_t)(g_config.alphas_mods[4] & 0xFF) );

	eeprom_update_byte( addr++, g_config.brightness );
	eeprom_update_byte( addr++, g_config.effect );
	eeprom_update_byte( addr++, g_config.color_1.h );
	eeprom_update_byte( addr++, g_config.color_1.s );
	eeprom_update_byte( addr++, g_config.color_1.v );
	eeprom_update_byte( addr++, g_config.color_2.h );
	eeprom_update_byte( addr++, g_config.color_2.s );
	eeprom_update_byte( addr++, g_config.color_2.v );


}

void backlight_init_drivers(void)
{
	uint8_t enable_led_LB5 = g_config.use_split_backspace;
	uint8_t enable_led_LC15 = g_config.use_split_left_shift;
	uint8_t enable_led_LD8 = g_config.use_split_right_shift;
	uint8_t enable_led_LD13 = g_config.use_7u_spacebar ? 0 : 1;
	
	sei();

	// Initialize TWI
	TWIInit();

	_delay_ms(100);	
		
	IS31FL3731_init( ISSI_ADDR_1 );
	
	_delay_ms(100);
			
	IS31FL3731_init( ISSI_ADDR_2 );

	_delay_ms(100);
				
	// This is how you define which LEDs are present in the matrix.
	// If you don't turn off missing LEDs, the LED driver doesn't work properly.

	// This is the bit pattern in the LED control registers
	// (per matrix)
	//
	// R08,R07,R06,R05,R04,R03,R02,R01
	// G08,G07,G06,G05,G04,G03,G02,R00
	// B08,B07,B06,B05,B04,B03,G01,G00
	//  - , - , - , - , - ,B02,B01,B00
	//  - , - , - , - , - , - , - , -
	// B17,B16,B15, - , - , - , - , -
	// G17,G16,B14,B13,B12,B11,B19,B09
	// R17,G15,G14,G13,G12,G11,G10,G09
	// R16,R15,R14,R13,R12,R11,R10,R09
	//
	// I could probably write some fancy wrapper for this to allow easy
	// reconfiguration, but it's really too much work and will probably use
	// up program/data. Easier to just work out which LEDs are not being used
	// by referencing the Nth LED per matrix and replacing some 1s with 0s below.
	//
	// Since this never needs to change at runtime, and only happens once,
	// it doesn't matter that it's 36 discrete calls ;-)
	//

	// Driver 1, Matrix A (LA0-LA17)
	IS31FL3731_write_register(ISSI_ADDR_1, 0x00, 0b11111111 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x02, 0b11111111 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x04, 0b11111111 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x06, 0b00000111 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x08, 0b00000000 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x0A, 0b11100000 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x0C, 0b11111111 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x0E, 0b11111111 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x10, 0b11111111 );

	// Driver 1, Matrix B (LB0-LB17)
	// Disabled LB6 LB7 LB8 LB15 LB16 LB17
	// Not present on Zeal60. Present on Zeal65
	
	IS31FL3731_write_register(ISSI_ADDR_1, 0x01, 0b00001111 | (enable_led_LB5<<4));
	IS31FL3731_write_register(ISSI_ADDR_1, 0x03, 0b00001111 | (enable_led_LB5<<4));
	IS31FL3731_write_register(ISSI_ADDR_1, 0x05, 0b00001111 | (enable_led_LB5<<4));
	IS31FL3731_write_register(ISSI_ADDR_1, 0x07, 0b00000111 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x09, 0b00000000 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x0B, 0b00000000 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x0D, 0b00111111 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x0F, 0b00111111 );
	IS31FL3731_write_register(ISSI_ADDR_1, 0x11, 0b00111111 );

	// Driver 2, Matrix A (LC0-LC17)
	IS31FL3731_write_register(ISSI_ADDR_2, 0x00, 0b11111111 );
	IS31FL3731_write_register(ISSI_ADDR_2, 0x02, 0b11111111 );
	IS31FL3731_write_register(ISSI_ADDR_2, 0x04, 0b11111111 );
	IS31FL3731_write_register(ISSI_ADDR_2, 0x06, 0b00000111 );
	IS31FL3731_write_register(ISSI_ADDR_2, 0x08, 0b00000000 );
	IS31FL3731_write_register(ISSI_ADDR_2, 0x0A, 0b11000000 | (enable_led_LC15<<5));
	IS31FL3731_write_register(ISSI_ADDR_2, 0x0C, 0b11111111 );
	IS31FL3731_write_register(ISSI_ADDR_2, 0x0E, 0b10111111 | (enable_led_LC15<<6));
	IS31FL3731_write_register(ISSI_ADDR_2, 0x10, 0b10111111 | (enable_led_LC15<<6));

	// Driver 2, Matrix B (LD0-LD17)
	IS31FL3731_write_register(ISSI_ADDR_2, 0x01, 0b01111111 | (enable_led_LD8<<7));
	IS31FL3731_write_register(ISSI_ADDR_2, 0x03, 0b01111111 | (enable_led_LD8<<7));
	IS31FL3731_write_register(ISSI_ADDR_2, 0x05, 0b01111111 | (enable_led_LD8<<7));
	IS31FL3731_write_register(ISSI_ADDR_2, 0x07, 0b00000111 );
	IS31FL3731_write_register(ISSI_ADDR_2, 0x09, 0b00000000 );
	IS31FL3731_write_register(ISSI_ADDR_2, 0x0B, 0b11100000 );
	IS31FL3731_write_register(ISSI_ADDR_2, 0x0D, 0b11101111 | (enable_led_LD13<<4));
	IS31FL3731_write_register(ISSI_ADDR_2, 0x0F, 0b11101111 | (enable_led_LD13<<4));
	IS31FL3731_write_register(ISSI_ADDR_2, 0x11, 0b11101111 | (enable_led_LD13<<4));

	// TODO: put the 1 second startup delay here?

	// clear the key hits
	for ( int led=0; led<72; led++ )
	{
		g_key_hit[led] = 255;
	}
}


// Deals with the messy details of incrementing an integer
uint8_t increment( uint8_t value, uint8_t step, uint8_t max )
{
	int16_t new_value = value;
	new_value += step;
	return ( new_value <= max ) ? new_value : max;
}

uint8_t decrement( uint8_t value, uint8_t step, uint8_t min )
{
	int16_t new_value = value;
	new_value -= step;
	return ( new_value >= min ) ? new_value : min;
}

void backlight_effect_increase(void)
{
	g_config.effect = increment( g_config.effect, 1, BACKLIGHT_EFFECT_MAX );
	backlight_config_save();
}

void backlight_effect_decrease(void)
{
	g_config.effect = decrement( g_config.effect, 1, 0 );
	backlight_config_save();
}

void backlight_brightness_increase(void)
{
	g_config.brightness = increment( g_config.brightness, 8, 255 );
	backlight_config_save();
}

void backlight_brightness_decrease(void)
{
	g_config.brightness = decrement( g_config.brightness, 8, 0 );
	backlight_config_save();
}

void backlight_color_1_hue_increase(void)
{
	g_config.color_1.h = increment( g_config.color_1.h, 8, 255 );
	backlight_config_save();
}

void backlight_color_1_hue_decrease(void)
{
	g_config.color_1.h = decrement( g_config.color_1.h, 8, 0 );
	backlight_config_save();
}

void backlight_color_1_sat_increase(void)
{
	g_config.color_1.s = increment( g_config.color_1.s, 8, 255 );
	backlight_config_save();
}

void backlight_color_1_sat_decrease(void)
{
	g_config.color_1.s = decrement( g_config.color_1.s, 8, 0 );
	backlight_config_save();
}

void backlight_color_2_hue_increase(void)
{
	g_config.color_2.h = increment( g_config.color_2.h, 8, 255 );
	backlight_config_save();
}

void backlight_color_2_hue_decrease(void)
{
	g_config.color_2.h = decrement( g_config.color_2.h, 8, 0 );
	backlight_config_save();
}

void backlight_color_2_sat_increase(void)
{
	g_config.color_2.s = increment( g_config.color_2.s, 8, 255 );
	backlight_config_save();
}

void backlight_color_2_sat_decrease(void)
{
	g_config.color_2.s = decrement( g_config.color_2.s, 8, 0 );
	backlight_config_save();
}

void *backlight_get_custom_key_color_eeprom_address( uint8_t led )
{
	// 3 bytes per color
	return EEPROM_BACKLIGHT_KEY_COLOR_ADDR + ( led * 3 );
}

void backlight_get_key_color( uint8_t led, HSV *hsv )
{
	void *address = backlight_get_custom_key_color_eeprom_address( led );
	hsv->h = eeprom_read_byte(address);
	hsv->s = eeprom_read_byte(address+1);
	hsv->v = eeprom_read_byte(address+2);
}

void backlight_set_key_color( uint8_t row, uint8_t col, HSV hsv )
{
	uint8_t led;
	map_row_col_to_led( row, col, &led );
	if ( led < 72 )
	{
		void *address = backlight_get_custom_key_color_eeprom_address(led);
		eeprom_update_byte(address, hsv.h);
		eeprom_update_byte(address+1, hsv.s);
		eeprom_update_byte(address+2, hsv.v);
	}
}
