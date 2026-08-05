// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * SSD1326 OLED driver for the Metakey Tenet 70.
 *
 * The main MCU drives the OLED directly over I2C0 (PB0 SDA, PB1 SCL, AFIO
 * mode 7, open-drain) with PD1 as active-low RST. 7-bit device addr 0x3C.
 *
 * chibios-contrib has no I2C LLD for the HT32F523xx family, so this file
 * drives the peripheral via raw register writes.
 *
 * The control byte before each transfer selects command (0x00) or data
 * (0x40) stream per SSD1326 datasheet.
 */

#include "ssd1326.h"
#include "quantum.h"
#include <string.h>

/* I2C0_BASE, AFIO_GPIO, AFIO_I2C come from the HT32F523xx CMSIS header. */
#define I2C0_CR    (*(volatile uint32_t *)(I2C0_BASE + 0x000))
#define I2C0_SR    (*(volatile uint32_t *)(I2C0_BASE + 0x00C))
#define I2C0_SHPGR (*(volatile uint32_t *)(I2C0_BASE + 0x010))
#define I2C0_SLPGR (*(volatile uint32_t *)(I2C0_BASE + 0x014))
#define I2C0_DR    (*(volatile uint32_t *)(I2C0_BASE + 0x018))
#define I2C0_TAR   (*(volatile uint32_t *)(I2C0_BASE + 0x01C))
#define I2C0_TOUT  (*(volatile uint32_t *)(I2C0_BASE + 0x028))

#define CR_I2CEN  (1u << 3)
#define CR_STOP   (1u << 1)

#define SR_TXDE   (1u << 17)
#define SR_RXNACK (1u << 9)

#define CKCU_APBCCR0 (*(volatile uint32_t *)0x4008802CU)
#define CKCU_I2C0_EN (1u << 0)

#define HT_AFIO_GPBCFGLR (*(volatile uint32_t *)0x40022028U)
#define HT_AFIO_GPDCFGLR (*(volatile uint32_t *)0x40022038U)
#define HT_GPIOB_ODR     (*(volatile uint32_t *)0x400B2010U)

#define HT_GPIOD_DIRCR   (*(volatile uint32_t *)0x400B6000U)
#define HT_GPIOD_INER    (*(volatile uint32_t *)0x400B6004U)
#define HT_GPIOD_DOUTR   (*(volatile uint32_t *)0x400B6020U)

#define PIN_PD1 (1u << 1)

#ifndef OLED_I2C_ADDR_7
#  define OLED_I2C_ADDR_7 0x3C
#endif

#define CTRL_CMD   0x00
#define CTRL_DATA  0x40

#define I2C_POLL_TIMEOUT 2000u   /* ~200 µs at 48 MHz */

static uint8_t ssd1326_fb[SSD1326_WIDTH * SSD1326_HEIGHT / 8];
static bool    ssd1326_dirty = true;

