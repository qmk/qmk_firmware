#include QMK_KEYBOARD_H
#include "brianoverby.h" // Includes Danish and custom keymaps

enum preonic_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _FN,
  _SYSTEM
};

enum preonic_keycodes {
  BASE = SAFE_RANGE,
  wntg
};

bool winkey_enabled = true;

/* Define mod keys */
#define lw MO(_LOWER)
#define ra MO(_RAISE)
#define fn MO(_FN)
#define rset RESET

#define ____ KC_TRNS
#define xxxx KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_preonic_grid(
  esc,  n1,   n2,   n3,   n4,   n5,   n6,   n7,   n8,   n9,   n0,   bspc,
  tab,  q,    w,    e,    r,    t,    y,    u,    i,    o,    p,    plus, 
  lt,   a,    s,    d,    f,    g,    h,    j,    k,    l,    quot, ent,
  lsft, z,    x,    c,    v,    b,    n,    m,    comm, dot,  up,   rsft, 
  lctl, fn,   lgui, lalt, lw,   spc,  spc,  ralt, mins, left, down, rght 
),

[_LOWER] = LAYOUT_preonic_grid(
  f1,   f2,   f3,   f4,   f5,   f6,   f7,   f8,   f9,   f10,  f11,  f12,
  tild, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, lcbr, rcbr, xxxx, xxxx,
  ____, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, lbrc, rbrc, xxxx, acut,
  ____, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, mute, vold, volu, xxxx, ____,
  ____, ____, ____, ____, ____, ____, ____, ____, bsls, pipe, xxxx, xxxx
),

[_RAISE] = LAYOUT_preonic_grid(
  f1,   f2,   f3,   f4,   f5,   f6,   f7,   f8,   f9,   f10,  f11,  f12,
  grv,  xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx,
  caps, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, uml,
  ____, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, mute, vold, volu, xxxx, ____,
  ____, ____, ____, ____, ____, ____, ____, ____, xxxx, xxxx, xxxx, xxxx
),

[_FN] = LAYOUT_preonic_grid(
  f1,   f2,   f3,   f4,   f5,   f6,   f7,   f8,   f9,   f10,  f11,  f12,
  tab,  xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, ins,  xxxx, prnt, aa,
  del,  xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, ae,   oe,
  ____, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, pgup, del,
  ____, fn,   lgui, lalt, ____, ____, ____, ____, xxxx, home, pgdn, end
),

[_SYSTEM] = LAYOUT_preonic_grid(
  xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx,
  xxxx, xxxx, wntg, xxxx, rset, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx,
  xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx,
  xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx,
  xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx  
)

};

/* Hold Lower + Raise to activate SYSTEM layer */
uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _SYSTEM);
  return state;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case wntg:
      if (record->event.pressed) { // Toggle Windows Key
        winkey_enabled = !winkey_enabled;
      }
      return false;
      break;
    case lgui: // Check if Windows Key is disabled 
      if (!winkey_enabled) {
        return false;
      } else {
        return true;
      }
      break;
  }
  return true;
}