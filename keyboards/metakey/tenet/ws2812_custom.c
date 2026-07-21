// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * LED driver for the Metakey Tenet 70.
 *
 * The 76 per-key RGBs are driven by two Holtek HT32F523xx sub-MCUs (marked
 * "BFWH AAD7") that live on a shared SPI1 bus:
 *   - mainboard sub-MCU:      CS = PA3, drives 64 main-cluster LEDs
 *   - daughterboard sub-MCU:  CS = PA5, drives 12 nav-cluster LEDs
 *
 * Pin map:
 *   PA0/PA1/PA2 = SPI1 NSS/SCK/MOSI (AFIO mode 5)
 *   PA3         = CS for mainboard sub-MCU
 *   PA4         = shared RESET, LOW at boot, HIGH to bring the chips up
 *   PA5         = CS for daughterboard sub-MCU
 *
 * Init: 0xA0 config-page writes then 216 × 0xA4 register writes per chip,
 * matching stock FUN_00010478.
 *
 * Frame: one 218-byte write per chip = {0xA2, 0x00, then 216 colour bytes
 * at positions given by the tenet_led_map lookup table that was extracted
 * from stock flash at file offset 0xbebc}. Matches stock FUN_000102f4.
 */

#include "ws2812.h"
#include "rgb_matrix.h"
#include <string.h>

#define SPI1_CR0  (*(volatile uint32_t *)0x40044000U)
#define SPI1_CR1  (*(volatile uint32_t *)0x40044004U)
#define SPI1_IER  (*(volatile uint32_t *)0x40044008U)
#define SPI1_CPR  (*(volatile uint32_t *)0x4004400CU)
#define SPI1_DR   (*(volatile uint32_t *)0x40044010U)
#define SPI1_SR   (*(volatile uint32_t *)0x40044014U)
#define SPI1_FCR  (*(volatile uint32_t *)0x40044018U)

#define SPI_CR0_SPIEN        (1u << 0)
#define SPI_CR0_SELOEN       (1u << 3)    /* NSS output enable */
#define SPI_CR1_MODE         (1u << 14)   /* master */
#define SPI_CR1_FORMAT_MODE3 (0x5u << 8)  /* CPOL=1 CPHA=1 */
#define SPI_SR_TXE           (1u << 1)
#define SPI_SR_BUSY          (1u << 8)

/* CR1 = 0x4508, CPR = 2 → 8 MHz SCK on 48 MHz PCLK. */
#define STOCK_CR1  (SPI_CR1_MODE | SPI_CR1_FORMAT_MODE3 | 0x08u)
#define STOCK_CPR  2u

#define CKCU_APBCCR0     (*(volatile uint32_t *)0x4008802CU)
#define CKCU_SPI1_EN     (1u << 5)

#define HT_AFIO_GPACFGLR (*(volatile uint32_t *)0x40022020U)

/* Port A GPIO register offsets per HT32F523xx TRM. DOUTR is at 0x020
 * (not 0x014, which is DRVR, drive current; not 0x028, which is RR,
 * write-1-to-clear). */
#define HT_GPIOA_DIRCR   (*(volatile uint32_t *)0x400B0000U)
#define HT_GPIOA_INER    (*(volatile uint32_t *)0x400B0004U)
#define HT_GPIOA_DOUTR   (*(volatile uint32_t *)0x400B0020U)

#define PIN_CS1  (1u << 3)   /* PA3 */
#define PIN_EN   (1u << 4)   /* PA4 */
#define PIN_CS2  (1u << 5)   /* PA5 */

/* LED position lookup, extracted from stock Tenet firmware at flash offset
 * 0xbebc. Each cell holds three signed int16 byte offsets into the 216-byte
 * colour payload: (R_pos, G_pos, B_pos). -1 means no LED at this cell.
 *
 * Cols 0-14 address the mainboard sub-MCU; cols 15-17 address the
 * daughterboard sub-MCU. Both accept the same byte stream — only the CS
 * line distinguishes which register file receives it. */
