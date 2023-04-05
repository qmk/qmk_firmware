# os/common/ports/ARMv7/compilers/GCC/mk/port.mk
target_sources(qmk PUBLIC
    ${CHIBIOS}/os/common/ports/ARMv7-M/chcore.c
    ${CHIBIOS}/os/common/ports/ARMv7-M/compilers/GCC/chcoreasm.S
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/common/portability/GCC
    ${CHIBIOS}/os/common/ports/ARM-common
    ${CHIBIOS}/os/common/ports/ARMv7-M
)