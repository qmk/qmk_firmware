#include <stdarg.h>
#include "atreus62.h"
#include "led.h"
#include "action_layer.h"
#include "action_util.h"

/*
 *WINDOWS SWEDISH
 */
 /*
  *WINDOWS SWEDISH
  */
 #define KN_HALF KC_GRV          // 1/2
 #define KN_PLUS KC_MINS         // +
 #define KN_ACUT KC_EQL          // ´
 #define KN_AO	 KC_LBRC         // Å
 #define KN_UMLA KC_RBRC         // ¨
 #define KN_OE	 KC_SCLN         // Ö
 #define KN_AE	 KC_QUOT         // Ä
 #define KN_QUOT KC_NUHS         // '
 #define KN_LABK KC_NUBS         // <
 #define KN_MINS KC_SLSH         // -
 #define KN_EXLM LSFT(KC_1)      // !
 #define KN_DQT  LSFT(KC_2)      // "
 #define KN_AT   RALT(KC_2)      // @
 #define KN_HASH LSFT(KC_3)      // #
 #define KN_EUR  LSFT(KC_4)      // €
 #define KN_DLR  RALT(KC_4)      // $
 #define KN_PERC LSFT(KC_5)      // %
 #define KN_AMPR LSFT(KC_6)      // &
 #define KN_SLSH LSFT(KC_7)      // /
 #define KN_LPRN LSFT(KC_8)      // (
 #define KN_RPRN LSFT(KC_9)      // )
 #define KN_EQL  LSFT(KC_0)      // =
 #define KN_UNDS LSFT(KN_MINS)   // _
 #define KN_QUES LSFT(KN_PLUS)   // ?
 #define KN_GRAV LSFT(KN_ACUT)   // `
 #define KN_LCBR RALT(KC_7)      // {
 #define KN_RCBR RALT(KC_0)      // }
 #define KN_LBRC RALT(KC_8)      // [
 #define KN_RBRC RALT(KC_9)      // ]
 #define KN_RABK LSFT(KN_LABK)   // <
 #define KN_COLN LSFT(KC_DOT)    // :
 #define KN_SCLN LSFT(KC_COMM)   // :
 #define KN_PIPE RALT(KN_LABK)   // |
 #define KN_QUES LSFT(KN_PLUS)   // ?
 #define KN_CIRC LSFT(KN_UMLA)   // ^
 #define KN_ASTR LSFT(KN_QUOT)   // *
 #define KN_TILD RALT(KN_UMLA)   // ~
 #define KN_BSLS RALT(KN_PLUS)   //

#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LSFT OSM(MOD_LSFT)

#define KC_HYP LSFT(LALT(LCTL(KC_LGUI)))

#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)
#define KC_UNDO LCTL(KC_Z)
#define KC_REDO LCTL(LSFT(KC_Z))

// Layers
enum {
  BASE = 0,
  NAV,
  SYM
};

//Macros
enum {
  KF_1 = 0, // 1, F1
  KF_2, // ...
  KF_3,
  KF_4,
  KF_5,
  KF_6,
  KF_7,
  KF_8,
  KF_9,
  KF_10,
  KF_11,
  KF_12
};

// Tapdance
enum {
  TD_FUN = 0,
  TD_EQ
};

