// SPDX-License-Identifier: GPL-2.0-or-later

#include "wwdg.h"
void WWDG_Init(void) {
    RCC->APB2ENR |= 0x00000802;
    WWDG->CR = 0x7F;
    WWDG->CR = 0x7F;
}

void WWDG_Deinit(void) {
    RCC->APB2RSTR |= 0x00000002;
    RCC->APB2RSTR &= ~0x00000002;
}

void WWDG_SetPrescaler(uint32_t WWDG_Prescaler) {
    uint32_t tmpreg = 0;
    /* Clear WDGTB[1:0] bits */
    tmpreg = WWDG->CFR & CFR_WDGTB_Mask;
    /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
    tmpreg |= WWDG_Prescaler;
    /* Store the new value */
    WWDG->CFR = tmpreg;
}

void WWDG_SetWindowValue(uint8_t WindowValue) {
    volatile uint32_t tmpreg = 0;

    tmpreg = WWDG->CFR & CFR_W_Mask;

    /* Set W[6:0] bits according to WindowValue value */
    tmpreg |= WindowValue & (uint32_t)BIT_Mask;

    /* Store the new value */
    WWDG->CFR = tmpreg;
}

void WWDG_Enable(uint8_t Counter) {
    WWDG->CR = CR_WDGA_Set | Counter;
}

void WWDG_SetCounter(uint8_t Counter) {
    WWDG->CR = Counter & BIT_Mask;
}

void Init_WWDG(void) {
    WWDG_Init();
    WWDG_Deinit();
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    WWDG_SetWindowValue(127);
}

void Disable_WWDG(void) {
    WWDG_Deinit();
    RCC->APB2ENR &= ~0x00000802;
}
