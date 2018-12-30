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

enum my_keycodes {
  GREEK = SAFE_RANGE,
  SYMBOL,
	MATH,
	GAME,
	MOUSE
};

enum unicode_name {
ACUTE,
AE,
ALPHA,
BETA,
BITCOIN,
BULLET,
CENT,
CHI,
CLUBS,
COPYR,
CROSS,
CURRENCY,
DEGREE,
DELTA,
DIAMS,
DIGAMMA,
DIVISION,
DOTS,
DQT1,
DQT2,
DQT3,
DQT4,
DQT5,
EMDASH,
EPSILON,
ETA,
EURO,
GAMMA,
HEARTS,
HETA,
INV_EXCL,
INV_QST,
IOTA,
KAPPA,
KOPPA,
LAMBDA,
MICRO,
MINUTE,
MY,
NO,
NY,
N_TILDE,
OE,
OHM,
OMEGA,
OMIKRON,
PERMIL,
PHI,
PI,
POUND,
PSI,
REGTM,
RHO,
ROOT,
SAMPI,
SAN,
SCHO,
SECOND,
SECTION,
SIGMA,
SNEK,
SPADES,
SQT1,
SQT2,
SQT3,
SQT4,
SQT5,
STIGMA,
SUP1,
SUP2,
SUP3,
SUP_A,
SUP_MIN,
SUP_O,
SZ,
TAU,
THETA,
TMARK,
UE,
XI,
YEN,
YES,
YPSI2,
YPSILON,
ZETA,
ae,
alpha,
beta,
beta2,
chi,
delta,
digamma,
epsi2,
epsilon,
eta,
gamma,
heta,
iota,
kappa,
kappa2,
koppa,
lambda,
my,
n_tilde,
ny,
oe,
omega,
omikron,
phi,
phi2,
pi,
pi2,
psi,
rho,
rho2,
sampi,
san,
scho,
sigma,
sigma2,
sigma3,
stigma,
sz,
tau,
theta,
theta2,
ue,
xi,
ypsilon,
zeta
};

