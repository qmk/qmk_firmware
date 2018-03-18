#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// I use a pro micro clocked at 8Mhz. It can't reach 1M baud, so this is the
// next fastest possible baud without errors. I don't notice any difference in
// behavior at this slower speed. (So I think it should maybe be the default,
// to allow a single codebase to support both available flavors of pro micro.)
// This requires a corresponding change to the wireless module firmware; see
// https://github.com/reversebias/mitosis/pull/10
#undef SERIAL_UART_BAUD // avoids redefinition warning
#define SERIAL_UART_BAUD 250000

// TODO: figure out which of these I can safely enable to reduce firmware size.
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT // can't; errors
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
