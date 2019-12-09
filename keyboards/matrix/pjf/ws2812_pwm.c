/*
 * ws2812_pwm.c
 *
 */

#include "ws2812_pwm.h"
#include "ch.h"
#include "hal.h"
#include "wait.h"

#define PIN_MASK(pin)           (0x01<<pin)
#define RGBBUF_LEN              (RGBLED_NUM*24)
static uint32_t rgb_buffer[RGBBUF_LEN];
static uint32_t dma_source[0];

static void setColor(uint8_t color, uint32_t *buf, uint32_t pin)
{
    for (int i = 0; i < 8; i++){
        buf[i]=((color<<i)&0x80 ? 0x0 : PIN_MASK(pin));
    }
}

static void setColorRGB(uint8_t r, uint8_t g, uint8_t b, uint32_t *buf, uint32_t pin)
{
    setColor(r, buf, pin);
    setColor(g, buf+8, pin);
    setColor(b, buf+16, pin);
}

/**
 * @brief   Initialize Led Driver
 * @details Initialize the Led Driver based on parameters.
 *          Following initialization, the frame buffer would automatically be
 *          exported to the supplied port and pins in the right timing to drive
 *          a chain of WS2812B controllers
 * @note    The function assumes the controller is running at 72Mhz
 * @note    Timing is critical for WS2812. While all timing is done in hardware
 *          need to verify memory bandwidth is not exhausted to avoid DMA delays
 *
 *
 */
void ws2812_init()
{
    palSetPadMode(PORT_WS2812, PIN_WS2812, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(PORT_WS2812, PIN_WS2812);
    wait_ms(1);

    // configure pwm timers -
    // timer 1 as master, active for data transmission and inactive to disable transmission during reset period (50uS)
    // timer 3 as slave, during active time creates a 1.25 uS signal, with duty cycle controlled by frame buffer values
    static PWMConfig pwmc1 = {
        72000000 / 90, /* 800Khz PWM clock frequency. 1/90 of PWMC3   */
        (72000000 / 90) * 0.05, /*Total period is 50ms (20FPS), including sLeds cycles + reset length for ws2812b and FB writes  */
        NULL,
        {
            {PWM_OUTPUT_ACTIVE_HIGH, NULL},
            {PWM_OUTPUT_DISABLED, NULL},
            {PWM_OUTPUT_DISABLED, NULL},
//            {PWM_OUTPUT_ACTIVE_HIGH, pwm1cb},
            {PWM_OUTPUT_DISABLED, NULL}
        },
        TIM_CR2_MMS_2, /* master mode selection */
        0,
    };

    static PWMConfig pwmc3 = {
        72000000,/* 72Mhz PWM clock frequency.   */
        90, /* 90 cycles period (1.25 uS per period @72Mhz       */
        NULL,
        {
            {PWM_OUTPUT_ACTIVE_HIGH, NULL},
            {PWM_OUTPUT_ACTIVE_HIGH, NULL},
            {PWM_OUTPUT_ACTIVE_HIGH, NULL},
            {PWM_OUTPUT_ACTIVE_HIGH, NULL}
        },
        0,
        0,
    };

    for (int j = 0; j < RGBBUF_LEN; j++) {
        rgb_buffer[j] = 0;
    }
    dma_source[0] = PIN_MASK(PIN_WS2812);

    // DMA stream 2, triggered by TIM3_CH3 signal. if FB indicates, reset output value early to indicate "0" bit to ws2812
    dmaStreamAllocate(STM32_DMA1_STREAM2, 10, NULL, NULL);
    dmaStreamSetPeripheral(STM32_DMA1_STREAM2, &(PORT_WS2812->BRR));
    dmaStreamSetMemory0(STM32_DMA1_STREAM2, &rgb_buffer[0]);
    dmaStreamSetTransactionSize(STM32_DMA1_STREAM2, (RGBLED_NUM) * 24);
    dmaStreamSetMode( STM32_DMA1_STREAM2,
        STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_MINC | STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(2));

    // DMA stream 3, triggered by TIM3_UP event. output high at beginning of signal
    dmaStreamAllocate(STM32_DMA1_STREAM3, 10, NULL, NULL);
    dmaStreamSetPeripheral(STM32_DMA1_STREAM3, &(PORT_WS2812->BSRR));
    dmaStreamSetMemory0(STM32_DMA1_STREAM3, dma_source);
    dmaStreamSetTransactionSize(STM32_DMA1_STREAM3, 1);
    dmaStreamSetMode( STM32_DMA1_STREAM3,
        STM32_DMA_CR_TEIE | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));

    // DMA stream 6, triggered by TIM3_CH1 signal. reset output value late to indicate "1" bit to ws2812.
    // always triggers but no affect if dma stream 2 already change output value to 0
    dmaStreamAllocate(STM32_DMA1_STREAM6, 10, NULL, NULL);
    dmaStreamSetPeripheral(STM32_DMA1_STREAM6, &(PORT_WS2812->BRR));
    dmaStreamSetMemory0(STM32_DMA1_STREAM6, dma_source);
    dmaStreamSetTransactionSize(STM32_DMA1_STREAM6, 1);
    dmaStreamSetMode( STM32_DMA1_STREAM6,
        STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));

    pwmStart(&PWMD1, &pwmc1);
    pwmStart(&PWMD3, &pwmc3);

    // set pwm3 as slave, triggerd by pwm1 oc1 event. disables pwmd1 for synchronization.
    PWMD3.tim->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_2; //101: Gated Mode, ITR0 (TS = 000)
    PWMD1.tim->CR1 &= ~TIM_CR1_CEN;

    // set pwm values.
    // 28 (duty in ticks) / 90 (period in ticks) * 1.25uS (period in S) = 0.39 uS
    //pwmEnableChannel(&PWMD3, 2, 28);
    pwmEnableChannel(&PWMD3, 2, 22);
    // 58 (duty in ticks) / 90 (period in ticks) * 1.25uS (period in S) = 0.806 uS
    //pwmEnableChannel(&PWMD3, 0, 58);
    pwmEnableChannel(&PWMD3, 0, 63);
    // active during transfer of 90 cycles * sLeds * 24 bytes * 1/90 multiplier
    pwmEnableChannel(&PWMD1, 0, 90 * RGBLED_NUM * 24 / 90);
//    pwmEnableChannel(&PWMD1, 2, 90 * (RGBLED_NUM+10) * 24 / 90);

    // stop and reset counters for synchronization
    PWMD1.tim->CNT = 0;

    // Slave (TIM3) needs to "update" immediately after master (TIM1) start in order to start in sync.
    // this initial sync is crucial for the stability of the run
    PWMD3.tim->CNT = 89;
    PWMD3.tim->DIER |= TIM_DIER_CC3DE | TIM_DIER_CC1DE | TIM_DIER_UDE;
    dmaStreamEnable(STM32_DMA1_STREAM3);
    dmaStreamEnable(STM32_DMA1_STREAM6);
    dmaStreamEnable(STM32_DMA1_STREAM2);

    // all systems go! both timers and all channels are configured to resonate
    // in complete sync without any need for CPU cycles (only DMA and timers)
    // start pwm1 for system to start resonating
    PWMD1.tim->CR1 |= TIM_CR1_CEN;
}

void ws2812_setleds(uint8_t* leds, uint16_t number)
{
    for (uint16_t i = 0; i < number; i++) {
        setColorRGB(leds[i*3], leds[i*3+1], leds[i*3+2], &rgb_buffer[i*24], PIN_WS2812);
    }
}
