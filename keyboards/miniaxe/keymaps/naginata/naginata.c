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
// メモリ削減のため配列はNG_Qを0にしている
const uint32_t ng_key[] = {
  [NG_Q - NG_Q]    = B_Q,
  [NG_W - NG_Q]    = B_W,
  [NG_E - NG_Q]    = B_E,
  [NG_R - NG_Q]    = B_R,
  [NG_T - NG_Q]    = B_T,

  [NG_Y - NG_Q]    = B_Y,
  [NG_U - NG_Q]    = B_U,
  [NG_I - NG_Q]    = B_I,
  [NG_O - NG_Q]    = B_O,
  [NG_P - NG_Q]    = B_P,

  [NG_A - NG_Q]    = B_A,
  [NG_S - NG_Q]    = B_S,
  [NG_D - NG_Q]    = B_D,
  [NG_F - NG_Q]    = B_F,
  [NG_G - NG_Q]    = B_G,

  [NG_H - NG_Q]    = B_H,
  [NG_J - NG_Q]    = B_J,
  [NG_K - NG_Q]    = B_K,
  [NG_L - NG_Q]    = B_L,
  [NG_SCLN - NG_Q] = B_SCLN,

  [NG_Z - NG_Q]    = B_Z,
  [NG_X - NG_Q]    = B_X,
  [NG_C - NG_Q]    = B_C,
  [NG_V - NG_Q]    = B_V,
  [NG_B - NG_Q]    = B_B,

  [NG_N - NG_Q]    = B_N,
  [NG_M - NG_Q]    = B_M,
  [NG_COMM - NG_Q] = B_COMM,
  [NG_DOT - NG_Q]  = B_DOT,
  [NG_SLSH - NG_Q] = B_SLSH,
};

// 薙刀式カナ変換テーブル
typedef struct {
  uint32_t key;
  char kana[5];
} naginata_keymap;

