#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include <string.h>
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#define LAYOUT_half( \
    L00, L01, L02, L03, L04, L05,       \
    L10, L11, L12, L13, L14, L15,       \
    L20, L21, L22, L23, L24, L25,       \
    L30, L31, L32, L33, L34, L35, L36,  \
    L40, L41, L42, L43, L44, L45, L46   \
) { \
    { L00, L01, L02, L03, L04, L05, KC_NO }, \
    { L10, L11, L12, L13, L14, L15, KC_NO }, \
    { L20, L21, L22, L23, L24, L25, KC_NO }, \
    { L30, L31, L32, L33, L34, L35, L36 }, \
    { L40, L41, L42, L43, L44, L45, L46 }, \
    { _______, _______, _______, _______, _______, _______, KC_NO }, \
    { _______, _______, _______, _______, _______, _______, KC_NO }, \
    { _______, _______, _______, _______, _______, _______, KC_NO }, \
    { _______, _______, _______, _______, _______, _______, _______ }, \
    { _______, _______, _______, _______, _______, _______, _______ } \
}

#define DELAY_TIME  75
static uint16_t key_timer;
static uint16_t tap_timer;
static uint16_t delay_registered_code;
static uint8_t delay_registered_layer;
static uint8_t delay_mat_row;
static uint8_t delay_mat_col;
static bool delay_key_stat;
static bool delay_key_pressed;
static bool tapping_key;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE = 0,
  _BASE_106,
  _OPT,
  _OPT_106,
  _SYM,
  _SYM_106,
  _NUM,
  _NUM_106,
  _FUNC,
  _LAYER_NUM,
};
bool RGBAnimation = false; //Flag for LED Layer color Refresh.

typedef union {
  uint32_t raw;
  struct {
    bool mac_mode:1;
  };
} user_config_t;
user_config_t user_config;

