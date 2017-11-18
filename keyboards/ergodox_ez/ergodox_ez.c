#include QMK_KEYBOARD_H
#include "i2cmaster.h"
#include <ctype.h>


extern inline void ergodox_board_led_on(void);
extern inline void ergodox_right_led_1_on(void);
extern inline void ergodox_right_led_2_on(void);
extern inline void ergodox_right_led_3_on(void);
extern inline void ergodox_right_led_on(uint8_t led);

extern inline void ergodox_board_led_off(void);
extern inline void ergodox_right_led_1_off(void);
extern inline void ergodox_right_led_2_off(void);
extern inline void ergodox_right_led_3_off(void);
extern inline void ergodox_right_led_off(uint8_t led);

extern inline void ergodox_led_all_on(void);
extern inline void ergodox_led_all_off(void);

extern inline void ergodox_right_led_1_set(uint8_t n);
extern inline void ergodox_right_led_2_set(uint8_t n);
extern inline void ergodox_right_led_3_set(uint8_t n);
extern inline void ergodox_right_led_set(uint8_t led, uint8_t n);

extern inline void ergodox_led_all_set(uint8_t n);


bool i2c_initialized = 0;
// left hand: mcp23018 expander
uint8_t mcp23018_status = 0x20;
// add-on: mcp23008 used to drive a 4x20 LCD
uint8_t mcp23008_status = 0x0;
uint8_t mcp23008_gpio = 0x0;
static uint8_t *state, *chord;

static inline uint8_t mcp23008_writeport(uint8_t port, uint8_t value) {
    mcp23008_status = i2c_start(LCD_ADDR_WRITE);    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(port);     if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(value);	    if (mcp23008_status) goto out;
out:
    i2c_stop();
    if (mcp23008_status)
        ergodox_right_led_1_on();
    return mcp23008_status;
}

uint8_t lcd_setpins(void) {
    return mcp23008_writeport(MCP23008_GPIO, mcp23008_gpio);
}

uint8_t lcd_write4(uint8_t value) {
    mcp23008_gpio = (mcp23008_gpio & ~MCP23008_DATA) | ((value & 0xF) << 3);
    mcp23008_status = lcd_setpins();                  if (mcp23008_status) goto out;
    mcp23008_gpio |= MCP23008_ENABLE;
    mcp23008_status = lcd_setpins();                  if (mcp23008_status) goto out;
    mcp23008_gpio &= ~MCP23008_ENABLE;
    mcp23008_status = lcd_setpins();                  if (mcp23008_status) goto out;
out:
    return mcp23008_status;
}

uint8_t lcd_write8(uint8_t value) {
    mcp23008_status = lcd_write4((value >> 4) & 0xF); if (mcp23008_status) goto out;
    mcp23008_status = lcd_write4(value & 0xF);        if (mcp23008_status) goto out;
out:
    return mcp23008_status;
}

uint8_t lcd_command(uint8_t c) {
    mcp23008_gpio &= ~MCP23008_RS;
    mcp23008_status = lcd_write8(c);
    // allow command to complete
    _delay_us(50);
    return mcp23008_status;
}

void
lcd_move(int row, int col) {
    row %= 4;
    col %= 20;
    // 0xA * (row & 2) = 0x14 if the high order bit is set.
    // the display order puts row 2 exactly 20 characters past row 0,
    // and then row 3 exactly 20 characters past row 1, but this omits
    // a shift
    uint8_t addr = 0xA * (row & 2) + 0x40 * (row & 1);
    lcd_command(0x80 | (addr + col));
}

uint8_t lcd_char(uint8_t c) {
    mcp23008_gpio |= MCP23008_RS;
    return lcd_write8(c);
}

