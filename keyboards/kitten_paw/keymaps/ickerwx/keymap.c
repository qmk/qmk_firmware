#include "kitten_paw.h"
#include "mousekey.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define  C(kc) LCTL(KC_##kc)
#define RA(kc) RALT(KC_##kc)
#define KC_SLCT KC_SELECT
#define MEDAPP LT(MEDIA, KC_APP)
#undef S
#define S(kc) LSFT(KC_##kc)

uint8_t current_layer_global = 255;

enum layers {
    DEFAULT,
    PROG1,
    PROG2,
    MEDIA,
    MOUSE1,
    MOUSE2,
    MISC,
};

enum function_id {
    LSHFT_PAREN,
    RSHFT_PAREN,
    LCTRL_BRACKET,
    RCTRL_BRACKET,
    LALT_CURLY,
    RALT_CURLY,
    CTRL_CLICK
};

enum macro_id {
    GRV,
    CFLEX
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEFAULT] = KEYMAP(\
          KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,           KC_PSCR,KC_SLCK,KC_PAUS,                                   \
          KC_GRV,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL,KC_BSPC,    KC_INS,KC_HOME,KC_PGUP,  KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS, \
          KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_LBRC,KC_RBRC,KC_BSLS,    KC_DEL, KC_END,KC_PGDN,    KC_P7,  KC_P8,  KC_P9,KC_PPLS, \
            F(0),   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,         KC_ENT,                               KC_P4,  KC_P5,  KC_P6,         \
            F(8),KC_NUBS,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,           F(9),             KC_UP,            KC_P1,  KC_P2,  KC_P3,KC_PENT, \
            F(1),KC_LGUI,   F(3),              LT(MISC,  KC_SPC),                           F(4),   F(5), MEDAPP,   F(2),   KC_LEFT,KC_DOWN,KC_RGHT,    KC_P0,KC_PDOT),
  /* Layer 1: Programming Layer 1, emulating US l ayout */
  [PROG1] = KEYMAP(\
          KC_ESC,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,           _______,_______,_______,                                   \
          M(GRV),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_SLSH,   S(0),_______,   _______,_______,_______,  _______,_______,_______,_______, \
         _______,_______,_______,_______,_______,_______,   KC_Z,_______,_______,_______,_______,  RA(8),  RA(9),RA(MINS),  _______,_______,_______,  _______,_______,_______,_______, \
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,S(COMM),S(BSLS),        _______,                             _______,_______,_______,         \
       MO(PROG2),_______,   KC_Y,_______,_______,_______,_______,_______,_______,_______,_______,   S(7),      MO(PROG2),           _______,          _______,_______,_______,_______, \
         _______,_______,_______,                        _______,                        _______,_______,_______,_______,   _______,_______,_______,  _______,_______),
    /* Layer 2: programming layer 2
       all keys that are not FN keys are sent as LSFT+key on this layer
    */
  [PROG2] = KEYMAP(\
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,           _______,_______,_______,                                   \
        RA(RBRC),_______,  RA(Q),KC_BSLS,_______,_______,M(CFLEX),  S(6),S(RBRC),   S(8),   S(9),S(SLSH),KC_RBRC,_______,   _______,_______,_______,  _______,_______,_______,_______, \
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,  RA(7),  RA(0),RA(NUBS),  _______,_______,_______,  _______,_______,_______,_______, \
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______, S(DOT),   S(2),        _______,                             _______,_______,_______,         \
         _______,S(NUBS),_______,_______,_______,_______,_______,_______,_______,KC_NUBS,S(NUBS),S(MINS),        _______,           _______,          _______,_______,_______,_______, \
         _______,_______,_______,                        _______,                        _______,_______,_______,_______,   _______,_______,_______,  _______,_______),
    /* Layer 3: media layer */
  [MEDIA] = KEYMAP(\
          KC_PWR,KC_SLEP,KC_WAKE,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,           XXXXXXX,XXXXXXX,XXXXXXX,                                   \
         XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,   KC_MPRV,KC_MPLY,KC_MNXT,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
         XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,   KC_VOLD,KC_MUTE,KC_VOLU,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
         XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,        XXXXXXX,                             XXXXXXX,XXXXXXX,XXXXXXX,         \
         XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,        XXXXXXX,           KC_EJCT,          XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
         XXXXXXX,XXXXXXX,XXXXXXX,                        XXXXXXX,                        XXXXXXX,XXXXXXX,_______,XXXXXXX,   KC_MRWD,KC_MSTP,KC_MFFD,  XXXXXXX,XXXXXXX),
    /* Layer 4: Mouse layer */
  [MOUSE1] = KEYMAP(\
            F(6),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,           _______,_______,_______,                                   \
         _______,KC_ACL0,KC_ACL1,KC_ACL2,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______, \
         _______,KC_BTN4,KC_WH_D,KC_MS_U,KC_WH_U,_______,   C(Z),_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______, \
         _______,KC_BTN5,KC_MS_L,KC_MS_D,KC_MS_R,   F(7),KC_WH_L,KC_WH_D,KC_WH_U,KC_WH_R,_______,_______,        _______,                             _______,_______,_______,         \
      MO(MOUSE2),_______,   C(Y),   C(X),   C(C),   C(V),_______,KC_BTN2,KC_BTN3,C(PGUP),C(PGDN),_______,        KC_RSFT,           _______,          _______,_______,_______,_______, \
         KC_LCTL,_______,KC_LALT,                        KC_BTN1,                        KC_RALT,KC_RGUI, KC_APP,KC_RCTL,   _______,_______,_______,  _______,_______),
    /* Layer 5: Mouse layer 2*/
  [MOUSE2] = KEYMAP(\
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,           _______,_______,_______,                                   \
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______, \
         _______,_______,KC_BTN2,KC_WH_U,KC_BTN3,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______, \
         _______,_______,KC_WH_L,KC_WH_D,KC_WH_R,_______,KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,_______,        _______,                             _______,_______,_______,         \
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,           _______,          _______,_______,_______,_______, \
         _______,_______,_______,                        _______,                        _______,_______,_______,_______,   _______,_______,_______,  _______,_______),
    /* Layer 6: Misc layer */
  [MISC] = KEYMAP(\
         _______, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,           _______,_______,_______,                                   \
         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______, \
         _______,KC_SLCT,   C(W),  KC_UP,_______,_______,_______,_______,KC_BSPC, KC_DEL,_______,_______,_______,_______,   _______,_______,_______,  _______,_______,_______,_______, \
         _______,_______,KC_LEFT,KC_DOWN,KC_RGHT,_______,KC_HOME,KC_PGDN,KC_PGUP,_______,_______,_______,        _______,                             _______,_______,_______,         \
         KC_LSFT,_______,   C(Y),   C(X),   C(C),   C(V), KC_SPC, KC_END,_______,C(PGUP),C(PGDN),_______,        _______,           _______,          _______,_______,_______,_______, \
         _______,_______,_______,               LT(MISC, KC_SPC),                        _______,_______,_______,_______,   _______,_______,_______,  _______,_______),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_TOGGLE(MOUSE1),      // tap-toggle mouse layer (4)
    [1] = ACTION_FUNCTION_TAP(LCTRL_BRACKET),   // tap to print [
    [2] = ACTION_FUNCTION_TAP(RCTRL_BRACKET),   // tap to print ]
    [3] = ACTION_FUNCTION_TAP(LALT_CURLY),      // tap to print {
    [4] = ACTION_FUNCTION_TAP(RALT_CURLY),      // tap to print }
    [5] = ACTION_LAYER_TAP_TOGGLE(PROG1),       // tap-toggle programming layer 1
    [6] = ACTION_LAYER_SET_CLEAR(DEFAULT),
    [7] = ACTION_FUNCTION_TAP(CTRL_CLICK),
    [8] = ACTION_FUNCTION_TAP(LSHFT_PAREN),     // tap to print (
    [9] = ACTION_FUNCTION_TAP(RSHFT_PAREN),     // tap to print )
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case GRV: // macro to print accent grave
            return (record->event.pressed ?
                    MACRO( D(LSFT), T(EQL), U(RALT), T(SPC), END) :
                    MACRO_NONE );
        case CFLEX: // print accent circonflex
            return (record->event.pressed ?
                    MACRO( T(GRV), T(SPC), END ) :
                    MACRO_NONE );
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
    uint8_t layer;
    layer = biton32(layer_state);

    if (current_layer_global != layer) {
        current_layer_global = layer;

        // unset CAPSLOCK and SCROLL LOCK LEDs
        led_set_kb(host_keyboard_leds() & ~(1<<USB_LED_CAPS_LOCK));
        led_set_kb(host_keyboard_leds() & ~(1<<USB_LED_SCROLL_LOCK));
        // set SCROLL LOCK LED when the mouse layer is active, CAPS LOCK when PROG layer is active
        if (layer == MOUSE1 || layer == MOUSE2) {
          led_set_kb(host_keyboard_leds() | (1<<USB_LED_SCROLL_LOCK));
        } else if (layer == PROG1 || layer == PROG2) {
          led_set_kb(host_keyboard_leds() | (1<<USB_LED_CAPS_LOCK));
        }
    }
}

