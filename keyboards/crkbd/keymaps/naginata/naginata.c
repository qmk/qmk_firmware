#include QMK_KEYBOARD_H
#include "naginata.h"

#define NGBUFFER 5 // バッファのサイズ

static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ (シフトキーを除く)
static bool is_naginata = false; // 薙刀式がオンかオフか
static bool is_naginata_edit = false; // 薙刀式編集モードがオンかオフか
static uint8_t naginata_layer = 0; // レイヤー番号
static bool ng_shift = false; // シフトキーの状態
static bool ng_space = false; // シフトキーかスペース入力か
static uint8_t n_modifier = 0; // 押しているmodifierキーの数

#ifdef NAGINATA_EDIT_MODE
static uint8_t naginata_elayerl = 0; // 左編集レイヤー番号
static uint8_t naginata_elayerr = 0; // 右編集レイヤー番号
static uint8_t n_editl = 0; // 押しているJKキーの数
static uint8_t n_editr = 0; // 押しているFGキーの数
#endif

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

// キーコードとキービットの対応
const uint32_t PROGMEM ng_key[] = {
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
  "vu", "ha", "te", "si" , SS_TAP(X_BSPACE), "ru", "su", "he",
  "ro", "ki", "to", "ka", "ltu", "ku", "a" , "i" , "u" , "-" ,
  "ho", "hi", "ke", "ko", "so" , "ta", "na", "nn", "ra", "re",

  // シフト
        "mi", "ri", "me"            , "sa", "yo", "yu", "e" ,
  "se", "ne", "ni", "ma", "ti", "wa", "no", "mo", "tu", "ya",
              "wo", "," , "nu", "o" , "." , "mu", "hu",

  // 濁音
        "ba", "de", "ji"            , "za",       "zu", "be",
  "ze", "gi", "do", "ga", "du", "gu",             "du",
  "bo", "bi", "ge", "go", "zo", "da",             "bu",

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

  SS_TAP(X_ENTER),
};

// 同時キー組み合わせのマップ。ng_kanaと対応する。
const uint32_t PROGMEM ng_comb[] = {
  // 単独
  B_Q, B_W, B_E, B_R          , B_U, B_I   , B_O  , B_P,
  B_A, B_S, B_D, B_F, B_G, B_H, B_J, B_K   , B_L  , B_SCLN,
  B_Z, B_X, B_C, B_V, B_B, B_N, B_M, B_COMM, B_DOT, B_SLSH,

  // シフト
              B_SHFT|B_W, B_SHFT|B_E, B_SHFT|B_R                        , B_SHFT|B_U, B_SHFT|B_I   , B_SHFT|B_O  , B_SHFT|B_P,
  B_SHFT|B_A, B_SHFT|B_S, B_SHFT|B_D, B_SHFT|B_F, B_SHFT|B_G, B_SHFT|B_H, B_SHFT|B_J, B_SHFT|B_K   , B_SHFT|B_L  , B_SHFT|B_SCLN,
                          B_SHFT|B_C, B_SHFT|B_V, B_SHFT|B_B, B_SHFT|B_N, B_SHFT|B_M, B_SHFT|B_COMM, B_SHFT|B_DOT,

  // 濁音
           B_J|B_W, B_J|B_E, B_J|B_R                  , B_F|B_U,             B_F|B_O  , B_F|B_P,
  B_J|B_A, B_J|B_S, B_J|B_D, B_J|B_F, B_J|B_G, B_F|B_H                     , B_F|B_L  ,
  B_J|B_Z, B_J|B_X, B_J|B_C, B_J|B_V, B_J|B_B, B_F|B_N                     , B_F|B_DOT,

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

  // enter
  B_V|B_M,
};

// 薙刀式のレイヤー、シフトキーを設定
void set_naginata(uint8_t layer) {
  naginata_layer = layer;
}

