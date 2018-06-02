#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

// config settings
#define TAPPING_TERM 250
#define ONESHOT_TAP_TOGGLE 1
#define ONESHOT_TIMEOUT 10000

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _ONEHANDR 3
#define _ONEHANDL 4
#define _RLAYER 5
#define _LLAYER 6
#define _DUAL 7
#define _CONFIG 8

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  ONEHANDR,
  ONEHANDL,
  RLAYER,
  LLAYER,
  RLOCK,
  LLOCK,
  DUAL,
  CONFIG,
};

/* Tap Dance */
enum {
  TD_LGUIAPP,
  TD_SHIFTCAPS,
};

/* NOOP Key and Transparent */
#define KC_     KC_TRNS
#define KC_XXXX KC_NO

/* LAYERS */
#define KC_LLAY LLAYER
#define KC_RLAY RLAYER
#define KC_RLOK RLOCK
#define KC_LLOK LLOCK
#define KC_QWER QWERTY
#define KC_DVOR DVORAK
#define KC_COLE COLEMAK
#define KC_ONER ONEHANDR
#define KC_ONEL ONEHANDL
#define KC_DUAL DUAL
#define KC_CONF CONFIG

/* Custom Shortened Keys */
#define KC_MCTB LCTL(KC_TAB)
#define KC_MCST LCTL(LSFT(KC_TAB))
#define KC_MCAD LALT(LCTL(KC_DEL))
#define KC_CTEC CTL_T(KC_ESC)
#define KC_SINS LSFT(KC_INS)
#define KC_LGU1 LGUI(KC_1)
#define KC_LGU2 LGUI(KC_2)
#define KC_LGU3 LGUI(KC_3)
#define KC_LGU4 LGUI(KC_4)
#define KC_LGU5 LGUI(KC_5)
#define KC_LGU6 LGUI(KC_6)
#define KC_LGU7 LGUI(KC_7)
#define KC_LGU8 LGUI(KC_8)
#define KC_LGU9 LGUI(KC_9)
#define KC_LGU0 LGUI(KC_0)
#define KC_BLUP BL_INC
#define KC_BLDN BL_DEC
#define KC_SYSR KC_SYSREQ
#define KC_REST RESET

/* Tap Dance */
#define KC_LGUA TD(TD_LGUIAPP)
#define KC_SHCL TD(TD_SHIFTCAPS)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     XXXX, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CTEC, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,ENT ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     SHCL, Z  , X  , C  , V  , B  ,LLOK,     RLOK, N  , M  ,COMM,DOT ,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LLAY,TAB ,        SPC ,RLAY,LGUA
  //                  `----+----+----'        `----+----+----'
  ),

  [_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     XXXX, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CTEC, A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,ENT ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     SHCL, Z  , X  , C  , V  , B  ,LLOK,     RLOK, K  , M  ,COMM,DOT ,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LLAY,TAB ,        SPC ,RLAY,LGUA
  //                  `----+----+----'        `----+----+----'
  ),

  [_DVORAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     XXXX, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB ,QUOT,COMM,DOT , P  , Y  ,                F  , G  , C  , R  , L  ,SLSH,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CTEC, A  , O  , E  , U  , I  ,                D  , H  , T  , N  , S  ,ENT ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     SHCL,SCLN, Q  , J  , K  , X  ,LLOK,     RLOK, B  , M  , W  , V  , Z  ,EQL ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LLAY,TAB ,        SPC ,RLAY,LGUA
  //                  `----+----+----'        `----+----+----'
  ),

  [_ONEHANDR] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,                Y  , U  , I  , O  , P  ,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,QWER,     XXXX, N  , M  ,COMM,DOT ,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       XXXX,XXXX,XXXX,        SPC ,ONEL,ENT
  //                  `----+----+----'        `----+----+----'
  ),

  [_ONEHANDL] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,                5  , 4  , 3  , 2  , 1  ,XXXX,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,                T  , R  , E  , W  , Q  ,TAB ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,                G  , F  , D  , S  , A  ,ENT ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,     XXXX, B  , V  , C  , X  , Z  ,SHCL,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       XXXX,XXXX,XXXX,        SPC ,ONEL,ENT
  //                  `----+----+----'        `----+----+----'
  ),

  [_RLAYER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,SLCK,SYSR,PSCR,INS ,PAUS,               MUTE,VOLD,VOLU,BLDN,BLUP,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,TILD,GRV ,EQL ,LBRC,RBRC,               ASTR,HOME, UP ,PGUP,PLUS,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,EXLM,PIPE,DLR ,LPRN,RPRN,               AMPR,LEFT,DOWN,RGHT,MINS,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         , AT ,HASH,PERC,LCBR,RCBR,    ,         ,CIRC,END ,UNDS,PGDN,BSLS,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----' 
                           ,    ,    ,            ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_LLAYER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,XXXX,XXXX, UP , F5 ,XXXX,               ASTR, 7  , 8  , 9  ,PLUS,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,XXXX,MCST,DOWN,MCTB,ENT ,               SLSH, 4  , 5  , 6  ,MINS,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,XXXX,XXXX,BSPC,SINS,SPC ,F11 ,     F12 ,EQL , 1  , 2  , 3  ,DOT ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,         0  ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_DUAL] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,XXXX,XXXX,XXXX,XXXX,XXXX,               XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,XXXX,XXXX,XXXX,XXXX,XXXX,               XXXX,XXXX,MS_U,XXXX,XXXX,MCAD,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,XXXX,XXXX,XXXX,XXXX,XXXX,               BTN2,MS_L,MS_D,MS_R,BTN1,XXXX,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,LGU1,LGU2,LGU3,LGU4,LGU5,CONF,     XXXX,LGU6,LGU7,LGU8,LGU9,LGU0,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,            ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_CONFIG] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     REST,XXXX,XXXX,XXXX,XXXX,XXXX,               XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     XXXX,QWER,XXXX,XXXX,XXXX,XXXX,               XXXX,XXXX,XXXX,ONER,XXXX,XXXX,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     XXXX,XXXX,XXXX,DVOR,XXXX,XXXX,               XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     XXXX,XXXX,XXXX,COLE,XXXX,XXXX,    ,         ,XXXX,XXXX,XXXX,XXXX,XXXX,XXXX,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       XXXX,    ,XXXX,        XXXX,    ,XXXX
  //                  `----+----+----'        `----+----+----'
  ),
};