//State and timers
uint16_t kf_timers[12];


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = {

   { M(KF_11) ,M(KF_1)  ,M(KF_2)  ,M(KF_3)  ,M(KF_4) ,M(KF_5)  ,KC_NO   ,M(KF_6) ,M(KF_7) ,M(KF_8) ,M(KF_9) ,M(KF_10) ,M(KF_12) },
   { KC_TAB   ,KC_Q     ,KC_W     ,KC_E     ,KC_R    ,KC_T     ,KC_NO   ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P     ,KN_AO },
   { OSM_LCTL ,KC_A     ,KC_S     ,KC_D     ,KC_F    ,KC_G     ,KC_NO   ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KN_OE    ,KN_AE },
   { OSM_LSFT ,KC_Z     ,KC_X     ,KC_C     ,KC_V    ,KC_B     ,KC_DELT ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KN_MINS  ,OSM_LSFT },
   { MO(NAV)  ,OSM_LCTL ,OSM_LALT ,KC_LGUI  ,MO(SYM) ,KC_BSPC  ,KC_ENT  ,KC_SPC  ,MO(SYM) ,KC_LEAD ,KC_LALT ,KC_LCTRL ,KC_HYP }

 },
  [NAV] = {

   { KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS },
   { KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_NO   ,KC_HOME  ,KC_PGDN  ,KC_PGUP  ,KC_END   ,KC_TRNS  ,KC_TRNS },
   { KC_TRNS  ,KC_LSFT  ,KC_LCTL  ,KC_LALT  ,KC_L     ,KC_TRNS  ,KC_NO   ,KC_LEFT  ,KC_DOWN  ,KC_UP    ,KC_RIGHT ,KC_TRNS  ,KC_TRNS },
   { KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS },
   { KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_VOLD  ,KC_VOLU }

  },
  [SYM] = {

   { KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,TD(TD_EQ) ,KC_NO   ,TD(TD_FUN) ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS },
   { KC_TRNS  ,KN_LABK  ,KN_RABK  ,KN_LCBR  ,KN_RCBR  ,KN_PLUS   ,KC_NO   ,KN_AT      ,KN_DQT   ,KN_QUOT  ,KN_GRAV  ,KN_SLSH  ,KC_TRNS },
   { KC_TRNS  ,KN_EXLM  ,KN_EQL   ,KN_LPRN  ,KN_RPRN  ,KN_MINS   ,KC_NO   ,KN_UNDS    ,KN_CIRC  ,KN_DLR   ,KN_AMPR  ,KN_PIPE  ,KC_TRNS },
   { KC_TRNS  ,KN_EUR   ,KN_PERC  ,KN_LBRC  ,KN_RBRC  ,KN_ASTR   ,KC_TRNS ,KN_HASH    ,KN_SCLN  ,KN_COLN  ,KN_QUES  ,KN_BSLS  ,KC_TRNS },
   { KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS   ,KC_TRNS ,KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS }

  }
};

#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)

static void m_tapn (uint8_t code, ...) {
  uint8_t kc = code;
  va_list ap;

  va_start(ap, code);
  do {
    register_code(kc);
    unregister_code(kc);
    wait_ms(50);
    kc = va_arg(ap, int);
  } while (kc != 0);
  va_end(ap);
}

static void m_handle_kf (keyrecord_t *record, uint8_t id) {
  uint8_t code = id - KF_1;

  if (record->event.pressed) {
    kf_timers[code] = timer_read ();
  } else {
    uint8_t kc_base;
    uint8_t long_press = (kf_timers[code] && timer_elapsed (kf_timers[code]) > TAPPING_TERM);

    kf_timers[code] = 0;

    switch(id){
      case KF_1 ... KF_10:
        if (long_press) {
          // Long press
          kc_base = KC_F1;
        } else {
          kc_base = KC_1;
        }
        code += kc_base;
        break;
      case KF_11:
        code = long_press ? KC_F11 : KC_ESC;
        break;
      case KF_12:
        code = long_press ? KC_F12 : KN_PLUS;
        break;
    }
    register_code (code);
    unregister_code (code);
  }
}

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch (id) {
    case KF_1 ... KF_12:
      m_handle_kf(record, id);
      break;
  }
  return MACRO_NONE;
};

// Custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool queue = true;

  //Cancle one-shot mods.
  switch (keycode) {
    case KC_ESC:
      if (record->event.pressed && get_oneshot_mods() && !has_oneshot_mods_timed_out()) {
        clear_oneshot_mods();
        queue = false;
      }
      break;
  }
  return queue;
}

// TAP DANCE SETTINGS
void dance_eq (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // ===
      register_code(KC_LSHIFT);
      m_tapn(KC_0, KC_0, KC_0, 0);
      unregister_code(KC_LSHIFT);
      break;
    case 2:
      register_code(KC_LSHIFT);
      m_tapn(KC_1, KC_0, KC_0, 0);
      unregister_code(KC_LSHIFT);
      break;
    default:
      reset_tap_dance(state);
  }
}