#define IS_MODE_106()   ((default_layer_state & (1UL << _BASE_106)) != 0)
#define IS_MODE_MAC()   (user_config.mac_mode)
#ifndef MAX
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif
#ifndef MIN
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EISU,
  KANA,
  RGBRST,
  RGBOFF,
  RGB1,
  RGB2,
  RGB3,
  OPT_TAP_SP,
  DESKTOP,
  MAC,
  WIN,
  L_SYM,
  L_NUM,
  TO_106,
  TO_101,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   * ,-----------------------------------------.
   * |  C+z |   ;  |   [  |   (  |   <  |   {  |
   * |------+------+------+------+------+------|
   * | KANA |   P  |   K  |   R  |   A  |   F  |
   * |------+------+------+------+------+------|
   * |  BS  |   D  |   T  |   H  |   E  |   O  |
   * |------+------+------+------+------+------+------.
   * | Shift|   Y  |   S  |   N  |   I  |   U  |Space |
   * |------+------+------+------+------+------+------|
   * | Ctrl | Alt  | Gui  | Sym  | Num  | OPT  | Ent  |
   * `------------------------------------------------'
   */
  [_BASE] = LAYOUT_half( \
      LCTL(KC_Z),    KC_SCLN,       KC_LBRC,       KC_LPRN,   KC_LT,     KC_LCBR,            \
      KANA,          KC_P,          KC_K,          KC_R,      KC_A,      KC_F,               \
      KC_BSPC,       KC_D,          KC_T,          KC_H,      KC_E,      KC_O,               \
      OSM(MOD_LSFT), KC_Y,          KC_S,          KC_N,      KC_I,      KC_U,       KC_SPC, \
      OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), L_SYM,     L_NUM,     OPT_TAP_SP, KC_ENT  \
      ),
  [_BASE_106] = LAYOUT_half( \
      LCTL(KC_Z),    JP_SCLN,       JP_LBRC,       JP_LPRN,   JP_LABK,   JP_LCBR,            \
      KANA,          KC_P,          KC_K,          KC_R,      KC_A,      KC_F,               \
      KC_BSPC,       KC_D,          KC_T,          KC_H,      KC_E,      KC_O,               \
      OSM(MOD_LSFT), KC_Y,          KC_S,          KC_N,      KC_I,      KC_U,       KC_SPC, \
      OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), L_SYM,     L_NUM,     OPT_TAP_SP, KC_ENT  \
      ),

  /* Opt
   * ,-----------------------------------------.
   * |  Esc |  :   |  ]   |  )   |  >   |  }   |
   * |------+------+------+------+------+------|
   * |  EISU|   J  |   M  |   B  |   '  |  Tab |
   * |------+------+------+------+------+------|
   * |   .  |   V  |   C  |   L  |   Z  |  Q   |
   * |------+------+------+------+------+------+------.
   * |      |   X  |   G  |   W  |   -  |  Del | Esc  |
   * |------+------+------+------+------+------+------|
   * |      |      |      |   ,  | DTOP |      |      |
   * `------------------------------------------------'
   */
  [_OPT] = LAYOUT_half( \
      KC_ESC,  KC_COLN,KC_RBRC, KC_RPRN,KC_GT,     KC_RCBR,         \
      EISU,    KC_J,   KC_M,    KC_B,   KC_QUOT,   KC_TAB,          \
      KC_DOT,  KC_V,   KC_C,    KC_L,   KC_Z,      KC_Q,            \
      _______, KC_X,   KC_G,    KC_W,   KC_MINUS,  KC_DEL,  KC_ESC, \
      _______, _______,_______, KC_COMM,DESKTOP,   _______, _______ \
      ),
  [_OPT_106] = LAYOUT_half( \
      KC_ESC,  JP_COLN,JP_RBRC, JP_RPRN,JP_RABK,   JP_RCBR,         \
      EISU,    KC_J,   KC_M,    KC_B,   JP_QUOT,   KC_TAB,          \
      KC_DOT,  KC_V,   KC_C,    KC_L,   KC_Z,      KC_Q,            \
      _______, KC_X,   KC_G,    KC_W,   JP_MINS,   KC_DEL,  KC_ESC, \
      _______, _______,_______, KC_COMM,DESKTOP,   _______, _______ \
      ),

  /* Sym
   * ,-----------------------------------------.
   * |  Ins |  GRV |      |  PU  |  PD  |   ^  |
   * |------+------+------+------+------+------|
   * |      |   \  |   #  |   =  |   ?  |   %  |
   * |------+------+------+------+------+------|
   * |      |   $  |  upA |   @  |   !  |   |  |
   * |------+------+------+------+------+------+------.
   * |  CL  |  <-  |  dwA |  ->  |   _  |   &  |      |
   * |------+------+------+------+------+------+------+
   * |      |      |  PS  |      |   ~  |      |      |
   * `------------------------------------------------'
   */
  [_SYM] = LAYOUT_half( \
      KC_INS,  KC_GRV,  _______, KC_PGUP, KC_PGDN, KC_CIRC,          \
      _______, KC_BSLS, KC_HASH, KC_EQL,  KC_QUES, KC_PERC,          \
      _______, KC_DLR,  KC_UP,   KC_AT,   KC_EXLM, KC_PIPE,          \
      KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_UNDS, KC_AMPR, _______, \
      _______, _______, KC_PSCR, _______, KC_TILD, _______, _______  \
      ),
  [_SYM_106] = LAYOUT_half( \
      KC_INS,  JP_GRV,  _______, KC_PGUP, KC_PGDN, JP_CIRC,          \
      _______, JP_BSLS, JP_HASH, JP_EQL,  JP_QUES, JP_PERC,          \
      _______, JP_DLR,  KC_UP,   JP_AT,   JP_EXLM, JP_PIPE,          \
      KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,JP_UNDS, JP_AMPR, _______, \
      _______, _______, KC_PSCR, _______, JP_TILD, _______, _______  \
      ),
  
  /* Raise
   * ,-----------------------------------------.
   * |      |      | Func | home |  End |      |
   * |------+------+------+------+------+------|
   * |      |   *  |  7   |  8   |  9   |  -   |
   * |------+------+------+------+------+------|
   * |  .   |   /  |  4   |  5   |  6   |  +   |
   * |------+------+------+------+------+------+------.
   * |  LN  |  0   |  1   |  2   |  3   |C+S+F1|      |
   * |------+------+------+------+------+------+------|
   * |      |      |  .   |  ,   |      |      |      |
   * `------------------------------------------------'
   */
  [_NUM] = LAYOUT_half( \
      _______,  _______, OSL(_FUNC), KC_HOME, KC_END,  _______,                 \
      _______,  KC_ASTR, KC_P7,      KC_P8,   KC_P9,   KC_MINS,                 \
      KC_DOT,   KC_SLSH, KC_P4,      KC_P5,   KC_P6,   KC_PLUS,                 \
      KC_NLCK,  KC_P0,   KC_P1,      KC_P2,   KC_P3,   LCTL(S(KC_F1)), _______, \
      _______,  _______, KC_PDOT,    KC_COMM, _______, _______,        _______  \
      ),
  [_NUM_106] = LAYOUT_half( \
      _______,  _______, OSL(_FUNC), KC_HOME, KC_END,  _______,                 \
      _______,  JP_ASTR, KC_P7,      KC_P8,   KC_P9,   JP_MINS,                 \
      KC_DOT,   JP_SLSH, KC_P4,      KC_P5,   KC_P6,   JP_PLUS,                 \
      KC_NLCK,  KC_P0,   KC_P1,      KC_P2,   KC_P3,   LCTL(S(KC_F1)), _______, \
      _______,  _______, KC_PDOT,    JP_COMM, _______, _______,        _______  \
      ),
  
  /* Func
   * ,-----------------------------------------.
   * |RGBRST|  Hue |To101 |  RST |  Mac |  Win |
   * |------+------+------+------+------+------|
   * | RGB1 | VAL+ |  F7  |  F8  |  F9  |To106 |
   * |------+------+------+------+------+------|
   * | RGB2 | VAL- |  F4  |  F5  |  F6  | F12  |
   * |------+------+------+------+------+------+------.
   * | RGB3 |  F10 |  F1  |  F2  |  F3  | F11  |      |
   * |------+------+------+------+------+------+------|
   * |RGBOFF|      |      |      |      |      |      |
   * `------------------------------------------------'
   */
  [_FUNC] = LAYOUT_half( \
      RGBRST,RGB_HUI, TO_101,  QK_BOOT, MAC,     WIN,               \
      RGB1,  RGB_VAI, KC_F7,   KC_F8,   KC_F9,   TO_106,            \
      RGB2,  RGB_VAD, KC_F4,   KC_F5,   KC_F6,   KC_F12,            \
      RGB3,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,   _______, \
      RGBOFF,_______, _______, _______, _______, _______,  _______  \
      )
};
#else
#error "undefined keymaps"
#endif

void set_mac_mode(bool enable) {
  if(enable){
    user_config.mac_mode = true;
    keymap_config.swap_lalt_lgui = false;
    keymap_config.swap_ralt_rgui = false;
  }else{
    user_config.mac_mode = false;
    keymap_config.swap_lalt_lgui = true;
    keymap_config.swap_ralt_rgui = true;
  }
  eeconfig_update_user(user_config.raw);
}

void eeconfig_init_user(void) {
  user_config.raw = 0;
  eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
  set_mac_mode(user_config.mac_mode);
}

bool find_mairix(uint16_t keycode, uint8_t *row, uint8_t *col){
  int base_keymap = IS_MODE_106() ? _BASE_106 : _BASE;
  for(uint8_t i=0; i<MATRIX_ROWS; i++){
    for(uint8_t j=0; j<MATRIX_COLS; j++){
      if( pgm_read_word(&(keymaps[base_keymap][i][j]))==keycode){
        *row = i;
        *col = j;
        return true;
      }
    }
  }
  return false;
}

void unregister_delay_code(void){
  if(delay_registered_code){
    unregister_code(delay_registered_code);
    if (delay_registered_code & QK_LSFT){
      unregister_code(KC_LSFT);
    }
    if (delay_registered_code & QK_LCTL){
      unregister_code(KC_LCTL);
    }
    if (delay_registered_code & QK_LALT){
      unregister_code(KC_LALT);
    }
    if (delay_registered_code & QK_LGUI){
      unregister_code(KC_LGUI);
    }
    delay_registered_code=0;
    delay_registered_layer=0;
  }
}

void register_delay_code(uint8_t layer){
  if(delay_key_stat){
    unregister_delay_code();

    uint16_t code = pgm_read_word(&(keymaps[layer][delay_mat_row][delay_mat_col]));
    if (code & QK_LSFT){
      register_code(KC_LSFT);
    }
    if (code & QK_LCTL){
      register_code(KC_LCTL);
    }
    if (code & QK_LALT){
      register_code(KC_LALT);
    }
    if (code & QK_LGUI){
      register_code(KC_LGUI);
    }
    register_code(code);
    delay_registered_code = code;
    delay_registered_layer = layer;
    delay_key_stat = false;
    tapping_key = true;
  }
}

#ifdef RGBLIGHT_ENABLE
struct keybuf {
  char col, row;
  char frame;
};
struct keybuf keybufs[256];
unsigned char keybuf_begin, keybuf_end;

int col, row;
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  #ifdef RGBLIGHT_ENABLE
    col = record->event.key.col;
    row = record->event.key.row;
    if (record->event.pressed && ((row < 5 && is_keyboard_master()) || (row >= 5 && !is_keyboard_master()))) {
      int end = keybuf_end;
      keybufs[end].col = col;
      keybufs[end].row = row % 5;
      keybufs[end].frame = 0;
      keybuf_end ++;
    }
  #endif

  if(tap_timer&&keycode!=OPT_TAP_SP){
    tapping_key = true;
  }

  if(keycode==delay_registered_code){
    if (!record->event.pressed){
      unregister_delay_code();
    }
  }

  switch (keycode) {
    case KC_SCLN:
    case KC_LBRC:
    case KC_LPRN:
    case KC_LT:
    case KC_LCBR:
    case KC_P:
    case KC_K:
    case KC_R:
    case KC_A:
    case KC_F:
    case KC_BSPC:
    case KC_D:
    case KC_T:
    case KC_H:
    case KC_E:
    case KC_O:
    case KC_Y:
    case KC_S:
    case KC_N:
    case KC_I:
    case KC_U:
    case LCTL(KC_Z):
    case KC_SPC:
    //case JP_SCLN: // == KC_SCLN
    case JP_LBRC:
    case JP_LPRN:
    //case JP_LABK: // == KC_LT
    case JP_LCBR:
      if (IS_MODE_106()) {
          if (keycode == KC_LBRC || keycode == KC_LPRN || keycode == KC_LCBR)
            break;
      }else{
          if (keycode == JP_LBRC || keycode == JP_LPRN || keycode == JP_LCBR)
            break;
      }
      if (record->event.pressed) {
        if (IS_MODE_106())
          register_delay_code(_BASE_106);
        else
          register_delay_code(_BASE);
        if(find_mairix(keycode, &delay_mat_row, &delay_mat_col)){
          key_timer = timer_read();
          delay_key_stat = true;
          delay_key_pressed = true;
        }
      }else{
        delay_key_pressed = false;
      }
      return false;
      break;
    case L_SYM:
      if (record->event.pressed) {
        if (IS_MODE_106()) {
          register_delay_code(_SYM_106);
          layer_on(_SYM_106);
        }else{
          register_delay_code(_SYM);
          layer_on(_SYM);
        }
      }else{
        layer_off(_SYM);
        layer_off(_SYM_106);
        if(delay_registered_layer == _SYM || delay_registered_layer == _SYM_106) {
          unregister_delay_code();
        }
      }
      return false;
      break;
    case L_NUM:
      if (record->event.pressed) {
        if (IS_MODE_106()) {
          register_delay_code(_NUM_106);
          layer_on(_NUM_106);
        }else{
          register_delay_code(_NUM);
          layer_on(_NUM);
        }
      }else{
        layer_off(_NUM);
        layer_off(_NUM_106);
        if(delay_registered_layer == _NUM || delay_registered_layer == _NUM_106) {
          unregister_delay_code();
        }
      }
      return false;
      break;
    case OPT_TAP_SP:
      if (record->event.pressed) {
        tapping_key = false;
        if (IS_MODE_106()) {
          register_delay_code(_OPT_106);
          layer_on(_OPT_106);
        }else{
          register_delay_code(_OPT);
          layer_on(_OPT);
        }
        tap_timer = timer_read();
      }else{
        layer_off(_OPT);
        layer_off(_OPT_106);
        if(tapping_key==false && timer_elapsed(tap_timer) < TAPPING_TERM){
          SEND_STRING(" ");
        }else if(delay_registered_layer == _OPT || delay_registered_layer == _OPT_106) {
          unregister_delay_code();
        }
        tap_timer = 0;
      }
      return false;
      break;
   case EISU:
      if (record->event.pressed) {
        if(IS_MODE_MAC()){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(IS_MODE_MAC()){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case DESKTOP:
      if (record->event.pressed) {
        if(IS_MODE_MAC()){
          register_code(KC_F11);
        }else{
          SEND_STRING(SS_LGUI("d"));
        }
      } else {
        unregister_code(KC_F11);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGBAnimation = false;
        }
      #endif
      break;
    case RGBOFF:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_disable();
        }
      #endif
      break;
    case RGB1:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
        }
      #endif
      break;
    case RGB2:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 1);
        }
      #endif
      break;
    case RGB3:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_KNIGHT);
        }
      #endif
      break;
    case MAC:
      if (record->event.pressed) {
        set_mac_mode(true);
      }
      break;
    case WIN:
      if (record->event.pressed) {
        set_mac_mode(false);
      }
      break;
    case TO_101:
      if (record->event.pressed) {
        if (IS_MODE_106()) {
          set_single_persistent_default_layer(_BASE);
        }
      }
      break;
    case TO_106:
      if (record->event.pressed) {
        if (!IS_MODE_106()) {
          set_single_persistent_default_layer(_BASE_106);
        }
      }
      break;
  }
  return true;
}


