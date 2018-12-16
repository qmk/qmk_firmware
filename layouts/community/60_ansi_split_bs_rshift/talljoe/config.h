#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H

#define ENABLE_GAME_LAYER

#define TEMPLATE(                                                                   \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2D,      \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,           \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,                \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,           \
    K40, K41, K42,      K44, K45, K46,      K48, K49,      K4B, K4C                 \
) LAYOUT_60_ansi_split_bs_rshift(                                                   \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2D,      \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,           \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,                \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,           \
    K40, K41, K42,           K45,           K48, K49,      K4B, K4C                 \
)

/* Color Map */
#define CM( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2C, \
    K30, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3C, K3D, \
    K40, K41, K42,           K47,                     K4A, K4B, K4C, K4D  \
) { \
   { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
   { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
   { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D }, \
   { K30, {}, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
   { K40, K41, K42, {}, {}, {}, {}, K47, {}, {}, K4A, K4B, K4C, K4D } \
  }

#if defined (RGB_BACKLIGHT_ZEAL60) || defined (RGB_BACKLIGHT_M60_A)

  #define ZEAL_RGB

  /* enable/disable LEDs based on layout */
  #undef USE_SPLIT_BACKSPACE
  #define USE_SPLIT_BACKSPACE 1

  #undef USE_SPLIT_LEFT_SHIFT
  #define USE_SPLIT_LEFT_SHIFT 0

  #undef USE_SPLIT_RIGHT_SHIFT
  #define USE_SPLIT_RIGHT_SHIFT 1

  #undef USE_7U_SPACEBAR
  #define USE_7U_SPACEBAR 0

  #undef USE_ISO_ENTER
  #define USE_ISO_ENTER 0

  #undef TAPPING_TOGGLE
  #define TAPPING_TOGGLE 2

  #undef BACKLIGHT_MOD_LAYER_3
  #define BACKLIGHT_MOD_LAYER_3 RESET_LAYER

  #undef BACKLIGHT_ALPHAS_MODS_ROW_0
  #undef BACKLIGHT_ALPHAS_MODS_ROW_1
  #undef BACKLIGHT_ALPHAS_MODS_ROW_2
  #define BACKLIGHT_ALPHAS_MODS_ROW_0 0b0000000000000001
  #define BACKLIGHT_ALPHAS_MODS_ROW_1 0b0010000000000001
  #define BACKLIGHT_ALPHAS_MODS_ROW_2 0b0011000000000001

#endif //KEYBOARD_zeal60

#endif //CONFIG_USER_H
