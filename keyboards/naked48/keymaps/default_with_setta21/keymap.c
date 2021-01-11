#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  KANJI,
  RGBRST,
  SEND_SUM,
  SEND_AVERAGE,
  SEND_COUNTIF,
  SEND_MAX,
  SEND_MIN
};

// Fillers to make layering more clear
#define _____ KC_TRNS
#define XXXXX KC_NO

#define KC_SNUBS S(KC_NUBS)
#define KC_SNUHS S(KC_NUHS)

#define KC_SSUM  SEND_SUM
#define KC_SAVE  SEND_AVERAGE
#define KC_SCOU  SEND_COUNTIF
#define KC_SMAX  SEND_MAX
#define KC_SMIN  SEND_MIN

#define KC_RADO LT(_RAISE, KC_PDOT)
#define KC_LOP0 LT(_LOWER, KC_P0)
#define KC_ADNL LT(_ADJUST, KC_NLCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_with_setta21(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,       KC_LOP0,  KC_P1,  KC_P4,  KC_P7,KC_ADNL, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
       KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,                 KC_P2,  KC_P5,  KC_P8,KC_PSLS,  KC_F2,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,       KC_RADO,  KC_P3,  KC_P6,  KC_P9,KC_PAST, KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
                ADJUST,KC_LCTRL, KC_LALT, KC_LGUI,   LOWER,  KC_SPC,  KC_SPC,   RAISE, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,                        KC_PENT,        KC_PPLS,KC_PMNS, KC_DEL
          //`------------------------------------------------------------------------------------------------------------'               |-----------------------------------------------|
  ),

  [_LOWER] = LAYOUT_with_setta21(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR,  KC_ASTR,KC_LPRN, KC_RPRN,  KC_DEL,         LOWER,  XXXXX,KC_LEFT,  XXXXX,  XXXXX, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
       KC_DEL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,               KC_DOWN,KC_DOWN,  KC_UP,KC_PSLS,  KC_F2,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
        _____,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,                    KC_F12,KC_SNUHS,KC_SNUBS,   _____,   _____,   _____,         RAISE,  XXXXX,KC_RIGHT, XXXXX,KC_PAST, KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
                 _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,                        KC_PENT,        KC_PPLS,KC_PMNS, KC_DEL
          //`------------------------------------------------------------------------------------------------------------'               |-----------------------------------------------|
  ),


  [_RAISE] = LAYOUT_with_setta21(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
      KC_TILD,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,         LOWER, KC_F11,  KC_F4,  KC_F7,KC_SMIN, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
       KC_DEL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,                KC_F12,  KC_F5,  KC_F8,KC_SMAX,  KC_F2,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
        _____,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,                    KC_F12, KC_NUHS, KC_NUBS,   _____,   _____,   _____,         RAISE,  KC_F3,  KC_F6,  KC_F9,KC_SCOU, KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
                 _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,                        KC_RPRN,        KC_SSUM,KC_SAVE, KC_DEL
          //`------------------------------------------------------------------------------------------------------------'               |-----------------------------------------------|
  ),

  [_ADJUST] = LAYOUT_with_setta21( /* Base */
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
        _____,   RESET,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                     XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   _____,         LOWER,RGB_VAD,RGB_HUD,RGB_SAD, ADJUST,RGB_TOG,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
        _____,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                   RGB_TOG, RGB_MOD,   XXXXX,LCA(KC_DEL),LALT(KC_PSCR),KC_PSCR,        RGB_VAI,RGB_HUI,RGB_SAI,  XXXXX,  _____,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
        _____,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                   RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI,         RAISE,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  _____,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
                 _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,                        RGB_MOD,          _____,  _____,  _____
          //`------------------------------------------------------------------------------------------------------------'               |-----------------------------------------------|
  )
};

static inline void update_change_layer(bool pressed, uint8_t layer1, uint8_t layer2, uint8_t layer3) {

  pressed ? layer_on(layer1) : layer_off(layer1);
  IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2) ? layer_on(layer3) : layer_off(layer3);
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    case LOWER:
      update_change_layer(record->event.pressed, _LOWER, _RAISE, _ADJUST);
      break;
    case RAISE:
      update_change_layer(record->event.pressed, _RAISE, _LOWER, _ADJUST);
        break;
    case SEND_SUM:
      if (record->event.pressed) {
        SEND_STRING("=SUM(");
      }
      break;
    case SEND_AVERAGE:
      if (record->event.pressed) {
        SEND_STRING("=AVERAGE(");
      }
      break;
    case SEND_COUNTIF:
      if (record->event.pressed) {
        SEND_STRING("=COUNTIF(");
      }
      break;
    case SEND_MAX:
      if (record->event.pressed) {
        SEND_STRING("=MAX(");
      }
      break;
    case SEND_MIN:
      if (record->event.pressed) {
        SEND_STRING("=MIN(");
      }
      break;
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGBRST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  return result;
}

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
}