/* TAP DANCE */
void shift_caps_down (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 3) {
    register_code (KC_CAPS);
  } else {
    register_code (KC_LSFT);
  }
}

void shift_caps_up (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 3) {
    unregister_code (KC_CAPS);
  } else {
    unregister_code (KC_LSFT);
  }
}
qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_LGUIAPP] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_APP),
        [TD_SHIFTCAPS] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, shift_caps_down, shift_caps_up)
};

/* END TAP DANCE */


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

/* Variables for layer light toggling */
static uint16_t currentBL = 0;
static uint16_t rlocked = 0;
static uint16_t llocked = 0;

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
    case ONEHANDR:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_ONEHANDR);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case CONFIG:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_CONFIG);
        backlight_toggle();
      }
      return false;
      break;
    case RLAYER:
      if (record->event.pressed) {
        layer_on(_RLAYER);
        update_tri_layer(_RLAYER, _LLAYER, _DUAL);
        /* add logic to toggle backlight change when on a layer */
        currentBL = get_backlight_level();
        if ( currentBL == 0 || currentBL == 1 ) {
          backlight_set(5);
        } else {
          backlight_set(0);
        }
      } else {
        unregister_code(KC_LGUI);
        rlocked = 0; 
        layer_off(_RLAYER);
        update_tri_layer(_RLAYER, _LLAYER, _DUAL);
        if ( llocked == 0 ) {
          backlight_set(currentBL);
        } else {
        }
      }
      return false;
      break;
    case LLAYER:
      if (record->event.pressed) {
        layer_on(_LLAYER);
        update_tri_layer(_RLAYER, _LLAYER, _DUAL);
        /* add logic to toggle backlight change when on a layer */
        currentBL = get_backlight_level();
        if ( currentBL == 0 || currentBL == 1 ) {
          backlight_set(5);
        } else {
          backlight_set(0);
        }
      } else {
        llocked = 0; 
        layer_off(_LLAYER);
        update_tri_layer(_RLAYER, _LLAYER, _DUAL);
        if ( rlocked == 0 ) {
          backlight_set(currentBL);
        } else {
        }
      }
      return false;
      break;
    case RLOCK:
      if (record->event.pressed) {
        layer_on(_RLAYER);
        /* add logic to toggle backlight change when on a layer */
        rlocked = 1; 
        currentBL = get_backlight_level();
        if ( currentBL == 0 || currentBL == 1 ) {
          backlight_set(5);
        } else {
          backlight_set(0);
        }
      } else {
      }
      return false;
      break;
    case LLOCK:
      if (record->event.pressed) {
        layer_on(_LLAYER);
        /* add logic to toggle backlight change when on a layer */
        llocked = 1;
        currentBL = get_backlight_level();
        if ( currentBL == 0 || currentBL == 1 ) {
          backlight_set(5);
        } else {
          backlight_set(0);
        }
      } else {
      }
      return false;
      break;
    case ONEHANDL:
      if (record->event.pressed) {
        layer_on(_ONEHANDL);
      } else {
        layer_off(_ONEHANDL);
      }
      return false;
      break;
  }
  return true;
}
