// Copyright 2024 Shanghai Eastsoft Microelectronics Co., Ltd
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "board.h"

/*rows[0] = B0*/
#define IN_PORT GPIOB
#define IN_PIN MD_GPIO_PIN_0

/*cols[0] = D6*/
#define OUT_PORT GPIOD
#define OUT_PIN MD_GPIO_PIN_6

void enter_bootloader_mode_if_requested(void) {
    volatile uint32_t   i;
    md_gpio_inittypedef gpiox;

    /*init GPIO*/
    gpiox.Pin        = IN_PIN;
    gpiox.Mode       = MD_GPIO_MODE_INPUT;
    gpiox.OutputType = MD_GPIO_OUTPUT_PUSHPULL;
    gpiox.Pull       = MD_GPIO_PULL_FLOATING;
    gpiox.OutDrive   = MD_GPIO_DRIVING_8MA;
    gpiox.Function   = MD_GPIO_AF0;
    md_gpio_init(IN_PORT, &gpiox);

    gpiox.Pin  = OUT_PIN;
    gpiox.Mode = MD_GPIO_MODE_OUTPUT;
    gpiox.Pull = MD_GPIO_PULL_UP;
    md_gpio_init(OUT_PORT, &gpiox);

    /*if rows[0] connect cols[0],jump to boot*/
    md_gpio_set_pin_high(OUT_PORT, OUT_PIN);

    for (i = 0; i < 999;) {
        i++;
    }

    if (md_gpio_get_inputpinset(IN_PORT, IN_PIN)) {
        md_gpio_set_pin_low(OUT_PORT, OUT_PIN);

        for (i = 0; i < 999;) {
            i++;
        }

        if (md_gpio_get_inputpinset(IN_PORT, IN_PIN) == 0) {
            /*Remap EFLASH,remap to boot*/
            md_fc_lock();
            md_syscfg_set_memory_mapping(SYSCFG, MD_SYSCFG_MEMMOD_MAIN);
            md_syscfg_set_flash_remap_base(SYSCFG, 0);
            md_syscfg_enable_memory_remap(SYSCFG);

            NVIC_SystemReset();
        }
    }
}

void board_init(void) {
    /*Using USB_SOF to calibrate the internal clock*/
    md_rcu_enable_csu(RCU);
    CSU->CON |= CSU_CON_AUTOEN_MSK;
    CSU->CON |= CSU_CON_CNTEN_MSK;
}
