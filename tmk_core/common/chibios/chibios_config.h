#pragma once

#if defined(STM32F1XX)
#    define USE_GPIOV1
#endif

#if defined(STM32F1XX) || defined(STM32F2XX) || defined(STM32F4XX) || defined(STM32L1XX)
#    define USE_I2CV1
#endif