const uint32_t PROGMEM unicode_map[] = {
	[ACUTE] = 0x00b4,  // ´
	[AE] = 0x00c4,  // Ä
	[ALPHA] = 0x0391,  // Α
	[BETA] = 0x0392,  // Β
	[BITCOIN] = 0x20bf,  // ₿
	[BULLET] = 0x2022,  // •
	[CENT] = 0x00a2,  // ¢
	[CHI] = 0x03a7,  // Χ
	[CLUBS] = 0x2663,  // ♣
	[COPYR] = 0x00a9,  // ©
	[CROSS] = 0x2020,  // †
	[CURRENCY] = 0x00a4,  // ¤
	[DEGREE] = 0x00b0,  // °
	[DELTA] = 0x0394,  // Δ
	[DIAMS] = 0x2666,  // ♦
	[DIGAMMA] = 0x03dc,  // Ϝ
	[DIVISION] = 0x00f7,  // ÷
	[DOTS] = 0x2026,  // …
	[DQT1] = 0x00bb,  // »
	[DQT2] = 0x201e,  // „
	[DQT3] = 0x201c,  // “
	[DQT4] = 0x201d,  // ”
	[DQT5] = 0x00ab,  // «
	[EMDASH] = 0x2014,  // —
	[EPSILON] = 0x0395,  // Ε
	[ETA] = 0x0397,  // Η
	[EURO] = 0x20ac,  // €
	[GAMMA] = 0x0393,  // Γ
	[HEARTS] = 0x2665,  // ♥
	[HETA] = 0x0370,  // Ͱ
	[INV_EXCL] = 0x00a1,  // ¡
	[INV_QST] = 0x00bf,  // ¿
	[IOTA] = 0x0399,  // Ι
	[KAPPA] = 0x039a,  // Κ
	[KOPPA] = 0x03d8,  // Ϙ
	[LAMBDA] = 0x039b,  // Λ
	[MICRO] = 0x00b5,  // µ
	[MINUTE] = 0x02b9,  // ʹ
	[MY] = 0x039c,  // Μ
	[NO] = 0x2717,  // ✗
	[NY] = 0x039d,  // Ν
	[N_TILDE] = 0x00d1,  // Ñ
	[OE] = 0x00d6,  // Ö
	[OHM] = 0x2126,  // Ω
	[OMEGA] = 0x03a9,  // Ω
	[OMIKRON] = 0x039f,  // Ο
	[PERMIL] = 0x2030,  // ‰
	[PHI] = 0x03a6,  // Φ
	[PI] = 0x03a0,  // Π
	[POUND] = 0x00a3,  // £
	[PSI] = 0x03a8,  // Ψ
	[REGTM] = 0x00ae,  // ®
	[RHO] = 0x03a1,  // Ρ
	[ROOT] = 0x221a,  // √
	[SAMPI] = 0x0372,  // Ͳ
	[SAN] = 0x03fa,  // Ϻ
	[SCHO] = 0x03f7,  // Ϸ
	[SECOND] = 0x02ba,  // ʺ
	[SECTION] = 0x00a7,  // §
	[SIGMA] = 0x03a3,  // Σ
	[SNEK] = 0x1f40d,  // 🐍
	[SPADES] = 0x2660,  // ♠
	[SQT1] = 0x203a,  // ›
	[SQT2] = 0x201a,  // ‚
	[SQT3] = 0x2018,  // ‘
	[SQT4] = 0x2019,  // ’
	[SQT5] = 0x2039,  // ‹
	[STIGMA] = 0x03da,  // Ϛ
	[SUP1] = 0x00b9,  // ¹
	[SUP2] = 0x00b2,  // ²
	[SUP3] = 0x00b3,  // ³
	[SUP_A] = 0x00aa,  // ª
	[SUP_MIN] = 0x207b,  // ⁻
	[SUP_O] = 0x00ba,  // º
	[SZ] = 0x1e9e,  // ẞ
	[TAU] = 0x03a4,  // Τ
	[THETA] = 0x0398,  // Θ
	[TMARK] = 0x2122,  // ™
	[UE] = 0x00dc,  // Ü
	[XI] = 0x039e,  // Ξ
	[YEN] = 0x00a5,  // ¥
	[YES] = 0x2713,  // ✓
	[YPSI2] = 0x03d2,  // ϒ
	[YPSILON] = 0x03a5,  // Υ
	[ZETA] = 0x0396,  // Ζ
	[ae] = 0x00e4,  // ä
	[alpha] = 0x03b1,  // α
	[beta] = 0x03b2,  // β
	[beta2] = 0x03d0,  // ϐ
	[chi] = 0x03c7,  // χ
	[delta] = 0x03b4,  // δ
	[digamma] = 0x03dd,  // ϝ
	[epsi2] = 0x03f5,  // ϵ
	[epsilon] = 0x03b5,  // ε
	[eta] = 0x03b7,  // η
	[gamma] = 0x03b3,  // γ
	[heta] = 0x0371,  // ͱ
	[iota] = 0x03b9,  // ι
	[kappa] = 0x03ba,  // κ
	[kappa2] = 0x03f0,  // ϰ
	[koppa] = 0x03d9,  // ϙ
	[lambda] = 0x03bb,  // λ
	[my] = 0x03bc,  // μ
	[n_tilde] = 0x00f1,  // ñ
	[ny] = 0x03bd,  // ν
	[oe] = 0x00f6,  // ö
	[omega] = 0x03c9,  // ω
	[omikron] = 0x03bf,  // ο
	[phi] = 0x03c6,  // φ
	[phi2] = 0x03d5,  // ϕ
	[pi] = 0x03c0,  // π
	[pi2] = 0x03d6,  // ϖ
	[psi] = 0x03c8,  // ψ
	[rho] = 0x03c1,  // ρ
	[rho2] = 0x03f1,  // ϱ
	[sampi] = 0x0373,  // ͳ
	[san] = 0x03fb,  // ϻ
	[scho] = 0x03f8,  // ϸ
	[sigma] = 0x03c3,  // σ
	[sigma2] = 0x03c2,  // ς
	[sigma3] = 0x03f2,  // ϲ
	[stigma] = 0x03db,  // ϛ
	[sz] = 0x00df,  // ß
	[tau] = 0x03c4,  // τ
	[theta] = 0x03b8,  // θ
	[theta2] = 0x03d1,  // ϑ
	[ue] = 0x00fc,  // ü
	[xi] = 0x03be,  // ξ
	[ypsilon] = 0x03c5,  // υ
	[zeta] = 0x03b6  // ζ
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
 *    NEO            GAME    GREEK |  L6   |  L4   | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_9), X(ACUTE), S(KC_0), S(KC_RBRC), KC_DEL,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_U, KC_I, KC_O, KC_P, KC_ENT,
		MO(1), KC_A, KC_S, KC_D, KC_F, KC_J, KC_K, KC_L, KC_QUOT, MO(1),
		KC_LGUI, KC_Y, KC_X, KC_C, KC_V, KC_M, KC_COMM, KC_DOT, KC_MINS, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
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
 *    NEO            GAME    GREEK |  L6   |  L4   | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, X(INV_EXCL), S(KC_7), KC_SLSH, S(KC_5), KC_LBRC, S(KC_MINS), KC_RBRC, S(KC_DOT), KC_DEL,
		S(KC_TAB), S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_U), S(KC_I), S(KC_O), S(KC_P), S(KC_ENT),
		MO(1), S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_J), S(KC_K), S(KC_L), S(KC_QUOT), MO(1),
		TG(1), S(KC_Y), S(KC_X), S(KC_C), S(KC_V), S(KC_M), KC_SCLN, S(KC_SCLN), KC_EQL, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
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
 *    NEO            GAME    GREEK |  L6   |  L4   | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_9), X(ACUTE), S(KC_0), S(KC_RBRC), KC_DEL,
		KC_TAB, KC_X, KC_V, KC_L, KC_C, KC_H, KC_G, KC_F, KC_Q, KC_ENT,
		MO(3), KC_U, KC_I, KC_A, KC_E, KC_N, KC_R, KC_T, KC_D, MO(3),
		KC_LGUI, KC_QUOT, KC_J, KC_Y, KC_P, KC_M, KC_COMM, KC_DOT, KC_MINS, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
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
 *    NEO            GAME    GREEK |  L6   |  L4   | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, X(INV_EXCL), S(KC_7), KC_SLSH, S(KC_5), KC_LBRC, S(KC_MINS), KC_RBRC, S(KC_DOT), KC_DEL,
		S(KC_TAB), S(KC_X), S(KC_V), S(KC_L), S(KC_C), S(KC_H), S(KC_G), S(KC_F), S(KC_Q), S(KC_ENT),
		MO(3), S(KC_U), S(KC_I), S(KC_A), S(KC_E), S(KC_N), S(KC_R), S(KC_T), S(KC_D), MO(3),
		TG(3), S(KC_QUOT), S(KC_J), S(KC_Y), S(KC_P), S(KC_M), KC_SCLN, S(KC_SCLN), KC_EQL, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
		MO(4), S(KC_Z), S(KC_O), S(KC_W), X(INV_QST), S(KC_COMM), S(KC_K), S(KC_S), S(KC_B), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ¹   |   ²   |   ³   |   ⁻   |   √   |               |   [   |   (   |   %   |   )   |   ]   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ¤   |   :   |   °   |   ʹ   |   ʺ   |               |   *   |   7   |   8   |   9   |   /   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ¢   |   ¥   |   £   |   €   |   $   |               |   +   |   4   |   5   |   6   |   -   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T4   |   ÷   |   µ   |   Ω   |   ₿   |   §   |               |   ^   |   1   |   2   |   3   |   "   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  XXX  |  L4   | Ctrl  |   .   |   0   |   ,   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, X(SUP1), X(SUP2), X(SUP3), X(SUP_MIN), S(KC_9), S(KC_5), S(KC_0), KC_RBRC, KC_DEL,
		KC_TAB, X(CURRENCY), S(KC_SCLN), X(DEGREE), X(MINUTE), KC_7, KC_8, KC_9, KC_SLSH, KC_ENT,
		MO(1), X(CENT), X(YEN), X(POUND), X(EURO), KC_4, KC_5, KC_6, KC_MINS, MO(1),
		TG(4), X(DIVISION), X(MICRO), X(OHM), X(BITCOIN), KC_1, KC_2, KC_3, S(KC_QUOT), KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, KC_COMM, MATH, SYMBOL, KC_DOT, MOUSE,
		MO(4), X(SECTION), S(KC_4), X(SECOND), X(ROOT), KC_LBRC, S(KC_8), S(KC_EQL), S(KC_6), KC_0),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  💥   |  💥   |  💥   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |  F1   |  F2   |  F3   |  F4   | altF4 |               | Led + | Led 0 | Led - | Led ~ |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |  F5   |  F6   |  F7   |  F8   |  XXX  |               | Vol + | Vol 0 | Vol - | Mic 0 |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T5   |  F9   |  F10  |  F11  |  F12  |  XXX  |               |  |<<  |play/ps|  >>|  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  XXX  |  L4   | Ctrl  |  Alt  | Space |  XXX  | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, KC_F1, KC_F2, KC_F3, KC_F4, BL_TOGG, BL_DEC, BL_BRTG, XXXXXXX, KC_ENT,
		MO(1), KC_F5, KC_F6, KC_F7, KC_F8, KC_MUTE, KC_VOLD, LCTL(KC_M), XXXXXXX, MO(1),
		TG(5), KC_F9, KC_F10, KC_F11, KC_F12, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, XXXXXXX, MATH, SYMBOL, KC_LALT, MOUSE,
		MO(4), XXXXXXX, XXXXXXX, LALT(KC_F4), XXXXXXX, XXXXXXX, BL_INC, KC_VOLU, KC_MPRV, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |   |   |  XXX  |  XXX  |               |  XXX  |  XXX  |   :   |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   !   |   @   |   #   |   $   |   ?   |               |   {   |   (   |   ,   |   )   |   }   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   '   |   *   |   \   |   "   |   =   |               |   +   |   .   |   _   |   ;   |   -   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T6   |   ~   |   &   |   /   |   %   |   ^   |               |   <   |   [   |   §   |   ]   |   >   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  XXX  | Ctrl  |  Alt  | Space |  XXX  | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, S(KC_BSLS), XXXXXXX, XXXXXXX, S(KC_SCLN), XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_9), KC_COMM, S(KC_0), S(KC_RBRC), KC_ENT,
		MO(1), KC_QUOT, S(KC_8), KC_BSLS, S(KC_QUOT), KC_DOT, S(KC_MINS), KC_SCLN, KC_MINS, MO(1),
		TG(6), S(KC_GRV), S(KC_7), KC_SLSH, S(KC_5), KC_LBRC, X(SECTION), KC_RBRC, S(KC_DOT), KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, MO(6), XXXXXXX, MATH, SYMBOL, KC_LALT, MOUSE,
		XXXXXXX, S(KC_6), KC_EQL, S(KC_SLSH), XXXXXXX, XXXXXXX, S(KC_LBRC), S(KC_EQL), S(KC_COMM), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ›   |   ‚   |   ‘   |   ’   |   ‹   |               |Insert |Scr Lck|Pr Scr | Pause |C+A+Del|  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ª   |   º   |   ™   |   ©   |   ®   |               | Pg Up | Home  |^ Arrow|  End  |  App  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   …   |   †   |   •   |   —   |   ‰   |               |Pg Down|< Arrow|v Arrow|> Arrow| Menu  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T7   |   »   |   „   |   “   |   ”   |   «   |               |Macro 1|Macro 2|Macro 3|Macro 4|Macro 5|BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  XXX  | Ctrl  |  Alt  | Space |  XXX  | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, X(SQT1), X(SQT2), X(SQT3), X(SQT4), KC_SLCK, KC_PSCR, KC_BRK, LCTL(LALT(KC_DEL)), KC_DEL,
		KC_TAB, X(SUP_A), X(SUP_O), X(TMARK), X(COPYR), KC_HOME, KC_UP, KC_END, KC_APP, KC_ENT,
		MO(1), X(DOTS), X(CROSS), X(BULLET), X(EMDASH), KC_LEFT, KC_DOWN, KC_RIGHT, KC_MENU, MO(1),
		TG(7), X(DQT1), X(DQT2), X(DQT3), X(DQT4), KC_2, KC_3, KC_4, KC_5, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, MO(6), XXXXXXX, MATH, SYMBOL, KC_LALT, MOUSE,
		XXXXXXX, X(DQT5), X(PERMIL), X(REGTM), X(SQT5), KC_INS, KC_PGUP, KC_PGDN, KC_1, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |Compose|  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ü   |   ö   |   ä   |  XXX  |  XXX  |               |   ß   |   ñ   |  XXX  |  XXX  |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T8   |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  XXX  |  XXX  | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_ALGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), X(ue), X(oe), X(ae), XXXXXXX, X(n_tilde), XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		TG(8), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
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
 *    NEO            GAME    GREEK |  XXX  |  XXX  | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_ALGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), X(UE), X(OE), X(AE), XXXXXXX, X(N_TILDE), XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		TG(9), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(SZ), XXXXXXX, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |Compose|  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ü   |   ö   |   ä   |  XXX  |  XXX  |               |   ß   |   ñ   |  XXX  |  XXX  |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T8   |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  XXX  |  XXX  | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_ALGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), X(ue), X(oe), X(ae), XXXXXXX, X(n_tilde), XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		TG(8), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
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
 *    NEO            GAME    GREEK |  XXX  |  XXX  | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_ALGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), X(UE), X(OE), X(AE), XXXXXXX, X(N_TILDE), XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		TG(9), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(SZ), XXXXXXX, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |   ϝ   |   ϛ   |   ͱ   |   ϻ   |               |   ϰ   |   ϙ   |   ͳ   |   ϸ   |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ξ   |   ς   |   λ   |   χ   |   ω   |               |   κ   |   ψ   |   γ   |   φ   |   ϕ   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   υ   |   ι   |   α   |   ε   |   ο   |               |   σ   |   ν   |   ρ   |   τ   |   δ   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |  XXX  |   ϰ   |   η   |   π   |   ζ   |               |   β   |   μ   |   ϱ   |   θ   |   ϑ   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, X(digamma), X(stigma), X(heta), X(koppa), X(sampi), X(scho), XXXXXXX, KC_DEL,
		KC_TAB, X(xi), X(sigma2), X(lambda), X(chi), X(psi), X(gamma), X(phi), X(phi2), KC_ENT,
		MO(1), X(ypsilon), X(iota), X(alpha), X(epsilon), X(ny), X(rho), X(tau), X(delta), MO(1),
		KC_LGUI, XXXXXXX, X(kappa2), X(eta), X(pi), X(my), X(rho2), X(theta), X(theta2), KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), X(zeta), X(omikron), X(omega), X(san), X(kappa2), X(kappa), X(sigma), X(beta), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |   Ϝ   |   Ϛ   |   Ͱ   |   Ϻ   |               |  XXX  |   Ϙ   |   Ͳ   |   Ϸ   |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   Ξ   |  XXX  |   Λ   |   Χ   |   Ω   |               |   Κ   |   Ψ   |   Γ   |   Φ   |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   Υ   |   Ι   |   Α   |   Ε   |   Ο   |               |   Σ   |   Ν   |   Ρ   |   Τ   |   Δ   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |  XXX  |  XXX  |   Η   |   Π   |   Ζ   |               |   Β   |   Μ   |  XXX  |   Θ   |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, X(DIGAMMA), X(STIGMA), X(HETA), X(KOPPA), X(SAMPI), X(SCHO), XXXXXXX, KC_DEL,
		KC_TAB, X(XI), XXXXXXX, X(LAMBDA), X(CHI), X(PSI), X(GAMMA), X(PHI), XXXXXXX, KC_ENT,
		MO(1), X(YPSILON), X(IOTA), X(ALPHA), X(EPSILON), X(NY), X(RHO), X(TAU), X(DELTA), MO(1),
		KC_LGUI, XXXXXXX, XXXXXXX, X(ETA), X(PI), X(MY), XXXXXXX, X(THETA), XXXXXXX, KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), X(ZETA), X(OMIKRON), X(OMEGA), X(SAN), XXXXXXX, X(KAPPA), X(SIGMA), X(BETA), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |   ϝ   |   ϛ   |   ͱ   |   ϻ   |               |   ϰ   |   ϙ   |   ͳ   |   ϸ   |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ξ   |   ς   |   λ   |   χ   |   ω   |               |   κ   |   ψ   |   γ   |   φ   |   ϕ   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   υ   |   ι   |   α   |   ε   |   ο   |               |   σ   |   ν   |   ρ   |   τ   |   δ   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |  XXX  |   ϰ   |   η   |   π   |   ζ   |               |   β   |   μ   |   ϱ   |   θ   |   ϑ   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, X(digamma), X(stigma), X(heta), X(koppa), X(sampi), X(scho), XXXXXXX, KC_DEL,
		KC_TAB, X(xi), X(sigma2), X(lambda), X(chi), X(psi), X(gamma), X(phi), X(phi2), KC_ENT,
		MO(1), X(ypsilon), X(iota), X(alpha), X(epsilon), X(ny), X(rho), X(tau), X(delta), MO(1),
		KC_LGUI, XXXXXXX, X(kappa2), X(eta), X(pi), X(my), X(rho2), X(theta), X(theta2), KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), X(zeta), X(omikron), X(omega), X(san), X(kappa2), X(kappa), X(sigma), X(beta), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |   Ϝ   |   Ϛ   |   Ͱ   |   Ϻ   |               |  XXX  |   Ϙ   |   Ͳ   |   Ϸ   |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   Ξ   |  XXX  |   Λ   |   Χ   |   Ω   |               |   Κ   |   Ψ   |   Γ   |   Φ   |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   Υ   |   Ι   |   Α   |   Ε   |   Ο   |               |   Σ   |   Ν   |   Ρ   |   Τ   |   Δ   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |  XXX  |  XXX  |   Η   |   Π   |   Ζ   |               |   Β   |   Μ   |  XXX  |   Θ   |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, X(DIGAMMA), X(STIGMA), X(HETA), X(KOPPA), X(SAMPI), X(SCHO), XXXXXXX, KC_DEL,
		KC_TAB, X(XI), XXXXXXX, X(LAMBDA), X(CHI), X(PSI), X(GAMMA), X(PHI), XXXXXXX, KC_ENT,
		MO(1), X(YPSILON), X(IOTA), X(ALPHA), X(EPSILON), X(NY), X(RHO), X(TAU), X(DELTA), MO(1),
		KC_LGUI, XXXXXXX, XXXXXXX, X(ETA), X(PI), X(MY), XXXXXXX, X(THETA), XXXXXXX, KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), X(ZETA), X(OMIKRON), X(OMEGA), X(SAN), XXXXXXX, X(KAPPA), X(SIGMA), X(BETA), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   l   |   m   |   n   |   o   |   j   |               |   ✓   |   ✗   |   w   |   x   |   y   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |  XXX  |   g   |   h   |   i   |   j   |               |   0   |   1   |   2   |   3   |   4   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |  💥   |  💥   |  💥   |  💥   |  💥   |               |   5   |   6   |   7   |   8   |   9   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |  💥   |  💥   |  💥   |  💥   |  💥   |               |   a   |   b   |   c   |   d   |   e   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, KC_L, KC_M, KC_N, KC_O, X(NO), KC_W, KC_X, KC_Y, KC_DEL,
		KC_TAB, XXXXXXX, KC_G, KC_H, KC_I, KC_1, KC_2, KC_3, KC_4, KC_ENT,
		MO(1), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_6, KC_7, KC_8, KC_9, MO(1),
		KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_B, KC_C, KC_D, KC_E, KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), XXXXXXX, XXXXXXX, KC_J, KC_J, X(YES), KC_0, KC_5, KC_A, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ¡   |   b   |   ¿   |   b   |   j   |               |   u   |   v   |   w   |   x   |   y   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   a   |   A   |   0   |   i   |   j   |               |   0   |   1   |   2   |   3   |   4   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |  💥   |  💥   |  💥   |  💥   |  💥   |               |   5   |   6   |   7   |   8   |   9   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |  💥   |  💥   |  💥   |  💥   |  💥   |               |   a   |   b   |   c   |   d   |   e   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, X(INV_EXCL), KC_B, X(INV_QST), KC_B, KC_V, KC_W, KC_X, KC_Y, KC_DEL,
		KC_TAB, KC_A, S(KC_A), KC_0, KC_I, KC_1, KC_2, KC_3, KC_4, KC_ENT,
		MO(1), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_6, KC_7, KC_8, KC_9, MO(1),
		KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_B, KC_C, KC_D, KC_E, KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), XXXXXXX, XXXXXXX, KC_J, KC_J, KC_U, KC_0, KC_5, KC_A, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  💥   |  💥   |  💥   |  💥   |  💥   |               |  💥   |  💥   |  💥   |  💥   |  💥   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |  💥   |  💥   |  💥   |  💥   |  💥   |               |  💥   |  💥   |  💥   |  💥   |  💥   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |  💥   |  💥   |   +   |  💥   |  💥   |               |  💥   |  💥   |  💥   |  💥   |   ε   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |  💥   |  💥   |  💥   |  💥   |  💥   |               |  💥   |  💥   |  💥   |   Ω   |  💥   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), XXXXXXX, XXXXXXX, S(KC_EQL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(epsilon), MO(1),
		KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(OMEGA), XXXXXXX, KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  💥   |   Δ   |  💥   |  💥   |  💥   |               |  💥   |  💥   |  💥   |  💥   |  💥   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |  💥   |  XXX  |  💥   |  💥   |  XXX  |               |  💥   |  💥   |  💥   |  💥   |  💥   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |  💥   |  💥   |  💥   |  💥   |  XXX  |               |  💥   |  XXX  |  💥   |  💥   |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |  💥   |  💥   |  💥   |  XXX  |  💥   |               |  💥   |  💥   |  💥   |  💥   |  💥   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, X(DELTA), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  💥   |   Δ   |  💥   |  💥   |  💥   |               |  💥   |  💥   |  💥   |  💥   |  💥   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   a   |   A   |   0   |   i   |   j   |               |   0   |   1   |   2   |   3   |   4   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   k   | _PSCR |   m   |   n   |   o   |               |   5   |   6   |   7   |   8   |   9   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |  💥   |  💥   |   r   |   s   |   t   |               |   a   |  💥   |  💥   |  💥   |  💥   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, X(DELTA), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, KC_A, S(KC_A), KC_0, KC_I, KC_1, KC_2, KC_3, KC_4, KC_ENT,
		MO(1), KC_K, KC_PSCR, KC_M, KC_N, KC_6, KC_7, KC_8, KC_9, MO(1),
		KC_LGUI, XXXXXXX, XXXXXXX, KC_R, KC_S, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), KC_T, KC_O, KC_J, XXXXXXX, XXXXXXX, KC_0, KC_5, KC_A, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ¹   |   ²   |   ³   |   ⁻   |   √   |               |   [   |   (   |   %   |   )   |   ]   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ¤   |   :   |   °   |   ʹ   |   ʺ   |               |   *   |   7   |   8   |   9   |   /   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ¢   |   ¥   |   £   |   €   |   $   |               |   +   |   4   |   5   |   6   |   -   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T4   |   ÷   |   µ   |   Ω   |   ₿   |   §   |               |   ^   |   1   |   2   |   3   |   "   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  XXX  |  L4   | Ctrl  |   .   |   0   |   ,   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, X(SUP1), X(SUP2), X(SUP3), X(SUP_MIN), S(KC_9), S(KC_5), S(KC_0), KC_RBRC, KC_DEL,
		KC_TAB, X(CURRENCY), S(KC_SCLN), X(DEGREE), X(MINUTE), KC_7, KC_8, KC_9, KC_SLSH, KC_ENT,
		MO(1), X(CENT), X(YEN), X(POUND), X(EURO), KC_4, KC_5, KC_6, KC_MINS, MO(1),
		TG(4), X(DIVISION), X(MICRO), X(OHM), X(BITCOIN), KC_1, KC_2, KC_3, S(KC_QUOT), KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, KC_COMM, MATH, SYMBOL, KC_DOT, MOUSE,
		MO(4), X(SECTION), S(KC_4), X(SECOND), X(ROOT), KC_LBRC, S(KC_8), S(KC_EQL), S(KC_6), KC_0),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  💥   |  💥   |  💥   |  💥   |  💥   |               |  💥   |  💥   |  💥   |  💥   |  💥   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |  XXX  |  XXX  |  💥   |  💥   |  💥   |               |  💥   |  💥   |  💥   |  💥   |  💥   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |  💥   |  💥   |  💥   |  💥   |  💥   |               |  💥   |  💥   |  💥   |  💥   |  💥   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |  💥   |  💥   |  💥   |  💥   |  💥   |               |  💥   |  💥   |  💥   |  💥   |  💥   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   1   |   2   |   3   |   4   |   5   |               |   6   |   7   |   8   |   9   |   0   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   q   |   w   |   e   |   r   |   t   |               |   y   |   u   |   i   |   o   |   p   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * | Caps  |   a   |   s   |   d   |   f   |   g   |               |   h   |   j   |   k   |   l   |^ Arrow| Shift |
 * -------------------------------------------------               -------------------------------------------------
 * | Shift |   z   |   x   |   c   |   v   |   b   |               |   n   |   m   |   ,   |< Arrow|v Arrow|> Arrow|
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  Alt  | Space | Ctrl  | Enter |RShift | Ctrl  | MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_7, KC_8, KC_9, KC_0, KC_DEL,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_U, KC_I, KC_O, KC_P, KC_ENT,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_J, KC_K, KC_L, KC_UP, KC_LSFT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_M, KC_COMM, KC_LEFT, KC_DOWN, KC_RIGHT,
		TG(2), KC_LCTRL, GAME, GREEK, KC_LALT, KC_LCTRL, MATH, SYMBOL, KC_ENT, MOUSE,
		KC_SPC, KC_B, KC_G, KC_T, KC_5, KC_6, KC_Y, KC_H, KC_N, KC_RSFT),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  | Menu  | < Tab |^ Arrow| > Tab | Pg Up |               |Pr Scr |Mouse 1|^ Mouse|Mouse 2|Scr Lck| Enter |
 * -------------------------------------------------               -------------------------------------------------
 * | Shift |BSpace |< Arrow|v Arrow|> Arrow|Pg Down|               |  XXX  |< Mouse|v Mouse|> Mouse|  XXX  | Shift |
 * -------------------------------------------------               -------------------------------------------------
 * | Enter | Undo  |  Cut  | Copy  | Paste |  Del  |               |Macro 1|Macro 2|Macro 3|Macro 4|Macro 5|BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  Alt  | Space | Ctrl  |Mouse 3|Mouse 1|Mouse 2| MATH   SYMBOL           MOUSE  
 *                                 -------------------------------------------------
 */
	KEYMAP(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, KC_MENU, LCTL(S(KC_TAB)), KC_UP, LCTL(KC_TAB), KC_BTN1, KC_MS_U, KC_BTN2, KC_SLCK, KC_ENT,
		KC_LSFT, KC_BSPC, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, KC_LSFT,
		KC_ENT, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_2, KC_3, KC_4, KC_5, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, KC_LALT, KC_BTN2, MATH, SYMBOL, KC_BTN3, MOUSE,
		KC_SPC, KC_DEL, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, KC_1, KC_BTN1)
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
	switch (keycode) {
		case GREEK:
			if (record->event.pressed) {
				layer_invert(12);
				layer_off(16);
				layer_off(18);
				layer_off(23);
				layer_off(24);
			} else {
				// Do something else when release
			}
			return false; // Skip all further processing of this key
		case SYMBOL:
			if (record->event.pressed) {
				layer_off(12);
				layer_invert(16);
				layer_off(18);
				layer_off(23);
				layer_off(24);
			} else {
				// Do something else when release
			}
			return false; // Skip all further processing of this key
		case MATH:
			if (record->event.pressed) {
				layer_off(12);
				layer_off(16);
				layer_invert(18);
				layer_off(23);
				layer_off(24);
			} else {
				// Do something else when release
			}
			return false; // Skip all further processing of this key
		case GAME:
			if (record->event.pressed) {
				layer_off(12);
				layer_off(16);
				layer_off(18);
				layer_invert(23);
				layer_off(24);
			} else {
				// Do something else when release
			}
			return false; // Skip all further processing of this key
		case MOUSE:
			if (record->event.pressed) {
				layer_off(12);
				layer_off(16);
				layer_off(18);
				layer_off(23);
				layer_invert(24);
			} else {
				// Do something else when release
			}
			return false; // Skip all further processing of this key
		default:
			return true; // Process all other keycodes normally
	}
}

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, 1, 2, 3);
  state = update_tri_layer_state(state, 1, 4, 5);
  state = update_tri_layer_state(state, 1, 6, 7);
  state = update_tri_layer_state(state, 1, 8, 9);
  state = update_tri_layer_state(state, 2, 8, 10);
  state = update_tri_layer_state(state, 1, 10, 11);
  state = update_tri_layer_state(state, 1, 12, 13);
  state = update_tri_layer_state(state, 2, 12, 14);
  state = update_tri_layer_state(state, 1, 14, 15);
  state = update_tri_layer_state(state, 1, 16, 17);
  state = update_tri_layer_state(state, 1, 18, 19);
  state = update_tri_layer_state(state, 4, 18, 20);
  state = update_tri_layer_state(state, 1, 20, 21);
  state = update_tri_layer_state(state, 2, 21, 22);
  return state;
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
