#include QMK_KEYBOARD_H

enum layers {
  _COLEMAK = 0,
  _EXTEND,
  _SYMBOLS
};

enum custom_keycodes {
  EXT_CTL = SAFE_RANGE,
  EXT_ALT,
  EXT_GUI,
  EXT_SFT
};

#define C_A LCTL_T(KC_A)
#define C_O RCTL_T(KC_O)

#define EXT_SPC LT(_EXTEND, KC_SPC)
#define SYM_SPC LT(_SYMBOLS, KC_SPC)

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EXT_SPC:
    case SYM_SPC:
    case LSFT_T(KC_ESC):
    case RSFT_T(KC_TAB):
      return true;
    default:
      return false;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
   //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_MINS,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_ESC,  C_A,     KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    C_O,     KC_QUOT,
   //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_BSPC,          KC_ENT,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,
   //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_LGUI, SYM_SPC, LSFT_T(KC_ESC),            RSFT_T(KC_TAB),  EXT_SPC, KC_RGUI
                                 // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
      ),

  [_EXTEND] = LAYOUT(
   //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, KC_BRID, KC_BRIU, RGB_TOG, RGB_VAD, RGB_VAI,                            KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, XXXXXXX,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_HOME, KC_PGUP, XXXXXXX, XXXXXXX, KC_DEL,  XXXXXXX,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, EXT_CTL, EXT_ALT, EXT_GUI, EXT_SFT, XXXXXXX,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC, XXXXXXX,
   //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______, KC_END,  KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
                                 // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
      ),

  [_SYMBOLS] = LAYOUT(
   //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_GRV,  KC_EXLM, KC_AT,   KC_LBRC, KC_RBRC, KC_BSLS,                            XXXXXXX, KC_7,    KC_8,    KC_9,    KC_PAST, KC_PSLS,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, KC_PIPE,                            XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_PMNS,
   //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, _______,          _______, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   XXXXXXX, KC_PEQL,
   //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, KC_P0,   _______
                                 // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
      )
};

static uint16_t one_shot_mod_mask = 0;
static uint16_t ctl_timer, alt_timer, gui_timer, sft_timer;

void handle_ex_mod(keyrecord_t *record, uint16_t mod, uint16_t *timer) {
  if (record->event.pressed) {
    *timer = record->event.time;
    register_code(mod);
  } else {
    if (record->event.time - *timer <= TAPPING_TERM) {
      one_shot_mod_mask ^= MOD_BIT(mod);
    } else {
      one_shot_mod_mask &= ~MOD_BIT(mod);
    }
    unregister_code(mod);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EXT_CTL:
      handle_ex_mod(record, KC_LCTL, &ctl_timer);
      return false;
    case EXT_ALT:
      handle_ex_mod(record, KC_LALT, &alt_timer);
      return false;
    case EXT_GUI:
      handle_ex_mod(record, KC_LGUI, &gui_timer);
      return false;
    case EXT_SFT:
      handle_ex_mod(record, KC_LSFT, &sft_timer);
      return false;
    case EXT_SPC:
      if (record->event.pressed) {
        clear_oneshot_mods();
      } else {
        if (one_shot_mod_mask) {
          set_oneshot_mods(one_shot_mod_mask);
        }
      }
      one_shot_mod_mask = 0;
      return true;
    case KC_ESC:
      if (get_oneshot_mods()) {
        clear_oneshot_mods();
        return false;
      } else {
        return true;
      }
    default:
      return true;
  }
}
