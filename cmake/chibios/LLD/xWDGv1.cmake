target_sources(qmk PUBLIC
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/xWDGv1/hal_wdg_lld.c
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/xWDGv1
)