// WindowsでJIS配列として認識しているときに、オシャレなUS配列用キーキャップを使うためのキーマップです。
// Google日本語入力の場合、以下のキー設定を行うとLower,Raiseのタップでそれぞれ半角入力と全角入力を切り替えできるようになります。
//  ・Henkan（入力文字なし/直接入力）に「IMEを有効化」を割り当て
//  ・Muhenkan（入力文字なし/直接入力）に「IMEを無効化」を割り当て

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"     // qmk_firmware-master/quantum/keymap_extras/keymap_japanese.h 日本語キーボード設定用
#include "sendstring_japanese.h" // macro sendstring for jis keyboard マクロ文字列送信時に日本語キーボード設定での文字化け回避

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY,
    _HDBX,
    _LOWER,
    _RAISE,
    _GAME,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  HDBX,
  MCR1,                // マクロ1
  MCR2,                // マクロ2
  MCR3,                // マクロ3
  MCR4,                // マクロ4
  MCR5,                // マクロ5
  WN_SCLN,              // タップでJISの「:」  シフトでJISの「;」 (Windows)
  DM_PLY1,
  DM_PLY2,
  DM_REC1,
  DM_REC2,
  DM_RSTP,
};

// Use Dynamic macro

// Fillers to make layering more clear
#define LOWER   LT(_LOWER, KC_MHEN)    // タップで無変換     ホールドでLower
#define RAISE   LT(_RAISE, KC_HENK)    // タップで変換       ホールドでRaise
#define GUI_ESC GUI_T(KC_ESC)          // タップでESC        ホールドでGUI
#define SFT_BS  SFT_T(KC_BSPC)         // タップでBackSpace  ホールドでSHIFT
#define CTL_ENT CTL_T(KC_ENT)          // タップでEnter      ホールドでCTRL
#define CTL_TAB CTL_T(KC_TAB)          // タップでTAB        ホールドでCTRL
#define SFT_DEL SFT_T(KC_DEL)          // タップでDELETE     ホールドでSHIFT
#define ALT_LBR ALT_T(JP_LBRC)         // タップで[          ホールドでALT
#define SFT_RBR SFT_T(JP_RBRC)         // タップで]          ホールドでSHIFT
#define SFT_SPC S(KC_SPC)              // Shift + Space
#define WN_CAPS S(KC_CAPS)             // Caps Lock           (Windows)
#define GAME    TO(_GAME)              // _GAMEレイヤーへ移動
#define ADJUST  TO(_ADJUST)            // _ADJUSTレイヤーへ移動

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty配列
   * ,----------------------------------.             ,----------------------------------.
   * |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |Alt/[ |WINESC|   ~  |Sft/Bs|Lower |CtlEnt|Space |Raise |CtrlTb|   -  |   '  |Sft/] |
   * `-----------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,    KC_K,    KC_L,    WN_SCLN,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
      ALT_LBR, GUI_ESC, JP_TILD, SFT_BS,  LOWER,   CTL_ENT,  KC_SPC,   RAISE,   CTL_TAB, KC_MINS, JP_QUOT, SFT_RBR
      ),

  /* HDBX配列 デフォルトレイヤーをこの配列にしたい場合は、AdjustレイヤーでK (Lower + Raise + K)
   * ,----------------------------------.             ,----------------------------------.
   * |   Q  |   W  |   E  |   ,  |   .  |             |   Y  |   D  |   P  |   F  |   :  |
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |   A  |   I  |   O  |   U  |   G  |             |   M  |   N  |   T  |   R  |   S  |
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |   Z  |   X  |   C  |   V  |   B  |             |   H  |   J  |   K  |   L  |   /  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |Alt/[ |WINESC|   ~  |Sft/Bs|Lower |CtlEnt|Space |Raise |CtrlTb|   -  |   '  |Sft/] |
   * `-----------------------------------------------------------------------------------'
   */
  [_HDBX] = LAYOUT(
      KC_Q,    KC_W,    KC_E,    KC_COMM, KC_DOT,                      KC_Y,    KC_D,    KC_P,    KC_F,    WN_SCLN,
      KC_A,    KC_I,    KC_O,    KC_U,    KC_G,                        KC_M,    KC_N,    KC_T,    KC_R,    KC_S,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SLSH,
      ALT_LBR, GUI_ESC, JP_TILD, SFT_BS,  LOWER,   CTL_ENT,  KC_SPC,   RAISE,   CTL_TAB, KC_MINS, JP_QUOT, SFT_RBR
      ),

  /* Lower
   * ,----------------------------------.             ,----------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |             |   7  |   8  |   9  |   .  | Bspc |
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |  F6  |  F7  |  F8  |  F9  |  F10 |             |   4  |   5  |   6  |   +  |   *  |
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |Zen/Ha|ScLock|Pause |  F11 |  F12 |             |   1  |   2  |   3  |   -  |   /  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Alt  | WIN  |   `  |SftDel|Lower | Ctrl |SftSpc|Raise |   0  |   ,  |   =  |Enter |
   * `-----------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( 
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_7,    KC_8,    KC_9,    KC_DOT,  KC_BSPC,
      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                      KC_4,    KC_5,    KC_6,    KC_PPLS, KC_PAST,
      KC_ZKHK, KC_SLCK, KC_PAUS, KC_F11,  KC_F12,                      KC_1,    KC_2,    KC_3,    KC_PMNS, KC_PSLS,
      KC_LALT, KC_LGUI, JP_GRV,  SFT_DEL, _______, KC_LCTL,  SFT_SPC,  _______, KC_0,    KC_COMM, JP_EQL,  KC_ENT
      ),

  /* Raise
   * ,----------------------------------.             ,----------------------------------.
   * |   !  |   @  |   #  |   $  |   %  |             | Home | App  | Ins  | Calc |PrtScr|
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |   ^  |   &  |   *  |   \  |   |  |             | Left | Down |  Up  |Right |   ;  |
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |   `  |   {  |   }  |   <  |   >  |             | End  | Mute |  (   |   )  |   ?  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Alt  | WIN  |   `  | Del  |Lower | Ctrl | Caps |Raise | Ctrl |   _  |   "  |Shift |
   * `-----------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT(
      KC_EXLM, JP_AT,   KC_HASH, KC_DLR,  KC_PERC,                     KC_HOME, KC_APP,  KC_INS,  KC_CALC, KC_PSCR,
      JP_CIRC, JP_AMPR, JP_ASTR, JP_YEN,  JP_PIPE,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN,
      JP_GRV,  JP_LCBR, JP_RCBR, KC_LT,   KC_GT,                       KC_END,  KC_MUTE, JP_LPRN, JP_RPRN, KC_QUES,
      KC_LALT, KC_LGUI, JP_GRV,  KC_DEL,  _______, KC_LCTL,  WN_CAPS,  _______, KC_RCTL, JP_UNDS, JP_DQUO, KC_RSFT
      ),

  /* GAME ゲームやテンキー固定で使用するレイヤーです。AdjustレイヤーでGを押下して遷移。戻るときはtoBaseから。
   * ,----------------------------------.             ,----------------------------------.
   * |   Q  |  Up  |   E  |   R  |   T  |             |   7  |   8  |   9  |   .  | Bspc |
   * |------+------+------+------+------|             |------+------+------+------+------|
   * | Left | Down |Right |   F  |   G  |             |   4  |   5  |   6  |   +  |   *  |
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |   Z  |   X  |   C  |   V  |   B  |             |   1  |   2  |   3  |   -  |   /  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Alt  | Esc  |  Tab |Shift |Space | Ctrl |toBase|   \  |   0  |   ,  |   =  |Enter |
   * `-----------------------------------------------------------------------------------'
   */
  [_GAME] = LAYOUT(
      KC_Q,    KC_UP,   KC_E,    KC_R,    KC_T,                        KC_7,    KC_8,    KC_9,    KC_DOT,  KC_BSPC,
      KC_LEFT, KC_DOWN, KC_RGHT, KC_F,    KC_G,                        KC_4,    KC_5,    KC_6,    KC_PPLS, KC_PAST,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_1,    KC_2,    KC_3,    KC_PMNS, KC_PSLS,
      KC_LALT, KC_ESC,  KC_TAB,  KC_LSFT, KC_SPC,  KC_LCTL,  ADJUST,   JP_YEN,  KC_0,    KC_COMM, JP_EQL,  KC_ENT
      ),

  /* Adjust (Lower + Raise)
   * ,----------------------------------.             ,----------------------------------.
   * | MCR1 | MCR2 | MCR3 | MCR4 | MCR5 |             |DyMcr1|DyMcr2|RcMcr1|RcMcr2|StpRec|
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |      |      |      |      |ToGAME|             |      |Qwerty| HDBX |      |      |
   * |------+------+------+------+------|             |------+------+------+------+------|
   * |      |      |      |      |      |             |      |      |      |      |      |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |RESET |      |      |      |      |      |      |      |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT(
      MCR1,    MCR2,    MCR3,    MCR4,    MCR5,                DM_PLY1, DM_PLY2, DM_REC1, DM_REC2, DM_RSTP,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, GAME,                      XXXXXXX, QWERTY,  HDBX,    XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RESET,   XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
      )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case HDBX:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_HDBX);
      }
      return false;
      break;
    static bool     lshift = false;
    case WN_SCLN: // コロン「;:」
      if (record->event.pressed) {
        lshift = get_mods() & MOD_BIT(KC_LSFT);
        if (lshift) {
          unregister_code(KC_LSFT);
          tap_code(JP_SCLN);
        } else {
          tap_code(JP_SCLN);
        }
      }
      return false;
      break;
    case MCR1:
      if (record->event.pressed) {
        SEND_STRING("0123456789"); // 送信文字列
      }
      return false;
      break;
    case MCR2:
      if (record->event.pressed) {
        SEND_STRING("hogehoge\n"); // 送信文字列
      }
      return false;
      break;
    case MCR3:
      if (record->event.pressed) {
        SEND_STRING("hoge@hoge.hoge"); // 送信文字列
      }
      return false;
      break;
    case MCR4:
      if (record->event.pressed) {
        SEND_STRING("\"\""SS_TAP(X_LEFT)); // 送信文字列
      }
      return false;
      break;
    case MCR5:
      if (record->event.pressed) {
        SEND_STRING("<>"SS_TAP(X_LEFT)); // 送信文字列
      }
      return false;
      break;
  }
  return true;
}
