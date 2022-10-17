#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

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
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  KANJI,
  RGBRST
};

enum tapdances{
  TD_SCCL = 0,
};

// Layer Mode aliases
#define KC_TBSF  LSFT_T(KC_TAB)
#define KC_ROSF  RSFT_T(JP_BSLS)
#define KC_ALAP  LALT_T(KC_APP)

// Layer tap
#define KC_BSLO  LT(_LOWER, KC_BSPC)
#define KC_SPRA  LT(_RAISE, KC_SPC)
#define KC_MLAD  MO(_ADJUST)

#define KC_SCCL  TD(TD_SCCL)

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------.
  //      Esc        Q        W        E        R        T        Y        U        I        O        P        -
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //Tab/Shift        A        S        D        F        G        H        J        K        L      ;/:    Enter
      KC_TBSF,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCCL,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //    Shift        Z        X        C        V        B        N        M        ,        .        /       yen
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_ROSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //     Ctrl      Alt GUI/Comm            BackSpace/Lower                Space/Raise      Alt     Menu     Ctrl
      KC_LCTL, KC_LALT, KC_LGUI,                   KC_BSLO,                   KC_SPRA, KC_RALT, KC_ALAP, KC_RCTL
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------.
  //                F1       F2       F3       F4       F5        -        ^        \        @        [   Delete
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_MINS,  KC_EQL,  JP_YEN, KC_LBRC, KC_RBRC,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //                F6       F7       F8       F9      F10                          ;        :        ]
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX, XXXXXXX, KC_SCLN, KC_QUOT, KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //               F11      F12        Kana/Kanji    Enter   Delete
      _______,  KC_F11,  KC_F12, XXXXXXX,   KANJI,  KC_ENT,  KC_DEL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //                                                                           Adjust
      _______, _______, _______,                   _______,                   KC_MLAD, _______, _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------.
  //                 1        2        3        4        5        6        7        8        9        0        -
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //                                                           Left     Down       Up    Right
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //                                                                                ,        .        /      yen
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM,  KC_DOT, KC_SLSH, KC_ROSF,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______,                   _______,                   _______, _______, _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [_ADJUST] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------.
  //             Reset LEDReset  MacMode  WinMode              Home PageDown   PageUp      End
      _______,   QK_BOOT,  RGBRST, AG_NORM, AG_SWAP, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //           LED On/Off Hue/Saturation/Value Increment    Mouse Left Down Up Right
      _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //           LED Mode Hue/Saturation/Value Decrement      Mouse Button Left Right
      _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______,                   _______,                   _______, _______, _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
  )
};

#define TAPPING_LAYER_TERM 150 // Custom LT Tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_BSLO:
      return TAPPING_LAYER_TERM;
    case KC_SPRA:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    case KANJI:
      if (record->event.pressed) {
        if (keymap_config.swap_lalt_lgui == false) {
          register_code(KC_LNG2);
        } else {
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LNG2);
      }
      break;
    #ifdef RGBLIGHT_ENABLE
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
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
