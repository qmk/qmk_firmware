OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(vectors)

GROUP( libgcc.a libc.a libm.a libcr_newlib_nohost.a  crti.o crtn.o crtbegin.o crtend.o )

/* Memory Definitions: */
MEMORY
{
    Flash  (rx)  : ORIGIN = 0x00000000, LENGTH = 512k
    Ram    (rwx) : ORIGIN = 0x40000000, LENGTH = 32k
    UsbRam (rw)  : ORIGIN = 0x7FD00000, LENGTH = 8k
    EthRam (rw)  : ORIGIN = 0x7FE00000, LENGTH = 16k
    CanRam (rw)  : ORIGIN = 0xE0038000, LENGTH = 2k
    BatRam (rw)  : ORIGIN = 0xE0084000, LENGTH = 2k
}

/* Stack sizes: */
UND_Stack_Size = 16;
SVC_Stack_Size = 512;
ABT_Stack_Size = 16;
FIQ_Stack_Size = 16;
IRQ_Stack_Size = 256;
Stack_Size_Total = UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + FIQ_Stack_Size + IRQ_Stack_Size;

/* Stack tops for each mode: */
__und_stack_top__ = __stacks_top__;
__abt_stack_top__ = __und_stack_top__ - UND_Stack_Size ;
__fiq_stack_top__ = __abt_stack_top__ - ABT_Stack_Size ;
__irq_stack_top__ = __fiq_stack_top__ - FIQ_Stack_Size ;
__svc_stack_top__ = __irq_stack_top__ - IRQ_Stack_Size ;

/* C-accessible symbols for memory address ranges: */
__FLASH_segment_start__ = ORIGIN( Flash );
__FLASH_segment_end__   = ORIGIN( Flash ) + LENGTH( Flash );
__SRAM_segment_start__  = ORIGIN( Ram );
__SRAM_segment_end__    = ORIGIN( Ram ) + LENGTH( Ram );

/* Stacks (full descending) at top of RAM, grows downward:
 *
 * __stack_min__ is used by the malloc implementation to ensure heap never collides
 * with stack (assuming stack never grows beyond Stack_Size_Total in length) */
__stacks_top__ = __SRAM_segment_end__;
__stacks_min__ = __SRAM_segment_end__ - Stack_Size_Total;

SECTIONS
{
    /* first section is .text which is used for code */
    __text_start__ = . ;
    .text : {
        __privileged_code_start__ = . ;
        KEEP( *( .vectors ) )
        *( .privileged_code )
    
        __privileged_code_end__ = .;

        *( .text .text.* .gnu.linkonce.t.* )
        *( .plt )
        *( .gnu.warning )
        *( .glue_7t ) *( .glue_7 ) *( .vfp11_veneer )
        
        *( .rodata .rodata.* .gnu.linkonce.r.* )
        
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        *(.gcc_except_table)
        *(.eh_frame_hdr)
        *(.eh_frame)
        
        . = ALIGN( 4 ) ;
        KEEP( *( .init ) )
        . = ALIGN( 4 ) ;
        __preinit_array_start = . ;
        KEEP( *( .preinit_array ) )
        __preinit_array_end = . ;
        . = ALIGN( 4 ) ;
        __init_array_start = . ;
        KEEP( *( SORT( .init_array.* ) ) )
        KEEP( *( .init_array ) )
        __init_array_end = . ;
        
        . = ALIGN( 4 ) ;
        KEEP( *crtbegin.o( .ctors ) )
        KEEP( *( EXCLUDE_FILE( *crtend.o ) .ctors ) )
        KEEP( *( SORT( .ctors.* ) ) )
        KEEP( *crtend.o( .ctors ) )
        
        . = ALIGN( 4 ) ;
        KEEP( *( .fini ) )
        . = ALIGN( 4 ) ;
        __fini_array_start = . ;
        KEEP( *( .fini_array ) )
        KEEP( *( SORT( .fini_array.* ) ) )
        __fini_array_end = . ;
        
        KEEP( *crtbegin.o( .dtors ) )
        KEEP( *( EXCLUDE_FILE( *crtend.o ) .dtors ) )
        KEEP( *( SORT( .dtors.* ) ) )
        KEEP( *crtend.o( .dtors ) )
    
    } >Flash
    
    __exidx_start = . ;
    .ARM.exidx : {
        *( .ARM.exidx* .gnu.linkonce.armexidx.* )
    } >Flash
    __exidx_end = . ;
    
    .text.align : { . = ALIGN( 8 ) ; } >Flash /* Alignment schenanigans */
    __text_end__ = . ;
    
    /* .bss section -- used for uninitialized data */
    /* Located at the start of RAM */
    .bss (NOLOAD) : {
        __bss_start__ = . ;
        *crt0.o( .ram_vectors )
        
        __user_bss_start__ = . ;
        *( .user_bss )
        __user_bss_end__ = . ;
        
        *( .shbss )
        *( .bss .bss.* .gnu.linkonce.b.* )
        *( COMMON )
        *( .ram.b )
        . = ALIGN( 8 ) ;
        
        __bss_end__ = . ;
    } >Ram AT>Flash

    /* .data section -- used for initialized data */
    .data : {
        __data_start__ = . ;
        KEEP( *( .jcr ) )
        *( .got.plt ) *( .got )
        *( .shdata )
        *( .data .data.* .gnu.linkonce.d.* )
        *( .ram )
        . = ALIGN( 8 ) ;
        __data_end__ = . ;
    } >Ram AT>Flash

    __data_init_start__ = LOADADDR( .data ) ;

    /* Heap starts here and grows up in memory */
    . = ALIGN( 8 ) ;
    __heap_start__ = . ;
    _pvHeapStart = . ;
    end = . ;

    .stab    0 (NOLOAD) : { *(.stab) }
    .stabstr 0 (NOLOAD) : { *(.stabstr) }
    /* DWARF debug sections. */
    /* Symbols in the DWARF debugging sections are relative to the  */
    /* beginning of the section so we begin them at 0.              */
    /* DWARF 1 */
    .debug           0 : { *(.debug) }
    .line            0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo   0 : { *(.debug_srcinfo) }
    .debug_sfnames   0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges   0 : { *(.debug_aranges) }
    .debug_pubnames  0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info      0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev    0 : { *(.debug_abbrev) }
    .debug_line      0 : { *(.debug_line) }
    .debug_frame     0 : { *(.debug_frame) }
    .debug_str       0 : { *(.debug_str) }
    .debug_loc       0 : { *(.debug_loc) }
    .debug_macinfo   0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
    /* DWARF 3 */
    .debug_pubtypes  0 : { *(.debug_pubtypes) }
    .debug_ranges    0 : { *(.debug_ranges) }
    
    .note.gnu.arm.ident 0 : { KEEP( *( .note.gnu.arm.ident ) ) }
    .ARM.attributes     0 : {
        KEEP( *( .ARM.attributes ) )
        KEEP( *( .gnu.attributes ) )
    }
    /DISCARD/             : { *( .note.GNU-stack ) }
    
    /* C data can be defined as being in special purpose RAMs using
     * __attribute__ ((section ("ethram"))) for example. */
    .usbram (NOLOAD):
    {
        *( .usbram )
        *( .usbram.* )
    } > UsbRam
    .ethram (NOLOAD):
    {
        *( .ethram )
        *( .ethram.* )
    } > EthRam
    .canram (NOLOAD):
    {
        *( .canram )
        *( .canram.* )
    } > CanRam
    .batram (NOLOAD):
    {
        *( .batram )
        *( .batram.* )
    } > BatRam
}
