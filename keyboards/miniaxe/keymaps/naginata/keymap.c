/* Copyright 2018 ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
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

// Defines the keycodes used by our macros in process_record_user
#define _QWERTY 0
#define _NAGINATA 5 // 薙刀式入力レイヤー
#define _LOWER 10
#define _RAISE 11
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  NGSHFT, // 薙刀式シフトキー
};

#define SFTSPC  LSFT_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               | GUI  | LOWER|Ctrl/Esc|          |Spc/Sft| RAISE|Alt/BkSp |
 *               `--------------------'           `--------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
                    KC_LGUI, LOWER, SFTSPC,       SFTSPC, RAISE, MT(MOD_LALT, KC_BSPC)  \
),

/* 薙刀式
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |      |           |      |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               | GUI  | LOWER|Spc/Sft|          |Spc/Sft| RAISE|Alt/BkSp |
 *               `--------------------'           `--------------------'
 */
[_NAGINATA] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R, KC_LEFT,      KC_RGHT,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
                    KC_LGUI, LOWER, NGSHFT,       NGSHFT, RAISE, MT(MOD_LALT, KC_BSPC)  \
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab |   _  |   +  |  |   |  ~   |           |   :  |   "  |   >  |   {  |   }  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Caps|   -  |   =  |  \   |  `   |           |   ;  |   '  |   <  |   [  |   ]  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      | LOWER|      |           |  Esc | RAISE|      |
 *               `--------------------'           `--------------------'
 */
[_RAISE] = LAYOUT( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_TAB,  KC_UNDS, KC_PLUS, KC_PIPE, KC_TILD,      KC_COLN, KC_DQUO, KC_GT,   KC_LCBR, KC_RCBR, \
  KC_CAPS, KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,       KC_SCLN, KC_QUOT, KC_LT,   KC_LBRC, KC_RBRC, \
                    _______, _______, _______,      _______,  _______, _______\
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab |      |      |      |      |           | Left | Down |  Up  | Right| Enter|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Ctrl|   `  |  GUI |  Alt | Del  |           | BkSp | PgUp | PgDn |   \  |   '  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      | LOWER|      |           |      | RAISE|      |
 *               `--------------------'           `--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_TAB,  _______, _______, _______, _______,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT, \
  KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, KC_DEL,      KC_BSPC, KC_PGUP, KC_PGDN, KC_BSLS, KC_QUOT, \
                    _______, _______, _______,      _______, _______, _______                    \
),


/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|      |      |      |      |           | Prev | Next | Vol- | Vol+ | Play |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      | LOWER|      |           |      | RAISE|      |
 *               `--------------------'           `--------------------'
 */
[_ADJUST] =  LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, \
  KC_F11,  KC_F12,  _______, _______, _______,      _______, _______, _______, _______, _______, \
  RESET,   _______, _______, _______, _______,      KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, \
                    _______, _______, _______,      _______,  _______, _______                   \
)
};


// 薙刀式入力のコード1 ここから

static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ (シフトキーを除く)
static bool is_naginata = false; // 薙刀式入力モードかどうか
static bool is_modifier = false; // modifierの状態
static bool ng_shift = false; // シフトキーの状態
static bool ng_space = false; // シフトキーかスペース入力か

#define NGBUFFER 5 // バッファのサイズ

// 31キーを32bitの各ビットに割り当てる
#define B_Q    (1UL<<0)
#define B_W    (1UL<<1)
#define B_E    (1UL<<2)
#define B_R    (1UL<<3)
#define B_T    (1UL<<4)

#define B_Y    (1UL<<5)
#define B_U    (1UL<<6)
#define B_I    (1UL<<7)
#define B_O    (1UL<<8)
#define B_P    (1UL<<9)

#define B_A    (1UL<<10)
#define B_S    (1UL<<11)
#define B_D    (1UL<<12)
#define B_F    (1UL<<13)
#define B_G    (1UL<<14)

#define B_H    (1UL<<15)
#define B_J    (1UL<<16)
#define B_K    (1UL<<17)
#define B_L    (1UL<<18)
#define B_SCLN (1UL<<19)

