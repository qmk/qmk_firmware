#include QMK_KEYBOARD_H
#include <string.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

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
static uint8_t delay_mat_row;
static uint8_t delay_mat_col;
static bool delay_key_stat;
static bool delay_key_pressed;
static bool tapping_key;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _OPT 1
#define _FUNC 2
#define _SYM 3
#define _NUM 4

bool RGBAnimation = false; //Flag for LED Layer color Refresh.

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
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

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
  [_BASE] = LAYOUT_half(
      LCTL(KC_Z),    KC_SCLN,       KC_LBRC,       KC_LPRN,   KC_LT,     KC_LCBR,
      KANA,          KC_P,          KC_K,          KC_R,      KC_A,      KC_F,
      KC_BSPC,       KC_D,          KC_T,          KC_H,      KC_E,      KC_O,
      OSM(MOD_LSFT), KC_Y,          KC_S,          KC_N,      KC_I,      KC_U,       KC_SPC,
      OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), MO(_SYM),  MO(_NUM),  OPT_TAP_SP, KC_ENT ),

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
  [_OPT] = LAYOUT_half(
      KC_ESC,  KC_COLN,KC_RBRC, KC_RPRN,KC_GT,     KC_RCBR,
      EISU,    KC_J,   KC_M,    KC_B,   KC_QUOT,   KC_TAB,
      KC_DOT,  KC_V,   KC_C,    KC_L,   KC_Z,      KC_Q,
      _______, KC_X,   KC_G,    KC_W,   KC_MINUS,  KC_DEL,  KC_ESC,
      _______, _______,_______, KC_COMM,DESKTOP,   _______, _______
      ),

  /* Func
   * ,-----------------------------------------.
   * |RGBRST|  Hue |      |  RST |  Mac |  Win |
   * |------+------+------+------+------+------|
   * | RGB1 | VAL+ |  F7  |  F8  |  F9  |      |
   * |------+------+------+------+------+------|
   * | RGB2 | VAL- |  F4  |  F5  |  F6  | F12  |
   * |------+------+------+------+------+------+------.
   * | RGB3 |  F10 |  F1  |  F2  |  F3  | F11  |      |
   * |------+------+------+------+------+------+------|
   * |RGBOFF|      |      |      |      |      |      |
   * `------------------------------------------------'
   */
  [_FUNC] = LAYOUT_half(
      RGBRST,RGB_HUI, _______, QK_BOOT, MAC,     WIN,
      RGB1,  RGB_VAI, KC_F7,   KC_F8,   KC_F9,   _______,
      RGB2,  RGB_VAD, KC_F4,   KC_F5,   KC_F6,   KC_F12,
      RGB3,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,   _______,
      RGBOFF,_______, _______, _______, _______, _______,  _______
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
   * |------+------+------+------+------+------+------|
   * |      |      |  PS  |      |   ~  |      |      |
   * `------------------------------------------------'
   */
  [_SYM] = LAYOUT_half(
      KC_INS,  KC_GRV,  _______, KC_PGUP, KC_PGDN, KC_CIRC,
      _______, KC_BSLS, KC_HASH, KC_EQL,  KC_QUES, KC_PERC,
      _______, KC_DLR,  KC_UP,   KC_AT,   KC_EXLM, KC_PIPE,
      KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_UNDS, KC_AMPR, _______,
      _______, _______, KC_PSCR, _______, KC_TILD, _______, _______
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
   * |      |      |      |  ,   |      |      |      |
   * `------------------------------------------------'
   */
  [_NUM] = LAYOUT_half(
      _______,  _______, OSL(_FUNC), KC_HOME, KC_END,  _______,
      _______,  KC_ASTR, KC_P7,      KC_P8,   KC_P9,   KC_MINS,
      KC_PDOT,  KC_SLSH, KC_P4,      KC_P5,   KC_P6,   KC_PLUS,
      KC_NUM,   KC_P0,   KC_P1,      KC_P2,   KC_P3,   LCTL(S(KC_F1)), _______,
      _______,  _______, KC_PDOT,    KC_COMM, _______, _______,        _______
      )
};

#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
//bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool find_mairix(uint16_t keycode, uint8_t *row, uint8_t *col){
  for(uint8_t i=0; i<MATRIX_ROWS; i++){
    for(uint8_t j=0; j<MATRIX_COLS; j++){
      if( pgm_read_word(&(keymaps[_BASE][i][j]))==keycode){
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
      if (record->event.pressed) {
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
    case OPT_TAP_SP:
      if (record->event.pressed) {
        tapping_key = false;
        register_delay_code(_OPT);
        layer_on(_OPT);
        tap_timer = timer_read();
      }else{
        layer_off(_OPT);
        if(tapping_key==false && timer_elapsed(tap_timer) < TAPPING_TERM){
          SEND_STRING(" ");
        }
        tap_timer = 0;
      }
      return false;
      break;
   case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LNG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LNG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LNG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LNG1);
      }
      return false;
      break;
    case DESKTOP:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
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
          RGB_current_mode = rgblight_get_mode();
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
          RGB_current_mode = rgblight_get_mode();
        }
      #endif
      break;
    case RGB2:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 1);
          RGB_current_mode = rgblight_get_mode();
        }
      #endif
      break;
    case RGB3:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_KNIGHT);
          RGB_current_mode = rgblight_get_mode();
        }
      #endif
      break;
    case MAC:
      if (record->event.pressed) {
        keymap_config.swap_lalt_lgui = false;
        keymap_config.swap_ralt_rgui = false;
        #ifdef AUDIO_ENABLE
          PLAY_SONG(ag_norm_song);
        #endif
      }
      break;
    case WIN:
      if (record->event.pressed) {
        keymap_config.swap_lalt_lgui = true;
        keymap_config.swap_ralt_rgui = true;
        #ifdef AUDIO_ENABLE
          PLAY_SONG(ag_swap_song);
        #endif
      }
      break;
    }
  return true;
}


