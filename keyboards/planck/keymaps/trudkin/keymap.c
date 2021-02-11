/* Copyright 2020 Terence Rudkin 
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 

#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "trudkin.h"

#include "eeprom.h"

#include "tap.h"
#include "wrappers.h"


#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)



#undef MY_B
#define MY_B KC_B
#define MY_BSLH TD(TD_B)




#define LOWER TD(MOD_LOW)
#define RAISE TD(MOD_RAI)


// clang-format off
#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)  LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_5x12_wrapper(...)  LAYOUT_ortho_5x12(__VA_ARGS__)





// clang-format off
#define LAYOUT_ortho_4x12_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_ortho_4x12_wrapper( \
    KC_GESC,  K01,    K02,     K03,      K04,     K05,     K06,     K07,     K08,     K09,     K0A,     MY_BKSP, \
    KC_TAB, K11, K12, K13,      K14,     K15,     K16,     K17,     K18,     K19,     K1A, KC_QUOT, \
    KC_LSFT, CTL_T(K21), K22, K23,      K24,     K25,     K26,     K27,     K28,     K29, HYPR_T(KC_UP),  K2A, \
    KC_LCTRL,MY_LGUI,KC_LALT,LOWER,MY_BSLH,KC_SPACE,KC_NO,KC_ENTER,RAISE,RALT_T(KC_LEFT),RGUI_T(KC_DOWN),RCTL_T(KC_RIGHT) \
  )
#define LAYOUT_ortho_4x12_base_wrapper(...)       LAYOUT_ortho_4x12_base(__VA_ARGS__)

//123456

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



    [_COLEMAK] = LAYOUT_ortho_4x12_base_wrapper(
      _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, 
      _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
      _________________COLEMAK_L3________________, _________________COLEMAK_R3________________),  


    [_QWERTY] = LAYOUT_ortho_4x12_base_wrapper(
      _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
      _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
      _________________QWERTY_L3_________________, _________________QWERTY_R3_________________),   


    [_DVORAK] = LAYOUT_ortho_4x12_base_wrapper(
         _________________DVORAK_L1_________________, _________________DVORAK_R1_________________, 
         _________________DVORAK_L2_________________, _________________DVORAK_R2_________________, 
         _________________DVORAK_L3_________________, _________________DVORAK_R3_________________),

  [_LOWER] = LAYOUT_ortho_4x12_wrapper( 
      KC_TILD,    _________________LOWER_L1__________________, _________________LOWER_R1__________________,  _______,
      KC_DELETE,  _________________LOWER_L2__________________, _________________LOWER_R2__________________, KC_BSLASH,
      KC_LSPO,    _________________LOWER_L3__________________, _________________LOWER_R3__________________, KC_AUDIO_VOL_UP,
      _______,_______,_______,_______,_______,_______,KC_NO,_______,_______,KC_MEDIA_STOP,KC_AUDIO_VOL_DOWN,KC_MEDIA_PLAY_PAUSE),


//  [_LOWER] = LAYOUT_planck_grid(KC_TILD,  KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_KP_7,KC_8,KC_9,KC_0,  _______,
//                                KC_DELETE,SECRET1,SECRET2,_______,_______,_______,_______,KC_MINUS,KC_EQUAL,KC_LBRACKET,KC_RBRACKET,KC_BSLASH,
//                                KC_LSPO,  _______,_______,_______,_______,_______,_______,_______,KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_UP,KC_RSPC,
//                                _______,_______,_______,_______,_______,_______,KC_NO,_______,_______,KC_MEDIA_STOP,KC_AUDIO_VOL_DOWN,KC_MEDIA_PLAY_PAUSE),

  [_RAISE] = LAYOUT_ortho_4x12_wrapper(   
         KC_ESC,  _________________RAISE_L1__________________, _________________RAISE_R1__________________, KC_NO,
         KC_INS,  _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_BSLS,
         KC_DEL, _________________RAISE_L3__________________, _________________RAISE_R3__________________, RGB_TOG,
         _______,_______,_______, _______, NUMPAD ,  _______, _______, _______, _______, KC_MSTP, KC_VOLD, KC_MPLY),

  [_ADJUST] = LAYOUT_planck_grid(
      KC_PSCREEN,            QWERTY,COLEMAK,DVORAK,KC_NO,KC_NO,  KC_NO,KC_ASON,KC_ASOFF,KC_ASDN,KC_ASUP,         LALT(KC_PSCREEN),
      LALT(LCTL(KC_DELETE)), RESET,AU_ON,AU_OFF,AU_TOG,KC_NO,   _______,RGB_TOG,RGB_VAI,RGB_VAD,KC_ASRP,        RESET,
      KC_CAPSLOCK,           KC_MAKE,MU_ON,MU_OFF,MU_TOG,KC_NO, KC_NO,RGB_MOD,RGB_HUI,RGB_HUD,DYN_MACRO_PLAY2,  DYN_REC_STOP,
      _______,               SECRET1,SECRET1,_______, _______, _______,     KC_NO, _______, _______, DYN_REC_START1, DYN_REC_START2, DYN_MACRO_PLAY1),

  [_NUMPAD] = LAYOUT_planck_grid(_______,KC_P1,KC_P2,KC_P3,KC_P4,KC_P5,KC_P6,KC_KP_7,KC_KP_8,KC_KP_9,KC_0,_______,
                                 _______,LCTL(KC_A),_______,_______,_______,LCTL(KC_D),_______,KC_KP_4,KC_KP_5,KC_KP_6,KC_KP_PLUS,KC_KP_MINUS,
                                 KC_NUMLOCK,LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),LCTL(KC_B),_______,KC_KP_1,KC_KP_2,KC_KP_3,KC_KP_ASTERISK,KC_KP_SLASH,
                                 _______,_______,_______,_______,_______,_______,KC_NO,_______,KC_0,KC_KP_DOT,KC_CALCULATOR,_______),
//
//[_FUNCTION] = LAYOUT_planck_grid(_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MS_WH_UP,_______,KC_MS_WH_DOWN,
//                               _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,
//                                _______, _______, _______, _______, _______, TO(_COLEMAK), _______, _______, KC_MS_WH_LEFT, KC_MS_WH_RIGHT, KC_MS_UP, _______,
//                               _______,_______,_______,_______,_______,_______,KC_NO,_______,_______,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT),

};


/* need to find a naturally occuring macro to put here */

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {50,153,244}, {50,153,244}, {50,153,244}, {50,153,244}, {50,153,244}, {50,153,244}, {50,153,244}, {50,153,244}, {50,153,244}, {50,153,244}, {50,153,244}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {50,153,244}, {50,153,244}, {50,153,244}, {50,153,244}, {50,153,244}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {205,255,255}, {205,255,255}, {205,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {205,255,255}, {205,255,255}, {205,255,255} },

    [2] = { {50,153,244}, {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255}, {0,0,0}, {0,0,0}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {180,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {164,255,233}, {180,255,233}, {180,255,233}, {180,255,233} },

    [3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
           {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
           {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
           {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {180, 255, 233}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {180, 255, 233}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},

    [4] = { {0,0,0}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {146,224,255}, {146,224,255}, {146,224,255}, {134,255,213}, {0,0,0}, {0,0,0}, {85,203,158}, {0,0,0}, {0,0,0}, {0,0,0}, {85,203,158}, {0,0,0}, {146,224,255}, {146,224,255}, {146,224,255}, {0,204,255}, {0,204,255}, {105,255,255}, {85,203,158}, {85,203,158}, {85,203,158}, {85,203,158}, {85,203,158}, {0,0,0}, {146,224,255}, {146,224,255}, {146,224,255}, {0,204,255}, {0,204,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {146,224,255}, {146,224,255}, {105,255,255}, {0,0,0} },

    [5] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {154, 86, 255}, {154, 86, 255}, {154, 86, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {249, 228, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {195, 61, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {195, 61, 255}, {195, 61, 255}, {195, 61, 255}},

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}



bool led_update_user(led_t led_state) {

    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
        led_state.caps_lock ? rgb_matrix_set_color(24, 255,0,0) : rgb_matrix_set_color(24, 0,255,0);;
        caps_state = led_state.caps_lock;
    }

    return true;
}

void rgb_matrix_indicators_user(void) {
  uint8_t layer = get_highest_layer(layer_state);

  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
      uint8_t led_index = g_led_config.matrix_co[row][col];
      keypos_t pos = { col, row };
      uint16_t keycode = keymap_key_to_keycode(layer, pos);
      if (layer != _ADJUST ) {
          rgb_matrix_set_color(43, 0, 0, 255);
          rgb_matrix_set_color(39, 255,0,0);
      } else {       
          rgb_matrix_set_color(43, 255, 0, 255);
          rgb_matrix_set_color(39, 255,0,255);
      }
      host_keyboard_led_state().caps_lock ? rgb_matrix_set_color(24, 255,0,0) : rgb_matrix_set_color(24, 0,255,0);
      if (led_index != NO_LED || (led_index != 24 || led_index != 43 || led_index != 39)) {
          switch (keycode) {
          case RESET:
              rgb_matrix_set_color(led_index, 0,213,213);
              break;
          case DEBUG:
              rgb_matrix_set_color(led_index, 213,213,0);
              break;
          case AG_NORM:
              rgb_matrix_set_color(led_index, 0,255,0);
              break;
          case KC_TRNS:
          case KC_NO:
              rgb_matrix_set_color(led_index, 0x00, 0x00, 0x00);
              break;
          case KC_NUMLOCK ... KC_KP_DOT:
              rgb_matrix_set_color(led_index, 134,255,213);
              break;
          case 0x100 ... 0x1fff:
              rgb_matrix_set_color(led_index, keycode&0xff,255-8*(keycode>>8),16*(keycode>>8)&0x17);
              break; 
          }

      }
    }
  }
}

//void rgb_matrix_indicators_user(void) {
//  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
//
//  switch (biton32(layer_state)) {
//    case _LOWER:
//
//      set_layer_color(1);
//      break;
//    case _RAISE:
//
//      set_layer_color(2);
//      break;
//    case _ADJUST:
//
//      set_layer_color(3);
//      break;
//  case _NUMPAD:
//      set_layer_color(4);
//      break;
//  case _FUNCTION:
//      set_layer_color(5);
//      break;
//   default:
//    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
//      rgb_matrix_set_color_all(0, 0, 0);
//    break;
//  }
//}





#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

//void encoder_update(bool clockwise) {
//    if (muse_mode) {
//        if (IS_LAYER_ON(_RAISE)) {
//            if (clockwise) {
//                muse_offset++;
//            } else {
//                muse_offset--;
//            }
//        } else {
//            if (clockwise) {
//                muse_tempo+=1;
//            } else {
//                muse_tempo-=1;
//            }
//        }
//    } else {
//        if (clockwise) {
//        #ifdef MOUSEKEY_ENABLE
//            tap_code(KC_MS_WH_DOWN);
//        #else
//            tap_code(KC_PGDN);
//        #endif
//        } else {
//        #ifdef MOUSEKEY_ENABLE
//            tap_code(KC_MS_WH_UP);
//        #else
//            tap_code(KC_PGUP);
//        #endif
//        }
//    }
//}
//
//void matrix_scan_user(void) {
//#ifdef AUDIO_ENABLE
//    if (muse_mode) {
//        if (muse_counter == 0) {
//            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
//            if (muse_note != last_muse_note) {
//                stop_note(compute_freq_for_midi_note(last_muse_note));
//                play_note(compute_freq_for_midi_note(muse_note), 0xF);
//                last_muse_note = muse_note;
//            }
//        }
//        muse_counter = (muse_counter + 1) % muse_tempo;
//    }
//#endif
//}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif



layer_state_t layer_state_set_user(layer_state_t state) {
    state  = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
   return state;
}

qk_tap_dance_action_t tap_dance_actions[] = {
//    [NUM_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, nl_finished, nl_reset, 275),
//    [MOD_LOW] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, mod_low_finished, mod_low_reset, 275),
    [MOD_LOW] = MOD_LAYER( 1,KC_MINS, _LOWER, KC_RCTL, KC_RSFT),
    [MOD_RAI] = MOD_LAYER( 2,KC_EQL, _RAISE, KC_RALT, KC_RSFT),
    [MOD_FN]   = MOD_LAYER(4, KC_K, _FUNCTION, KC_RCTL, KC_RSFT),
    [TD_B]     = MOD_LAYER(3, KC_BSLS, _NUMPAD, KC_NO, KC_NO),


    [LBRC_9] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, l_brc_finished, l_brc_reset, 275),
    [RBRC_0] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, r_brc_finished, r_brc_reset, 275),
    // Tap Dance definitions

    [TD_BKSP_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, KC_DEL),

};
