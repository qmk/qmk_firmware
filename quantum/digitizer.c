#include "digitizer.h"

digitizer_t digitizer = {.tipswitch = 0,
                         .inrange = 0,
                         .id = 0,
                         .x = 0,
                         .y = 0,
                         .status = DZ_INITIALIZED|DZ_UPDATED};

