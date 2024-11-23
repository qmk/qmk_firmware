/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

#include "quantum.h"

void board_init(void) {
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
}

void bootloader_jump(void) {
    // This board doesn't use the "standard" stm32duino bootloader. There's no information on how to jump to the custom bootloader, so all we can do here is reset.
    NVIC_SystemReset();
}
