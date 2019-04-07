// Windows��JIS�z��Ƃ��ĔF�����Ă���Ƃ��ɁA�I�V������US�z��p�L�[�L���b�v���g�����߂̃L�[�}�b�v�ł��B
// Google���{����͂̏ꍇ�A�ȉ��̃L�[�ݒ���s����Lower,Raise�̃^�b�v�ł��ꂼ�ꔼ�p���͂ƑS�p���͂�؂�ւ��ł���悤�ɂȂ�܂��B
//  �EHenkan�i���͕����Ȃ�/���ړ��́j�ɁuIME��L�����v�����蓖��
//  �EMuhenkan�i���͕����Ȃ�/���ړ��́j�ɁuIME�𖳌����v�����蓖��

#include QMK_KEYBOARD_H
#include "keymap_jp.h"       // qmk_firmware-master/quantum/keymap_extras/keymap_jp.h ���{��L�[�{�[�h�ݒ�p
#include <sendstring_jis.h>  // macro sendstring for jis keyboard �}�N�������񑗐M���ɓ��{��L�[�{�[�h�ݒ�ł̕����������

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _HDBX,
    _LOWER,
    _RAISE,
    _GAME,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  HDBX,
  MCR1,                // �}�N��1
  MCR2,                // �}�N��2
  MCR3,                // �}�N��3
  MCR4,                // �}�N��4
  MCR5,                // �}�N��5
  DYNAMIC_MACRO_RANGE, // �_�C�i�~�b�N�}�N��
  WN_SCLN              // �^�b�v��JIS�́u:�v  �V�t�g��JIS�́u;�v (Windows)
};

// Use Dynamic macro
#include "dynamic_macro.h"