//keyboard start-up code. Runs once when the firmware starts up.
void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

// LED Effect
#ifdef RGBLIGHT_ENABLE
unsigned char rgb[7][5][3];
void led_ripple_effect(char r, char g, char b) {
    static int scan_count = -10;
    static int keys[] = { 6, 6, 6, 7, 7 };
    static int keys_sum[] = { 0, 6, 12, 18, 25 };

    if (scan_count == -1) {
      rgblight_enable_noeeprom();
      rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    } else if (scan_count >= 0 && scan_count < 5) {
      for (unsigned char c=keybuf_begin; c!=keybuf_end; c++) {
        int i = c;
        // FIXME:

        int y = scan_count;
        int dist_y = abs(y - keybufs[i].row);
        for (int x=0; x<keys[y]; x++) {
          int dist = abs(x - keybufs[i].col) + dist_y;
          if (dist <= keybufs[i].frame) {
            int elevation = MAX(0, (8 + dist - keybufs[i].frame)) << 2;
            if (elevation) {
              if ((rgb[x][y][0] != 255) && r) { rgb[x][y][0] = MIN(255, elevation + rgb[x][y][0]); }
              if ((rgb[x][y][1] != 255) && g) { rgb[x][y][1] = MIN(255, elevation + rgb[x][y][1]); }
              if ((rgb[x][y][2] != 255) && b) { rgb[x][y][2] = MIN(255, elevation + rgb[x][y][2]); }
            }
          }
        }
      }
    } else if (scan_count == 5) {
      for (unsigned char c=keybuf_begin; c!=keybuf_end; c++) {
        int i = c;
        if (keybufs[i].frame < 18) {
          keybufs[i].frame ++;
        } else {
          keybuf_begin ++;
        }
      }
    } else if (scan_count >= 6 && scan_count <= 10) {
      int y = scan_count - 6;
      for (int x=0; x<keys[y]; x++) {
        int at = keys_sum[y] + ((y & 1) ? x : (keys[y] - x - 1));
        led[at].r = rgb[x][y][0];
        led[at].g = rgb[x][y][1];
        led[at].b = rgb[x][y][2];
      }
      rgblight_set();
    } else if (scan_count == 11) {
      memset(rgb, 0, sizeof(rgb));
    }
    scan_count++;
    if (scan_count >= 12) { scan_count = 0; }
}
#endif

