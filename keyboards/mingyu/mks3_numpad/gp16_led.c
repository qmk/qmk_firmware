/* 板载 GP16 单颗 WS2812 驱动（RP2040 PIO1，独立于 RGB Matrix 使用的 PIO0）
 *
 * QMK 的 RGB Matrix 灯带驱动只占用一个 PIO 实例（默认 PIO0 + WS2812_DI_PIN=GP14），
 * 板载那颗灯在 GP16，所以这里复制一份同样的 PIO 时序程序，挂在 PIO1 上单独跑。
 * 由 mks3_numpad.c 在 housekeeping 里刷新颜色，休眠时发送全黑并锁存。
 */

#include "hardware/timer.h"
#include "hardware/clocks.h"
#include <hal.h>
#include "hardware/pio.h"

#include "gpio.h"
#include "debug.h"
#include "wait.h"

#include "config.h"
#include "gp16_led.h"

/* WS2812 时序（ns），与 QMK 默认值一致：T0H=350 T0L=800 T1H=800 T1L=350 */
/* 下面 6 条 PIO 指令里的延时已按 20MHz（50ns/周期）预先算好，不需要再改 */
static const uint16_t gp16_program_instructions[] = {
    /* out x, 1            side 0 */ (3U << 8) | 0x6021, /* T1L 150ns */
    /* nop                side 0 */ (2U << 8) | 0xa042, /* T1L 100ns */
    /* jmp !x, 5           side 1 */ (6U << 8) | 0x1025, /* T0H 350ns */
    /* nop                side 1 */ (4U << 8) | 0xb042, /* T1H 200ns */
    /* jmp 0              side 1 */ (3U << 8) | 0x1000, /* T1H 150ns */
    /* nop                side 0 */ (8U << 8) | 0xa042, /* T0L 450ns */
};

static const pio_program_t gp16_program = {
    .instructions = gp16_program_instructions,
    .length       = 6,
    .origin       = -1,
};

static const PIO pio        = pio1;
static int       gp16_sm    = -1;
static bool      gp16_ready = false;

void gp16_led_init(void) {
    /* 把 PIO1 从复位里放出来 */
    hal_lld_peripheral_unreset(RESETS_ALLREG_PIO1);

    iomode_t pin_mode = PAL_RP_PAD_SLEWFAST | PAL_RP_GPIO_OE | PAL_MODE_ALTERNATE_PIO1;
    palSetLineMode(GP16_LED_PIN, pin_mode);

    gp16_sm = pio_claim_unused_sm(pio, false);
    if (gp16_sm < 0) {
        dprintln("GP16: 没有可用的 PIO state machine");
        return;
    }

    uint offset = pio_add_program(pio, &gp16_program);
    pio_sm_set_consecutive_pindirs(pio, gp16_sm, GP16_LED_PIN, 1, true);

    pio_sm_config config = pio_get_default_sm_config();
    sm_config_set_wrap(&config, offset + 0, offset + 5);
    sm_config_set_sideset_pins(&config, GP16_LED_PIN);
    sm_config_set_fifo_join(&config, PIO_FIFO_JOIN_TX);
    sm_config_set_sideset(&config, 1, false, false);
    sm_config_set_out_shift(&config, false, true, 24);

    /* 20MHz 的 state machine 时钟 => 每条指令 50ns */
    float div = clock_get_hz(clk_sys) / (20.0f * MHZ);
    sm_config_set_clkdiv(&config, div);

    pio_sm_init(pio, gp16_sm, offset, &config);
    pio_sm_set_enabled(pio, gp16_sm, true);

    gp16_ready = true;
    gp16_led_set(0, 0, 0);
}

void gp16_led_set(uint8_t r, uint8_t g, uint8_t b) {
    if (!gp16_ready) {
        return;
    }

    /* WS2812 是 GRB 顺序，PIO 从最高位开始逐位发出 */
    uint32_t grb = ((uint32_t)g << 24) | ((uint32_t)r << 16) | ((uint32_t)b << 8);

    pio_sm_put_blocking(pio, gp16_sm, grb);
    while (!pio_sm_is_tx_fifo_empty(pio, gp16_sm)) {
        wait_us(1);
    }
    /* 24 bit 发完约 30us，再补一段低电平做复位锁存 */
    wait_us(60);
}
