/*
 * Copyright (c) 2021 Christiano Haesbaert <haesbaert@haesbaert.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E,      K0G,   \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1E,      K1F,        \
    K20,   K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E,    K2F,        \
    K30,    K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,                    \
    K41,       K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4D,          K4F,        \
         K51,   K53,                  K57,                 K5B,   K5D,    K5E, K5F, K5G    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   KC_NO, K0G   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   KC_NO, K1E,   K1F,   KC_NO }, \
    { K20,   KC_NO, K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E,   K2F,   KC_NO }, \
    { K30,   KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   KC_NO, KC_NO, KC_NO }, \
    { KC_NO, K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48,   K49,   K4A,   K4B,   KC_NO, K4D,   KC_NO, K4F,   KC_NO }, \
    { KC_NO, K51,   KC_NO, K53,   KC_NO, KC_NO, KC_NO, K57,   KC_NO, KC_NO, KC_NO, K5B,   KC_NO, K5D,   K5E,   K5F,   K5G   }, \
}
