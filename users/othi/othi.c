#include "othi.h"

void eeconfig_init_users(void) {
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
  #define OTHI_UNICODE_MODE UC_LNX
#else
  #define OTHI_UNICODE_MODE 1
#endif
}
