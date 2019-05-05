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
#define _EUCALYN 0
#define _QWERTY 1
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
  NAGINATA,
  NLSHFT, NRSHFT, // シフトキー
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
#define KC_NLSHFT NLSHFT // シフトキー
#define KC_NRSHFT NRSHFT // シフトキー
#define KC_QWERTY QWERTY
#define KC_EUCALYN EUCALYN
#define KC_EISU EISU
#define KC_NAGINATA NAGINATA
#define KC_RESET RESET
#define KC_ABLS LALT(KC_BSLS)
#define KC_CMDENT  CMD_T(KC_ENT)
#define KC_CMDSPC  CMD_T(KC_SPC)
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
                                  LOWER,  LSFT,CTLSPC,   CMDENT,  RSFT, RAISE \
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
                                  LOWER,  LSFT,CTLSPC,   CMDENT,  RSFT, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_NAGINATA] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, _____, _____, _____, _____,  LEFT,                   RGHT, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____,NLSHFT, _____,    _____,NLSHFT, _____ \
                              //`--------------------'  `--------------------'
  ),

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
      XXXXX, XXXXX, XXXXX,  LBRC,  RBRC, XXXXX,                  XXXXX,  PGDN, XXXXX, XXXXX, XXXXX,NAGINATA,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX,CTLSPC,   CMDENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  ),

  [_ADJUST] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LHUI,  LHUD,  WAKE, XXXXX, RESET, UNDGL,                   LTOG, XXXXX,  VOLU, XXXXX,  BRIU, XXXXX,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LSAI,  LSAD, XXXXX, XXXXX, XXXXX, XXXXX,                   LMOD,  MRWD,  VOLD,  MFFD,  BRID, XXXXX,\
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

static bool is_naginata = false; // 薙刀式入力モードかどうか
static uint8_t ng_chrcount = 0; // 文字キー入力のカウンタ (シフトキーを除く)
static bool is_modifier = false; // modifierの状態
static bool ng_shift = false; // シフトキーの状態

#define NGBUFFER 5 // バッファのサイズ

// キー単体押しから出力が変わる同時押しのキーのフラグ
// ここから同時押しされているキーの種類を分類する
#define BSHIFT (1UL<<0) // シフト
#define BLDK   (1UL<<1) // 濁音に変化させるキー左
#define BRDK   (1UL<<2) // 濁音に変化させるキー右
#define BLHD   (1UL<<3) // 半濁音に変化させるキー左
#define BRHD   (1UL<<4) // 半濁音に変化させるキー右
#define BLHS   (1UL<<5) // 左半分にあるキー
#define BRHS   (1UL<<6) // 右半分にあるキー
#define BYYA   (1UL<<7) // 拗音ゃに変化させるキー
#define BYYU   (1UL<<8) // 拗音ゅに変化させるキー
#define BYYO   (1UL<<9) // 拗音ょに変化させるキー
#define BGA    (1UL<<10) // 外来音ぁに変化させるキー
#define BGI    (1UL<<11) // 外来音ぃに変化させるキー
#define BGU    (1UL<<12) // 外来音ぅに変化させるキー
#define BGE    (1UL<<13) // 外来音ぇに変化させるキー
#define BGO    (1UL<<14) // 外来音ぉに変化させるキー

// 文字入力バッファ
static uint16_t ninputs[NGBUFFER];

// 関数宣言
void naginata_type(void);
void ng_clear(void);
bool ng_remove(uint16_t kc);
void ng_output(char[NGBUFFER][29][5], uint16_t, int);