static const int16_t tenet_led_map[5][18][3] = {
    { {  12, 13, 14},{  30, 31, 32},{  48, 49, 50},{  66, 67, 68},
      {  84, 85, 86},{ 102,103,104},{ 120,121,122},{ 138,139,140},
      { 156,157,158},{ 174,175,176},{ 192,193,194},{ 210,211,212},
      { 141,142,143},{ 159,160,161},{ 177,178,179},
      {  17, 16, 15},{  53, 52, 51},{  89, 88, 87} },
    { {   9, 10, 11},{  27, 28, 29},{  45, 46, 47},{  63, 64, 65},
      {  81, 82, 83},{  99,100,101},{ 117,118,119},{ 135,136,137},
      { 153,154,155},{ 171,172,173},{ 189,190,191},{ 207,208,209},
      { 213,214,215},{ 195,196,197},{  -1, -1, -1},
      {  14, 13, 12},{  50, 49, 48},{  86, 85, 84} },
    { {   2,  1,  0},{  20, 19, 18},{  38, 37, 36},{  56, 55, 54},
      {  74, 73, 72},{  92, 91, 90},{ 110,109,108},{ 128,127,126},
      { 146,145,144},{ 164,163,162},{ 182,181,180},{ 200,199,198},
      { 206,205,204},{  -1, -1, -1},{  -1, -1, -1},
      {  -1, -1, -1},{  -1, -1, -1},{  -1, -1, -1} },
    { {   5,  4,  3},{  23, 22, 21},{  41, 40, 39},{  59, 58, 57},
      {  77, 76, 75},{  95, 94, 93},{ 113,112,111},{ 131,130,129},
      { 149,148,147},{ 167,166,165},{ 185,184,183},{ 203,202,201},
      { 170,169,168},{ 188,187,186},{  -1, -1, -1},
      {  21, 22, 23},{  57, 58, 59},{  93, 94, 95} },
    { {   8,  7,  6},{  26, 25, 24},{  44, 43, 42},{  -1, -1, -1},
      {  80, 79, 78},{  98, 97, 96},{ 116,115,114},{ 134,133,132},
      { 152,151,150},{  -1, -1, -1},{  -1, -1, -1},{  -1, -1, -1},
      {  -1, -1, -1},{  -1, -1, -1},{  -1, -1, -1},
      {  24, 25, 26},{  60, 61, 62},{  96, 97, 98} },
};

#define LED_FRAME_SIZE 218   /* 0xA2 + 0x00 + 216 color bytes */

/* One 218-byte frame per sub-MCU, filled on every flush. */
static uint8_t chip_frame[2][LED_FRAME_SIZE];

ws2812_led_t ws2812_leds[WS2812_LED_COUNT];

/* Send a 3-byte (opcode, addr, data) register write with CS toggling. */
static void chip_write3(uint32_t cs_mask, uint8_t opcode, uint8_t addr, uint8_t data) {
    uint32_t t;

    HT_GPIOA_DOUTR &= ~cs_mask;

    t = 2000; while (!(SPI1_SR & SPI_SR_TXE) && --t) {}
    SPI1_DR = opcode;
    t = 2000; while (!(SPI1_SR & SPI_SR_TXE) && --t) {}
    SPI1_DR = addr;
    t = 2000; while (!(SPI1_SR & SPI_SR_TXE) && --t) {}
    SPI1_DR = data;

    t = 2000; while ((SPI1_SR & SPI_SR_BUSY) && --t) {}

    HT_GPIOA_DOUTR |= cs_mask;
}

/* ~500 µs busy-wait at 48 MHz — stock inserts this between the first few
 * init writes; the sub-MCU firmware needs it. */
static void chip_delay(void) {
    for (volatile uint32_t i = 0x5DC0; i > 0; i--) {}
}

/* Sub-MCU init: three 0xA0 config-page writes (registers 0x2F, 0x00, 0x01)
 * followed by 216 × 0xA4 auto-increment writes that zero the PWM register
 * bank. Must run on each chip before the first 0xA2 colour frame. */
