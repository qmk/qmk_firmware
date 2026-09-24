// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

// Per-key RGB is driven by two HT32F523xx sub-MCUs on SPI1, one on the main
// board (CS PA3) and one on the daughterboard (CS PA5). PA4 is their shared
// reset. A frame is 0xA2, 0x00 and 216 colour bytes; the byte positions come
// from the factory firmware's lookup table.

#include "quantum.h"
#include "rgb_matrix.h"
#include <string.h>

#define SPI_SR_BUSY (1U << 8)
#define SPI_CR1_DFL_8BIT 8U

// Master, mode 3, 8-bit frames, 8 MHz from the 48 MHz PCLK.
#define SPI1_CR1_VALUE (SPI_CR1_MODE | SPI_CR1_FORMAT_MODE3 | SPI_CR1_DFL_8BIT)
#define SPI1_CPR_VALUE 2U

#define PIN_CS1 (1U << 3)
#define PIN_RST (1U << 4)
#define PIN_CS2 (1U << 5)

#define FRAME_SIZE 218

// Sub-MCU and R/G/B byte offsets for each LED, in keyboard.json layout order.
// The two indicators are the spare channels the factory firmware uses for
// its side lights.
static const struct {
    uint8_t chip, r, g, b;
} led_map[RGB_MATRIX_LED_COUNT] = {
    {0,  12,  13,  14},  // Esc
    {0,  30,  31,  32},  // 1
    {0,  48,  49,  50},  // 2
    {0,  66,  67,  68},  // 3
    {0,  84,  85,  86},  // 4
    {0, 102, 103, 104},  // 5
    {0, 120, 121, 122},  // 6
    {0, 138, 139, 140},  // 7
    {0, 156, 157, 158},  // 8
    {0, 174, 175, 176},  // 9
    {0, 192, 193, 194},  // 0
    {0, 210, 211, 212},  // -
    {0, 141, 142, 143},  // =
    {1,  17,  16,  15},  // Ins
    {1,  53,  52,  51},  // Home
    {1,  89,  88,  87},  // PgUp
    {0,   9,  10,  11},  // Tab
    {0,  27,  28,  29},  // Q
    {0,  45,  46,  47},  // W
    {0,  63,  64,  65},  // E
    {0,  81,  82,  83},  // R
    {0,  99, 100, 101},  // T
    {0, 117, 118, 119},  // Y
    {0, 135, 136, 137},  // U
    {0, 153, 154, 155},  // I
    {0, 171, 172, 173},  // O
    {0, 189, 190, 191},  // P
    {0, 207, 208, 209},  // [
    {0, 213, 214, 215},  // ]
    {0, 195, 196, 197},  // Backslash
    {1,  14,  13,  12},  // Del
    {1,  50,  49,  48},  // End
    {1,  86,  85,  84},  // PgDn
    {0,   2,   1,   0},  // Ctrl
    {0,  20,  19,  18},  // A
    {0,  38,  37,  36},  // S
    {0,  56,  55,  54},  // D
    {0,  74,  73,  72},  // F
    {0,  92,  91,  90},  // G
    {0, 110, 109, 108},  // H
    {0, 128, 127, 126},  // J
    {0, 146, 145, 144},  // K
    {0, 164, 163, 162},  // L
    {0, 182, 181, 180},  // Semi
    {0, 200, 199, 198},  // Quote
    {0, 206, 205, 204},  // Enter
    {0, 159, 160, 161},  // Bksp
    {0,   5,   4,   3},  // LShift
    {0,  41,  40,  39},  // Z
    {0,  59,  58,  57},  // X
    {0,  77,  76,  75},  // C
    {0,  95,  94,  93},  // V
    {0, 113, 112, 111},  // B
    {0, 131, 130, 129},  // N
    {0, 149, 148, 147},  // M
    {0, 167, 166, 165},  // Comma
    {0, 185, 184, 183},  // Dot
    {0, 203, 202, 201},  // Slash
    {0, 170, 169, 168},  // RShift
    {0, 188, 187, 186},  // Fn2
    {1,  21,  22,  23},  // OLED-
    {1,  57,  58,  59},  // Up
    {1,  93,  94,  95},  // OLED+
    {0,   8,   7,   6},  // LCtrl
    {0,  26,  25,  24},  // Win
    {0,  44,  43,  42},  // Alt
    {0,  80,  79,  78},  // Space
    {0, 116, 115, 114},  // RAlt
    {0, 134, 133, 132},  // Fn
    {0, 152, 151, 150},  // RCtrl
    {1,  24,  25,  26},  // Left
    {1,  60,  61,  62},  // Down
    {1,  96,  97,  98},  // Right
    {0,  15,  16,  17},  // Left indicator
    {0,  33,  34,  35},  // Right indicator
};

