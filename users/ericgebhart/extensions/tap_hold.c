/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* This is variations on custom tap hold functionality. It makes it easy */
/* to maintain tap_hold keys and combinations. These combinations go into */
/* the file "tap_hold.def". Here are two examples. */
/*  */
/* This example is tap or tap for TAP_HOLD_TERM, It defines a key */
/* KC_CCCV, which sends Control-c on tap, and Control-v on hold. */
/*  */
/*  TP_TPL(KC_CCCV, LCTL(KC_C), LCTL(KC_V)) */
/*  */
/* This is an example of Open - Open and Close. */
/* It defines a key, KC_OCPRN which when tapped gives an '(' and */
/* when held gives '()' followed by a backarrow. */
/* Which places the cursor between them.*/
/*  */
/* OPEN_OCL(KC_OCPRN, KC_LPRN, KC_RPRN) */
/*  */
/* To use this, add it to your src in rules.mk, and include */
/* tap_hold.h in your code above process_record_user. */
/*  */
/* Add a call like this to use it. */
/* process_tap_hold_user(keycode, record); */
/*  */
/* Note: You must add any custom keycodes to your keycodes enum */
/* otherwise they will not exist. */


#include USERSPACE_H
#include "stdint.h"
#include "tap_hold.h"
void update_smart_lock(uint16_t keycode);


void tap_taplong(uint16_t kc1, uint16_t kc2, keyrecord_t *record) {
  if (record->event.pressed) {
    tap_taplong_timer = timer_read();
  } else {
    if (timer_elapsed(tap_taplong_timer) > TAP_HOLD_TERM) {
      tap_code16(kc2);
    } else {
      tap_code16(kc1);
    }
  }
}

void tap_sml(uint16_t kc1, uint16_t kc2, keyrecord_t *record) {
  if (record->event.pressed) {
    tap_taplong_timer = timer_read();
  } else {
    if (timer_elapsed(tap_taplong_timer) > TAP_HOLD_TERM) {
      update_smart_lock(kc2);
    } else {
      tap_code16(kc1);
    }
  }
}

/* for (){}[]""''<>``. tap for open. Hold for open and close, ending inbetween. */
/* Assumes a one character length.                                              */
void open_openclose(uint16_t kc1, uint16_t kc2, keyrecord_t *record) {
  if (record->event.pressed) {
    tap_taplong_timer = timer_read();
  }else{
    if (timer_elapsed(tap_taplong_timer) > TAP_HOLD_TERM) {
      tap_code16(kc1);
      tap_code16(kc2);
      tap_code16(KC_LEFT);

    } else {
      // is shifted
      uint16_t mod_state = get_mods();
      if ((mod_state & MOD_MASK_SHIFT) ||
          (get_oneshot_mods() & MOD_MASK_SHIFT)){
        del_mods(MOD_MASK_SHIFT);
        del_oneshot_mods(MOD_MASK_SHIFT);

        tap_code16(kc1);
        tap_code16(kc1);
        tap_code16(kc1);

        set_mods(mod_state);
      }else{
        tap_code16(kc1);
      }
    }
  }
}

// open and open close for dead keys.
void open_openclose_not_dead(uint16_t kc1, uint16_t kc2, keyrecord_t *record) {
  if (record->event.pressed) {
    tap_taplong_timer = timer_read();
  }else{
    if (timer_elapsed(tap_taplong_timer) > TAP_HOLD_TERM) {
      tap_code16(kc1);
      tap_code16(KC_SPACE);
      tap_code16(kc2);
      tap_code16(KC_SPACE);
      tap_code16(KC_LEFT);
    } else {
      // is shifted - give a triple
      uint16_t mod_state = get_mods();
      if ((mod_state & MOD_MASK_SHIFT) ||
          (get_oneshot_mods() & MOD_MASK_SHIFT)){
        del_mods(MOD_MASK_SHIFT);
        del_oneshot_mods(MOD_MASK_SHIFT);

        tap_code16(kc1);
        tap_code16(KC_SPACE);
        tap_code16(kc1);
        tap_code16(KC_SPACE);
        tap_code16(kc1);
        tap_code16(KC_SPACE);

        set_mods(mod_state);
      }else{
        tap_code16(kc1);
        tap_code16(KC_SPACE);
      }
    }
  }
}

// macros for use in tap_hold.defs.
#define TP_TPL(KCKEY, KC01, KC02)               \
  case KCKEY:                                   \
  tap_taplong(KC01, KC02, record);              \
  break;

#define TP_SML(KCKEY, KC01, KC02)        \
  case KCKEY:                            \
  tap_sml(KC01, KC02, record);           \
  break;

#define OPEN_OCL(KCKEY, KC01, KC02)             \
  case KCKEY:                                   \
  open_openclose(KC01, KC02, record);           \
  break;

#define OPEN_OCL_ND(KCKEY, KC01, KC02)          \
  case KCKEY:                                   \
  open_openclose_not_dead(KC01, KC02, record);  \
  break;

void process_tap_hold_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode){
#include "tap_hold.def"
  }
}
