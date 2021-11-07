#include QMK_KEYBOARD_H


#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
#include "unicode.h"
#endif


enum custom_keycodes {
  EMACS = SAFE_RANGE,
  EMACS_1,
  EMACS_2,
};

enum emacs_mode_t {
  EMACS_OFF = 0,
  EMACS_ON = 1,
  EMACS_SUPER,
  EMACS_ALT,
  EMACS_HYPER
};

static uint8_t  emacs_mode = EMACS_OFF;
static uint16_t emacs_delay = 475;
static uint16_t emacs_delay_min = 75;
static uint16_t emacs_delay_max = 725;
static uint16_t emacs_delay_step = 50;

bool process_emacs_modifier(const uint16_t cmd, const uint16_t keycode) {
  clear_mods();
  send_string_with_delay(SS_LCTL(SS_TAP(X_X)) "@", emacs_delay);
  tap_code_delay(cmd, emacs_delay);
  tap_code_delay(keycode, emacs_delay);
  emacs_mode = emacs_mode ? EMACS_ON : EMACS_OFF;
  return false;
}

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case EMACS:
      if (record->event.pressed) emacs_mode = emacs_mode ? EMACS_OFF : EMACS_ON;
      return false;
    case EMACS_1:
      if (record->event.pressed) emacs_delay = max(emacs_delay_min, emacs_delay-emacs_delay_step);
      return false;
    case EMACS_2:
      if (record->event.pressed) emacs_delay = min(emacs_delay_max, emacs_delay+emacs_delay_step);
      return false;
    case KC_LGUI:
      if (record->event.pressed)
        if (emacs_mode > 0) {
          emacs_mode = EMACS_SUPER;
          return false;
        }
    case KC_MEH:
      if (record->event.pressed)
        if (emacs_mode > 0) {
          emacs_mode = EMACS_ALT;
          return false;
        }
    case KC_HYPR:
      if (record->event.pressed)
        if (emacs_mode > 0) {
          emacs_mode = EMACS_HYPER;
          return false;
        }
    default:
      if (record->event.pressed)
        switch (emacs_mode) {
          case EMACS_SUPER:
            return process_emacs_modifier(KC_S, keycode);
          case EMACS_ALT:
            return process_emacs_modifier(KC_A, keycode);
          case EMACS_HYPER:
            return process_emacs_modifier(KC_H, keycode);
          default:
            return true;
        }
  }
  return true;
}


enum userspace_layers {
  _QWERTY,
  _NAVIGATE,
  _NUMERIC,
  _QUANTUM,
  _SYMBOLIC
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_ortho_5x15(
                                KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,
                                KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_INS,
                                MO(1),    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,   KC_PGUP,  KC_DEL,
                                KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_HOME,  KC_UP,    KC_END,
                                MO(3),    KC_LALT,  KC_LGUI,  KC_LCTL,  KC_HYPR,  KC_SPC,   KC_SPC,   MO(1),    KC_MEH,   MO(4),    KC_APP,   KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT),
        
	[_NAVIGATE] = LAYOUT_ortho_5x15(
                                KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  TO(2),
                                KC_NO,    KC_INS,   KC_HOME,  KC_UP,    KC_END,   KC_PGUP,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   KC_INS,   KC_NO,    KC_NO,    KC_NO,    KC_SLCK,
                                KC_TRNS,  KC_DEL,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN,  KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_DEL,   KC_NO,    KC_NO,    KC_NO,    KC_PAUS,
                                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_BSPC,  KC_BSPC,  KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO),
        
	[_NUMERIC] = LAYOUT_ortho_5x15(
                                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_SLSH,  KC_7,     KC_8,     KC_9,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_TRNS,
				KC_NO,	  KC_NO,    KC_NO,    KC_NO,	KC_NO,	  KC_NO,    KC_ASTR,  KC_4,	KC_5,	  KC_6,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
				KC_NO,	  KC_NO,    KC_NO,    KC_NO,	KC_NO,	  KC_NO,    KC_NO,    KC_1,	KC_2,	  KC_3,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
				KC_NO,	  KC_NO,    KC_NO,    KC_NO,	KC_NO,	  KC_NO,    KC_0,     KC_0,	KC_DOT,	  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
				KC_NO,	  KC_NO,    KC_NO,    KC_NO,	KC_NO,	  KC_MINS,  KC_PLUS,  KC_ENT,	KC_NO,	  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO),
        
	[_QUANTUM] = LAYOUT_ortho_5x15(
                                KC_HELP,  KC_BRID,  KC_BRIU,  BL_TOGG,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_MSTP,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MSTP,  KC_NO,    KC_NO,    KC_PWR,
                                RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_M_SW, RGB_M_SN, RGB_M_K,  RGB_M_X,  RGB_M_G,  RGB_M_T,
                                KC_NO,    RGB_RMOD, RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                KC_TRNS,  KC_NO,    EMACS,    KC_NO,    KC_NO,    EMACS_1,  EMACS_2,  RESET,    KC_NO,    KC_NO,    EMACS,    KC_NO,    KC_NO,    KC_NO,    KC_NO),
        
	[_SYMBOLIC] = LAYOUT_ortho_5x15(
                                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                KC_NO,    THETA,    OMEGA,    EPSLN,    RHO,      TAU,      UPSLN,    UPSLN,    IOTA,     OMCRN,    PI,       KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                KC_NO,    ALPHA,    SIGMA,    DELTA,    PHI,      GAMMA,    ETA,      PSI,      KAPPA,    LAMBD,    KC_SCLN,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                KC_LSFT,  ZETA,	    XI,	      CHI,      PHI,      BETA,     NU,       GMU,      KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_NO,    KC_NO,    KC_NO,
                                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO)
};
