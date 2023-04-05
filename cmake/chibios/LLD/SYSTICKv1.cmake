target_sources(qmk PUBLIC ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/SYSTICKv1/hal_st_lld.c)
target_include_directories(qmk PUBLIC ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/SYSTICKv1)