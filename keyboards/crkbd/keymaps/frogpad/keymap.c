 /* Copyright 2021 konomu 
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 
#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

enum custom_layers {
    _FROG,
    _SYM,
    _NUM,
    _EXT,
};

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
      XXXXXXX, KC_WBAK, KC_HOME,   KC_UP,  KC_END, KC_WFWD,                      KC_WFWD, KC_HOME,   KC_UP,  KC_END, KC_WBAK, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    ATAB, KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL,                       KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT,    ATAB, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), C(KC_V),    OALT,                         OALT, C(KC_V), C(KC_C), C(KC_X), C(KC_Z), XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             OSFT,    OCTL,    CBSP,       CBSP,    OCTL,    OSFT \
                                      //`--------------------------'  `--------------------------'
    )
};

uint8_t RGB_current_mode;

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
      RGB_current_mode = rgblight_get_mode();
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED init and update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
void matrix_master_OLED_init (void) {
    TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
    iota_gfx_init();   // turns on the display
}

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}
#endif

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_FROG 0
#define L_SYM 8
#define L_NUM 16
#define L_EXT 64

void iota_gfx_task_user(void) {
#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  struct CharacterMatrix matrix;

  matrix_clear(&matrix);
  matrix_write_P(&matrix, PSTR("USB: "));
#ifdef PROTOCOL_LUFA
  switch (USB_DeviceState) {
    case DEVICE_STATE_Unattached:
      matrix_write_P(&matrix, PSTR("Unattached"));
      break;
    case DEVICE_STATE_Suspended:
      matrix_write_P(&matrix, PSTR("Suspended"));
      break;
    case DEVICE_STATE_Configured:
      matrix_write_P(&matrix, PSTR("Connected"));
      break;
    case DEVICE_STATE_Powered:
      matrix_write_P(&matrix, PSTR("Powered"));
      break;
    case DEVICE_STATE_Default:
      matrix_write_P(&matrix, PSTR("Default"));
      break;
    case DEVICE_STATE_Addressed:
      matrix_write_P(&matrix, PSTR("Addressed"));
      break;
    default:
      matrix_write_P(&matrix, PSTR("Invalid"));
  }
#endif

// Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below

  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(&matrix, PSTR("\n\nLayer: "));
    switch (layer_state) {
        case L_FROG:
           matrix_write_P(&matrix, PSTR("Default"));
           break;
        case L_SYM:
           matrix_write_P(&matrix, PSTR("Symbols"));
           break;
        case L_NUM:
           matrix_write_P(&matrix, PSTR("Numbers"));
           break;
        case L_EXT:
           matrix_write_P(&matrix, PSTR("Extend"));
           break;
        default:
           matrix_write(&matrix, buf);
 }
