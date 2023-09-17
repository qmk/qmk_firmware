// Copyright 2022 Marek Kraus (@gamelaster)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ps2.h"
#include "debug.h"

#if !defined(MCU_RP)
#    error PIO Driver is only available for Raspberry Pi 2040 MCUs!
#endif

#if defined(PS2_ENABLE)
#    if defined(PS2_MOUSE_ENABLE)
#        if !defined(PS2_MOUSE_USE_REMOTE_MODE)
#            define BUFFERED_MODE_ENABLE
#        endif
#    else // PS2 Keyboard
#        define BUFFERED_MODE_ENABLE
#    endif
#endif

#if PS2_DATA_PIN + 1 != PS2_CLOCK_PIN
#    error PS/2 Clock pin must be followed by data pin!
#endif

static inline void pio_serve_interrupt(void);

#if defined(PS2_PIO_USE_PIO1)
static const PIO pio = pio1;

OSAL_IRQ_HANDLER(RP_PIO1_IRQ_0_HANDLER) {
    OSAL_IRQ_PROLOGUE();
    pio_serve_interrupt();
    OSAL_IRQ_EPILOGUE();
}
#else
static const PIO pio = pio0;

OSAL_IRQ_HANDLER(RP_PIO0_IRQ_0_HANDLER) {
    OSAL_IRQ_PROLOGUE();
    pio_serve_interrupt();
    OSAL_IRQ_EPILOGUE();
}
#endif

#define PS2_WRAP_TARGET 0
#define PS2_WRAP 20

// clang-format off
static const uint16_t ps2_program_instructions[] = {
            //     .wrap_target
    0x00c7, //  0: jmp    pin, 7
    0xe02a, //  1: set    x, 10
    0x2021, //  2: wait   0 pin, 1
    0x4001, //  3: in     pins, 1
    0x20a1, //  4: wait   1 pin, 1
    0x0042, //  5: jmp    x--, 2
    0x0000, //  6: jmp    0
    0x00e9, //  7: jmp    !osre, 9
    0x0000, //  8: jmp    0
    0xff81, //  9: set    pindirs, 1             [31]
    0xe280, // 10: set    pindirs, 0             [2]
    0xe082, // 11: set    pindirs, 2
    0x2021, // 12: wait   0 pin, 1
    0xe029, // 13: set    x, 9
    0x6081, // 14: out    pindirs, 1
    0x20a1, // 15: wait   1 pin, 1
    0x2021, // 16: wait   0 pin, 1
    0x004e, // 17: jmp    x--, 14
    0xe083, // 18: set    pindirs, 3
    0x2021, // 19: wait   0 pin, 1
    0x20a1, // 20: wait   1 pin, 1
            //     .wrap
};
// clang-format on

static const struct pio_program ps2_program = {
    .instructions = ps2_program_instructions,
    .length       = 21,
    .origin       = -1,
};

static int                state_machine = -1;
static thread_reference_t tx_thread     = NULL;

#define BUFFER_SIZE 32
static input_buffers_queue_t               pio_rx_queue;
static __attribute__((aligned(4))) uint8_t pio_rx_buffer[BQ_BUFFER_SIZE(BUFFER_SIZE, sizeof(uint32_t))];

uint8_t ps2_error = PS2_ERR_NONE;

void pio_serve_interrupt(void) {
    uint32_t irqs = pio->ints0;

    if (irqs & (PIO_IRQ0_INTF_SM0_RXNEMPTY_BITS << state_machine)) {
        osalSysLockFromISR();
        uint32_t* frame_buffer = (uint32_t*)ibqGetEmptyBufferI(&pio_rx_queue);
        if (frame_buffer == NULL) {
            osalSysUnlockFromISR();
            return;
        }
        *frame_buffer = pio_sm_get(pio, state_machine);
        ibqPostFullBufferI(&pio_rx_queue, sizeof(uint32_t));
        osalSysUnlockFromISR();
    }

    if (irqs & (PIO_IRQ0_INTF_SM0_TXNFULL_BITS << state_machine)) {
        pio_set_irq0_source_enabled(pio, pis_sm0_tx_fifo_not_full + state_machine, false);
        osalSysLockFromISR();
        osalThreadResumeI(&tx_thread, MSG_OK);
        osalSysUnlockFromISR();
    }
}

