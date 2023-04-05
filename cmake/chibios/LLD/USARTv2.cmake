target_sources(qmk PUBLIC
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/USARTv2/hal_serial_lld.c
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/USARTv2/hal_sio_lld.c
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/USARTv2/hal_uart_lld.c 
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/USART
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/USARTv2
)