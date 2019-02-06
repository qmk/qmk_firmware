#ifdef SSD1306OLED

#include "ssd1306.h"
#include "i2c_master.h"
#include "common/glcdfont.c"

#include <string.h>

// Used commands from spec sheet: https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
// Fundamental Commands
#define CONTRAST                0x81
#define DISPLAY_ALL_ON          0xA5
#define DISPLAY_ALL_ON_RESUME   0xA4
#define NORMAL_DISPLAY          0xA6
#define DISPLAY_ON              0xAF
#define DISPLAY_OFF             0xAE

// Scrolling Commands
#define DEACTIVATE_SCROLL       0x2E

// Addressing Setting Commands
#define MEMORY_MODE             0x20
#define COLUMN_ADDR             0x21
#define PAGE_ADDR               0x22

// Hardware Configuration Commands
#define DISPLAY_START_LINE      0x40
#define SEGMENT_REMAP           0xA0
#define SEGMENT_REMAP_INV       0xA1
#define MULTIPLEX_RATIO         0xA8
#define COM_SCAN_INC            0xC0
#define COM_SCAN_DEC            0xC8
#define DISPLAY_OFFSET          0xD3
#define COM_PINS                0xDA

// Timing & Driving Commands
#define DISPLAY_CLOCK           0xD5
#define PRE_CHARGE_PERIOD       0xD9
#define VCOM_DETECT             0xDB

// Charge Pump Commands
#define CHARGE_PUMP             0x8D

// Misc defines
#define SSD1306_ADDRESS (0x3C << 1)
#define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8) * OLED_DISPLAY_WIDTH

// i2c defines
#define I2C_TIMEOUT 100
#define I2C_SEND_CMD(data) i2c_writeReg_P(SSD1306_ADDRESS, 0x00, &data[0], sizeof(data), I2C_TIMEOUT)
#define I2C_SEND_DATA(data) i2c_writeReg(SSD1306_ADDRESS, 0x40, &data[0], sizeof(data), I2C_TIMEOUT)

#define OLED_DEBUGGING
#ifdef OLED_DEBUGGING
#include "print.h"
// These debug prints are designed to work with 0 = success and all other failure.
#define DEBUG_PRINT(Func, Msg) if (Func) print(Msg)
#define DEBUG_XPRINTF_RESULT(Func, Msg, Res) if (!Res && (Res = Func)) xprintf(Msg, Res)
#else
#define DEBUG_PRINT(Func, Msg) Func
#define DEBUG_XPRINTF_RESULT(Func, Msg, Res) Res |= Func
#endif


// Display buffer's is the same as the OLED memory layout
// this is so we don't end up with rounding errors with 
// parts of the display unusable or don't get cleared correctly
// and also allows for drawing & inverting
static uint8_t  display_buffer[OLED_MATRIX_SIZE];
static uint8_t* display_cursor;
static bool     display_dirty = false;
static bool     display_initialized = false;


// identical to i2c_writeReg, but for PROGMEM since all initialization is in PROGMEM arrays currently
static i2c_status_t i2c_writeReg_P(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout)
{
    i2c_status_t status = i2c_start(devaddr | 0x00, timeout);
    if (status) return status;

    status = i2c_write(regaddr, timeout);
    if (status) return status;

    for (uint16_t i = 0; i < length; i++) {
        status = i2c_write(pgm_read_byte(data++), timeout);
        if (status) return status;
    }

    status = i2c_stop(timeout);
    if (status) return status;

    return I2C_STATUS_SUCCESS;
}

// Moves the cursor forward 1 character length
// Advances lines if there is not enough room for the next character
// Wraps to the begining when out of bounds
static void AdvanceCursor(void)
{
    uint16_t index = display_cursor - &display_buffer[0] + OLED_FONT_WIDTH;
    uint8_t remainingSpace = OLED_DISPLAY_WIDTH - (index % OLED_DISPLAY_WIDTH);
    if (remainingSpace < OLED_FONT_WIDTH)
        index += remainingSpace;

    if (index >= OLED_MATRIX_SIZE)
        index = 0;

    display_cursor = &display_buffer[index];
}

// Moves the cursor to the begining of the next line
// Wraps to the begining when out of bounds
static void AdvancePage(void)
{
    uint8_t pageIndex = (display_cursor - &display_buffer[0]) / OLED_DISPLAY_WIDTH + 1;

    // Out of bounds?
    if (pageIndex > OLED_DISPLAY_HEIGHT / 8 - 1)
        pageIndex = 0;

    display_cursor = &display_buffer[pageIndex * OLED_DISPLAY_WIDTH];
}

