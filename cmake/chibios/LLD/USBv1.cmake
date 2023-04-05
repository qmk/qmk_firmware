target_sources(qmk PUBLIC
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/USBv1/hal_usb_lld.c
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/USBv1
)