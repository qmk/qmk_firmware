/*
 * Copyright (c) 2013-2016 Fabio UJonathan A. Kollaschtzig, http://fabioutzig.com
 *           (c) 2020 Yaotian Feng (Codetector) <codetector@codetector.cn>
 *           (c) 2025 Michał Kopeć <michal@nozomi.space>
 *           (c) 2026 BHE
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* HT32F52352 with the Anne Pro 2D 16 KiB bootloader region. */
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
