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
// Derived from smart_layers by @Possumvibes
// Derived from one shot_mod by @Callum.

#include "smart_lock.h"
#include USERSPACE_H

/* print("string"): Print a simple string. */
/* uprintf("%s string", var) */

bool ignore_key(uint16_t keycode,
                const uint16_t *cond_keys){

  // look for non-cancel condition.
  // look for keys to ignore, if we match, we do nothing.
  for (; pgm_read_word(cond_keys) != COND_KEYS_END ; ++cond_keys){
    if (pgm_read_word(cond_keys) == keycode){
      return true;
    }
  }
  return false;
}

void deactivate_sml_layer(smart_lock_t *sml){
  layer_off(sml->thing);
    sml->active = false;
}
void deactivate_sml_mod(smart_lock_t *sml){
  unregister_mods(sml->thing);
  sml->active = false;
}

void deactivate_sml(smart_lock_t *sml){
  switch(sml->type){
  case sml_layer:
    deactivate_sml_layer(sml);
  case sml_mod:
    deactivate_sml_mod(sml);
  }
}


void sml_activate_layer(smart_lock_t *sml){
  sml->active = true;
  layer_on(sml->thing);
}

void sml_maybe_activate_mod(smart_lock_t *sml ){
  if (sml->active) {
    unregister_mods(sml->thing);
  } else {
    register_mods(sml->thing);
  }
  sml->active = !sml->active;
}

void sml_activate(smart_lock_t *sml){
  switch(sml->type){
  case sml_layer:
    sml_activate_layer(sml);
    break;
  case sml_mod:
sml_maybe_activate_mod(sml);
      break;
    }
}



void update_smart_lock(uint16_t keycode) {

#ifdef SMART_LOCK_ENABLE
  bool deactivate = false;
  smart_lock_t *sml;

    for (int i = 0; i < SML_LEN; ++i){
      sml = &smart_locks[i];

      // if it's a match,
      // maybe activate/deactivate it if we got it's keycode.
      if (sml->keycode == keycode){
        sml_activate(sml);
        return;
      }

      // deactivate what we need to.
      if(sml->active){
        deactivate = !ignore_key(keycode,  &sml->keys[0]);
        if (deactivate){
          deactivate_sml(sml);
        }
      }
  }
#endif
  return;
}

void process_smart_lock(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    update_smart_lock(keycode);
  }
}