static void chip_init(uint32_t cs_mask) {
    chip_delay();
    chip_write3(cs_mask, 0xA0, 0x2F, 0xAE);
    chip_delay();
    chip_write3(cs_mask, 0xA0, 0x00, 0xB1);
    chip_delay();
    chip_write3(cs_mask, 0xA0, 0x01, 0xFF);
    for (uint8_t r = 0; r < 0xD8; r++) {
        chip_write3(cs_mask, 0xA4, r, 0xFF);
    }
}

void ws2812_init(void) {
    /* PA3/PA4/PA5 as GPIO outputs. CS lines idle HIGH, PA4 (reset) starts LOW. */
    HT_GPIOA_DIRCR |= (PIN_CS1 | PIN_EN | PIN_CS2);
    HT_GPIOA_INER  &= ~(PIN_CS1 | PIN_EN | PIN_CS2);
    HT_GPIOA_DOUTR = (HT_GPIOA_DOUTR & ~(PIN_CS1 | PIN_EN | PIN_CS2))
                      | PIN_CS1 | PIN_CS2;

    /* Enable SPI1 clock, route PA0/PA1/PA2 to the SPI1 alt function (mode 5). */
    CKCU_APBCCR0 |= CKCU_SPI1_EN;
    HT_AFIO_GPACFGLR = (HT_AFIO_GPACFGLR & ~0xFFFu)
                        | (5u << 0) | (5u << 4) | (5u << 8);

    SPI1_CR0 = 0;
    SPI1_IER = 0;
    SPI1_FCR = 0;
    SPI1_CR1 = STOCK_CR1;
    SPI1_CPR = STOCK_CPR;
    SPI1_CR0 = SPI_CR0_SPIEN | SPI_CR0_SELOEN;

    /* Raise PA4 to release both sub-MCUs from reset, then init each. */
    HT_GPIOA_DOUTR |= PIN_EN;
    chip_delay();
    chip_init(PIN_CS1);
    chip_init(PIN_CS2);
}

void ws2812_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    ws2812_leds[index].r = red;
    ws2812_leds[index].g = green;
    ws2812_leds[index].b = blue;
}

void ws2812_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < WS2812_LED_COUNT; i++) ws2812_set_color(i, red, green, blue);
}

/* Polled SPI1 send: assert cs_mask, clock out n bytes (TXE handshake per
 * byte), wait for the shift register to drain, deassert. */
static void spi1_send_frame(uint32_t cs_mask, const uint8_t *buf, uint16_t n) {
    HT_GPIOA_DOUTR &= ~cs_mask;
    for (uint16_t i = 0; i < n; i++) {
        uint32_t t = 2000;
        while (!(SPI1_SR & SPI_SR_TXE) && --t) {}
        SPI1_DR = buf[i];
    }
    uint32_t t = 20000;
    while ((SPI1_SR & SPI_SR_BUSY) && --t) {}
    HT_GPIOA_DOUTR |= cs_mask;
}

void ws2812_flush(void) {
    /* Frame = [0xA2, 0x00, <216 colour bytes>]. Re-init header each flush,
     * then zero the data region and fill it from the LED state. */
    chip_frame[0][0] = chip_frame[1][0] = 0xA2;
    chip_frame[0][1] = chip_frame[1][1] = 0x00;
    memset(&chip_frame[0][2], 0, 216);
    memset(&chip_frame[1][2], 0, 216);

    for (uint8_t row = 0; row < 5; row++) {
        for (uint8_t col = 0; col < 18; col++) {
            uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED || led >= WS2812_LED_COUNT) continue;
            int16_t rp = tenet_led_map[row][col][0];
            if (rp < 0) continue;
            int16_t gp = tenet_led_map[row][col][1];
            int16_t bp = tenet_led_map[row][col][2];
            uint8_t chip = (col < 15) ? 0 : 1;
            chip_frame[chip][2 + rp] = ws2812_leds[led].r;
            chip_frame[chip][2 + gp] = ws2812_leds[led].g;
            chip_frame[chip][2 + bp] = ws2812_leds[led].b;
        }
    }

    spi1_send_frame(PIN_CS1, chip_frame[0], LED_FRAME_SIZE);
    spi1_send_frame(PIN_CS2, chip_frame[1], LED_FRAME_SIZE);
}