// 薙刀式をオンオフ
void naginata_on(void) {
  is_naginata = true;
  naginata_clear();
  layer_on(naginata_layer);
#ifdef NAGINATA_EDIT_MODE
  naginata_edit_off();
#endif

  tap_code(KC_LANG1); // Mac
  tap_code(KC_HENK); // Win
}

void naginata_off(void) {
  is_naginata = false;
  naginata_clear();
  layer_off(naginata_layer);
#ifdef NAGINATA_EDIT_MODE
  naginata_edit_off();
#endif

  tap_code(KC_LANG2); // Mac
  tap_code(KC_MHEN); // Win
}

// 薙刀式の状態
bool naginata_state(void) {
  return is_naginata;
}

// キー入力を文字に変換して出力する
void naginata_type(void) {
  uint32_t bkey; // PROGMEM buffer
  char kana[5]; // PROGMEM buffer
  uint32_t comb; // PROGMEM buffer
  bool douji = false; // 同時押しか連続押しか
  uint32_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。

  if (ng_shift) keycomb |= B_SHFT; // シフトキー状態を反映

  for (int i = 0; i < ng_chrcount; i++) {
    memcpy_P(&bkey, &ng_key[ninputs[i]], sizeof(bkey));
    keycomb |= bkey; // バッファにあるキー状態を合成する
  }

  switch (keycomb) {
    // send_stringできないキーはここで定義
    case B_F|B_G:
      naginata_off();
      break;
    default:
      // キーから仮名に変換して出力する。
      // 同時押しの場合
      for (int i = 0; i < sizeof ng_comb / sizeof comb; i++) {
        memcpy_P(&comb, &ng_comb[i], sizeof(comb));
        if (keycomb == comb) {
          douji = true;
          memcpy_P(&kana, &ng_kana[i], sizeof(kana));
          send_string(kana);
          break;
        }
      }
      // 連続押しの場合
      if (!douji) {
        for (int j = 0; j < ng_chrcount; j++) {
          memcpy_P(&bkey, &ng_key[ninputs[j]], sizeof(bkey));
          for (int i = 0; i < sizeof ng_comb / sizeof comb; i++) {
            memcpy_P(&comb, &ng_comb[i], sizeof(comb));
            if (bkey == comb) {
              memcpy_P(&kana, &ng_kana[i], sizeof(kana)); 
              send_string(kana);
              break;
            }
          }
        }
      }
  }

  naginata_clear(); // バッファを空にする
}

// バッファをクリアする
void naginata_clear(void) {
  for (int i = 0; i < NGBUFFER; i++) {
    ninputs[i] = 0;
  }
  ng_chrcount = 0;
  ng_space = false;
}

// 同じキーを繰り返し入力
void repeatkey(uint16_t k, uint8_t n) {
  for (int i = 0; i < n; i++) {
    tap_code(k);
  }
}

// 入力モードか編集モードかを確認する
void naginata_mode(uint16_t keycode, keyrecord_t *record) {
  if (!is_naginata) return;

  // modifierが押されたらレイヤーをオフ
  switch (keycode) {
    case KC_LCTRL:
    case KC_LSHIFT:
    case KC_LALT:
    case KC_LGUI:
    case KC_RCTRL:
    case KC_RSHIFT:
    case KC_RALT:
    case KC_RGUI:
      if (record->event.pressed) {
        n_modifier++;
        layer_off(naginata_layer);
        #ifdef NAGINATA_EDIT_MODE
        naginata_edit_off();
        #endif
      } else {
        n_modifier--;
        if (n_modifier == 0) {
          layer_on(naginata_layer);
        }
      }
      break;
  }

  if (n_modifier == 0) {
    #ifdef NAGINATA_EDIT_MODE
    // 編集モードに入るかチェック
    if (record->event.pressed) {
      switch (keycode) {
        case KC_D:
        case KC_F:
          n_editr++;
          if (n_editr >= 2) {
            naginata_edit_right_on();
          }
          break;
        case KC_J:
        case KC_K:
          n_editl++;
          if (n_editl >= 2) {
            naginata_edit_left_on();
          }
          break;
      }
    } else {
      switch (keycode) {
        case KC_D:
        case KC_F:
        case KC_J:
        case KC_K:
          n_editl = 0;
          n_editr = 0;
          naginata_edit_off();
          break;
      }
    }
    #endif
  }
}

