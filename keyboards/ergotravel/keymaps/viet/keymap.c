#include "ergotravel.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "mousekey.h"
#include "process_unicode.h"
extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _NUMBERS 1
#define _SYMBOLS 2
#define _CODING 3
#define _NAVIGATION 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ADJUST,
  CODING_SPACE,
  NUMBERS_SPACE,
  SYMBOLS_SPACE,
  NAVIGATE_SPACE,
  TABLE_FLIP,
  RESET_TABLE,
  SHRUG,
  LOOK_OF_DISAPPROVAL
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_ADJT MO(_ADJUST)
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

#define KC_RSEN MT(MOD_RSFT, KC_ENT) // Tap for enter, hold for right shift

#define KC_LCCA MT(MOD_LCTL, KC_CAPS)  // Tap for caps lock, hold for left control
#define KC_SHDE MT(MOD_LSFT, KC_DEL) // Tap for delete, hold for left shift

#define KC_NAVI MO(_NAVIGATION)

#define KC_COSP CODING_SPACE
#define KC_NUSP NUMBERS_SPACE
#define KC_SYSP SYMBOLS_SPACE
#define KC_NASP NAVIGATE_SPACE

#define KC_FLIP TABLE_FLIP
#define KC_TSET RESET_TABLE
#define KC_SRUG SHRUG
#define KC_DISA LOOK_OF_DISAPPROVAL
#define KC_RST RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
       TAB , Q  , W  , E  , R  , T  ,HOME,      PGUP, Y  , U  , I  , O  , P  ,BSPC,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
       LCCA, A  , S  , D  , F  , G  ,END ,      PGDN, H  , J  , K  , L  ,SCLN,QUOT,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
       SHDE, Z  , X  , C  , V  , B  ,LGUI,      RALT, N  , M  ,COMM,DOT ,SLSH,RSEN,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
       ESC ,ADJT,LALT,ENT ,NUSP,NASP,                SYSP,COSP,RCTL,NAVI,ADJT,DEL
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_NUMBERS] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
      GRAVE, 1  , 2  , 3  , 4  , 5  ,MPLY,      VOLU,  6  , 7  , 8  , 9  , 0 ,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,MNXT,      VOLD,FLIP,TSET,SRUG,DISA,    ,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,    ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_SYMBOLS] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
      GRAVE,EXLM, AT ,HASH,DLR ,PERC,MPLY,      VOLU,CIRC,AMPR,ASTR,LPRN,RPRN,BSLS,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,MNXT,      VOLD,    ,    ,    ,    ,    ,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,    ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_CODING] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
           ,    ,    ,LCBR,RCBR,    ,MPLY,      VOLU,    ,AMPR,PIPE,DLR ,    ,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,LPRN,RPRN,    ,MNXT,      VOLD,    ,UNDS,MINS,ASTR,    ,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,LBRC,RBRC,    ,    ,          ,    ,PLUS,EQL ,    ,    ,    ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_NAVIGATION] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
           ,    ,    , UP ,    ,    ,MPLY,      VOLU,WH_U,BTN1,MS_U,BTN1,    ,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,LEFT,DOWN,RGHT,    ,MNXT,      VOLD,WH_D,MS_L,MS_D,MS_R,    ,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,    ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
    //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
       F1  ,F2  ,F3  ,F4  ,F5  ,F6  ,    ,          ,F7  ,F8  ,F9  ,F10 ,F11 ,F12 ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,RTOG,RVAI,RHUI,RSAI,    ,    ,          ,    ,    ,    ,    ,    ,    ,
    //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
           ,RMOD,RVAD,RHUD,RSAD,    ,    ,          ,RST ,    ,    ,    ,    ,    ,
    //|----+----+----+----+----+----+----.     .----+----+----+----+----+----+----|
           ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,
    //`----+----+----+--+-+----/----/               \----\----+----+----+----+----'
  )

};


#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

uint16_t custom_lt_timer;
keypos_t prv_key_pressed;
// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
//    set_unicode_input_mode(UC_LNX); // Linux
    set_unicode_input_mode(UC_OSX); // Mac OSX