// NAGINATA配列のテーブル
// NAGINATA on EUCALYN
const char PROGMEM ngmap[][29][5] = {
  //           単独  シフト  濁音  半濁音  拗音    拗音同時             濁音拗音同時　          半濁音拗音同時         外来音                             外来音シフト                         外来音濁音
  [KC_Q]    = {"vu" , ""  , "va", ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "va" , "vi" , "vulu", "ve", "vo" , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_W]    = {"ha" , "mi", "ba", "pa", ""   , "mya", "myu", "myo", ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_COMM] = {"te" , "ri", "de", ""  , ""   , "rya", "ryu", "ryo", ""   , ""   , ""   , ""   , ""   , ""   , ""   , "teli", "telu", "" , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "deli", "delu", "" , ""   }, 
  [KC_DOT]  = {"si" , "me", "ji", ""  , ""   , "sya", "syu", "syo", "jya", "jyu", "jyo", ""   , ""   , ""   , ""   , ""   , ""   , "sye", ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "je" , ""   }, 

  [KC_A]    = {"ro" , "se", "ze", ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   },
  [KC_O]    = {"ki" , "ne", "gi", ""  , ""   , "kya", "kyu", "kyo", "gya", "gyu", "gyo", ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_E]    = {"to" , "ni", "do", ""  , ""   , "nya", "nyu", "nyo", ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "tolu", ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "dolu", ""  , ""   }, 
  [KC_I]    = {"ka" , "ma", "ga", ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_U]    = {"ltu", "ti", "di", ""  , ""   , "tya", "tyu", "tyo", "dya", "dyu", "dyo", ""   , ""   , ""   , ""   , ""   , ""   , "tile", ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "dile", ""  }, 

  [KC_Z]    = {"ho" , ""  , "bo", "po", ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_X]    = {"hi" , ""  , "bi", "pi", ""   , "hya", "hyu", "hyo", "bya", "byu", "byo", "pya", "pyu", "pyo", ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_C]    = {"ke" , "wo", "ge", ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_V]    = {"ko" , "," , "go", ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_F]    = {"so" , "nu", "zo", ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 

  [KC_R]    = {"BS" , "sa", "za", ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_D]    = {"ru" , "yo", ""  , ""  , "lyo", ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_Y]    = {"su" , "yu", "zu", ""  , "lyu", ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_P]    = {"he" , "e" , "be", "pe", "le" , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 

  [KC_G]    = {"ku" , "wa", "gu", ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_T]    = {"a"  , "no", ""  , ""  , "la" , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   },  
  [KC_K]    = {"i"  , "mo", ""  , ""  , "li" , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_S]    = {"u"  , "tu", "du", ""  , "lu" , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "wi" , ""   , "we" , "wo" , "tula" , "tuli" , "" , "tule" , "tulo" , ""   , ""   , ""   , ""   , ""   },
  [KC_N]    = {"-"  , "ya", ""  , ""  , "lya", ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   },

  [KC_B]    = {"ta" , "o" , "da", ""  , "lo" , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_H]    = {"na" , "." , ""  , ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_J]    = {"nn" , "mu", ""  , ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_L]    = {"ra" , "hu", "bu", "pu", ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "fa" , "fi" , "fyu", "fe" , "fo" , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
  [KC_SLSH] = {"re" , "?" , ""  , ""  , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   }, 
};

// 各キーへフラグを割り当てる。同時押しで処理が必要なキー。
const uint16_t ngcomb[] = {
  //          左右  濁音半濁音 拗音 外来音同時
  //          NLHS | BLDK | BYYA | BGA
  [KC_Q]    = BLHS                     ,   
  [KC_W]    = BLHS                     , 
  [KC_COMM] = BLHS                     , 
  [KC_DOT]  = BLHS                     , 

  [KC_A]    = BLHS                     ,
  [KC_O]    = BLHS                     ,
  [KC_E]    = BLHS                     , 
  [KC_I]    = BLHS | BLDK              , 
  [KC_U]    = BLHS                     , 

  [KC_Z]    = BLHS                     ,   
  [KC_X]    = BLHS                     , 
  [KC_C]    = BLHS                     , 
  [KC_V]    = BLHS | BLHD              , 
  [KC_F]    = BLHS                     , 

  [KC_R]    = BRHS                     , 
  [KC_D]    = BRHS        | BYYO       , 
  [KC_Y]    = BRHS        | BYYU       , 
  [KC_P]    = BRHS               | BGE , 

  [KC_G]    = BRHS                     , 
  [KC_T]    = BRHS | BRDK        | BGA ,  
  [KC_K]    = BRHS               | BGI , 
  [KC_S]    = BRHS               | BGU ,
  [KC_N]    = BRHS        | BYYA       ,

  [KC_B]    = BRHS               | BGO , 
  [KC_H]    = BRHS | BRHD              , 
  [KC_J]    = BRHS                     , 
  [KC_L]    = BRHS                     , 
  [KC_SLSH] = BRHS                     , 
};

// キーが押されているかどうかの判定マクロ
#define KEYON(KC) ((modflag & (KC)) > 0)

// キー入力を文字に変換して出力する
void naginata_type(void) {
  uint16_t modflag = 0UL; // 押されているキー状態
  if (ng_shift) modflag |= BSHIFT; // シフトキー状態を反映

  char tngmap[NGBUFFER][29][5]; // メモリ上のキーマップ
  for (int i = 0; i < ng_chrcount; i++) {
    modflag |= ngcomb[ninputs[i]]; // バッファにあるキー状態を合成する
    // 必要なキーマップだけメモリにロードする
    memcpy_P(&tngmap[i], &ngmap[ninputs[i]], sizeof(tngmap[i])); 
  }

  if (ng_chrcount > 2) { // 3キー同時押し
    if (KEYON(BRDK) & KEYON(BYYA) & KEYON(BLHS)) { // 濁音拗音同時 じゃ
      ng_output(tngmap, BYYA, 8);
    } else if (KEYON(BRDK) & KEYON(BYYU) & KEYON(BLHS)) { // 濁音拗音同時 じゅ
      ng_output(tngmap, BYYU, 9);
    } else if (KEYON(BRDK) & KEYON(BYYO) & KEYON(BLHS)) { // 濁音拗音同時 じょ
      ng_output(tngmap, BYYO, 10);
    } else if (KEYON(BRHD) & KEYON(BYYA) & KEYON(BLHS)) { // 半濁音拗音同時 ぴゃ
      ng_output(tngmap, BYYA, 11);
    } else if (KEYON(BRHD) & KEYON(BYYU) & KEYON(BLHS)) { // 半濁音拗音同時 ぴゅ
      ng_output(tngmap, BYYU, 12);
    } else if (KEYON(BRHD) & KEYON(BYYO) & KEYON(BLHS)) { // 半濁音拗音同時 ぴょ
      ng_output(tngmap, BYYO, 13);
    // } else if (KEYON(BRDK) & KEYON(BGA) & KEYON(BLHS)) { // 外来音濁音同時
    //   ng_output(tngmap, BGA, 24);
    } else if (KEYON(BRDK) & KEYON(BGI) & KEYON(BLHS)) { // 外来音濁音同時 ディ
      ng_output(tngmap, BGI, 25);
    } else if (KEYON(BRDK) & KEYON(BGU) & KEYON(BLHS)) { // 外来音濁音同時 デゥ
      ng_output(tngmap, BGU, 26);
    } else if (KEYON(BRDK) & KEYON(BGE) & KEYON(BLHS)) { // 外来音濁音同時 ジェ
      ng_output(tngmap, BGE, 27);
    // } else if (KEYON(BRDK) & KEYON(BGO) & KEYON(BLHS)) { // 外来音濁音同時
    //   ng_output(tngmap, BGO, 28);
    }
  } else if (ng_chrcount > 1) { // 2キー同時押し
    if (KEYON(BSHIFT) & KEYON(BLHD) & KEYON(BRHS)) { // 拗音単体 ゃ
      ng_output(tngmap, BLHD, 4);
    } else if (KEYON(BSHIFT) & KEYON(BGA)) { // 外来音シフト同時 つぁ
      ng_output(tngmap, BGA, 19);
    } else if (KEYON(BSHIFT) & KEYON(BGI)) { // 外来音シフト同時 つぃ
      ng_output(tngmap, BGI, 20);
    // } else if (KEYON(BSHIFT) & KEYON(BGU)) { // 外来音シフト同時 つぅ
    //   ng_output(tngmap, BGU, 21);
    } else if (KEYON(BSHIFT) & KEYON(BGE)) { // 外来音シフト同時 つぇ
      ng_output(tngmap, BGE, 22);
    } else if (KEYON(BSHIFT) & KEYON(BGO)) { // 外来音シフト同時 つぉ
      ng_output(tngmap, BGO, 23);
    } else if (KEYON(BLDK) && KEYON(BRDK)) { // が
      send_string("ga");
      ng_clear();
    } else if (KEYON(BSHIFT) && KEYON(BLHD) && KEYON(BRDK)) { // ぁ
      send_string("la");
      ng_clear();
    } else if (KEYON(BLHD) && KEYON(BRDK)) { // ご
      send_string("go");
      ng_clear();
    } else if (KEYON(BLHD) && KEYON(BRHD)) { // enter
      register_code(KC_ENT);
      unregister_code(KC_ENT);
      ng_clear();
    } else if ((KEYON(BLDK) & KEYON(BRHS)) || (KEYON(BRDK) & KEYON(BLHS))) { // 濁音
      ng_output(tngmap, BLDK | BRDK, 2);
    } else if ((KEYON(BLHD) & KEYON(BRHS)) || (KEYON(BRHD) & KEYON(BLHS))) { // 半濁音
      ng_output(tngmap, BLHD | BRHD, 3);
    } else if (KEYON(BYYA) & KEYON(BLHS)) { // 拗音同時 しゃ
      ng_output(tngmap, BYYA, 5);
    } else if (KEYON(BYYU) & KEYON(BLHS)) { // 拗音同時 しゅ
      ng_output(tngmap, BYYU, 6);
    } else if (KEYON(BYYO) & KEYON(BLHS)) { // 拗音同時 しょ
      ng_output(tngmap, BYYO, 7);
    } else if (KEYON(BGA)) { // 外来音同時 ファ
      ng_output(tngmap, BGA, 14);
    } else if (KEYON(BGI)) { // 外来音同時 フィ
      ng_output(tngmap, BGI, 15);
    } else if (KEYON(BGU)) { // 外来音同時 フュ
      ng_output(tngmap, BGU, 16);
    } else if (KEYON(BGE)) { // 外来音同時 フェ
      ng_output(tngmap, BGE, 17);
    } else if (KEYON(BGO)) { // 外来音同時 フォ
      ng_output(tngmap, BGO, 18);
    }
  } else { // キー単独押し (シフト押しながらを含む)
    if (KEYON(BSHIFT)) { // シフトを押しながら
      send_string(tngmap[0][1]);
    } else { // 単独押し
      if (ninputs[0] == KC_R) { // BSキーの変換
        register_code(KC_BSPC);
        unregister_code(KC_BSPC);
      } else { // 一般キー
        send_string(tngmap[0][0]);
      }
    }
  }

  ng_clear(); // バッファを空にする
}

// マップのn列目を出力する
// skipのキーは出力しない。例えば濁音キーとして使う「か」など。
void ng_output(char tngmap[NGBUFFER][29][5], uint16_t skip, int n) {
  for (int i = 0; i < ng_chrcount; i++) {
    if ((ngcomb[ninputs[i]] & skip) == 0) {
      send_string(tngmap[i][n]);
    }
  }  
}

// バッファをクリアする
void ng_clear(void) {
  for (int i = 0; i < NGBUFFER; i++) {
    ninputs[i] = 0;
  }
  ng_chrcount = 0;
}

// 薙刀式入力のコード1 ここまで

void update_led(void);

void update_led() {
  // if (layer_state_is(_LOWER) && !isLeftHand) {
  //   // rgblight_setrgb_at(0, 0, 200, 7);
  //   rgblight_sethsv_at(240, 100, 255, 10);
  //   rgblight_sethsv_at(240, 100, 255, 11);
  //   rgblight_sethsv_at(240, 100, 255, 12);
  //   rgblight_sethsv_at(240, 100, 255, 15);
  //   rgblight_sethsv_at(240, 100, 255, 16);
  //   rgblight_sethsv_at(240, 100, 255, 17);
  //   rgblight_sethsv_at(240, 100, 255, 18);
  //   rgblight_sethsv_at(240, 100, 255, 19);
  //   rgblight_sethsv_at(240, 100, 255, 20);
  // }
  // if (layer_state_is(_RAISE) && !isLeftHand) {
  //   rgblight_sethsv_at(330, 100, 255, 11);
  //   rgblight_sethsv_at(330, 100, 255, 16);
  //   rgblight_sethsv_at(330, 100, 255, 17);
  //   rgblight_sethsv_at(330, 100, 255, 19);
  // }
  // if (!layer_state_is(_LOWER) && !layer_state_is(_RAISE)) {
  //   rgblight_sethsv_range(0, 0, 0, 6, 27);
  // }
  // if (is_naginata) {
  //   rgblight_sethsv_at(270, 200, 255, 6);
  //   rgblight_sethsv_at(270, 200, 255, 13);
  //   rgblight_sethsv_at(270, 200, 255, 14);
  // } else {
  //   rgblight_sethsv_at(0, 0, 0, 6);
  //   rgblight_sethsv_at(0, 0, 0, 13);
  //   rgblight_sethsv_at(0, 0, 0, 14);
  // }
  // if (underglow) {
  //   rgblight_sethsv_range(270, 200, 255, 0, 6);
  // } else {
  //   rgblight_sethsv_range(270, 200, 0, 0, 6);
  // }
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
        // register_code(KC_MHEN); // Win
        is_naginata = false;
        unregister_code(KC_LANG2); // Mac
        // unregister_code(KC_MHEN); // Win
      }
      return false;
      break;
    case NAGINATA:
      if (record->event.pressed) {
        layer_on(_NAGINATA);
        register_code(KC_LANG1); // Mac
        // register_code(KC_HENK); // Win
        is_naginata = true;
        unregister_code(KC_LANG1); // Mac
        // unregister_code(KC_HENK); // Win
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
          // register_code(KC_MHEN); // Win
          is_naginata = false;
          unregister_code(KC_LANG2); // Mac
          // unregister_code(KC_MHEN); // Win
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
          // register_code(KC_HENK); // Win
          is_naginata = true;
          unregister_code(KC_LANG1); // Mac
          // unregister_code(KC_HENK); // Win
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

  // 薙刀式入力の処理2　ここから

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
        case NLSHFT: // シフトキー
          ng_shift = true;
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
        case NLSHFT: // シフトキー
          ng_shift = false;
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
  // 薙刀式入力処理2 ここまで

  return true;
}

