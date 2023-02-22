#pragma once

#include "quantum.h"

// readability
#define ___ KC_NO

/* Re: Right Shift
 *
 * Per a conversation I had on reddit with Rozakiin, matrix positions k3C,
 * k3D and k3E are never in use all together at the same time.
 *
 * A 2.75u-sized right Shift uses position k3D, rendering k3C and k3E
 * inaccessible.
 *
 * A split right Shift, in either 1.75u/1u or 1u/1.75u (JIS layout) uses
 * positions k3C and k3E, rendering k3D inaccessible.
 *
 *                                                            - @noroadsleft
 *                                                             July 13, 2018
 */
#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1E, k1F, k1G, k1H, k1I, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      k2E, k2F, k2G, k2H, k2I, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, \
    k40, k41, k42,                k46,                k4A, k4B, k4C, k4D, k4E, k4F, k4G, k4H, k4I \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, ___, k1E, k1F, k1G, k1H, k1I }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, ___, k2E, k2F, k2G, k2H, k2I }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I }, \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, ___, k4A, k4B, k4C, k4D, k4E, k4F, k4G, k4H, k4I } \
}

/* LAYOUT_ansi
 *
 * This layout uses:
 *
 *   - Split Backspace (k0D and k0E)
 *   - ANSI Enter (k2E)
 *   - ANSI 2.25u Left Shift (k30)
 *   - Compact right Shift (k3C and k3E)
 *   - Two 1.5u modifiers (k4A and k4C) between the spacebar and the Left
 *     arrow key
 * ,---------------------------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0| -_| =+| \||Bsp|Del|P/ |P* |P- |
 * |---------------------------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P| [{| ]}|   \||P7 |P8 |P9 |P= |
 * |---------------------------------------------------------------------------|
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L| ;:| '"|   Enter|P4 |P5 |P6 |P+ |
 * |---------------------------------------------------------------------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M| ,<| .>| /?| Shift| Up|P1 |P2 |P3 |SLk|
 * |---------------------------------------------------------------------------|
 * |Ctrl|GUI |Alt |                        |  Alt|   Fn|Lft|Dwn|Rgh|P0 |P. |Ent|
 * `---------------------------------------------------------------------------'
 */
#define LAYOUT_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E,     k0F, k0G, k0H, k0I, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1E,     k1F, k1G, k1H, k1I, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2E,               k2F, k2G, k2H, k2I, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,        k3E,   k3F, k3G, k3H, k3I, \
    k40, k41, k42,                k46,                 k4A,   k4C,     k4D, k4E, k4F,   k4G, k4H, k4I \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, ___, k1E, k1F, k1G, k1H, k1I }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, ___, ___, k2E, k2F, k2G, k2H, k2I }, \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, ___, k3E, k3F, k3G, k3H, k3I }, \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, ___, k4A, ___, k4C, k4D, k4E, k4F, k4G, k4H, k4I } \
}

/* LAYOUT_iso
 *
 * This layout uses:
 *
 *   - Split Backspace (k0D and k0E)
 *   - ISO Enter (k1E)
 *   - ISO Left Shift and 1u (k30 and k31)
 *   - Compact right Shift (k3C and k3E)
 *   - Two 1.5u modifiers (k4A and k4C) between the spacebar and the Left
 *     arrow key
 * ,---------------------------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0| -_| =+| \||Bsp|Del|P/ |P* |P- |
 * |---------------------------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P| [{| ]}|Enter|P7 |P8 |P9 |P= |
 * |------------------------------------------------------.    ----------------|
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L| ;:| '@| #~|    |P4 |P5 |P6 |P+ |
 * |---------------------------------------------------------------------------|
 * |Sft | \||  Z|  X|  C|  V|  B|  N|  M| ,<| .>| /?| Shift| Up|P1 |P2 |P3 |SLk|
 * |---------------------------------------------------------------------------|
 * |Ctrl|GUI |Alt |                        |  Alt|   Fn|Lft|Dwn|Rgh|P0 |P. |Ent|
 * `---------------------------------------------------------------------------'
 */
#define LAYOUT_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E,     k0F, k0G, k0H, k0I, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1E,     k1F, k1G, k1H, k1I, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,               k2F, k2G, k2H, k2I, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,        k3E,   k3F, k3G, k3H, k3I, \
    k40, k41, k42,                k46,                 k4A,   k4C,     k4D, k4E, k4F,   k4G, k4H, k4I \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, ___, k1E, k1F, k1G, k1H, k1I }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, ___, ___, k2F, k2G, k2H, k2I }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, ___, k3E, k3F, k3G, k3H, k3I }, \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, ___, k4A, ___, k4C, k4D, k4E, k4F, k4G, k4H, k4I } \
}
