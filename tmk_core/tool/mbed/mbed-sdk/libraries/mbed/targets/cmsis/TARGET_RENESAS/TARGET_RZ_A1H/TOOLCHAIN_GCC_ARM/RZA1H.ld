/* Linker script for mbed RZ_A1H */

/* Linker script to configure memory regions. */
MEMORY
{
  ROM   (rx)  : ORIGIN = 0x00000000, LENGTH = 0x02000000
  BOOT_LOADER (rx) : ORIGIN = 0x18000000, LENGTH = 0x00004000 
  SFLASH (rx) : ORIGIN = 0x18004000, LENGTH = 0x07FFC000 
  L_TTB (rw)  : ORIGIN = 0x20000000, LENGTH = 0x00004000 
  RAM (rwx) : ORIGIN = 0x20020000, LENGTH = 0x00700000
  RAM_NC (rwx) : ORIGIN = 0x20900000, LENGTH = 0x00100000
}

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 * 
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 */
ENTRY(Reset_Handler)

SECTIONS
{
    .boot :
    {
        KEEP(*(.boot_loader)) 
    } > BOOT_LOADER 

    .text :
    {

        Image$$VECTORS$$Base = .;
        * (RESET)
        Image$$VECTORS$$Limit = .;
        . += 0x00000400;

        KEEP(*(.isr_vector))
        *(SVC_TABLE)
        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        Image$$RO_DATA$$Base = .;
        *(.rodata*)
        Image$$RO_DATA$$Limit = .;

        KEEP(*(.eh_frame*))
    } > SFLASH

    .ARM.extab : 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > SFLASH

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > SFLASH
    __exidx_end = .;


    .copy.table :
    {
        . = ALIGN(4);
        __copy_table_start__ = .;
        LONG (__etext)
        LONG (__data_start__)
        LONG (__data_end__ - __data_start__)
        LONG (__etext2)
        LONG (__nc_data_start)
        LONG (__nc_data_end - __nc_data_start)
        __copy_table_end__ = .;
    } > SFLASH

    .zero.table :
    {
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG (__bss_start__)
        LONG (__bss_end__ - __bss_start__)
        LONG (__nc_bss_start)
        LONG (__nc_bss_end - __nc_bss_start)
        __zero_table_end__ = .;
    } > SFLASH

    __etext = .;
        
    .ttb :
    {
        Image$$TTB$$ZI$$Base = .;
        . += 0x00004000;
        Image$$TTB$$ZI$$Limit = .;
    } > L_TTB

    .data : AT (__etext)
    {
        Image$$RW_DATA$$Base = .;
        __data_start__ = .;
        *(vtable)
        *(.data*)
        Image$$RW_DATA$$Limit = .;

        . = ALIGN(4);
        /* preinit data */
        PROVIDE (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE (__init_array_end = .);


        . = ALIGN(4);
        /* finit data */
        PROVIDE (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE (__fini_array_end = .);

        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;

    } > RAM

    
    .bss ALIGN(0x400):
    {
        Image$$ZI_DATA$$Base = .;
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
        Image$$ZI_DATA$$Limit = .;
    } > RAM

    
    .heap :
    {
        __end__ = .;
        end = __end__;
        *(.heap*)
        __HeapLimit = .;
    } > RAM

    /* .stack_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */
    .stack_dummy :
    {
        *(.stack)
    } > RAM

    __etext2 = __etext + SIZEOF(.data);
    .nc_data : AT (__etext2)
    {
        Image$$RW_DATA_NC$$Base = .;
        __nc_data_start = .;
        *(NC_DATA)

        . = ALIGN(4);
        __nc_data_end = .;
        Image$$RW_DATA_NC$$Limit = .;
    } > RAM_NC

    .nc_bss (NOLOAD) :
    {
        Image$$ZI_DATA_NC$$Base = .;
        __nc_bss_start = .;
        *(NC_BSS)

        . = ALIGN(4);
        __nc_bss_end = .;
        Image$$ZI_DATA_NC$$Limit = .;
    } > RAM_NC

    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    __StackTop = ORIGIN(RAM) + LENGTH(RAM);
    __StackLimit = __StackTop - SIZEOF(.stack_dummy);
    PROVIDE(__stack = __StackTop);
    
    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")


}
