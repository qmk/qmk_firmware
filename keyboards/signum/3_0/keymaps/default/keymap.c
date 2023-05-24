/* keymap.c is auto-generated, don't edit it directly.
 * Further instructions are provided in readme.md */

#include QMK_KEYBOARD_H

enum unicode_name {
AB_ARC,
AB_LINE,
AB_VEC,
ACUTE,
AE,
ALEPH,
ALLA_BR,
ALPHA,
AND,
AND_,
ANGLE,
AST_MID,
A_SET,
BARLINE,
BARLINE_D,
BARLINE_FIN,
BETA,
BETH,
BICOND,
BIG_O,
BISHOP_B,
BISHOP_W,
BITCOIN,
BOTTOM,
BOWTIE,
BRA,
BULLET,
B_SET,
CENT,
CHI,
CIRCLE,
CIRC_MID,
CLUBS_B,
CLUBS_W,
CODA,
COMMON_T,
COPYR,
CORRESP,
CROSS,
CURRENCY,
C_CLEF,
C_SET,
DACAPO,
DALSEGNO,
DEFINE,
DEGREE,
DELTA,
DIAMS_B,
DIAMS_W,
DIGAMMA,
DIVISION,
DOTS,
DOT_OP,
DQT1,
DQT2,
DQT3,
DQT4,
DQT5,
EIGHTH_N,
EIGHTH_P,
EJECT,
EMBED,
EMDASH,
EMPTYSET,
EPSILON,
EQUIV,
ETA,
EURO,
EXISTS,
FEMALE,
FLAG_B,
FLAG_W,
FLAT,
FORALL,
FORWARD,
FOURIER,
FULL_OUTER,
F_CLEF,
F_SET,
GAMMA,
GREAT_GREAT,
GR_EQ,
G_CLEF,
HALF_N,
HALF_P,
HAMILTON,
HEARTS_B,
HEARTS_W,
HETA,
H_SET,
IMAG_P,
IMPL,
IMPL_REV,
IN,
INDICATOR,
INEQUAL,
INFO,
INFTY,
INTEGRAL,
INTERS,
INTERS_,
INV_EXCL,
INV_QST,
IOTA,
ISOMORPH,
KAPPA,
KET,
KEY,
KING_B,
KING_W,
KNIGHT_B,
KNIGHT_W,
KOPPA,
K_SET,
LAMBDA,
LAPLACE,
LEFT_CEIL,
LEFT_FLOOR,
LEFT_OUTER,
LENGTH,
LESS_LESS,
LETTER,
LOCK,
LOCK_OPEN,
LS_EQ,
LTIMES,
MALE,
MAPSTO,
MDOT,
MICRO,
MINUS_OP,
MINUS_PLUS,
MINUTE,
MODELS,
MY,
M_ANGLE,
NABLA,
NATURAL,
NO,
NOT,
NOTIN,
NOTSUBS,
NOT_DIV,
NOT_PARA,
NY,
N_SET,
N_TILDE,
OE,
OHM,
OMEGA,
OMIKRON,
OR,
OR_,
PARALLEL,
PARTIAL,
PAWN_B,
PAWN_W,
PEDAL,
PEDAL_UP,
PERMIL,
PHI,
PHONE,
PI,
PLAY,
PLUS_MINUS,
PLUS_OP,
POUND,
POWERSET,
PRED,
PROD_,
PROP_TO,
PR_SUBSET,
PSI,
QED,
QUART_N,
QUART_P,
QUEEN_B,
QUEEN_W,
Q_SET,
REAL_P,
REGTM,
REPEAT_E,
REPEAT_S,
REWIND,
RHO,
RIGHT_CEIL,
RIGHT_FLOOR,
RIGHT_OUTER,
RIGHT_TACK,
ROOK_B,
ROOK_W,
ROOT,
ROUGHLY,
RTIMES,
R_SET,
SAMPI,
SAN,
SCHO,
SECOND,
SECTION,
SEGNO,
SETMINUS,
SHARP,
SHOGI_B,
SHOGI_BD,
SHOGI_W,
SHOGI_WD,
SIGMA,
SIXT_N,
SIXT_P,
SNEK,
SPADES_B,
SPADES_W,
SPEAKER_DN,
SPEAKER_TG,
SPEAKER_UP,
SQT1,
SQT2,
SQT3,
SQT4,
SQT5,
SQUARE,
SQ_LS,
SQ_LS_EQ,
STAFF,
STIGMA,
STOP,
SUBSET,
SUBSET_REV,
SUCC,
SUM_,
SUP1,
SUP2,
SUP3,
SUP_A,
SUP_MIN,
SUP_O,
SZ,
TAU,
THETA,
TIMES,
TIMES_OP,
TMARK,
TO,
TOP,
TRIANGLE,
UE,
UNION,
UNION_,
U_SET,
WHOLE_N,
WHOLE_P,
XI,
YEN,
YES,
YPSI2,
YPSILON,
ZETA,
Z_SET,
ae,
alpha,
beta,
beta2,
chi,
delta,
digamma,
e_FUN,
epsi2,
epsilon,
eta,
gamma,
heta,
i_UNIT,
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
	[AB_ARC] = 0x0361,  // ͡
	[AB_LINE] = 0x0305,  // ̅
	[AB_VEC] = 0x20d7,  // ⃗
	[ACUTE] = 0x00b4,  // ´
	[AE] = 0x00c4,  // Ä
	[ALEPH] = 0x2135,  // ℵ
	[ALLA_BR] = 0x1d135,  // 𝄵
	[ALPHA] = 0x0391,  // Α
	[AND] = 0x2227,  // ∧
	[AND_] = 0x22c0,  // ⋀
	[ANGLE] = 0x2220,  // ∠
	[AST_MID] = 0x2217,  // ∗
	[A_SET] = 0x1d538,  // 𝔸
	[BARLINE] = 0x1d100,  // 𝄀
	[BARLINE_D] = 0x1d101,  // 𝄁
	[BARLINE_FIN] = 0x1d102,  // 𝄂
	[BETA] = 0x0392,  // Β
	[BETH] = 0x2136,  // ℶ
	[BICOND] = 0x21d4,  // ⇔
	[BIG_O] = 0x1d4aa,  // 𝒪
	[BISHOP_B] = 0x265d,  // ♝
	[BISHOP_W] = 0x2657,  // ♗
	[BITCOIN] = 0x20bf,  // ₿
	[BOTTOM] = 0x22a5,  // ⊥
	[BOWTIE] = 0x22c8,  // ⋈
	[BRA] = 0x27e8,  // ⟨
	[BULLET] = 0x2022,  // •
	[B_SET] = 0x1d539,  // 𝔹
	[CENT] = 0x00a2,  // ¢
	[CHI] = 0x03a7,  // Χ
	[CIRCLE] = 0x25cb,  // ○
	[CIRC_MID] = 0x2218,  // ∘
	[CLUBS_B] = 0x2663,  // ♣
	[CLUBS_W] = 0x2667,  // ♧
	[CODA] = 0x1d10c,  // 𝄌
	[COMMON_T] = 0x1d134,  // 𝄴
	[COPYR] = 0x00a9,  // ©
	[CORRESP] = 0x2259,  // ≙
	[CROSS] = 0x2020,  // †
	[CURRENCY] = 0x00a4,  // ¤
	[C_CLEF] = 0x1d121,  // 𝄡
	[C_SET] = 0x2102,  // ℂ
	[DACAPO] = 0x1d10a,  // 𝄊
	[DALSEGNO] = 0x1d109,  // 𝄉
	[DEFINE] = 0x2254,  // ≔
	[DEGREE] = 0x00b0,  // °
	[DELTA] = 0x0394,  // Δ
	[DIAMS_B] = 0x2666,  // ♦
	[DIAMS_W] = 0x2662,  // ♢
	[DIGAMMA] = 0x03dc,  // Ϝ
	[DIVISION] = 0x00f7,  // ÷
	[DOTS] = 0x2026,  // …
	[DOT_OP] = 0x2299,  // ⊙
	[DQT1] = 0x00bb,  // »
	[DQT2] = 0x201e,  // „
	[DQT3] = 0x201c,  // “
	[DQT4] = 0x201d,  // ”
	[DQT5] = 0x00ab,  // «
	[EIGHTH_N] = 0x1d160,  // 𝅘𝅥𝅮
	[EIGHTH_P] = 0x1d13e,  // 𝄾
	[EJECT] = 0x23cf,  // ⏏
	[EMBED] = 0x21aa,  // ↪
	[EMDASH] = 0x2014,  // —
	[EMPTYSET] = 0x2205,  // ∅
	[EPSILON] = 0x0395,  // Ε
	[EQUIV] = 0x2261,  // ≡
	[ETA] = 0x0397,  // Η
	[EURO] = 0x20ac,  // €
	[EXISTS] = 0x2203,  // ∃
	[FEMALE] = 0x2640,  // ♀
	[FLAG_B] = 0x2691,  // ⚑
	[FLAG_W] = 0x2690,  // ⚐
	[FLAT] = 0x266d,  // ♭
	[FORALL] = 0x2200,  // ∀
	[FORWARD] = 0x23ed,  // ⏭
	[FOURIER] = 0x2131,  // ℱ
	[FULL_OUTER] = 0x27d7,  // ⟗
	[F_CLEF] = 0x1d122,  // 𝄢
	[F_SET] = 0x1d53d,  // 𝔽
	[GAMMA] = 0x0393,  // Γ
	[GREAT_GREAT] = 0x226b,  // ≫
	[GR_EQ] = 0x2265,  // ≥
	[G_CLEF] = 0x1d11e,  // 𝄞
	[HALF_N] = 0x1d15e,  // 𝅗𝅥
	[HALF_P] = 0x1d13c,  // 𝄼
	[HAMILTON] = 0x210b,  // ℋ
	[HEARTS_B] = 0x2665,  // ♥
	[HEARTS_W] = 0x2661,  // ♡
	[HETA] = 0x0370,  // Ͱ
	[H_SET] = 0x210d,  // ℍ
	[IMAG_P] = 0x2111,  // ℑ
	[IMPL] = 0x21d2,  // ⇒
	[IMPL_REV] = 0x21d0,  // ⇐
	[IN] = 0x2208,  // ∈
	[INDICATOR] = 0x1d7cf,  // 𝟏
	[INEQUAL] = 0x2260,  // ≠
	[INFO] = 0x1f6c8,  // 🛈
	[INFTY] = 0x221e,  // ∞
	[INTEGRAL] = 0x222b,  // ∫
	[INTERS] = 0x2229,  // ∩
	[INTERS_] = 0x22c2,  // ⋂
	[INV_EXCL] = 0x00a1,  // ¡
	[INV_QST] = 0x00bf,  // ¿
	[IOTA] = 0x0399,  // Ι
	[ISOMORPH] = 0x2245,  // ≅
	[KAPPA] = 0x039a,  // Κ
	[KET] = 0x27e9,  // ⟩
	[KEY] = 0x1f511,  // 🔑
	[KING_B] = 0x265a,  // ♚
	[KING_W] = 0x2654,  // ♔
	[KNIGHT_B] = 0x265e,  // ♞
	[KNIGHT_W] = 0x2658,  // ♘
	[KOPPA] = 0x03d8,  // Ϙ
	[K_SET] = 0x1d542,  // 𝕂
	[LAMBDA] = 0x039b,  // Λ
	[LAPLACE] = 0x2112,  // ℒ
	[LEFT_CEIL] = 0x2308,  // ⌈
	[LEFT_FLOOR] = 0x230a,  // ⌊
	[LEFT_OUTER] = 0x27d5,  // ⟕
	[LENGTH] = 0x2113,  // ℓ
	[LESS_LESS] = 0x226a,  // ≪
	[LETTER] = 0x2709,  // ✉
	[LOCK] = 0x1f512,  // 🔒
	[LOCK_OPEN] = 0x1f513,  // 🔓
	[LS_EQ] = 0x2264,  // ≤
	[LTIMES] = 0x22c9,  // ⋉
	[MALE] = 0x2642,  // ♂
	[MAPSTO] = 0x27fc,  // ⟼
	[MDOT] = 0x22c5,  // ⋅
	[MICRO] = 0x00b5,  // µ
	[MINUS_OP] = 0x2296,  // ⊖
	[MINUS_PLUS] = 0x2213,  // ∓
	[MINUTE] = 0x02b9,  // ʹ
	[MODELS] = 0x22a7,  // ⊧
	[MY] = 0x039c,  // Μ
	[M_ANGLE] = 0x2221,  // ∡
	[NABLA] = 0x2207,  // ∇
	[NATURAL] = 0x266e,  // ♮
	[NO] = 0x2717,  // ✗
	[NOT] = 0x00ac,  // ¬
	[NOTIN] = 0x2209,  // ∉
	[NOTSUBS] = 0x2288,  // ⊈
	[NOT_DIV] = 0x2224,  // ∤
	[NOT_PARA] = 0x2226,  // ∦
	[NY] = 0x039d,  // Ν
	[N_SET] = 0x2115,  // ℕ
	[N_TILDE] = 0x00d1,  // Ñ
	[OE] = 0x00d6,  // Ö
	[OHM] = 0x2126,  // Ω
	[OMEGA] = 0x03a9,  // Ω
	[OMIKRON] = 0x039f,  // Ο
	[OR] = 0x2228,  // ∨
	[OR_] = 0x22c1,  // ⋁
	[PARALLEL] = 0x2225,  // ∥
	[PARTIAL] = 0x2202,  // ∂
	[PAWN_B] = 0x265f,  // ♟
	[PAWN_W] = 0x2659,  // ♙
	[PEDAL] = 0x1d1ae,  // 𝆮
	[PEDAL_UP] = 0x1d1af,  // 𝆯
	[PERMIL] = 0x2030,  // ‰
	[PHI] = 0x03a6,  // Φ
	[PHONE] = 0x2706,  // ✆
	[PI] = 0x03a0,  // Π
	[PLAY] = 0x23ef,  // ⏯
	[PLUS_MINUS] = 0x00b1,  // ±
	[PLUS_OP] = 0x2295,  // ⊕
	[POUND] = 0x00a3,  // £
	[POWERSET] = 0x1d4ab,  // 𝒫
	[PRED] = 0x227a,  // ≺
	[PROD_] = 0x220f,  // ∏
	[PROP_TO] = 0x221d,  // ∝
	[PR_SUBSET] = 0x2282,  // ⊂
	[PSI] = 0x03a8,  // Ψ
	[QED] = 0x220e,  // ∎
	[QUART_N] = 0x1d15f,  // 𝅘𝅥
	[QUART_P] = 0x1d13d,  // 𝄽
	[QUEEN_B] = 0x265b,  // ♛
	[QUEEN_W] = 0x2655,  // ♕
	[Q_SET] = 0x211a,  // ℚ
	[REAL_P] = 0x211c,  // ℜ
	[REGTM] = 0x00ae,  // ®
	[REPEAT_E] = 0x1d107,  // 𝄇
	[REPEAT_S] = 0x1d106,  // 𝄆
	[REWIND] = 0x23ee,  // ⏮
	[RHO] = 0x03a1,  // Ρ
	[RIGHT_CEIL] = 0x2309,  // ⌉
	[RIGHT_FLOOR] = 0x230b,  // ⌋
	[RIGHT_OUTER] = 0x27d6,  // ⟖
	[RIGHT_TACK] = 0x22a2,  // ⊢
	[ROOK_B] = 0x265c,  // ♜
	[ROOK_W] = 0x2656,  // ♖
	[ROOT] = 0x221a,  // √
	[ROUGHLY] = 0x2248,  // ≈
	[RTIMES] = 0x22ca,  // ⋊
	[R_SET] = 0x211d,  // ℝ
	[SAMPI] = 0x0372,  // Ͳ
	[SAN] = 0x03fa,  // Ϻ
	[SCHO] = 0x03f7,  // Ϸ
	[SECOND] = 0x02ba,  // ʺ
	[SECTION] = 0x00a7,  // §
	[SEGNO] = 0x1d10b,  // 𝄋
	[SETMINUS] = 0x2216,  // ∖
	[SHARP] = 0x266f,  // ♯
	[SHOGI_B] = 0x2617,  // ☗
	[SHOGI_BD] = 0x26ca,  // ⛊
	[SHOGI_W] = 0x2616,  // ☖
	[SHOGI_WD] = 0x26c9,  // ⛉
	[SIGMA] = 0x03a3,  // Σ
	[SIXT_N] = 0x1d161,  // 𝅘𝅥𝅯
	[SIXT_P] = 0x1d13f,  // 𝄿
	[SNEK] = 0x1f40d,  // 🐍
	[SPADES_B] = 0x2660,  // ♠
	[SPADES_W] = 0x2664,  // ♤
	[SPEAKER_DN] = 0x1f509,  // 🔉
	[SPEAKER_TG] = 0x1f507,  // 🔇
	[SPEAKER_UP] = 0x1f50a,  // 🔊
	[SQT1] = 0x203a,  // ›
	[SQT2] = 0x201a,  // ‚
	[SQT3] = 0x2018,  // ‘
	[SQT4] = 0x2019,  // ’
	[SQT5] = 0x2039,  // ‹
	[SQUARE] = 0x25a1,  // □
	[SQ_LS] = 0x228f,  // ⊏
	[SQ_LS_EQ] = 0x2291,  // ⊑
	[STAFF] = 0x1d11a,  // 𝄚
	[STIGMA] = 0x03da,  // Ϛ
	[STOP] = 0x25fc,  // ◼
	[SUBSET] = 0x2286,  // ⊆
	[SUBSET_REV] = 0x2287,  // ⊇
	[SUCC] = 0x227b,  // ≻
	[SUM_] = 0x2211,  // ∑
	[SUP1] = 0x00b9,  // ¹
	[SUP2] = 0x00b2,  // ²
	[SUP3] = 0x00b3,  // ³
	[SUP_A] = 0x00aa,  // ª
	[SUP_MIN] = 0x207b,  // ⁻
	[SUP_O] = 0x00ba,  // º
	[SZ] = 0x1e9e,  // ẞ
	[TAU] = 0x03a4,  // Τ
	[THETA] = 0x0398,  // Θ
	[TIMES] = 0x00d7,  // ×
	[TIMES_OP] = 0x2297,  // ⊗
	[TMARK] = 0x2122,  // ™
	[TO] = 0x27f6,  // ⟶
	[TOP] = 0x22a4,  // ⊤
	[TRIANGLE] = 0x25b3,  // △
	[UE] = 0x00dc,  // Ü
	[UNION] = 0x222a,  // ∪
	[UNION_] = 0x22c3,  // ⋃
	[U_SET] = 0x1d54c,  // 𝕌
	[WHOLE_N] = 0x1d15d,  // 𝅝
	[WHOLE_P] = 0x1d13b,  // 𝄻
	[XI] = 0x039e,  // Ξ
	[YEN] = 0x00a5,  // ¥
	[YES] = 0x2713,  // ✓
	[YPSI2] = 0x03d2,  // ϒ
	[YPSILON] = 0x03a5,  // Υ
	[ZETA] = 0x0396,  // Ζ
	[Z_SET] = 0x2124,  // ℤ
	[ae] = 0x00e4,  // ä
	[alpha] = 0x03b1,  // α
	[beta] = 0x03b2,  // β
	[beta2] = 0x03d0,  // ϐ
	[chi] = 0x03c7,  // χ
	[delta] = 0x03b4,  // δ
	[digamma] = 0x03dd,  // ϝ
	[e_FUN] = 0x0065,  // e
	[epsi2] = 0x03f5,  // ϵ
	[epsilon] = 0x03b5,  // ε
	[eta] = 0x03b7,  // η
	[gamma] = 0x03b3,  // γ
	[heta] = 0x0371,  // ͱ
	[i_UNIT] = 0x0069,  // i
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

/*
 * Layer 0
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   q   |   w   |   e   |   r   |   t   |               |   y   |   u   |   i   |   o   |   p   |   [   |
 * -------------------------------------------------               -------------------------------------------------
 * |LCtTEsc|   a   |   s   |   d   |   f   |   g   |               |   h   |   j   |   k   |   l   |   ;   |   '   |
 * -------------------------------------------------               -------------------------------------------------
 * |LShift(|   z   |   x   |   c   |   v   |   b   |               |   n   |   m   |   ,   |   .   |   /   |RShift)|
 * -----------------------------------------------------------------------------------------------------------------
 *  LCtrl[   LAlt    LGui          |  TT2  |LT6_SPC|LT4_DEL|LT4_ENT| Space |LT2_BSP|         RGui    RLAlt  RCtrl]
 *                                 -------------------------------------------------
 */
	LAYOUT_ortho_4x12(
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC,
		LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
		KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
		LCTL_T(KC_LBRC), KC_LALT, KC_LGUI, TT(2), LT(6,KC_SPC), LT(4,KC_DEL), LT(4,KC_ENT), KC_SPC, LT(2,KC_BSPC), KC_RGUI, LALT_T(KC_RALT), RCTL_T(KC_RBRC)
	),

/*
 * Layer 1
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   q   |   w   |   f   |   p   |   g   |               |   j   |   l   |   u   |   y   |   ;   |   [   |
 * -------------------------------------------------               -------------------------------------------------
 * |LCtTEsc|   a   |   r   |   s   |   t   |   d   |               |   h   |   n   |   e   |   i   |   o   |   '   |
 * -------------------------------------------------               -------------------------------------------------
 * |LShift(|   z   |   x   |   c   |   v   |   b   |               |   k   |   m   |   ,   |   .   |   /   |RShift)|
 * -----------------------------------------------------------------------------------------------------------------
 *  LCtrl[   LAlt    LGui          |  TT2  |LT6_SPC|LT4_DEL|LT4_ENT| Space |LT2_BSP|         RGui    RLAlt  RCtrl]
 *                                 -------------------------------------------------
 */
	LAYOUT_ortho_4x12(
		KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_LBRC,
		LCTL_T(KC_ESC), KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT,
		KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
		LCTL_T(KC_LBRC), KC_LALT, KC_LGUI, TT(2), LT(6,KC_SPC), LT(4,KC_DEL), LT(4,KC_ENT), KC_SPC, LT(2,KC_BSPC), KC_RGUI, LALT_T(KC_RALT), RCTL_T(KC_RBRC)
	),

/*
 * Layer 2
 * -------------------------------------------------               -------------------------------------------------
 * |   `   |   1   |   2   |   3   |   4   |   5   |               |   6   |   7   |   8   |   9   |   0   |   ]   |
 * -------------------------------------------------               -------------------------------------------------
 * |       |  DF0  |  DF1  |  XXX  |  MO3  |  MO3  |               |   4   |   4   |   5   |   6   |   -   |   =   |
 * -------------------------------------------------               -------------------------------------------------
 * |       |  MO5  |  XXX  |  XXX  |  XXX  |  XXX  |               |   1   |   1   |   2   |   3   |   \   |       |
 * -----------------------------------------------------------------------------------------------------------------
 *    TG2                          |       |       |  Del  |       |   0   |BSpace |
 *                                 -------------------------------------------------
 */
	LAYOUT_ortho_4x12(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_RBRC,
		KC_TRNS, DF(0), DF(1), KC_NO, MO(3), MO(3), KC_4, KC_4, KC_5, KC_6, KC_MINS, KC_EQL,
		KC_TRNS, MO(5), KC_NO, KC_NO, KC_NO, KC_NO, KC_1, KC_1, KC_2, KC_3, KC_BSLS, KC_TRNS,
		TG(2), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_0, KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS
	),

/*
 * Layer 3
 * -------------------------------------------------               -------------------------------------------------
 * |       |  F1   |  F2   |  F3   |  F4   |  F5   |               |  F6   |  F7   |  F8   |  F9   |  F10  |  XXX  |
 * -------------------------------------------------               -------------------------------------------------
 * |       |  XXX  |  XXX  |  XXX  |  MO3  |  MO3  |               |  F4   |  F4   |  F5   |  F6   |  F11  |  XXX  |
 * -------------------------------------------------               -------------------------------------------------
 * |       |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  F1   |  F1   |  F2   |  F3   |  F12  |       |
 * -----------------------------------------------------------------------------------------------------------------
 *    TG3                          |       |       |       |       |       |       |
 *                                 -------------------------------------------------
 */
	LAYOUT_ortho_4x12(
		KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO,
		KC_TRNS, KC_NO, KC_NO, KC_NO, MO(3), MO(3), KC_F4, KC_F4, KC_F5, KC_F6, KC_F11, KC_NO,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F1, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS,
		TG(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

/*
 * Layer 4
 * -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  Esc  | Tab x | Tab n |CPg Dn |CPg Dn |               |Pg Down| Home  |^ Arrow|Insert |SInsert|  Esc  |
 * -------------------------------------------------               -------------------------------------------------
 * |       | Caps  | < Gui |Gui Tab| > Gui | > Gui |               |< Arrow|< Arrow|v Arrow|> Arrow|  End  |Pr Scr |
 * -------------------------------------------------               -------------------------------------------------
 * |       |  XXX  |  XXX  |  XXX  |CPg Up |CPg Up |               | Pg Up |       |v Arrow|  XXX  |  App  |       |
 * -----------------------------------------------------------------------------------------------------------------
 *    TG4                          |       |       |  Del  |       |BSpace |       |
 *                                 -------------------------------------------------
 */
	LAYOUT_ortho_4x12(
		KC_ESC, KC_ESC, LCTL(KC_W), LCTL(KC_T), LCTL(KC_PGDN), LCTL(KC_PGDN), KC_PGDN, KC_HOME, KC_UP, KC_INS, LSFT(KC_INS), KC_ESC,
		KC_TRNS, KC_CAPS, LGUI(KC_LEFT), LGUI(KC_TAB), LGUI(KC_RGHT), LGUI(KC_RGHT), KC_LEFT, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_PSCR,
		KC_TRNS, KC_NO, KC_NO, KC_NO, LCTL(KC_PGUP), LCTL(KC_PGUP), KC_PGUP, KC_TRNS, KC_DOWN, KC_NO, KC_APP, KC_TRNS,
		TG(4), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

/*
 * Layer 5
 * -------------------------------------------------               -------------------------------------------------
 * |       |  XXX  |play/ps| Vol + | Vol + |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |_reset | Power |
 * -------------------------------------------------               -------------------------------------------------
 * |       |  XXX  |  |<<  | Vol 0 |  >>|  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  | Sleep |
 * -------------------------------------------------               -------------------------------------------------
 * |       |  MO5  |  XXX  | Vol - | Vol - |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |
 * -----------------------------------------------------------------------------------------------------------------
 *    TG5                          |       |       |       |       |       |       |
 *                                 -------------------------------------------------
 */
	LAYOUT_ortho_4x12(
		KC_TRNS, KC_NO, KC_MPLY, KC_VOLU, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_PWR,
		KC_TRNS, KC_NO, KC_MPRV, KC_MUTE, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SLEP,
		KC_TRNS, MO(5), KC_NO, KC_VOLD, KC_VOLD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		TG(5), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

/*
 * Layer 6
 * -------------------------------------------------               -------------------------------------------------
 * |       | acc1  |  XXX  |  XXX  |  XXX  |  XXX  |               |^ Wheel|< Wheel|^ Mouse|> Wheel|  XXX  |  XXX  |
 * -------------------------------------------------               -------------------------------------------------
 * |       | acc2  |Mouse 2|Mouse 3|Mouse 1|Mouse 1|               |< Mouse|< Mouse|v Mouse|> Mouse|  XXX  |  XXX  |
 * -------------------------------------------------               -------------------------------------------------
 * |       | acc0  |  XXX  |  XXX  |  XXX  |  XXX  |               |v Wheel|  XXX  |v Mouse|  XXX  |  XXX  |       |
 * -----------------------------------------------------------------------------------------------------------------
 *    TG6                          |       |       |       |       |       |       |
 *                                 -------------------------------------------------
 */
	LAYOUT_ortho_4x12(
		KC_TRNS, KC_ACL1, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_NO, KC_NO,
		KC_TRNS, KC_ACL2, KC_BTN2, KC_BTN3, KC_BTN1, KC_BTN1, KC_MS_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO,
		KC_TRNS, KC_ACL0, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_NO, KC_MS_D, KC_NO, KC_NO, KC_TRNS,
		TG(6), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	)
};

/* vi: ft=c:tw=80:sw=2:ts=2:sts=2:et
 */
