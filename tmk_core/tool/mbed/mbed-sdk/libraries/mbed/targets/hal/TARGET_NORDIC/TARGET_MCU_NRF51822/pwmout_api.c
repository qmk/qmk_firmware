/* mbed Microcontroller Library
 * Copyright (c) 2013 Nordic Semiconductor
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed_assert.h"
#include "pwmout_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"

#define NO_PWMS         3
#define TIMER_PRECISION 4 //4us ticks
#define TIMER_PRESCALER 6 //4us ticks  =   16Mhz/(2**6)
static const PinMap PinMap_PWM[] = {
    {p0,  PWM_1, 1},
    {p1,  PWM_1, 1},
    {p2,  PWM_1, 1},
    {p3,  PWM_1, 1},
    {p4,  PWM_1, 1},
    {p5,  PWM_1, 1},
    {p6,  PWM_1, 1},
    {p7,  PWM_1, 1},
    {p8,  PWM_1, 1},
    {p9,  PWM_1, 1},
    {p10,  PWM_1, 1},
    {p11,  PWM_1, 1},
    {p12,  PWM_1, 1},
    {p13,  PWM_1, 1},
    {p14,  PWM_1, 1},
    {p15,  PWM_1, 1},
    {p16,  PWM_1, 1},
    {p17,  PWM_1, 1},
    {p18,  PWM_1, 1},
    {p19,  PWM_1, 1},
    {p20,  PWM_1, 1},
    {p21,  PWM_1, 1},
    {p22,  PWM_1, 1},
    {p23,  PWM_1, 1},
    {p24,  PWM_1, 1},
    {p25,  PWM_1, 1},
    {p28,  PWM_1, 1},
    {p29,  PWM_1, 1},
    {p30,  PWM_1, 1},
    {NC, NC, 0}
};

static NRF_TIMER_Type *Timers[1] = {
    NRF_TIMER2
};

uint16_t PERIOD            = 20000 / TIMER_PRECISION;  //20ms
uint8_t PWM_taken[NO_PWMS] = {0, 0, 0};
uint16_t PULSE_WIDTH[NO_PWMS] = {1, 1, 1}; //set to 1 instead of 0
uint16_t ACTUAL_PULSE[NO_PWMS] = {0, 0, 0};


/** @brief Function for handling timer 2 peripheral interrupts.
 */
#ifdef __cplusplus
extern "C" {
#endif
void TIMER2_IRQHandler(void)
{
    NRF_TIMER2->EVENTS_COMPARE[3] = 0;
    NRF_TIMER2->CC[3]             =  PERIOD;

    if (PWM_taken[0]) {
        NRF_TIMER2->CC[0] = PULSE_WIDTH[0];
    }
    if (PWM_taken[1]) {
        NRF_TIMER2->CC[1] = PULSE_WIDTH[1];
    }
    if (PWM_taken[2]) {
        NRF_TIMER2->CC[2] = PULSE_WIDTH[2];
    }

    NRF_TIMER2->TASKS_START = 1;
}

#ifdef __cplusplus
}
#endif
/** @brief Function for initializing the Timer peripherals.
 */
void timer_init(uint8_t pwmChoice)
{
    NRF_TIMER_Type *timer = Timers[0];
    timer->TASKS_STOP = 0;

    if (pwmChoice == 0) {
        timer->POWER     = 0;
        timer->POWER     = 1;
        timer->MODE      = TIMER_MODE_MODE_Timer;
        timer->BITMODE   = TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos;
        timer->PRESCALER = TIMER_PRESCALER;
        timer->CC[3]     = PERIOD;
    }

    timer->CC[pwmChoice] = PULSE_WIDTH[pwmChoice];

    //high priority application interrupt
    NVIC_SetPriority(TIMER2_IRQn, 1);
    NVIC_EnableIRQ(TIMER2_IRQn);

    timer->TASKS_START = 0x01;
}

/** @brief Function for initializing the GPIO Tasks/Events peripheral.
 */