//keyboard start-up code. Runs once when the firmware starts up.
void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_get_mode();
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user(void)
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user(void)
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_OPT 2
#define L_FUNC 4
#define L_SYM 8
#define L_NUM 16
#define L_FNLAYER 64
#define L_NUMLAY 128
#define L_NLOWER 136
#define L_NFNLAYER 192
#define L_MOUSECURSOR 256

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

uint8_t layer_state_old;

//runs every scan cycle (a lot)
void matrix_scan_user(void) {
  if(delay_key_stat && (timer_elapsed(key_timer) > DELAY_TIME)){
    register_delay_code(_BASE);
    if(!delay_key_pressed){
      unregister_delay_code();
    }
  }

  if(layer_state_old != layer_state){
    switch (layer_state) {
      case L_BASE:
        break;
      case L_OPT:
        register_delay_code(_OPT);
        break;
      case L_NUM:
        register_delay_code(_NUM);
        break;
      case L_SYM:
        register_delay_code(_SYM);
        break;
      case L_FUNC:
        register_delay_code(_FUNC);
        break;
    }
    layer_state_old = layer_state;
  }

  #ifdef RGBLIGHT_ENABLE
    if(!RGBAnimation){
      switch (layer_state) {
        case L_BASE:
          #ifdef RGBLED_BACK
            led_ripple_effect(0,112,127);
          #else
            rgblight_setrgb(0,112,127);
          #endif
          break;
        case L_OPT:
          #ifdef RGBLED_BACK
            led_ripple_effect(127,0,100);
          #else
            rgblight_setrgb(127,0,100);
          #endif
          break;
        case L_NUM:
          #ifdef RGBLED_BACK
            led_ripple_effect(127,23,0);
          #else
            rgblight_setrgb(127,23,0);
          #endif
          break;
        case L_SYM:
          #ifdef RGBLED_BACK
            led_ripple_effect(0,127,0);
          #else
            rgblight_setrgb(0,127,0);
          #endif
          break;
        case L_FUNC:
          #ifdef RGBLED_BACK
            led_ripple_effect(127,0,61);
          #else
            rgblight_setrgb(127,0,61);
          #endif
          break;
        }
    }
  #endif
}

//OLED update loop
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

// Render to OLED
void render_status(void) {

  // froggy logo
  static char logo[4][1][17]=
  {
    {
      {0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0}
    },
    {
      {0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0}
    },
    {
      {0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,0}
    },
    {
      {0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0}
    }
  };

  static char indctr[8][2][4]=
  {
    // white icon
    {
      {0x60,0x61,0x62,0},
      {0x63,0x64,0}
    },
    {
      {0x80,0x81,0x82,0},
      {0x83,0x84,0}
    },
    {
      {0xa0,0xa1,0xa2,0},
      {0xa3,0xa4,0}
    },
    {
      {0xc0,0xc1,0xc2,0},
      {0xc3,0xc4,0}
    },
    // Black icon
    {
      {0x75,0x76,0x77,0},
      {0x78,0x79,0}
    },
    {
      {0x95,0x96,0x97,0},
      {0x98,0x99,0}
    },
    {
      {0xb5,0xb6,0xb7,0},
      {0xb8,0xb9,0}
    },
    {
      {0xd5,0xd6,0xd7,0},
      {0xd8,0xd9,0}
    },
  };

  int rown = 0;
  int rowf = 0;
  int rowa = 0;
  int rows = 0;

  //Set Indicator icon
  led_t led_state = host_keyboard_led_state();
  if (led_state.num_lock) { rown = 4; } else { rown = 0; }
  if (led_state.caps_lock) { rowa = 4; } else { rowa = 0; }
  if (led_state.scroll_lock) { rows = 4; } else { rows = 0; }
  if (layer_state == L_FUNC) { rowf = 4; }

  oled_write(indctr[rown]  [0], false);
  oled_write(indctr[rowf]  [1], false);
  oled_write(logo  [0]     [0], false);
  oled_write(indctr[rown+1][0], false);
  oled_write(indctr[rowf+1][1], false);
  oled_write(logo  [1]     [0], false);
  oled_write(indctr[rowa+2][0], false);
  oled_write(indctr[rows+2][1], false);
  oled_write(logo  [2]     [0], false);
  oled_write(indctr[rowa+3][0], false);
  oled_write(indctr[rows+3][1], false);
  oled_write(logo  [3]     [0], false);

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