// Flips the rendering bits for a character at the current cursor position
static void InvertCharacter(uint8_t *cursor)
{
    const uint8_t *end = cursor + OLED_FONT_WIDTH;
    while (cursor < end)
    {
        *cursor = ~(*cursor);
        cursor++;
    }
}

// Main handler that writes character data to the display buffer
static void WriteCharToBuffer(const uint8_t data, bool invert)
{
    static uint8_t oled_temp_buffer[OLED_FONT_WIDTH];
    if (data == '\n')
        AdvancePage();
    else if (data < OLED_FONT_START || data > OLED_FONT_END)
    {
        memcpy(&oled_temp_buffer, display_cursor, OLED_FONT_WIDTH);
        memset(display_cursor, invert, OLED_FONT_WIDTH);
        display_dirty |= memcmp(&oled_temp_buffer, display_cursor, OLED_FONT_WIDTH) != 0;
        AdvanceCursor();
        return;
    }
    else
    {
        const uint8_t *glyph = &font[(data - OLED_FONT_START) * OLED_FONT_WIDTH];
        memcpy(&oled_temp_buffer, display_cursor, OLED_FONT_WIDTH);
        memcpy_P(display_cursor, glyph, OLED_FONT_WIDTH);
        if (invert) InvertCharacter(display_cursor);
        display_dirty |= memcmp(&oled_temp_buffer, display_cursor, OLED_FONT_WIDTH) != 0;
        AdvanceCursor();
    }
}

void iota_gfx_init(bool flip180)
{
    i2c_init();
    static const uint8_t PROGMEM display_setup1[] = {
        DISPLAY_OFF,
        DISPLAY_CLOCK, 0x80,
        MULTIPLEX_RATIO, OLED_DISPLAY_HEIGHT - 1,
        DISPLAY_OFFSET, 0x00,
        DISPLAY_START_LINE | 0x00,
        CHARGE_PUMP, 0x14,
        MEMORY_MODE, 0x00, };
    DEBUG_PRINT(I2C_SEND_CMD(display_setup1), "display_setup1 failed\n");

    if (!flip180)
    {
        static const uint8_t PROGMEM display_normal[] = {
            SEGMENT_REMAP_INV,
            COM_SCAN_DEC };
        DEBUG_PRINT(I2C_SEND_CMD(display_normal), "display_normal failed\n");
    }
    else
    {
        static const uint8_t PROGMEM display_flipped[] = {
            SEGMENT_REMAP,
            COM_SCAN_INC };
        DEBUG_PRINT(I2C_SEND_CMD(display_flipped), "display_flipped failed\n");
    }

    static const uint8_t PROGMEM display_setup2[] = {
        COM_PINS, 0x02,
        CONTRAST, 0x8F,
        PRE_CHARGE_PERIOD, 0xF1,
        VCOM_DETECT, 0x40,
        DISPLAY_ALL_ON_RESUME,
        NORMAL_DISPLAY,
        DEACTIVATE_SCROLL,
        DISPLAY_ON };
    DEBUG_PRINT(I2C_SEND_CMD(display_setup2), "display_setup2 failed\n");

    iota_gfx_clear();
    display_initialized = true;
}

void iota_gfx_clear(void)
{
    memset(display_buffer, 0, sizeof(display_buffer));
    display_cursor = &display_buffer[0];
    display_dirty = true;
}

void iota_gfx_set_cursor(uint8_t col, uint8_t line)
{
    uint16_t index = line * OLED_DISPLAY_WIDTH + col * OLED_FONT_WIDTH;
    display_cursor = &display_buffer[index];

    // Out of bounds?
    if (display_cursor - &display_buffer[0] > OLED_MATRIX_SIZE)
        display_cursor = &display_buffer[0];
}

void iota_gfx_render(void)
{
    static const uint8_t PROGMEM display_start[] = {
        COLUMN_ADDR, 0, OLED_DISPLAY_WIDTH - 1,
        PAGE_ADDR, 0, OLED_DISPLAY_HEIGHT / 8 - 1 };

    if (!display_dirty) return;

    DEBUG_PRINT(I2C_SEND_CMD(display_start), "iota_gfx_render command failed\n");
    DEBUG_PRINT(I2C_SEND_DATA(display_buffer), "iota_gfx_render data failed\n");
    display_cursor = &display_buffer[0];
    display_dirty = false;
}

void iota_gfx_write(const char *data, bool invert)
{
    const char *end = data + strlen(data);
    while (data < end)
    {
        WriteCharToBuffer(*data, invert);
        data++;
    }
}

void iota_gfx_write_P(const char *data, bool invert)
{
    uint8_t c = pgm_read_byte(data);
    while (c != 0)
    {
        WriteCharToBuffer(c, invert);
        c = pgm_read_byte(++data);
    }
}

bool iota_gfx_ready(void)
{
    return display_initialized;
}
#endif
