#include QMK_KEYBOARD_H

#define MEDAPP LT(MEDIA, KC_APP)

enum layers {
    DEFAULT,
    PROG1,
    PROG2,
    MEDIA,
    MOUSE1,
    MOUSE2,
    MISC,
};

enum custom_keycodes {
    LSHFT_PAREN = SAFE_RANGE,
    RSHFT_PAREN,
    LCTRL_BRACKET,
    RCTRL_BRACKET,
    LALT_CURLY,
    RALT_CURLY,
    CTRL_CLICK,
    M_GRV,
    M_CFLEX
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEFAULT] = LAYOUT(
          KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,           KC_PSCR,KC_SCRL,KC_PAUS,
          KC_GRV,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL,KC_BSPC,    KC_INS,KC_HOME,KC_PGUP,  KC_NUM,KC_PSLS,KC_PAST,KC_PMNS,
          KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_LBRC,KC_RBRC,KC_BSLS,    KC_DEL, KC_END,KC_PGDN,    KC_P7,  KC_P8,  KC_P9,KC_PPLS,
        TT(MOUSE1), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,         KC_ENT,                               KC_P4,  KC_P5,  KC_P6,
            LSHFT_PAREN,KC_NUBS,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,           RSHFT_PAREN,             KC_UP,            KC_P1,  KC_P2,  KC_P3,KC_PENT,
            LCTRL_BRACKET,KC_LGUI,   LALT_CURLY,              LT(MISC,  KC_SPC),                           RALT_CURLY,TT(PROG1), MEDAPP, RCTRL_BRACKET,   KC_LEFT,KC_DOWN,KC_RGHT,    KC_P0,KC_PDOT),
  /* Layer 1: Programming Layer 1, emulating US l ayout */
  [PROG1] = LAYOUT(
          KC_ESC,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,           _______,_______,_______,
          M_GRV,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_SLSH,S(KC_0),_______,   _______,_______,_______,  _______,_______,_______,_______,
         _______,_______,_______,_______,_______,_______,   KC_Z,_______,_______,_______,_______,ALGR(KC_8),ALGR(KC_9),ALGR(KC_MINS),  _______,_______,_______,  _______,_______,_______,_______,
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,S(KC_COMM),S(KC_BSLS),        _______,                             _______,_______,_______,
       MO(PROG2),_______,   KC_Y,_______,_______,_______,_______,_______,_______,_______,_______,   S(KC_7),      MO(PROG2),           _______,          _______,_______,_______,_______,
         _______,_______,_______,                        _______,                        _______,_______,_______,_______,   _______,_______,_______,  _______,_______),
    /* Layer 2: programming layer 2
       all keys that are not FN keys are sent as LSFT+key on this layer
    */
  [PROG2] = LAYOUT(
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,           _______,_______,_______,
        ALGR(KC_RBRC),_______,  ALGR(KC_Q),KC_BSLS,_______,_______,M_CFLEX,  S(KC_6),S(KC_RBRC),   S(KC_8),S(KC_9),S(KC_SLSH),KC_RBRC,_______,   _______,_______,_______,  _______,_______,_______,_______,
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,  ALGR(KC_7),ALGR(KC_0),ALGR(KC_NUBS),  _______,_______,_______,  _______,_______,_______,_______,
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______, S(KC_DOT),   S(KC_2),        _______,                             _______,_______,_______,
         _______,S(KC_NUBS),_______,_______,_______,_______,_______,_______,_______,KC_NUBS,S(KC_NUBS),S(KC_MINS),        _______,           _______,          _______,_______,_______,_______,
         _______,_______,_______,                        _______,                        _______,_______,_______,_______,   _______,_______,_______,  _______,_______),
    /* Layer 3: media layer */
  [MEDIA] = LAYOUT(
          KC_PWR,KC_SLEP,KC_WAKE,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,           XXXXXXX,XXXXXXX,XXXXXXX,
         XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,   KC_MPRV,KC_MPLY,KC_MNXT,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
         XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,   KC_VOLD,KC_MUTE,KC_VOLU,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
         XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,        XXXXXXX,                             XXXXXXX,XXXXXXX,XXXXXXX,
         XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,        XXXXXXX,           KC_EJCT,          XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
         XXXXXXX,XXXXXXX,XXXXXXX,                        XXXXXXX,                        XXXXXXX,XXXXXXX,_______,XXXXXXX,   KC_MRWD,KC_MSTP,KC_MFFD,  XXXXXXX,XXXXXXX),
    /* Layer 4: Mouse layer */
  [MOUSE1] = LAYOUT(
            TO(DEFAULT),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,           _______,_______,_______,
         _______,KC_ACL0,KC_ACL1,KC_ACL2,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______,
         _______,KC_BTN4,KC_WH_D,KC_MS_U,KC_WH_U,_______,   C(KC_Z),_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______,
         _______,KC_BTN5,KC_MS_L,KC_MS_D,KC_MS_R,   CTRL_CLICK,KC_WH_L,KC_WH_D,KC_WH_U,KC_WH_R,_______,_______,        _______,                             _______,_______,_______,
      MO(MOUSE2),_______,C(KC_Y),C(KC_X),C(KC_C),C(KC_V),_______,KC_BTN2,KC_BTN3,C(KC_PGUP),C(KC_PGDN),_______,        KC_RSFT,           _______,          _______,_______,_______,_______,
         KC_LCTL,_______,KC_LALT,                        KC_BTN1,                        KC_RALT,KC_RGUI, KC_APP,KC_RCTL,   _______,_______,_______,  _______,_______),
    /* Layer 5: Mouse layer 2*/
  [MOUSE2] = LAYOUT(
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,           _______,_______,_______,
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______,
         _______,_______,KC_BTN2,KC_WH_U,KC_BTN3,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______,
         _______,_______,KC_WH_L,KC_WH_D,KC_WH_R,_______,KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,_______,        _______,                             _______,_______,_______,
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,           _______,          _______,_______,_______,_______,
         _______,_______,_______,                        _______,                        _______,_______,_______,_______,   _______,_______,_______,  _______,_______),
    /* Layer 6: Misc layer */
  [MISC] = LAYOUT(
         _______, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,           _______,_______,_______,
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______,
         _______,KC_SLCT,   C(KC_W),  KC_UP,_______,_______,_______,_______,KC_BSPC, KC_DEL,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______,
         _______,_______,KC_LEFT,KC_DOWN,KC_RGHT,_______,KC_HOME,KC_PGDN,KC_PGUP,_______,_______,_______,        _______,                             _______,_______,_______,
         KC_LSFT,_______,C(KC_Y),C(KC_X),C(KC_C),C(KC_V), KC_SPC, KC_END,_______,C(KC_PGUP),C(KC_PGDN),_______,        _______,           _______,          _______,_______,_______,_______,
         _______,_______,_______,               LT(MISC, KC_SPC),                        _______,_______,_______,_______,   _______,_______,_______,  _______,_______),
};

