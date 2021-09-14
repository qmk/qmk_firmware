// WindowsでJIS配列として認識しているときに、US配列として使うためのキーマップ
// @leopard_gecko さんがPlanck用に作成されたキーマップをかなり参考にしています。

#include QMK_KEYBOARD_H
#include "keymap_jp.h"       // qmk_firmware-master/quantum/keymap_extras/keymap_jp.h 日本語キーボード設定用
#include <sendstring_jis.h>  // macro sendstring for jis keyboard マクロ文字列送信時に日本語キーボード設定での文字化け回避

extern keymap_config_t keymap_config;

// レイヤー
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _GAME 3
#define _ADJUST 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE, // QWERTYレイヤーへ
  MCR1,                // マクロ1
  MCR2,                // マクロ2
  MCR3,                // マクロ3
  DYNAMIC_MACRO_RANGE, // ダイナミックマクロ
  WN_SCLN,             // タップでJISの「:」  シフトでJISの「;」 (Windows)
};

// Use Dynamic macro
#include "dynamic_macro.h"

#define KC_LOWR LT(_LOWER, KC_MHEN)    // タップで無変換     ホールドでLower
#define KC_RASE LT(_RAISE, KC_HENK)    // タップで変換       ホールドでRaise
#define KC_LSLB MT(MOD_LSFT, JP_LBRC)  // タップで[          ホールドで左Shift
#define KC_RSRB MT(MOD_RSFT, JP_RBRC)  // タップで]          ホールドで右Shift
#define KC_ALTB MT(MOD_LALT, KC_TAB)   // タップでTAB        ホールドで左Alt
#define CTL_ZH  CTL_T(KC_ZKHK)         // タップで半角/全角  ホールドで左Control     (Windows)
#define WN_CAPS S(KC_CAPS)             // Caps Lock                                  (Windows)
#define KC_ALPS LALT(KC_PSCR)          // Alt + PrintScreen
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define GAME DF(_GAME)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY // WindowsでJIS配列時のデフォルトキーマップ
   * ,-------------------------------------------------------.   ,-------------------------------------------------------.
   * |Tab/Alt|   Q   |   W   |   E   |   R   |   T   |   -   |   |   ~   |   Y   |   U   |   I   |   O   |   P   | BSPC  |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * |ZH/Ctrl|   A   |   S   |   D   |   F   |   G   |   (   |   |   )   |   H   |   J   |   K   |   L   |   :   |   '   |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * | [/Sft |   Z   |   X   |   C   |   V   |   B   |  F2   |   |  Home |   N   |   M   |   ,   |   .   |   /   | ]/Sft |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * |WN CAPS|  GUI  |   \   |  Esc  |無変換 | Enter |  Del  |   |  End  | Space | 変換  | Left  | Down  |   Up  | Right |
   * |       |       |       |       | LOWER |       |       |   |       |       | RAISE |       |       |       |       |
   * `-------------------------------------------------------'   `-------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_ALTB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,   JP_TILD, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    CTL_ZH,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    JP_LPRN,   JP_RPRN, KC_H,    KC_J,    KC_K,    KC_L,    WN_SCLN, JP_QUOT, \
    KC_LSLB,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_F2,     KC_HOME, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSRB, \
    WN_CAPS,  KC_LGUI, JP_YEN,  KC_ESC,  KC_LOWR, KC_ENT,  KC_DEL,    KC_END,  KC_SPC,  KC_RASE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
  ),

  /* LOWER // 数字入力用レイヤー
   * ,-------------------------------------------------------.   ,-------------------------------------------------------.
   * |       |   1   |   2   |   3   |   4   |   5   |   6   |   |  Esc  |   7   |   8   |   9   |   .   |   =   |       |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * |       |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |   |  F2   |   4   |   5   |   6   |   -   |   /   | Enter |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * | Shift |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |   |       |   1   |   2   |   3   |   +   |   *   | Shift |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * |       |       |XXXXXXX|       |       |       |       |   |       |   0   |       |       |       |       |       |
   * `-------------------------------------------------------'   `-------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,       KC_ESC,  KC_7,    KC_8,    KC_9,    KC_PDOT, JP_EQL,  _______, \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F2,   KC_P4,   KC_P5,   KC_P6,   KC_PMNS, KC_PSLS, KC_ENT,  \
    KC_LSFT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_PAST, KC_RSFT, \
    _______, _______, XXXXXXX, _______, _______, _______, _______,    _______, KC_0,    _______, _______, _______, _______, _______ \
  ),

  /* RAISE // 記号入力用レイヤー
   * ,-------------------------------------------------------.   ,-------------------------------------------------------.
   * |       |   !   |   @   |   #   |   $   |   %   |   _   |   |   `   |   ^   |   &   |  Ins  |   \   |PrntScr|       |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * |       |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|   {   |   |   }   | Left  | Down  |   Up  | Right |   ;   |   "   |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * | Shift |M-PLAY |M-MUTE |VOL_DWN|VOL_UP |PREV_TR|NEXT_TR|   |PageUp |XXXXXXX|XXXXXXX|   <   |   >   |   ?   | Shift |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * |       |       |   |   |       |       |       |       |   |PageDwn|       |       |       |       |       |       |
   * `-------------------------------------------------------'   `-------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
    _______, KC_EXLM, JP_AT,   KC_HASH, KC_DLR,  KC_PERC, JP_UNDS,    JP_GRV,  JP_CIRC, JP_AMPR, KC_INS,  JP_YEN,  KC_ALPS, _______, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, JP_LCBR,    JP_RCBR, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, JP_DQUO, \
    KC_LSFT, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT,    KC_PGUP, XXXXXXX, XXXXXXX, KC_LT,   KC_GT,   KC_QUES, KC_RSFT, \
    _______, _______, JP_PIPE, _______, _______, _______, _______,    KC_PGDN, _______, _______, _______, _______, _______, _______ \
  ),

  /* GAME // 左手はゲーム用レイヤー、右手はNumPad
   * ,-------------------------------------------------------.   ,-------------------------------------------------------.
   * |  Tab  |   Q   |   W   |   E   |   R   |   T   |PrntScr|   |  Esc  |   7   |   8   |   9   |   .   |   =   | BSPC  |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * | Ctrl  |   A   |   S   |   D   |   F   |   G   |  F1   |   |  F2   |   4   |   5   |   6   |   -   |   /   | Enter |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   Z   |   X   |   C   |   V   |   B   |  F2   |   |  Home |   1   |   2   |   3   |   +   |   *   | Shift |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * |  Del  |  GUI  |  Alt  |  Esc  | LOWER | Space | Enter |   |  End  |   0   | RAISE | Left  | Down  |   Up  | Right |
   * `-------------------------------------------------------'   `-------------------------------------------------------'
   */
  [_GAME] = LAYOUT( \
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_ALPS,    KC_ESC,  KC_P7,   KC_P8,   KC_P9,   KC_PDOT, JP_EQL,  KC_BSPC, \
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_F1,      KC_F2,   KC_P4,   KC_P5,   KC_P6,   KC_PMNS, KC_PSLS, KC_ENT,  \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_F2,      KC_HOME, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_PAST, KC_RSFT, \
    KC_DEL,   KC_LGUI, KC_LALT, KC_ESC,  LOWER,   KC_SPC, KC_ENT,     KC_PGDN, KC_P0,   RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
  ),

  /* ADJUST // 設定用レイヤー (LOWER+RAISE)
   * ,-------------------------------------------------------.   ,-------------------------------------------------------.
   * |RGB_TOG| MCR1  | MCR2  | MCR3  |XXXXXXX|XXXXXXX|XXXXXXX|   |XXXXXXX|PLAY_M1|PLAY_M2|REC_M1 |REC_M2 |STP_REC| BSPC  |
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * | RESET |       |       |       |       |       |       |   |XXXXXXX|XXXXXXX|QWERTY | GAME  |XXXXXXX|XXXXXXX|XXXXXXX|
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * | Shift |       |       |       |       |       |       |   |XXXXXXX| M-PLAY|M-MUTE |VOL_DWN|VOL_UP |PREV_TR|NEXT_TR|
   * |-------+-------+-------+-------+-------+-------+-------|   |-------+-------+-------+-------+-------+-------+-------|
   * | DEBUG |XXXXXXX|XXXXXXX|       |       |XXXXXXX|XXXXXXX|   |XXXXXXX|XXXXXXX|       | Left  | Down  |   Up  | Right |
   * `-------------------------------------------------------'   `-------------------------------------------------------'
   */
  [_ADJUST] = LAYOUT( \
    RGB_TOG,  MCR1,    MCR2,    MCR3,    XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, DYN_REC_START1, DYN_REC_START2, DYN_REC_STOP, KC_BSPC, \
    RESET,    RGB_MOD, RGB_M_P, RGB_M_B, RGB_HUI, RGB_SAI, RGB_VAI,   XXXXXXX, XXXXXXX, QWERTY,  GAME,   XXXXXXX, XXXXXXX, XXXXXXX, \
    KC_LSFT,  RGB_M_R, RGB_M_SN,RGB_M_G, RGB_HUD, RGB_SAD, RGB_VAD,   XXXXXXX, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT, \
    DEBUG,    XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
  ),

};

