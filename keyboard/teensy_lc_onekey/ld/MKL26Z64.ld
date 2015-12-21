/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * KL26Z64 memory setup.
 */
MEMORY
{
  flash0   :  org = 0x00000000,  len = 0xc0
  flashcfg :  org = 0x00000400,  len = 0x10
  flash    :  org = 0x00000410,  len = 62k - 0x410
  eeprom_emu : org = 0x0000F800, len = 2k
  ram0     :  org = 0x1FFFF800,  len = 8k
  ram1     :  org = 0x00000000,  len = 0
  ram2     :  org = 0x00000000,  len = 0
  ram3     :  org = 0x00000000,  len = 0
  ram4     :  org = 0x00000000,  len = 0
  ram5     :  org = 0x00000000,  len = 0
  ram6     :  org = 0x00000000,  len = 0
  ram7     :  org = 0x00000000,  len = 0
}

__eeprom_workarea_start__ = ORIGIN(eeprom_emu);
__eeprom_workarea_size__  = LENGTH(eeprom_emu);
__eeprom_workarea_end__   = __eeprom_workarea_start__ + __eeprom_workarea_size__;

/* RAM region to be used for Main stack. This stack accommodates the processing
   of all exceptions and interrupts*/
REGION_ALIAS("MAIN_STACK_RAM", ram0);

/* RAM region to be used for the process stack. This is the stack used by
   the main() function.*/
REGION_ALIAS("PROCESS_STACK_RAM", ram0);

/* RAM region to be used for data segment.*/
REGION_ALIAS("DATA_RAM", ram0);

/* RAM region to be used for BSS segment.*/
REGION_ALIAS("BSS_RAM", ram0);

/* RAM region to be used for the default heap.*/
REGION_ALIAS("HEAP_RAM", ram0);

INCLUDE ld/rules_kinetis.ld
