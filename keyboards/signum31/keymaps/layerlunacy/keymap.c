#include "kb.h"

/*#define _BASE 0
#define _SFT 1
#define _CALC 2
#define _CALC_SFT 3
#define _PCNT 4
#define _PNCT_SFT 5
#define _LANG 6
#define _LANG_SFT 7
#define _GAME 8
#define _MOUSE 9
*/

enum unicode_name {
ACUTE,
AE,
BITCOIN,
BULLET,
CENT,
CLUBS,
COPYR,
CROSS,
CURRENCY,
DEGREE,
DIAMS,
DIVISION,
DOTS,
DQT1,
DQT2,
DQT3,
DQT4,
DQT5,
EMDASH,
EURO,
HEARTS,
INV_EXCL,
INV_QST,
MICRO,
MINUTE,
NO,
N_TILDE,
OE,
OHM,
PERMIL,
POUND,
REGTM,
ROOT,
SECOND,
SECTION,
SNEK,
SPADES,
SQT1,
SQT2,
SQT3,
SQT4,
SQT5,
SUP1,
SUP2,
SUP3,
SUP_A,
SUP_MIN,
SUP_O,
SZ,
TMARK,
UE,
YEN,
YES,
ae,
n_tilde,
oe,
sz,
ue
};

const uint32_t PROGMEM unicode_map[] = {
	[ACUTE] = 0x00b4,  // ´
	[AE] = 0x00c4,  // Ä
	[BITCOIN] = 0x20bf,  // ₿
	[BULLET] = 0x2022,  // •
	[CENT] = 0x00a2,  // ¢
	[CLUBS] = 0x2663,  // ♣
	[COPYR] = 0x00a9,  // ©
	[CROSS] = 0x2020,  // †
	[CURRENCY] = 0x00a4,  // ¤
	[DEGREE] = 0x00b0,  // °
	[DIAMS] = 0x2666,  // ♦
	[DIVISION] = 0x00f7,  // ÷
	[DOTS] = 0x2026,  // …
	[DQT1] = 0x00ab,  // «
	[DQT2] = 0x201e,  // „
	[DQT3] = 0x201c,  // “
	[DQT4] = 0x201d,  // ”
	[DQT5] = 0x00bb,  // »
	[EMDASH] = 0x2014,  // —
	[EURO] = 0x20ac,  // €
	[HEARTS] = 0x2665,  // ♥
	[INV_EXCL] = 0x00a1,  // ¡
	[INV_QST] = 0x00bf,  // ¿
	[MICRO] = 0x00b5,  // µ
	[MINUTE] = 0x02b9,  // ʹ
	[NO] = 0x2717,  // ✗
	[N_TILDE] = 0x00d1,  // Ñ
	[OE] = 0x00d6,  // Ö
	[OHM] = 0x2126,  // Ω
	[PERMIL] = 0x2030,  // ‰
	[POUND] = 0x00a3,  // £
	[REGTM] = 0x00ae,  // ®
	[ROOT] = 0x221a,  // √
	[SECOND] = 0x02ba,  // ʺ
	[SECTION] = 0x00a7,  // §
	[SNEK] = 0x1F40D,  // 🐍
	[SPADES] = 0x2660,  // ♠
	[SQT1] = 0x2039,  // ‹
	[SQT2] = 0x201a,  // ‚
	[SQT3] = 0x2018,  // ‘
	[SQT4] = 0x2019,  // ’
	[SQT5] = 0x203a,  // ›
	[SUP1] = 0x00b9,  // ¹
	[SUP2] = 0x00b2,  // ²
	[SUP3] = 0x00b3,  // ³
	[SUP_A] = 0x00aa,  // ª
	[SUP_MIN] = 0x207b,  // ⁻
	[SUP_O] = 0x00ba,  // º
	[SZ] = 0x1e9e,  // ẞ
	[TMARK] = 0x2122,  // ™
	[UE] = 0x00dc,  // Ü
	[YEN] = 0x00a5,  // ¥
	[YES] = 0x2713,  // ✓
	[ae] = 0x00e4,  // ä
	[n_tilde] = 0x00f1,  // ñ
	[oe] = 0x00f6,  // ö
	[sz] = 0x00df,  // ß
	[ue] = 0x00fc  // ü
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   !   |   @   |   #   |   $   |   ?   |               |   {   |   (   |   ´   |   )   |   }   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   q   |   w   |   e   |   r   |   t   |               |   z   |   u   |   i   |   o   |   p   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   a   |   s   |   d   |   f   |   g   |               |   h   |   j   |   k   |   l   |   '   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |   y   |   x   |   c   |   v   |   b   |               |   n   |   m   |   ,   |   .   |   -   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  L6   |  L4   | Ctrl  |  Alt  | Space |  L8   |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_9), X(ACUTE), S(KC_0), S(KC_RBRC), KC_DEL,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_U, KC_I, KC_O, KC_P, KC_ENT,
		MO(1), KC_A, KC_S, KC_D, KC_F, KC_J, KC_K, KC_L, KC_QUOT, MO(1),
		KC_LGUI, KC_Y, KC_X, KC_C, KC_V, KC_M, KC_COMM, KC_DOT, KC_MINS, KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, MO(6), MO(8), XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,
		MO(4), KC_B, KC_G, KC_T, S(KC_SLSH), S(KC_LBRC), KC_Z, KC_H, KC_N, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ¡   |   &   |   /   |   %   |   ¿   |               |   <   |   [   |   _   |   ]   |   >   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * | S_Tab |   Q   |   W   |   E   |   R   |   T   |               |   Z   |   U   |   I   |   O   |   P   |S_Enter|
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   A   |   S   |   D   |   F   |   G   |               |   H   |   J   |   K   |   L   |   "   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T1   |   Y   |   X   |   C   |   V   |   B   |               |   N   |   M   |   ;   |   :   |   =   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  L6   |  L4   | Ctrl  |  Alt  | Space |  L8   |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, X(INV_EXCL), S(KC_7), KC_SLSH, S(KC_5), KC_LBRC, S(KC_MINS), KC_RBRC, S(KC_DOT), KC_DEL,
		S(KC_TAB), S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_U), S(KC_I), S(KC_O), S(KC_P), S(KC_ENT),
		MO(1), S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_J), S(KC_K), S(KC_L), S(KC_QUOT), MO(1),
		TG(1), S(KC_Y), S(KC_X), S(KC_C), S(KC_V), S(KC_M), KC_SCLN, S(KC_SCLN), KC_EQL, KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, MO(6), MO(8), XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,
		MO(4), S(KC_B), S(KC_G), S(KC_T), X(INV_QST), S(KC_COMM), S(KC_Z), S(KC_H), S(KC_N), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   !   |   @   |   #   |   $   |   ?   |               |   {   |   (   |   ´   |   )   |   }   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   x   |   v   |   l   |   c   |   w   |               |   k   |   h   |   g   |   f   |   q   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L3   |   u   |   i   |   a   |   e   |   o   |               |   s   |   n   |   r   |   t   |   d   |  L3   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |   '   |   j   |   y   |   p   |   z   |               |   b   |   m   |   ,   |   .   |   -   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  L6   |  L4   | Ctrl  |  Alt  | Space |  L8   |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_9), X(ACUTE), S(KC_0), S(KC_RBRC), KC_DEL,
		KC_TAB, KC_X, KC_V, KC_L, KC_C, KC_H, KC_G, KC_F, KC_Q, KC_ENT,
		MO(3), KC_U, KC_I, KC_A, KC_E, KC_N, KC_R, KC_T, KC_D, MO(3),
		KC_LGUI, KC_QUOT, KC_J, KC_Y, KC_P, KC_M, KC_COMM, KC_DOT, KC_MINS, KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, MO(6), MO(8), XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,
		MO(4), KC_Z, KC_O, KC_W, S(KC_SLSH), S(KC_LBRC), KC_K, KC_S, KC_B, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ¡   |   &   |   /   |   %   |   ¿   |               |   <   |   [   |   _   |   ]   |   >   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * | S_Tab |   X   |   V   |   L   |   C   |   W   |               |   K   |   H   |   G   |   F   |   Q   |S_Enter|
 * -------------------------------------------------               -------------------------------------------------
 * |  L3   |   U   |   I   |   A   |   E   |   O   |               |   S   |   N   |   R   |   T   |   D   |  L3   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T3   |   "   |   J   |   Y   |   P   |   Z   |               |   B   |   M   |   ;   |   :   |   =   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  L6   |  L4   | Ctrl  |  Alt  | Space |  L8   |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, X(INV_EXCL), S(KC_7), KC_SLSH, S(KC_5), KC_LBRC, S(KC_MINS), KC_RBRC, S(KC_DOT), KC_DEL,
		S(KC_TAB), S(KC_X), S(KC_V), S(KC_L), S(KC_C), S(KC_H), S(KC_G), S(KC_F), S(KC_Q), S(KC_ENT),
		MO(3), S(KC_U), S(KC_I), S(KC_A), S(KC_E), S(KC_N), S(KC_R), S(KC_T), S(KC_D), MO(3),
		TG(3), S(KC_QUOT), S(KC_J), S(KC_Y), S(KC_P), S(KC_M), KC_SCLN, S(KC_SCLN), KC_EQL, KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, MO(6), MO(8), XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,
		MO(4), S(KC_Z), S(KC_O), S(KC_W), X(INV_QST), S(KC_COMM), S(KC_K), S(KC_S), S(KC_B), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ¹   |   ²   |   ³   |   ⁻   |   √   |               |   ✓   |   =   |   %   |   ^   |   ✗   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ¤   |   :   |   °   |   ʹ   |   ʺ   |               |   *   |   7   |   8   |   9   |   /   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ¢   |   ¥   |   £   |   €   |   $   |               |   +   |   4   |   5   |   6   |   -   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T4   |   ÷   |   µ   |   Ω   |   ₿   |   §   |               |   (   |   1   |   2   |   3   |   )   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  XXX  |  L4   | Ctrl  |   .   |   0   |   ,   |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, X(SUP1), X(SUP2), X(SUP3), X(SUP_MIN), KC_EQL, S(KC_5), S(KC_6), X(NO), KC_DEL,
		KC_TAB, X(CURRENCY), S(KC_SCLN), X(DEGREE), X(MINUTE), KC_7, KC_8, KC_9, KC_SLSH, KC_ENT,
		MO(1), X(CENT), X(YEN), X(POUND), X(EURO), KC_4, KC_5, KC_6, KC_MINS, MO(1),
		TG(4), X(DIVISION), X(MICRO), X(OHM), X(BITCOIN), KC_1, KC_2, KC_3, S(KC_0), KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, XXXXXXX, XXXXXXX, KC_DOT, XXXXXXX,
		MO(4), X(SECTION), S(KC_4), X(SECOND), X(ROOT), X(YES), S(KC_8), S(KC_EQL), S(KC_9), KC_0),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  💥   |  💥   |  💥   |  💥   |  💥   |               |  💥   |  💥   |  💥   |  💥   |  💥   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |  F1   |  F2   |  F3   |  F4   | altF4 |               | Led + | Led 0 | Led - | Led ~ |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |  F5   |  F6   |  F7   |  F8   |  XXX  |               | Vol + | Vol 0 | Vol - | Mic 0 |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T5   |  F9   |  F10  |  F11  |  F12  |  XXX  |               |  |<<  |play/ps|  >>|  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  XXX  |  L4   | Ctrl  |  Alt  | Space |  XXX  |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, KC_DEL,
		KC_TAB, KC_F1, KC_F2, KC_F3, KC_F4, BL_TOGG, BL_DEC, BL_BRTG, XXXXXXX, KC_ENT,
		MO(1), KC_F5, KC_F6, KC_F7, KC_F8, KC_MUTE, KC_VOLD, LCTL(KC_M), XXXXXXX, MO(1),
		TG(5), KC_F9, KC_F10, KC_F11, KC_F12, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,
		MO(4), XXXXXXX, XXXXXXX, LALT(KC_F4), FAIL, FAIL, BL_INC, KC_VOLU, KC_MPRV, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |   |   |  XXX  |  XXX  |               |  XXX  |  XXX  |   :   |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   !   |   @   |   #   |   $   |   ?   |               |   {   |   (   |   ,   |   )   |   }   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   '   |   *   |   \   |   "   |   =   |               |   +   |   .   |   _   |   ;   |   -   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T6   |   ~   |   &   |   /   |   %   |   ^   |               |   <   |   [   |   §   |   ]   |   >   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  L6   |  XXX  | Ctrl  |  Alt  | Space |  XXX  |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, S(KC_BSLS), XXXXXXX, XXXXXXX, S(KC_SCLN), XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_9), KC_COMM, S(KC_0), S(KC_RBRC), KC_ENT,
		MO(1), KC_QUOT, S(KC_8), KC_BSLS, S(KC_QUOT), KC_DOT, S(KC_MINS), KC_SCLN, KC_MINS, MO(1),
		TG(6), S(KC_GRV), S(KC_7), KC_SLSH, S(KC_5), KC_LBRC, X(SECTION), KC_RBRC, S(KC_DOT), KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, MO(6), XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,
		XXXXXXX, S(KC_6), KC_EQL, S(KC_SLSH), XXXXXXX, XXXXXXX, S(KC_LBRC), S(KC_EQL), S(KC_COMM), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ‹   |   ‚   |   ‘   |   ’   |   ›   |               |Insert |Scr Lck|Pr Scr | Pause |C+A+Del|  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ª   |   º   |   ™   |   ©   |   ®   |               | Pg Up | Home  |^ Arrow|  End  |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   …   |   †   |   •   |   —   |   ‰   |               |Pg Down|< Arrow|v Arrow|> Arrow| Menu  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T7   |   «   |   „   |   “   |   ”   |   »   |               |  💥   |  💥   |  💥   |  💥   |  💥   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  L6   |  XXX  | Ctrl  |  Alt  | Space |  XXX  |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, X(SQT1), X(SQT2), X(SQT3), X(SQT4), KC_SLCK, KC_PSCR, KC_BRK, LCTL(LALT(KC_DEL)), KC_DEL,
		KC_TAB, X(SUP_A), X(SUP_O), X(TMARK), X(COPYR), KC_HOME, KC_UP, KC_END, XXXXXXX, KC_ENT,
		MO(1), X(DOTS), X(CROSS), X(BULLET), X(EMDASH), KC_LEFT, KC_DOWN, KC_RIGHT, KC_MENU, MO(1),
		TG(7), X(DQT1), X(DQT2), X(DQT3), X(DQT4), FAIL, FAIL, FAIL, FAIL, KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, MO(6), XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,
		XXXXXXX, X(DQT5), X(PERMIL), X(REGTM), X(SQT5), KC_INS, KC_PGUP, KC_PGDN, FAIL, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |Compose|  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ü   |   ö   |   ä   |  XXX  |  XXX  |               |   ß   |   ñ   |  XXX  |  XXX  |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T8   |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  XXX  |  XXX  | Ctrl  |  Alt  | Space |  L8   |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_ALGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), X(ue), X(oe), X(ae), XXXXXXX, X(n_tilde), XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		TG(8), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, MO(8), XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(sz), XXXXXXX, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |Compose|  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   Ü   |   Ö   |   Ä   |  XXX  |  XXX  |               |   ẞ   |   Ñ   |  XXX  |  XXX  |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T9   |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  XXX  |  XXX  | Ctrl  |  Alt  | Space |  L8   |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_ALGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), X(UE), X(OE), X(AE), XXXXXXX, X(N_TILDE), XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		TG(9), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, MO(8), XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(SZ), XXXXXXX, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   1   |   2   |   3   |   4   |   5   |               |   6   |   7   |   8   |   9   |   0   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   q   |   w   |   e   |   r   |   t   |               |   y   |   u   |   i   |   o   |   p   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * | Caps  |   a   |   s   |   d   |   f   |   g   |               |   h   |   j   |   k   |   l   |^ Arrow| Shift |
 * -------------------------------------------------               -------------------------------------------------
 * | Shift |   z   |   x   |   c   |   v   |   b   |               |   n   |   m   |  💥   |< Arrow|v Arrow|> Arrow|
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  Alt  | Space | Ctrl  | Enter |RShift | Ctrl  |
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_7, KC_8, KC_9, KC_0, KC_DEL,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_U, KC_I, KC_O, KC_P, KC_ENT,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_J, KC_K, KC_L, KC_UP, KC_LSFT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_M, FAIL, KC_LEFT, KC_DOWN, KC_RIGHT,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, KC_LALT, KC_LCTRL, XXXXXXX, XXXXXXX, KC_ENT, XXXXXXX,
		KC_SPC, KC_B, KC_G, KC_T, KC_5, KC_6, KC_Y, KC_H, KC_N, KC_RSFT),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  | Enter |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  | Menu  | < Tab |^ Arrow| > Tab | Pg Up |               |Pr Scr |Mouse 1|^ Mouse|Mouse 2|Scr Lck| Enter |
 * -------------------------------------------------               -------------------------------------------------
 * | Shift |BSpace |< Arrow|v Arrow|> Arrow|Pg Down|               |  XXX  |< Mouse|v Mouse|> Mouse|  XXX  | Shift |
 * -------------------------------------------------               -------------------------------------------------
 * |  💥   | Undo  |  Cut  | Copy  | Paste |  Del  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *                                 |  Alt  | Space | Ctrl  |Mouse 3|Mouse 1|Mouse 2|
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, KC_MENU, LCTL(S(KC_TAB)), KC_UP, LCTL(KC_TAB), KC_BTN1, KC_MS_U, KC_BTN2, KC_SLCK, KC_ENT,
		KC_LSFT, KC_BSPC, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, KC_LSFT,
		FAIL, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		XXXXXXX, KC_LCTRL, XXXXXXX, XXXXXXX, KC_LALT, KC_BTN2, XXXXXXX, XXXXXXX, KC_BTN3, XXXXXXX,
		KC_SPC, KC_DEL, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX, KC_BTN1)
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
/*	keyevent_t event = record->event;
	switch (id) {}
*/	return MACRO_NONE;
}

void matrix_init_user(void) {
	set_unicode_input_mode(UC_WINC);
}

void matrix_scan_user(void) {}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {
	if (usb_led & (1 << USB_LED_NUM_LOCK)) {} else {}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {} else {}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		DDRB |= (1 << 6); PORTB &= ~(1 << 6);
	} else {
		DDRB &= ~(1 << 6); PORTB &= ~(1 << 6);
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {} else {}

	if (usb_led & (1 << USB_LED_KANA)) {} else {}
}
