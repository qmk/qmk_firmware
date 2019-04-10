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



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {




//In this case, this "alt" Dvorak layout is for Mac
  [_DVORAK] = LAYOUT_wrapper( \

      KC_ESC,    _______________DVORAK_L1___________________,                   _______________DVORAK_R1___________________, KC_____, \
      KC_LSFT,   _______________DVORAK_L2___________________,                   _______________DVORAK_R2___________________, KC_RSFT, \
      KC_____,   _______________WINDVK_L3___________________,                   _______________WINDVK_R3___________________, KC_____, \
                                           __________________WIN_THUMB_CLUSTER_V2______________ \
      ),

  [_ALTDVK] = LAYOUT_wrapper( \

      KC_ESC,    _______________DVORAK_L1___________________,                   _______________DVORAK_R1___________________, KC_____, \
      KC_LSFT,   _______________DVORAK_L2___________________,                   _______________DVORAK_R2___________________, KC_RSFT, \
      KC_____,   _______________MACDVK_L3___________________,                   _______________MACDVK_R3___________________, KC_____, \
                                          __________________MAC_THUMB_CLUSTER_V2______________ \
      ),

  [_QWERTY] = LAYOUT_wrapper( \

      KC_TAB,    _________________QWERTY_L1_________________,                   _________________QWERTY_R1_________________, KC_BSLASH, \
      KC_CAPS,   _________________QWERTY_L2_________________,                   _________________QWERTY_R2_________________, KC_ENT, \
      KC_LSPO,   _________________QWERTY_L3_________________,                   _________________QWERTY_R3_________________, KC_RSPC, \
                                          __________________WIN_THUMB_CLUSTER_V2______________ \
      ),

  [_SYMB] = LAYOUT_wrapper( \

      KC_____, _________________PUNC_L1_ALT_______________,                   KC_____, SHRUG,   KC_____, KC_____, MAKEKF,   KC_____, \
      KC_____, _________________PUNC_L2___________________,                   KC_____, KC_____, KC_BSLS, KC_____, KC_____, KC_____, \
      KC_____, _________________PUNC_L3___________________,                   KC_GRV,  KC_____, KC_____, KC_____, KC_____, KC_____, \
                                          KC_____, KC_____, KC_DEL,  KC_____, KC_CAPS, KC_____ \
      ),

  [_FUNC] = LAYOUT_wrapper( \

      KC_____, MAKEK,   KC_____, KC_____, KC_____, KC_____,                   KC_ALTDVK, _____________FUNC_1_______________, KC_____, \
      KC_____, KC_____, KC_____, KC_____, KC_TAB,  KC_____,                   KC_DVORAK, _____________FUNC_2_______________, KC_____, \
      KC_____, KC_LGUI, KC_RALT, KC_LCTL, KC_____, KC_____,                   KC_GRV,    _____________FUNC_3_______________, KC_____, \
                                          KC_____, KC_____, KC_DEL,  KC_____, KC_CAPS,   MO(_MDIA) \
      ),

  [_MNMB] = LAYOUT_wrapper( \

      KC_____, _________________MACNAV_L1_________________,                   _________________NUMB_R1___________________, KC_____, \
      KC_____, _________________MACNAV_L2_________________,                   _________________NUMB_R2___________________, KC_____, \
      KC_____, _________________MACNAV_L3_________________,                   _________________NUMB_R3_MAC_______________, KC_____, \
                                          KC_____, KC_____, KC_BSPC, KC_____, KC_____,  KC_0 \
      ),

  [_NUMB] = LAYOUT_wrapper( \

      KC_____, _________________WINNAV_L1_________________,                   _________________NUMB_R1___________________, _______, \
      KC_____, _________________WINNAV_L2_________________,                   _________________NUMB_R2___________________, _______, \
      KC_____, _________________WINNAV_L3_________________,                   _________________NUMB_R3_WIN_______________, _______, \
                                          KC_____, KC_____, KC_BSPC, KC_____, KC_____,  KC_0 \
      ),


  [_MDIA] =  LAYOUT_wrapper( \

      KC_____, _________________LYOUT_____________________,                   _________________RGB_1_____________________, KC_____, \
      KC_____, _________________KC_BLANK__________________,                   _________________RGB_2_____________________, KC_____, \
      KC_____, _________________KC_BLANK__________________,                   _________________MEDIA_____________________, KC_____, \
                                          KC_____, KC_____, KC_____, KC_____, KC_____, KC_____ \
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

