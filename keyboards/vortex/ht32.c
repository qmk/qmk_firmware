#include "vortex.h"

void firmware_reset(uint32_t key) {
    wait_us(10000); // 10 ms
    chSysDisable(); // mask all interrupts
    usbDisconnectBus(&USB_DRIVER); // disconnect usb
    // SBVT registers are not reset on reset
    // SBVT1 is read by pok3r bootloader to stop in bootloader
    FMC->SBVT[1] = key;
    wait_us(50000); // 50 ms
    NVIC_SystemReset();
}

void flash_erase_page(uint32_t addr){
    FMC->TADR = addr;
    FMC->OCMR = FMC_OCMR_CMD_PAGE_ERASE;
    FMC->OPCR = FMC_OPCR_OPM_COMMIT;
    while((FMC->OPCR & FMC_OPCR_OPM_MASK) != FMC_OPCR_OPM_FINISHED);
}

void flash_write_word(uint32_t addr, uint32_t word){
    FMC->TADR = addr;
    FMC->WRDR = word;
    FMC->OCMR = FMC_OCMR_CMD_WORD_PROGRAM;
    FMC->OPCR = FMC_OPCR_OPM_COMMIT;
    while((FMC->OPCR & FMC_OPCR_OPM_MASK) != FMC_OPCR_OPM_FINISHED);
}