// Fillers to make layering more clear
#define LOWER   LT(_LOWER, KC_MHEN)    // �^�b�v�Ŗ��ϊ�     �z�[���h��Lower
#define RAISE   LT(_RAISE, KC_HENK)    // �^�b�v�ŕϊ�       �z�[���h��Raise
#define GUI_ESC GUI_T(KC_ESC)          // �^�b�v��ESC        �z�[���h��GUI
#define SFT_BS  SFT_T(KC_BSPC)         // �^�b�v��BackSpace  �z�[���h��SHIFT
#define CTL_ENT CTL_T(KC_ENT)          // �^�b�v��Enter      �z�[���h��CTRL
#define CTL_TAB CTL_T(KC_TAB)          // �^�b�v��TAB        �z�[���h��CTRL
#define SFT_DEL SFT_T(KC_DEL)          // �^�b�v��DELETE     �z�[���h��SHIFT
#define ALT_LBR ALT_T(JP_LBRC)         // �^�b�v��[          �z�[���h��ALT
#define SFT_RBR SFT_T(JP_RBRC)         // �^�b�v��]          �z�[���h��SHIFT
#define SFT_SPC S(KC_SPC)              // Shift + Space
#define WN_CAPS S(KC_CAPS)             // Caps Lock           (Windows)
#define MPLAY1  DYN_MACRO_PLAY1        // �_�C�i�~�b�N�}�N��1 
#define MPLAY2  DYN_MACRO_PLAY2        // �_�C�i�~�b�N�}�N��2
#define MREC1   DYN_REC_START1         // �_�C�i�~�b�N�}�N��1�L�^�J�n
#define MREC2   DYN_REC_START2         // �_�C�i�~�b�N�}�N��2�L�^�J�n
#define MRSTOP  DYN_REC_STOP           // �_�C�i�~�b�N�}�N���L�^�I��
#define GAME    TO(_GAME)              // _GAME���C���[�ֈړ�
#define ADJUST  TO(_ADJUST)            // _ADJUST���C���[�ֈړ�

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty�z��
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
  [_QWERTY] = LAYOUT( \
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,    KC_K,    KC_L,    WN_SCLN, \
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
      ALT_LBR, GUI_ESC, JP_TILD, SFT_BS,  LOWER,   CTL_ENT,  KC_SPC,   RAISE,   CTL_TAB, KC_MINS, JP_QUOT, SFT_RBR  \
      ),

  /* HDBX�z�� �f�t�H���g���C���[�����̔z��ɂ������ꍇ�́AAdjust���C���[��K (Lower + Raise + K)
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
  [_HDBX] = LAYOUT( \
      KC_Q,    KC_W,    KC_E,    KC_COMM, KC_DOT,                      KC_Y,    KC_D,    KC_P,    KC_F,    WN_SCLN, \
      KC_A,    KC_I,    KC_O,    KC_U,    KC_G,                        KC_M,    KC_N,    KC_T,    KC_R,    KC_S,    \
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SLSH, \
      ALT_LBR, GUI_ESC, JP_TILD, SFT_BS,  LOWER,   CTL_ENT,  KC_SPC,   RAISE,   CTL_TAB, KC_MINS, JP_QUOT, SFT_RBR  \
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
  [_LOWER] = LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_7,    KC_8,    KC_9,    KC_DOT,  KC_BSPC, \
      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                      KC_4,    KC_5,    KC_6,    KC_PPLS, KC_PAST, \
      KC_ZKHK, KC_SLCK, KC_PAUS, KC_F11,  KC_F12,                      KC_1,    KC_2,    KC_3,    KC_PMNS, KC_PSLS, \
      KC_LALT, KC_LGUI, JP_GRV,  SFT_DEL, _______, KC_LCTL,  SFT_SPC,  _______, KC_0,    KC_COMM, JP_EQL,  KC_ENT   \
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
  [_RAISE] = LAYOUT( \
      KC_EXLM, JP_AT,   KC_HASH, KC_DLR,  KC_PERC,                     KC_HOME, KC_APP,  KC_INS,  KC_CALC, KC_PSCR, \
      JP_CIRC, JP_AMPR, JP_ASTR, JP_YEN,  JP_PIPE,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, \
      JP_GRV,  JP_LCBR, JP_RCBR, KC_LT,   KC_GT,                       KC_END,  KC_MUTE, JP_LPRN, JP_RPRN, KC_QUES, \
      KC_LALT, KC_LGUI, JP_GRV,  KC_DEL,  _______, KC_LCTL,  WN_CAPS,  _______, KC_RCTL, JP_UNDS, JP_DQT,  KC_RSFT  \
      ),

  /* GAME �Q�[����e���L�[�Œ�Ŏg�p���郌�C���[�ł��BAdjust���C���[��G���������đJ�ځB�߂�Ƃ���toBase����B
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
  [_GAME] = LAYOUT( \
      KC_Q,    KC_UP,   KC_E,    KC_R,    KC_T,                        KC_7,    KC_8,    KC_9,    KC_DOT,  KC_BSPC, \
      KC_LEFT, KC_DOWN, KC_RGHT, KC_F,    KC_G,                        KC_4,    KC_5,    KC_6,    KC_PPLS, KC_PAST, \
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_1,    KC_2,    KC_3,    KC_PMNS, KC_PSLS, \
      KC_LALT, KC_ESC,  KC_TAB,  KC_LSFT, KC_SPC,  KC_LCTL,  ADJUST,   JP_YEN,  KC_0,    KC_COMM, JP_EQL,  KC_ENT   \
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
  [_ADJUST] =  LAYOUT( \
      MCR1,    MCR2,    MCR3,    MCR4,    MCR5,                      MPLAY1,  MPLAY2,  MREC1,   MREC2,   MRSTOP, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, GAME,                      XXXXXXX, QWERTY,  HDBX,    XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      RESET,   XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      )
};

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
    case HDBX:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_HDBX);
      }
      return false;
      break;
    static bool     lshift = false;
    case WN_SCLN: // �R�����u;:�v
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
        SEND_STRING("0123456789"); // ���M������
      }
      return false;
      break;
    case MCR2:
      if (record->event.pressed) {
        SEND_STRING("hogehoge"SS_TAP(X_ENTER)); // ���M������
      }
      return false;
      break;
    case MCR3:
      if (record->event.pressed) {
        SEND_STRING("hoge@hoge.hoge"); // ���M������
      }
      return false;
      break;
    case MCR4:
      if (record->event.pressed) {
        SEND_STRING("\"\""SS_TAP(X_LEFT)); // ���M������
      }
      return false;
      break;
    case MCR5:
      if (record->event.pressed) {
        SEND_STRING("<>"SS_TAP(X_LEFT)); // ���M������
      }
      return false;
      break;
  }
  return true;
}
