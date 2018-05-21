#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#define ADVENTURE_TIME \
    H__NOTE(_F5),    \
    Q__NOTE(_F5),    \
    H__NOTE(_F5),    \
    H__NOTE(_G5),    \
    H__NOTE(_E5),    \
    H__NOTE(_E5),    \
    H__NOTE(_D5),    \
    H__NOTE(_C5),    \
    HD_NOTE(_C6),

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(ADVENTURE_TIME)
#endif

#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 15
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 10

// let's split configuration:
#define USE_I2C
#define EE_HANDS

#endif
