target_sources(qmk PUBLIC
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/SPIv2/hal_i2s_lld.c
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/SPIv2/hal_spi_v2_lld.c
)
target_include_directories(qmk PUBLIC ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/SPIv2)