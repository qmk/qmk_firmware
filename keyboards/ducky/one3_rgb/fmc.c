// Copyright 2026 doombadroid (@doombadroid)
// SPDX-License-Identifier: GPL-2.0-or-later
// FMC ISP users: (1) wear-leveled EEPROM (WEAR_LEVELING_DRIVER = custom) in spare APROM pages 0x30000..,
// above the QMK image (linker caps flash at 0x30000) and below everything stock owns (data flash 0x33200..0x3F7FF);
// (2) the stock APROM->LDROM request on handshake page 0x3F800 for bootloader_jump().
// Every ISP command is checked against those two targets; LDROM/CONFIG update enables (LDUEN/CFGUEN) are never set.
#include "quantum.h"
#include "wear_leveling.h"
#include "wear_leveling_internal.h"

#define EE_BASE 0x30000u
#define EE_PAGE 0x800u // NUC126 flash page
#define ISP_PROGRAM 0x21u
#define ISP_PAGE_ERASE 0x22u
#define LDROM_REQ_ADDR 0x3F800u     // stock handshake page (data flash)
#define LDROM_REQ_MAGIC 0x4E754C64u // "dLuN": stay in ISP mode (stock vendor HID cmd 0x1e @0x6350)

_Static_assert(WEAR_LEVELING_BACKING_SIZE % EE_PAGE == 0, "backing store must be whole 2K pages");
_Static_assert(BACKING_STORE_WRITE_SIZE == 4, "FMC programs 32-bit words");

static bool isp(uint32_t cmd, uint32_t addr, uint32_t data) {
    if ((addr < EE_BASE || addr >= EE_BASE + WEAR_LEVELING_BACKING_SIZE) && addr != LDROM_REQ_ADDR) return false;
    FMC->ISPCMD  = cmd;
    FMC->ISPADDR = addr;
    FMC->ISPDAT  = data;
    FMC->ISPTRG  = FMC_ISPTRG_ISPGO_Msk;
    __ISB();
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {
    }
    if (FMC->ISPCTL & FMC_ISPCTL_ISPFF_Msk) { // ISP fail flag, write 1 to clear
        FMC->ISPCTL |= FMC_ISPCTL_ISPFF_Msk;
        return false;
    }
    return true;
}

bool backing_store_init(void) {
    return true;
}

bool backing_store_unlock(void) {
    UNLOCKREG();
    FMC->ISPCTL |= FMC_ISPCTL_ISPEN_Msk | FMC_ISPCTL_APUEN_Msk;
    return true;
}

bool backing_store_lock(void) {
    FMC->ISPCTL &= ~(FMC_ISPCTL_ISPEN_Msk | FMC_ISPCTL_APUEN_Msk);
    LOCKREG();
    return true;
}

bool backing_store_erase(void) {
    bool ok = true;
    for (uint32_t a = EE_BASE; a < EE_BASE + WEAR_LEVELING_BACKING_SIZE; a += EE_PAGE) {
        if (!isp(ISP_PAGE_ERASE, a, 0)) ok = false;
    }
    return ok;
}

// Erased flash reads 0xFFFFFFFF; wear-leveling expects erased == 0, so store inverted (as the EFL driver does).
bool backing_store_write(uint32_t address, backing_store_int_t value) {
    return isp(ISP_PROGRAM, EE_BASE + address, ~value);
}

bool backing_store_read(uint32_t address, backing_store_int_t *value) {
    *value = ~*(volatile uint32_t *)(EE_BASE + address);
    return true;
}

// Stock's LDROM request, step for step: erase handshake page, write magic, clear POR/PIN reset flags,
// ISPEN off + BS=1 (boot LDROM), SYSRESETREQ. The LDROM sees the magic and stays in ISP mode.
void bootloader_jump(void) {
    __disable_irq();
    UNLOCKREG();
    FMC->ISPCTL |= FMC_ISPCTL_ISPEN_Msk;
    isp(ISP_PAGE_ERASE, LDROM_REQ_ADDR, 0);
    isp(ISP_PROGRAM, LDROM_REQ_ADDR, LDROM_REQ_MAGIC);
    SYS->RSTSTS = SYS_RSTSTS_PORF_Msk | SYS_RSTSTS_PINRF_Msk;
    FMC->ISPCTL = (FMC->ISPCTL & ~(FMC_ISPCTL_ISPEN_Msk | FMC_ISPCTL_BS_Msk)) | FMC_ISPCTL_BS_Msk;
    NVIC_SystemReset();
}

// Back in APROM with our request still on the page (LDROM didn't consume it): clear it, so a later power-up
// can't land in ISP mode with no flasher running.
void keyboard_pre_init_kb(void) {
    if (*(volatile uint32_t *)LDROM_REQ_ADDR == LDROM_REQ_MAGIC) {
        UNLOCKREG();
        FMC->ISPCTL |= FMC_ISPCTL_ISPEN_Msk;
        isp(ISP_PAGE_ERASE, LDROM_REQ_ADDR, 0);
        FMC->ISPCTL &= ~FMC_ISPCTL_ISPEN_Msk;
        LOCKREG();
    }
    keyboard_pre_init_user();
}
