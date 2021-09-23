/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#ifndef PINGMASTER_H
#define PINGMASTER_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, k011, k012, k013, k014, k015, k016, k017, k018, k019, k020, k021, k022, k023,  \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111, k112, k113, k114,       k116, k117, k118, k119, k120, k121, k122, k123,  \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211, k212, k213, k214,       k216, k217, k218, k219, k220, k221, k222, k223,  \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311, k312, k313,             k316, k317, k318, k319, k320, k321, k322, k323,  \
    k40, k41, k42,                     k47,                 k411, k412,       k414,       k416, k417, k418, k419, k420, k421, k422, k423   \
) { \
  	{ K000, K001, K002, K003,  K004,  K005,  K006,  K007, K008,  K009,  K010,  K011, K012, K013,  K014,  K015,  K016, K017, K018, K019, K020, K021, K022, K023}, \
  	{ K100, K101, K102, K103,  K104,  K105,  K106,  K107, K108,  K109,  K110,  K111, K112, K113,  K114,  KC_NO, K116, K117, K118, K119, K120, K121, K122, K123}, \
  	{ K200, K201, K202, K203,  K204,  K205,  K206,  K207, K208,  K209,  K210,  K211, K212, K213,  K214,  KC_NO, K216, K217, K218, K219, K220, K221, K222, K223}, \
  	{ K300, K301, K302, K303,  K304,  K305   K306,  K307, K308,  K309,  K310,  K311, K312, K313,  KC_NO, KC_NO, K316, K317, K318, K319, K320, K321, K322, K313}, \
  	{ K400, K401, K402, KC_NO, KC_NO, KC_NO, KC_NO, K407, KC_NO, KC_NO, KC_NO, K411, K412, KC_NO, K414,  KC_NO, K416, K417, K418, K419, K420, K421, K422} \
}

#endif
