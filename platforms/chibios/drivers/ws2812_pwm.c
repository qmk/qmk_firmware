#include "ws2812.h"
#include "quantum.h"
#include <hal.h>

/* Adapted from https://github.com/joewa/WS2812-LED-Driver_ChibiOS/ */

#ifdef RGBW
#    define WS2812_CHANNELS 4
#else
#    define WS2812_CHANNELS 3
#endif

#ifndef WS2812_PWM_DRIVER
#    define WS2812_PWM_DRIVER PWMD2 // TIMx
#endif
#ifndef WS2812_PWM_CHANNEL
#    define WS2812_PWM_CHANNEL 2 // Channel
#endif
#ifndef WS2812_PWM_PAL_MODE
#    define WS2812_PWM_PAL_MODE 2 // DI Pin's alternate function value
#endif
#ifndef WS2812_DMA_STREAM
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM2 // DMA Stream for TIMx_UP
#endif
#ifndef WS2812_DMA_CHANNEL
#    define WS2812_DMA_CHANNEL 2 // DMA Channel for TIMx_UP
#endif
#if (STM32_DMA_SUPPORTS_DMAMUX == TRUE) && !defined(WS2812_DMAMUX_ID)
#    error "please consult your MCU's datasheet and specify in your config.h: #define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM?_UP"
#endif

/* Summarize https://www.st.com/resource/en/application_note/an4013-stm32-crossseries-timer-overview-stmicroelectronics.pdf to
 * figure out if we are using a 32bit timer. This is needed to setup the DMA controller correctly.
 * Ignore STM32H7XX and STM32U5XX as they are not supported by ChibiOS.
 */
#if !defined(STM32F1XX) && !defined(STM32L0XX) && !defined(STM32L1XX)
#    define WS2812_PWM_TIMER_32BIT_PWMD2 1
#endif
#if !defined(STM32F1XX)
#    define WS2812_PWM_TIMER_32BIT_PWMD5 1
#endif
#define WS2812_CONCAT1(a, b) a##b
#define WS2812_CONCAT(a, b) WS2812_CONCAT1(a, b)
#if WS2812_CONCAT(WS2812_PWM_TIMER_32BIT_, WS2812_PWM_DRIVER)
#    define WS2812_PWM_TIMER_32BIT
#endif

#ifndef WS2812_PWM_COMPLEMENTARY_OUTPUT
#    define WS2812_PWM_OUTPUT_MODE PWM_OUTPUT_ACTIVE_HIGH
#else
#    if !STM32_PWM_USE_ADVANCED
#        error "WS2812_PWM_COMPLEMENTARY_OUTPUT requires STM32_PWM_USE_ADVANCED == TRUE"
#    endif
#    define WS2812_PWM_OUTPUT_MODE PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH
#endif

// Push Pull or Open Drain Configuration
// Default Push Pull
#ifndef WS2812_EXTERNAL_PULLUP
#    if defined(USE_GPIOV1)
#        define WS2812_OUTPUT_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define WS2812_OUTPUT_MODE PAL_MODE_ALTERNATE(WS2812_PWM_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING
#    endif
#else
#    if defined(USE_GPIOV1)
#        define WS2812_OUTPUT_MODE PAL_MODE_ALTERNATE_OPENDRAIN
#    else
#        define WS2812_OUTPUT_MODE PAL_MODE_ALTERNATE(WS2812_PWM_PAL_MODE) | PAL_OUTPUT_TYPE_OPENDRAIN | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING
#    endif
#endif

#ifndef WS2812_PWM_TARGET_PERIOD
//#    define WS2812_PWM_TARGET_PERIOD 800000 // Original code is 800k...?
#    define WS2812_PWM_TARGET_PERIOD 80000 // TODO: work out why 10x less on f303/f4x1
#endif

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

#define WS2812_PWM_FREQUENCY (CPU_CLOCK / 2)                                /**< Clock frequency of PWM, must be valid with respect to system clock! */
#define WS2812_PWM_PERIOD (WS2812_PWM_FREQUENCY / WS2812_PWM_TARGET_PERIOD) /**< Clock period in ticks. 1 / 800kHz = 1.25 uS (as per datasheet) */

/**
 * @brief   Number of bit-periods to hold the data line low at the end of a frame
 *
 * The reset period for each frame is defined in WS2812_TRST_US.
 * Calculate the number of zeroes to add at the end assuming 1.25 uS/bit:
 */
