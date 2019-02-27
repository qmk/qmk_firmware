#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef USE_I2C
#include "i2c.h"
#endif
#ifdef SSD1306OLED
#include "ssd1306.h"
#endif
extern keymap_config_t keymap_config;

//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _MOUSECURSOR 8
#define _ADJUST 16

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  BACKLIT,
  RGBLED_TOGGLE,
  RGBLED_STEP_MODE,
  RGBLED_INCREASE_HUE,
  RGBLED_DECREASE_HUE,
  RGBLED_INCREASE_SAT,
  RGBLED_DECREASE_SAT,
  RGBLED_INCREASE_VAL,
  RGBLED_DECREASE_VAL,
};

enum macro_keycodes {
  KC_DEMOMACRO,
};

// Custom macros
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define CTL_TTAB    CTL_T(KC_TAB)               // Tap for Esc, hold for Ctrl
#define CTL_ENT     CTL_T(KC_ENT)               // Tap for Enter, hold for Ctrl
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift
// Requires KC_TRNS/_______ for the trigger key in the destination layer
#define LT_MC(kc)   LT(_MOUSECURSOR, kc)        // L-ayer T-ap M-ouse C-ursor
#define LT_RAI(kc)  LT(_RAISE, kc)              // L-ayer T-ap to Raise
#define DEMOMACRO   M(KC_DEMOMACRO)            // Sample for macros


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------+------+------+------+------+------------------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  DEL |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   7  |   8  |   9  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |   A  |   S  |   D  |   F  |   G  |   4  |   5  |   6  |   H  |   J  |   K  |   L  | ;/Nav|  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   1  |   2  |   3  |   N  |   M  |   ,  |   .  |   /  |Ctl/Et|
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |  `   | Ctrl | Alt  | GUI  |Lower |Space |   0  |   .  |   =  |Space |Raise | Left | Down |  Up  |Right |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
  KC_ESC,   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_DEL,\
  KC_TAB,   KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_P7,   KC_P8,   KC_P9,    KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,     KC_BSPC, \
  KC_CAPS,  KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_P4,   KC_P5,   KC_P6,    KC_H,    KC_J,    KC_K,   KC_L,LT_MC(KC_SCLN), KC_QUOT, \
  KC_LSFT,  KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_P1,   KC_P2,   KC_P3,    KC_N,    KC_M,    KC_COMM,KC_DOT,  KC_SLSH,  CTL_ENT, \
  KC_GRV,   KC_LCTRL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_P0,   KC_DOT,  KC_EQL,  KC_SPC,   RAISE,   KC_LEFT,KC_DOWN, KC_UP,    KC_RGHT  \
),

/* Colemak
 * ,------+------+------+------+------+------------------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |   0  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   7  |   8  |   9  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * | CAPS |   A  |   R  |   S  |   T  |   D  |   4  |   5  |   6  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   1  |   2  |   3  |   K  |   M  |   ,  |   .  |   /  |Ctl/Et|
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  | Ctrl | Alt  | GUI  |Lower |Space |   0  |   .  |   =  |Space |Raise | Left | Down |  Up  |Right |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT(
  KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10, KC_DEL,\
  KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_P7,   KC_P8,   KC_P9,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_BSPC, \
  KC_LCTRL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_P4,   KC_P5,   KC_P6,    KC_H,    KC_N,    KC_E,    KC_I, LT_MC(KC_O), KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_P1,   KC_P2,   KC_P3,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  CTL_ENT, \
  KC_GRV,   KC_LCTRL, KC_LGUI, KC_LALT, LOWER,  KC_SPC,  KC_P0,   KC_DOT,  KC_EQL,   KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT  \
  ),

/* Dvorak
 * ,------+------+------+------+------+------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   7  |   8  |   9  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   4  |   5  |   6  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   1  |   2  |   3  |   B  |   M  |   W  |   V  |   Z  |Ctl/Et|
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  | Ctrl | Alt  | GUI  |Lower |Space |   0  |   .  |   =  |Space |Raise | Left | Down |  Up  |Right |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT(
  KC_ESC,   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10, KC_DEL,\
  KC_TAB,   KC_QUOT,  KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_P7,   KC_P8,   KC_P9,    KC_F,    KC_G,   KC_C,    KC_R,    KC_L,     KC_BSPC, \
  KC_LCTL,  KC_A,     KC_O,    KC_E,    KC_U,    KC_I,    KC_P4,   KC_P5,   KC_P6,    KC_D,    KC_H,   KC_T,    KC_N, LT_MC(KC_S), KC_SLSH, \
  KC_LSFT,  KC_SCLN,  KC_Q,    KC_J,    KC_K,    KC_X,    KC_P1,   KC_P2,   KC_P3,    KC_B,    KC_M,   KC_W,    KC_V,    KC_Z,     CTL_ENT, \
  KC_GRV,   KC_LCTRL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_P0,   KC_DOT,  KC_EQL,   KC_SPC,  RAISE,  KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT \
),

/* Lower
 * ,------+------+------+------+------+------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |      |      |      |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |      |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN, KC_DEL, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, KC_F6,   KC_UNDS, KC_PLUS,  KC_LBRC, KC_RBRC, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, _______, _______, KC_F12,S(KC_NUHS),S(KC_NUBS),_______,_______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,------+------+------+------+------+------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |      |      |      |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |      |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, _______, _______, KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, \
  _______, _______, _______, _______,  _______, KC_SPC, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY   \
),

/* Mouse Layer (semi-col)
 * ,------+------+------+------+------+------------------------------------------------.
 * | ACCL0| ACCL1| ACCL2|      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |      |      |      |      |      |      |      |      | Home | Wh_Up| WHL_L| M_Up | WHL_R| Macro|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | End  | Wh_Dn| M_Lft| M_Dn | M_Rt |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | BTN2 | BTN3 | BTN4 | BTN5 |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | BTN1 |      |      |      | BTN1 |      |      |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */

[_MOUSECURSOR] = LAYOUT(
  KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_WH_L, KC_MS_U, KC_WH_R,DEMOMACRO,_______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_END , KC_PGDN, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, _______, _______, \
  _______, _______, _______, _______, _______, KC_BTN1, _______, _______, _______, KC_BTN1, _______, _______, _______, _______, _______  \
),

/* Adjust (Lower + Raise)
 * ,------+------+------+------+------+------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * | Reset|RGB TG|RGB ST|RGBH -|RGBH +|RGBS -|RGBS +|RGBV -|RGBV +|      |      |      |      |      |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|      |      |      |AGswap|Qwerty|Colemk|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|      |      |      |      |      |      |      | BL + |BL ST |BL TG |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  RESET,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, _______, _______, _______, AG_SWAP, QWERTY,  COLEMAK, _______,  _______,  _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF, _______, _______, _______,  _______, BL_DEC,  BL_INC,  BL_STEP, BL_TOGG, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
)



};

// define variables for reactive RGB
bool RGB_INIT = false;
bool TOG_STATUS = false;
int RGB_current_mode;

void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    rgblight_mode(RGB_current_mode);
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (RGB_INIT) {} else {
          RGB_current_mode = rgblight_config.mode;
          RGB_INIT = true;
        }
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(16);
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (RGB_INIT) {} else {
          RGB_current_mode = rgblight_config.mode;
          RGB_INIT = true;
        }
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(15);
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case RGB_MOD:
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      if (record->event.pressed) {
        rgblight_mode(RGB_current_mode);
        rgblight_step();
        RGB_current_mode = rgblight_config.mode;
      }
      return false;
      break;
  }
  return true;
}



/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }

    switch (id) {
      case KC_DEMOMACRO:
        if (record->event.pressed){
          return MACRO (I(1), T(H),T(E),T(L), T(L), T(O), T(SPACE), T(W), T(O), T(R), T(L), T(D),  END);
        }
    }

    return MACRO_NONE;
}


//Functions for ver2
#ifdef KEYBOARD_hadron_ver2
#include "LUFA/Drivers/Peripheral/TWI.h"
void matrix_init_user(void) {
  #ifdef USE_I2C
    i2c_master_init();
  #ifdef SSD1306OLED
  // calls code for the SSD1306 OLED
        _delay_ms(400);
        TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
        iota_gfx_init();   // turns on the display
  #endif
  #endif
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}


void matrix_scan_user(void) {
    #ifdef SSD1306OLED
     iota_gfx_task();  // this is what updates the display continuously
    #endif
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}
//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER 8
#define L_RAISE 16
#define L_FNLAYER 64
#define L_NUMLAY 128
#define L_NLOWER 136
#define L_NFNLAYER 192
#define L_MOUSECURSOR 256
#define L_ADJUST 65560

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
        case L_BASE:
           matrix_write_P(&matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(&matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(&matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
           matrix_write_P(&matrix, PSTR("ADJUST"));
           break;
        default:
           matrix_write(&matrix, buf);
 }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(&matrix, led);
  matrix_update(&display, &matrix);
}

#endif
