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
#include <util/delay.h>
#include "action.h"
#include "action_macro.h"

#ifdef DEBUG_ACTION
#include "debug.h"
#else
#include "nodebug.h"
#endif


#ifndef NO_ACTION_MACRO

#define MACRO_READ()  (macro = pgm_read_byte(macro_p++))
void action_macro_play(const macro_t *macro_p)
{
    macro_t macro = END;
    uint8_t interval = 0;

    if (!macro_p) return;
    while (true) {
        switch (MACRO_READ()) {
            case INTERVAL:
                interval = MACRO_READ();
                debug("INTERVAL("); debug_dec(interval); debug(")\n");
                break;
            case WAIT:
                MACRO_READ();
                debug("WAIT("); debug_dec(macro); debug(")\n");
                { uint8_t ms = macro; while (ms--) _delay_ms(1); }
                break;
            case MODS_DOWN:
                MACRO_READ();
                debug("MODS_DOWN("); debug_hex(macro); debug(")\n");
                add_mods(macro);
                break;
            case MODS_UP:
                MACRO_READ();
                debug("MODS_UP("); debug_hex(macro); debug(")\n");
                del_mods(macro);
                break;
            case 0x04 ... 0x73:
                debug("DOWN("); debug_hex(macro); debug(")\n");
                register_code(macro);
                break;
            case 0x84 ... 0xF3:
                debug("UP("); debug_hex(macro); debug(")\n");
                unregister_code(macro&0x7F);
                break;
            case END:
            default:
                return;
        }
        // interval
        { uint8_t ms = interval; while (ms--) _delay_ms(1); }
    }
}
#endif
