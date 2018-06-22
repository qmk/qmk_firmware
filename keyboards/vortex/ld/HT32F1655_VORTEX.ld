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
 * HT32F1655 w/ cykb bootloader memory setup.
 */
MEMORY {
    flash0   : org = 0x00000000, len = 0x2800           /* bootloader */
    flash1   : org = 0x00002800, len = 0x400            /* version page */
    flash2   : org = 0x00002c00, len = 0x160            /* firmware vectors */
    flash3   : org = 0x00002d60, len = 0x80             /* firmware identifier */
    flash4   : org = 0x00002de0, len = 128k - 0x2de0    /* text, rodata, data */
    flash5   : org = 0x00000000, len = 0
    flash6   : org = 0x00000000, len = 0
    flash7   : org = 0x00000000, len = 0
    ram0     : org = 0x20000000, len = 32k - 4          /* RAM */
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
}

/* For each data/text section two region are defined, a virtual region
   and a load region (_LMA suffix).*/

/* Flash region to be used for exception vectors.*/
REGION_ALIAS("VECTORS_FLASH", flash2);
REGION_ALIAS("VECTORS_FLASH_LMA", flash2);

/* Flash region to be used for constructors and destructors.*/
REGION_ALIAS("XTORS_FLASH", flash4);
REGION_ALIAS("XTORS_FLASH_LMA", flash4);

/* Flash region to be used for code text.*/
REGION_ALIAS("TEXT_FLASH", flash4);
REGION_ALIAS("TEXT_FLASH_LMA", flash4);

/* Flash region to be used for read only data.*/
REGION_ALIAS("RODATA_FLASH", flash4);
REGION_ALIAS("RODATA_FLASH_LMA", flash4);

/* Flash region to be used for various.*/
REGION_ALIAS("VARIOUS_FLASH", flash4);
REGION_ALIAS("VARIOUS_FLASH_LMA", flash4);

/* Flash region to be used for RAM(n) initialization data.*/
REGION_ALIAS("RAM_INIT_FLASH_LMA", flash4);

/* RAM region to be used for Main stack. This stack accommodates the processing
   of all exceptions and interrupts.*/
REGION_ALIAS("MAIN_STACK_RAM", ram0);

/* RAM region to be used for the process stack. This is the stack used by
   the main() function.*/
REGION_ALIAS("PROCESS_STACK_RAM", ram0);

/* RAM region to be used for data segment.*/
REGION_ALIAS("DATA_RAM", ram0);
REGION_ALIAS("DATA_RAM_LMA", flash4);

/* RAM region to be used for BSS segment.*/
REGION_ALIAS("BSS_RAM", ram0);

/* RAM region to be used for the default heap.*/
REGION_ALIAS("HEAP_RAM", ram0);

/* Generic rules inclusion.*/
INCLUDE rules.ld
