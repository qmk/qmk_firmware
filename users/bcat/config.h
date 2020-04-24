/* Wait between tap_code register and unregister to fix flaky media keys. */
#undef TAP_CODE_DELAY

#define TAP_CODE_DELAY 20

/*
 * Force the default tapping term since some keyboards make it way too short
 * (*cough*Lily58*cough*).
 */
#undef TAPPING_TERM

#define TAPPING_TERM 200

/*
 * Treat mod-tap keys as holds even if the mod-tap key and the key being
 * modified are both relased within TAPPING_TERM. This assumes the mod-tap key
 * isn't usually pressed in quick succession with other tapped keys, which is
 * good when the tap keycode is something like KC_ESC rather than a letter.
 */
#define PERMISSIVE_HOLD

/*
 * Turn off key repeat support of the tap keycode for tap-hold keys, enabling
 * holds to work correctly in quick succession after taps.
 */
#define TAPPING_FORCE_HOLD

#if defined(RGB_MATRIX_ENABLE)
/* Turn off per-key RGB when the host goes to sleep. */
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true

/* Keep per-key RGB increments consistent across keyboards. */
#    undef RGB_MATRIX_HUE_STEP
#    undef RGB_MATRIX_SAT_STEP
#    undef RGB_MATRIX_VAL_STEP
#    undef RGB_MATRIX_SPD_STEP

#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 17
#    define RGB_MATRIX_VAL_STEP 17
#    define RGB_MATRIX_SPD_STEP 17

/* Turn on additional RGB animations. */
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_KEYPRESSES
#endif

#if defined(RGBLIGHT_ENABLE)
/* Turn off RGB underglow when the host goes to sleep. */
#    define RGBLIGHT_SLEEP

/* Keep RGB underglow level increments consistent across keyboards. */
#    undef RGBLIGHT_HUE_STEP
#    undef RGBLIGHT_SAT_STEP
#    undef RGBLIGHT_VAL_STEP

#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17
#endif

#if defined(BACKLIGHT_ENABLE)
/* Enable backlight breathing across the board. */
#    define BACKLIGHT_BREATHING

/* Keep backlight level increments consistent across keyboards. */
#    undef BACKLIGHT_LEVELS

#    define BACKLIGHT_LEVELS 7
#endif
