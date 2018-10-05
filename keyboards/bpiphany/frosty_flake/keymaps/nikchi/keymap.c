#include "frosty_flake.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "process_unicode.h"
#include "process_unicodemap.h"
#include "quantum.h"

#define _______ KC_TRNS
#define MAXEMOJITAPS 80


//declarations for tap dancing emojis
void register_hex32(uint32_t hex);
void cycleEmojis(qk_tap_dance_state_t *state, void *user_data);
void cycleAnimals(qk_tap_dance_state_t *state, void *user_data);
void cycleFoods(qk_tap_dance_state_t *state, void *user_data);
void cycleEtc(qk_tap_dance_state_t *state, void *user_data);
void cycleAll(qk_tap_dance_state_t *state, void *user_data);

void tap(uint16_t keycode){
    register_code(keycode);
    unregister_code(keycode);
};

//Tap Dance Declarations
enum taps{
  TD_CTCPS = 0,
  EMOJIS,
  ANIMAL,
  HAND,
  MEMES,
  COPA,
  ALLS
};

enum unicode_name { 
  EMOTIS = 1,//80, //1F60x - 1F64x
  ANIMALS, //64, //1F40x - 1F43x
  SYMBOLS,// = 45, //1F300 - 1F32C
  FOODS,// = 87 , //1F32D - 
  ETC,// = 192, //1F44x -1F4Fx
  VEHICLES,// = 83, //1F68x - 1F6Dx
  SUPPLEMENT,// = 32, //1F91x-1F92x
  ALCHEMY,// = 116 //1F70x - 1F773
  
};

enum my_macros {
  NEWDESK = 0,
  LEFTDESK,
  RIGHTDESK,
  CLOSEDESK
};


// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for CTRL, twice for Caps Lock
  [TD_CTCPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_CAPS),
  [COPA]  = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_C), LCTL(KC_V)),
  [EMOJIS] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(cycleEmojis, NULL, NULL, 800),
  [ANIMAL] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(cycleAnimals, NULL, NULL, 800),
  //[SYMBOLS] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(cycleSymbols, NULL, NULL, 800),
  [FOODS] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(cycleFoods, NULL, NULL, 800),
  [ETC] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(cycleEtc, NULL, NULL, 800),
  //[VEHICLES] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(cycleVehicles, NULL, NULL, 800),
  //[SUPPLEMENT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(cycleSupplement, NULL, NULL, 800),
  [ALLS] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(cycleAll, NULL, NULL, 800)
// Other declarations would go here, separated by commas, if you have them
};

// macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case NEWDESK: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(1), D(LGUI), D(LCTL), D(D), U(LGUI), U(LCTL), U(D), END  ); // NEW DESKTOP
      }
      break;
    case LEFTDESK: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(1), D(LGUI), D(LCTL), D(LEFT), U(LGUI), U(LCTL), U(LEFT), END  ); // LEFT DESKTOP
      }
      break;
    case RIGHTDESK: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(1), D(LGUI), D(LCTL), D(RGHT), U(LGUI), U(LCTL), U(RGHT), END  ); // RIGHT DESKTOP
      }
      break;
    case CLOSEDESK: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(1), D(LGUI), D(LCTL), D(F4), U(LGUI), U(LCTL), U(F4), END  ); // CLOSE DESKTOP
      }
      break;
  }
  return MACRO_NONE;
};


// emojis in unicode
const uint32_t PROGMEM unicode_map[] = {
  [EMOTIS]     = 0x1F600,
  [ANIMALS]    = 0x1F400,
  [SYMBOLS]    = 0x1F300,
  [FOODS]      = 0x1F32D, 
  [ETC]        = 0x1F440,
  [VEHICLES]   = 0x1F680,
  [SUPPLEMENT] = 0x1F910,
  [ALCHEMY]    = 0x1F700
 };
// Layouts
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP(\
      KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,           KC_PSCR,KC_SLCK,KC_PAUS,                        \
      KC_GRV,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL,KC_BSPC,   KC_INS,KC_HOME,KC_PGUP,  KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS, \
      KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_LBRC,KC_RBRC,KC_BSLS,   KC_DEL, KC_END,KC_PGDN,    KC_P7,  KC_P8,  KC_P9,KC_PPLS, \
      KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,         KC_ENT,                              KC_P4,  KC_P5,  KC_P6,      \
      KC_LSPO,KC_NUBS,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,        KC_RSPC,            KC_UP,            KC_P1,  KC_P2,  KC_P3,KC_PENT, \
 TD(TD_CTCPS),KC_LGUI,KC_LALT,                 KC_SPC,                                KC_LEAD,KC_RGUI, KC_APP,MO(1)  ,  KC_LEFT,KC_DOWN,KC_RGHT,    KC_P0,KC_PDOT),
