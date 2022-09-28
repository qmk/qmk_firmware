#pragma once

#include_next <mcuconf.h>
#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLP_VALUE
#undef STM32_PLLQ_VALUE
#undef STM32_PPRE1
#undef STM32_PPRE2

#define STM32_PLLM_VALUE                    4
#define STM32_PLLN_VALUE                    168
#define STM32_PLLP_VALUE                    4
#define STM32_PLLQ_VALUE                    7
#define STM32_PPRE1                         STM32_PPRE1_DIV2
#define STM32_PPRE2                         STM32_PPRE2_DIV1

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE