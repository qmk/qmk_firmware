#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _FROG 0
#define _SYM 1
#define _NUM 2
#define _EXT 3
#define _COLE 4
#define _RAISE 5
#define _EXT2 6

layer_state_t layer_state_set_user(layer_state_t state) {
    combo_disable();
    if (layer_state_cmp(state, _FROG)) {
        combo_enable();
    }
    return state;
}

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//This is the left-handed version.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_FROG] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_F,    KC_D,    KC_N,    KC_I,    KC_G,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LT(_EXT, KC_BSPC),KC_S,    KC_T,    KC_H,    KC_E,    KC_O,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
OSM(MOD_LSFT),    KC_C,    KC_W,    KC_R,    KC_A,    KC_U,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       OSL(_NUM),OSL(_SYM),  KC_SPC,    XXXXXXX, XXXXXXX, XXXXXXX \
                                      //`--------------------------'  `--------------------------'

  ),

  [_SYM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_5,    KC_4,    KC_3, S(KC_2), S(KC_8),                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   KC_BSLS,S(KC_SCLN),KC_SCLN,S(KC_SLSH),    KC_1, KC_SLSH,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    S(KC_GRV),    KC_8,    KC_9,    KC_0, S(KC_9), S(KC_0),                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            XXXXXXX,XXXXXXX,XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
                                      //`--------------------------'  `--------------------------'
    ),

  [_NUM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_PEQL,   KC_P6,   KC_P7,   KC_P8,   KC_P9,  KC_DOT,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PPLS,   KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |-:------+--------+--------+--------+-------+--------|
      KC_PMNS, S(KC_3), S(KC_4), S(KC_5),   KC_P0, KC_COMM,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX,XXXXXXX,OSM(MOD_LGUI),    XXXXXXX, XXXXXXX, XXXXXXX \
                                      //`--------------------------'  `--------------------------'
  ),

    [_EXT] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  //I recommend adding a TO() that leads to your default layer to the first key in the next line. It is left blank for this purpose.
    TO(_COLE), KC_VOLD, KC_HOME,   KC_UP,  KC_END, KC_VOLU,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   XXXXXXX,LCA(KC_TAB), KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_MUTE,C(KC_Z),C(KC_X),C(KC_C),C(KC_V),OSM(MOD_LALT),                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                             OSM(MOD_LSFT),OSM(MOD_LCTL),C(KC_BSPC),    XXXXXXX, XXXXXXX, XXXXXXX \
                                      //`--------------------------'  `--------------------------'
  ),

    [_COLE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, KC_MINS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   LT(_EXT, KC_BSPC),KC_A,  KC_R,    KC_S,    KC_T,    KC_G,                         KC_K,    KC_N,    KC_E,    KC_I,    KC_O, KC_SCLN,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_M,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   KC_LCTL,  KC_LALT, OSM(MOD_LSFT),     KC_SPC,MO(_RAISE),KC_ENT \
                                      //`--------------------------'  `--------------------------'
  ),

    [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_DEL,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_8,    KC_9,    KC_0,  KC_EQL,  KC_GRV, KC_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    TO(_FROG),   KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,                        KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0, KC_PSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   KC_LGUI,  OSM(MOD_LSFT), KC_BSPC,     KC_SPC, XXXXXXX, KC_ENT \
                                      //`--------------------------'  `--------------------------'
  ),
  
    [_EXT2] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  KC_LGUI, LCA(KC_TAB), KC_WH_U, KC_WBAK, KC_WFWD, KC_MS_U,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL, KC_SLEP,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   XXXXXXX, LCTL(KC_A), KC_WH_D, KC_LSFT, KC_LCTL, KC_MS_D,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_VOLU,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
OSM(MOD_LALT),LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),KC_BTN1,               KC_BTN3, KC_BTN2, KC_MS_L, KC_MS_R, KC_MUTE, KC_VOLD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                          OSM(MOD_LSFT),OSM(MOD_LCTL),LCTL(KC_BSPC),     KC_SPC, XXXXXXX, KC_ENT \
                                      //`--------------------------'  `--------------------------'
  )
  /* This is the right-handed version.
  
    [_FROG] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_G,    KC_I,    KC_N,    KC_D,    KC_F,  KC_ESC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_O,    KC_E,    KC_H,    KC_T,    KC_S,LT(_EXT, KC_BSPC),\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_U,    KC_A,    KC_R,    KC_W,    KC_C,OSM(MOD_LSFT),\    
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,     KC_SPC,OSL(_SYM),OSL(_NUM) \
                                      //`--------------------------'  `--------------------------'

  ),

  [_SYM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      S(KC_6), S(KC_2), S(KC_9),S(KC_LBRC),KC_LBRC, KC_TAB,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_SLSH, S(KC_1),S(KC_SLSH),KC_SCLN,S(KC_SCLN),KC_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      S(KC_8), S(KC_7), S(KC_0),S(KC_RBRC),KC_RBRC,S(KC_GRV),\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
                                      //`--------------------------'  `--------------------------'
    ),

  [_NUM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_DOT,    KC_9,    KC_8,    KC_7,    KC_6, KC_PEQL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_5,    KC_4,    KC_3,    KC_2,    KC_1, KC_PPLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_COMM,    KC_0, S(KC_5), S(KC_4), S(KC_3), KC_PMNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX, OSM(MOD_LGUI),XXXXXXX,XXXXXXX \
                                      //`--------------------------'  `--------------------------'
  ),

    [_EXT] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    //I recommend adding a TO() that leads to your default layer to the last key in the next line. It is left blank for this purpose.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_WFWD,  KC_END,   KC_UP, KC_HOME, KC_WBAK, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_DEL, KC_RGHT, KC_DOWN, KC_LEFT,LCA(KC_TAB),XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                OSM(MOD_LALT), C(KC_V), C(KC_C), C(KC_X), C(KC_Z), XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX, C(KC_BSPC),OSM(MOD_LCTL),OSM(MOD_LSFT) \
                                      //`--------------------------'  `--------------------------'
  )
  */
  
  //You should add these layers on to your existing keymap so you can toggle between one-handed usage and two-handed usage. Don't 
  //forget to change the first keycode in _EXT to whatever you name your default layer aside from the frogpad layers. If you add 
  //a TO(_FROG) somewhere on your default layer, you can easily switch between the two.
  
  //Make sure to add "#include "g/keymap_combo.h"" to the top of your keymap.c and add combos.def to the keyboard folder. 
  //Also add "VPATH  +=  keyboards/gboards/" and "COMBO_ENABLE = yes" to rules.mk."
  
  //If you're having trouble with the OSM modifiers include the code for individual tapping terms in this keymap. 
  //You must also use the last six 'define's in the config.h file.

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