uint8_t init_lcd(void) {
    state = steno_get_state();
    chord = steno_get_chord();
    uint8_t stopped = 1;
    // init code for mcp23008 and LCD
    mcp23008_status = 0x20;
    stopped = 0;
    mcp23008_status = i2c_start(LCD_ADDR_WRITE);    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(MCP23008_IODIR);    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0xFF);		    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00);		    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00);		    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00);		    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00);		    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00);		    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00);		    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00);		    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00);		    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00);		    if (mcp23008_status) goto out;
    i2c_stop();
    stopped = 1;
    mcp23008_status = mcp23008_writeport(MCP23008_IODIR, 0x01);    if (mcp23008_status) goto out;
    // turn on the backlight pin. don't turn on any others, which
    // means that RS and ENABLE are now off...
    // mcp23008_gpio = MCP23008_BACKLIGHT;
    mcp23008_gpio = MCP23008_BACKLIGHT;
    mcp23008_status = lcd_setpins();                if (mcp23008_status) goto out;
    _delay_ms(50);
    mcp23008_gpio &= ~MCP23008_BACKLIGHT;
    mcp23008_status = lcd_setpins();                if (mcp23008_status) goto out;
    lcd_write4(0x03);
    _delay_us(4150);
    lcd_write4(0x03);
    _delay_us(4150);
    lcd_write4(0x03);
    _delay_us(150);
    lcd_write4(0x02);
    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x01);
    _delay_ms(2);
    lcd_command(0x06);
    lcd_move(0, 0);
    lcd_char('y');
    lcd_char('o');
    lcd_char('.');
    _delay_ms(100);
    mcp23008_gpio |= MCP23008_BACKLIGHT;
    mcp23008_status = lcd_setpins();                if (mcp23008_status) goto out;
    _delay_ms(100);
    mcp23008_gpio &= ~MCP23008_BACKLIGHT;
    mcp23008_status = lcd_setpins();                if (mcp23008_status) goto out;
    _delay_ms(100);
    mcp23008_gpio |= MCP23008_BACKLIGHT;
    mcp23008_status = lcd_setpins();                if (mcp23008_status) goto out;
out:
    if (!stopped)
	    i2c_stop();
    return mcp23008_status;
}

static char *display      = "?######SSTKPWHRAO**???**EUFRPBLGTSD######Z";
// A = position 1...
// position Z isn't displayed, it's there for "don't display this"

// #STKPWHR*FRPBLGTSDZ
//       AO EU
// static char *displaypos = "WAAAAAABBCDEFGHUVIIWWWIIXYJKLMNOPQRAAAAAAS";

// #TPH FPLTD
// SKWR*RBGSZ
//   AO?EU
static char *displaypos = "WAAAAAAKKBLCMDNUVOOWWWOOXYFPGQHRISJAAAAAAT";
static uint8_t counter = 0;
static uint8_t prev_state[6];
static uint8_t prev_chord[6];
void update_lcd(void) {
    if (!memcmp(state, prev_state, 6))
        return;
    memcpy(prev_state, state, 6);
    char keys[26];
    int pressed = 0;

    memset(keys, ' ', 25);
    for (int i = 0; i < 6; ++i) {
	for (int j = 0; j < 7; ++j) {
	    uint8_t bit = 1 << j;
	    uint8_t idx = (i * 7) + (6 - j);
	    if (chord[i] & bit) {
		++pressed;
	        uint8_t pos = displaypos[idx] - 'A';
		uint8_t ch = display[idx];
		keys[pos] = ch;
		if (ch == '*') {
		    keys[pos - 10] = (state[i] & bit) ? ch : ' ';
		}
		if (!(state[i] & bit)) {
		    keys[pos] = tolower(keys[pos]);
		}
	    }
	}
    }
    lcd_move(0, 0);
    for (int i = 0; i < 10; ++i) {
    	lcd_char(keys[i]);
    }
    lcd_move(1, 0);
    for (int i = 10; i < 20; ++i) {
    	lcd_char(keys[i]);
    }
    lcd_move(2, 2);
    for (int i = 20; i < 25; ++i) {
        lcd_char(keys[i]);
    }
    if (!pressed) {
	    memset(keys, ' ', 25);
	    for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 7; ++j) {
		    uint8_t bit = 1 << j;
		    uint8_t idx = (i * 7) + (6 - j);
		    if (prev_chord[i] & bit) {
			uint8_t pos = displaypos[idx] - 'A';
			uint8_t ch = display[idx];
			keys[pos] = ch;
		    }
		}
	    }
	    char *k = keys;
	    for (int i = 0; i < 25; ++i) {
	        if (keys[i] != ' ') {
		    *k++ = keys[i];
		}
	    }
	    // help my children are starving
	    // push fewer keys at once
	    // no
	    if ((k - keys) > 20) {
	        keys[17] = '.';
	        keys[18] = '.';
	        keys[19] = '.';
	    } else {
		    for (int i = (k - keys) + 1; i < 20; ++i) {
			keys[i] = ' ';
		    }
	    }
	    lcd_move(3, 0);
	    for (int i = 0; i < 20; ++i) {
	        lcd_char(keys[i]);
	    }
    }
    lcd_move(0, 17);
    snprintf(keys, 5, "%3d", counter++);
    for (int i = 0; i < 3; ++i) {
        lcd_char(keys[i]);
    }
    memcpy(prev_chord, chord, 6);
}