void dance_fun (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // =>
      register_code(KC_LSHIFT);
      m_tapn(KC_0, KN_LABK, 0);
      unregister_code(KC_LSHIFT);
      break;
    case 2: // () => {}
      register_code(KC_LSHIFT);
      m_tapn(KC_8, KC_9, KC_SPC, KC_0, KN_LABK, KC_SPC, 0);
      unregister_code(KC_LSHIFT);
      register_code(KC_RALT);
      m_tapn(KC_7, 0);
      unregister_code(KC_RALT);
      TAP_ONCE(KC_ENT);
      break;
    default:
      reset_tap_dance(state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_FUN] = ACTION_TAP_DANCE_FN (dance_fun)
 ,[TD_EQ] = ACTION_TAP_DANCE_FN (dance_eq)
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  set_unicode_input_mode(UC_WINC);
};

LEADER_EXTERNS();
// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    SEQ_ONE_KEY(KC_L){
      register_code(KC_RGUI);
      TAP_ONCE(KC_L);
      unregister_code(KC_RGUI);
    };


    SEQ_TWO_KEYS (KC_A, KC_W) {
      //Web - chrome
      register_code (KC_LGUI); TAP_ONCE (KC_1); unregister_code (KC_LGUI);
    }
    SEQ_TWO_KEYS (KC_A, KC_P) {
      //sPotify
      register_code (KC_LGUI); TAP_ONCE (KC_2); unregister_code (KC_LGUI);

    }
    SEQ_TWO_KEYS (KC_A, KC_T) {
      //Total Commander
      register_code (KC_LGUI); TAP_ONCE (KC_3); unregister_code (KC_LGUI);

    }
    SEQ_TWO_KEYS (KC_A, KC_A) {
      //Atom
      register_code (KC_LGUI); TAP_ONCE (KC_4); unregister_code (KC_LGUI);

    }
    SEQ_TWO_KEYS (KC_A, KC_E) {
      //Emacs
      register_code (KC_LGUI); TAP_ONCE (KC_5); unregister_code (KC_LGUI);

    }
    SEQ_TWO_KEYS (KC_A, KC_C) {
      //Cmdr
      register_code (KC_LGUI); TAP_ONCE (KC_6); unregister_code (KC_LGUI);

    }
    SEQ_TWO_KEYS (KC_A, KC_S) {
      //Slack
      register_code (KC_LGUI); TAP_ONCE (KC_7); unregister_code (KC_LGUI);
    }

    SEQ_TWO_KEYS (KC_U, KC_L) {
      set_unicode_input_mode(UC_LNX);
    }


    SEQ_TWO_KEYS (KC_U, KC_W) {
      set_unicode_input_mode(UC_WINC);
    }


    SEQ_TWO_KEYS (KC_S, KC_S) {
      // ¯\_(ツ)_/¯
      unicode_input_start(); register_hex(0xaf); unicode_input_finish();
      register_code (KC_LALT);
      register_code (KC_LCTL);
      TAP_ONCE (KN_PLUS);
      unregister_code (KC_LCTL);
      unregister_code (KC_LALT);

      register_code (KC_RSFT); TAP_ONCE (KC_8); unregister_code (KC_RSFT);
      unicode_input_start (); register_hex(0x30c4); unicode_input_finish();
      register_code (KC_RSFT); TAP_ONCE (KC_9); TAP_ONCE(KC_7); unregister_code (KC_RSFT);
      unicode_input_start (); register_hex(0xaf); unicode_input_finish();
    }

    SEQ_TWO_KEYS (KC_S, KC_F) {
      // 凸(ツ)凸
      unicode_input_start(); register_hex(0x51F8); unicode_input_finish();
      register_code (KC_RSFT); TAP_ONCE (KC_8); unregister_code (KC_RSFT);
      unicode_input_start (); register_hex(0x30c4); unicode_input_finish();
      register_code (KC_RSFT); TAP_ONCE (KC_9); unregister_code (KC_RSFT);
      unicode_input_start (); register_hex(0x51F8); unicode_input_finish();
    }

    SEQ_TWO_KEYS (KC_S, KC_L) {
      // λ
      unicode_input_start();
      register_hex(0x03bb);
      unicode_input_finish();
    }
  };
};
