#pragma once
#include "csc027.h"

#define MC_LCAD LCA(KC_DEL)     // Control-Alt-Delete
#define MC_RSFE RSFT_T(KC_ENT)  // Right Shift on hold, Enter on tap
#define MC_LSEC LSFT_T(KC_ESC)  // Left Shift on hold, Escape on tap

#define ________________ KC_TRNS

/* QWERTY Layer
 *
 *  The basic layer of this keymap is a QWERTY layer.
 *
 *  - Modifier keys more closely resemble a standard keyboard's layout.
 *  - There is a "Nxt L" function that cycles through the QWERTY and
 *    game layers.  This has been implemented by hard coding the jump to the
 *    next layer in each of the layers using the TO() macro.  Currently, the
 *    "Nxt L" function skips over the momentary layers (i.e., Mouse, Git,
 *    Lower, Raise, and Convenience layers).
 *  - There is a "Rst L" function that resets the current layer to the
 *    QWERTY layer.
 *  - The "Git" one shot function goes to the macro layer which has Git
 *    commands implemented.
 *  - The "Convc" momentary function goes to the Convenience layer which has a
 *    tenkey.  Note: The tenkey will operate using the secondary functions if
 *    the Number Lock is not enabled (e.g., Left and Right instead of 4 and
 *    6).
 *  - The Right Shift key also doubles as an Enter key if it is tapped rather
 *    than held.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * | Tab |  Q  |  W  |  E  |  R  |  T  |  |  Y  |  U  |  I  |  O  |  P  |BkSpc|
 * |-----------------------------------|  |-----------------------------------|
 * | Esc |  A  |  S  |  D  |  F  |  G  |  |  H  |  J  |  K  |  L  |  ;  |  '  |
 * |-----------------------------------|  |-----------------------------------|
 * |Shift|  Z  |  X  |  C  |  V  |  B  |  |  N  |  M  |  ,  |  .  |  /  |Sf/En|
 * |-----------------------------------|  |-----------------------------------|
 * |Cntrl|Super| Alt |Convc|Lower|Space|  |Space|Raise|  \  | Git |Nxt L|Rst L|
 * `-----------------------------------'  `-----------------------------------'
 */

#define _____________________QWERTY_L1_____________________  KC_TAB,   KC_Q,     KC_W,     KC_E,      KC_R,     KC_T
#define _____________________QWERTY_L2_____________________  KC_ESC,   KC_A,     KC_S,     KC_D,      KC_F,     KC_G
#define _____________________QWERTY_L3_____________________  KC_LSFT,  KC_Z,     KC_X,     KC_C,      KC_V,     KC_B
#define _____________________QWERTY_L4_____________________  KC_LCTL,  KC_LGUI,  KC_LALT,  MO(_CN),   LOWER,    KC_SPC

#define _____________________QWERTY_R1_____________________  KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,     KC_BSPC
#define _____________________QWERTY_R2_____________________  KC_H,     KC_J,     KC_K,     KC_L,      KC_SCLN,  KC_QUOT
#define _____________________QWERTY_R3_____________________  KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,  MC_RSFE
#define _____________________QWERTY_R4_____________________  KC_SPC,   RAISE,    KC_BSLS,  OSL(_GT),  TO(_GW),  XXXXXXX

/* Raise Layer
 *
 *  The Raise layer accommodates the Home, End, Page Up, and Page Down keys
 *  in what would be the Vim arrow keys positions.  This is done as opposed
 *  to using C-D, C-U, 0, $, and ^, because it would require a separate layer.
 *
 *  - The top row has the shifted versions of the number row, rather than the
 *    numbers themselves.  This is a change to have a mnemonic where shifted
 *    elements are on the Raise layer.  This also makes it easy to use some of
 *    Vim style movement controls (e.g. $, %), but makes it harder for others
 *    (e.g. ^, (, )). Consider swapping the number row with the shifted number
 *    row if you do not care about the mnemonic.
 *  - The Left Brace, Right Brace, Underscore, and Plus keys have been moved
 *    from the right side to the left side.  This will take some getting used
 *    to, as these keys are normally on the right side of the keyboard.  An
 *    alternative would be to keep the keys on the right hand side just under
 *    the Parentheses.  This would prevent the use of Vim arrow keys however.
 *  - The F keys have been laid across the bottom in the Raise layer, rather
 *    than the Lower layer to allow easy access to the Alt-F4 chord for
 *    Windows.  When the F keys were put in the Lower layer, it made it hard
 *    to use this chord, as the Lower key, the Alt key, and the F4 key were
 *    all right next to each other.
 *  - A Delete key has been added in this layer to allow easy access to the
 *    Control-Alt-Delete login chord for Windows.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |  ~  |  !  |  @  |  #  |  $  |  %  |  |  ^  |  &  |  *  |  (  |  )  | Del |
 * |-----------------------------------|  |-----------------------------------|
 * |     |  _  |  +  |  {  |  }  | Caps|  | Home| PgDn| PgUp| End |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |  F1 |  F2 |  F3 |  F4 |  F5 |  |  F6 |  F7 |  F8 |  F9 | F10 |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * `-----------------------------------'  `-----------------------------------'
 */

