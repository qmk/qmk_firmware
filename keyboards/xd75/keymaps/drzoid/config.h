/* Copyright 2017 Benjamin Kesselring
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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// place overrides here

#ifdef MANUFACTURER
  #undef MANUFACTURER
  #define MANUFACTURER drzoid
#endif

//Comment/uncomment based on OS setup
#define DRZ_AZERTY_FR_OS  // Qwerty keycaps & layout with Azerty French OS */
//#define DRZ_QWERTY_INTL_OS  // Qwerty keycaps & layout with Qwerty Intl OS */


#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

//Unicode chars
#define DRZ_UC_STAR     RALT(UC(0x2605))    // ★
#define DRZ_UC_SQUARE   RALT(UC(0x00B2))    // ²
#define DRZ_UC_CUBE     RALT(UC(0x00B3))    // ³

//uni-sized keycodes for keymap uses
#define DRZ_ENT  KC_ENTER
#define DRZ_BSP  KC_BSPACE
#define DRZ_SPA  KC_SPACE
#define DRZ_UST  DRZ_UC_STAR
#define DRZ_USQ  DRZ_UC_SQUARE
#define DRZ_UCU  DRZ_UC_CUBE
#define DRZ_LCK  DRZ_LOCK
#define DRZ__ST  LSFT(KC_TAB)
#define DRZ__SH  DRZ_SWAP_HANDS
#define DRZ__LS  KC_LSHIFT
#define DRZ__RS  KC_RSHIFT
#define DRZ__AC  DRZ_ACCENTS_TAPDANCE
#define DRZ__EM  DRZ_EMOJIS_TAPDANCE
#define DRZ__CA  LCTL(KC_LALT)
#define DRZ__CS  LCTL(KC_LSHIFT)
#define DRZ__EU  LCTL(RALT(KC_E))
#define DRZ_MCS  M(DRZ_MACRO_COMMENT_START)
#define DRZ_MCE  M(DRZ_MACRO_COMMENT_END)


/*\ ------------------------------------------------------*/
//  QWERTY KEYMAP ON QWERTY INTL OS !
/*\-------------------------------------------------------*/


#ifdef DRZ_QWERTY_INTL_OS

  //Qwerty single num keys
  #define DRZ___1   KC_1
  #define DRZ___2   KC_2
  #define DRZ___3   KC_3
  #define DRZ___4   KC_4
  #define DRZ___5   KC_5
  #define DRZ___6   KC_6
  #define DRZ___7   KC_7
  #define DRZ___8   KC_8
  #define DRZ___9   KC_9
  #define DRZ___0   KC_0

  //Qwerty single alpha keys
  #define DRZ___Q   KC_Q
  #define DRZ___W   KC_W
  #define DRZ___E   KC_E
  #define DRZ___R   KC_R
  #define DRZ___T   KC_T
  #define DRZ___Y   KC_Y
  #define DRZ___U   KC_U
  #define DRZ___I   KC_I
  #define DRZ___O   KC_O
  #define DRZ___P   KC_P
  #define DRZ___A   KC_A
  #define DRZ___S   KC_S
  #define DRZ___D   KC_D
  #define DRZ___F   KC_F
  #define DRZ___G   KC_G
  #define DRZ___H   KC_H
  #define DRZ___J   KC_J
  #define DRZ___K   KC_K
  #define DRZ___L   KC_L
  #define DRZ___Z   KC_Z
  #define DRZ___X   KC_X
  #define DRZ___C   KC_C
  #define DRZ___V   KC_V
  #define DRZ___B   KC_B
  #define DRZ___N   KC_N
  #define DRZ___M   KC_M

  #define DRZ_MNS KC_MINS
  #define DRZ_PLS KC_PLUS
  #define DRZ_EQU KC_EQL
  #define DRZ_UDS KC_UNDS
  #define DRZ_SLA KC_SLASH
  #define DRZ_DLR KC_DLR
  #define DRZ_SUP KC_LABK       //  > (superior)
  #define DRZ_LES KC_RABK       //  < (inferior)
  #define DRZ_SCL KC_SCLN
  #define DRZ_CLN KC_COLN
  #define DRZ_TIL KC_TILD
  #define DRZ_SBL KC_LBRC
  #define DRZ_SBR KC_RBRC
  #define DRZ_CBL KC_LCBR
  #define DRZ_CBR KC_RCBR
  #define DRZ_PIP KC_PIPE       //  | (pipe)
  #define DRZ_INT KC_QUES       //  ? (interrogation mark)
  #define DRZ_SQT KC_GRV        //  ` (special quote ?)
  #define DRZ_ASL KC_BSLS       //  \ (antislash)
  #define DRZ_AST KC_ASTR
  #define DRZ_EXC KC_EXLM
  #define DRZ_LPR KC_LPRN
  #define DRZ_RPR KC_RPRN
  #define DRZ_APS KC_QUOT       // '
  #define DRZ_QOT KC_DQT        // "
