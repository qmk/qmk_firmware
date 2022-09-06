#include "d51_util.h"

static volatile uint32_t w;

// Display unsigned 32-bit number by port toggling DBG_1 (to view on a scope)
// Read as follows: 1230 = |    | |    | | |    ||  (note zero is fast double toggle)
#define DBG_PAUSE 5
void dbg_print(uint32_t x) {
    int8_t   t;
    uint32_t n;
    uint32_t p, p2;

    if (x < 10)
        t = 0;
    else if (x < 100)
        t = 1;
    else if (x < 1000)
        t = 2;
    else if (x < 10000)
        t = 3;
    else if (x < 100000)
        t = 4;
    else if (x < 1000000)
        t = 5;
    else if (x < 10000000)
        t = 6;
    else if (x < 100000000)
        t = 7;
    else if (x < 1000000000)
        t = 8;
    else
        t = 9;

    while (t >= 0) {
        p2 = t;
        p  = 1;
        while (p2--) p *= 10;
        n = x / p;
        x -= n * p;
        if (!n) {
            DBG_1_ON;
            DBG_1_OFF;
            DBG_1_ON;
            DBG_1_OFF;
            n--;
        } else {
            while (n > 0) {
                DBG_1_ON;
                DBG_1_OFF;
                n--;
            }
        }

        t--;
    }

    for (w = DBG_PAUSE; w; w--)
        ;  // Long pause after number is complete
}

// Display unsigned 32-bit number through debug led
// Read as follows: 1230 = [*]  [* *]  [* * *]  [**]  (note zero is fast double flash)
#define DLED_ONTIME 1000000
#define DLED_PAUSE 1500000
void dled_print(uint32_t x, uint8_t long_pause) {
    int8_t   t;
    uint32_t n;
    uint32_t p, p2;

    if (x < 10)
        t = 0;
    else if (x < 100)
        t = 1;
    else if (x < 1000)
        t = 2;
    else if (x < 10000)
        t = 3;
    else if (x < 100000)
        t = 4;
    else if (x < 1000000)
        t = 5;
    else if (x < 10000000)
        t = 6;
    else if (x < 100000000)
        t = 7;
    else if (x < 1000000000)
        t = 8;
    else
        t = 9;

    while (t >= 0) {
        p2 = t;
        p  = 1;
        while (p2--) p *= 10;
        n = x / p;
        x -= n * p;
        if (!n) {
            DBG_LED_ON;
            for (w = DLED_ONTIME / 4; w; w--)
                ;
            DBG_LED_OFF;
            for (w = DLED_ONTIME / 4; w; w--)
                ;
            DBG_LED_ON;
            for (w = DLED_ONTIME / 4; w; w--)
                ;
            DBG_LED_OFF;
            for (w = DLED_ONTIME / 4; w; w--)
                ;
            n--;
        } else {
            while (n > 0) {
                DBG_LED_ON;
                for (w = DLED_ONTIME; w; w--)
                    ;
                DBG_LED_OFF;
                for (w = DLED_ONTIME / 2; w; w--)
                    ;
                n--;
            }
        }

        for (w = DLED_PAUSE; w; w--)
            ;
        t--;
    }

    if (long_pause) {
        for (w = DLED_PAUSE * 4; w; w--)
            ;
    }
}

#ifdef DEBUG_BOOT_TRACING_ENABLE

volatile uint32_t debug_code;

// These macros are for compile time substitution
#    define DEBUG_BOOT_TRACING_EXTINTn (DEBUG_BOOT_TRACING_PIN % _U_(0x10))
#    define DEBUG_BOOT_TRACING_EXTINTb (_U_(0x1) << DEBUG_BOOT_TRACING_EXTINTn)
#    define DEBUG_BOOT_TRACING_CONFIG_INDn (DEBUG_BOOT_TRACING_EXTINTn / _U_(0x8))
#    define DEBUG_BOOT_TRACING_CONFIG_SENSEn (DEBUG_BOOT_TRACING_EXTINTn % _U_(0x8))
#    define DEBUG_BOOT_TRACING_CONFIG_SENSEb (DEBUG_BOOT_TRACING_CONFIG_SENSEn * _U_(0x4))
#    define DEBUG_BOOT_TRACING_IRQn (EIC_0_IRQn + DEBUG_BOOT_TRACING_EXTINTn)

// These macros perform PORT+PIN definition translation to IRQn in the preprocessor
#    define PORTPIN_TO_IRQn_EXPAND(def) def
#    define PORTPIN_TO_IRQn_DEF(def) PORTPIN_TO_IRQn_EXPAND(def)
#    if DEBUG_BOOT_TRACING_PIN < 10
#        define PORTPIN_TO_IRQn_TODEF(port, pin) PORTPIN_TO_IRQn_DEF(PIN_##port##0##pin##A_EIC_EXTINT_NUM)
#    else
#        define PORTPIN_TO_IRQn_TODEF(port, pin) PORTPIN_TO_IRQn_DEF(PIN_##port##pin##A_EIC_EXTINT_NUM)
#    endif
#    define PORTPIN_TO_IRQn(port, pin) PORTPIN_TO_IRQn_TODEF(port, pin)

