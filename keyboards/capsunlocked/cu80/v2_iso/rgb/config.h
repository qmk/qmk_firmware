/* enable RGB matrix */
#define CU80_RGB

/*update the product for VIA/VIAL and Remap-keys.app */
#undef PRODUCT_ID
#define PRODUCT_ID      0x0083
#undef PRODUCT
#define PRODUCT         CU80 v2 ISO RGB

/* moved to RGB specific */
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50

/* RGB firmware override */
#undef RGBLIGHT_ANIMATIONS
#undef RGBLIGHT_HUE_STEP
#undef RGBLIGHT_SAT_STEP
#undef RGBLIGHT_VAL_STEP
#undef RGBLIGHT_LIMIT_VAL
