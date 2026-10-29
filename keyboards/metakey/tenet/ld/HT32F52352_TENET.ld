/*
 * Tenet 70 memory layout:
 *   0x00000 - 0x03FFF : Hexcore IAP bootloader (16KB, do not touch)
 *   0x04000 - 0x1FFFF : application firmware (112KB available)
 *   SRAM 0x20000000 - 0x20003FFF : 16KB
 */
MEMORY {
    flash0   : org = 0x00004000, len = 128k - 16k
    flash1   : org = 0x00000000, len = 0
    flash2   : org = 0x00000000, len = 0
    flash3   : org = 0x00000000, len = 0
    flash4   : org = 0x00000000, len = 0
    flash5   : org = 0x00000000, len = 0
    flash6   : org = 0x00000000, len = 0
    flash7   : org = 0x00000000, len = 0
    ram0     : org = 0x20000000, len = 16k
    ram1     : org = 0x00000000, len = 0
    ram2     : org = 0x00000000, len = 0
    ram3     : org = 0x00000000, len = 0
    ram4     : org = 0x00000000, len = 0
    ram5     : org = 0x00000000, len = 0
    ram6     : org = 0x00000000, len = 0
    ram7     : org = 0x00000000, len = 0
}

REGION_ALIAS("VECTORS_FLASH", flash0);
REGION_ALIAS("VECTORS_FLASH_LMA", flash0);
REGION_ALIAS("XTORS_FLASH", flash0);
REGION_ALIAS("XTORS_FLASH_LMA", flash0);
REGION_ALIAS("TEXT_FLASH", flash0);
REGION_ALIAS("TEXT_FLASH_LMA", flash0);
REGION_ALIAS("RODATA_FLASH", flash0);
REGION_ALIAS("RODATA_FLASH_LMA", flash0);
REGION_ALIAS("VARIOUS_FLASH", flash0);
REGION_ALIAS("VARIOUS_FLASH_LMA", flash0);
REGION_ALIAS("RAM_INIT_FLASH_LMA", flash0);
REGION_ALIAS("MAIN_STACK_RAM", ram0);
REGION_ALIAS("PROCESS_STACK_RAM", ram0);
REGION_ALIAS("DATA_RAM", ram0);
REGION_ALIAS("DATA_RAM_LMA", flash0);
REGION_ALIAS("BSS_RAM", ram0);
REGION_ALIAS("HEAP_RAM", ram0);

INCLUDE rules.ld