const PROGMEM naginata_keymap ngmap[] = {
  // 単独
  {.key = B_Q               , .kana = "vu"},
  {.key = B_W               , .kana = "ha"},
  {.key = B_E               , .kana = "te"},
  {.key = B_R               , .kana = "si"},
  {.key = B_U               , .kana = SS_TAP(X_BSPACE)},
  {.key = B_I               , .kana = "ru"},
  {.key = B_O               , .kana = "su"},
  {.key = B_P               , .kana = "he"},
  {.key = B_A               , .kana = "ro"},
  {.key = B_S               , .kana = "ki"},
  {.key = B_D               , .kana = "to"},
  {.key = B_F               , .kana = "ka"},
  {.key = B_G               , .kana = "ltu"},
  {.key = B_H               , .kana = "ku"},
  {.key = B_J               , .kana = "a"},
  {.key = B_K               , .kana = "i"},
  {.key = B_L               , .kana = "u"},
  {.key = B_SCLN            , .kana = "-"},
  {.key = B_Z               , .kana = "ho"},
  {.key = B_X               , .kana = "hi"},
  {.key = B_C               , .kana = "ke"},
  {.key = B_V               , .kana = "ko"},
  {.key = B_B               , .kana = "so"},
  {.key = B_N               , .kana = "ta"},
  {.key = B_M               , .kana = "na"},
  {.key = B_COMM            , .kana = "nn"},
  {.key = B_DOT             , .kana = "ra"},
  {.key = B_SLSH            , .kana = "re"},

  // シフト
  {.key = B_SHFT|B_Q        , .kana = "vu"},
  {.key = B_SHFT|B_W        , .kana = "mi"},
  {.key = B_SHFT|B_E        , .kana = "ri"},
  {.key = B_SHFT|B_R        , .kana = "me"},
  {.key = B_SHFT|B_U        , .kana = "sa"},
  {.key = B_SHFT|B_I        , .kana = "yo"},
  {.key = B_SHFT|B_O        , .kana = "yu"},
  {.key = B_SHFT|B_P        , .kana = "e"},
  {.key = B_SHFT|B_A        , .kana = "se"},
  {.key = B_SHFT|B_S        , .kana = "ne"},
  {.key = B_SHFT|B_D        , .kana = "ni"},
  {.key = B_SHFT|B_F        , .kana = "ma"},
  {.key = B_SHFT|B_G        , .kana = "ti"},
  {.key = B_SHFT|B_H        , .kana = "wa"},
  {.key = B_SHFT|B_J        , .kana = "no"},
  {.key = B_SHFT|B_K        , .kana = "mo"},
  {.key = B_SHFT|B_L        , .kana = "tu"},
  {.key = B_SHFT|B_SCLN     , .kana = "ya"},
  {.key = B_SHFT|B_Z        , .kana = "ho"},
  {.key = B_SHFT|B_X        , .kana = "hi"},
  {.key = B_SHFT|B_C        , .kana = "wo"},
  {.key = B_SHFT|B_V        , .kana = ","},
  {.key = B_SHFT|B_B        , .kana = "nu"},
  {.key = B_SHFT|B_N        , .kana = "o"},
  {.key = B_SHFT|B_M        , .kana = "."SS_TAP(X_ENTER)},
  {.key = B_SHFT|B_COMM     , .kana = "mu"},
  {.key = B_SHFT|B_DOT      , .kana = "hu"},
  {.key = B_SHFT|B_SLSH     , .kana = "re"},

  // 濁音
  {.key = B_J|B_W           , .kana = "ba"},
  {.key = B_J|B_E           , .kana = "de"},
  {.key = B_J|B_R           , .kana = "ji"},
  {.key = B_F|B_U           , .kana = "za"},
  {.key = B_F|B_O           , .kana = "zu"},
  {.key = B_F|B_P           , .kana = "be"},
  {.key = B_J|B_A           , .kana = "ze"},
  {.key = B_J|B_S           , .kana = "gi"},
  {.key = B_J|B_D           , .kana = "do"},
  {.key = B_J|B_F           , .kana = "ga"},
  {.key = B_J|B_G           , .kana = "du"},
  {.key = B_F|B_H           , .kana = "gu"},
  {.key = B_F|B_L           , .kana = "du"},
  {.key = B_J|B_Z           , .kana = "bo"},
  {.key = B_J|B_X           , .kana = "bi"},
  {.key = B_J|B_C           , .kana = "ge"},
  {.key = B_J|B_V           , .kana = "go"},
  {.key = B_J|B_B           , .kana = "zo"},
  {.key = B_F|B_N           , .kana = "da"},
  {.key = B_F|B_DOT         , .kana = "bu"},

  // 半濁音
  {.key = B_M|B_W           , .kana = "pa"},
  {.key = B_M|B_X           , .kana = "pi"},
  {.key = B_V|B_DOT         , .kana = "pu"},
  {.key = B_V|B_P           , .kana = "pe"},
  {.key = B_M|B_Z           , .kana = "po"},

  // 小書き
  {.key = B_SHFT|B_V|B_J    , .kana = "la"},
  {.key = B_SHFT|B_V|B_K    , .kana = "li"},
  {.key = B_SHFT|B_V|B_L    , .kana = "lu"},
  {.key = B_SHFT|B_V|B_P    , .kana = "le"},
  {.key = B_SHFT|B_V|B_N    , .kana = "lo"},

  // 拗音
  {.key = B_SHFT|B_V|B_SCLN , .kana = "lya"},
  {.key = B_SHFT|B_V|B_O    , .kana = "lyu"},
  {.key = B_SHFT|B_V|B_I    , .kana = "lyo"},

  // 拗音同時
  {.key = B_S|B_SCLN        , .kana = "kya"},
  {.key = B_S|B_O           , .kana = "kyu"},
  {.key = B_S|B_I           , .kana = "kyo"},
  {.key = B_R|B_SCLN        , .kana = "sya"},
  {.key = B_R|B_O           , .kana = "syu"},
  {.key = B_R|B_I           , .kana = "syo"},
  {.key = B_G|B_SCLN        , .kana = "tya"},
  {.key = B_G|B_O           , .kana = "tyu"},
  {.key = B_G|B_I           , .kana = "tyo"},
  {.key = B_D|B_SCLN        , .kana = "nya"},
  {.key = B_D|B_O           , .kana = "nyu"},
  {.key = B_D|B_I           , .kana = "nyo"},
  {.key = B_X|B_SCLN        , .kana = "hya"},
  {.key = B_X|B_O           , .kana = "hyu"},
  {.key = B_X|B_I           , .kana = "hyo"},
  {.key = B_W|B_SCLN        , .kana = "mya"},
  {.key = B_W|B_O           , .kana = "myu"},
  {.key = B_W|B_I           , .kana = "myo"},
  {.key = B_E|B_SCLN        , .kana = "rya"},
  {.key = B_E|B_O           , .kana = "ryu"},
  {.key = B_E|B_I           , .kana = "ryo"},

  // 濁音拗音同時
  {.key = B_J|B_S|B_SCLN    , .kana = "gya"},
  {.key = B_J|B_S|B_O       , .kana = "gyu"},
  {.key = B_J|B_S|B_I       , .kana = "gyo"},
  {.key = B_J|B_R|B_SCLN    , .kana = "jya"},
  {.key = B_J|B_R|B_O       , .kana = "jyu"},
  {.key = B_J|B_R|B_I       , .kana = "jyo"},
  {.key = B_J|B_G|B_SCLN    , .kana = "dya"},
  {.key = B_J|B_G|B_O       , .kana = "dyu"},
  {.key = B_J|B_G|B_I       , .kana = "dyo"},
  {.key = B_J|B_X|B_SCLN    , .kana = "bya"},
  {.key = B_J|B_X|B_O       , .kana = "byu"},
  {.key = B_J|B_X|B_I       , .kana = "byo"},

  // 半濁音拗音同時
  {.key = B_M|B_X|B_SCLN    , .kana = "pya"},
  {.key = B_M|B_X|B_O       , .kana = "pyu"},
  {.key = B_M|B_X|B_I       , .kana = "pyo"},

  // 外来音
  {.key = B_Q|B_J           , .kana = "va"},
  {.key = B_Q|B_K           , .kana = "vi"},
  {.key = B_Q|B_L           , .kana = "vyu"},
  {.key = B_Q|B_P           , .kana = "ve"},
  {.key = B_Q|B_N           , .kana = "vo"},
  {.key = B_E|B_K           , .kana = "teli"},
  {.key = B_E|B_L           , .kana = "telu"},
  {.key = B_R|B_P           , .kana = "sye"},
  {.key = B_D|B_L           , .kana = "tolu"},
  {.key = B_G|B_P           , .kana = "tile"},
  {.key = B_L|B_K           , .kana = "uli"},
  {.key = B_L|B_P           , .kana = "ule"},
  {.key = B_L|B_N           , .kana = "ulo"},
  {.key = B_DOT|B_J         , .kana = "fa"},
  {.key = B_DOT|B_K         , .kana = "fi"},
  {.key = B_DOT|B_L         , .kana = "fyu"},
  {.key = B_DOT|B_P         , .kana = "fe"},
  {.key = B_DOT|B_N         , .kana = "fo"},

  // シフト外来音
  {.key = B_SHFT|B_L|B_J    , .kana = "tula"},
  {.key = B_SHFT|B_L|B_K    , .kana = "tuli"},
  {.key = B_SHFT|B_L|B_P    , .kana = "tule"},
  {.key = B_SHFT|B_L|B_N    , .kana = "tulo"},

  // 濁音外来音
  {.key = B_E|B_J|B_K       , .kana = "deli"},
  {.key = B_E|B_J|B_L       , .kana = "delu"},
  {.key = B_R|B_J|B_P       , .kana = "je"},
  {.key = B_D|B_J|B_L       , .kana = "dolu"},
  {.key = B_G|B_J|B_P       , .kana = "dile"},

  // enter
  {.key = B_V|B_M           , .kana = SS_TAP(X_ENTER)},
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
  naginata_keymap bngmap; // PROGMEM buffer

  bool douji = false; // 同時押しか連続押しか
  uint32_t keycomb = 0UL; // 同時押しの状態を示す。32bitの各ビットがキーに対応する。

  if (ng_shift) keycomb |= B_SHFT; // シフトキー状態を反映

  for (int i = 0; i < ng_chrcount; i++) {
    keycomb |= ng_key[ninputs[i] - NG_Q]; // バッファにあるキー状態を合成する
  }

  switch (keycomb) {
    // send_stringできないキーはここで定義
    case B_F|B_G:
      naginata_off();
      break;
    default:
      // キーから仮名に変換して出力する。
      // 同時押しの場合
      for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
        memcpy_P(&bngmap, &ngmap[i], sizeof bngmap);
        if (keycomb == bngmap.key) {
          douji = true;
          send_string(bngmap.kana);
          break;
        }
      }
      // 連続押しの場合
      if (!douji) {
        for (int j = 0; j < ng_chrcount; j++) {
          keycomb = ng_key[ninputs[j] - NG_Q];
          if (ng_shift) keycomb |= B_SHFT; // シフトキー状態を反映
          for (int i = 0; i < sizeof ngmap / sizeof bngmap; i++) {
            memcpy_P(&bngmap, &ngmap[i], sizeof bngmap);
            if (keycomb == bngmap.key) {
              send_string(bngmap.kana);
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
        case NG_D:
        case NG_F:
          n_editr++;
          if (n_editr >= 2) {
            naginata_edit_right_on();
          }
          break;
        case NG_J:
        case NG_K:
          n_editl++;
          if (n_editl >= 2) {
            naginata_edit_left_on();
          }
          break;
      }
    } else {
      switch (keycode) {
        case NG_D:
        case NG_F:
        case NG_J:
        case NG_K:
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
      case NG_Q ... NG_SLSH:
        ninputs[ng_chrcount] = keycode; // キー入力をバッファに貯める
        ng_chrcount++;
        ng_space = false;
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
      case NG_Q ... NG_SLSH:
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
      case UP10:
        repeatkey(KC_UP, 10);
        return false;
        break;
      case DOWN10:
        repeatkey(KC_DOWN, 10);
        return false;
        break;
      }
  }
  return true;
}
#endif
