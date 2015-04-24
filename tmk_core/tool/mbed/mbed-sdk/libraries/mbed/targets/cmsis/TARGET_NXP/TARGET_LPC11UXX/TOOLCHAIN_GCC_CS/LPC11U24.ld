/* Linker script for mbed LPC1768
 *
 * Version:CodeSourcery Sourcery G++ Lite 2007q3-53
 * BugURL:https://support.codesourcery.com/GNUToolchain/
 *
 *  Copyright 2007 CodeSourcery.
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply. */

OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
ENTRY(__cs3_reset_cortex_m)
SEARCH_DIR(.)

/*
ram ORIGIN: 8_byte_aligned(48 vect * 4 bytes) =  8_byte_aligned(0xC0) = 0xC0
ram LENGTH: 8KB - 0xC0 = 0xF40
*/
MEMORY
{
  rom (rx)  : ORIGIN = 0x00000000, LENGTH = 32K
  
  ram (rwx) : ORIGIN = 0x100000C0, LENGTH = 0x1F40
  usb_ram (rwx) : ORIGIN = 0x20004000, LENGTH = 0x800
}

/* These force the linker to search for particular symbols from
 * the start of the link process and thus ensure the user's
 * overrides are picked up
 */
EXTERN(__cs3_reset_cortex_m)
EXTERN(__cs3_interrupt_vector_cortex_m)
EXTERN(__cs3_start_c main __cs3_stack __cs3_stack_size __cs3_heap_end)

PROVIDE(__cs3_stack = __cs3_region_start_ram + __cs3_region_size_ram);
PROVIDE(__cs3_stack_size = __cs3_region_start_ram + __cs3_region_size_ram - _end);
PROVIDE(__cs3_heap_start = _end);
PROVIDE(__cs3_heap_end = __cs3_region_start_ram + __cs3_region_size_ram);

SECTIONS
{
  .text :
  {
    CREATE_OBJECT_SYMBOLS
    __cs3_region_start_rom = .;
    *(.cs3.region-head.rom)
    __cs3_interrupt_vector = __cs3_interrupt_vector_cortex_m;
    *(.cs3.interrupt_vector)
    /* Make sure we pulled in an interrupt vector.  */
    ASSERT (. != __cs3_interrupt_vector_cortex_m, "No interrupt vector");
    *(.rom)
    *(.rom.b)

    __cs3_reset = __cs3_reset_cortex_m;
    *(.cs3.reset)
    /* Make sure we pulled in some reset code.  */
    ASSERT (. != __cs3_reset, "No reset code");

    *(.text .text.* .gnu.linkonce.t.*)
    *(.plt)
    *(.gnu.warning)
    *(.glue_7t) *(.glue_7) *(.vfp11_veneer)

    *(.rodata .rodata.* .gnu.linkonce.r.*)

    *(.ARM.extab* .gnu.linkonce.armextab.*)
    *(.gcc_except_table)
    *(.eh_frame_hdr)
    *(.eh_frame)

    . = ALIGN(4);
    KEEP(*(.init))

    . = ALIGN(4);
    __preinit_array_start = .;
    KEEP (*(.preinit_array))
    __preinit_array_end = .;

    . = ALIGN(4);
    __init_array_start = .;
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    __init_array_end = .;

    . = ALIGN(0x4);
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend.o(.ctors))

    . = ALIGN(4);
    KEEP(*(.fini))

    . = ALIGN(4);
    __fini_array_start = .;
    KEEP (*(.fini_array))
    KEEP (*(SORT(.fini_array.*)))
    __fini_array_end = .;

    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*crtend.o(.dtors))

    . = ALIGN(4);
    __cs3_regions = .;
    LONG (0)
    LONG (__cs3_region_init_ram)
    LONG (__cs3_region_start_ram)
    LONG (__cs3_region_init_size_ram)
    LONG (__cs3_region_zero_size_ram)
  }

  /* .ARM.exidx is sorted, so has to go in its own output section.  */
  __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } >rom
  __exidx_end = .;
  .text.align :
  {
    . = ALIGN(8);
    _etext = .;
  } >rom
  __cs3_region_size_rom = LENGTH(rom);
  __cs3_region_num = 1;
  
  .data :
  {
    __cs3_region_start_ram = .;
    *(.cs3.region-head.ram)
    KEEP(*(.jcr))
    *(.got.plt) *(.got)
    *(.shdata)
    *(.data .data.* .gnu.linkonce.d.*)
    *(.ram)
    . = ALIGN (8);
    _edata = .;
  } >ram AT>rom
  .bss :
  {
    *(.shbss)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
    *(.ram.b)
    . = ALIGN (8);
    _end = .;
    __end = .;
  } >ram AT>rom
  
  .heap (NOLOAD) :
  {
    *(.heap)
  } >ram
  .stack (__cs3_stack - __cs3_stack_size) (NOLOAD):
  {
    *(.stack)
    _estack = .;
    PROVIDE(estack = .);
  } >ram

  __cs3_region_init_ram = LOADADDR (.data);
  __cs3_region_init_size_ram = _edata - __cs3_region_start_ram;
  __cs3_region_zero_size_ram = _end - _edata;
  __cs3_region_size_ram = LENGTH(ram);
  __cs3_region_num = 1;

  .stab 0 (NOLOAD) : { *(.stab) }
  .stabstr 0 (NOLOAD) : { *(.stabstr) }
  /* DWARF debug sections.
   * Symbols in the DWARF debugging sections are relative to the beginning
   * of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }

  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) }
  /DISCARD/ : { *(.note.GNU-stack) }
}
