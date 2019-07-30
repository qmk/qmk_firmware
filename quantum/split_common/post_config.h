#if defined(USE_I2C) || defined(EH)
  // When using I2C, using rgblight implicitly involves split support.
  #if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_SPLIT)
    #define RGBLIGHT_SPLIT
  #endif

  #ifndef F_SCL
    #define F_SCL 100000UL  // SCL frequency
  #endif

#else  // use serial
  // When using serial, the user must define RGBLIGHT_SPLIT explicitly
  //  in config.h as needed.
  //      see quantum/rgblight_post_config.h
  #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    // When using serial and RGBLIGHT_SPLIT need separate transaction
    #define SERIAL_USE_MULTI_TRANSACTION
  #endif
#endif
