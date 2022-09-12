#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LABK_MAC KC_GRAVE
#define ES_RABK_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    KC_TAB,      KC_Q,     KC_W,    KC_E,    KC_R,  KC_T,     KC_Y,  KC_U,  KC_I,     KC_O,    KC_P,      KC_BSPACE,
    KC_ESCAPE,   KC_A,     KC_S,    KC_D,    KC_F,  KC_G,     KC_H,  KC_J,  KC_K,     KC_L,    KC_SCOLON, KC_QUOTE,
    KC_LSHIFT,   KC_Z,     KC_X,    KC_C,    KC_V,  KC_B,     KC_N,  KC_M,  KC_COMMA, KC_DOT,  KC_SLASH,  KC_ENTER,
    WEBUSB_PAIR, KC_LCTRL, KC_LALT, KC_LGUI, LOWER, KC_SPACE, KC_NO, RAISE, KC_LEFT,  KC_DOWN, KC_UP,     KC_RIGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
    KC_TILD,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,       KC_ASTR,             KC_LPRN,           KC_RPRN,         _______,
    KC_DELETE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,       KC_PLUS,             KC_LCBR,           KC_RCBR,         KC_PIPE,
    _______,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NONUS_HASH, KC_NONUS_BSLASH,     KC_HOME,           KC_END,          _______,
    KC_COMMA,  _______, _______, _______, _______, _______, KC_NO,   _______,       KC_MEDIA_NEXT_TRACK, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_MEDIA_PLAY_PAUSE
  ),

  [_RAISE] = LAYOUT_planck_grid(
    KC_GRAVE,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,          KC_8,                KC_9,               KC_0,            _______,
    KC_DELETE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_MINUS,      KC_EQUAL,            KC_LBRACKET,        KC_RBRACKET,     KC_BSLASH,
    _______,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_NONUS_HASH, KC_NONUS_BSLASH,     KC_PGUP,            KC_PGDOWN,       _______,
    _______,   _______, _______, _______, _______, _______, KC_NO,  _______,       KC_MEDIA_NEXT_TRACK, KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP, KC_MEDIA_PLAY_PAUSE
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    _______,   CK_UP,   _______, _______, _______, _______, _______, _______, _______,_______,  _______, _______,
    KC_DELETE, CK_TOGG, AU_ON,   AU_OFF,  AU_TOG,  _______, _______, _______, RGB_VAI,RGB_VAD , _______, QK_BOOT,
    _______,   CK_DOWN, MU_ON,   MU_OFF,  MU_TOG,  _______, _______, _______, _______, _______, _______, _______,
    _______,   _______, _______, _______, _______, _______, KC_NO,   _______, _______, _______, _______, _______
  ),

};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255} },

    [1] = { {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255}, {193,255,255} },

    [2] = { {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255}, {104,255,255} },

    [3] = { {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255} },

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
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (get_highest_layer(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_DOWN);
        #else
            tap_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_UP);
        #else
            tap_code(KC_PGUP);
        #endif
        }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

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
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