#define B_Z    (1UL<<20)
#define B_X    (1UL<<21)
#define B_C    (1UL<<22)
#define B_V    (1UL<<23)
#define B_B    (1UL<<24)

#define B_N    (1UL<<25)
#define B_M    (1UL<<26)
#define B_COMM (1UL<<27)
#define B_DOT  (1UL<<28)
#define B_SLSH (1UL<<29)

#define B_SHFT (1UL<<30)

// 文字入力バッファ
static uint16_t ninputs[NGBUFFER];

// 関数宣言
void naginata_type(void);
void ng_clear(void);
void ng_output(char[NGBUFFER][29][5], uint16_t, int);

// キーコードとキービットの対応
const uint32_t ng_key[] = {
  [KC_Q]    = B_Q,
  [KC_W]    = B_W, 
  [KC_E]    = B_E, 
  [KC_R]    = B_R,
  [KC_T]    = B_T, 

  [KC_Y]    = B_Y, 
  [KC_U]    = B_U, 
  [KC_I]    = B_I, 
  [KC_O]    = B_O, 
  [KC_P]    = B_P, 

  [KC_A]    = B_A,
  [KC_S]    = B_S,
  [KC_D]    = B_D, 
  [KC_F]    = B_F, 
  [KC_G]    = B_G,

  [KC_H]    = B_H, 
  [KC_J]    = B_J,  
  [KC_K]    = B_K, 
  [KC_L]    = B_L,
  [KC_SCLN] = B_SCLN,

  [KC_Z]    = B_Z,   
  [KC_X]    = B_X, 
  [KC_C]    = B_C, 
  [KC_V]    = B_V, 
  [KC_B]    = B_B, 

  [KC_N]    = B_N, 
  [KC_M]    = B_M, 
  [KC_COMM] = B_COMM, 
  [KC_DOT]  = B_DOT, 
  [KC_SLSH] = B_SLSH, 
};

// 仮名のマップ。ng_combと対応する。
const char PROGMEM ng_kana[][5] = {
  // 単独
  "vu", "ha", "te", "si"             , "BS", "ru", "su", "he",
  "ro", "ki", "to", "ka", "ltu", "ku", "a" , "i" , "u" , "-" ,
  "ho", "hi", "ke", "ko", "so" , "ta", "na", "nn", "ra", "re",

  // シフト
  ""  , "mi", "ri", "me"            , "sa", "yo", "yu", "e" ,
  "se", "ne", "ni", "ma", "ti", "wa", "no", "mo", "tu", "ya",
  ""  , ""  , "wo", "," , "nu", "o" , "." , "mu", "hu", ""  ,

  // 濁音
        "ba", "de", "ji"            , "za", ""  , "zu", "be",
  "ze", "gi", "do", "ga", "du", "gu", ""  , ""  , "du", ""  ,
  "bo", "bi", "ge", "go", "zo", "da", ""  , ""  , "bu", ""  ,

  // 半濁音
  "pa", "pi", "pu", "pe", "po",

  // 小書き
  "la", "li", "lu" , "le", "lo",
  // 拗音
  "lya", "lyu", "lyo",

  // 拗音同時
  "kya", "kyu", "kyo", 
  "sya", "syu", "syo", 
  "tya", "tyu", "tyo", 
  "nya", "nyu", "nyo", 
  "hya", "hyu", "hyo", 
  "mya", "myu", "myo", 
  "rya", "ryu", "ryo",

  // 濁音拗音同時
  "gya", "gyu", "gyo",
  "jya", "jyu", "jyo",
  "dya", "dyu", "dyo",
  "bya", "byu", "byo",

  // 半濁音拗音同時
  "pya", "pyu", "pyo",

  // 外来音
  "va", "vi", "vyu", "ve", "vo",
  "teli", "telu",
  "sye",
  "tolu",
  "tile",
  "uli", "ule", "ulo",
  "fa", "fi", "fyu", "fe", "fo" ,

  // シフト外来音
  "tula", "tuli", "tule", "tulo",

  // 濁音外来音
  "deli", "delu",
  "je",
  "dolu",
  "dile",
};

