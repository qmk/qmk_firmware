#include QMK_KEYBOARD_H
#include "keymap_japanese.h"


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
  _FLOCK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE,
  SEND_SUM,
  SEND_AVE,
  SEND_CIF,
  SEND_MAX,
  SEND_MIN
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define LWR_P0 LT(_LOWER, KC_P0)
#define RSE_DOT LT(_RAISE, KC_PDOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ,---.    ,-----------------------.   ,---------------------------.   ,---------------.
     * |PUp|    |Esc| 1 | 2 | 3 | 4 | 5 |   | 6 | 7 | 8 | 9 | 0 | - |Bsp|   |Esc|F2 | = |Del|
     * |---|  ,-------------------------|   |---------------------------|   |---------------|
     * |PDn|  | Tab | Q | W | E | R | T |   | Y | U | I | O | P | [ | ] |   |NLk| / | * | - |
     * `---' ,--------------------------|   |---------------------------|   |---------------|
     *       | Caps | A | S | D | F | G |   | H | J | K | L | ; | ' |Ent|   | 7 | 8 | 9 |   |
     *      ,---------------------------|   |---------------------------|   |-----------| + |
     *      | Shift | Z | X | C | V | B |   | N | M | , | . | / |Up |Sft|   | 4 | 5 | 6 |   |
     *      `---------------------------|   |---------------------------|   |---------------|
     *        |Adjust| |Alt | Space |Lwr|   |Rse| Space |Win|Lft|Dwn|Rgt|   | 1 | 2 | 3 |   |
     *        `------'  `---------------'   `---------------------------'   |-----------|Ent|
     *                                                                      |   0   | . |   |
     *                                                                      `---------------'
     */
    [_QWERTY] = LAYOUT_with_setta21(
        KC_PGUP,    KC_ESC , KC_1   , KC_2   , KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC,    KC_ESC,  KC_F2,   KC_EQL,  KC_DEL,
        KC_PGDN,    KC_TAB , KC_Q   , KC_W   , KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LCBR, KC_RCBR,    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
                    KC_LCTL, KC_A   , KC_S   , KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,     KC_P7,   KC_P8,   KC_P9,
                    KC_LSFT, KC_Z   , KC_X   , KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT,    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
                    ADJUST ,          KC_LALT,          KC_SPC,  LOWER,      RAISE,   KC_SPC,           KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT,    KC_P1,   KC_P2,   KC_P3,
                                                                                                                                               LWR_P0,           RSE_DOT, KC_PENT
    ),

    [_FLOCK] = LAYOUT_with_setta21(
     TG(_FLOCK),    KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,      _______, _______, _______, _______,
        _______,    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______,
                    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,
                    _______,          _______,          _______, _______,    _______, _______,          _______, _______, _______, _______,    _______, _______, _______,
                                                                                                                                               _______,          _______, _______
    ),

    [_LOWER] = LAYOUT_with_setta21(
        _______,    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,      KC_F8,      KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_ESC,  KC_F2,   KC_EQL,  KC_DEL,
        _______,    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL,  _______,    XXXXXXX, KC_PSLS, KC_PAST, KC_PMNS,
                    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE, _______,    XXXXXXX, KC_UP,   XXXXXXX,
                    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,     KC_F12,  S(KC_NUHS), S(KC_NUBS), _______, _______, KC_VOLU, _______,    KC_LEFT, KC_DOWN, KC_RGHT, KC_PPLS,
                    _______,          _______,          _______, _______,    _______, _______,                _______, KC_MNXT, KC_VOLD, KC_MPLY,    XXXXXXX, KC_DOWN, XXXXXXX,
                                                                                                                                                     LOWER,            RAISE,   KC_PENT
    ),

    [_RAISE] = LAYOUT_with_setta21(
        _______,    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_ESC,   KC_F2,    KC_EQL,   KC_DEL,
        _______,    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC,    SEND_MIN, SEND_MAX, SEND_CIF, SEND_AVE,
                    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______,    KC_F7,    KC_F8,    KC_F9,
                    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,     KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, _______,    KC_F4,    KC_F5,    KC_F6,    SEND_SUM,
                    _______,          _______,          _______, _______,    _______,          _______, _______, _______, _______, _______,    KC_F11,   KC_F12,   KC_F3,
                                                                                                                                               _______,            _______,  KC_RPRN
    ),

    [_ADJUST] = LAYOUT_with_setta21( /* Base */
     TG(_FLOCK),    QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,       KC_F10,        KC_F11,  KC_F12,     _______, _______, _______, _______,
        _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,       XXXXXXX, _______,    XXXXXXX, XXXXXXX, XXXXXXX, _______,
                    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    RGB_TOG, RGB_MOD, XXXXXXX, LCA(KC_DEL), LALT(KC_PSCR), KC_PSCR, XXXXXXX,    RGB_SAD, RGB_SAI, XXXXXXX,
                    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI,     RGB_SAD,       RGB_SAI, XXXXXXX,    RGB_HUD, RGB_HUI, XXXXXXX, RGB_TOG,
                    _______,          _______,          _______, _______,    _______,          _______, _______,     _______,       _______, _______,    RGB_VAD, RGB_VAI, XXXXXXX,
                                                                                                                                                         _______,          _______, RGB_MOD
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _FLOCK:
      rgblight_sethsv_range(HSV_YELLOW, 0, 2);
      break;
    case _LOWER:
      rgblight_sethsv_range(HSV_BLUE, 0, 2);
      break;
    case _RAISE:
      rgblight_sethsv_range(HSV_RED, 0, 2);
      break;
    case _ADJUST:
      rgblight_sethsv_range(HSV_PURPLE, 0, 2);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_range( 0, 0, 0, 0, 2);
      break;
    }
    rgblight_set_effect_range( 2, 6);
#endif
return state;
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    case SEND_SUM:
      if (record->event.pressed) {
        SEND_STRING("=SUM(");
      }
      break;
    case SEND_AVE:
      if (record->event.pressed) {
        SEND_STRING("=AVERAGE(");
      }
      break;
    case SEND_CIF:
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
      case RGB_RST:
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

}
