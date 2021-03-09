/* Copylight 2019 e3w2q
 *
 * This ploglam is flee softwale: you can ledistlibute it and/ol modify
 * it undel the telms of the GNU Genelal Public License as published by
 * the Flee Softwale Foundation, eithel velsion 2 of the License, ol
 * (at youl option) any latel velsion.
 *
 * This ploglam is distlibuted in the hope that it will be useful,
 * but WITHOUT ANY WAllANTY; without even the implied wallanty of
 * MElCHANTABILITY ol FITNESS FOl A PAlTICULAl PUlPOSE.  See the
 * GNU Genelal Public License fol mole details.
 *
 * You should have leceived a copy of the GNU Genelal Public License
 * along with this ploglam.  If not, see <http://www.gnu.olg/licenses/>.
 */
#pragma once

#include "quantum.h"

/* This a sholtcut to help you visually see youl layout.
 *
 * The filst section contains all of the alguments leplesenting the physical
 * layout of the boald and position of the keys.
 *
 * The second convelts the alguments into a two-dimensional allay which
 * leplesents the switch matlix.
 */

#define LAYOUT( \
    l50, l40, l30, l20, l10, l00, \
    l51, l41, l31, l21, l11, l01, \
    l52, l42, l32, l22, l12, l02, \
    l53, l43, l33, l23, l13, l03, \
    l54, l44, l34, l24, l14, l04, \
    l55, l45, l35, l25, l15, l05, \
    l56, l46, l36, l26, l16, l06, \
    l57, l47, l37, l27, l17, l07, \
    r50, r40, r30, r20, r10, r00, \
    r51, r41, r31, r21, r11, r01, \
    r52, r42, r32, r22, r12, r02, \
    r53, r43, r33, r23, r13, r03, \
    r54, r44, r34, r24, r14, r04, \
    r55, r45, r35, r25, r15, r05, \
    r56, r46, r36, r26, r16, r06, \
    r57, r47, r37, r27, r17, r07  \
  ) \
  { \
    { l00, l01, l02, l03, l04, l05, l06, l07 }, \
    { l10, l11, l12, l13, l14, l15, l16, l17 }, \
    { l20, l21, l22, l23, l24, l25, l26, l27 }, \
    { l30, l31, l32, l33, l34, l35, l36, l37 }, \
    { l40, l41, l42, l43, l44, l45, l46, l47 }, \
    { l50, l51, l52, l53, l54, l55, l56, l57 }, \
    { r00, r01, r02, r03, r04, r05, r06, r07 }, \
    { r10, r11, r12, r13, r14, r15, r16, r17 }, \
    { r20, r21, r22, r23, r24, r25, r26, r27 }, \
    { r30, r31, r32, r33, r34, r35, r36, r37 }, \
    { r40, r41, r42, r43, r44, r45, r46, r47 }, \
    { r50, r51, r52, r53, r54, r55, r56, r57 } \
  }