#define ______________________RAISE_L1_____________________  KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,   KC_DLR,   KC_PERC
#define ______________________RAISE_L2_____________________  _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,   KC_RCBR,  KC_CAPS
#define ______________________RAISE_L3_____________________  _______,  KC_F1,    KC_F2,    KC_F3,     KC_F4,    KC_F5
#define ______________________RAISE_L4_____________________  _______,  _______,  _______,  _______,   _______,  _______

#define ______________________RAISE_R1_____________________  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,   KC_RPRN,  KC_DELT
#define ______________________RAISE_R2_____________________  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,    XXXXXXX,  XXXXXXX
#define ______________________RAISE_R3_____________________  KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   _______
#define ______________________RAISE_R4_____________________  _______,  _______,  _______,  _______,   XXXXXXX,  XXXXXXX

/* Lower Layer
 *
 *  The lower layout scheme accommodates the Vim style arrow keys.
 *
 *  - The arrow keys are in the normal Vim positions.
 *  - The Left Square Bracket, Right Square Bracket, Minus, and Equal keys
 *    have been moved from the right side to the left side.  This will take
 *    some getting used to, as it is on the left rather than the right.
 *  - A Delete key has been added in this layer to allow easy access to the
 *    Control-Alt-Delete login chord for Windows.
 *  - The remaining F keys are in this layer.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |  `  |  1  |  2  |  3  |  4  |  5  |  |  6  |  7  |  8  |  9  |  0  | Del |
 * |-----------------------------------|  |-----------------------------------|
 * |     |  -  |  =  |  [  |  ]  |     |  | Left| Down|  Up |Right|     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     | F11 | F12 |     |     |     |  |     |     |     |     |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * `-----------------------------------'  `-----------------------------------'
 */

#define ______________________LOWER_L1_____________________  KC_GRV,   KC_1,     KC_2,     KC_3,      KC_4,     KC_5
#define ______________________LOWER_L2_____________________  _______,  KC_MINS,  KC_EQL,   KC_LBRC,   KC_RBRC,  XXXXXXX
#define ______________________LOWER_L3_____________________  _______,  KC_F11,   KC_F12,   XXXXXXX,   XXXXXXX,  XXXXXXX
#define ______________________LOWER_L4_____________________  _______,  _______,  _______,  _______,   _______,  _______

#define ______________________LOWER_R1_____________________  KC_6,     KC_7,     KC_8,     KC_9,      KC_0,     KC_DELT
#define ______________________LOWER_R2_____________________  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,   XXXXXXX,  XXXXXXX
#define ______________________LOWER_R3_____________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  _______
#define ______________________LOWER_R4_____________________  _______,  _______,  _______,  _______,   XXXXXXX,  XXXXXXX


/* MIT Layout (Mouse)
 *
 *  The mouse layer adds keys to use the keyboard like a mouse.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |Ms-Lc|Ms-Rc|     |  | Ms-L| Ms-D| Ms-U| Ms-R|     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * `-----------------------------------'  `-----------------------------------'
 */

#define ______________________MOUSE_L1_____________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX
#define ______________________MOUSE_L2_____________________  _______,  XXXXXXX,  XXXXXXX,  KC_BTN1,   KC_BTN2,  XXXXXXX
#define ______________________MOUSE_L3_____________________  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX
#define ______________________MOUSE_L4_____________________  _______,  _______,  _______,  _______,   _______,  _______

#define ______________________MOUSE_R1_____________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX
#define ______________________MOUSE_R2_____________________  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,   XXXXXXX,  XXXXXXX
#define ______________________MOUSE_R3_____________________  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  _______
#define ______________________MOUSE_R4_____________________  _______,  _______,  _______,  _______,   XXXXXXX,  XXXXXXX

