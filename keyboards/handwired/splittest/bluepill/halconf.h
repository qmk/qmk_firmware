/* Needed for serial bitbang, half-duplex and full-duplex */
#define HAL_USE_PAL TRUE
#define PAL_USE_WAIT TRUE
#define PAL_USE_CALLBACKS TRUE

#include_next <halconf.h>