void tap_helper(keyrecord_t *record, uint16_t orig_mod, uint16_t macro_mod, uint16_t macro_kc ) {
  if (record->event.pressed) {
      if (record->tap.count > 0 && !record->tap.interrupted) {
          if (record->tap.interrupted) {
              register_mods(MOD_BIT(orig_mod));
          }
      } else {
          register_mods(MOD_BIT(orig_mod));
      }
  } else {
      if (record->tap.count > 0 && !(record->tap.interrupted)) {
          add_weak_mods(MOD_BIT(macro_mod));
          send_keyboard_report();
          register_code(macro_kc);
          unregister_code(macro_kc);
          del_weak_mods(MOD_BIT(macro_mod));
          send_keyboard_report();
          record->tap.count = 0;  // ad hoc: cancel tap
      } else {
          unregister_mods(MOD_BIT(orig_mod));
      }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t layer;
    layer = get_highest_layer(layer_state);
    if (layer == PROG2) {
         if (keycode >= KC_A && keycode <= KC_EXSEL && \
             !(  // do not send LSFT + these keycodes, they are needed for emulating the US layout
                 keycode == KC_NUBS ||
                 keycode == KC_RBRC ||
                 keycode == KC_BSLS ||
                 keycode == KC_GRV
            )) {
              // LSFT is the modifier for this layer, so we set LSFT for every key to get the expected behavior
              if (record->event.pressed) {
                  register_mods(MOD_LSFT);
              } else {
                  unregister_mods(MOD_LSFT);
              }
         }
    }

    switch (keycode) {
        case LCTRL_BRACKET:
            tap_helper(record, KC_LCTL, KC_RALT, KC_8);
            return false;
        case RCTRL_BRACKET:
            tap_helper(record, KC_RCTL, KC_RALT, KC_9);
            return false;
        case LALT_CURLY:
            tap_helper(record, KC_LALT, KC_RALT, KC_7);
            return false;
        case RALT_CURLY:
            tap_helper(record, KC_RALT, KC_RALT, KC_0);
            return false;
        case LSHFT_PAREN:
            tap_helper(record, KC_LSFT, KC_LSFT, KC_8);
            return false;
        case RSHFT_PAREN:
            tap_helper(record, KC_RSFT, KC_LSFT, KC_9);
            return false;
        case CTRL_CLICK:
            if (record->event.pressed) {
                mousekey_clear();
                register_mods(MOD_BIT(KC_LCTL));
                send_keyboard_report();
                wait_ms(5);
                mousekey_on(KC_BTN1);
                mousekey_send();
                wait_ms(10);
                mousekey_off(KC_BTN1);
                mousekey_send();
                wait_ms(5);
                unregister_mods(MOD_BIT(KC_LCTL));
                send_keyboard_report();
            }
            return false;
        case M_GRV:
            tap_code16(S(KC_EQL));
            tap_code(KC_SPC);
            return false;
        case M_CFLEX:
            tap_code(KC_GRV);
            tap_code(KC_SPC);
            return false;
    }

    return true;
}
