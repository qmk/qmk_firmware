#pragma once

#include_next <mcuconf.h>

#undef AT32_HEXT_ENABLED
#define AT32_HEXT_ENABLED TRUE

#undef AT32_PLLRCS
#define AT32_PLLRCS AT32_PLLRCS_HICK

#undef AT32_PLLMULT_VALUE
#define AT32_PLLMULT_VALUE 36

