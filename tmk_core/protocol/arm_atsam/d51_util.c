#include "d51_util.h"

//Display unsigned 32-bit number through m15
//Read as follows: 1230 = || ||| |||| |  (note always ending toggle)
void m15_print(uint32_t x)
{
    int8_t t;
    uint32_t n;
    uint32_t p, p2;

    if      (x < 10) t = 0;
    else if (x < 100) t = 1;
    else if (x < 1000) t = 2;
    else if (x < 10000) t = 3;
    else if (x < 100000) t = 4;
    else if (x < 1000000) t = 5;
    else if (x < 10000000) t = 6;
    else if (x < 100000000) t = 7;
    else if (x < 1000000000) t = 8;
    else t = 9;

    while (t >= 0)
    {
        p2 = t;
        p = 1;
        while (p2--) p *= 10;
        n = x / p;
        x -= n * p;
        while (n > 0)
        {
            m15_on;
            n--;
            m15_off;
        }
        //Will always end with an extra toggle
        m15_on;
        t--;
        m15_off;
    }
}

//Display unsigned 32-bit number through debug led
//Read as follows: 1230 = [*]  [* *]  [* * *]  [**]  (note zero is fast double flash)
#define DLED_ONTIME 1000000
#define DLED_PAUSE 1500000
volatile uint32_t w;
void dled_print(uint32_t x, uint8_t long_pause)
{
    int8_t t;
    uint32_t n;
    uint32_t p, p2;

    if      (x < 10) t = 0;
    else if (x < 100) t = 1;
    else if (x < 1000) t = 2;
    else if (x < 10000) t = 3;
    else if (x < 100000) t = 4;
    else if (x < 1000000) t = 5;
    else if (x < 10000000) t = 6;
    else if (x < 100000000) t = 7;
    else if (x < 1000000000) t = 8;
    else t = 9;

    while (t >= 0)
    {
        p2 = t;
        p = 1;
        while (p2--) p *= 10;
        n = x / p;
        x -= n * p;
        if (!n)
        {
            led_on;
            for (w = DLED_ONTIME / 4; w; w--);
            led_off;
            for (w = DLED_ONTIME / 4; w; w--);
            led_on;
            for (w = DLED_ONTIME / 4; w; w--);
            led_off;
            for (w = DLED_ONTIME / 4; w; w--);
            n--;
        }
        else
        {
            while (n > 0)
            {
                led_on;
                for (w = DLED_ONTIME; w; w--);
                led_off;
                for (w = DLED_ONTIME / 2; w; w--);
                n--;
            }
        }

        for (w = DLED_PAUSE; w; w--);
        t--;
    }

    if (long_pause)
    {
        for (w = DLED_PAUSE * 4; w; w--);
    }
}

#ifdef DEBUG_BOOT_TRACING

volatile uint32_t debug_code;

void EIC_15_Handler()
{
    //This is only for non-functional keyboard troubleshooting and should be disabled after boot
    //Intention is to lock up the keyboard here with repeating debug led code
    while (1)
    {
        dled_print(debug_code, 1);
    }
}

void debug_code_init(void)
{
    DBGC(DC_UNSET);

    //Configure Ports for EIC on PB31
    PORT->Group[1].DIRCLR.reg = 1 << 31; //Input
    PORT->Group[1].OUTSET.reg = 1 << 31; //High
    PORT->Group[1].PINCFG[31].bit.INEN = 1; //Input Enable
    PORT->Group[1].PINCFG[31].bit.PULLEN = 1; //Pull Enable
    PORT->Group[1].PINCFG[31].bit.PMUXEN = 1; //Mux Enable
    PORT->Group[1].PMUX[15].bit.PMUXO = 0; //Mux A

    //Enable CLK_EIC_APB
    MCLK->APBAMASK.bit.EIC_ = 1;

    //Configure EIC
    EIC->CTRLA.bit.SWRST = 1;
    while (EIC->SYNCBUSY.bit.SWRST) {}
    EIC->ASYNCH.reg = 1 << 15;
    EIC->INTENSET.reg = 1 << 15;
    EIC->CONFIG[1].bit.SENSE7 = 2;
    EIC->CTRLA.bit.ENABLE = 1;
    while (EIC->SYNCBUSY.bit.ENABLE) {}

    //Enable EIC IRQ
    NVIC_EnableIRQ(EIC_15_IRQn);
}

void debug_code_disable(void)
{
    //Disable EIC IRQ
    NVIC_DisableIRQ(EIC_15_IRQn);

    //Disable EIC
    EIC->CTRLA.bit.ENABLE = 0;
    while (EIC->SYNCBUSY.bit.ENABLE) {}

    //Disable CLK_EIC_APB
    MCLK->APBAMASK.bit.EIC_ = 0;
}

#else

void debug_code_init(void) {}
void debug_code_disable(void) {}

#endif //DEBUG_BOOT_TRACING
