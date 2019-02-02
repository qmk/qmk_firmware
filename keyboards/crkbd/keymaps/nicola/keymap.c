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
#define _NICOLA 10 // 親指シフトレイヤー
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
  NICOLA,
  NLSHFT, NRSHFT // 親指シフトキー
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
#define KC_NLSHFT NLSHFT // 親指シフトキー
#define KC_NRSHFT NRSHFT // 親指シフトキー
#define KC_QWERTY QWERTY
#define KC_EUCALYN EUCALYN
#define KC_EISU EISU
#define KC_NICOLA NICOLA
#define KC_RESET RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  RGUI,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,  LSFT,   SPC,      ENT,  RSFT, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_EUCALYN] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,  COMM,   DOT,  SCLN,                      M,     R,     D,     Y,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     O,     E,     I,     U,                      G,     T,     K,     S,     N,  RGUI,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     F,                      B,     H,     J,     L,  SLSH,  RALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,  LSFT,   SPC,      ENT,  RSFT, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_NICOLA] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____,NLSHFT, _____,    _____,NRSHFT, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             !      @      #      $      %                       *                           +       
      _____,  EXLM,    AT,  HASH,   DLR,  PERC,                   ASTR,     7,     8,     9,  PLUS,   DEL,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             ^      &      '      "      ~                       /                           -       
      XXXXX,  CIRC,  AMPR,  QUOT,  DQUO,  TILD,                   SLSH,     4,     5,     6,  MINS,  EISU,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             \      |      `     _       \                                                   =                           
      XXXXX,  BSLS,  PIPE,   GRV,  UNDS,  JYEN,                      0,     1,     2,     3,   EQL,NICOLA,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX,   SPC,      ENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  ),

  [_RAISE] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //                           <      >                                                                          
      _____, XXXXX, XXXXX,    LT,    GT, XXXXX,                  XXXXX, XXXXX,    UP, XXXXX,  PGUP,   DEL,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             (      )      {      }                                                                   
      XXXXX,  LPRN,  RPRN,  LCBR,  RCBR, XXXXX,                  XXXXX,  LEFT,  DOWN,  RGHT,  PGDN,  EISU,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //                           [      ]                                                     
      XXXXX, XXXXX, XXXXX,  LBRC,  RBRC, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,NICOLA,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX,   SPC,      ENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  ),

  [_ADJUST] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
      XXXXX,QWERTY,  WAKE, XXXXX, RESET, XXXXX,                  XXXXX, XXXXX,  VOLU, XXXXX,  BRIU, XXXXX,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
      XXXXX, XXXXX, XXXXX,EUCALYN,XXXXX, XXXXX,                  XXXXX,  MRWD,  VOLD,  MFFD,  BRID, XXXXX,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
      XXXXX, XXXXX,  SLEP, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX,  MPLY, XXXXX, XXXXX, XXXXX,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX,   SPC,      ENT, XXXXX, RAISE \
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

// 親指シフト
static bool is_nicola = false; // 親指シフトモードかどうか
static uint8_t ncl_chrcount = 0; // 文字キー入力のカウンタ (シフトキーを除く)
static uint8_t ncl_keycount = 0; // シフトキーも含めた入力のカウンタ
static bool ncl_rshift = false; // 右シフトキーの状態  
static bool ncl_lshift = false; // 左シフトキーの状態
static bool is_modifier = false; // modifierの状態

// 文字入力バッファ
static uint16_t ninputs[5];

// NICOLA配列のテーブル
typedef struct {
  char t[4]; // 単独
  char l[4]; // 左シフト
  char r[4]; // 右シフト
} ncl_keymap;

// NICOLA on QWERTY
const ncl_keymap nmap[] = {
  [KC_Q]    = {.t = ".",  .l = "la",  .r = ""},   
  [KC_W]    = {.t = "ka", .l = "e",   .r = "ga"}, 
  [KC_E]    = {.t = "ta", .l = "ri",  .r = "da"}, 
  [KC_R]    = {.t = "ko", .l = "lya", .r = "go"}, 
  [KC_T]    = {.t = "sa", .l = "re",  .r = "za"}, 

  [KC_Y]    = {.t = "ra", .l = "pa",  .r = "yo"}, 
  [KC_U]    = {.t = "ti", .l = "di",  .r = "ni"}, 
  [KC_I]    = {.t = "ku", .l = "gu",  .r = "ru"}, 
  [KC_O]    = {.t = "tu", .l = "du",  .r = "ma"}, 
  [KC_P]    = {.t = ",",  .l = "pi",  .r = "le"}, 

  [KC_A]    = {.t = "u",  .l = "wo",  .r = "vu"},
  [KC_S]    = {.t = "si", .l = "a",   .r = "zi"}, 
  [KC_D]    = {.t = "te", .l = "na",  .r = "de"}, 
  [KC_F]    = {.t = "ke", .l = "lyu", .r = "ge"}, 
  [KC_G]    = {.t = "se", .l = "mo",  .r = "ze"}, 

  [KC_H]    = {.t = "ha", .l = "ba",  .r = "mi"}, 
  [KC_J]    = {.t = "to", .l = "do",  .r = "o"},  
  [KC_K]    = {.t = "ki", .l = "gi",  .r = "no"}, 
  [KC_L]    = {.t = "i",  .l = "po",  .r = "lyo"},
  [KC_SCLN] = {.t = "nn", .l = "",    .r = "ltu"},

  [KC_Z]    = {.t = ".",  .l = "lu",  .r = ""},   
  [KC_X]    = {.t = "hi", .l = "-",   .r = "bi"}, 
  [KC_C]    = {.t = "su", .l = "ro",  .r = "zu"}, 
  [KC_V]    = {.t = "hu", .l = "ya",  .r = "bu"}, 
  [KC_B]    = {.t = "he", .l = "li",  .r = "be"}, 

  [KC_N]    = {.t = "me", .l = "pu",  .r = "nu"}, 
  [KC_M]    = {.t = "so", .l = "zo",  .r = "yu"}, 
  [KC_COMM] = {.t = "ne", .l = "pe",  .r = "mu"}, 
  [KC_DOT]  = {.t = "ho", .l = "bo",  .r = "wa"}, 
  [KC_SLSH] = {.t = "/",  .l = "",    .r = "lo"}, 
};

void ncl_type(void);
void ncl_clear(void);

// シフトキーの状態に応じて文字をPCへ送る
void ncl_type(void) {
  for (int i = 0; i < ncl_chrcount; i++) {
    if (ninputs[i] == 0) break;
    if (ncl_lshift) {
      send_string(nmap[ninputs[i]].l);
    } else if (ncl_rshift) {
      send_string(nmap[ninputs[i]].r);
    } else {
      send_string(nmap[ninputs[i]].t);
    }
  }
  ncl_clear();
}

// バッファをクリアする
void ncl_clear(void) {
  for (int i = 0; i < 5; i++) {
    ninputs[i] = 0;
  }
  ncl_chrcount = 0;
  ncl_keycount = 0;
  ncl_lshift = false;
  ncl_rshift = false;
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
        layer_off(_NICOLA);
        register_code(KC_LANG2); // Mac
        // register_code(KC_MHEN); // Win
        is_nicola = false;
        unregister_code(KC_LANG2); // Mac
        // unregister_code(KC_MHEN); // Win
      }
      return false;
      break;
    case NICOLA:
      if (record->event.pressed) {
        layer_on(_NICOLA);
        register_code(KC_LANG1); // Mac
        // register_code(KC_HENK); // Win
        is_nicola = true;
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
          layer_off(_NICOLA);
          register_code(KC_LANG2); // Mac
          // register_code(KC_MHEN); // Win
          is_nicola = false;
          unregister_code(KC_LANG2); // Mac
          // unregister_code(KC_HENK); // Win
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
          layer_on(_NICOLA);
          register_code(KC_LANG1); // Mac
          // register_code(KC_HENK); // Win
          is_nicola = true;
          unregister_code(KC_LANG1); // Mac
          // unregister_code(KC_HENK); // Win
          raise_pressed = false;
        }
      }
      return false;
      break;
    default:
      lower_pressed = false;
      raise_pressed = false;
  }

  // 親指シフトの処理　ここから

  // modifierが押されているか
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

  if (is_nicola & !is_modifier) {
    if (record->event.pressed) {
      switch (keycode) {
        case NLSHFT: // 親指シフトキー
          ncl_lshift = true;
          ncl_keycount++;
          if (ncl_keycount > 1) ncl_type();
          return false;
          break;
        case NRSHFT:
          ncl_rshift = true;
          ncl_keycount++;
          if (ncl_keycount > 1) ncl_type();
          return false;
          break;
        case KC_A ... KC_Z: // 親指シフト処理するキー
        case KC_SLSH:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
          ninputs[ncl_chrcount] = keycode;
          ncl_chrcount++;
          ncl_keycount++;
          if (ncl_keycount > 1) ncl_type();
          return false;
          break;
        default: // 親指シフトに関係ないキー
          ncl_clear();
          break;
      }

    } else { // key release
      switch (keycode) {
        case NLSHFT: // 親指シフトキー
          ncl_lshift = false;
          if (ncl_keycount > 0) ncl_type();
          return false;
          break;
        case NRSHFT:
          ncl_rshift = false;
          if (ncl_keycount > 0) ncl_type();
          return false;
          break; 
        case KC_A ... KC_Z: // 親指シフト処理するキー
        case KC_SLSH:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
          if (ncl_keycount > 0) ncl_type();
          return false;
          break;
      }
    }
  }
  // 親指シフト処理 ここまで

  return true;
}

