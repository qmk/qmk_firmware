/* Copyright 2019 flehrad
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "quantum.h"

#define LAYOUT_ortho_4x4( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33  \
) { \
    { K00,   K01,   K02,   K03 }, \
    { K10,   K11,   K12,   K13 }, \
    { K20,   K21,   K22,   K23 }, \
    { K30,   K31,   K32,   K33 }  \
}

#define LAYOUT_tradestation( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
       K20,      K22,   \
       K30,      K32    \
) { \
    { K00,   K01,   K02,   K03   }, \
    { K10,   K11,   K12,   K13   }, \
    { K20,   KC_NO, K22,   KC_NO }, \
    { K30,   KC_NO, K32,   KC_NO }  \
}
