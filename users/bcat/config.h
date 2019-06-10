/* Delay between tap_code register and unregister to fix flaky media keys. */
#undef TAP_CODE_DELAY

#define TAP_CODE_DELAY 10

/* Turn off RGB lighting when the host goes to sleep. */
#define RGBLIGHT_SLEEP

/* Keep backlight and RGB level increments consistent across keyboards. */
#undef BACKLIGHT_LEVELS
#undef RGBLIGHT_HUE_STEP
#undef RGBLIGHT_SAT_STEP
#undef RGBLIGHT_VAL_STEP

#define BACKLIGHT_LEVELS 7
#define RGVLIGHT_HUE_STEP 8
#define RGVLIGHT_SAT_STEP 17
#define RGVLIGHT_VAL_STEP 17

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
