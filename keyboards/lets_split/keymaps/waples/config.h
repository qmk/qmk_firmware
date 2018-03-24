#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
//	#define MASTER_LEFT
//  #define MASTER_RIGHT
#define EE_HANDS              // We like to have choices I guess

#define PREVENT_STUCK_MODIFIERS // When switching layers, this will release all mods

#endif