void ps2_host_init(void) {
    ibqObjectInit(&pio_rx_queue, false, pio_rx_buffer, sizeof(uint32_t), BUFFER_SIZE, NULL, NULL);
    uint pio_idx = pio_get_index(pio);

    hal_lld_peripheral_unreset(pio_idx == 0 ? RESETS_ALLREG_PIO0 : RESETS_ALLREG_PIO1);

    state_machine = pio_claim_unused_sm(pio, true);
    if (state_machine < 0) {
        dprintln("ERROR: Failed to acquire state machine for PS/2!");
        ps2_error = PS2_ERR_NODATA;
        return;
    }

    uint offset = pio_add_program(pio, &ps2_program);

    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + PS2_WRAP_TARGET, offset + PS2_WRAP);

    // Set pindirs to input (output enable is inverted below)
    pio_sm_set_consecutive_pindirs(pio, state_machine, PS2_DATA_PIN, 2, true);
    sm_config_set_clkdiv(&c, (float)clock_get_hz(clk_sys) / (200.0f * KHZ));
    sm_config_set_set_pins(&c, PS2_DATA_PIN, 2);
    sm_config_set_out_pins(&c, PS2_DATA_PIN, 1);
    sm_config_set_out_shift(&c, true, true, 10);
    sm_config_set_in_shift(&c, true, true, 11);
    sm_config_set_jmp_pin(&c, PS2_CLOCK_PIN);
    sm_config_set_in_pins(&c, PS2_DATA_PIN);

    // clang-format off
    iomode_t pin_mode = PAL_RP_PAD_IE |
                        PAL_RP_GPIO_OE |
                        PAL_RP_PAD_SLEWFAST |
                        PAL_RP_PAD_DRIVE12 |
                        // Invert output enable so that pindirs=1 means input
                        // and indirs=0 means output. This way, out pindirs
                        // works correctly with the open-drain PS/2 interface.
                        // Setting pindirs=1 effectively pulls the line high,
                        // due to the pull-up resistor, while pindirs=0 pulls
                        // the line low.
                        PAL_RP_IOCTRL_OEOVER_DRVINVPERI |
                        (pio_idx == 0 ? PAL_MODE_ALTERNATE_PIO0 : PAL_MODE_ALTERNATE_PIO1);
    // clang-format on

    palSetLineMode(PS2_DATA_PIN, pin_mode);
    palSetLineMode(PS2_CLOCK_PIN, pin_mode);

    pio_set_irq0_source_enabled(pio, pis_sm0_rx_fifo_not_empty + state_machine, true);
    pio_sm_init(pio, state_machine, offset, &c);

#if defined(PS2_PIO_USE_PIO1)
    nvicEnableVector(RP_PIO1_IRQ_0_NUMBER, CORTEX_MAX_KERNEL_PRIORITY);
#else
    nvicEnableVector(RP_PIO0_IRQ_0_NUMBER, CORTEX_MAX_KERNEL_PRIORITY);
#endif

    pio_sm_set_enabled(pio, state_machine, true);
}

static int bit_parity(int x) {
    return !__builtin_parity(x);
}

uint8_t ps2_host_send(uint8_t data) {
    uint32_t frame = 0b1000000000;
    frame          = frame | data;

    if (bit_parity(data)) {
        frame = frame | (1 << 8);
    }

    pio_sm_put(pio, state_machine, frame);

    msg_t msg = MSG_OK;
    osalSysLock();
    while (pio_sm_is_tx_fifo_full(pio, state_machine)) {
        pio_set_irq0_source_enabled(pio, pis_sm0_tx_fifo_not_full + state_machine, true);
        msg = osalThreadSuspendTimeoutS(&tx_thread, TIME_MS2I(100));
        if (msg < MSG_OK) {
            pio_set_irq0_source_enabled(pio, pis_sm0_tx_fifo_not_full + state_machine, false);
            ps2_error = PS2_ERR_NODATA;
            osalSysUnlock();
            return 0;
        }
    }
    osalSysUnlock();

    return ps2_host_recv_response();
}

static uint8_t ps2_get_data_from_frame(uint32_t frame) {
    uint8_t  data       = (frame >> 22) & 0xFF;
    uint32_t start_bit  = (frame & 0b00000000001000000000000000000000) ? 1 : 0;
    uint32_t parity_bit = (frame & 0b01000000000000000000000000000000) ? 1 : 0;
    uint32_t stop_bit   = (frame & 0b10000000001000000000000000000000) ? 1 : 0;

    if (start_bit != 0) {
        ps2_error = PS2_ERR_STARTBIT1;
        return 0;
    }

    if (parity_bit != bit_parity(data)) {
        ps2_error = PS2_ERR_PARITY;
        return 0;
    }

    if (stop_bit != 1) {
        ps2_error = PS2_ERR_STARTBIT2;
        return 0;
    }

    return data;
}

uint8_t ps2_host_recv_response(void) {
    uint32_t frame = 0;
    msg_t    msg   = MSG_OK;

    msg = ibqReadTimeout(&pio_rx_queue, (uint8_t*)&frame, sizeof(uint32_t), TIME_MS2I(100));
    if (msg < MSG_OK) {
        ps2_error = PS2_ERR_NODATA;
        return 0;
    }

    return ps2_get_data_from_frame(frame);
}

#ifdef BUFFERED_MODE_ENABLE

bool pbuf_has_data(void) {
    osalSysLock();
    bool has_data = !ibqIsEmptyI(&pio_rx_queue);
    osalSysUnlock();
    return has_data;
}

uint8_t ps2_host_recv(void) {
    uint32_t frame = 0;
    msg_t    msg   = MSG_OK;

    uint8_t has_data = pbuf_has_data();
    if (has_data) {
        msg = ibqReadTimeout(&pio_rx_queue, (uint8_t*)&frame, sizeof(uint32_t), TIME_MS2I(100));
        if (msg < MSG_OK) {
            ps2_error = PS2_ERR_NODATA;
            return 0;
        }
    } else {
        ps2_error = PS2_ERR_NODATA;
    }

    return frame != 0 ? ps2_get_data_from_frame(frame) : 0;
}

#endif
