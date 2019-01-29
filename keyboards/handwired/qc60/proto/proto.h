/* Copyright 2018 Michael Pio Mayol <mfmayol@up.edu.ph>
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

#include "qc60.h"

#include "quantum.h"

// readability
#define XXX KC_NO

/* Split Backspace
 * {R07, XXX, R05, R04, R03, R02, R01, R00}
 *
 * Split Right Shift
 * {R37, R36, R35, R34, R33, R32, R31, XXX}
 *
 * Split Left Shift
 * {L30, L31, L32, L33, L34, L35, L36, XXX}
 *
 * 6-key Bottom-left row
 * {R47, R46, R45, R44, R43, R42, XXX, XXX}
 */

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05, R06, R07, \
    L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, R16, R17, \
    L20, L21, L22, L23, L24, L25,           R21, R22, R23, R24, R25, R26, R27, \
    L30, L31, L32, L33, L34, L35, L36,      R31, R32, R33, R34, R35, R36, R37, \
    L40, L41, L42, L43, L44,                     R43, R44, R42, R45, R46, R47  \
) \
{ \
    {L00, L01, L02, L03, L04, L05, L06, XXX}, \
    {L10, L11, L12, L13, L14, L15, XXX, XXX}, \
    {L20, L21, L22, L23, L24, L25, XXX, XXX}, \
    {L30, L31, L32, L33, L34, L35, L36, XXX}, \
    {L40, L41, L42, L43, L44, XXX, XXX, XXX}, \
    {R07, XXX, R05, R04, R03, R02, R01, R00}, \
    {R17, R16, R15, R14, R13, R12, R11, R10}, \
    {R27, R26, R25, R24, R23, R22, R21, XXX}, \
    {R37, R36, R35, R34, R33, R32, R31, XXX}, \
    {R47, R46, R45, R44, R43, R42, XXX, XXX}, \
}

#define LAYOUT_ansi_default( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05,      R07, \
    L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, R16, R17, \
    L20, L21, L22, L23, L24, L25,           R21, R22, R23, R24, R25, R26, R27, \
         L31, L32, L33, L34, L35, L36,      R31, R32, R33, R34, R35, R36,      \
    L40, L41, L42, L43, L44,                     R43, R44, R42, R45, R46, R47  \
) \
{ \
    {L00, L01, L02, L03, L04, L05, L06, XXX}, \
    {L10, L11, L12, L13, L14, L15, XXX, XXX}, \
    {L20, L21, L22, L23, L24, L25, XXX, XXX}, \
    {XXX, L31, L32, L33, L34, L35, L36, XXX}, \
    {L40, L41, L42, L43, L44, XXX, XXX, XXX}, \
    {R07, XXX, R05, R04, R03, R02, R01, R00}, \
    {R17, R16, R15, R14, R13, R12, R11, R10}, \
    {R27, R26, R25, R24, R23, R22, R21, XXX}, \
    {XXX, R36, R35, R34, R33, R32, R31, XXX}, \
    {R47, R46, R45, R44, R43, R42, XXX, XXX}, \
}

#define LAYOUT_ansi_alt( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05,      R07, \
    L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, R16, R17, \
    L20, L21, L22, L23, L24, L25,           R21, R22, R23, R24, R25, R26, R27, \
         L31, L32, L33, L34, L35, L36,      R31, R32, R33, R34, R35, R36,      \
    L40, L41, L42, L43, L44,                     R43, R44,      R45, R46, R47  \
) \
{ \
    {L00, L01, L02, L03, L04, L05, L06, XXX}, \
    {L10, L11, L12, L13, L14, L15, XXX, XXX}, \
    {L20, L21, L22, L23, L24, L25, XXX, XXX}, \
    {XXX, L31, L32, L33, L34, L35, L36, XXX}, \
    {L40, L41, L42, L43, L44, XXX, XXX, XXX}, \
    {R07, XXX, R05, R04, R03, R02, R01, R00}, \
    {R17, R16, R15, R14, R13, R12, R11, R10}, \
    {R27, R26, R25, R24, R23, R22, R21, XXX}, \
    {XXX, R36, R35, R34, R33, R32, R31, XXX}, \
    {R47, R46, R45, R44, R43, XXX, XXX, XXX}, \
}

#define LAYOUT_iso_default( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05,           R07, \
    L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, R16,           \
    L20, L21, L22, L23, L24, L25,           R21, R22, R23, R24, R25, R26, R17, R27, \
    L30, L31, L32, L33, L34, L35, L36,      R31, R32, R33, R34, R35, R36,           \
    L40, L41, L42, L43, L44,                     R43, R44, R42, R45, R46,      R47  \
) \
{ \
    {L00, L01, L02, L03, L04, L05, L06, XXX}, \
    {L10, L11, L12, L13, L14, L15, XXX, XXX}, \
    {L20, L21, L22, L23, L24, L25, XXX, XXX}, \
    {L30, L31, L32, L33, L34, L35, L36, XXX}, \
    {L40, L41, L42, L43, L44, XXX, XXX, XXX}, \
    {R07, XXX, R05, R04, R03, R02, R01, R00}, \
    {R17, R16, R15, R14, R13, R12, R11, R10}, \
    {R27, R26, R25, R24, R23, R22, R21, XXX}, \
    {XXX, R36, R35, R34, R33, R32, R31, XXX}, \
    {R47, R46, R45, R44, R43, R42, XXX, XXX}, \
}

