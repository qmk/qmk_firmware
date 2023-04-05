# os/hal/ports/STM32/STM32F3xx/platform.mk
target_sources(qmk PUBLIC
    ${CHIBIOS}/os/hal/ports/common/ARMCMx/nvic.c
    ${CHIBIOS}/os/hal/ports/STM32/STM32F3xx/stm32_isr.c
    ${CHIBIOS}/os/hal/ports/STM32/STM32F3xx/hal_lld.c
    ${CHIBIOS}/os/hal/ports/STM32/STM32F3xx/hal_efl_lld.c
)
target_include_directories(qmk PUBLIC
    ${CHIBIOS}/os/hal/ports/common/ARMCMx
    ${CHIBIOS}/os/hal/ports/STM32/STM32F3xx
)
include(chibios/LLD/ADCv3)
include(chibios/LLD/CANv1)
include(chibios/LLD/DACv1)
include(chibios/LLD/DMAv1)
include(chibios/LLD/EXTIv1)
include(chibios/LLD/GPIOv2)
include(chibios/LLD/I2Cv2)
include(chibios/LLD/RTCv2)
include(chibios/LLD/SPIv2)
include(chibios/LLD/SYSTICKv1)
include(chibios/LLD/TIMv1)
include(chibios/LLD/USARTv2)
include(chibios/LLD/USBv1)
include(chibios/LLD/xWDGv1)