#pragma once


#undef PRODUCT
#define PRODUCT         Corne


#define SSD1306OLED

#define USE_SERIAL_PD2

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #undef RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 27
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#define LED_LAYOUT( \
    L00, L01, L02, L03, L04, L05,  \
    L24, L23, L18, L17, L10, L09, \
    L25, L22, L19, L16, L11, L08,     \
    L26, L21, L20, L15, L12, L07,   \
                    L14, L13, L06   \
    ) { \
    L00, L01, L02, L03, L04, L05,  \
    L06, L07, L08, L09, L10, L11,  \
    L12, L13, L14, L15, L16, L17,  \
    L18, L19, L20, L21, L22, L23,  \
                    L24, L25, L26   \
  }

// RGB LED logical order map 
// Top->Bottom, Right->Left 
#define RGBLIGHT_LED_MAP LED_LAYOUT( \
   0,  1,  2,  3,  4,  5,       \
   6,  7,  8,  9, 10, 11,       \
  12, 13, 14, 15, 16, 17,       \
  18, 19, 20, 21, 22, 23,      \
              24, 25, 26      \
)


#define K_TL0 KC_LSFT
#define K_TL1 LT(1,KC_BSPC)
#define K_TL2 LT(2,KC_TAB)
#define K_TL3 MO(3)

#define KX__SFT KC_RSFT
#define KX__CTL KC_RCTL
#define KX__ALT KC_RALT
#define KX__GUI KC_RGUI

#define K_IM_EN KC_HAEN
#define K_IM_JP KC_HANJ



#define LED_HIGH  96
#define LED_MID   32
#define LED_LOW    4


