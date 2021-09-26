#if defined(USE_I2C)
// When using I2C, using rgblight implicitly involves split support.
#    if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_SPLIT)
#        define RGBLIGHT_SPLIT
#    endif

#    ifndef F_SCL
#        define F_SCL 100000UL  // SCL frequency
#    endif
#endif
