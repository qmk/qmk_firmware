#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
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
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  AQOURS, //サンシャインぴっかぴかモード
  ELEC_BOARD //電光掲示板
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
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)
#define KC_AQOURS AQOURS
#define KC_ELEC_BOARD ELEC_BOARD
#ifdef RGBLIGHT_ENABLE
//9色に変化するLEDのHSV各パラメータ
//千歌,梨子,果南,ダイヤ,曜,善子,花丸,マリ、ルビィ
int aqours_h[] = { 26, 340, 150,   0, 199, 220,  53, 265, 322};
int aqours_s[] = {255, 165, 255, 255, 255, 350, 255, 255, 255};
int aqours_v[] = {255, 255, 255, 255, 255, 255, 255, 255, 255};
const int NEXT_COLOR_TIME = 2400; //次の色に切り替わるまでの時間
const int NEXT_CHANGE_TARGET_TIME = 150; //次のキーに色が伝播するまでの時間
bool aqours_mode = false;
int aqours_next_color_timer_count = 0;
int aqours_num  = 0;
int target_col = 0;
static uint16_t color_timer, change_target_timer;

//■    ■■■  ■   ■  ■■■    ■    ■   ■   ■  ■■■
//■    ■ ■   ■ ■   ■■     ■    ■    ■ ■   ■■
//■■■  ■■■    ■    ■■■    ■■■  ■     ■    ■■■
#define ELECTRIC_BOARD_LENGTH 47
bool electric_board_mode = false;
int electric_board_data[3][ELECTRIC_BOARD_LENGTH] = {
  {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,},
  {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,},
  {1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,}
};

#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------. ,-----------------------------------------.
     AQOURS, ELEC_BOARD,     W,     E,     R,     T,       Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------| |------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,       H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------| |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,       N,     M,  COMM,   DOT,  SLSH,  RSFT,\
  //`------+------+------+------+------+------| |------+------+------+------+------+------'
                           GUIEI, LOWER,   SPC,     ENT, RAISE, ALTKN \
                       //`--------------------' `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------. ,-----------------------------------------.
        ESC,     1,     2,     3,     4,     5,      6,     7,     8,     9,     0,  BSPC,\
  //|------+------+------+------+------+------| |------+------+------+------+------+------|
      CTLTB,    F1,    F2,    F3,    F4,    F5,     F6,    F7,    F8,    F9,   F10, XXXXX,\
  //|------+------+------+------+------+------| |------+------+------+------+------+------|
       LSFT,   F11,   F12,   F13,   F14,   F15,     F16,   F17,   F18,   F19,   F20, XXXXX,\
  //`------+------+------+------+------+------| |------+------+------+------+------+------'
                           GUIEI, LOWER,   SPC,     ENT, RAISE, ALTKN \
                       //`--------------------' `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------. ,-----------------------------------------.
        ESC,  EXLM,    AT,  HASH,   DLR,  PERC,    CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  BSPC,\
  //|------+------+------+------+------+------| |------+------+------+------+------+------|
      CTLTB, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,    MINS,   EQL,  LCBR,  RCBR,  PIPE,   GRV,\
  //|------+------+------+------+------+------| |------+------+------+------+------+------|
       LSFT, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,    UNDS,  PLUS,  LBRC,  RBRC,  BSLS,  TILD,\
  //`------+------+------+------+------+------| |------+------+------+------+------+------'
                           GUIEI, LOWER,   SPC,     ENT, RAISE, ALTKN \
                       //`--------------------' `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------. ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------| |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------| |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //`------+------+------+------+------+------| |------+------+------+------+------+------'
                           GUIEI, LOWER,   SPC,     ENT, RAISE, ALTKN \
                       //`--------------------' `--------------------'
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

#ifdef RGBLIGHT_ENABLE

  void aqours_led(void) {
    aqours_next_color_timer_count++;
    //一定間隔で色が変化
    if (aqours_next_color_timer_count > NEXT_COLOR_TIME) {
      aqours_num++;
      aqours_next_color_timer_count = 0;
      target_col = 0;
      if (aqours_num == sizeof(aqours_h) / sizeof(int)) {
        aqours_num = 0;
      }
    }

    //キー毎に時間差で色が変化していく
    if (aqours_next_color_timer_count % NEXT_CHANGE_TARGET_TIME == 0) {
      if (target_col < MATRIX_COLS) {
        sethsv(aqours_h[aqours_num] * 256 / 360, aqours_s[aqours_num], aqours_v[aqours_num], (LED_TYPE *)&led[target_col]);
        sethsv(aqours_h[aqours_num] * 256 / 360, aqours_s[aqours_num], aqours_v[aqours_num], (LED_TYPE *)&led[11 - target_col]);
        sethsv(aqours_h[aqours_num] * 256 / 360, aqours_s[aqours_num], aqours_v[aqours_num], (LED_TYPE *)&led[12 + target_col]);
        sethsv(aqours_h[aqours_num] * 256 / 360, aqours_s[aqours_num], aqours_v[aqours_num], (LED_TYPE *)&led[23 - target_col]);
        target_col++;
        rgblight_set();
      }
    }
  }

  int board_timer = 0;
  int board_index = 0;
  void electric_board_render(void) {
    if (timer_elapsed(color_timer) > 400) {
        color_timer = timer_read();
        board_timer = 0;
        board_index++;
        if (board_index == ELECTRIC_BOARD_LENGTH) {
            board_index = 0;
        }
        for (int i = 0; i <= 5; i++) {
          for (int c = 0; c <= 2; c++) {
            int read_num = board_index + i;
            if (!is_master) {
                read_num = read_num + 6;
            }
            if (read_num > ELECTRIC_BOARD_LENGTH)  {
                read_num = read_num - ELECTRIC_BOARD_LENGTH;
            }
            if (electric_board_data[c][read_num]) {
                sethsv(aqours_h[3] * 256 / 360, aqours_s[3], aqours_v[3], (LED_TYPE *)&led[i + 6 * c]);
            } else {
                sethsv(aqours_h[4] * 256 / 360, aqours_s[4], aqours_v[4], (LED_TYPE *)&led[i + 6 * c]);
            }
          }
        }
        rgblight_set();
      }
    };
#endif

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

void matrix_scan_user(void) {
    #ifdef RGBLIGHT_ENABLE
      if (aqours_mode) {
        aqours_led();
      }
      if (electric_board_mode) {
        electric_board_render();
      }
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
    case AQOURS:
    #ifdef RGBLIGHT_ENABLE
      if (record->event.pressed) {
        aqours_mode = !aqours_mode;
      }
    #endif
    break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
          aqours_mode = false;
          electric_board_mode = false;
        }
      #endif
      break;
    case ELEC_BOARD:
    #ifdef RGBLIGHT_ENABLE
      if (record->event.pressed) {
        electric_board_mode = !electric_board_mode;
        aqours_mode = false;
      }
      if (electric_board_mode) {
          color_timer = timer_read();
          change_target_timer = color_timer;
      }
    #endif
    break;
  }
  return true;
}
