/* Copyright 2017 Fred Sundvik
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bootloader.h"
#include "samd51j18a.h"

//Set watchdog timer to reset. Directs the bootloader to stay in programming mode.
void bootloader_jump(void)
{
    //Keyboards released with certain bootloader can not enter bootloader from app until workaround is created
    uint8_t ver_no_jump[] = "v2.18Jun 22 2018 17:28:08";
    uint8_t *ver_check = ver_no_jump;
    uint8_t *boot_check = (uint8_t *)0x21A0;
    while (*ver_check && *boot_check == *ver_check)
    {
        ver_check++;
        boot_check++;
    }
    if (!*ver_check)
    {
        //Version match
        //Software workaround would go here
        return; //No software restart method implemented... must use hardware reset button
    }

    WDT->CTRLA.bit.ENABLE = 0;
    while (WDT->SYNCBUSY.bit.ENABLE) {}
    while (WDT->CTRLA.bit.ENABLE) {}
    WDT->CONFIG.bit.WINDOW = 0;
    WDT->CONFIG.bit.PER = 0;
    WDT->EWCTRL.bit.EWOFFSET = 0;
    WDT->CTRLA.bit.ENABLE = 1;
    while (WDT->SYNCBUSY.bit.ENABLE) {}
    while (!WDT->CTRLA.bit.ENABLE) {}
    while (1) {} //Wait on timeout
}