#endif

/*\ ------------------------------------------------------*/
//  QWERTY KEYMAP ON AZERTY OS !
/*\-------------------------------------------------------*/

#ifdef DRZ_AZERTY_FR_OS

  #include "keymap_french.h"

  //Azerty's FR single num keys
  #define DRZ___1   FR_1
  #define DRZ___2   FR_2
  #define DRZ___3   FR_3
  #define DRZ___4   FR_4
  #define DRZ___5   FR_5
  #define DRZ___6   FR_6
  #define DRZ___7   FR_7
  #define DRZ___8   FR_8
  #define DRZ___9   FR_9
  #define DRZ___0   FR_0

  //Azerty's FR single alpha keys
  #define DRZ___Q   FR_Q
  #define DRZ___W   FR_W
  #define DRZ___E   FR_E
  #define DRZ___R   FR_R
  #define DRZ___T   FR_T
  #define DRZ___Y   FR_Y
  #define DRZ___U   FR_U
  #define DRZ___I   FR_I
  #define DRZ___O   FR_O
  #define DRZ___P   FR_P
  #define DRZ___A   FR_A
  #define DRZ___S   FR_S
  #define DRZ___D   FR_D
  #define DRZ___F   FR_F
  #define DRZ___G   FR_G
  #define DRZ___H   FR_H
  #define DRZ___J   FR_J
  #define DRZ___K   FR_K
  #define DRZ___L   FR_L
  #define DRZ___Z   FR_Z
  #define DRZ___X   FR_X
  #define DRZ___C   FR_C
  #define DRZ___V   FR_V
  #define DRZ___B   FR_B
  #define DRZ___N   FR_N
  #define DRZ___M   FR_M

  //Azerty's FR single keys
  #define DRZ_SCL   FR_SCLN       //  ,
  #define DRZ_CLN   FR_COLN       //  ;
  #define DRZ_APS   FR_APOS       //  '
  #define DRZ_QOT   FR_QUOT       //  "
  #define DRZ_UDS   FR_UNDS       //  _
  #define DRZ_EQU   FR_EQUA       //  =
  #define DRZ_LPR   FR_LPAR       //  (
  #define DRZ_RPR   FR_RPAR       //  )
  #define DRZ_EXC   FR_EXCL       //  !
  #define DRZ_SLA   FR_SLSH       //  /
  #define DRZ_AST   FR_AST        //  *
  #define DRZ_MNS   FR_PLUS       //  +
  #define DRZ_PLS   FR_MINS       //  -
  #define DRZ_DLR   FR_DLR        //  $
  #define DRZ_LES   FR_LESS       //  <

  //Azerty's FR combined key
  #define DRZ_TIL   RALT(FR_EACU) //  ~ (tilde)
  #define DRZ_SBL   RALT(FR_LPAR) //  [ (square bracket left)
  #define DRZ_SBR   RALT(FR_RPAR) //  ] (square bracket right)
  #define DRZ_CBL   RALT(FR_APOS) //  { (curly bracket left)
  #define DRZ_CBR   RALT(FR_EQUA) //  } (curly bracket right)
  #define DRZ_PIP   RALT(KC_6)    //  | (pipe)
  #define DRZ_INT   LSFT(FR_COMM) //  ? (interrogation mark)
  #define DRZ_SQT   RALT(FR_EGRV) //  ` (special quote ?)
  #define DRZ_ASL   LALT(FR_UNDS) //  \ (antislash)
  #define DRZ_SUP   LSFT(FR_LESS) //  > (superior)


#endif

#endif