/* Minimal 5x7 font, chars 0x20..0x5F. */
static const uint8_t font5x7[][5] = {
    {0x00,0x00,0x00,0x00,0x00},{0x00,0x00,0x5F,0x00,0x00},
    {0x00,0x07,0x00,0x07,0x00},{0x14,0x7F,0x14,0x7F,0x14},
    {0x24,0x2A,0x7F,0x2A,0x12},{0x23,0x13,0x08,0x64,0x62},
    {0x36,0x49,0x55,0x22,0x50},{0x00,0x05,0x03,0x00,0x00},
    {0x00,0x1C,0x22,0x41,0x00},{0x00,0x41,0x22,0x1C,0x00},
    {0x08,0x2A,0x1C,0x2A,0x08},{0x08,0x08,0x3E,0x08,0x08},
    {0x00,0x50,0x30,0x00,0x00},{0x08,0x08,0x08,0x08,0x08},
    {0x00,0x60,0x60,0x00,0x00},{0x20,0x10,0x08,0x04,0x02},
    {0x3E,0x51,0x49,0x45,0x3E},{0x00,0x42,0x7F,0x40,0x00},
    {0x42,0x61,0x51,0x49,0x46},{0x21,0x41,0x45,0x4B,0x31},
    {0x18,0x14,0x12,0x7F,0x10},{0x27,0x45,0x45,0x45,0x39},
    {0x3C,0x4A,0x49,0x49,0x30},{0x01,0x71,0x09,0x05,0x03},
    {0x36,0x49,0x49,0x49,0x36},{0x06,0x49,0x49,0x29,0x1E},
    {0x00,0x36,0x36,0x00,0x00},{0x00,0x56,0x36,0x00,0x00},
    {0x00,0x08,0x14,0x22,0x41},{0x14,0x14,0x14,0x14,0x14},
    {0x41,0x22,0x14,0x08,0x00},{0x02,0x01,0x51,0x09,0x06},
    {0x32,0x49,0x79,0x41,0x3E},{0x7E,0x11,0x11,0x11,0x7E},
    {0x7F,0x49,0x49,0x49,0x36},{0x3E,0x41,0x41,0x41,0x22},
    {0x7F,0x41,0x41,0x22,0x1C},{0x7F,0x49,0x49,0x49,0x41},
    {0x7F,0x09,0x09,0x01,0x01},{0x3E,0x41,0x41,0x51,0x32},
    {0x7F,0x08,0x08,0x08,0x7F},{0x00,0x41,0x7F,0x41,0x00},
    {0x20,0x40,0x41,0x3F,0x01},{0x7F,0x08,0x14,0x22,0x41},
    {0x7F,0x40,0x40,0x40,0x40},{0x7F,0x02,0x04,0x02,0x7F},
    {0x7F,0x04,0x08,0x10,0x7F},{0x3E,0x41,0x41,0x41,0x3E},
    {0x7F,0x09,0x09,0x09,0x06},{0x3E,0x41,0x51,0x21,0x5E},
    {0x7F,0x09,0x19,0x29,0x46},{0x46,0x49,0x49,0x49,0x31},
    {0x01,0x01,0x7F,0x01,0x01},{0x3F,0x40,0x40,0x40,0x3F},
    {0x1F,0x20,0x40,0x20,0x1F},{0x7F,0x20,0x18,0x20,0x7F},
    {0x63,0x14,0x08,0x14,0x63},{0x03,0x04,0x78,0x04,0x03},
    {0x61,0x51,0x49,0x45,0x43},{0x00,0x00,0x7F,0x41,0x41},
    {0x02,0x04,0x08,0x10,0x20},{0x41,0x41,0x7F,0x00,0x00},
    {0x04,0x02,0x01,0x02,0x04},{0x40,0x40,0x40,0x40,0x40},
};

/* One I2C transaction: START, address, bytes..., STOP.
 *
 * HT32 auto-clears CR_STOP once the STOP condition is generated, so the
 * inter-transaction wait at the top polls CR_STOP (not SR_BUSBUSY — BUSBUSY
 * only drops after CR_STOP clears, and waiting on it first would timeout).
 * Writing TAR triggers START + address. Last byte's TXDE wait ensures it
 * has left the shift register before we raise STOP. */
static int i2c0_write(uint8_t addr7, const uint8_t *buf, uint16_t len) {
    uint32_t t;

    t = I2C_POLL_TIMEOUT; while ((I2C0_CR & CR_STOP) && --t) {}
    if (t == 0) return -1;

    I2C0_TAR = (uint32_t)(addr7 & 0x7Fu);

    for (uint16_t i = 0; i < len; i++) {
        t = I2C_POLL_TIMEOUT; while (!(I2C0_SR & SR_TXDE) && --t) {}
        if (t == 0) return -2;
        if (I2C0_SR & SR_RXNACK) return -3;
        I2C0_DR = buf[i];
    }

    t = I2C_POLL_TIMEOUT; while (!(I2C0_SR & SR_TXDE) && --t) {}
    I2C0_CR |= CR_STOP;

    return 0;
}

static int oled_cmd(uint8_t c) {
    uint8_t buf[2] = { CTRL_CMD, c };
    return i2c0_write(OLED_I2C_ADDR_7, buf, sizeof(buf));
}