void gpiote_init(PinName pin, uint8_t channel_number)
{
    // Connect GPIO input buffers and configure PWM_OUTPUT_PIN_NUMBER as an output.
    NRF_GPIO->PIN_CNF[pin] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                            | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                            | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                            | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                            | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
    NRF_GPIO->OUTCLR = (1UL << pin);
    // Configure GPIOTE channel 0 to toggle the PWM pin state
    // @note Only one GPIOTE task can be connected to an output pin.
    /* Configure channel to Pin31, not connected to the pin, and configure as a tasks that will set it to proper level */
    NRF_GPIOTE->CONFIG[channel_number] = (GPIOTE_CONFIG_MODE_Task << GPIOTE_CONFIG_MODE_Pos) |
                                         (31UL << GPIOTE_CONFIG_PSEL_Pos) |
                                         (GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos);
    /* Three NOPs are required to make sure configuration is written before setting tasks or getting events */
    __NOP();
    __NOP();
    __NOP();
    /* Launch the task to take the GPIOTE channel output to the desired level */
    NRF_GPIOTE->TASKS_OUT[channel_number] = 1;

    /* Finally configure the channel as the caller expects. If OUTINIT works, the channel is configured properly.
       If it does not, the channel output inheritance sets the proper level. */
    NRF_GPIOTE->CONFIG[channel_number] = (GPIOTE_CONFIG_MODE_Task << GPIOTE_CONFIG_MODE_Pos) |
                                         ((uint32_t)pin << GPIOTE_CONFIG_PSEL_Pos) |
                                         ((uint32_t)GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos) |
                                         ((uint32_t)GPIOTE_CONFIG_OUTINIT_Low << GPIOTE_CONFIG_OUTINIT_Pos); // ((uint32_t)GPIOTE_CONFIG_OUTINIT_High <<
                                                                                                             // GPIOTE_CONFIG_OUTINIT_Pos);//

    /* Three NOPs are required to make sure configuration is written before setting tasks or getting events */
    __NOP();
    __NOP();
    __NOP();
}

/** @brief Function for initializing the Programmable Peripheral Interconnect peripheral.
 */
static void ppi_init(uint8_t pwm)
{
    //using ppi channels 0-7 (only 0-7 are available)
    uint8_t channel_number = 2 * pwm;
    NRF_TIMER_Type *timer  = Timers[0];

    // Configure PPI channel 0 to toggle ADVERTISING_LED_PIN_NO on every TIMER1 COMPARE[0] match
    NRF_PPI->CH[channel_number].TEP     = (uint32_t)&NRF_GPIOTE->TASKS_OUT[pwm];
    NRF_PPI->CH[channel_number + 1].TEP = (uint32_t)&NRF_GPIOTE->TASKS_OUT[pwm];
    NRF_PPI->CH[channel_number].EEP     = (uint32_t)&timer->EVENTS_COMPARE[pwm];
    NRF_PPI->CH[channel_number + 1].EEP = (uint32_t)&timer->EVENTS_COMPARE[3];

    // Enable PPI channels.
    NRF_PPI->CHEN |= (1 << channel_number) |
                     (1 << (channel_number + 1));
}

void setModulation(pwmout_t *obj, uint8_t toggle, uint8_t high)
{
    if (high) {
        NRF_GPIOTE->CONFIG[obj->pwm] |= ((uint32_t)GPIOTE_CONFIG_OUTINIT_High << GPIOTE_CONFIG_OUTINIT_Pos);
        if (toggle) {
            NRF_GPIOTE->CONFIG[obj->pwm] |= (GPIOTE_CONFIG_MODE_Task << GPIOTE_CONFIG_MODE_Pos) |
                                            ((uint32_t)GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos);
        } else {
            NRF_GPIOTE->CONFIG[obj->pwm] &= ~((uint32_t)GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos);
            NRF_GPIOTE->CONFIG[obj->pwm] |= ((uint32_t)GPIOTE_CONFIG_POLARITY_LoToHi << GPIOTE_CONFIG_POLARITY_Pos);
        }
    } else {
        NRF_GPIOTE->CONFIG[obj->pwm] &= ~((uint32_t)GPIOTE_CONFIG_OUTINIT_High << GPIOTE_CONFIG_OUTINIT_Pos);

        if (toggle) {
            NRF_GPIOTE->CONFIG[obj->pwm] |= (GPIOTE_CONFIG_MODE_Task << GPIOTE_CONFIG_MODE_Pos) |
                                            ((uint32_t)GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos);
        } else {
            NRF_GPIOTE->CONFIG[obj->pwm] &= ~((uint32_t)GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos);
            NRF_GPIOTE->CONFIG[obj->pwm] |= ((uint32_t)GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos);
        }
    }
}

void pwmout_init(pwmout_t *obj, PinName pin)
{
    // determine the channel
    uint8_t pwmOutSuccess = 0;
    PWMName pwm           = (PWMName)pinmap_peripheral(pin, PinMap_PWM);

    MBED_ASSERT(pwm != (PWMName)NC);

    if (PWM_taken[(uint8_t)pwm]) {
        for (uint8_t i = 1; !pwmOutSuccess && (i<NO_PWMS); i++) {
            if (!PWM_taken[i]) {
                pwm           = (PWMName)i;
                PWM_taken[i]  = 1;
                pwmOutSuccess = 1;
            }
        }
    } else {
        pwmOutSuccess           = 1;
        PWM_taken[(uint8_t)pwm] = 1;
    }

    if (!pwmOutSuccess) {
        error("PwmOut pin mapping failed. All available PWM channels are in use.");
    }

    obj->pwm = pwm;
    obj->pin = pin;

    gpiote_init(pin, (uint8_t)pwm);
    ppi_init((uint8_t)pwm);

    if (pwm == 0) {
        NRF_POWER->TASKS_CONSTLAT = 1;
    }

    timer_init((uint8_t)pwm);

    //default to 20ms: standard for servos, and fine for e.g. brightness control
    pwmout_period_ms(obj, 20);
    pwmout_write    (obj, 0);
}

