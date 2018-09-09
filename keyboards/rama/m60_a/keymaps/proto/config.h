#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// This fixes the diodes mounted reversed (fab fail) on M60-A prototype
#undef DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL

#endif //CONFIG_USER_H 