/* MIT Layout (Git)
 *
 *  The macro layer that has common git commands.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |     |Chery| Show|Rebas|Reset| Tag |  |     | Pull| Init|Rmote| Push|     |
 * |-----------------------------------|  |-----------------------------------|
 * |     | Add |Sttus| Diff|Fetch| Grep|  |Stash|     |ChkOt| Log |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |Comit| Move|Brnch|  |     |Merge|     |     |     |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |     |     |     |     |     |
 * `-----------------------------------'  `-----------------------------------'
 */

#define _______________________GIT_L1______________________  XXXXXXX,  GIT_CHR,  GIT_SHW,  GIT_RBS,   GIT_RST,  GIT_TAG
#define _______________________GIT_L2______________________  _______,  GIT_ADD,  GIT_STS,  GIT_DIF,   GIT_FTC,  GIT_GRP
#define _______________________GIT_L3______________________  _______,  XXXXXXX,  XXXXXXX,  GIT_CMT,   GIT_MOV,  GIT_BRC
#define _______________________GIT_L4______________________  _______,  _______,  _______,  _______,   _______,  _______

#define _______________________GIT_R1______________________  XXXXXXX,  GIT_PUL,  GIT_INT,  GIT_RMT,   GIT_PSH,  XXXXXXX
#define _______________________GIT_R2______________________  GIT_STH,  XXXXXXX,  GIT_CHK,  GIT_LOG,   XXXXXXX,  XXXXXXX
#define _______________________GIT_R3______________________  XXXXXXX,  GIT_MRG,  XXXXXXX,  XXXXXXX,   XXXXXXX,  _______
#define _______________________GIT_R4______________________  _______,  _______,  _______,  _______,   XXXXXXX,  XXXXXXX


/* MIT Layout (Convenience)
 *
 *  The Convenience layer adds a tenkey and miscellaneous chords to the keyboard.
 *  The lack of a fifth row means that some of the tenkey's functions need to be
 *  moved to the left of tenkey from the top.
 *
 *  - The Number Lock key is physically in the same spot as the Caps Lock key
 *    in the raise layer.
 *  - There is also a Backspace Key for convenience.
 *  - There is a convenience macro to type the Control-Alt-Delete login chord for Windows.
 *  - There is a convenience macro to Minimize Remote Desktop within Remote Desktop
 *    in Windows.
 *  - There is a convenience macro to cycle through programs in Windows.
 *  - There is a convenience macro to go to the previous program in Windows.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * |     |     |Insrt|ScrLk|PrtSc|     |  |  *  |  7  |  8  |  9  |  -  |BkSpc|
 * |-----------------------------------|  |-----------------------------------|
 * |     |     | App | LCAD|MRDP7|NmLck|  |  /  |  4  |  5  |  6  |  +  |     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     | ATRD|MRDP8|     |  |     |  1  |  2  |  3  |Enter|     |
 * |-----------------------------------|  |-----------------------------------|
 * |     |     |     |     |     |     |  |     |  0  |  0  |  .  |     |     |
 * `-----------------------------------'  `-----------------------------------'
 */

#define ___________________CONVENIENCE_L1__________________  XXXXXXX,  XXXXXXX,  KC_INS,   KC_SLCK,   KC_PSCR,  XXXXXXX
#define ___________________CONVENIENCE_L2__________________  _______,  XXXXXXX,  KC_APP,   MC_LCAD,   MC_MRD7,  KC_NLCK
#define ___________________CONVENIENCE_L3__________________  _______,  XXXXXXX,  XXXXXXX,  MC_ATRD,   MC_MRD8,  XXXXXXX
#define ___________________CONVENIENCE_L4__________________  _______,  _______,  _______,  _______,   _______,  _______

#define ___________________CONVENIENCE_R1__________________  KC_PAST,  KC_P7,    KC_P8,    KC_P9,     KC_PMNS,  KC_BSPC
#define ___________________CONVENIENCE_R2__________________  KC_PSLS,  KC_P4,    KC_P5,    KC_P6,     KC_PPLS,  XXXXXXX
#define ___________________CONVENIENCE_R3__________________  XXXXXXX,  KC_P1,    KC_P2,    KC_P3,     KC_PENT,  _______
#define ___________________CONVENIENCE_R4__________________  _______,  KC_P0,    KC_P0,    KC_PDOT,   XXXXXXX,  XXXXXXX