// 薙刀式の入力処理
bool process_naginata(uint16_t keycode, keyrecord_t *record) {
  if (!is_naginata || is_naginata_edit || n_modifier > 0) return true;

  if (record->event.pressed) {
    switch (keycode) {
      case KC_A ... KC_Z:
      case KC_SLSH:
      case KC_DOT:
      case KC_COMM:
      case KC_SCLN:
        ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
        ng_chrcount++;
        if (ng_chrcount > 2) {
          naginata_type(); // 3文字押したら処理を開始
        }
        return false;
        break;
      case NGSHFT:
        ng_shift = true;
        if (ng_chrcount == 0) ng_space = true;
        return false;
        break;
    }
  } else { // key release
    switch (keycode) {
      case KC_A ... KC_Z:
      case KC_SLSH:
      case KC_DOT:
      case KC_COMM:
      case KC_SCLN:
        // 3文字入力していなくても、どれかキーを離したら処理を開始する
        if (ng_chrcount > 0) {
          naginata_type();
          return false;
        }
        break;
      case NGSHFT:
        if (ng_space) { // シフト単独押し
          tap_code(KC_SPC);
          ng_space = false;
        } else if (ng_chrcount > 0) { // シフトを先に離すとき
          naginata_type();
        }
        ng_shift = false;
        return false;
        break;
    }
  }
  return true;
}


#ifdef NAGINATA_EDIT_MODE

// 編集モードのレイヤー、マクロ
void set_naginata_edit(uint8_t layer1, uint8_t layer2) {
  naginata_elayerl = layer1;
  naginata_elayerr = layer2;
}

// 薙刀式編集モードをオンオフ
void naginata_edit_left_on(void) {
  is_naginata_edit = true;
  n_editl = 0;
  n_editr = 0;
  if (!layer_state_is(naginata_elayerl)) layer_on(naginata_elayerl);
  naginata_clear();
}

void naginata_edit_right_on(void) {
  is_naginata_edit = true;
  n_editl = 0;
  n_editr = 0;
  if (!layer_state_is(naginata_elayerr)) layer_on(naginata_elayerr);
  naginata_clear();
}

void naginata_edit_off(void) {
  is_naginata_edit = false;
  n_editl = 0;
  n_editr = 0;
  if (layer_state_is(naginata_elayerl))
    layer_off(naginata_elayerl);
  if (layer_state_is(naginata_elayerr))
    layer_off(naginata_elayerr);
}

// 薙刀式編集モードの状態
bool naginata_edit_state(void) {
  return is_naginata_edit;
}

// 編集モード
bool process_naginata_edit(uint16_t keycode, keyrecord_t *record) {
  // if (!is_naginata || !is_naginata_edit) return true;

  if (record->event.pressed) {
    switch (keycode) {
      case CHR10:
        register_code(KC_LCMD);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_LCMD);      
        repeatkey(KC_RGHT, 10);
        return false;
        break;
      case CHR20:
        register_code(KC_LCMD);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_LCMD);      
        repeatkey(KC_RGHT, 20);
        return false;
        break;
      case CHR30:
        register_code(KC_LCMD);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_LCMD);      
        repeatkey(KC_RGHT, 30);
        return false;
        break;
      case UP5:
        repeatkey(KC_UP, 5);
        return false;
        break;
      case DOWN5:
        repeatkey(KC_DOWN, 5);
        return false;
        break;
      }
  }
  return true;
}
#endif