void led_set_user(uint8_t usb_led) {

}

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

/* if LCTRL is tabbed, print (, or ) if RCTRL is tabbed, same for LALT/RALT and [/] */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    // The code is copied from keymap_hasu.c in the tmk keyboards hhkb folder
    switch (id) {
        case LCTRL_BRACKET:
            tap_helper(record, KC_LCTL, KC_RALT, KC_8);
            break;
        case RCTRL_BRACKET:
            tap_helper(record, KC_RCTL, KC_RALT, KC_9);
            break;
        case LALT_CURLY:
            tap_helper(record, KC_LALT, KC_RALT, KC_7);
            break;
        case RALT_CURLY:
            tap_helper(record, KC_RALT, KC_RALT, KC_0);
            break;
        case LSHFT_PAREN:
            tap_helper(record, KC_LSFT, KC_LSFT, KC_8);
            break;
        case RSHFT_PAREN:
            tap_helper(record, KC_RSFT, KC_LSFT, KC_9);
            break;
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
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t layer;
    layer = biton32(layer_state);
    if (layer == PROG2) {
         if (keycode >= KC_A && keycode <= KC_EXSEL && \
             !(  // do not send LSFT + these keycodes, they are needed for emulating the US layout
                 keycode == KC_NONUS_BSLASH ||
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
    return true;
}
