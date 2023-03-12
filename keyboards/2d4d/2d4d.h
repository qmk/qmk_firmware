/*
Copyright 2023 Mehmet DEĞİRMENCİOĞLU (@mechMehmet) <https://www.youtube.com/@mechmehmet>

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

#pragma once

#include "quantum.h"

//üst kısım görsel amaç, tuş düzeni (layout) yerleşiminde kullanılacak, satır sütun nasıl görünüyorsa o şekilde düzenleyebilirsin
//alt kısım da satır sütun yerleşimini gösterecek. yani 8 satır 6 sütun
// harflendirme önemli değil 
// satırları belirlerkken;
// 1                       8  
// 2                       7 
// 3                       6
// 4                       5 

// sütunları bu şekilde bağladım;
// 1 2 3 4 5 6 - 6 5 4 3 2 1
//kabloları nasıl bağladıysam, tuşları nasıl yerleştirdiysem ona uygun olarak üstü düzenledim.

#define LAYOUT_8x6( \
    K000, K001, K002, K003, K004, K005,              K705, K704, K703, K702, K701, K700, \
    K100, K101, K102, K103, K104, K105,              K605, K604, K603, K602, K601, K600, \
    K200, K201, K202, K203, K204, K205,              K505, K504, K503, K502, K501, K500, \
    K300, K301, K302,                   K305,  K405,                   K402, K401, K400, \
                                  K303, K304,  K404, K403                                \
) { \
    { K000, K001, K002, K003, K004, K005 }, \
    { K100, K101, K102, K103, K104, K105 }, \
    { K200, K201, K202, K203, K204, K205 }, \
    { K300, K301, K302, K303, K304, K305 }, \
    { K400, K401, K402, K403, K404, K405 }, \
    { K500, K501, K502, K503, K504, K505 }, \
    { K600, K601, K602, K603, K604, K605 }, \
    { K700, K701, K702, K703, K704, K705 }  \
}


