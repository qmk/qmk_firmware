// Copyright 20010 Alex Norman
// writen by Alex Norman
//
// This file is part of avr-bytequeue.
//
// avr-bytequeue is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
// avr-bytequeue is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with avr-bytequeue.  If not, see <http://www.gnu.org/licenses/>.

// AVR specific code
// should be able to port to other systems by simply providing chip specific
// implementations of the typedef and these functions

#include "interrupt_setting.h"
#if defined(__AVR__)
#    include <avr/interrupt.h>

interrupt_setting_t store_and_clear_interrupt(void) {
    uint8_t sreg = SREG;
    cli();
    return sreg;
}

void restore_interrupt_setting(interrupt_setting_t setting) { SREG = setting; }
#elif defined(__arm__)
#    include <ch.h>

interrupt_setting_t store_and_clear_interrupt(void) {
    chSysLock();
    return 0;
}

void restore_interrupt_setting(interrupt_setting_t setting) { chSysUnlock(); }
#endif
