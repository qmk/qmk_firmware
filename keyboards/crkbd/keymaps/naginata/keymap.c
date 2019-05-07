#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

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
#define _QWERTY 0
#define _EUCALYN 1
#define _NAGINATA 10 // 薙刀式入力レイヤー
#define _LOWER 11
#define _RAISE 12
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EUCALYN,
  EISU,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  KANA2,
  NGSHFT, // 薙刀式シフトキー
  UNDGL
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUITB GUI_T(KC_TAB)
#define KC_NGSHFT NGSHFT // シフトキー
#define KC_QWERTY QWERTY
#define KC_EUCALYN EUCALYN
#define KC_EISU EISU
#define KC_KANA2 KANA2
#define KC_RESET RESET
#define KC_ABLS LALT(KC_BSLS)
#define KC_CMDENT  CMD_T(KC_ENT)
#define KC_SFTSPC  LSFT_T(KC_SPC)
#define KC_CTLSPC  CTL_T(KC_SPC)
#define KC_ALTSPC  ALT_T(KC_SPC)
#define KC_CTLBS   CTL_T(KC_BSPC)
#define KC_CTLENT  CTL_T(KC_ENT)
#define KC_UNDGL UNDGL

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,   ENT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,SFTSPC,CTLSPC,   CMDENT,SFTSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_EUCALYN] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,  COMM,   DOT,  SCLN,                      M,     R,     D,     Y,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     O,     E,     I,     U,                      G,     T,     K,     S,     N,   ENT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     F,                      B,     H,     J,     L,  SLSH,  RALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,SFTSPC,CTLSPC,   CMDENT,SFTSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

// 薙刀式キーマップ

  [_NAGINATA] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,     Q,     W,     E,     R,  LEFT,                   RGHT,     U,     I,     O,     P, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____,NGSHFT, _____,    _____,NGSHFT, _____ \
                              //`--------------------'  `--------------------'
  ),

// 薙刀式キーマップ

  [_LOWER] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             !      @      #      $      %                       /                           -       
        ESC,  EXLM,    AT,  HASH,   DLR,  PERC,                   SLSH,     7,     8,     9,  MINS,   DEL,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             ^      &      '      "      ~                       *                           +       
      XXXXX,  CIRC,  AMPR,  QUOT,  DQUO,  TILD,                   ASTR,     4,     5,     6,  PLUS,   EQL,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             \      |      `     _       ¥                                                   .                           
      XXXXX,  ABLS,  PIPE,   GRV,  UNDS,  BSLS,                      0,     1,     2,     3,   DOT,   ENT,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX,CTLSPC,   CMDENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  ),

  [_RAISE] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //                           <      >                                                                          
      _____, XXXXX, XXXXX,    LT,    GT, XXXXX,                  XXXXX,  PGUP,    UP, XXXXX,  PGUP,   DEL,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             (      )      {      }                                                                   
      XXXXX,  LPRN,  RPRN,  LCBR,  RCBR, XXXXX,                  XXXXX,  LEFT,  DOWN,  RGHT,  PGDN,  EISU,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //                           [      ]                                                     
      XXXXX, XXXXX, XXXXX,  LBRC,  RBRC, XXXXX,                  XXXXX,  PGDN, XXXXX, XXXXX, XXXXX,  KANA2,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX,CTLSPC,   CMDENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  ),

  [_ADJUST] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LHUI,  LHUD,  WAKE, XXXXX, RESET, UNDGL,                   LTOG, XXXXX,  VOLU, XXXXX,  BRIU, QWERTY,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LSAI,  LSAD, XXXXX, XXXXX, XXXXX, XXXXX,                   LMOD,  MRWD,  VOLD,  MFFD,  BRID, EUCALYN,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LVAI,  LVAD,  SLEP, XXXXX, XXXXX, XXXXX,                   LRST, XXXXX,  MPLY, XXXXX, XXXXX, XXXXX,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX,CTLSPC,   CMDENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

static bool underglow = false;

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

// NAGINATA配列のテーブル
// NAGINATA on EUCALYN

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

// キー組み合わせのマップ。ng_kanaと対応する。
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
    case B_U:
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

void update_led(void);

void update_led() {
  if (layer_state_is(_LOWER) && !isLeftHand) {
    // rgblight_setrgb_at(0, 0, 200, 7);
    rgblight_sethsv_at(200, 100, 255, 10);
    rgblight_sethsv_at(200, 100, 255, 11);
    rgblight_sethsv_at(200, 100, 255, 12);
    rgblight_sethsv_at(200, 100, 255, 15);
    rgblight_sethsv_at(200, 100, 255, 16);
    rgblight_sethsv_at(200, 100, 255, 17);
    rgblight_sethsv_at(200, 100, 255, 18);
    rgblight_sethsv_at(200, 100, 255, 19);
    rgblight_sethsv_at(200, 100, 255, 20);
  }
  if (layer_state_is(_RAISE) && !isLeftHand) {
    rgblight_sethsv_at(200, 100, 255, 11);
    rgblight_sethsv_at(200, 100, 255, 16);
    rgblight_sethsv_at(200, 100, 255, 17);
    rgblight_sethsv_at(200, 100, 255, 19);
  }
  if (!layer_state_is(_LOWER) && !layer_state_is(_RAISE)) {
    rgblight_sethsv_range(0, 0, 0, 6, 27);
  }
  if (is_naginata) {
    rgblight_sethsv_at(200, 200, 255, 6);
    rgblight_sethsv_at(200, 200, 255, 13);
    rgblight_sethsv_at(200, 200, 255, 14);
  } else {
    rgblight_sethsv_at(0, 0, 0, 6);
    rgblight_sethsv_at(0, 0, 0, 13);
    rgblight_sethsv_at(0, 0, 0, 14);
  }
  if (underglow) {
    rgblight_sethsv_range(200, 200, 255, 0, 6);
  } else {
    rgblight_sethsv_range(200, 200, 0, 0, 6);
  }
}

static bool lower_pressed = false;
static bool raise_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case UNDGL:
      if (record->event.pressed) {
        underglow = !underglow;
      }
      update_led();
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case EUCALYN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_EUCALYN);
      }
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        layer_off(_NAGINATA);
        register_code(KC_LANG2); // Mac
        register_code(KC_MHEN); // Win
        is_naginata = false;
        unregister_code(KC_LANG2); // Mac
        unregister_code(KC_MHEN); // Win
      }
      return false;
      break;
    case KANA2:
      if (record->event.pressed) {
        layer_on(_NAGINATA);
        register_code(KC_LANG1); // Mac
        register_code(KC_HENK); // Win
        is_naginata = true;
        unregister_code(KC_LANG1); // Mac
        unregister_code(KC_HENK); // Win
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
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }

  switch (keycode) {
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
      update_led();
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
      update_led();
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

