#include "quantum.h"
#include "ws2812.h"

/* Adapted from https://github.com/gamazeps/ws2812b-chibios-SPIDMA/ */

#ifdef RGBW
#    error "RGBW not supported"
#endif

// Define the spi your LEDs are plugged to here
#ifndef WS2812_SPI
#    define WS2812_SPI SPID1
#endif

#ifndef WS2812_SPI_MOSI_PAL_MODE
#    define WS2812_SPI_MOSI_PAL_MODE 5
#endif

#define BYTES_FOR_LED_BYTE 4
#define NB_COLORS 3
#define BYTES_FOR_LED (BYTES_FOR_LED_BYTE * NB_COLORS)
#define DATA_SIZE (BYTES_FOR_LED * RGBLED_NUM)
#define RESET_SIZE 200
#define PREAMBLE_SIZE 4

static uint8_t txbuf[PREAMBLE_SIZE + DATA_SIZE + RESET_SIZE] = {0};

/*
 * As the trick here is to use the SPI to send a huge pattern of 0 and 1 to
 * the ws2812b protocol, we use this helper function to translate bytes into
 * 0s and 1s for the LED (with the appropriate timing).
 */
static uint8_t get_protocol_eq(uint8_t data, int pos) {
    uint8_t eq = 0;
    if (data & (1 << (2 * (3 - pos))))
        eq = 0b1110;
    else
        eq = 0b1000;
    if (data & (2 << (2 * (3 - pos))))
        eq += 0b11100000;
    else
        eq += 0b10000000;
    return eq;
}

static void set_led_color_rgb(LED_TYPE color, int pos) {
    uint8_t* tx_start = &txbuf[PREAMBLE_SIZE];

    for (int j = 0; j < 4; j++) tx_start[BYTES_FOR_LED * pos + j] = get_protocol_eq(color.g, j);
    for (int j = 0; j < 4; j++) tx_start[BYTES_FOR_LED * pos + BYTES_FOR_LED_BYTE + j] = get_protocol_eq(color.r, j);
    for (int j = 0; j < 4; j++) tx_start[BYTES_FOR_LED * pos + BYTES_FOR_LED_BYTE * 2 + j] = get_protocol_eq(color.b, j);
}

void ws2812_init(void) {
#if defined(USE_GPIOV1)
    palSetLineMode(RGB_DI_PIN, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
#else
    palSetLineMode(RGB_DI_PIN, PAL_MODE_ALTERNATE(WS2812_SPI_MOSI_PAL_MODE) | PAL_STM32_OTYPE_PUSHPULL);
#endif

    // TODO: more dynamic baudrate
    static const SPIConfig spicfg = {
        0, NULL, PAL_PORT(RGB_DI_PIN), PAL_PAD(RGB_DI_PIN),
        SPI_CR1_BR_1 | SPI_CR1_BR_0  // baudrate : fpclk / 8 => 1tick is 0.32us (2.25 MHz)
    };

    spiAcquireBus(&WS2812_SPI);     /* Acquire ownership of the bus.    */
    spiStart(&WS2812_SPI, &spicfg); /* Setup transfer parameters.       */
    spiSelect(&WS2812_SPI);         /* Slave Select assertion.          */
}

void ws2812_setleds(LED_TYPE* ledarray, uint16_t leds) {
    static bool s_init = false;
    if (!s_init) {
        ws2812_init();
        s_init = true;
    }

    for (uint8_t i = 0; i < leds; i++) {
        set_led_color_rgb(ledarray[i], i);
    }

    // Send async - each led takes ~0.03ms, 50 leds ~1.5ms, animations flushing faster than send will cause issues.
    // Instead spiSend can be used to send synchronously (or the thread logic can be added back).
#ifdef WS2812_SPI_SYNC
    spiSend(&WS2812_SPI, sizeof(txbuf) / sizeof(txbuf[0]), txbuf);
#else
    spiStartSend(&WS2812_SPI, sizeof(txbuf) / sizeof(txbuf[0]), txbuf);
#endif
}
