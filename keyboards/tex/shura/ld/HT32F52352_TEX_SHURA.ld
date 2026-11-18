/*
 * Adapted from Mauro DiBenedetto's GPL-2.0-or-later TEX Shinobi port,
 * itself adapted from HT32F52352_ANNEPRO2_C18.ld (MIT):
 * Copyright (c) 2013-2016 Fabio Utzig, (c) 2020 Yaotian Feng,
 * (c) 2025 Michal Kopec. Upstream licenses are retained with this port.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * The TEX bootloader occupies flash below 0x3000 and its version block 0x3000-0x31FF;
 * the application starts at 0x3200. The bootloader's updater checks a 12-byte record
 * at 0x3BF8 (as in the stock firmware) and erases up to 0x1FE00; the image ends at
 * 0x1FC00. SRAM 0x20003FE0-0x20003FFF is the bootloader handoff area.
 */
__vectors_align__ = 256;
MEMORY {
    flash0 : org = 0x00003200, len = 0x3800 - 0x3200
    flash0b : org = 0x00003800, len = 0x3BF8 - 0x3800
    flash1 : org = 0x00003BF8, len = 12
    flash2 : org = 0x00003C04, len = 0x1FC00 - 0x3C04
    flash3 : org = 0, len = 0
    flash4 : org = 0, len = 0
    flash5 : org = 0, len = 0
    flash6 : org = 0, len = 0
    flash7 : org = 0, len = 0
    ram0 : org = 0x20000000, len = 0x3FE0
    ram1 : org = 0, len = 0
    ram2 : org = 0, len = 0
    ram3 : org = 0, len = 0
    ram4 : org = 0, len = 0
    ram5 : org = 0, len = 0
    ram6 : org = 0, len = 0
    ram7 : org = 0, len = 0
}
REGION_ALIAS("VECTORS_FLASH", flash0);
REGION_ALIAS("VECTORS_FLASH_LMA", flash0);
REGION_ALIAS("XTORS_FLASH", flash0);
REGION_ALIAS("XTORS_FLASH_LMA", flash0);
REGION_ALIAS("TEXT_FLASH", flash2);
REGION_ALIAS("TEXT_FLASH_LMA", flash2);
REGION_ALIAS("RODATA_FLASH", flash2);
REGION_ALIAS("RODATA_FLASH_LMA", flash2);
REGION_ALIAS("VARIOUS_FLASH", flash0);
REGION_ALIAS("VARIOUS_FLASH_LMA", flash0);
REGION_ALIAS("RAM_INIT_FLASH_LMA", flash0);
REGION_ALIAS("MAIN_STACK_RAM", ram0);
REGION_ALIAS("PROCESS_STACK_RAM", ram0);
REGION_ALIAS("DATA_RAM", ram0);
REGION_ALIAS("DATA_RAM_LMA", flash0);
REGION_ALIAS("BSS_RAM", ram0);
REGION_ALIAS("HEAP_RAM", ram0);
SECTIONS {
    .tex_keymaps : ALIGN(4) {
        *(.rodata.keymaps)
    } > flash0b
    .tex_app_record : {
        LONG(0x040451C0) LONG(0x34000001) LONG(0x00020004)
    } > flash1
}
INCLUDE rules.ld
SECTIONS {
    .tex_rodata0 : {
        *(.tex_rodata0)
    } > flash0
}
ASSERT((__main_stack_end__ & 7) == 0, "Main stack must be 8-byte aligned")
ASSERT((__process_stack_end__ & 7) == 0, "Process stack must be 8-byte aligned")