layer_state_t layer_state_old;

//runs every scan cycle (a lot)
void matrix_scan_user(void) {
  #ifdef SSD1306OLED
    iota_gfx_task();  // this is what updates the display continuously
  #endif

  if(delay_key_stat && (timer_elapsed(key_timer) > DELAY_TIME)){
    if (IS_MODE_106())
      register_delay_code(_BASE_106);
    else
      register_delay_code(_BASE);
    if(!delay_key_pressed){
      unregister_delay_code();
    }
  }

  if(layer_state_old != layer_state){
    for (int8_t i = _LAYER_NUM-1; i > _BASE_106; i--) {
      if(IS_LAYER_ON(i)){
        register_delay_code(i);
        break;
      }
    }
    layer_state_old = layer_state;
  }

  #ifdef RGBLIGHT_ENABLE
    if(!RGBAnimation){
      if(IS_LAYER_ON(_FUNC)){
        #ifdef RGBLED_BACK
          led_ripple_effect(127,23,0);
        #else
          rgblight_setrgb(127,23,0);
        #endif
      }else if(IS_LAYER_ON(_NUM)||IS_LAYER_ON(_NUM_106)){
        #ifdef RGBLED_BACK
          led_ripple_effect(127,0,61);
        #else
          rgblight_setrgb(127,0,61);
        #endif
      }else if(IS_LAYER_ON(_SYM)||IS_LAYER_ON(_SYM_106)){
        #ifdef RGBLED_BACK
          led_ripple_effect(0,127,0);
        #else
          rgblight_setrgb(0,127,0);
        #endif
      }else if(IS_LAYER_ON(_OPT)||IS_LAYER_ON(_OPT_106)){
        #ifdef RGBLED_BACK
          led_ripple_effect(127,0,100);
        #else
          rgblight_setrgb(127,0,100);
        #endif
      } else {
        #ifdef RGBLED_BACK
          led_ripple_effect(0,112,127);
        #else
          rgblight_setrgb(0,112,127);
        #endif
      }
    }
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

// Render to OLED
void render_status(struct CharacterMatrix *matrix) {

  // froggy logo
  static char logo[4][17]=
  {
    {0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0},
    {0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0},
    {0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,0},
    {0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0},
  };
  
  static char modectl[4][2][4]=
  {
    {
      {0x65,0x66,0x67,0}, //WIN
      {0x85,0x86,0x87,0}, //WIN
    },
    {
      {0xa5,0xa6,0xa7,0}, //US(101)
      {0xc5,0xc6,0xc7,0}, //US(101)
    },
    {
      {0xbd,0xbe,0xbf,0}, //MAC
      {0xdd,0xde,0xdf,0}, //MAC
    },
    {
      {0xba,0xbb,0xbc,0}, //JP(106)
      {0xda,0xdb,0xdc,0}, //JP(106)
    },
  };
  
  static char indctr[8][2][4]=
  {
    // white icon
    {
      {0x60,0x61,0x62,0}, //NUM
      {0x63,0x64,0}       //FUNC
    },
    {
      {0x80,0x81,0x82,0}, //NUM
      {0x83,0x84,0}       //FUNC
    },
    {
      {0xa0,0xa1,0xa2,0}, //CAPS
      {0xa3,0xa4,0}       //SCLK
    },
    {
      {0xc0,0xc1,0xc2,0}, //CAPS
      {0xc3,0xc4,0}       //SCLK
    },
    // Black icon
    {
      {0x75,0x76,0x77,0}, //NUM
      {0x78,0x79,0}       //FUNC
    },
    {
      {0x95,0x96,0x97,0}, //NUM
      {0x98,0x99,0}       //FUNC
    },
    {
      {0xb5,0xb6,0xb7,0}, //CAPS
      {0xb8,0xb9,0}       //SCLK
    },
    {
     {0xd5,0xd6,0xd7,0}, //CAPS
     {0xd8,0xd9,0}       //SCLK
    },
  };

  int rown = 0;
  int rowf = 0;
  int rowa = 0;
  int rows = 0;
  int rowm = 0;
  int rowj = 1;

  //Set Indicator icon
  if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) { rown = 4; }
  if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { rowa = 4; }
  if (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) { rows = 4; }
  if (IS_LAYER_ON(_FUNC)) { rowf = 4; }

  //Set Mode icon
  if (IS_MODE_MAC()) { rowm = 2; }
  if (IS_MODE_106()) { rowj = 3; }

  matrix_write(matrix, indctr[rown]  [0]);
  matrix_write(matrix, indctr[rowf]  [1]);
  matrix_write(matrix, modectl[rowm] [0]);
  matrix_write(matrix, logo[0]);
  matrix_write(matrix, indctr[rown+1][0]);
  matrix_write(matrix, indctr[rowf+1][1]);
  matrix_write(matrix, modectl[rowm] [1]);
  matrix_write(matrix, logo[1]);
  matrix_write(matrix, indctr[rowa+2][0]);
  matrix_write(matrix, indctr[rows+2][1]);
  matrix_write(matrix, modectl[rowj] [0]);
  matrix_write(matrix, logo[2]);
  matrix_write(matrix, indctr[rowa+3][0]);
  matrix_write(matrix, indctr[rows+3][1]);
  matrix_write(matrix, modectl[rowj] [1]);
  matrix_write(matrix, logo[3]);

}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if (is_keyboard_master()) {
    render_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif // end of SSD1306OLED

//OLED update loop
#ifdef OLED_ENABLE

// Render to OLED
void render_status(void) {

  // froggy logo
  static char logo[4][17]=
  {
    {0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0},
    {0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0},
    {0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,0},
    {0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0},
  };

  static char modectl[4][2][4]=
  {
    {
      {0x65,0x66,0x67,0}, //WIN
      {0x85,0x86,0x87,0}, //WIN
    },
    {
      {0xa5,0xa6,0xa7,0}, //US(101)
      {0xc5,0xc6,0xc7,0}, //US(101)
    },
    {
      {0xbd,0xbe,0xbf,0}, //MAC
      {0xdd,0xde,0xdf,0}, //MAC
    },
    {
      {0xba,0xbb,0xbc,0}, //JP(106)
      {0xda,0xdb,0xdc,0}, //JP(106)
    },
  };

  static char indctr[8][2][4]=
  {
    // white icon
    {
      {0x60,0x61,0x62,0}, //NUM
      {0x63,0x64,0}       //FUNC
    },
    {
      {0x80,0x81,0x82,0}, //NUM
      {0x83,0x84,0}       //FUNC
    },
    {
      {0xa0,0xa1,0xa2,0}, //CAPS
      {0xa3,0xa4,0}       //SCLK
    },
    {
      {0xc0,0xc1,0xc2,0}, //CAPS
      {0xc3,0xc4,0}       //SCLK
    },
    // Black icon
    {
      {0x75,0x76,0x77,0}, //NUM
      {0x78,0x79,0}       //FUNC
    },
    {
      {0x95,0x96,0x97,0}, //NUM
      {0x98,0x99,0}       //FUNC
    },
    {
      {0xb5,0xb6,0xb7,0}, //CAPS
      {0xb8,0xb9,0}       //SCLK
    },
    {
     {0xd5,0xd6,0xd7,0}, //CAPS
     {0xd8,0xd9,0}       //SCLK
    },
  };

  int rown = 0;
  int rowf = 0;
  int rowa = 0;
  int rows = 0;
  int rowm = 0;
  int rowj = 1;

  //Set Indicator icon
  if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) { rown = 4; }
  if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { rowa = 4; }
  if (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) { rows = 4; }
  if (IS_LAYER_ON(_FUNC)) { rowf = 4; }

  //Set Mode icon
  if (IS_MODE_MAC()) { rowm = 2; }
  if (IS_MODE_106()) { rowj = 3; }

  oled_write(indctr[rown]  [0], false);
  oled_write(indctr[rowf]  [1], false);
  oled_write(modectl[rowm] [0], false);
  oled_write(logo[0],           false);
  oled_write(indctr[rown+1][0], false);
  oled_write(indctr[rowf+1][1], false);
  oled_write(modectl[rowm] [1], false);
  oled_write(logo[1],           false);
  oled_write(indctr[rowa+2][0], false);
  oled_write(indctr[rows+2][1], false);
  oled_write(modectl[rowj] [0], false);
  oled_write(logo[2],           false);
  oled_write(indctr[rowa+3][0], false);
  oled_write(indctr[rows+3][1], false);
  oled_write(modectl[rowj] [1], false);
  oled_write(logo[3],           false);

}

bool oled_task_user(void) {

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  if (is_keyboard_master()) {
    render_status();
  }
  return false;
}

#endif // end of OLED_ENABLE

// Local Variables:
// mode: c++
// truncate-lines: t
// indent-tabs-mode: nil
// End:
