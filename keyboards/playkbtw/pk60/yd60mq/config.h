#pragma once
#include "config_common.h"

#undef MANUFACTURER
#undef PRODUCT
#undef DESCRIPTION

#define MANUFACTURER    YMDK
#define PRODUCT         YD60MQ
#define DESCRIPTION     Keyboard

#ifdef LOCKING_RESYNC_ENABLE
#undef LOCKING_RESYNC_ENABLE
#endif
