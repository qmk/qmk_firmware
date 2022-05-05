#pragma once

#ifndef NUM_GPIO_PORTS
#ifdef KEYBOARD_REQUIRES_GPIOK
#    define NUM_GPIO_PORTS 11
#else
#    define NUM_GPIO_PORTS 10
#endif
#endif // NUM_GPIO_PORTS