/* SSD1326 init command stream, sent as one I2C transaction under a single
 * CMD control byte (0x00 = multi-command mode). The controller consumes
 * params inline per each command's spec. */
static const uint8_t ssd1326_init_cmds[] = {
    0xFD, 0x12,        /* unlock command lock */
    0xAE,              /* display off */
    0xA8, 0x1F,        /* multiplex ratio = 32 rows */
    0xA2, 0x00,        /* display offset = 0 */
    0xA1, 0x04,        /* display start line = 4 */
    0xA0, 0x00,        /* re-map: default; vertical flip handled in software */
    0x81, 0x3D,        /* contrast = 0x3D */
    0xBE, 0x0F,        /* VCOMH deselect */
    0xBC, 0x20,        /* precharge voltage */
    0xB1, 0x11,        /* phase length */
    0xB3, 0xF1,        /* oscillator freq */
    0xA4,              /* entire display ON (resume from forced on/off) */
    0xAF,              /* display ON */
};

void ssd1326_send_command(uint8_t cmd) { oled_cmd(cmd); }

void ssd1326_send_data(const uint8_t *data, uint16_t len) {
    /* SSD1326 I2C stream: one control byte (0x40) then payload per
     * transaction. Chunk at 64 bytes to keep the on-stack buffer small. */
    uint8_t buf[65];
    buf[0] = CTRL_DATA;
    while (len > 0) {
        uint16_t chunk = len > 64 ? 64 : len;
        memcpy(&buf[1], data, chunk);
        i2c0_write(OLED_I2C_ADDR_7, buf, chunk + 1);
        data += chunk;
        len  -= chunk;
    }
}

void ssd1326_render(void);

static void i2c0_bus_init(void) {
    /* Enable I2C0 peripheral clock (APBCCR0 bit 0, per HT32F52352 CKCU). */
    CKCU_APBCCR0 |= CKCU_I2C0_EN;

    /* PB0 SDA, PB1 SCL → AFIO mode 7 (I2C). Open-drain for both. */
    HT_AFIO_GPBCFGLR = (HT_AFIO_GPBCFGLR & ~0xFFu) | (AFIO_I2C << 0) | (AFIO_I2C << 4);
    HT_GPIOB_ODR |= (1u << 0) | (1u << 1);

    /* SCL_freq = PCLK / (SHPGR + SLPGR + 7). PCLK = 48 MHz → ~400 kHz
     * (SSD1326 fast-mode spec max). */
    I2C0_SHPGR = 56;
    I2C0_SLPGR = 56;
    I2C0_TOUT  = 0;

    I2C0_CR = CR_I2CEN;
}

void ssd1326_init(void) {
    /* PD1 = RST. Set AFIO to GPIO explicitly (board.c doesn't configure
     * PD1), then pulse it HIGH → LOW → HIGH. */
    HT_AFIO_GPDCFGLR = (HT_AFIO_GPDCFGLR & ~(0xFu << 4)) | (AFIO_GPIO << 4);
    HT_GPIOD_DIRCR |= PIN_PD1;
    HT_GPIOD_INER  &= ~PIN_PD1;
    HT_GPIOD_DOUTR |= PIN_PD1;
    wait_ms(1);
    HT_GPIOD_DOUTR &= ~PIN_PD1;
    wait_ms(10);
    HT_GPIOD_DOUTR |= PIN_PD1;
    wait_ms(10);

    i2c0_bus_init();

    uint8_t init_buf[1 + sizeof(ssd1326_init_cmds)];
    init_buf[0] = CTRL_CMD;
    memcpy(&init_buf[1], ssd1326_init_cmds, sizeof(ssd1326_init_cmds));
    i2c0_write(OLED_I2C_ADDR_7, init_buf, sizeof(init_buf));

    memset(ssd1326_fb, 0, sizeof(ssd1326_fb));
    ssd1326_dirty = true;
    ssd1326_render();
}

