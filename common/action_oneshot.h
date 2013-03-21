/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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
#ifndef ACTION_ONESHOT_H
#define ACTION_ONESHOT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef NO_ACTION_TAPPING
    #define NO_ACTION_ONESHOT
#endif

#ifndef NO_ACTION_ONESHOT
/* Oneshot modifier
 *
 * Problem: Want to capitalize like 'The' but the result tends to be 'THe'.
 * Solution: Oneshot modifier have its effect on only one key coming next.
 *           Tap Shift, then type 't', 'h' and 'e'. Not need to hold Shift key.
 *
 *  Hold:       works as normal modifier.
 *  Tap:        one shot modifier.
 *  2 Tap:      cancel one shot modifier.
 *  5-Tap:      toggles enable/disable oneshot feature.
 */
typedef struct {
    uint8_t mods;
    bool    disabled;
}   oneshot_state_t;


oneshot_state_t oneshot_state;

void oneshot_start(uint8_t mods);
void oneshot_cancel(void);
void oneshot_toggle(void);
#endif

#endif
