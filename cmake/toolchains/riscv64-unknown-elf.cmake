if(${USE_PICOLIBC})
    add_compile_options(
        --specs=picolibc.specs
    )
    add_compile_definitions(USE_PICOLIBC)
    add_link_options(
        -Wl,--defsym=__heap_start=__heap_base__,--defsym=__heap_end=__heap_end__
    )
endif()

add_compile_options(
    -march=${MCU_ARCH}
    -mabi=${MCU_ABI}
    -mcmodel=${MCU_CMODEL}
    -mstrict-align
)