// 同時キー組み合わせのマップ。ng_kanaと対応する。
const uint32_t ng_comb[] = {
  // 単独
  B_Q, B_W, B_E, B_R          , B_U, B_I   , B_O  , B_P,
  B_A, B_S, B_D, B_F, B_G, B_H, B_J, B_K   , B_L  , B_SCLN,
  B_Z, B_X, B_C, B_V, B_B, B_N, B_M, B_COMM, B_DOT, B_SLSH,

  // シフト
  B_SHFT|B_Q, B_SHFT|B_W, B_SHFT|B_E, B_SHFT|B_R                        , B_SHFT|B_U, B_SHFT|B_I   , B_SHFT|B_O  , B_SHFT|B_P,
  B_SHFT|B_A, B_SHFT|B_S, B_SHFT|B_D, B_SHFT|B_F, B_SHFT|B_G, B_SHFT|B_H, B_SHFT|B_J, B_SHFT|B_K   , B_SHFT|B_L  , B_SHFT|B_SCLN,
  B_SHFT|B_Z, B_SHFT|B_X, B_SHFT|B_C, B_SHFT|B_V, B_SHFT|B_B, B_SHFT|B_N, B_SHFT|B_M, B_SHFT|B_COMM, B_SHFT|B_DOT, B_SHFT|B_SLSH,

  // 濁音
           B_J|B_W, B_J|B_E, B_J|B_R                  , B_F|B_U, B_F|B_I   , B_F|B_O  , B_F|B_P,
  B_J|B_A, B_J|B_S, B_J|B_D, B_J|B_F, B_J|B_G, B_F|B_H, B_F|B_J, B_F|B_K   , B_F|B_L  , B_F|B_SCLN,
  B_J|B_Z, B_J|B_X, B_J|B_C, B_J|B_V, B_J|B_B, B_F|B_N, B_F|B_M, B_F|B_COMM, B_F|B_DOT, B_F|B_SLSH,

  // 半濁音
  B_M|B_W, B_M|B_X, B_V|B_DOT , B_V|B_P , B_M|B_Z,

  // 小書き
  B_SHFT|B_V|B_J, B_SHFT|B_V|B_K, B_SHFT|B_V|B_L, B_SHFT|B_V|B_P, B_SHFT|B_V|B_N,
  // 拗音
  B_SHFT|B_V|B_SCLN, B_SHFT|B_V|B_O, B_SHFT|B_V|B_I,

  // 拗音同時
  B_S|B_SCLN, B_S|B_O, B_S|B_I,
  B_R|B_SCLN, B_R|B_O, B_R|B_I,
  B_G|B_SCLN, B_G|B_O, B_G|B_I,
  B_D|B_SCLN, B_D|B_O, B_D|B_I,
  B_X|B_SCLN, B_X|B_O, B_X|B_I,
  B_W|B_SCLN, B_W|B_O, B_W|B_I,
  B_E|B_SCLN, B_E|B_O, B_E|B_I,

  // 濁音拗音同時
  B_J|B_S|B_SCLN, B_J|B_S|B_O, B_J|B_S|B_I,
  B_J|B_R|B_SCLN, B_J|B_R|B_O, B_J|B_R|B_I,
  B_J|B_G|B_SCLN, B_J|B_G|B_O, B_J|B_G|B_I,
  B_J|B_X|B_SCLN, B_J|B_X|B_O, B_J|B_X|B_I,

  // 半濁音拗音同時
  B_M|B_X|B_SCLN, B_M|B_X|B_O, B_M|B_X|B_I,

  // 外来音
  B_Q|B_J, B_Q|B_K, B_Q|B_L, B_Q|B_P, B_Q|B_N,
  B_E|B_K, B_E|B_L,
  B_R|B_P,
  B_D|B_L,
  B_G|B_P,
  B_L|B_K, B_L|B_P, B_L|B_N,
  B_DOT|B_J, B_DOT|B_K, B_DOT|B_L, B_DOT|B_P, B_DOT|B_N,

  // シフト外来音
  B_SHFT|B_L|B_J, B_SHFT|B_L|B_K, B_SHFT|B_L|B_P, B_SHFT|B_L|B_N,

  // 濁音外来音
  B_E|B_J|B_K, B_E|B_J|B_L,
  B_R|B_J|B_P,
  B_D|B_J|B_L,
  B_G|B_J|B_P,
};