void pwmout_free(pwmout_t *obj)
{
    MBED_ASSERT(obj->pwm != (PWMName)NC);
    PWM_taken[obj->pwm] = 0;
    pwmout_write(obj, 0);
}

void pwmout_write(pwmout_t *obj, float value)
{
    uint16_t oldPulseWidth;

    NRF_TIMER2->EVENTS_COMPARE[3] = 0;
    NRF_TIMER2->TASKS_STOP        = 1;

    if (value < 0.0f) {
        value = 0.0;
    } else if (value > 1.0f) {
        value = 1.0;
    }

    oldPulseWidth          = ACTUAL_PULSE[obj->pwm];
    ACTUAL_PULSE[obj->pwm] = PULSE_WIDTH[obj->pwm]  = value * PERIOD;

    if (PULSE_WIDTH[obj->pwm] == 0) {
        PULSE_WIDTH[obj->pwm] = 1;
        setModulation(obj, 0, 0);
    } else if (PULSE_WIDTH[obj->pwm] == PERIOD) {
        PULSE_WIDTH[obj->pwm] = PERIOD - 1;
        setModulation(obj, 0, 1);
    } else if ((oldPulseWidth == 0) || (oldPulseWidth == PERIOD)) {
        setModulation(obj, 1, oldPulseWidth == PERIOD);
    }

    NRF_TIMER2->INTENSET    = TIMER_INTENSET_COMPARE3_Msk;
    NRF_TIMER2->SHORTS      = TIMER_SHORTS_COMPARE3_CLEAR_Msk | TIMER_SHORTS_COMPARE3_STOP_Msk;
    NRF_TIMER2->TASKS_START = 1;
}

float pwmout_read(pwmout_t *obj)
{
    return ((float)PULSE_WIDTH[obj->pwm] / (float)PERIOD);
}

void pwmout_period(pwmout_t *obj, float seconds)
{
    pwmout_period_us(obj, seconds * 1000000.0f);
}

void pwmout_period_ms(pwmout_t *obj, int ms)
{
    pwmout_period_us(obj, ms * 1000);
}

// Set the PWM period, keeping the duty cycle the same.
void pwmout_period_us(pwmout_t *obj, int us)
{
    uint32_t periodInTicks = us / TIMER_PRECISION;

    NRF_TIMER2->EVENTS_COMPARE[3] = 0;
    NRF_TIMER2->TASKS_STOP        = 1;

    if (periodInTicks>((1 << 16) - 1)) {
        PERIOD = (1 << 16) - 1; //131ms
    } else if (periodInTicks<5) {
        PERIOD = 5;
    } else {
        PERIOD = periodInTicks;
    }
    NRF_TIMER2->INTENSET    = TIMER_INTENSET_COMPARE3_Msk;
    NRF_TIMER2->SHORTS      = TIMER_SHORTS_COMPARE3_CLEAR_Msk | TIMER_SHORTS_COMPARE3_STOP_Msk;
    NRF_TIMER2->TASKS_START = 1;
}

void pwmout_pulsewidth(pwmout_t *obj, float seconds)
{
    pwmout_pulsewidth_us(obj, seconds * 1000000.0f);
}

void pwmout_pulsewidth_ms(pwmout_t *obj, int ms)
{
    pwmout_pulsewidth_us(obj, ms * 1000);
}

void pwmout_pulsewidth_us(pwmout_t *obj, int us)
{
    uint32_t pulseInTicks  = us / TIMER_PRECISION;
    uint16_t oldPulseWidth = ACTUAL_PULSE[obj->pwm];

    NRF_TIMER2->EVENTS_COMPARE[3] = 0;
    NRF_TIMER2->TASKS_STOP        = 1;

    ACTUAL_PULSE[obj->pwm] = PULSE_WIDTH[obj->pwm]  = pulseInTicks;

    if (PULSE_WIDTH[obj->pwm] == 0) {
        PULSE_WIDTH[obj->pwm] = 1;
        setModulation(obj, 0, 0);
    } else if (PULSE_WIDTH[obj->pwm] == PERIOD) {
        PULSE_WIDTH[obj->pwm] = PERIOD - 1;
        setModulation(obj, 0, 1);
    } else if ((oldPulseWidth == 0) || (oldPulseWidth == PERIOD)) {
        setModulation(obj, 1, oldPulseWidth == PERIOD);
    }
    NRF_TIMER2->INTENSET    = TIMER_INTENSET_COMPARE3_Msk;
    NRF_TIMER2->SHORTS      = TIMER_SHORTS_COMPARE3_CLEAR_Msk | TIMER_SHORTS_COMPARE3_STOP_Msk;
    NRF_TIMER2->TASKS_START = 1;
}