#define LAYOUT_iso_alt( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05,           R07, \
    L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, R16,           \
    L20, L21, L22, L23, L24, L25,           R21, R22, R23, R24, R25, R26, R17, R27, \
    L30, L31, L32, L33, L34, L35, L36,      R31, R32, R33, R34, R35, R36,           \
    L40, L41, L42, L43, L44,                     R43, R44,      R45, R46,      R47  \
) \
{ \
    {L00, L01, L02, L03, L04, L05, L06, XXX}, \
    {L10, L11, L12, L13, L14, L15, XXX, XXX}, \
    {L20, L21, L22, L23, L24, L25, XXX, XXX}, \
    {L30, L31, L32, L33, L34, L35, L36, XXX}, \
    {L40, L41, L42, L43, L44, XXX, XXX, XXX}, \
    {R07, XXX, R05, R04, R03, R02, R01, R00}, \
    {R17, R16, R15, R14, R13, R12, R11, R10}, \
    {R27, R26, R25, R24, R23, R22, R21, XXX}, \
    {XXX, R36, R35, R34, R33, R32, R31, XXX}, \
    {R47, R46, R45, R44, R43, XXX, XXX, XXX}, \
}

#define LAYOUT_hhkb_default( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05, R06, R07, \
    L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, R16, R17, \
    L20, L21, L22, L23, L24, L25,           R21, R22, R23, R24, R25, R26, R27, \
         L31, L32, L33, L34, L35, L36,      R31, R32, R33, R34, R35, R36, R37, \
         L41, L42, L43, L44,                     R43, R44,      R45, R46       \
) \
{ \
    {L00, L01, L02, L03, L04, L05, L06, XXX}, \
    {L10, L11, L12, L13, L14, L15, XXX, XXX}, \
    {L20, L21, L22, L23, L24, L25, XXX, XXX}, \
    {XXX, L31, L32, L33, L34, L35, L36, XXX}, \
    {XXX, L41, L42, L43, L44, XXX, XXX, XXX}, \
    {R07, R06, R05, R04, R03, R02, R01, R00}, \
    {R17, R16, R15, R14, R13, R12, R11, R10}, \
    {R27, R26, R25, R24, R23, R22, R21, XXX}, \
    {R37, R36, R35, R34, R33, R32, R31, XXX}, \
    {XXX, R46, R45, R44, R43, XXX, XXX, XXX}, \
}

#define LAYOUT_hhkb_split_lshift( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05, R06, R07, \
    L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, R16, R17, \
    L20, L21, L22, L23, L24, L25,           R21, R22, R23, R24, R25, R26, R27, \
    L30, L31, L32, L33, L34, L35, L36,      R31, R32, R33, R34, R35, R36, R37, \
         L41, L42, L43, L44,                     R43, R44,      R45, R46       \
) \
{ \
    {L00, L01, L02, L03, L04, L05, L06, XXX}, \
    {L10, L11, L12, L13, L14, L15, XXX, XXX}, \
    {L20, L21, L22, L23, L24, L25, XXX, XXX}, \
    {L30, L31, L32, L33, L34, L35, L36, XXX}, \
    {XXX, L41, L42, L43, L44, XXX, XXX, XXX}, \
    {R07, R06, R05, R04, R03, R02, R01, R00}, \
    {R17, R16, R15, R14, R13, R12, R11, R10}, \
    {R27, R26, R25, R24, R23, R22, R21, XXX}, \
    {R37, R36, R35, R34, R33, R32, R31, XXX}, \
    {XXX, R46, R45, R44, R43, XXX, XXX, XXX}, \
}

#define LAYOUT_wkl_default( \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05,      R07, \
    L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, R16, R17, \
    L20, L21, L22, L23, L24, L25,           R21, R22, R23, R24, R25, R26, R27, \
         L31, L32, L33, L34, L35, L36,      R31, R32, R33, R34, R35, R36,       \
    L40,      L42, L43, L44,                     R43, R44,      R45,      R47  \
) \
{ \
    {L00, L01, L02, L03, L04, L05, L06, XXX}, \
    {L10, L11, L12, L13, L14, L15, XXX, XXX}, \
    {L20, L21, L22, L23, L24, L25, XXX, XXX}, \
    {XXX, L31, L32, L33, L34, L35, L36, XXX}, \
    {L40, XXX, L42, L43, L44, XXX, XXX, XXX}, \
    {R07, XXX, R05, R04, R03, R02, R01, R00}, \
    {R17, R16, R15, R14, R13, R12, R11, R10}, \
    {R27, R26, R25, R24, R23, R22, R21, XXX}, \
    {XXX, R36, R35, R34, R33, R32, R31, XXX}, \
    {R47, XXX, R45, R44, R43, XXX, XXX, XXX}, \
}
