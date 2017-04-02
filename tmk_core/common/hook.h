/*
Copyright 2016 Jun Wako <wakojun@gmail.com>

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

#ifndef _HOOKS_H_
#define _HOOKS_H_

#include "keyboard.h"
#include "led.h"

/* -------------------------------------
 * Protocol hooks
 * ------------------------------------- */

/* Called once, very early stage of initialization, just after processor startup. */
/* Default behaviour: do nothing. */
void hook_early_init(void);

/* Called once, very last stage of initialization, just before keyboard loop. */
/* Default behaviour: do nothing. */
void hook_late_init(void);

/* Called once, on getting SUSPEND event from USB. */
/* Default behaviour: do nothing. */
void hook_usb_suspend_entry(void);

/* Called repeatedly during the SUSPENDed state. */
/* Default behaviour: power down and periodically check
 * the matrix, cause wakeup if needed. */
void hook_usb_suspend_loop(void);

/* Called once, on getting WAKE event from USB. */
/* Default behaviour: disables sleep LED breathing and restores 
 * the "normal" indicator LED status by default. */
void hook_usb_wakeup(void);


/* -------------------------------------
 * Keyboard hooks
 * ------------------------------------- */

/* Called periodically from the keyboard loop (very often!) */
/* Default behaviour: do nothing. */
void hook_keyboard_loop(void);

/* Called on matrix state change event (every keypress => often!) */
/* Default behaviour: do nothing. */
void hook_matrix_change(keyevent_t event);

/* Called on default layer state change event. */
/* Default behaviour: do nothing. */
void hook_default_layer_change(uint32_t default_layer_state);

/* Called on layer state change event. */
/* Default behaviour: do nothing. */
void hook_layer_change(uint32_t layer_state);

/* Called on indicator LED update event (when reported from host). */
/* Default behaviour: calls keyboard_set_leds. */
void hook_keyboard_leds_change(uint8_t led_status);

/* Called once, on checking the bootmagic combos. */
/* Default behaviour: do nothing. */
void hook_bootmagic(void);


#endif /* _HOOKS_H_ */