// RGB Underglow使用時のレイヤー毎のカラー切り替え
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_enable();
  rgblight_setrgb_teal();
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#ifdef RGBLIGHT_ENABLE
    switch (biton32(state)) {
    case _RAISE:
      rgblight_setrgb_chartreuse(); // RAISE:シャルトリューズ
      break;
    case _LOWER:
      rgblight_setrgb_pink(); // LOWER:ピンク
      break;
    case _ADJUST:
      rgblight_setrgb_red(); // ADJUST:レッド
      break;
    default: //  for any other layers, or the default layer
      rgblight_setrgb_teal(); // 他:ティール
      break;
    }
#endif
return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool     lshift = false;
  if (!process_record_dynamic_macro(keycode, record)) {
      return false;
  }
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case WN_SCLN: // コロン「;:」
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        if (lshift) {
          unregister_code(KC_LSFT);
          register_code(JP_SCLN);
          unregister_code(JP_SCLN);
        } else {
          register_code(JP_COLN);
          unregister_code(JP_COLN);
        }
      }
      return false;
      break;
    case MCR1:
      if (record->event.pressed) {
        SEND_STRING("hoge"); // 送信文字列
      }
      return false;
      break;
    case MCR2:
      if (record->event.pressed) {
        SEND_STRING("hogehoge"SS_TAP(X_ENTER)); // 送信文字列
      }
      return false;
      break;
    case MCR3:
      if (record->event.pressed) {
                SEND_STRING("hoge@hoge.hoge"); // 送信文字列
      }
      return false;
      break;
  }
  return true;
}
