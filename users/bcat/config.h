/* Wait between tap_code register and unregister to fix flaky media keys. */
#undef TAP_CODE_DELAY

#define TAP_CODE_DELAY 20

#if defined(RGBLIGHT_ENABLE)
  /* Turn off RGB underglow when the host goes to sleep. */
  #define RGBLIGHT_SLEEP

  /* Keep RGB underglow level increments consistent across keyboards. */
  #undef RGBLIGHT_HUE_STEP
  #undef RGBLIGHT_SAT_STEP
  #undef RGBLIGHT_VAL_STEP

  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 17
  #define RGBLIGHT_VAL_STEP 17
#endif

#if defined(BACKLIGHT_ENABLE)
  /* Enable backlight breathing across the board. */
  #define BACKLIGHT_BREATHING

  /* Keep backlight level increments consistent across keyboards. */
  #undef BACKLIGHT_LEVELS

  #define BACKLIGHT_LEVELS 7
#endif

#if defined(MOUSEKEY_ENABLE)
  /* Make mouse operation smoother. */
  #undef MOUSEKEY_DELAY
  #undef MOUSEKEY_INTERVAL

  #define MOUSEKEY_DELAY 0
  #define MOUSEKEY_INTERVAL 16

  /* Lower mouse speed to adjust for reduced MOUSEKEY_INTERVAL. */
  #undef MOUSEKEY_MAX_SPEED
  #undef MOUSEKEY_TIME_TO_MAX
  #undef MOUSEKEY_WHEEL_MAX_SPEED
  #undef MOUSEKEY_WHEEL_TIME_TO_MAX

  #define MOUSEKEY_MAX_SPEED 7
  #define MOUSEKEY_TIME_TO_MAX 150
  #define MOUSEKEY_WHEEL_MAX_SPEED 3
  #define MOUSEKEY_WHEEL_TIME_TO_MAX 150
#endif

#if defined(KEYBOARD_cannonkeys_instant60)
  /*
   * Work around EEPROM incompatibility with VIA:
   * https://github.com/qmk/qmk_firmware/issues/6589#issuecomment-524042457.
   */
  #undef EEPROM_MAGIC_ADDR
  #undef EEPROM_VERSION_ADDR
  #undef DYNAMIC_KEYMAP_EEPROM_ADDR
  #undef EEPROM_CUSTOM_BACKLIGHT
  #undef DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR

  #define EEPROM_MAGIC_ADDR 34
  #define EEPROM_VERSION_ADDR 36
  #define DYNAMIC_KEYMAP_EEPROM_ADDR 37
  #define EEPROM_CUSTOM_BACKLIGHT 637
  #define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR 638
#endif