static rgb_t   led_state[RGB_MATRIX_LED_COUNT];
static uint8_t frame[2][FRAME_SIZE];

static void spi1_send(uint32_t cs, const uint8_t *buf, uint16_t len) {
    uint32_t t;

    GPIOA->DOUTR &= ~cs;
    for (uint16_t i = 0; i < len; i++) {
        t = 2000;
        while (!(SPI1->SR & SPI_SR_TXE) && --t) {
        }
        SPI1->DR = buf[i];
    }
    t = 20000;
    while ((SPI1->SR & SPI_SR_BUSY) && --t) {
    }
    GPIOA->DOUTR |= cs;
}

static void chip_write(uint32_t cs, uint8_t opcode, uint8_t addr, uint8_t data) {
    uint8_t buf[3] = {opcode, addr, data};
    spi1_send(cs, buf, sizeof(buf));
}

// Roughly 500 us at 48 MHz. The sub-MCUs need this between the config writes.
static void chip_delay(void) {
    for (volatile uint32_t i = 0x5DC0; i > 0; i--) {
    }
}

static void chip_init(uint32_t cs) {
    chip_delay();
    chip_write(cs, 0xA0, 0x2F, 0xAE);
    chip_delay();
    chip_write(cs, 0xA0, 0x00, 0xB1);
    chip_delay();
    chip_write(cs, 0xA0, 0x01, 0xFF);
    for (uint8_t reg = 0; reg < 0xD8; reg++) {
        chip_write(cs, 0xA4, reg, 0xFF);
    }
}

static void init(void) {
    // Chip selects idle high; hold both chips in reset until SPI1 is ready.
    GPIOA->DIRCR |= PIN_CS1 | PIN_RST | PIN_CS2;
    GPIOA->INER &= ~(PIN_CS1 | PIN_RST | PIN_CS2);
    GPIOA->DOUTR = (GPIOA->DOUTR & ~(PIN_CS1 | PIN_RST | PIN_CS2)) | PIN_CS1 | PIN_CS2;

    // PA0, PA1 and PA2 to SPI1.
    CKCU->APBCCR0 |= CKCU_APBCCR0_SPI1EN;
    AFIO->GPxCFGR[0][0] = (AFIO->GPxCFGR[0][0] & ~0xFFFU) | (AFIO_SPI << 0) | (AFIO_SPI << 4) | (AFIO_SPI << 8);

    SPI1->CR0 = 0;
    SPI1->IER = 0;
    SPI1->FCR = 0;
    SPI1->CR1 = SPI1_CR1_VALUE;
    SPI1->CPR = SPI1_CPR_VALUE;
    SPI1->CR0 = SPI_CR0_SPIEN | SPI_CR0_SELOEN;

    GPIOA->DOUTR |= PIN_RST;
    chip_delay();
    chip_init(PIN_CS1);
    chip_init(PIN_CS2);
}

static void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    led_state[index] = (rgb_t){.r = r, .g = g, .b = b};
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        set_color(i, r, g, b);
    }
}

static void flush(void) {
    memset(frame, 0, sizeof(frame));
    frame[0][0] = frame[1][0] = 0xA2;

    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        uint8_t *data = &frame[led_map[i].chip][2];

        data[led_map[i].r] = led_state[i].r;
        data[led_map[i].g] = led_state[i].g;
        data[led_map[i].b] = led_state[i].b;
    }

    spi1_send(PIN_CS1, frame[0], FRAME_SIZE);
    spi1_send(PIN_CS2, frame[1], FRAME_SIZE);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .set_color     = set_color,
    .set_color_all = set_color_all,
    .flush         = flush,
};