void ssd1326_fb_pixel(uint16_t x, uint8_t y, bool on) {
    if (x >= SSD1326_WIDTH || y >= SSD1326_HEIGHT) return;
    /* The panel is case-mounted with COM0 at the visual bottom, so y=0 (top)
     * maps to the last physical row. */
    y = SSD1326_HEIGHT - 1 - y;
    uint16_t idx = (y * SSD1326_WIDTH + x) / 8;
    uint8_t  m   = 0x80 >> (x % 8);
    if (on) ssd1326_fb[idx] |= m;
    else    ssd1326_fb[idx] &= ~m;
    ssd1326_dirty = true;
}

void ssd1326_fb_char(uint16_t x, uint8_t y, char c, uint8_t scale) {
    if (c < 0x20 || c > 0x5F) c = '?';
    const uint8_t *g = font5x7[c - 0x20];
    for (uint8_t col = 0; col < 5; col++)
        for (uint8_t row = 0; row < 7; row++)
            if (g[col] & (1 << row))
                for (uint8_t sy = 0; sy < scale; sy++)
                    for (uint8_t sx = 0; sx < scale; sx++)
                        ssd1326_fb_pixel(x + col*scale + sx, y + row*scale + sy, true);
}

void ssd1326_fb_string(uint16_t x, uint8_t y, const char *s, uint8_t scale) {
    while (*s) { ssd1326_fb_char(x, y, *s, scale); x += 6 * scale; s++; }
}

void ssd1326_render(void) {
    if (!ssd1326_dirty) return;
    ssd1326_dirty = false;

    /* Set column/row window to cover the whole display. SSD1326 packs 2 px
     * per byte in 4-bit grayscale mode; 256 px wide → 128 column bytes. */
    oled_cmd(0x15); oled_cmd(0x00); oled_cmd(0x7F);  /* col 0..127 (in byte units) */
    oled_cmd(0x75); oled_cmd(0x00); oled_cmd(0x1F);  /* row 0..31 */

    /* Expand each 1-bit source byte into four 4-bit output nibbles (full ON
     * or OFF — no actual grayscale). Stream in 64-byte chunks behind one
     * CTRL_DATA control byte. */
    uint8_t buf[65];
    buf[0] = CTRL_DATA;
    uint8_t cnt = 1;
    for (uint16_t i = 0; i < sizeof(ssd1326_fb); i++) {
        uint8_t b = ssd1326_fb[i];
        for (int bit = 7; bit >= 0; bit -= 2) {
            uint8_t nib = ((b >> bit) & 1) ? 0xF0 : 0x00;
            nib |= ((b >> (bit - 1)) & 1) ? 0x0F : 0x00;
            buf[cnt++] = nib;
            if (cnt == sizeof(buf)) {
                i2c0_write(OLED_I2C_ADDR_7, buf, cnt);
                cnt = 1;
            }
        }
    }
    if (cnt > 1) i2c0_write(OLED_I2C_ADDR_7, buf, cnt);
}

void ssd1326_render_mono(const uint8_t *buf) {
    memcpy(ssd1326_fb, buf, sizeof(ssd1326_fb));
    ssd1326_dirty = true;
    ssd1326_render();
}

void ssd1326_clear(void) {
    memset(ssd1326_fb, 0, sizeof(ssd1326_fb));
    ssd1326_dirty = true;
    ssd1326_render();
}

/* Clear the framebuffer, draw `text` horizontally + vertically centred
 * (scale 2, falling back to scale 1 when the string won't fit at 2), render. */
void ssd1326_set_text(const char *text) {
    memset(ssd1326_fb, 0, sizeof(ssd1326_fb));
    if (!text || *text == 0) {
        ssd1326_dirty = true;
        ssd1326_render();
        return;
    }

    uint8_t len = 0;
    while (text[len] && len < 64) len++;

    uint8_t  scale  = (len * 12 <= SSD1326_WIDTH) ? 2 : 1;
    uint16_t text_w = len * 6 * scale;
    uint8_t  text_h = 7 * scale;

    uint16_t x = (text_w < SSD1326_WIDTH)  ? (SSD1326_WIDTH  - text_w) / 2 : 0;
    uint8_t  y = (text_h < SSD1326_HEIGHT) ? (SSD1326_HEIGHT - text_h) / 2 : 0;

    ssd1326_fb_string(x, y, text, scale);
    ssd1326_render();
}