#define WS2812_COLOR_BITS (WS2812_CHANNELS * 8)
#define WS2812_RESET_BIT_N (1000 * WS2812_TRST_US / WS2812_TIMING)
#define WS2812_COLOR_BIT_N (WS2812_LED_COUNT * WS2812_COLOR_BITS) /**< Number of data bits */
#define WS2812_BIT_N (WS2812_COLOR_BIT_N + WS2812_RESET_BIT_N)    /**< Total number of bits in a frame */

/**
 * @brief   High period for a zero, in ticks
 *
 * Per the datasheet:
 * WS2812:
 * - T0H: 200 nS to 500 nS, inclusive
 * - T0L: 650 nS to 950 nS, inclusive
 * WS2812B:
 * - T0H: 200 nS to 500 nS, inclusive
 * - T0L: 750 nS to 1050 nS, inclusive
 *
 * The duty cycle is calculated for a high period of 350 nS.
 */
#define WS2812_DUTYCYCLE_0 (WS2812_PWM_FREQUENCY / (1000000000 / 350))
#if (WS2812_DUTYCYCLE_0 > 255)
#    error WS2812 PWM driver: High period for a 0 is more than a byte
#endif

/**
 * @brief   High period for a one, in ticks
 *
 * Per the datasheet:
 * WS2812:
 * - T1H: 550 nS to 850 nS, inclusive
 * - T1L: 450 nS to 750 nS, inclusive
 * WS2812B:
 * - T1H: 750 nS to 1050 nS, inclusive
 * - T1L: 200 nS to 500 nS, inclusive
 *
 * The duty cycle is calculated for a high period of 800 nS.
 * This is in the middle of the specifications of the WS2812 and WS2812B.
 */
#define WS2812_DUTYCYCLE_1 (WS2812_PWM_FREQUENCY / (1000000000 / 800))
#if (WS2812_DUTYCYCLE_1 > 255)
#    error WS2812 PWM driver: High period for a 1 is more than a byte
#endif

/* --- PRIVATE MACROS ------------------------------------------------------- */

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given bit
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_COUNT)
 * @param[in] byte:                 The byte number [0, 2]
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#define WS2812_BIT(led, byte, bit) (WS2812_COLOR_BITS * (led) + 8 * (byte) + (7 - (bit)))

#if (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_GRB)
/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given red bit
 *
 * @note    The red byte is the middle byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_COUNT)
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#    define WS2812_RED_BIT(led, bit) WS2812_BIT((led), 1, (bit))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given green bit
 *
 * @note    The red byte is the first byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_COUNT)
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#    define WS2812_GREEN_BIT(led, bit) WS2812_BIT((led), 0, (bit))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given blue bit
 *
 * @note    The red byte is the last byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_COUNT)
 * @param[in] bit:                  The bit index [0, 7]
 *
 * @return                          The bit index
 */
#    define WS2812_BLUE_BIT(led, bit) WS2812_BIT((led), 2, (bit))

#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_RGB)
/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given red bit
 *
 * @note    The red byte is the middle byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_COUNT)
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#    define WS2812_RED_BIT(led, bit) WS2812_BIT((led), 0, (bit))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given green bit
 *
 * @note    The red byte is the first byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_COUNT)
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#    define WS2812_GREEN_BIT(led, bit) WS2812_BIT((led), 1, (bit))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given blue bit
 *
 * @note    The red byte is the last byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_COUNT)
 * @param[in] bit:                  The bit index [0, 7]
 *
 * @return                          The bit index
 */
#    define WS2812_BLUE_BIT(led, bit) WS2812_BIT((led), 2, (bit))

#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_BGR)
/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given red bit
 *
 * @note    The red byte is the middle byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_COUNT)
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#    define WS2812_RED_BIT(led, bit) WS2812_BIT((led), 2, (bit))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given green bit
 *
 * @note    The red byte is the first byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_COUNT)
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#    define WS2812_GREEN_BIT(led, bit) WS2812_BIT((led), 1, (bit))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given blue bit
 *
 * @note    The red byte is the last byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_COUNT)
 * @param[in] bit:                  The bit index [0, 7]
 *
 * @return                          The bit index
 */
#    define WS2812_BLUE_BIT(led, bit) WS2812_BIT((led), 0, (bit))
#endif

