#include "ch.h"
#include "hal.h"

#include "led.h"
#include "sleep_led.h"

#if defined(KL2x) || defined(K20x) /* platform selection: familiar Kinetis chips */
/* All right, we go the "software" way: LP timer, toggle LED in interrupt.
 * Based on hasu's code for AVRs.
 */

/* Breathing Sleep LED brighness(PWM On period) table
 * (64[steps] * 4[duration]) / 64[PWM periods/s] = 4 second breath cycle
 *
 * http://www.wolframalpha.com/input/?i=%28sin%28+x%2F64*pi%29**8+*+255%2C+x%3D0+to+63
 * (0..63).each {|x| p ((sin(x/64.0*PI)**8)*255).to_i }
 */
static const uint8_t breathing_table[64] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 6, 10,
15, 23, 32, 44, 58, 74, 93, 113, 135, 157, 179, 199, 218, 233, 245, 252,
255, 252, 245, 233, 218, 199, 179, 157, 135, 113, 93, 74, 58, 44, 32, 23,
15, 10, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* LP Timer interrupt handler */
OSAL_IRQ_HANDLER(KINETIS_LPTMR0_IRQ_VECTOR) {
    OSAL_IRQ_PROLOGUE();

    /* Software PWM
    * timer:1111 1111 1111 1111
    *       \_____/\/ \_______/____  count(0-255)
    *          \    \______________  duration of step(4)
    *           \__________________  index of step table(0-63)
    */

    // this works for cca 65536 irqs/sec
    static union {
    uint16_t row;
    struct {
      uint8_t count:8;
      uint8_t duration:2;
      uint8_t index:6;
    } pwm;
    } timer = { .row = 0 };

    timer.row++;

    // LED on
    if (timer.pwm.count == 0) {
        led_set(1<<USB_LED_CAPS_LOCK);
    }
    // LED off
    if (timer.pwm.count == breathing_table[timer.pwm.index]) {
        led_set(0);
    }

    /* Reset the counter */
    LPTMR0->CSR |= LPTMRx_CSR_TCF;

    OSAL_IRQ_EPILOGUE();
}

/* LPTMR clock options */
#define LPTMR_CLOCK_MCGIRCLK 0 /* 4MHz clock */
#define LPTMR_CLOCK_LPO      1 /* 1kHz clock */
#define LPTMR_CLOCK_ERCLK32K 2
#define LPTMR_CLOCK_OSCERCLK 3 /* output from OSC */

/* Work around inconsistencies in Freescale naming */
#if !defined(SIM_SCGC5_LPTMR)
#define SIM_SCGC5_LPTMR SIM_SCGC5_LPTIMER
#endif

/* Initialise the timer */
void sleep_led_init(void) {
    /* Make sure the clock to the LPTMR is enabled */
    SIM->SCGC5 |= SIM_SCGC5_LPTMR;
    /* Reset LPTMR settings */
    LPTMR0->CSR = 0;
    /* Set the compare value */
    LPTMR0->CMR = 1;  // trigger on counter value (i.e. every time)
    /* Set up clock source and prescaler */
    /* Software PWM
    *  ______           ______           __
    * |  ON  |___OFF___|  ON  |___OFF___|   ....
    * |<-------------->|<-------------->|<- ....
    *     PWM period       PWM period
    *
    * R                interrupts/period[resolution]
    * F                periods/second[frequency]
    * R * F            interrupts/second
    */
    /* === OPTION 1 === */
    //  for 1kHz LPO
    //  No prescaler => 1024 irqs/sec
    // LPTMR0->PSR = LPTMRx_PSR_PCS(LPTMR_CLOCK_LPO)|LPTMRx_PSR_PBYP;
    /* === OPTION 2 === */
    //  for nMHz IRC (n=4 on KL25Z, KL26Z and K20x; n=2 or 8 on KL27Z)
    MCG->C2 |= MCG_C2_IRCS; // fast (4MHz) internal ref clock
    #if defined(KL27Z) // divide the 8MHz IRC by 2, to have the same MCGIRCLK speed as others
    MCG->MC |= MCG_MC_LIRC_DIV2_DIV2;
    #endif /* KL27Z */
    MCG->C1 |= MCG_C1_IRCLKEN; // enable internal ref clock
    //  to work in stop mode, also MCG_C1_IREFSTEN
    //  Divide 4MHz by 2^N (N=5) => 62500 irqs/sec =>
    //  => approx F=61, R=256, duration = 4
    LPTMR0->PSR = LPTMRx_PSR_PCS(LPTMR_CLOCK_MCGIRCLK)|LPTMRx_PSR_PRESCALE(5);
    /* === OPTION 3 === */
    //  for OSC output (external crystal), usually 8MHz or 16MHz
    // OSC0->CR |= OSC_CR_ERCLKEN; // enable ext ref clock
    //  to work in stop mode, also OSC_CR_EREFSTEN
    //  Divide by 2^N
    // LPTMR0->PSR = LPTMRx_PSR_PCS(LPTMR_CLOCK_OSCERCLK)|LPTMRx_PSR_PRESCALE(7);
    /* === END OPTIONS === */
    /* Interrupt on TCF set (compare flag) */
    nvicEnableVector(LPTMR0_IRQn, 2); // vector, priority
    LPTMR0->CSR |= LPTMRx_CSR_TIE;
}

void sleep_led_enable(void) {
    /* Enable the timer */
    LPTMR0->CSR |= LPTMRx_CSR_TEN;
}

void sleep_led_disable(void) {
    /* Disable the timer */
    LPTMR0->CSR &= ~LPTMRx_CSR_TEN;
}

void sleep_led_toggle(void) {
    /* Toggle the timer */
    LPTMR0->CSR ^= LPTMRx_CSR_TEN;
}

#else /* platform selection: not on familiar Kinetis chips */

void sleep_led_init(void) {
}
 
void sleep_led_enable(void) {
    led_set(1<<USB_LED_CAPS_LOCK);
}
 
void sleep_led_disable(void) {
    led_set(0);
}
 
void sleep_led_toggle(void) {
    // not implemented
}

#endif /* platform selection */