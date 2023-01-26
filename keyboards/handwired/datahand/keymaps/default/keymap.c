/* Copyright 2017-2019 Nikolaus Wittenstein <nikolaus.wittenstein@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include QMK_KEYBOARD_H

#include <stdbool.h>

/* Datahand features not supported:
 * * All online reprogramming (user settings using the reset button).
 *   * Program Selection features.
 *   * Macros.
 *   * Direct substitutions.
 * * L/R Modf.
 * * Mouse Click Lock (Function Direct Access + Mouse Button key).
 * * Different mouse movement speeds with the two pointer fingers, and using both pointer fingers to move even faster.
 *
 * As far as I know, everything else works.
 */

enum layer {
  NORMAL,
#ifdef DATAHAND_THUMB_RETURN_COMMAND
  NORMAL_THUMB_RETURN_COMMAND,
#endif
  FUNCTION_MOUSE,
  FUNCTION_ARROWS,
  NAS,
  NAS_NUMLOCK,
  NAS_TENKEY,
  NAS_TENKEY_NUMLOCK,

  NUM_LAYERS
};

enum custom_keycodes {
  N = SAFE_RANGE,   /* Normal */
  NS,               /* NAS */
  NSL,              /* NAS Lock */
  NLK,              /* Numlock */
  FN,               /* Function mode - needs to be able to switch to mouse or arrow layer */
  TK0,              /* Ten-key off button */
  TK1,              /* Ten-key on button */
  AR,               /* FN arrow mode */
  MS,               /* FN mouse mode */
  DZ,               /* Double zero button */
};

static bool mouse_enabled = true;
static bool tenkey_enabled = false;
static bool numlock_enabled = false;
static bool nas_locked = false;

/* Declared weak so that it can easily be overridden. */
__attribute__((weak)) const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
[NORMAL] = LAYOUT(
        KC_Q,                     KC_W,                 KC_E,                 KC_R,                       KC_U,                   KC_I,                     KC_O,                    KC_P,
KC_DEL, KC_A, KC_LBRC,    KC_ESC, KC_S, KC_B,   KC_GRV, KC_D, KC_T,   KC_DQT, KC_F, KC_G,           KC_H, KC_J, KC_QUOT,   KC_Y,  KC_K,   KC_COLN,   KC_N,  KC_L, KC_ENT,   KC_RBRC, KC_SCLN, KC_BSLS,
        KC_Z,                     KC_X,                 KC_C,                 KC_V,                       KC_M,                   KC_COMM,                  KC_DOT,                  KC_SLSH,
                                                                          KC_ENT,    KC_TAB,   KC_BSPC,  KC_SPC,
                                                                              KC_LSFT,              NS,
                                                                              KC_CAPS,              NSL,
                                                                          N,         KC_LCTL,  KC_LALT,  FN),

#ifdef DATAHAND_THUMB_RETURN_COMMAND
[NORMAL_THUMB_RETURN_COMMAND] = LAYOUT(
         _______,                    _______,                    _______,                    _______,                       _______,                    _______,                    _______,                    _______,
_______, _______, _______,  _______, _______, _______,  _______, _______, _______,  _______, _______, _______,     _______, _______, _______,  _______, _______, _______,  _______, _______, _______,  _______, _______, _______,
         _______,                    _______,                    _______,                    _______,                       _______,                    _______,                    _______,                    _______,
                                                                                            KC_LCMD,   _______,   _______,   _______,
                                                                                                 _______,              _______,
                                                                                                 _______,              _______,
                                                                                             _______,   _______,   _______,   _______),
#endif

[FUNCTION_MOUSE] = LAYOUT(
         KC_F2,                     KC_F4,                  KC_F6,                   KC_MS_U,                      KC_MS_U,                    KC_F8,                   KC_F10,                  KC_PGUP,
_______, KC_NO, KC_SCRL,   _______, KC_BTN3, NLK,  KC_BTN1, MS, KC_BTN2,    KC_MS_L, KC_BTN1, KC_MS_R,    KC_MS_L, KC_BTN2, KC_MS_R,   KC_END, AR,  KC_LSFT,    KC_INS, KC_9,  KC_ENT,   KC_F11, KC_0,   KC_F12,
         KC_F1,                     KC_F3,                  KC_F5,                   KC_MS_D,                      KC_MS_D,                    KC_F7,                   KC_F9,                   KC_PGDN,
                                                                                             _______,   _______,   _______,   _______,
                                                                                                  _______,              _______,
                                                                                                  _______,              _______,
                                                                                             _______,   _______,   _______,   _______),