#ifdef RGBW
/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given white bit
 *
 * @note    The white byte is the last byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_N)
 * @param[in] bit:                  The bit index [0, 7]
 *
 * @return                          The bit index
 */
#    define WS2812_WHITE_BIT(led, bit) WS2812_BIT((led), 3, (bit))
#endif

/* --- PRIVATE VARIABLES ---------------------------------------------------- */

// STM32F2XX, STM32F4XX and STM32F7XX do NOT zero pad DMA transfers of unequal data width. Buffer width must match TIMx CCR.
// For all other STM32 DMA transfer will automatically zero pad. We only need to set the right peripheral width.
#if defined(STM32F2XX) || defined(STM32F4XX) || defined(STM32F7XX)
#    if defined(WS2812_PWM_TIMER_32BIT)
#        define WS2812_DMA_MEMORY_WIDTH STM32_DMA_CR_MSIZE_WORD
#        define WS2812_DMA_PERIPHERAL_WIDTH STM32_DMA_CR_PSIZE_WORD
typedef uint32_t ws2812_buffer_t;
#    else
#        define WS2812_DMA_MEMORY_WIDTH STM32_DMA_CR_MSIZE_HWORD
#        define WS2812_DMA_PERIPHERAL_WIDTH STM32_DMA_CR_PSIZE_HWORD
typedef uint16_t ws2812_buffer_t;
#    endif
#else
#    define WS2812_DMA_MEMORY_WIDTH STM32_DMA_CR_MSIZE_BYTE
#    if defined(WS2812_PWM_TIMER_32BIT)
#        define WS2812_DMA_PERIPHERAL_WIDTH STM32_DMA_CR_PSIZE_WORD
#    else
#        define WS2812_DMA_PERIPHERAL_WIDTH STM32_DMA_CR_PSIZE_HWORD
#    endif
typedef uint8_t ws2812_buffer_t;
#endif

static ws2812_buffer_t ws2812_frame_buffer[WS2812_BIT_N + 1]; /**< Buffer for a frame */

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */
/*
 * Gedanke: Double-buffer type transactions: double buffer transfers using two memory pointers for
 * the memory (while the DMA is reading/writing from/to a buffer, the application can
 * write/read to/from the other buffer).
 */

void ws2812_init(void) {
    // Initialize led frame buffer
    uint32_t i;
    for (i = 0; i < WS2812_COLOR_BIT_N; i++)
        ws2812_frame_buffer[i] = WS2812_DUTYCYCLE_0; // All color bits are zero duty cycle
    for (i = 0; i < WS2812_RESET_BIT_N; i++)
        ws2812_frame_buffer[i + WS2812_COLOR_BIT_N] = 0; // All reset bits are zero

    palSetLineMode(WS2812_DI_PIN, WS2812_OUTPUT_MODE);

    // PWM Configuration
    //#pragma GCC diagnostic ignored "-Woverride-init"  // Turn off override-init warning for this struct. We use the overriding ability to set a "default" channel config
    static const PWMConfig ws2812_pwm_config = {
        .frequency = WS2812_PWM_FREQUENCY,
        .period    = WS2812_PWM_PERIOD, // Mit dieser Periode wird UDE-Event erzeugt und ein neuer Wert (Länge WS2812_BIT_N) vom DMA ins CCR geschrieben
        .callback  = NULL,
        .channels =
            {
                [0 ... 3]                = {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},    // Channels default to disabled
                [WS2812_PWM_CHANNEL - 1] = {.mode = WS2812_PWM_OUTPUT_MODE, .callback = NULL}, // Turn on the channel we care about
            },
        .cr2  = 0,
        .dier = TIM_DIER_UDE, // DMA on update event for next period
    };
    //#pragma GCC diagnostic pop  // Restore command-line warning options

    // Configure DMA
    // dmaInit(); // Joe added this
#if defined(WB32F3G71xx) || defined(WB32FQ95xx)
    dmaStreamAlloc(WS2812_DMA_STREAM - WB32_DMA_STREAM(0), 10, NULL, NULL);
    dmaStreamSetSource(WS2812_DMA_STREAM, ws2812_frame_buffer);
    dmaStreamSetDestination(WS2812_DMA_STREAM, &(WS2812_PWM_DRIVER.tim->CCR[WS2812_PWM_CHANNEL - 1])); // Ziel ist der An-Zeit im Cap-Comp-Register
    dmaStreamSetMode(WS2812_DMA_STREAM, WB32_DMA_CHCFG_HWHIF(WS2812_DMA_CHANNEL) | WB32_DMA_CHCFG_DIR_M2P | WB32_DMA_CHCFG_PSIZE_WORD | WB32_DMA_CHCFG_MSIZE_WORD | WB32_DMA_CHCFG_MINC | WB32_DMA_CHCFG_CIRC | WB32_DMA_CHCFG_TCIE | WB32_DMA_CHCFG_PL(3));
#else
    dmaStreamAlloc(WS2812_DMA_STREAM - STM32_DMA_STREAM(0), 10, NULL, NULL);
    dmaStreamSetPeripheral(WS2812_DMA_STREAM, &(WS2812_PWM_DRIVER.tim->CCR[WS2812_PWM_CHANNEL - 1])); // Ziel ist der An-Zeit im Cap-Comp-Register
    dmaStreamSetMemory0(WS2812_DMA_STREAM, ws2812_frame_buffer);
    dmaStreamSetMode(WS2812_DMA_STREAM, STM32_DMA_CR_CHSEL(WS2812_DMA_CHANNEL) | STM32_DMA_CR_DIR_M2P | WS2812_DMA_PERIPHERAL_WIDTH | WS2812_DMA_MEMORY_WIDTH | STM32_DMA_CR_MINC | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));
