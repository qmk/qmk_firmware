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
  LOWER,
  RAISE
};

/* Define mod keys */
#define game TG(_GAME)
#define lw MO(_LOWER)
#define ra MO(_RAISE)
#define fn MO(_FN)
#define rset RESET

#define ____ KC_TRNS
#define xxxx KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_preonic_grid(
  n1,   n2,   n3,   n4,   n5,   n6,   n7,   n8,   n9,   n0,   mins, plus,
  tab,  q,    w,    e,    r,    t,    y,    u,    i,    o,    p,    bspc, 
  esc,  a,    s,    d,    f,    g,    h,    j,    k,    l,    SCLN, QUOT,
  LSFT, z,    x,    c,    v,    b,    n,    m,    COMM, DOT,  up,   ent, 
  lctl, fn,   lgui, lalt, lw,   spc,  spc,  ra,   SLSH, left, down, rght 
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
  tild, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx,
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
  ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
  ____, rset, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
  ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
  ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
  ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  
)

};

/* Hold Lower + Raise to activate SYSTEM layer */
uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _SYSTEM);
  return state;
}

