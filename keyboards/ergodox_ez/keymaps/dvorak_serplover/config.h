#undef LED_BRIGHTNESS_DEFAULT
#define LED_BRIGHTNESS_DEFAULT 5

#define QMK_KEYS_PER_SCAN 8

#undef DEBOUNCE
#define DEBOUNCE 4

/* HIGH: # on number keys, use the qwerty/asdf rows for letters.
 * default: # on qwerty, use the asdf/zxcv rows for letters.
 */
// #define STENO_KEYS_HIGH

/* IN: use the vertical 1.5 keys as *, put the other keys one row in,
 * don't use the horizontal 1.5 keys.
 */
// #define STENO_KEYS_IN

/* use top S as a # key instead */
#define STENO_KEYS_SNUM

#ifdef STENO_KEYS_SNUM
#define STN_SN STN_NC
#else
#define STN_SN STN_S1
#endif
