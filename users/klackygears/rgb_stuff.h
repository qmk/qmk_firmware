//  #pragma once
//  #include "quantum.h"
//  #ifdef RGB_MATRIX_ENABLE
//    #include "rgb_matrix.h"
//  #endif

#define _RGBM_SINGLE_STATIC(sym)   RGBLIGHT_MODE_ ## sym,
#define _RGBM_SINGLE_DYNAMIC(sym)  RGBLIGHT_MODE_ ## sym,
#define _RGBM_MULTI_STATIC(sym)    RGBLIGHT_MODE_ ## sym,
#define _RGBM_MULTI_DYNAMIC(sym)   RGBLIGHT_MODE_ ## sym,
#define _RGBM_TMP_STATIC(sym)      RGBLIGHT_MODE_ ## sym,
#define _RGBM_TMP_DYNAMIC(sym)     RGBLIGHT_MODE_ ## sym,
// enum RGBLIGHT_EFFECT_MODE {
//     RGBLIGHT_MODE_zero = 0,
// #include "rgblight.h"
//     RGBLIGHT_MODE_last
// };

#ifndef RGBLIGHT_H_DUMMY_DEFINE



#define RGBLIGHT_MODES (RGBLIGHT_MODE_last-1)

void rgblight_mode_noeeprom(uint8_t mode);
void rgblight_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom);


#ifndef RGBLIGHT_EFFECT_BEAM_LENGTH
#define RGBLIGHT_EFFECT_BEAM_LENGTH 16
#endif

#ifndef RGBLIGHT_EFFECT_HYPER_LENGTH
#define RGBLIGHT_EFFECT_HYPER_LENGTH  104
#endif

void rgblight_effect_beam(uint8_t interval);
void rgblight_effect_hyper(uint8_t interval);
void rgblight_effect_rainbow_sparkle(uint8_t interval);

#endif

  #ifdef RGBLIGHT_EFFECT_BEAM
    _RGBM_MULTI_DYNAMIC( BEAM )
    _RGBM_TMP_DYNAMIC( beam_37 )
    //_RGBM_TMP_DYNAMIC( beam_38 )
    //_RGBM_TMP_DYNAMIC( beam_39 )
    //_RGBM_TMP_DYNAMIC( beam_40 )
    _RGBM_TMP_DYNAMIC( BEAM_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_HYPER
    _RGBM_MULTI_DYNAMIC( HYPER )
    //_RGBM_TMP_DYNAMIC( hyper_50 )
    //_RGBM_TMP_DYNAMIC( hyper_90 )
    //_RGBM_TMP_DYNAMIC( hyper_100 )
    //_RGBM_TMP_DYNAMIC( hyper_200 )
    _RGBM_TMP_DYNAMIC( HYPER_end )
  #endif
  #ifdef RGBLIGHT_EFFECT_RAINBOW_SPARKLE
    _RGBM_MULTI_DYNAMIC( RAINBOW_SPARKLE )
    _RGBM_TMP_DYNAMIC( rainbow_sparkle_10 )
    _RGBM_TMP_DYNAMIC( rainbow_sparkle_11 )
    _RGBM_TMP_DYNAMIC( rainbow_sparkle_12 )
    _RGBM_TMP_DYNAMIC( rainbow_sparkle_13 )
    _RGBM_TMP_DYNAMIC( RAINBOW_SPARKLE_end )
  #endif

#undef _RGBM_SINGLE_STATIC
#undef _RGBM_SINGLE_DYNAMIC
#undef _RGBM_MULTI_STATIC
#undef _RGBM_MULTI_DYNAMIC
#undef _RGBM_TMP_STATIC
#undef _RGBM_TMP_DYNAMIC






/*
typedef struct {
    bool enabled;
    uint8_t hue;
    uint16_t timer;
    uint8_t life;
} rgblight_fadeout;

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
void scan_rgblight_fadeout(void);
void keyboard_post_init_rgb(void);
void matrix_scan_rgb(void);
uint32_t layer_state_set_rgb(uint32_t state);
uint32_t default_layer_state_set_rgb(uint32_t state);
void rgblight_sethsv_default_helper(uint8_t index);
void rgb_matrix_set_color_all( uint8_t red, uint8_t green, uint8_t blue );
*/
