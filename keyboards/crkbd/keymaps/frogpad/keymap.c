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

// Layer Mode aliases
#define BSP_EXT LT(_EXT,KC_BSPC)
#define OSYM OSL(_SYM)
#define ONUM OSL(_NUM)
#define OSFT OSM(MOD_LSFT)
#define OGUI OSM(MOD_LGUI)
#define ATAB LCA(KC_TAB)
#define OALT OSM(MOD_LALT)
#define OCTL OSM(MOD_LCTL)
#define CBSP C(KC_BSPC)

//This is the left-handed version.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_FROG] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_F,    KC_D,    KC_N,    KC_I,    KC_G,                         KC_G,    KC_I,    KC_N,    KC_D,    KC_F,  KC_ESC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      BSP_EXT,    KC_S,    KC_T,    KC_H,    KC_E,    KC_O,                         KC_O,    KC_E,    KC_H,    KC_T,    KC_S, BSP_EXT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         OSFT,    KC_C,    KC_W,    KC_R,    KC_A,    KC_U,                         KC_U,    KC_A,    KC_R,    KC_W,    KC_C,    OSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             ONUM,    OSYM,  KC_SPC,     KC_SPC,    OSYM,    ONUM \
                                      //`--------------------------'  `--------------------------'
    ),

    [_SYM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_LBRC, KC_LCBR, KC_LPRN,   KC_AT, KC_CIRC,                      KC_CIRC,   KC_AT, KC_LPRN, KC_LCBR, KC_LBRC,  KC_TAB,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSLS, KC_COLN, KC_SCLN, KC_QUES, KC_EXLM, KC_SLSH,                      KC_SLSH, KC_EXLM, KC_QUES, KC_SCLN, KC_COLN, KC_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD, KC_RBRC, KC_RCBR, KC_RPRN, KC_AMPR, KC_ASTR,                      KC_ASTR, KC_AMPR, KC_RPRN, KC_RCBR, KC_RBRC, KC_TILD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
                                      //`--------------------------'  `--------------------------'
    ),

    [_NUM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_EQL,    KC_6,    KC_7,    KC_8,    KC_9,  KC_DOT,                       KC_DOT,    KC_9,    KC_8,    KC_7,    KC_6,  KC_EQL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PLUS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_5,    KC_4,    KC_3,    KC_2,    KC_1, KC_PLUS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINS, KC_HASH,  KC_DLR, KC_PERC,    KC_0, KC_COMM,                      KC_COMM,    KC_0, KC_PERC,  KC_DLR, KC_HASH, KC_MINS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX,    OGUI,       OGUI, XXXXXXX, XXXXXXX \
                                      //`--------------------------'  `--------------------------'
    ),

    [_EXT] = LAYOUT( \
/*I recommend adding a TO() that leads to your two-handed layer to the first and last key in the next line of code if you 
are adding this keymap to a two-handed keymap. It is left blank for this purpose.*/
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_WBAK, KC_HOME,   KC_UP,  KC_END, KC_WFWD,                      KC_WBAK, KC_HOME,   KC_UP,  KC_END, KC_WFWD, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    ATAB, KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL,                       KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT,    ATAB, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), C(KC_V),    OALT,                         OALT, C(KC_V), C(KC_C), C(KC_X), C(KC_Z), XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             OSFT,    OCTL,    CBSP,       CBSP,    OCTL,    OSFT \
                                      //`--------------------------'  `--------------------------'
    )
  
/* You should add these layers on to your existing keymap so you can toggle between one-handed usage and two-handed usage. Don't 
forget to change the first keycode in _EXT to whatever you name your default layer aside from the frogpad layers. If you add 
a TO(_FROG) somewhere on your default layer, you can easily switch between the two.
  
Make sure to add "#include "g/keymap_combo.h"" to the top of your keymap.c and add combos.def to the keyboard folder. 
Also add "VPATH  +=  keyboards/gboards/" and "COMBO_ENABLE = yes" to rules.mk."
  
If you're having trouble with the OSM modifiers include the code for individual tapping terms in this keymap. 
You must also use the last six 'define's in the config.h file. */

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

