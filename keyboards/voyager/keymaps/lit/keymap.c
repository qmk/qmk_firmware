#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"
#include "keymap_korean.h"
#include "keymap_bepo.h"
#include "keymap_italian.h"
#include "keymap_slovenian.h"
#include "keymap_lithuanian_azerty.h"
#include "keymap_danish.h"
#include "keymap_norwegian.h"
#include "keymap_portuguese.h"
#include "keymap_contributions.h"
#include "keymap_czech.h"
#include "keymap_romanian.h"
#include "keymap_russian.h"
#include "keymap_uk.h"
#include "keymap_estonian.h"
#include "keymap_belgian.h"
#include "keymap_us_international.h"
#include "keymap_croatian.h"
#include "keymap_turkish_q.h"
#include "keymap_slovak.h"

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
#define SE_SECT_MAC ALGR(KC_6)
#define MOON_LED_LEVEL LED_LEVEL

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  MAC_MISSION_CONTROL,
};



enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
  DANCE_3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    CAPS_WORD,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,       
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           TD(DANCE_1),    TD(DANCE_2),    
    KC_ESCAPE,      MT(MOD_LCTL, KC_A),MT(MOD_LALT, KC_S),MT(MOD_LGUI, KC_D),MT(MOD_LSFT, KC_F),KC_G,                                           KC_H,           MT(MOD_RSFT, KC_J),MT(MOD_RGUI, KC_K),MT(MOD_RALT, KC_L),MT(MOD_RCTL, KC_SCOLON),KC_QUOTE,       
    TD(DANCE_0),    KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_EQUAL,       
                                                    LT(1,KC_BSPACE),LT(2,KC_ESCAPE),                                LT(3,KC_ENTER), LT(4,KC_SPACE)
  ),
  [1] = LAYOUT_voyager(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         
    KC_GRAVE,       KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,                                        KC_MINUS,       KC_7,           KC_8,           KC_9,           KC_SLASH,       KC_F12,         
    KC_TRANSPARENT, KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,                                        KC_PLUS,        KC_4,           KC_5,           KC_6,           KC_ASTR,        KC_BSPACE,      
    KC_TRANSPARENT, KC_TILD,        KC_LBRACKET,    KC_RBRACKET,    KC_LCBR,        KC_RCBR,                                        KC_DOT,         KC_1,           KC_2,           KC_3,           KC_EQUAL,       KC_ENTER,       
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_0
  ),
  [2] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LABK,        KC_RABK,        KC_GRAVE,                                       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LBRACKET,    KC_RBRACKET,    KC_QUOTE,                                       KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_BTN3,     KC_MS_BTN2,     KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LCBR,        KC_RCBR,        KC_DQUO,                                        KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_UP,       KC_MS_RIGHT,    KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LPRN,        KC_RPRN,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_voyager(
    RGB_TOG,        TOGGLE_LAYER_COLOR,RGB_MOD,        RGB_SLD,        RGB_VAD,        RGB_VAI,                                        LGUI(KC_F1),    LGUI(LSFT(KC_E)),KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    RGB_SLD,        RGB_MOD,        KC_BRIGHTNESS_UP,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_PSCREEN,                                     KC_HOME,        KC_PGDOWN,      KC_PGUP,        KC_END,         KC_DELETE,      KC_TRANSPARENT, 
    RGB_SPI,        RGB_SPD,        KC_BRIGHTNESS_DOWN,KC_AUDIO_VOL_DOWN,KC_MEDIA_PLAY_PAUSE,LSFT(KC_PSCREEN),                                KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_BSPACE,      KC_TRANSPARENT, 
    RGB_HUI,        RGB_HUD,        RGB_SAI,        RGB_SAD,        MAC_MISSION_CONTROL,KC_TRANSPARENT,                                 KC_ESCAPE,      LCTL(KC_D),     LCTL(KC_U),     KC_ENTER,       KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_voyager(
    TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    TO(1),          KC_TRANSPARENT, KC_TRANSPARENT, DT_UP,          KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    TO(2),          KC_TRANSPARENT, KC_TRANSPARENT, DT_DOWN,        KC_TRANSPARENT, KC_TRANSPARENT,                                 OSM(MOD_MEH),   OSM(MOD_LSFT),  OSM(MOD_LGUI),  OSM(MOD_LALT),  OSM(MOD_LCTL),  OSM(MOD_HYPR),  
    TO(3),          TO(5),          KC_TRANSPARENT, DT_PRNT,        KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_MEH,         KC_LSHIFT,      KC_LGUI,        KC_LALT,        KC_LCTRL,       KC_HYPR,        
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [5] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    TD(DANCE_3),    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
};



extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {0,226,204}, {170,116,255}, {170,116,255}, {170,116,255}, {170,116,255}, {170,116,255}, {207,114,255}, {207,114,255}, {207,114,255}, {207,114,255}, {207,114,255}, {207,114,255}, {0,0,0}, {207,114,255}, {207,114,255}, {207,114,255}, {74,255,255}, {74,255,255}, {0,0,0}, {139,163,179}, {41,255,255}, {41,255,255}, {169,255,255}, {169,255,255}, {0,0,0}, {0,0,0}, {170,116,255}, {170,116,255}, {170,116,255}, {170,116,255}, {170,116,255}, {170,116,255}, {16,200,255}, {129,201,237}, {129,201,237}, {129,201,237}, {16,200,255}, {170,116,255}, {41,225,235}, {129,201,237}, {129,201,237}, {129,201,237}, {41,225,235}, {1,218,204}, {93,218,204}, {129,201,237}, {129,201,237}, {129,201,237}, {93,218,204}, {41,207,250}, {0,0,0}, {129,201,237} },

    [2] = { {0,0,0}, {0,0,0}, {0,0,0}, {42,70,251}, {42,70,251}, {190,67,228}, {0,0,0}, {0,0,0}, {0,0,0}, {36,185,239}, {36,185,239}, {190,120,201}, {0,0,0}, {0,0,0}, {0,0,0}, {48,218,204}, {48,218,204}, {190,183,204}, {0,0,0}, {0,0,0}, {0,0,0}, {65,218,204}, {65,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {37,255,255}, {37,203,179}, {37,255,255}, {0,0,0}, {0,0,0}, {87,202,219}, {87,202,219}, {87,202,219}, {87,202,219}, {0,0,0}, {0,0,0}, {0,0,0}, {27,225,242}, {27,225,242}, {27,225,242}, {0,0,0}, {0,0,0}, {30,207,250}, {30,207,250} },

    [3] = { {25,255,255}, {0,0,0}, {0,0,0}, {90,255,255}, {32,218,204}, {32,218,204}, {0,0,0}, {214,255,255}, {41,255,255}, {169,255,255}, {0,255,255}, {213,164,239}, {90,255,255}, {139,255,255}, {41,255,255}, {169,255,255}, {74,255,255}, {213,229,128}, {139,255,255}, {139,255,255}, {170,141,255}, {170,141,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,119}, {41,92,215}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {158,144,228}, {30,207,250}, {30,207,250}, {158,218,204}, {0,255,255}, {0,0,0}, {27,255,255}, {27,255,255}, {27,255,255}, {27,255,255}, {0,255,255}, {0,0,0}, {236,199,235}, {21,218,204}, {21,218,204}, {249,85,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {78,255,255}, {78,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {78,255,255}, {0,0,0}, {78,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {78,255,255}, {0,0,0}, {78,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {78,255,255}, {78,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {139,255,255}, {0,0,0}, {139,255,255}, {40,255,255}, {40,255,255}, {40,255,255}, {139,255,255}, {0,0,0}, {139,255,255}, {40,255,255}, {40,255,255}, {40,255,255}, {139,255,255}, {0,0,0}, {139,255,255}, {40,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {139,255,255}, {0,0,0}, {40,255,255}, {40,255,255}, {40,255,255}, {0,0,0}, {0,0,0} },

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

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MAC_MISSION_CONTROL:
      HCS(0x29F);

    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}


typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[4];

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(qk_tap_dance_state_t *state, void *user_data);
void dance_0_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_0(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LCTL(KC_C));
        tap_code16(LCTL(KC_C));
        tap_code16(LCTL(KC_C));
    }
    if(state->count > 3) {
        tap_code16(LCTL(KC_C));
    }
}

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(LCTL(KC_C)); break;
        case DOUBLE_TAP: register_code16(RCTL(KC_V)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LCTL(KC_C)); register_code16(LCTL(KC_C));
    }
}

void dance_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(LCTL(KC_C)); break;
        case DOUBLE_TAP: unregister_code16(RCTL(KC_V)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LCTL(KC_C)); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(qk_tap_dance_state_t *state, void *user_data);
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_1(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_P);
        tap_code16(KC_P);
        tap_code16(KC_P);
    }
    if(state->count > 3) {
        tap_code16(KC_P);
    }
}

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_P); break;
        case DOUBLE_TAP: register_code16(KC_LBRACKET); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_P); register_code16(KC_P);
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_P); break;
        case DOUBLE_TAP: unregister_code16(KC_LBRACKET); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_P); break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(qk_tap_dance_state_t *state, void *user_data);
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_2_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_2(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_BSLASH);
        tap_code16(KC_BSLASH);
        tap_code16(KC_BSLASH);
    }
    if(state->count > 3) {
        tap_code16(KC_BSLASH);
    }
}

void dance_2_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(KC_BSLASH); break;
        case DOUBLE_TAP: register_code16(KC_RBRACKET); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_BSLASH); register_code16(KC_BSLASH);
    }
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_BSLASH); break;
        case DOUBLE_TAP: unregister_code16(KC_RBRACKET); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_BSLASH); break;
    }
    dance_state[2].step = 0;
}
void on_dance_3(qk_tap_dance_state_t *state, void *user_data);
void dance_3_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_3_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_3(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LGUI(KC_C));
        tap_code16(LGUI(KC_C));
        tap_code16(LGUI(KC_C));
    }
    if(state->count > 3) {
        tap_code16(LGUI(KC_C));
    }
}

void dance_3_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP: register_code16(LGUI(KC_C)); break;
        case DOUBLE_TAP: register_code16(RGUI(KC_V)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LGUI(KC_C)); register_code16(LGUI(KC_C));
    }
}

void dance_3_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP: unregister_code16(LGUI(KC_C)); break;
        case DOUBLE_TAP: unregister_code16(RGUI(KC_V)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LGUI(KC_C)); break;
    }
    dance_state[3].step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
};