[1] = KEYMAP(\
    TD(ALLS),  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,           KC_PSCR,KC_SLCK,KC_PAUS,                        \
      KC_GRV, TD(EMOJIS),TD(ANIMAL),TD(ETC),TD(FOODS),   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL,KC_BSPC,   KC_MPRV,KC_MPLY,KC_MNXT,  KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS, \
      KC_TAB,   KC_Q,   M(0),   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P, KC_UP  ,KC_RBRC,KC_BSLS,   KC_MUTE,KC_VOLD,KC_VOLU,    KC_P7,  KC_P8,  KC_P9,KC_PPLS, \
      KC_LCTL,   M(1),   M(3),   M(2),   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_LEFT,KC_RGHT,         KC_ENT,                              KC_P4,  KC_P5,  KC_P6,      \
      KC_LSFT,KC_NUBS,   KC_Z,   KC_X,   KC_C, KC_V,   KC_B,   KC_N,    KC_M,KC_COMM, KC_DOT,KC_DOWN,        KC_RSFT,          KC_MS_U,            KC_P1,  KC_P2,  KC_P3,KC_PENT, \
      KC_BTN1,KC_BTN3,KC_BTN2,                 KC_SPC,                                KC_RALT,KC_RGUI, TG(2),_______  ,  KC_MS_L,KC_MS_D,KC_MS_R,    KC_P0,KC_PDOT),
[2] = KEYMAP(\
      KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,           KC_PSCR,KC_SLCK,KC_PAUS,                        \
      KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL,KC_BSPC,   KC_MPRV,KC_MPLY,KC_MNXT,  KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS, \
      KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_LBRC,KC_RBRC,KC_BSLS,   KC_MUTE,KC_VOLD,KC_VOLU,    KC_P7,  KC_P8,  KC_P9,KC_PPLS, \
      KC_LCTL,   KC_D,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,         KC_ENT,                              KC_P4,  KC_P5,  KC_P6,      \
      KC_LSFT,KC_NUBS,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,        KC_RSFT,          KC_MS_U,            KC_P1,  KC_P2,  KC_P3,KC_PENT, \
      KC_BTN1,KC_BTN3,KC_BTN2,                 KC_SPC,                                KC_RALT,KC_RGUI, TG(2) , KC_NO ,  KC_MS_L,KC_MS_D,KC_MS_R,    KC_P0,KC_PDOT),
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_TWO_KEYS(KC_A, KC_A) { // select all and copy
      register_code(KC_LCTL);
      tap(KC_A);
      tap(KC_C);
      unregister_code(KC_LCTL);
    }
  }
}

void matrix_init_user(void) {
  _delay_ms(500);
  set_unicode_input_mode(UC_WINC);
};

void cycleAll(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[EMOTIS]));
    unicode_input_finish();
  }
  else if(state->count <= 1642) {
    tap(KC_BSPC);
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[1])+state->count);
    unicode_input_finish();
  }
};


void cycleEmojis(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[EMOTIS]));
    unicode_input_finish();
  }
  else if(state->count <= 80) {
    tap(KC_BSPC);
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[EMOTIS])+state->count);
    unicode_input_finish();
  }
};

void cycleAnimals(qk_tap_dance_state_t *state, void *user_data) { 
  if(state->count == 1) {
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[ANIMALS]));
    unicode_input_finish();
  }
  else if(state->count <= MAXEMOJITAPS) {
    tap(KC_BSPC);
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[ANIMALS])+state->count);
    unicode_input_finish();
  }
};

void cycleFoods(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[FOODS]));
    unicode_input_finish();
  }
  else if(state->count <= 87) {
    tap(KC_BSPC);
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[FOODS])+state->count);
    unicode_input_finish();
  }
};


void cycleEtc(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[ETC]));
    unicode_input_finish();
  }
  else if(state->count <= MAXEMOJITAPS) {
    tap(KC_BSPC);
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[ETC])+state->count);
    unicode_input_finish();
  }
};