//    set_unicode_input_mode(UC_WIN); // Windows (with registry key, see wiki)
    //set_unicode_input_mode(UC_WINC); // Windows (with WinCompose, see wiki)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if(record->event.pressed) prv_key_pressed = record->event.key;
    #define IS_KEYPOS_SAME(keyone,keytwo)  ((keyone.col==keytwo.col)&&(keyone.row==keytwo.row))
    #define ANOTHER_KEY_PRESSED (!IS_KEYPOS_SAME(prv_key_pressed, record->event.key))

  inline void tap(uint16_t keycode) {
    register_code(keycode);
    unregister_code(keycode);
  };

  inline void swapInput(void) {
    register_code(KC_LGUI);
    tap(KC_SPC);
    unregister_code(KC_LGUI);
  };

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case CODING_SPACE:
      if (record->event.pressed) {
        custom_lt_timer = timer_read();
        layer_on(_CODING);
      } else {
        layer_off(_CODING);
        if (timer_elapsed(custom_lt_timer)<150 && (!ANOTHER_KEY_PRESSED)) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
        }
      }
      return false;
      break;
    case NUMBERS_SPACE:
      if (record->event.pressed) {
        custom_lt_timer = timer_read();
        layer_on(_NUMBERS);
      } else {
        layer_off(_NUMBERS);
        if (timer_elapsed(custom_lt_timer)<150 && (!ANOTHER_KEY_PRESSED)) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
        }
      }
      return false;
      break;
    case SYMBOLS_SPACE:
      if (record->event.pressed) {
        custom_lt_timer = timer_read();
        layer_on(_SYMBOLS);
      } else {
        layer_off(_SYMBOLS);
        if (timer_elapsed(custom_lt_timer)<150 && (!ANOTHER_KEY_PRESSED)) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
        }
      }
      return false;
      break;
    case NAVIGATE_SPACE:
      if (record->event.pressed) {
        custom_lt_timer = timer_read();
        layer_on(_NAVIGATION);
      } else {
        layer_off(_NAVIGATION);
        if (timer_elapsed(custom_lt_timer)<150 && (!ANOTHER_KEY_PRESSED)) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
        }
      }
      return false;
      break;
    case TABLE_FLIP:
      if (record->event.pressed) {
        swapInput();

        register_code(KC_RSFT);
        tap(KC_9);
        unregister_code(KC_RSFT);
        process_unicode((0x256F|QK_UNICODE), record);   // Arm
        process_unicode((0x00B0|QK_UNICODE), record);   // Eye
        process_unicode((0x25A1|QK_UNICODE), record);   // Mouth
        process_unicode((0x00B0|QK_UNICODE), record);   // Eye
        register_code(KC_RSFT);
        tap(KC_0);
        unregister_code(KC_RSFT);
        process_unicode((0x256F|QK_UNICODE), record);   // Arm
        tap(KC_SPC);
        process_unicode((0x0361|QK_UNICODE), record);   // Flippy
        tap(KC_SPC);
        process_unicode((0x253B|QK_UNICODE), record);   // Table
        process_unicode((0x2501|QK_UNICODE), record);   // Table
        process_unicode((0x253B|QK_UNICODE), record);   // Table

        swapInput();
      }
      return false;
      break;
    case RESET_TABLE: // ┬──┬ ノ( ゜-゜ノ)
      if (record->event.pressed) {
        swapInput();

        process_unicode((0x252C|QK_UNICODE), record);   // Table
        process_unicode((0x2500|QK_UNICODE), record);   // Table
        process_unicode((0x2500|QK_UNICODE), record);   // Table
        process_unicode((0x252C|QK_UNICODE), record);   // Table
        tap(KC_SPC);
        process_unicode((0x30CE|QK_UNICODE), record);   // Arm
        register_code(KC_RSFT);
        tap(KC_9);
        unregister_code(KC_RSFT);
        tap(KC_SPC);
        process_unicode((0x309C|QK_UNICODE), record);   // Eye
        tap(KC_MINS);
        process_unicode((0x309C|QK_UNICODE), record);   // Eye
        process_unicode((0x30CE|QK_UNICODE), record);   // Arm
        register_code(KC_RSFT);
        tap(KC_0);
        unregister_code(KC_RSFT);

        swapInput();
      }
      return false;
      break;
    case SHRUG: // ¯\_(ツ)_/¯
      if (record->event.pressed) {
        swapInput();

        process_unicode((0x00AF|QK_UNICODE), record);   // Hand
        tap(KC_BSLS);                                   // Arm
        register_code(KC_RSFT);
        tap(KC_UNDS);                                   // Arm
        tap(KC_LPRN);                                   // Head
        unregister_code(KC_RSFT);
        process_unicode((0x30C4|QK_UNICODE), record);   // Face
        register_code(KC_RSFT);
        tap(KC_RPRN);                                   // Head
        tap(KC_UNDS);                                   // Arm
        unregister_code(KC_RSFT);
        tap(KC_SLSH);                                   // Arm
        process_unicode((0x00AF|QK_UNICODE), record);   // Hand

        swapInput();
      }
      return false;
      break;
    case LOOK_OF_DISAPPROVAL:       // ಠ_ಠ
      if(record->event.pressed){
        swapInput();

        process_unicode((0x0CA0|QK_UNICODE), record);   // Eye
        register_code(KC_RSFT);
        tap(KC_MINS);
        unregister_code(KC_RSFT);
        process_unicode((0x0CA0|QK_UNICODE), record);   // Eye

        swapInput();
      }
      return false;
      break;
  }
  return true;
}