[FUNCTION_ARROWS] = LAYOUT(
         _______,                     _______,                     _______,                     KC_UP,                              KC_UP,                       _______,                     _______,                     _______,
_______, _______, _______,   _______, KC_LCTL, _______,   _______, _______, _______,   KC_LEFT, KC_HOME, KC_RGHT,          KC_LEFT, KC_HOME, KC_RGHT,   _______, _______, _______,   _______, _______, _______,   _______, _______, _______,
         _______,                     _______,                     _______,                     KC_DOWN,                            KC_DOWN,                     _______,                     _______,                     _______,
                                                                                             _______,   _______,   _______,   _______,
                                                                                                  _______,              _______,
                                                                                                  _______,              _______,
                                                                                             _______,   _______,   _______,   _______),
[NAS] = LAYOUT(
         KC_EXLM,                    KC_AT,                KC_HASH,                    KC_DLR,                      KC_AMPR,                    KC_ASTR,                    KC_LPRN,                KC_RPRN,
_______, KC_1,   KC_TILD,   _______, KC_2, NLK,   KC_LABK, KC_3,   KC_RABK,   KC_SLSH, KC_4,   KC_5,          KC_6, KC_7,   KC_UNDS,   KC_CIRC, KC_8,   KC_ENT,   KC_SCLN,  KC_9,   KC_BSLS,   TK0, KC_0,   TK1,
         KC_EQL,                     KC_X,                 KC_PERC,                    KC_MINS,                     KC_PLUS,                    KC_DOT,                     KC_SLSH,                KC_QUES,
                                                                                             _______,   _______,   _______,   _______,
                                                                                                  _______,              _______,
                                                                                                  _______,              _______,
                                                                                             _______,   _______,   _______,   _______),
[NAS_NUMLOCK] = LAYOUT(
         _______,                     _______,                     _______,                     _______,                            _______,                     KC_PAST,                     _______,                     _______,
_______, KC_KP_1, _______,   _______, KC_KP_2, _______,   _______, KC_KP_3, _______,   KC_PSLS, KC_KP_4, KC_KP_5,          KC_KP_6, KC_KP_7, _______,   _______, KC_KP_8, _______,   _______, KC_KP_9, KC_PENT,   _______, KC_KP_0, _______,
         KC_PEQL,                     _______,                     _______,                     KC_PMNS,                            KC_PPLS,                     _______,                     KC_PDOT,                     _______,
                                                                                             _______,   _______,   _______,   _______,
                                                                                                  _______,              _______,
                                                                                                  _______,              _______,
                                                                                             _______,   _______,   _______,   _______),
[NAS_TENKEY] = LAYOUT(
         _______,                     _______,                   _______,                    KC_UP,                       KC_7,               KC_8,                   KC_9,                   KC_ASTR,
_______, KC_QUOT, _______,   _______, KC_DLR, _______,  _______, KC_AMPR, _______,  KC_LEFT, KC_HOME, KC_RGHT,      KC_0, KC_4, DZ,  KC_PLUS, KC_5, KC_MINS,  KC_EQL, KC_6, KC_ENT,  _______, KC_DOT, _______,
         KC_LPRN,                     KC_RPRN,                   _______,                    KC_DOWN,                     KC_1,               KC_2,                   KC_3,                   KC_SLSH,
                                                                                             _______,   _______,   _______,   _______,
                                                                                                  _______,              _______,
                                                                                                  _______,              _______,
                                                                                             _______,   _______,   _______,   _______),
[NAS_TENKEY_NUMLOCK] = LAYOUT(
         _______,                    _______,                    _______,                    _______,                       KC_KP_7,                    KC_KP_8,                    KC_KP_9,                    KC_PAST,
_______, _______, _______,  _______, _______, _______,  _______, _______, _______,  _______, _______, _______,     KC_KP_0, KC_KP_4, _______,  KC_PPLS, KC_KP_5, KC_PMNS,  KC_PEQL, KC_KP_6, KC_PENT,  _______, KC_PDOT, _______,
         _______,                    _______,                    _______,                    _______,                       KC_KP_1,                    KC_KP_2,                    KC_KP_3,                    KC_PSLS,
                                                                                             _______,   _______,   _______,   _______,
                                                                                                  _______,              _______,
                                                                                                  _______,              _______,
                                                                                             _______,   _______,   _______,   _______),
};

static void lock_led_set(bool on, uint8_t led) {
  if (on) {
    LED_LOCK_PORT &= ~led;
  } else {
    LED_LOCK_PORT |= led;
  }
}

