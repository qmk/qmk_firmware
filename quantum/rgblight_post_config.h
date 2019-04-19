#if defined(RGBLED_SPLIT) && !defined(RGBLIGHT_SPLIT)
  // When RGBLED_SPLIT is defined,
  // it is considered that RGBLIGHT_SPLIT is defined implicitly.
  #define RGBLIGHT_SPLIT
#endif
