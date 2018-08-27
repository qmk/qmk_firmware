// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MACRO 3

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
  MACRO,
  DBLQ,
  ITERML, ITERMD, ITERMU, ITERMR
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | Ctrl | Lower|GUIEnt| Alt  |Rs/Spc| Macro| Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,          KC_Y,    KC_U,               KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,          KC_H,    KC_J,               KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,          KC_N,    KC_M,               KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT},
  {KC_CAPS, BACKLIT, XXXXXXX, KC_LCTL, LOWER, GUI_T(KC_ENT), KC_LALT, LT(_RAISE, KC_SPC), MACRO, KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |buttn1|buttn3|buttn2| home |  left| down |  up  | right|wheelu| pgup |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |  end |mousel|moused|mouseu|mouser|wheeld|pgdown|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |bcklit|      |      |      |      |      |      |      |      |light-|light+|      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    _______},
  {_______, _______, KC_BTN1, KC_BTN3, KC_BTN2, KC_HOME, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_WH_U, KC_PGUP},
  {_______, _______, _______, _______, _______, KC_END,  KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,  KC_WH_D, KC_PGDOWN},
  {BACKLIT, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLCK,  KC_PAUS, KC_MNXT }
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   +  |   {  |   }  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   _  |   =  |   [  |   ]  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Reset|      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,  KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL},
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINUS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_UNDS,  KC_EQL,  KC_LBRC, KC_RBRC, KC_PIPE},
  {RESET,   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______}
},

/* Macro
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |iTermL|iTermD|iTermU|iTermR|      |swift"|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_MACRO] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______},
  {_______, _______, _______, _______, _______, _______, ITERML ,  ITERMD,  ITERMU,  ITERMR,  _______, DBLQ   },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______}
}
};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);

float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case MACRO:
     if (record->event.pressed) {
            layer_on(_MACRO);
          } else {
            layer_off(_MACRO);
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
    case DBLQ: // Swift quotes
      if (record->event.pressed) {
          SEND_STRING("\\()");
          SEND_STRING(SS_TAP(X_LEFT));
          return false;
          break;
        }
      return false;
      break;
    case ITERML:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_LEFT))));
      }
      return false;
      break;
    case ITERMD:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_DOWN))));
      }
      return false;
      break;
    case ITERMU:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_UP))));
      }
      return false;
      break;
    case ITERMR:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_RIGHT))));
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE
void led_set_user(uint8_t usb_led)
{
    static uint8_t old_usb_led = 0;

    _delay_ms(10); // gets rid of tick

    if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
            // If CAPS LK LED is turning on...
            PLAY_SONG(tone_caps_on);
    }
    else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
            // If CAPS LK LED is turning off...
            PLAY_SONG(tone_caps_off);
    }
    old_usb_led = usb_led;
}

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_goodbye);
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
