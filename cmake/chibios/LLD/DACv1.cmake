target_sources(qmk PUBLIC ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/DACv1/hal_dac_lld.c)
target_include_directories(qmk PUBLIC ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/DACv1)