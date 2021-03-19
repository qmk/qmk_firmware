
#include_next<board.h>
#ifdef STM32_LSECLK
#undef STM32_LSECLK
#define STM32_LSECLK            0
#endif

#ifdef STM32_HSECLK
#undef STM32_HSECLK
#define STM32_HSECLK            12000000
#endif

#undef GPIOC_LED


