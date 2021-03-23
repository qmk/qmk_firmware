/* Copyright 2020 Joseph Wasson
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

#define SPACE_COUNT 2

#define TEMPLATE_TKL(\
  KESC,       KF01, KF02, KF03, KF04, KF05, KF06, KF07, KF08, KF09, KF10, KF11, KF12,   KSCL, KPRS, KADJ, \
  KGRV, K_1 , K_2 , K_3 , K_4 , K_5 , K_6 , K_7 , K_8 , K_9 , K_0 , KMIN, KEQL, KBLS,   KINS, KHOM, KPUP, \
  KTAB, K_Q , K_W , K_E , K_R , K_T , K_Y , K_U , K_I , K_O , K_P , KLBR, KRBR, KBSP,   KDEL, KEND, LPDN, \
  KCAP, K_A , K_S , K_D , K_F , K_G , K_H , K_J , K_K , K_L , KSMI, KQUO,       KENT,                     \
  KLSH, K_Z , K_X , K_C , K_V , K_B , K_N , K_M , KCMA, KDOT, KSLS,             KRSH,         K_UP,       \
  KLCT, KLOS, KLAL,             KSP2, KSP3, KSP1,             KRAL, KROS, KRCT, KPTT,   K_LT, K_DN, K_RT  \
) LAYOUT_all( \
	KF01, KTAB, K_Q , K_W , K_E , K_R , K_T , K_Y , K_U , K_I , K_O , K_P , KLBR, KRBR, KBSP, \
	KF02, KCAP, K_A , K_S , K_D , K_F , K_G , K_H , K_J , K_K , K_L , KSMI, KQUO,       KENT, \
	KF03, KLSH, K_Z , K_X , K_C , K_V , K_B , K_N , K_M , KCMA, KDOT, KSLS,       KRSH, KADJ, \
	KF04,             KLOS, KLAL,       KSP2,             KSP1,       KRAL, KESC              \
)
