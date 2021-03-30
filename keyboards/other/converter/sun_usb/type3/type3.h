/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef TYPE3_H
#define TYPE3_H

#include "quantum.h"

/* Sun type 3 keyboard
,-------.  ,-----------------------------------------------------------.  ,-----------.
| 01| 03|  | 05| 06|     08|     0A|     0C|     0E|     10| 11| 12| 2B|  | 15| 16| 17|
|-------|  |-----------------------------------------------------------|  |-----------|
| 19| 1A|  | 1D| 1E| 1F| 20| 21| 22| 23| 24| 25| 26| 27| 28| 29| 58| 2A|  | 2D| 2E| 2F|
|-------|  |-----------------------------------------------------------|  |-----------|
| 31| 33|  |  35 | 36| 37| 38| 39| 3A| 3B| 3C| 3D| 3E| 3F| 40| 41| 42  |  | 44| 45| 46|
|-------|  |-----------------------------------------------------------|  |-----------|
| 48| 49|  |  4C  | 4D| 4E| 4F| 50| 51| 52| 53| 54| 55| 56| 57|   59   |  | 5B| 5C| 5D|
|-------|  |-----------------------------------------------------------|  |-----------|
| 5F| 61|  |   63   | 64| 65| 66| 67| 68| 69| 6A| 6B| 6C| 6D|    6E| 6F|  | 70| 71| 72|
`-------'  |-----------------------------------------------------------|  `-----------'
           | 77 | 78  |               79                  | 7A  |   13 |
           `-----------------------------------------------------------'
*/


#define LAYOUT(                                                         \
    K01,K03,  K05,K06,    K08,    K0A,    K0C,    K0E,    K10,K11,K12,K2B,  K15,K16,K17, \
    K19,K1A,  K1D,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K58,K2A,  K2D,K2E,K2F, \
    K31,K33,  K35, K36,K37,K38,K39,K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,   K42,  K44,K45,K46, \
    K48,K49,  K4C,  K4D,K4E,K4F,K50,K51,K52,K53,K54,K55,K56,K57,      K59,  K5B,K5C,K5D, \
    K5F,K61,  K63,   K64,K65,K66,K67,K68,K69,K6A,K6B,K6C,K6D,     K6E,K6F,  K70,K71,K72, \
              K77,K78,                    K79,                    K7A,K13                \
) { \
    { KC_NO,  K01 , KC_NO,  K03 , KC_NO,  K05 ,  K06 , KC_NO }, \
    {  K08 , KC_NO,  K0A , KC_NO,  K0C , KC_NO,  K0E , KC_NO }, \
    {  K10 ,  K11 ,  K12 ,  K13 , KC_NO,  K15 ,  K16 ,  K17  }, \
    { KC_NO,  K19 ,  K1A , KC_NO, KC_NO,  K1D ,  K1E ,  K1F  }, \
    {  K20 ,  K21 ,  K22 ,  K23 ,  K24 ,  K25 ,  K26 ,  K27  }, \
    {  K28 ,  K29 ,  K2A ,  K2B , KC_NO,  K2D ,  K2E ,  K2F  }, \
    { KC_NO,  K31 , KC_NO,  K33 , KC_NO,  K35 ,  K36 ,  K37  }, \
    {  K38 ,  K39 ,  K3A ,  K3B ,  K3C ,  K3D ,  K3E ,  K3F  }, \
    {  K40 ,  K41 ,  K42 , KC_NO,  K44 ,  K45 ,  K46 , KC_NO }, \
    {  K48 ,  K49 , KC_NO, KC_NO,  K4C ,  K4D ,  K4E ,  K4F  }, \
    {  K50 ,  K51 ,  K52 ,  K53 ,  K54 ,  K55 ,  K56 ,  K57  }, \
    {  K58 ,  K59 , KC_NO,  K5B ,  K5C ,  K5D , KC_NO,  K5F  }, \
    { KC_NO,  K61 , KC_NO,  K63 ,  K64 ,  K65 ,  K66 ,  K67  }, \
    {  K68 ,  K69 ,  K6A ,  K6B ,  K6C ,  K6D ,  K6E ,  K6F  }, \
    {  K70 ,  K71 ,  K72 , KC_NO, KC_NO, KC_NO, KC_NO,  K77  }, \
    {  K78 ,  K79 ,  K7A , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }  \
}

#endif
