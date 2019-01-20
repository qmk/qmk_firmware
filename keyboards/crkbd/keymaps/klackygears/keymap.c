#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
//#ifdef SSD1306OLED
  //#include "ssd1306.h"
//#endif
#include "action_layer.h"
#include "wait.h"
#include "klackygears.h"


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;
// Layout for klackygears
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
// #define _DVRK 0
// #define _NUMB 1
// #define _MDVK 2
// #define _MNMB 3
// #define _SYMB 4
// #define _MDIA 5


//enum custom_keycodes {
//  DVRK = SAFE_RANGE,
//  MDVK,
//  NUMB,
//  MNMB,
//  SYMB,
//  MDIA,
//  RGBRST,
//  DYNAMIC_MACRO_RANGE,
//};

//#include "dynamic_macro.h"





const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVRK] = LAYOUT_kc( \
 //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  QUOT, COMQUES, DTEX,    P,     Y,                      F,     G,     C,     R,     L,   WNL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     A,     O,     E,     U,     I,                      D,     H,     T,     N,     S,  RSFT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      MCRTG,  WNSC,  ALTQ,  CTLJ,     K,     X,                      B,     M,  CTLW,  ALTV,  MDAZ,  QUAD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   ENT,  SPSY,  BSNB,     TBNB,  ENSY,   RSFT \
                              //`--------------------'  `--------------------'
  ),

  [_MDVK] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  QUOT, COMQUES, DTEX,    P,     Y,                      F,     G,     C,     R,     L,   MCL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     A,     O,     E,     U,     I,                      D,     H,     T,     N,     S,  RSFT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      QUAD,  CSCN,  ALTQ,  GUIJ,     K,     X,                      B,     M,  GUIW,  ALTV,  MDAZ,  QUAD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   ENT,  SPSY,  MBNB,     MTNB,  ENSY,   RSFT \
                              //`--------------------'  `--------------------'
  ),

  [_NUMB] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,  PGUP,  PGDN,  HOME,   END,  FNDR,                 MINPLS,     7,     8,     9, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  LEFT,    UP,  DOWN, RIGHT,  PTSP,                 DIVMLT,     4,     5,     6,  CSTC, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  ACCW,  CTLA,  CCPY,  PSTI,  DDEL,                 DOTEQL,     1,  CTL2,  ALT3,  RWIN, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____,     0 \
                              //`--------------------'  `--------------------'
  ),


  [_MNMB] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,  PGUP,  PGDN,  HOME,   END, XXXXX,                 MINPLS,     7,     8,     9, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  LEFT,    UP,  DOWN, RIGHT, XXXXX,                 DIVMLT,     4,     5,     6,  CSTC, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, MCCPY, MCPIN,   DEL,                 DOTEQL,     1,  CTL2,  ALT3,  RWIN, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, SPACE, BSPC,     _____, _____,     0 \
                              //`--------------------'  `--------------------'
  ),


  [_SYMB] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,  BSLS,    AT,  HASH,   DLR,  PERC,                   MACD,    F9,   F10,   F11,   F12, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  PLUS,  MINS,  ASTR,  SLSH,   EQL,                   MCNB,    F5,    F6,    F7,    F8, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  LBRC,  RBRC,  LPRN,  RPRN,  AMPR,                    GRV,    F1,    F2,    F3,    F4, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____,   DEL,    _____,  CAPS, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_MDIA] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  XXXXX, XXXXX, XXXXX, XXXXX, ACL2,                  XXXXX,  LRST,  LSAD,  LSAI, XXXXX, _____,\
  //|------+-------+------+------+------+-----|                |------+------+------+------+------+------|
      _____,   MS_L,  MS_U,  MS_D,  MS_R, ACL1,                  XXXXX, LRMOD,  LHUD,  LHUI, XXXXX, _____,\
  //|------+-------+------+------+------+-----|                |------+------+------+------+------+------|
      _____,  LRMOD,  WH_U,  WH_D,  LVAD, ACL0,                  XXXXX,  MUTE,  VOLD,  VOLU, XXXXX, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____,  BTN1,  BTN2,    _____, _____, XXXXX \
                              //`--------------------'  `--------------------'
  )
};


int RGB_current_mode;

// Setting MDIA layer RGB back to default
static inline void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
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
//#ifdef SSD1306OLED


// When add source files to SRC in rules.mk, you can use functions.
//const char *read_layer_state(void);
//const char *read_logo(void);
//void set_keylog(uint16_t keycode, keyrecord_t *record);
//const char *read_keylog(void);
//const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

#ifdef RGBLIGHT_ENABLE
  const char *read_rgb_info(void);
  #define RENDER_RGB_INFO(m) matrix_write_ln(m, (const char*)read_rgb_info())
#else
  #define RENDER_RGB_INFO(m)
#endif


//void matrix_scan_user(void) {
   //iota_gfx_task();
//}

//static inline void matrix_render_user(struct CharacterMatrix *matrix) {
  //if (is_master) {
    // If you want to change the display of OLED, you need to change here
   // matrix_write_ln(matrix, read_layer_state());
   // matrix_write_ln(matrix, read_keylog());
   // RENDER_RGB_INFO(matrix);
    // matrix_write_ln(matrix, read_keylogs());
    // matrix_write_ln(matrix, read_host_led_state());

    // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    // matrix_write_ln(matrix, read_timelog());
  //} else {
   // matrix_write(matrix, read_logo());
 // }
//}

//static inline void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
 // if (memcmp(dest->display, source->display, sizeof(dest->display))) {
  //  memcpy(dest->display, source->display, sizeof(dest->display));
   // dest->dirty = true;
 // }
//}

//void iota_gfx_task_user(void) {
  //struct CharacterMatrix matrix;
  //matrix_clear(&matrix);
  //matrix_render_user(&matrix);
  //matrix_update(&display, &matrix);
//}

//#endif

