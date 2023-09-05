/* Copyright 2021 Nick Brassel (@tzarc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <quantum.h>

#ifndef USBPD_UCPD1_CFG1
#    define USBPD_UCPD1_CFG1 (UCPD_CFG1_PSC_UCPDCLK_0 | UCPD_CFG1_TRANSWIN_3 | UCPD_CFG1_IFRGAP_4 | UCPD_CFG1_HBITCLKDIV_4)
#endif // USBPD_UCPD1_CFG1

// Initialises the USBPD subsystem
__attribute__((weak)) void usbpd_init(void) {
    // Enable the clock for the UCPD1 peripheral
    RCC->APB1ENR2 |= RCC_APB1ENR2_UCPD1EN;

    // Copy the existing value
    uint32_t CFG1 = UCPD1->CFG1;
    // Force-disable UCPD1 before configuring
    CFG1 &= ~UCPD_CFG1_UCPDEN;
    // Configure UCPD1
    CFG1 = USBPD_UCPD1_CFG1;
    // Apply the changes
    UCPD1->CFG1 = CFG1;
    // Enable UCPD1
    UCPD1->CFG1 |= UCPD_CFG1_UCPDEN;

    // Copy the existing value
    uint32_t CR = UCPD1->CR;
    // Clear out ANASUBMODE (irrelevant as a sink device)
    CR &= ~UCPD_CR_ANASUBMODE_Msk;
    // Advertise our capabilities as a sink, with both CC lines enabled
    CR |= UCPD_CR_ANAMODE | UCPD_CR_CCENABLE_Msk;
    // Apply the changes
    UCPD1->CR = CR;

    // Disable dead-battery signals only after UCPD1 is configured to ensure
    // that the transition does not go through any intermediate state without
    // any pull-down resistance.
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;
}

// Gets the current state of the USBPD allowance
__attribute__((weak)) usbpd_allowance_t usbpd_get_allowance(void) {
    uint32_t CR = UCPD1->CR;

    int ucpd_enabled = (UCPD1->CFG1 & UCPD_CFG1_UCPDEN_Msk) >> UCPD_CFG1_UCPDEN_Pos;
    int anamode      = (CR & UCPD_CR_ANAMODE_Msk) >> UCPD_CR_ANAMODE_Pos;
    int cc_enabled   = (CR & UCPD_CR_CCENABLE_Msk) >> UCPD_CR_CCENABLE_Pos;

    if (ucpd_enabled && anamode && cc_enabled) {
        uint32_t SR         = UCPD1->SR;
        int      vstate_cc1 = (SR & UCPD_SR_TYPEC_VSTATE_CC1_Msk) >> UCPD_SR_TYPEC_VSTATE_CC1_Pos;
        int      vstate_cc2 = (SR & UCPD_SR_TYPEC_VSTATE_CC2_Msk) >> UCPD_SR_TYPEC_VSTATE_CC2_Pos;
        int      vstate_max = vstate_cc1 > vstate_cc2 ? vstate_cc1 : vstate_cc2;
        switch (vstate_max) {
            case 0:
            case 1:
                return USBPD_500MA; // Note that this is 500mA (i.e. max USB 2.0), not 900mA, as we're not using USB 3.1 as a sink device.
            case 2:
                return USBPD_1500MA;
            case 3:
                return USBPD_3000MA;
        }
    }

    return USBPD_500MA;
}