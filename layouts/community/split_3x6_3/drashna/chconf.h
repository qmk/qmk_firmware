
#define CH_CFG_ST_RESOLUTION                16
#define CH_CFG_ST_FREQUENCY                 10000

#if __has_include("platforms/chibios/common/configs/chconf.h")
#    include_next "platforms/chibios/common/configs/chconf.h"
#else
#    include_next "chconf.h"
#endif
