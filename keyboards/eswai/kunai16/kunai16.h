#pragma once

#include "quantum.h"

#if defined(STM32F303_CONFIG_H)
  #include "stm32f303.h"
#elif defined(STM32F103_CONFIG_H)
  #include "stm32f103.h"
#endif
