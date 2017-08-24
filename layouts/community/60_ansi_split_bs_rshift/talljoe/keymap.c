#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _WORKMAN,
    _NORMAN,
    _DVORAK,
    _COLMAK,
    _GAME,
    _NAV,
    _ADJUST,
    _RESET,
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define NV_SPC  LT(_NAV, KC_SPC)
#define AD_GRV  LT(_ADJUST, KC_GRV)

#define MO_NAV    MO(_NAV)
#define MO_ADJ    MO(_ADJUST)
#define MO_RST    MO(_RESET)
#define TG_ADJ    TG(_ADJUST)
#define TG_GAME   TG(_GAME)
#define LY_QWER   DF(_BASE)
#define LY_WORK   DF(_WORKMAN)
#define LY_NRMN   DF(_NORMAN)
#define LY_DVRK   DF(_DVORAK)
#define LY_CLMK   DF(_COLMAK)
#define TG_NKRO   MAGIC_TOGGLE_NKRO
#define KC_PTT    KC_F24

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = KM(
      KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSLS, KC_GRV,
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSPC,
      KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,          KC_ENT ,
      KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT, AD_GRV ,
      KC_LCTL, KC_LGUI, KC_LALT,                            NV_SPC ,                            KC_RALT, KC_RGUI, KC_RCTL, KC_PTT ),
  [_WORKMAN] = KM(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, KC_Q   , KC_D   , KC_R   , KC_W   , KC_B   , KC_J   , KC_F   , KC_U   , KC_P   , KC_SCLN, _______, _______, _______,
      _______, KC_A   , KC_S   , KC_H   , KC_T   , KC_G   , KC_Y   , KC_N   , KC_E   , KC_O   , KC_I   , _______,          _______,
      _______, KC_Z   , KC_X   , KC_M   , KC_C   , KC_V   , KC_K   , KC_L   , KC_COMM, KC_DOT , KC_SLSH,          _______, _______,
      _______, _______, _______,                            _______,                            _______, _______, _______, _______),
  [_NORMAN] = KM(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, KC_Q   , KC_W   , KC_D   , KC_F   , KC_K   , KC_J   , KC_U   , KC_R   , KC_L   , KC_SCLN, _______, _______, _______,
      _______, KC_A   , KC_S   , KC_E   , KC_T   , KC_G   , KC_Y   , KC_N   , KC_I   , KC_O   , KC_H   , _______,          _______,
      _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_P   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          _______, _______,
      _______, _______, _______,                            _______,                            _______, _______, _______, _______),
  [_DVORAK] = KM(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______,
      _______, KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   , KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_SLSH, KC_EQL , _______,
      _______, KC_A   , KC_O   , KC_E   , KC_U   , KC_I   , KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_MINS,          _______,
      _______, KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   , KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   ,          _______, _______,
      _______, _______, _______,                            _______,                            _______, _______, _______, _______),
  [_COLMAK] = KM(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, _______, _______, _______,
      _______, KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , _______,          _______,
      _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          _______, _______,
      _______, _______, _______,                            _______,                            _______, _______, _______, _______),
  [_GAME] = KM(
      KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSLS, KC_GRV,
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSPC,
      MO_NAV , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,          KC_ENT ,
      KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT, MO_ADJ ,
      KC_LCTL, KC_PTT , KC_PGDN,                            KC_SPC ,                            KC_RALT, KC_RGUI, KC_RCTL, KC_PTT ),
  [_NAV] = KM(
      KC_GRV , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_VOLU, KC_INS , KC_PGUP, KC_UP  , KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL ,
      XXXXXXX, KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_MUTE, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END , XXXXXXX,          TG_ADJ ,
      KC_LSFT, KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_VOLD, KC_END , KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,          KC_RSFT, XXXXXXX,
      KC_LCTL, KC_LGUI, KC_LALT,                            _______,                            KC_RALT, KC_RGUI, KC_RCTL, _______),
  // Adjust layer is on the split-shift key; or NAV+Enter (for non-split keyboards)
  [_ADJUST] = KM(
      MO_RST , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          TG_ADJ ,
      TG_NKRO, LY_QWER, LY_WORK, LY_NRMN, LY_DVRK, LY_CLMK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG_GAME,          XXXXXXX, XXXXXXX,
      MO_RST , AG_NORM, AG_SWAP,                            BL_TOGG,                            XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS),
  // To Reset hit FN + ` + Esc
  [_RESET] = KM(
      RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
      RESET  , XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
};

void matrix_scan_user(void) {
  #ifdef KEYBOARD_gh60
    if (IS_LAYER_ON(_GAME)) {
      gh60_wasd_leds_on();
    } else {
      gh60_wasd_leds_off();
    }
  #endif
}

void matrix_init_user(void) {
  if (!eeconfig_is_enabled()) {
    eeconfig_init();
  }
}

uint32_t default_layer_state_set_kb(uint32_t state) {
  // persist changes to default layers
  eeconfig_update_default_layer(state);
  return state;
}