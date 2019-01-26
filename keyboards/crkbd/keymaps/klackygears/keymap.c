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
  [_DVRK] = LAYOUT( \

KC_ESC,         KC_QUOT,              TD(TD_COMQUES),    TD(TD_DTEX),       KC_P, KC_Y,         KC_F, KC_G, KC_C,              KC_R,              KC_L,            LGUI(KC_L),\
KC_LSFT,        KC_A,                 KC_O,              KC_E,              KC_U, KC_I,         KC_D, KC_H, KC_T,              KC_N,              KC_S,            KC_RSFT,\
TD(TD_MCROTG2), MT(MOD_LGUI,KC_SCLN), MT(MOD_LALT,KC_Q), MT(MOD_LCTL,KC_J), KC_K, KC_X,         KC_B, KC_M, MT(MOD_LCTL,KC_W), MT(MOD_LALT,KC_V), LT(_MDIA,KC_Z),  TD(TD_MCROTOG),\
                          KC_ENT, LT(_SYMB,KC_SPC), LT(_NUMB,KC_BSPC),     LT(_NUMB,KC_TAB),  LT(_SYMB,KC_ENT),   KC_RSFT \
  ),

  [_MDVK] = LAYOUT( \
KC_ESC,         KC_QUOT,              TD(TD_COMQUES),    TD(TD_DTEX),       KC_P, KC_Y,         KC_F, KC_G, KC_C,              KC_R,              KC_L,            LGUI(KC_L),\
KC_LSFT,        KC_A,                 KC_O,              KC_E,              KC_U, KC_I,         KC_D, KC_H, KC_T,              KC_N,              KC_S,            KC_RSFT,\
KC______,       MT(MOD_LCTL,KC_SCLN), MT(MOD_LALT,KC_Q), MT(MOD_LGUI,KC_J), KC_K, KC_X,         KC_B, KC_M, MT(MOD_LGUI,KC_W), MT(MOD_LALT,KC_V), LT(_MDIA,KC_Z),  KC______,\
                          KC_ENT, LT(_SYMB,KC_SPC), LT(_MNMB,KC_BSPC),     LT(_MNMB,KC_TAB),  LT(_SYMB,KC_ENT),   KC_RSFT \
 ),

  [_NUMB] = LAYOUT( \
KC______,  KC_PGUP,     KC_PGDN,    KC_HOME,     KC_END,      TD(TD_FNDR),           TD(TD_MINPLS), KC_7, KC_8,              KC_9,              KC_COLN,        KC______,\
KC______,  KC_LEFT,     KC_UP,      KC_DOWN,     KC_RIGHT,    TD(TD_PTSP),           TD(TD_DIVMLT), KC_4, KC_5,              KC_6,              C_S_T(KC_COLN), KC______,\
KC______,  TD(TD_ACCW), LCTL(KC_A), TD(TD_CCPY), TD(TD_PSTI), TD(TD_DDEL),           TD(TD_DOTEQL), KC_1, MT(MOD_LCTL,KC_2), MT(MOD_LALT,KC_3), KC_RWIN,        KC______,\
                                KC______, KC______, KC______,            KC______, KC______,     KC_0 \
 ),


  [_MNMB] = LAYOUT( \
KC______, KC_PGUP,  KC_PGDN,  KC_HOME,       KC_END,         KC_XXXXX,          TD(TD_MINPLS), KC_7, KC_8,              KC_9,              KC_COLN,        KC______,\
KC______, KC_LEFT,  KC_UP,    KC_DOWN,       KC_RIGHT,       KC_XXXXX,          TD(TD_DIVMLT), KC_4, KC_5,              KC_6,              C_S_T(KC_COLN), KC______,\
KC______, KC_XXXXX, KC_XXXXX, TD(TD_MCCCPY), TD(TD_MCPSTIN), KC_DEL,            TD(TD_DOTEQL), KC_1, MT(MOD_LCTL,KC_2), MT(MOD_LALT,KC_3), KC_RWIN,        KC______,\
                            KC______, KC______, KC______,                KC______, KC______,     KC_0 \
),


  [_SYMB] = LAYOUT( \
KC______,  KC_BSLS,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,          TO(_MDVK), KC_F9,   KC_F10,   KC_F11,   KC_F12, KC______,\
KC______,  KC_PLUS,  KC_MINS,  KC_ASTR,  KC_SLSH,   KC_EQL,          TO(_DVRK), KC_F5,   KC_F6,    KC_F7,    KC_F8,  KC______,\
KC______,  KC_LBRC,  KC_RBRC,  KC_LPRN,  KC_RPRN,  KC_AMPR,          KC_GRV,    KC_F1,   KC_F2,    KC_F3,    KC_F4,  KC______,\
                                 KC______, KC______, KC_DEL,           KC______,  KC_CAPS, KC______ \
  ),

  [_MDIA] = LAYOUT( \
RESET,    KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_ACL2,                  KC_XXXXX, RGBRST,   RGB_SAD,  RGB_SAI, KC_XXXXX, KC______,\
KC______, KC_MS_L,  KC_MS_U,  KC_MS_D,  KC_MS_R,  KC_ACL1,                  KC_XXXXX, RGB_RMOD, RGB_HUD,  RGB_HUI, KC_XXXXX, KC______,\
KC______, RGB_RMOD, KC_WH_U,  KC_WH_D,  KC_XXXXX, KC_ACL0,                  KC_XXXXX, KC_MUTE,  KC_VOLD,  KC_VOLU, KC_XXXXX, KC______,\
                              KC______, KC_BTN1,  KC_BTN2,    KC______, KC______, KC_XXXXX \
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
/*
void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}
*/
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

