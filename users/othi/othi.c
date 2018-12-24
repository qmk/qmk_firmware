#include "othi.h"

#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
  #define OTHI_UNICODE_MODE UC_LNX
#else
  #define OTHI_UNICODE_MODE 1
#endif

#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
set_unicode_input_mode(OTHI_UNICODE_MODE);
#endif //UNICODE_ENABLE

