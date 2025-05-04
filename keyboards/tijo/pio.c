#include "hardware/pio.h"
#include "hardware/irq.h"

#include "spi.h"
#include "pio/mux.pio.h"

#define MUX_SM 0
#define MUX_IRQ 0
#define MUX_PIO pio0
#define PIN_BASE 10
#define PIN_COUNT 5

#define MUX_NUM_PINS 5

static uint32_t current_mux = 0;

void mux_irq_handler(void) {
    if (pio_interrupt_get(MUX_PIO, MUX_IRQ)) {
        pio_interrupt_clear(MUX_PIO, MUX_IRQ);

        custom_irq_spi_xfer();

        // Advance to next pin
        if (current_mux != 4) {
            current_mux++;
            pio_sm_put_blocking(MUX_PIO, MUX_SM, current_mux);
            return;
        }
        current_mux = 0;
    }
}

void mux_init(void) {
    uint          offset = pio_add_program(MUX_PIO, &mux_program);
    pio_sm_config c      = mux_program_get_default_config(offset);

    for (int i = 0; i < PIN_COUNT; ++i) {
        pio_gpio_init(MUX_PIO, PIN_BASE + i);
    }

    pio_sm_set_consecutive_pindirs(MUX_PIO, MUX_SM, PIN_BASE, PIN_COUNT, true);

    sm_config_set_out_pins(&c, PIN_BASE, PIN_COUNT);
    sm_config_set_in_pins(&c, PIN_BASE);
    sm_config_set_clkdiv(&c, 1.0f);

    pio_sm_init(MUX_PIO, MUX_SM, offset, &c);

    pio_set_irq0_source_enabled(MUX_PIO, pis_interrupt0, true);
    irq_set_exclusive_handler(PIO0_IRQ_0, mux_irq_handler);
    irq_set_enabled(PIO0_IRQ_0, true);
    pio_interrupt_clear(MUX_PIO, MUX_IRQ);

    pio_sm_set_enabled(MUX_PIO, MUX_SM, true);
}