#endif
    dmaStreamSetTransactionSize(WS2812_DMA_STREAM, WS2812_BIT_N);
    // M2P: Memory 2 Periph; PL: Priority Level

#if (STM32_DMA_SUPPORTS_DMAMUX == TRUE)
    // If the MCU has a DMAMUX we need to assign the correct resource
    dmaSetRequestSource(WS2812_DMA_STREAM, WS2812_DMAMUX_ID);
#endif

    // Start DMA
    dmaStreamEnable(WS2812_DMA_STREAM);

    // Configure PWM
    // NOTE: It's required that preload be enabled on the timer channel CCR register. This is currently enabled in the
    // ChibiOS driver code, so we don't have to do anything special to the timer. If we did, we'd have to start the timer,
    // disable counting, enable the channel, and then make whatever configuration changes we need.
    pwmStart(&WS2812_PWM_DRIVER, &ws2812_pwm_config);
    pwmEnableChannel(&WS2812_PWM_DRIVER, WS2812_PWM_CHANNEL - 1, 0); // Initial period is 0; output will be low until first duty cycle is DMA'd in
}

void ws2812_write_led(uint16_t led_number, uint8_t r, uint8_t g, uint8_t b) {
    // Write color to frame buffer
    for (uint8_t bit = 0; bit < 8; bit++) {
        ws2812_frame_buffer[WS2812_RED_BIT(led_number, bit)]   = ((r >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
        ws2812_frame_buffer[WS2812_GREEN_BIT(led_number, bit)] = ((g >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
        ws2812_frame_buffer[WS2812_BLUE_BIT(led_number, bit)]  = ((b >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
    }
}
void ws2812_write_led_rgbw(uint16_t led_number, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    // Write color to frame buffer
    for (uint8_t bit = 0; bit < 8; bit++) {
        ws2812_frame_buffer[WS2812_RED_BIT(led_number, bit)]   = ((r >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
        ws2812_frame_buffer[WS2812_GREEN_BIT(led_number, bit)] = ((g >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
        ws2812_frame_buffer[WS2812_BLUE_BIT(led_number, bit)]  = ((b >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
#ifdef RGBW
        ws2812_frame_buffer[WS2812_WHITE_BIT(led_number, bit)] = ((w >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
#endif
    }
}

// Setleds for standard RGB
void ws2812_setleds(LED_TYPE* ledarray, uint16_t leds) {
    static bool s_init = false;
    if (!s_init) {
        ws2812_init();
        s_init = true;
    }

    for (uint16_t i = 0; i < leds; i++) {
#ifdef RGBW
        ws2812_write_led_rgbw(i, ledarray[i].r, ledarray[i].g, ledarray[i].b, ledarray[i].w);
#else
        ws2812_write_led(i, ledarray[i].r, ledarray[i].g, ledarray[i].b);
#endif
    }
}
