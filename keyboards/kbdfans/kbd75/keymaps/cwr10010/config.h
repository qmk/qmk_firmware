
/* turn off RGB when computer sleeps */
#ifdef RGB_DI_PIN
#define RGBLIGHT_SLEEP
#endif

/* number of backlight levels */
#ifdef BACKLIGHT_LEVELS
#undef BACKLIGHT_LEVELS
#endif
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 9
#endif