// キー入力を文字に変換して出力する
void naginata_type(void) {
  char kana[5];
  uint32_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。
  if (ng_shift) keycomb |= B_SHFT; // シフトキー状態を反映

  for (int i = 0; i < ng_chrcount; i++) {
    keycomb |= ng_key[ninputs[i]]; // バッファにあるキー状態を合成する
  }

  switch (keycomb) {
    case B_U: // send_stringできないキーはここで定義
      register_code(KC_BSPC);
      unregister_code(KC_BSPC);
      break;
    case B_V|B_M:
      register_code(KC_ENT);
      unregister_code(KC_ENT);
      break;
    default:
      // 同時押しされているキーから仮名に変換して出力する。
      for (int i = 0; i < sizeof ng_comb / sizeof ng_comb[0]; i++) {
        if (keycomb == ng_comb[i]) {
          memcpy_P(&kana, &ng_kana[i], sizeof(kana)); 
          send_string(kana);
          break;
        }
      }
  }

  ng_clear(); // バッファを空にする
}

// バッファをクリアする
void ng_clear(void) {
  for (int i = 0; i < NGBUFFER; i++) {
    ninputs[i] = 0;
  }
  ng_chrcount = 0;
  ng_space = false;
}

// 薙刀式入力のコード1 ここまで

static bool lower_pressed = false;
static bool raise_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        // persistant_default_layer_set(1UL<<_QWERTY);
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        if (raise_pressed) {
          raise_pressed = false;
        } else {
          lower_pressed = true;
        }
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (lower_pressed) {
          layer_off(_NAGINATA);
          register_code(KC_LANG2); // Mac
          register_code(KC_MHEN); // Win
          is_naginata = false;
          unregister_code(KC_LANG2); // Mac
          unregister_code(KC_MHEN); // Win
          lower_pressed = false;
        }
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        if (lower_pressed) {
          lower_pressed = false;
        } else {
          raise_pressed = true;
        }
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (raise_pressed) {
          layer_on(_NAGINATA);
          register_code(KC_LANG1); // Mac
          register_code(KC_HENK); // Win
          is_naginata = true;
          unregister_code(KC_LANG1); // Mac
          unregister_code(KC_HENK); // Win
          raise_pressed = false;
        }
      }
      return false;
      break;
    default:
      lower_pressed = false;
      raise_pressed = false;
  }

  // 薙刀式入力のコード2　ここから

  // modifierが押されているか確認する
  switch (keycode) {
    case KC_LCTRL:
    case KC_LSHIFT:
    case KC_LALT:
    case KC_LGUI:
    case KC_RCTRL:
    case KC_RSHIFT:
    case KC_RALT:
    case KC_RGUI:
    case LOWER:
    case RAISE:
    case ADJUST:
      if (record->event.pressed) {
        is_modifier = true;
      } else {
        is_modifier = false;
      }
      break;
  }

  // 薙刀式入力モードでmodifierキーを押していない時
  if (is_naginata & !is_modifier) {
    if (record->event.pressed) {
      switch (keycode) {
        case NGSHFT: // シフトキー
          ng_shift = true;
          ng_space = true;
          return false;
          break;
        case KC_A ... KC_Z:
        case KC_SLSH:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
          ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
          ng_chrcount++;
          if (ng_chrcount > 2) naginata_type(); // 3文字押したら処理を開始
          return false;
          break;
        default: // 薙刀式入力に関係ないキーを押したらバッファを空にして処理を中断
          ng_clear();
          break;
      }

    } else { // key release
      switch (keycode) {
        case NGSHFT: // シフトキー
          ng_shift = false;
          if (ng_space) {
            register_code(KC_SPC);
            unregister_code(KC_SPC);
          }
          return false;
          break;
        case KC_A ... KC_Z:
        case KC_SLSH:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
          // 3文字入力していなくても、どれかキーを離したら処理を開始する
          if (ng_chrcount > 0) naginata_type();
          return false;
          break;
      }
    }
  }
  // 薙刀式入力コード2 ここまで

  return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
}
