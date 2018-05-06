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
#include "action.h"
#include "action_util.h"
#include "action_macro.h"
#include "wait.h"

#ifdef DEBUG_ACTION
#include "debug.h"
#else
#include "nodebug.h"
#endif


#ifndef NO_ACTION_MACRO

#define MACRO_READ()  (macro = MACRO_GET(macro_p++))
/** \brief Action Macro Play
 *
 * FIXME: Needs doc
 */
void action_macro_play(const macro_t *macro_p)
{
    macro_t macro = END;
    uint8_t interval = 0;

    if (!macro_p) return;
    while (true) {
        switch (MACRO_READ()) {
            case KEY_DOWN:
                MACRO_READ();
                dprintf("KEY_DOWN(%02X)\n", macro);
                if (IS_MOD(macro)) {
                    add_macro_mods(MOD_BIT(macro));
                    send_keyboard_report();
                } else {
                    register_code(macro);
                }
                break;
            case KEY_UP:
                MACRO_READ();
                dprintf("KEY_UP(%02X)\n", macro);
                if (IS_MOD(macro)) {
                    del_macro_mods(MOD_BIT(macro));
                    send_keyboard_report();
                } else {
                    unregister_code(macro);
                }
                break;
            case WAIT:
                MACRO_READ();
                dprintf("WAIT(%u)\n", macro);
                { uint8_t ms = macro; while (ms--) wait_ms(1); }
                break;
            case INTERVAL:
                interval = MACRO_READ();
                dprintf("INTERVAL(%u)\n", interval);
                break;
            case 0x04 ... 0x73:
                dprintf("DOWN(%02X)\n", macro);
                register_code(macro);
                break;
            case 0x84 ... 0xF3:
                dprintf("UP(%02X)\n", macro);
                unregister_code(macro&0x7F);
                break;
            case END:
            default:
                return;
        }
        // interval
        { uint8_t ms = interval; while (ms--) wait_ms(1); }
    }
}
#endif
