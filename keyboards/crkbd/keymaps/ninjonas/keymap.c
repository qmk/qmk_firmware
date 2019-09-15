#include QMK_KEYBOARD_H
#include "ninjonas.h"	

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper( 
  //,----------------------------------------------------.      ,----------------------------------------------------.
     _____________________QWERTY_L1______________________,       _____________________QWERTY_R1______________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
     _____________________QWERTY_L2______________________,       _____________________QWERTY_R2______________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
     _____________________QWERTY_L3______________________,       _____________________QWERTY_R3______________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
                                    T_GUI, KC_LCTL,LT_RAI,       LT_LOW,KC_BSPC,KC_DEL
                                 //`---------------------'      `---------------------'
  ),

  [_DVORAK] = LAYOUT_wrapper( 
  //,----------------------------------------------------.      ,----------------------------------------------------.
     _____________________DVORAK_L1______________________,       _____________________DVORAK_R1______________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
     _____________________DVORAK_L2______________________,       _____________________DVORAK_R2______________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
     _____________________DVORAK_L3______________________,       _____________________DVORAK_R3______________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
                                    T_GUI, KC_LCTL,LT_RAI,       LT_LOW,KC_BSPC,KC_DEL
                                 //`---------------------'      `---------------------'
  ),

  [_COLEMAK] = LAYOUT_wrapper( 
  //,----------------------------------------------------.      ,----------------------------------------------------.
     _____________________COLEMAK_L1_____________________,       _____________________COLEMAK_R1_____________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
     _____________________COLEMAK_L2_____________________,       _____________________COLEMAK_R2_____________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
     _____________________COLEMAK_L3_____________________,       _____________________COLEMAK_R3_____________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
                                    T_GUI, KC_LCTL,LT_RAI,       LT_LOW,KC_BSPC,KC_DEL
                                 //`---------------------'      `---------------------'
  ),

  [_LOWER] = LAYOUT_wrapper( 
  //,----------------------------------------------------.      ,----------------------------------------------------.
     XXXXXXX, XXXXXXX, _________MEDIA_1_________, XXXXXXX,       _______________NAV_1______________,  XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
     XXXXXXX, XXXXXXX, _________MEDIA_2_________, XXXXXXX,       _______________NAV_2______________,   K_LOCK, XXXXXXX,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
     XXXXXXX, XXXXXXX, _________MEDIA_3_________,  T_LBRC,         T_RBRC, XXXXXXX, XXXXXXX,  M_CODE,  M_ZOOM, M_PYNV,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
                                    _______,_______,_______,     _______,_______,_______
                                 //`---------------------'      `---------------------'
  ),

  [_RAISE] = LAYOUT_wrapper( \
  //,----------------------------------------------------.      ,----------------------------------------------------.
     _____________________NUM_LEFT_______________________,       _____________________NUM_RIGHT______________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
     _____________________SYM_LEFT_______________________,       _____________________SYM_RIGHT______________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
     _____________________FUNC_LEFT______________________,       _____________________FUNC_RIGHT_____________________,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
                                    _______,_______,_______,     _______,_______,_______
                                 //`---------------------'      `---------------------'
  ),

  [_ADJUST] = LAYOUT_wrapper( \
  //,----------------------------------------------------.      ,----------------------------------------------------.
       M_MAKE, EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       RGB_TOG, XXXXXXX, XXXXXXX, COLEMAK,  DVORAK, QWERTY,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
       M_VRSN, XXXXXXX, XXXXXXX, RGB_SAI, RGB_HUI, RGB_VAI,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
       M_FLSH, XXXXXXX, XXXXXXX, RGB_SAD, RGB_HUD, RGB_VAD,       RGB_M_P, RGB_M_B, RGB_M_G,RGB_M_SW, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
                                    _______,_______,_______,     _______,_______,_______
                                 //`---------------------'      `---------------------'
  ),
/*
  [_TEMPLATE] = LAYOUT_wrapper( \
  //,----------------------------------------------------.      ,----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-------|      |--------+--------+--------+--------+--------+-------|
                                    _______,_______,_______,     _______,_______,_______
                                 //`---------------------'      `---------------------'
  ),
*/
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
    //matrix_write_ln(matrix, read_keylogs());
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