/* Copyright 2019 @haswellep
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
#pragma once

#include "quantum.h"

#define NOP KC_NO

#define LAYOUT( \
    L01, L02, L03, L04, L05, L06,              R01, R02, R03, R04, R05, R06, R28, R07, R35, \
    L07, L08, L09, L10, L11, L12,              R08, R09, R10, R11, R12, R13, R34, R14, \
    L13, L14, L15, L16, L17, L18,              R15, R16, R17, R18, R19, R20, R21,  \
    L19, L20, L21, L22, L23, L24, L25,    R22, R23, R24, R25, R26, R27,        R29, \
                   L26, L27, L28, L29,    R30, R31, R32, R33                      \
    ) \
    { \
        { L01, L02, L03, L04, L05, L06, NOP, NOP  }, \
        { L07, L08, L09, L10, L11, L12, NOP, NOP  }, \
        { L13, L14, L15, L16, L17, L18, NOP, NOP  }, \
        { L19, L20, L21, L22, L23, L24, L25, NOP  }, \
        { NOP, NOP, NOP, L26, L27, L28, L29, NOP  }, \
        { NOP, R01, R02, R03, R04, R05, R06 ,R07  }, \
        { NOP, R08, R09, R10, R11, R12, R13, R14  }, \
        { NOP, R15, R16 ,R17, R18, R19, R20, R21  }, \
        { R22, R23, R24, R25, R26 ,R27, R28, R29  }, \
        { R30, R31, R32, R33, NOP, NOP, R34, R35 }  \
    }

#define DUMMY KC_A

#define TESTLAYOUT( \
    L01, L02, L03, L04, L05, L06,              R01, R02, R03, R04, R05, R06, R28, R07, R35, \
    L07, L08, L09, L10, L11, L12,              R08, R09, R10, R11, R12, R13, R34, R14, \
    L13, L14, L15, L16, L17, L18,              R15, R16, R17, R18, R19, R20, R21,  \
    L19, L20, L21, L22, L23, L24, L25,    R22, R23, R24, R25, R26, R27,        R29, \
                   L26, L27, L28, L29,    R30, R31, R32, R33                      \
    ) \
    { \
        { L01, L02, L03, L04, L05, L06, DUMMY, DUMMY  }, \
        { L07, L08, L09, L10, L11, L12, DUMMY, DUMMY  }, \
        { L13, L14, L15, L16, L17, L18, DUMMY, DUMMY  }, \
        { L19, L20, L21, L22, L23, L24, L25, DUMMY  }, \
        { DUMMY, DUMMY, DUMMY, L26, L27, L28, L29, DUMMY  }, \
        { DUMMY, R01, R02, R03, R04, R05, R06 ,R07  }, \
        { DUMMY, R08, R09, R10, R11, R12, R13, R14  }, \
        { DUMMY, R15, R16 ,R17, R18, R19, R20, R21  }, \
        { R22, R23, R24, R25, R26 ,R27, R28, R29  }, \
        { R30, R31, R32, R33, DUMMY, DUMMY, R34, R35 }  \
    }
