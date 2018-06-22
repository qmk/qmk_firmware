/*
 * Copyright (c) 2013-2016 Fabio UJonathan A. Kollaschtzig, http://fabioutzig.com
 *           (c) 2016 flabbergast <s3+flabbergast@sdfeu.org>
 *           (c) 2018 Jonathan A. Kollasch
 *           (c) 2018 Charlie Waters
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

/*
 * HT32F1654 w/ cykb bootloader memory setup.
 */
MEMORY {
    flash0   : org = 0x00000000, len = 0x3000           /* bootloader */
    flash1   : org = 0x00003000, len = 0x400            /* version page */
    flash2   : org = 0x00003400, len = 0x160            /* firmware vectors */
    flash3   : org = 0x00003560, len = 0x80             /* firmware identifier */
    flash4   : org = 0x000035e0, len = 0x3bf8 - 0x35e0  /* descriptor, keymaps, etc */
    flash5   : org = 0x00003bf8, len = 12               /* bootloader magic */
    flash6   : org = 0x00003c04, len = 63k - 0x3c04     /* firmware */
    flash7   : org = 0x00000000, len = 0
    ram0     : org = 0x20000000, len = 16k - 4          /* RAM */
    ram1     : org = 0x00000000, len = 0
    ram2     : org = 0x00000000, len = 0
    ram3     : org = 0x00000000, len = 0
    ram4     : org = 0x00000000, len = 0
    ram5     : org = 0x00000000, len = 0
    ram6     : org = 0x00000000, len = 0
    ram7     : org = 0x00000000, len = 0
}

SECTIONS {
    .rodata.firmwareid : {
        KEEP(*(.id.firmware))
    } > flash3 AT > flash3

    .rodata.flash4 : {
        *(.rodata.*Descriptor)
        *(.rodata.*Report)
        *(.rodata.*String)
        *(.rodata.keymaps)
        *(.rodata.pal_default_config)
        *(.rodata.ch_debug)
    } > flash4 AT > flash4

    .rodata.bootloadermagic : {
        KEEP(*(.magic.bootloader))
    } > flash5 AT > flash5
}

/* For each data/text section two region are defined, a virtual region
   and a load region (_LMA suffix).*/

/* Flash region to be used for exception vectors.*/
REGION_ALIAS("VECTORS_FLASH", flash2);
REGION_ALIAS("VECTORS_FLASH_LMA", flash2);

/* Flash region to be used for constructors and destructors.*/
REGION_ALIAS("XTORS_FLASH", flash6);
REGION_ALIAS("XTORS_FLASH_LMA", flash6);

/* Flash region to be used for code text.*/
REGION_ALIAS("TEXT_FLASH", flash6);
REGION_ALIAS("TEXT_FLASH_LMA", flash6);

/* Flash region to be used for read only data.*/
REGION_ALIAS("RODATA_FLASH", flash6);
REGION_ALIAS("RODATA_FLASH_LMA", flash6);

/* Flash region to be used for various.*/
REGION_ALIAS("VARIOUS_FLASH", flash6);
REGION_ALIAS("VARIOUS_FLASH_LMA", flash6);

/* Flash region to be used for RAM(n) initialization data.*/
REGION_ALIAS("RAM_INIT_FLASH_LMA", flash6);

/* RAM region to be used for Main stack. This stack accommodates the processing
   of all exceptions and interrupts.*/
REGION_ALIAS("MAIN_STACK_RAM", ram0);

/* RAM region to be used for the process stack. This is the stack used by
   the main() function.*/
REGION_ALIAS("PROCESS_STACK_RAM", ram0);

/* RAM region to be used for data segment.*/
REGION_ALIAS("DATA_RAM", ram0);
REGION_ALIAS("DATA_RAM_LMA", flash6);

/* RAM region to be used for BSS segment.*/
REGION_ALIAS("BSS_RAM", ram0);

/* RAM region to be used for the default heap.*/
REGION_ALIAS("HEAP_RAM", ram0);

/* Generic rules inclusion.*/
INCLUDE rules.ld
