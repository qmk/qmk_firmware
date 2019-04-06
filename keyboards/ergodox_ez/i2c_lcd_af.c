#include QMK_KEYBOARD_H

/* The backpack uses nearly the same chip as the left hand. The
 * left hand uses 0x20 as its base i2c address. The backpack has
 * jumpers for address bits. For instance, if you solder the A0
 * jumper, you would set I2CLCD_PORT to 1.
 */
#define LCD_ADDR (0x20 | (I2CLCD_PORT))
#define LCD_ADDR_WRITE  ( (LCD_ADDR<<1) | I2C_WRITE )
#define LCD_ADDR_READ   ( (LCD_ADDR<<1) | I2C_READ  )

#define MCP23008_IODIR 0x00
#define MCP23008_GPIO 0x09

#define MCP23008_RS 0x2
#define MCP23008_ENABLE 0x4
#define MCP23008_DATA (0xF << 3)
#define MCP23008_BACKLIGHT 0x80

// add-on: mcp23008 used to drive a 4x20 LCD
static uint8_t mcp23008_status = 0x0;
static uint8_t mcp23008_gpio = 0x0;

static inline uint8_t
mcp23008_writeport(uint8_t port, uint8_t value) {
    mcp23008_status = i2c_start(LCD_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);    if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(port, ERGODOX_EZ_I2C_TIMEOUT);              if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(value, ERGODOX_EZ_I2C_TIMEOUT);	            if (mcp23008_status) goto out;
out:
    i2c_stop();
    return mcp23008_status;
}

static uint8_t
lcd_setpins(void) {
    return mcp23008_writeport(MCP23008_GPIO, mcp23008_gpio);
}

static uint8_t
lcd_write4(uint8_t value) {
    mcp23008_gpio = (mcp23008_gpio & ~MCP23008_DATA) | ((value & 0xF) << 3);
    mcp23008_status = lcd_setpins();                if (mcp23008_status) goto out;
    mcp23008_gpio |= MCP23008_ENABLE;
    mcp23008_status = lcd_setpins();                if (mcp23008_status) goto out;
    mcp23008_gpio &= ~MCP23008_ENABLE;
    mcp23008_status = lcd_setpins();                if (mcp23008_status) goto out;
out:
    return mcp23008_status;
}

static uint8_t
lcd_write8(uint8_t value) {
    mcp23008_status = lcd_write4((value >> 4) & 0xF); if (mcp23008_status) goto out;
    mcp23008_status = lcd_write4(value & 0xF);        if (mcp23008_status) goto out;
out:
    return mcp23008_status;
}

static uint8_t
lcd_command(uint8_t c) {
    mcp23008_gpio &= ~MCP23008_RS;
    mcp23008_status = lcd_write8(c);
    // note: you need to delay about 37us after most commands...
    // but that's longer than it takes us to write a single set of gpio bits,
    // so no delay is actually needed.
    return mcp23008_status;
}

uint8_t
lcd_move(int row, int col) {
    row %= 4;
    col %= 20;
    // 0xA * (row & 2) = 0x14 if the high order bit is set.
    // the display order puts row 2 exactly 20 characters past row 0,
    // and then row 3 exactly 20 characters past row 1, but this omits
    // a shift
    uint8_t addr = 0xA * (row & 2) + 0x40 * (row & 1);
    return lcd_command(0x80 | (addr + col));
}

uint8_t
lcd_char(uint8_t c) {
    mcp23008_gpio |= MCP23008_RS;
    return lcd_write8(c);
}

uint8_t
lcd_string(char *s, int len) {
    // cap at one line or end of string
    if (len < 1)
        len = 20;
    for (int i = 0; *s && (i < len); ++i, ++s) {
        if (lcd_char(*s))
            return mcp23008_status;
    }
    return 0;
}

uint8_t
lcd_clear(void) {
    // clear, which needs a bit over 1ms delay
    lcd_command(0x01);
    if (!mcp23008_status)
        _delay_ms(2);
    return mcp23008_status;
}

void lcd_init(void) {
    uint8_t stopped = 1;
    // init code for mcp23008 and LCD
    mcp23008_status = 0x20;
    stopped = 0;
    mcp23008_status = i2c_start(LCD_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT); if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(MCP23008_IODIR, ERGODOX_EZ_I2C_TIMEOUT); if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0xFF, ERGODOX_EZ_I2C_TIMEOUT);		 if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00, ERGODOX_EZ_I2C_TIMEOUT);		 if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00, ERGODOX_EZ_I2C_TIMEOUT);		 if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00, ERGODOX_EZ_I2C_TIMEOUT);		 if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00, ERGODOX_EZ_I2C_TIMEOUT);		 if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00, ERGODOX_EZ_I2C_TIMEOUT);		 if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00, ERGODOX_EZ_I2C_TIMEOUT);		 if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00, ERGODOX_EZ_I2C_TIMEOUT);		 if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00, ERGODOX_EZ_I2C_TIMEOUT);		 if (mcp23008_status) goto out;
    mcp23008_status = i2c_write(0x00, ERGODOX_EZ_I2C_TIMEOUT);		 if (mcp23008_status) goto out;
    i2c_stop();
    stopped = 1;
    // IODIR: 1 == input. We want everything but pin 0 to be an output.
    mcp23008_status = mcp23008_writeport(MCP23008_IODIR, 0x01);    if (mcp23008_status) goto out;
    // turn on the backlight pin. don't turn on any others, which
    // means that RS and ENABLE are now off...
    mcp23008_gpio = MCP23008_BACKLIGHT;
    mcp23008_status = lcd_setpins();             if (mcp23008_status) goto out;
    lcd_write4(0x03);				 if (mcp23008_status) goto out;
    _delay_us(4150);
    lcd_write4(0x03);				 if (mcp23008_status) goto out;
    _delay_us(4150);
    lcd_write4(0x03);				 if (mcp23008_status) goto out;
    _delay_us(150);
    lcd_write4(0x02);				 if (mcp23008_status) goto out;
    // mode settings
    lcd_command(0x28);				 if (mcp23008_status) goto out;
    lcd_command(0x0C);				 if (mcp23008_status) goto out;
    lcd_clear();
    lcd_command(0x06);				 if (mcp23008_status) goto out;
out:
    if (!stopped)
	    i2c_stop();
}

// can't set backlight to anything but on or off
uint8_t
lcd_backlight(uint8_t brightness) {
    if (brightness) {
    	mcp23008_gpio |= MCP23008_BACKLIGHT;
    } else {
    	mcp23008_gpio &= ~MCP23008_BACKLIGHT;
    }
    return lcd_setpins();
}

// no default update, but you could define one if you wanted to
__attribute__ ((weak))
void lcd_update_user(matrix_row_t *matrix) { }

uint8_t reset_counter = 0;

void
lcd_update(matrix_row_t *matrix) {
    if (mcp23008_status) {
    	++reset_counter;
	if (reset_counter == 0) {
	    // try to reset display.
	    lcd_init();
	}
    }
    lcd_update_user(matrix);
}

