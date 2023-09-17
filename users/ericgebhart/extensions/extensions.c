/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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

#include USERSPACE_H

#include "extensions.h"
#include "keymap_combo.h"
#include "altlocal_keys.h"
#include "tap_hold.h"
#include "accented_keys.h"
#include "process_smart_lock.h"
#include "mod_lock.h"
#include "oneshot.h"
#include "process_nshot.h"
#include "process_locales.h"
#include "unicode.h"
#include "key_overrides.h"
#include "console_key_logger.h"

// should make header files maybe. being lazy.
void process_not_dead(uint16_t keycode, keyrecord_t *record);
bool process_alt_shift_user(uint16_t keycode, keyrecord_t *record);
void process_send_strs(uint16_t keycode, keyrecord_t *record);
//bool process_alt_local_key(uint16_t keycode, keyrecord_t* record);
bool process_global_quick_tap(uint16_t keycode, keyrecord_t *record);

// call this from the top of process records before the switch.

bool process_extensions(uint16_t keycode, keyrecord_t *record){
  if (!process_locales(keycode, record)) { return false; }

#ifdef GLOBAL_QUICK_TAP_ENABLE
  if (!process_global_quick_tap(keycode, record)) {return false; }
#endif
#ifdef CAPS_WORD_ENABLE
 if (!process_caps_word(keycode, record)) { return false; }
#endif
#ifdef ALT_LOCAL_ENABLE
  if (!process_alt_local_key(keycode, record)) { return false; }
#endif
#ifdef ACCENTED_KEYS_ENABLE
  if (!process_accent_keys(keycode, record)) { return false; }
#endif
#ifdef TAP_HOLD_ENABLE
  process_tap_hold_user(keycode, record);
#endif
#ifdef SMART_LOCK_ENABLE
  process_smart_lock(keycode, record);
#endif
#ifdef MOD_LOCK_ENABLE
  process_mod_lock(keycode, record);
#endif
#ifdef NSHOT_ENABLE
  if(!process_nshot_state(keycode, record)) {return false;}
#endif
#ifdef SEND_UNICODE_ENABLE
  process_unicode_strs(keycode, record);
#endif
#ifdef SEND_STRING_ENABLE
  process_send_strs(keycode, record);
#endif
#ifdef NOT_DEAD_ENABLE
  process_not_dead(keycode, record);
#endif
#ifdef ALT_SHIFT_ENABLE
  if(!process_alt_shift_user(keycode, record)) {return false;}
#endif
#if defined( CONSOLE_ENABLE) && defined(CONSOLE_KEY_LOGGER_ENABLE)
  process_console_key_logger(keycode, record);
#endif
#ifdef ONESHOT_MOD_ENABLE
  int8_t keycode_consumed = 0;
  keycode_consumed += update_oneshot_modifiers(keycode, record, keycode_consumed);
#endif
  return true;

}