// These macros perform function name output in the preprocessor
#    define DEBUG_BOOT_TRACING_HANDLER_CONCAT(irq) void EIC_##irq##_Handler(void)
#    define DEBUG_BOOT_TRACING_HANDLER(irq) DEBUG_BOOT_TRACING_HANDLER_CONCAT(irq)

// To generate the function name of the IRQ handler catching boot tracing,
//  certain macros must be undefined, so save their current values to macro stack
#    pragma push_macro("PA")
#    pragma push_macro("PB")
#    pragma push_macro("_L_")

// Undefine / redefine pushed macros
#    undef PA
#    undef PB
#    undef _L_
#    define _L_(x) x

// Perform the work and output
// Ex: PORT PB, PIN 31 = void EIC_15_Handler(void)
DEBUG_BOOT_TRACING_HANDLER(PORTPIN_TO_IRQn(DEBUG_BOOT_TRACING_PORT, DEBUG_BOOT_TRACING_PIN))
// Restore macros
#    pragma pop_macro("PA")
#    pragma pop_macro("PB")
#    pragma pop_macro("_L_")
{
    // This is only for non-functional keyboard troubleshooting and should be disabled after boot
    // Intention is to lock up the keyboard here with repeating debug led code
    while (1) {
        dled_print(debug_code, 1);
    }
}

void debug_code_init(void) {
    DBGC(DC_UNSET);

    // Configure Ports for EIC
    PORT->Group[DEBUG_BOOT_TRACING_PORT].DIRCLR.reg                                 = 1 << DEBUG_BOOT_TRACING_PIN;  // Input
    PORT->Group[DEBUG_BOOT_TRACING_PORT].OUTSET.reg                                 = 1 << DEBUG_BOOT_TRACING_PIN;  // High
    PORT->Group[DEBUG_BOOT_TRACING_PORT].PINCFG[DEBUG_BOOT_TRACING_PIN].bit.INEN    = 1;                            // Input Enable
    PORT->Group[DEBUG_BOOT_TRACING_PORT].PINCFG[DEBUG_BOOT_TRACING_PIN].bit.PULLEN  = 1;                            // Pull Enable
    PORT->Group[DEBUG_BOOT_TRACING_PORT].PINCFG[DEBUG_BOOT_TRACING_PIN].bit.PMUXEN  = 1;                            // Mux Enable
    PORT->Group[DEBUG_BOOT_TRACING_PORT].PMUX[DEBUG_BOOT_TRACING_PIN / 2].bit.PMUXO = 0;                            // Mux A

    // Enable CLK_EIC_APB
    MCLK->APBAMASK.bit.EIC_ = 1;

    // Configure EIC
    EIC->CTRLA.bit.SWRST = 1;
    while (EIC->SYNCBUSY.bit.SWRST) {
    }
    EIC->ASYNCH.reg   = DEBUG_BOOT_TRACING_EXTINTb;
    EIC->INTENSET.reg = DEBUG_BOOT_TRACING_EXTINTb;
    EIC->CONFIG[DEBUG_BOOT_TRACING_CONFIG_INDn].reg |= (EIC_CONFIG_SENSE0_FALL_Val << DEBUG_BOOT_TRACING_CONFIG_SENSEb);
    EIC->CTRLA.bit.ENABLE = 1;
    while (EIC->SYNCBUSY.bit.ENABLE) {
    }

    // Enable EIC IRQ
    NVIC_EnableIRQ(DEBUG_BOOT_TRACING_IRQn);
}

void debug_code_disable(void) {
    // Disable EIC IRQ
    NVIC_DisableIRQ(DEBUG_BOOT_TRACING_IRQn);

    // Disable EIC
    EIC->CTRLA.bit.ENABLE = 0;
    while (EIC->SYNCBUSY.bit.ENABLE) {
    }

    // Default port configuration
    PORT->Group[DEBUG_BOOT_TRACING_PORT].DIRCLR.reg                                 = 1 << DEBUG_BOOT_TRACING_PIN;  // Input
    PORT->Group[DEBUG_BOOT_TRACING_PORT].OUTCLR.reg                                 = 1 << DEBUG_BOOT_TRACING_PIN;  // Low
    PORT->Group[DEBUG_BOOT_TRACING_PORT].PINCFG[DEBUG_BOOT_TRACING_PIN].bit.INEN    = 0;                            // Input Disable
    PORT->Group[DEBUG_BOOT_TRACING_PORT].PINCFG[DEBUG_BOOT_TRACING_PIN].bit.PULLEN  = 0;                            // Pull Disable
    PORT->Group[DEBUG_BOOT_TRACING_PORT].PINCFG[DEBUG_BOOT_TRACING_PIN].bit.PMUXEN  = 0;                            // Mux Disable
    PORT->Group[DEBUG_BOOT_TRACING_PORT].PMUX[DEBUG_BOOT_TRACING_PIN / 2].bit.PMUXO = 0;                            // Mux A

    // Disable CLK_EIC_APB
    MCLK->APBAMASK.bit.EIC_ = 0;
}

#else

void debug_code_init(void) {}
void debug_code_disable(void) {}

#endif  // DEBUG_BOOT_TRACING_ENABLE