static void mode_led_set(uint8_t led) {
  static const uint8_t ALL_MODE_LEDS = LED_FN | LED_NORMAL | LED_NAS | LED_TENKEY;
  LED_MODE_PORT |= ALL_MODE_LEDS;
  LED_MODE_PORT &= ~led;
}

static void layer_set(bool on, uint8_t layer) {
  if (on) {
    layer_on(layer);
  } else {
    layer_off(layer);
  }

  if (layer_state_is(NAS) || layer_state_is(NAS_NUMLOCK) || layer_state_is(NAS_TENKEY) || layer_state_is(NAS_TENKEY_NUMLOCK)) {
    if (tenkey_enabled) {
      mode_led_set(LED_NAS | LED_TENKEY);
    } else {
      mode_led_set(LED_NAS);
    }
  } else if (layer_state_is(FUNCTION_MOUSE) || layer_state_is(FUNCTION_ARROWS)) {
    mode_led_set(LED_FN);
  } else if (layer_state_is(NORMAL)) {
    mode_led_set(LED_NORMAL);
  }
}

static void set_normal(void) {
  layer_move(NORMAL);

#ifdef DATAHAND_THUMB_RETURN_COMMAND
  layer_set(true, NORMAL_THUMB_RETURN_COMMAND);
#endif

  /* Then call layer_set to update LEDs. */
  layer_set(true, NORMAL);
}

static void set_nas(bool on) {
  /* Always turn on the base NAS layer so other layers can fall through. */
  layer_set(on, NAS);

  layer_set(on && numlock_enabled, NAS_NUMLOCK);
  layer_set(on && tenkey_enabled, NAS_TENKEY);
  layer_set(on && tenkey_enabled && numlock_enabled, NAS_TENKEY_NUMLOCK);
}

static void set_tenkey(bool on) {
  tenkey_enabled = on;
  
  /* We have to be on the NAS layer in order to be able to toggle TK.
   * Re-toggle it on so that we move to the right layer (and set the right LED).
   */
  set_nas(true);
}

static void toggle_numlock(void) {
  numlock_enabled = !numlock_enabled;
  lock_led_set(numlock_enabled, LED_NUM_LOCK);
  
  if (layer_state_is(NAS)) {
    /* If we're already in NAS, re-set it so that we activate the numlock layer. */
    set_nas(true);
  }
}

static void set_function(void) {
  /* Make sure to turn off NAS if we're entering function */
  set_nas(false);

  /* Always turn on the mouse layer so the arrow layer can fall through. */
  layer_set(true, FUNCTION_MOUSE);
  layer_set(!mouse_enabled, FUNCTION_ARROWS);
}

static void set_mouse_enabled(bool on) {
  mouse_enabled = on;

  /* Re-run set_function to set our layers correctly. */
  set_function();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool pressed = record->event.pressed;
  
  switch(keycode) {
    case N:
    if (pressed) {
      set_normal();
    }
    break;

    case NS:
    if (pressed) {
      nas_locked = false;
    }
    set_nas(pressed);
    break;
    
    case NSL:
    if (pressed) {
      nas_locked = true;
      set_nas(true);
    }
    break;
    
    case NLK:
    if (pressed) {
      toggle_numlock();
      SEND_STRING(SS_DOWN(X_NUM_LOCK));
    } else {
      SEND_STRING(SS_UP(X_NUM_LOCK));
    }
    break;
    
    case FN:
    if (pressed) {
      set_function();
    }
    break;
    
    case TK0:
    if (pressed) {
      set_tenkey(false);
    }
    break;
    
    case TK1:
    if (pressed) {
      set_tenkey(true);
    }
    break;

    case MS:
    if (pressed) {
      set_mouse_enabled(true);
    }
    break;

    case AR:
    if (pressed) {
      set_mouse_enabled(false);
    }
    break;
    
    case DZ:
    if (pressed) {
      SEND_STRING(SS_TAP(X_KP_0) SS_TAP(X_KP_0));
    }
    break;
  }

  return true;
};

void matrix_init_user(void) {
#ifdef DATAHAND_THUMB_RETURN_COMMAND
  set_normal();
#endif
}

void led_set_user(uint8_t usb_led) {
  lock_led_set(usb_led & (1<<USB_LED_NUM_LOCK), LED_NUM_LOCK);
  lock_led_set(usb_led & (1<<USB_LED_CAPS_LOCK), LED_CAPS_LOCK);
  lock_led_set(usb_led & (1<<USB_LED_SCROLL_LOCK), LED_SCROLL_LOCK);
}
