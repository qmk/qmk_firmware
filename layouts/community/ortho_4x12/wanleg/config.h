#ifndef CONFIG_USER_H
#define CONFIG_USER_H

//split keyboard settings
#if defined(KEYBOARD_lets_split_rev2)
#define USE_SERIAL
#undef USE_I2C
#define EE_HANDS
#endif

#endif
