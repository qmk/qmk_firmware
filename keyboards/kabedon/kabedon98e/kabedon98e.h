/* Copyright 2021 KDon<370490639@qq.com>
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

#define XXXX KC_NO

#define LAYOUT( \
    KB00,   KA01, KB01, KA02, KB02,    KA03, KB03, KA04, KB04,    KA05, KB05, KB06, KB07,     KF07,    KE08,    KE00,        \
    KD00, KC01, KD01, KC02, KD02, KC03, KD03, KC04, KD04, KC05, KD05, KC06, KD06,   KD07,     KD09, KE09, KE10, KF10,  KA00, \
    KF00, KE01, KF01, KE02, KF02, KE03, KF03, KE04, KF04, KE05, KF05, KE06, KF06,   KE07,     KF09, KG09, KG10,        KC00, \
    KH00, KG01, KH01, KG02, KH02, KG03, KH03, KG04, KH04, KG05, KH05, KG06,      KH07,        KH09, KI09, KI10, KH10,        \
    KJ00, KJ01, KI02, KJ02, KI03, KJ03, KI04, KJ04, KI05, KJ05, KI06,       KJ07,     KI08,   KJ09, KK09, KJ10,        KG00, \
    KL00, KK01, KL01, KL03,               KL02,                 KL05,   KK07,   KL07, KK08, KL08,   KL09, KK10, KL10,  KI00  \
) { \
  { KA00,  KA01,  KA02,  KA03,  KA04,  KA05,  XXXX,  XXXX,  XXXX,  XXXX,  XXXX }, \
  { KB00,  KB01,  KB02,  KB03,  KB04,  KB05,  KB06,  KB07,  XXXX,  XXXX,  XXXX }, \
  { KC00,  KC01,  KC02,  KC03,  KC04,  KC05,  KC06,  XXXX,  XXXX,  XXXX,  XXXX }, \
  { KD00,  KD01,  KD02,  KD03,  KD04,  KD05,  KD06,  KD07,  XXXX,  KD09,  XXXX }, \
  { KE00,  KE01,  KE02,  KE03,  KE04,  KE05,  KE06,  KE07,  KE08,  KE09,  KE10 }, \
  { KF00,  KF01,  KF02,  KF03,  KF04,  KF05,  KF06,  KF07,  XXXX,  KF09,  KF10 }, \
  { KG00,  KG01,  KG02,  KG03,  KG04,  KG05,  KG06,  XXXX,  XXXX,  KG09,  KG10 }, \
  { KH00,  KH01,  KH02,  KH03,  KH04,  KH05,  XXXX,  KH07,  XXXX,  KH09,  KH10 }, \
  { KI00,  XXXX,  KI02,  KI03,  KI04,  KI05,  KI06,  XXXX,  KI08,  KI09,  KI10 }, \
  { KJ00,  KJ01,  KJ02,  KJ03,  KJ04,  KJ05,  XXXX,  KJ07,  XXXX,  KJ09,  KJ10 }, \
  { XXXX,  KK01,  XXXX,  XXXX,  XXXX,  XXXX,  XXXX,  KK07,  KK08,  KK09,  KK10 }, \
  { KL00,  KL01,  KL02,  KL03,  XXXX,  KL05,  XXXX,  KL07,  KL08,  KL09,  KL10 }  \
}
