#include QMK_KEYBOARD_H

/* This drives a custom lcd driver I built using an atmega
 * chip because it's way faster than the adafruit one based
 * on a gpio expander
 *
 * https://github.com/seebs/lcd_tiny
 *
 * This is badly under-documented, but if anyone wants to
 * make these or clean it up, you go right ahead.
 */
#define LCD_ADDR (0x32 | (I2CLCD_PORT))
#define LCD_ADDR_WRITE  ( (LCD_ADDR<<1) | I2C_WRITE )
#define LCD_ADDR_READ   ( (LCD_ADDR<<1) | I2C_READ  )

/* Protocol:
 * Printable ASCII characters, and 0x00 through 0x0F, are simply
 * passed on as characters to write. Values from 0x10 through 0x1F
 * are potentially commands. Specifically:
 *
 * 0x10: no operation
 * 0x11: move, next byte ((row << 5) | (col & 0x1F)
 * 0x12: brightness, next byte backlight PWM duty cycle (0-255)
 * 0x13: setcgram: next byte address, then 8 bytes of graphic data
 * 0x14: clear
 */

uint8_t lcd_status;

static inline uint8_t
i2c_startw(uint8_t addr) {
	uint8_t ret;
	for (int i = 0; i < 10; ++i) {
		ret = i2c_start(addr, ERGODOX_EZ_I2C_TIMEOUT);
		if (!ret)
			break;
	}
	return ret;
}


uint8_t
lcd_move(int row, int col) {
    uint8_t addr = ((row & 3) << 5) | (col & 0x1F);
    // xprintf("lcd_move[%d,%d] => %d | %d", row, col, addr & 0xE0, addr & 0x1F);
    lcd_status = i2c_startw(LCD_ADDR_WRITE);	if (lcd_status) goto out;
    lcd_status = i2c_write(0x11, ERGODOX_EZ_I2C_TIMEOUT);		if (lcd_status) goto out;
    lcd_status = i2c_write(addr, ERGODOX_EZ_I2C_TIMEOUT);		if (lcd_status) goto out;
out:
    i2c_stop();
    // xprintf("->%d\n", lcd_status);
    return lcd_status;
}

uint8_t
lcd_char(uint8_t c) {
    // xprintf("lcd_char(%c)", c);
    lcd_status = i2c_startw(LCD_ADDR_WRITE);	if (lcd_status) goto out;
    lcd_status = i2c_write(c, ERGODOX_EZ_I2C_TIMEOUT);			if (lcd_status) goto out;
out:
    i2c_stop();
    // xprintf("->%d\n", lcd_status);
    return lcd_status;
}

uint8_t
lcd_string(char *s, int len) {
    if (len < 1)
        len = 20;
    // xprintf("lcd_string(%s)", s);
    lcd_status = i2c_startw(LCD_ADDR_WRITE);	if (lcd_status) goto out;
    for (int i = 0; *s && (i < len); ++i, ++s) {
    	if (i2c_write(*s, ERGODOX_EZ_I2C_TIMEOUT))
	    goto out;
    }
out:
    i2c_stop();
    // xprintf("->%d\n", lcd_status);
    return lcd_status;
}

uint8_t
lcd_clear(void) {
    lcd_status = i2c_startw(LCD_ADDR_WRITE);	if (lcd_status) goto out;
    lcd_status = i2c_write(0x14, ERGODOX_EZ_I2C_TIMEOUT);		if (lcd_status) goto out;
out:
    i2c_stop();
    return lcd_status;
}

uint8_t
lcd_backlight(uint8_t brightness) {
    lcd_status = i2c_startw(LCD_ADDR_WRITE);	if (lcd_status) goto out;
    lcd_status = i2c_write(0x12, ERGODOX_EZ_I2C_TIMEOUT);		if (lcd_status) goto out;
    lcd_status = i2c_write(brightness, ERGODOX_EZ_I2C_TIMEOUT);		if (lcd_status) goto out;
out:
    i2c_stop();
    return lcd_status;
}

void lcd_init(void) {
    lcd_backlight(0);
    lcd_clear();
    // nothing to do, the other end did it already
}

// no default update, but you could define one if you wanted to
__attribute__ ((weak))
void lcd_update_user(matrix_row_t *matrix) { }

uint8_t reset_counter = 0;

void
lcd_update(matrix_row_t *matrix) {
    lcd_update_user(matrix);
}