void matrix_init_kb(void) {
   // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM

    // (tied to Vcc for hardware convenience)
    DDRB  &= ~(1<<4);  // set B(4) as input
    PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled

    // unused pins - C7, D4, D5, D7, E6
    // set as input with internal pull-ip enabled
    DDRC  &= ~(1<<7);
    DDRD  &= ~(1<<5 | 1<<4);
    DDRE  &= ~(1<<6);
    PORTC |=  (1<<7);
    PORTD |=  (1<<5 | 1<<4);
    PORTE |=  (1<<6);

    ergodox_blink_all_leds();

    matrix_init_user();
}

void ergodox_blink_all_leds(void)
{
    ergodox_led_all_off();
    ergodox_led_all_set(LED_BRIGHTNESS_DEFAULT);
    ergodox_right_led_1_on();
    _delay_ms(50);
    ergodox_right_led_2_on();
    _delay_ms(50);
    ergodox_right_led_3_on();
    _delay_ms(50);
#ifdef LEFT_LEDS
    ergodox_left_led_1_on();
    _delay_ms(50);
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
    ergodox_left_led_2_on();
    _delay_ms(50);
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
    ergodox_left_led_3_on();
    _delay_ms(50);
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
#endif
    ergodox_right_led_1_off();
    _delay_ms(50);
    ergodox_right_led_2_off();
    _delay_ms(50);
    ergodox_right_led_3_off();
#ifdef LEFT_LEDS
    _delay_ms(50);
    ergodox_left_led_1_off();
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
    _delay_ms(50);
    ergodox_left_led_2_off();
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
    _delay_ms(50);
    ergodox_left_led_3_off();
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
#endif
    
    //ergodox_led_all_on();
    //_delay_ms(333);
    ergodox_led_all_off();
}

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();
    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
    }

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA);            if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111);        if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111);        if (mcp23018_status) goto out;

out:
    i2c_stop();

#ifdef LEFT_LEDS
    if (!mcp23018_status) mcp23018_status = ergodox_left_leds_update();
#endif // LEFT_LEDS

    // SREG=sreg_prev;

    return mcp23018_status;
}

#ifdef LEFT_LEDS
uint8_t ergodox_left_leds_update(void) {
    if (mcp23018_status) { // if there was an error
        return mcp23018_status;
    }
#define LEFT_LED_1_SHIFT        7       // in MCP23018 port B
#define LEFT_LED_2_SHIFT        6       // in MCP23018 port B
#define LEFT_LED_3_SHIFT        7       // in MCP23018 port A

    // set logical value (doesn't matter on inputs)
    // - unused  : hi-Z : 1
    // - input   : hi-Z : 1
    // - driving : hi-Z : 1
    mcp23018_status = i2c_start(I2C_ADDR_WRITE);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(OLATA);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111
                                & ~(ergodox_left_led_3<<LEFT_LED_3_SHIFT)
                                );
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111
                                & ~(ergodox_left_led_2<<LEFT_LED_2_SHIFT)
                                & ~(ergodox_left_led_1<<LEFT_LED_1_SHIFT)
                                );
    if (mcp23018_status) goto out;

 out:
    i2c_stop();
    return mcp23018_status;
}
#endif


#ifdef ONEHAND_ENABLE
__attribute__ ((weak))
// swap-hands action needs a matrix to define the swap
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0,13}, {1,13}, {2,13}, {3,13}, {4,13}, {5,13}},
    {{0,12}, {1,12}, {2,12}, {3,12}, {4,12}, {5,12}},
    {{0,11}, {1,11}, {2,11}, {3,11}, {4,11}, {5,11}},
    {{0,10}, {1,10}, {2,10}, {3,10}, {4,10}, {5,10}},
    {{0,9}, {1,9}, {2,9}, {3,9}, {4,9}, {5,9}},
    {{0,8}, {1,8}, {2,8}, {3,8}, {4,8}, {5,8}},
    {{0,7}, {1,7}, {2,7}, {3,7}, {4,7}, {5,7}},
    /* Right hand, matrix positions */
    {{0,6}, {1,6}, {2,6}, {3,6}, {4,6}, {5,6}},
    {{0,5}, {1,5}, {2,5}, {3,5}, {4,5}, {5,5}},
    {{0,4}, {1,4}, {2,4}, {3,4}, {4,4}, {5,4}},
    {{0,3}, {1,3}, {2,3}, {3,3}, {4,3}, {5,3}},
    {{0,2}, {1,2}, {2,2}, {3,2}, {4,2}, {5,2}},
    {{0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}},
    {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}},
};
#endif
