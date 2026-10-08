/*
 * CH579M memory layout.
 *
 * Flash: 250 KB at 0x00000000 (code + const data)
 * RAM:    32 KB at 0x20000000 (stack + heap + bss + data)
 *
 * Note: 0x40008800–0x400089FF is the USB endpoint buffer RAM,
 * managed directly by the USB driver — not in this linker map.
 */
MEMORY
{
    flash0 (rx) : org = 0x00000000, len = 250k
    flash1 (rx) : org = 0x00000000, len = 0
    flash2 (rx) : org = 0x00000000, len = 0
    flash3 (rx) : org = 0x00000000, len = 0
    flash4 (rx) : org = 0x00000000, len = 0
    flash5 (rx) : org = 0x00000000, len = 0
    flash6 (rx) : org = 0x00000000, len = 0
    flash7 (rx) : org = 0x00000000, len = 0
    ram0   (wx) : org = 0x20000000, len = 32k
    ram1   (wx) : org = 0x00000000, len = 0
    ram2   (wx) : org = 0x00000000, len = 0
    ram3   (wx) : org = 0x00000000, len = 0
    ram4   (wx) : org = 0x00000000, len = 0
    ram5   (wx) : org = 0x00000000, len = 0
    ram6   (wx) : org = 0x00000000, len = 0
    ram7   (wx) : org = 0x00000000, len = 0
}

/* Exception vectors → flash0 */
REGION_ALIAS("VECTORS_FLASH",     flash0);
REGION_ALIAS("VECTORS_FLASH_LMA", flash0);

/* Constructors/destructors */
REGION_ALIAS("XTORS_FLASH",     flash0);
REGION_ALIAS("XTORS_FLASH_LMA", flash0);

/* Code text */
REGION_ALIAS("TEXT_FLASH",     flash0);
REGION_ALIAS("TEXT_FLASH_LMA", flash0);

/* Read-only data */
REGION_ALIAS("RODATA_FLASH",     flash0);
REGION_ALIAS("RODATA_FLASH_LMA", flash0);

/* Various (e.g. ARM.extab, ARM.exidx) */
REGION_ALIAS("VARIOUS_FLASH",     flash0);
REGION_ALIAS("VARIOUS_FLASH_LMA", flash0);

/* RAM init data load from flash */
REGION_ALIAS("RAM_INIT_FLASH_LMA", flash0);

/* Main (exception/interrupt) stack */
REGION_ALIAS("MAIN_STACK_RAM", ram0);

/* Process (main() + thread) stack */
REGION_ALIAS("PROCESS_STACK_RAM", ram0);

/* .data segment */
REGION_ALIAS("DATA_RAM",     ram0);
REGION_ALIAS("DATA_RAM_LMA", flash0);

/* .bss segment */
REGION_ALIAS("BSS_RAM", ram0);

/* Default heap */
REGION_ALIAS("HEAP_RAM", ram0);

/* ChibiOS generic ARM Cortex-M rules */
INCLUDE rules.ld
