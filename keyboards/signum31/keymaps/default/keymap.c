#include QMK_KEYBOARD_H

enum my_keycodes {
  GREEK = SAFE_RANGE,
  SYMBOL,
	MATH,
	GAME,
	MOUSE
};

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
	LAYOUT(
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
	LAYOUT(
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
	LAYOUT(
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
	LAYOUT(
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
	LAYOUT(
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
	LAYOUT(
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
	LAYOUT(
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
	LAYOUT(
		KC_ESC, X(SQT1), X(SQT2), X(SQT3), X(SQT4), KC_SLCK, KC_PSCR, KC_BRK, LCTL(LALT(KC_DEL)), KC_DEL,
		KC_TAB, X(SUP_A), X(SUP_O), X(TMARK), X(COPYR), KC_HOME, KC_UP, KC_END, KC_APP, KC_ENT,
		MO(1), X(DOTS), X(CROSS), X(BULLET), X(EMDASH), KC_LEFT, KC_DOWN, KC_RIGHT, KC_MENU, MO(1),
		TG(7), X(DQT1), X(DQT2), X(DQT3), X(DQT4), KC_2, KC_3, KC_4, KC_5, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, MO(6), XXXXXXX, MATH, SYMBOL, KC_LALT, MOUSE,
		XXXXXXX, X(DQT5), X(PERMIL), X(REGTM), X(SQT5), KC_INS, KC_PGUP, KC_PGDN, KC_1, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |Compose|  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |   ü   |  XXX  |   ö   |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ä   |   ß   |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T8   |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |   ñ   |  XXX  |  XXX  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  XXX  |  XXX  | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE
 *                                 -------------------------------------------------
 */
	LAYOUT(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_ALGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(ue), XXXXXXX, X(oe), XXXXXXX, KC_ENT,
		MO(1), X(ae), X(sz), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		TG(8), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(n_tilde), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |Compose|  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |   Ü   |  XXX  |   Ö   |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   Ä   |   ẞ   |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T9   |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |   Ñ   |  XXX  |  XXX  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  XXX  |  XXX  | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE
 *                                 -------------------------------------------------
 */
	LAYOUT(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_ALGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(UE), XXXXXXX, X(OE), XXXXXXX, KC_ENT,
		MO(1), X(AE), X(SZ), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		TG(9), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(N_TILDE), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |Compose|  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ü   |  XXX  |   ä   |  XXX  |   ö   |               |   ß   |   ñ   |  XXX  |  XXX  |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T8   |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  XXX  |  XXX  | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE
 *                                 -------------------------------------------------
 */
	LAYOUT(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_ALGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), X(ue), XXXXXXX, X(ae), XXXXXXX, X(n_tilde), XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		TG(8), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
		XXXXXXX, XXXXXXX, X(oe), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(sz), XXXXXXX, KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |Compose|  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   Ü   |  XXX  |   Ä   |  XXX  |   Ö   |               |   ẞ   |   Ñ   |  XXX  |  XXX  |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  T9   |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |               |  XXX  |  XXX  |  XXX  |  XXX  |  XXX  |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  XXX  |  XXX  | Ctrl  |  Alt  | Space |  L8   | MATH   SYMBOL           MOUSE
 *                                 -------------------------------------------------
 */
	LAYOUT(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_ALGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
		MO(1), X(UE), XXXXXXX, X(AE), XXXXXXX, X(N_TILDE), XXXXXXX, XXXXXXX, XXXXXXX, MO(1),
		TG(9), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, MO(8), MATH, SYMBOL, KC_LALT, MOUSE,
		XXXXXXX, XXXXXXX, X(OE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(SZ), XXXXXXX, KC_SPC),

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
	LAYOUT(
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
	LAYOUT(
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
	LAYOUT(
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
	LAYOUT(
		KC_ESC, XXXXXXX, X(DIGAMMA), X(STIGMA), X(HETA), X(KOPPA), X(SAMPI), X(SCHO), XXXXXXX, KC_DEL,
		KC_TAB, X(XI), XXXXXXX, X(LAMBDA), X(CHI), X(PSI), X(GAMMA), X(PHI), XXXXXXX, KC_ENT,
		MO(1), X(YPSILON), X(IOTA), X(ALPHA), X(EPSILON), X(NY), X(RHO), X(TAU), X(DELTA), MO(1),
		KC_LGUI, XXXXXXX, XXXXXXX, X(ETA), X(PI), X(MY), XXXXXXX, X(THETA), XXXXXXX, KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), X(ZETA), X(OMIKRON), X(OMEGA), X(SAN), XXXXXXX, X(KAPPA), X(SIGMA), X(BETA), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ⛉   |   ⚐   |   ✉   |   ✆   |   🛈   |               |   ⏮   |   ⏯   |   ⏭   |   ◼   |   ⏏   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ☖   |   ♀   |   ♂   |   ✗   |   ✓   |               |   ♭   |   ♮   |   ♯   |   𝄴   |   𝄵   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ♙   |   ♢   |   ♡   |   ♤   |   ♧   |               |   𝅝   |   𝅗𝅥   |   𝅘𝅥   |   𝅘𝅥𝅮   |   𝅘𝅥𝅯   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |   ♖   |   ♘   |   ♗   |   ♕   |   ♔   |               |   𝄡   |   𝄞   |   𝄢   |   𝆮   |   𝆯   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE
 *                                 -------------------------------------------------
 */
	LAYOUT(
		KC_ESC, X(SHOGI_WD), X(FLAG_W), X(LETTER), X(PHONE), X(PLAY), X(FORWARD), X(STOP), X(EJECT), KC_DEL,
		KC_TAB, X(SHOGI_W), X(FEMALE), X(MALE), X(NO), X(NATURAL), X(SHARP), X(COMMON_T), X(ALLA_BR), KC_ENT,
		MO(1), X(PAWN_W), X(DIAMS_W), X(HEARTS_W), X(SPADES_W), X(HALF_N), X(QUART_N), X(EIGHTH_N), X(SIXT_N), MO(1),
		KC_LGUI, X(ROOK_W), X(KNIGHT_W), X(BISHOP_W), X(QUEEN_W), X(G_CLEF), X(F_CLEF), X(PEDAL), X(PEDAL_UP), KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), X(KING_W), X(CLUBS_W), X(YES), X(INFO), X(REWIND), X(FLAT), X(WHOLE_N), X(C_CLEF), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ⛊   |   ⚑   |  XXX  |  XXX  |  XXX  |               |   🔊   |   🔇   |   🔉   |  XXX  |  XXX  |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ☗   |   🔑   |   🔒   |   🔓   |  XXX  |               |   𝄚   |   𝄀   |   𝄁   |   𝄂   |   𝄌   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ♟   |   ♦   |   ♥   |   ♠   |   ♣   |               |   𝄻   |   𝄼   |   𝄽   |   𝄾   |   𝄿   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |   ♜   |   ♞   |   ♝   |   ♛   |   ♚   |               |   𝄆   |   𝄇   |   𝄋   |   𝄉   |   𝄊   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE
 *                                 -------------------------------------------------
 */
	LAYOUT(
		KC_ESC, X(SHOGI_BD), X(FLAG_B), XXXXXXX, XXXXXXX, X(SPEAKER_TG), X(SPEAKER_DN), XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, X(SHOGI_B), X(KEY), X(LOCK), X(LOCK_OPEN), X(BARLINE), X(BARLINE_D), X(BARLINE_FIN), X(CODA), KC_ENT,
		MO(1), X(PAWN_B), X(DIAMS_B), X(HEARTS_B), X(SPADES_B), X(HALF_P), X(QUART_P), X(EIGHTH_P), X(SIXT_P), MO(1),
		KC_LGUI, X(ROOK_B), X(KNIGHT_B), X(BISHOP_B), X(QUEEN_B), X(REPEAT_E), X(SEGNO), X(DALSEGNO), X(DACAPO), KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), X(KING_B), X(CLUBS_B), XXXXXXX, XXXXXXX, X(SPEAKER_UP), X(STAFF), X(WHOLE_P), X(REPEAT_S), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ∃   |   ∀   |   ≡   |   ≙   |   ≠   |               |   ≔   |   ⟶   |   ⟼   |   ∖   |   ∎   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ⋁   |   ⋀   |   ∨   |   ∧   |   ¬   |               |   ⇔   |   ⇐   |   ⇒   |   ⊤   |   ⊥   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ∑   |   ∏   |   +   |   ⋅   |   ∉   |               |   ∈   |   ≤   |   ≥   |   ∞   |   ε   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |   ⋃   |   ⋂   |   ∪   |   ∩   |   ⊈   |               |   ⊂   |   ⊆   |   ⊇   |   Ω   |   ∅   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE
 *                                 -------------------------------------------------
 */
	LAYOUT(
		KC_ESC, X(EXISTS), X(FORALL), X(EQUIV), X(CORRESP), X(TO), X(MAPSTO), X(SETMINUS), X(QED), KC_DEL,
		KC_TAB, X(OR_), X(AND_), X(OR), X(AND), X(IMPL_REV), X(IMPL), X(TOP), X(BOTTOM), KC_ENT,
		MO(1), X(SUM_), X(PROD_), S(KC_EQL), X(MDOT), X(LS_EQ), X(GR_EQ), X(INFTY), X(epsilon), MO(1),
		KC_LGUI, X(UNION_), X(INTERS_), X(UNION), X(INTERS), X(SUBSET), X(SUBSET_REV), X(OMEGA), X(EMPTYSET), KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), X(NOTSUBS), X(NOTIN), X(NOT), X(INEQUAL), X(DEFINE), X(BICOND), X(IN), X(PR_SUBSET), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ⌈   |   Δ   |   ℜ   |   ∇   |   ⌉   |               |   ⌊   |   ⟨   |   ℑ   |   ⟩   |   ⌋   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   ℚ   |  XXX  |   e   |   ℝ   |  XXX  |               |   ℤ   |   𝕌   |   i   |   𝒪   |   𝒫   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   𝔸   |   ∫   |   ∂   |   𝔽   |  XXX  |               |   ℍ   |  XXX  |   𝕂   |   ℓ   |  XXX  |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |   ℵ   |   ℶ   |   ℂ   |  XXX  |   𝔹   |               |   ℕ   |   𝟏   |   ℱ   |   ℋ   |   ℒ   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE
 *                                 -------------------------------------------------
 */
	LAYOUT(
		KC_ESC, X(LEFT_CEIL), X(DELTA), X(REAL_P), X(NABLA), X(BRA), X(IMAG_P), X(KET), X(RIGHT_FLOOR), KC_DEL,
		KC_TAB, X(Q_SET), XXXXXXX, X(e_FUN), X(R_SET), X(U_SET), X(i_UNIT), X(BIG_O), X(POWERSET), KC_ENT,
		MO(1), X(A_SET), X(INTEGRAL), X(PARTIAL), X(F_SET), XXXXXXX, X(K_SET), X(LENGTH), XXXXXXX, MO(1),
		KC_LGUI, X(ALEPH), X(BETH), X(C_SET), XXXXXXX, X(INDICATOR), X(FOURIER), X(HAMILTON), X(LAPLACE), KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), X(B_SET), XXXXXXX, XXXXXXX, X(RIGHT_CEIL), X(LEFT_FLOOR), X(Z_SET), X(H_SET), X(N_SET), KC_SPC),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ⌈   |   Δ   |   ℜ   |   ∇   |   ⌉   |               |   ⌊   |   ⟨   |   ℑ   |   ⟩   |   ⌋   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |   a   |   A   |   0   |   i   |   j   |               |   0   |   1   |   2   |   3   |   4   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   k   | _PSCR |   m   |   n   |   o   |               |   5   |   6   |   7   |   8   |   9   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |   ℵ   |   ℶ   |   r   |   s   |   t   |               |   a   |   𝟏   |   ℱ   |   ℋ   |   ℒ   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE
 *                                 -------------------------------------------------
 */
	LAYOUT(
		KC_ESC, X(LEFT_CEIL), X(DELTA), X(REAL_P), X(NABLA), X(BRA), X(IMAG_P), X(KET), X(RIGHT_FLOOR), KC_DEL,
		KC_TAB, KC_A, S(KC_A), KC_0, KC_I, KC_1, KC_2, KC_3, KC_4, KC_ENT,
		MO(1), KC_K, KC_PSCR, KC_M, KC_N, KC_6, KC_7, KC_8, KC_9, MO(1),
		KC_LGUI, X(ALEPH), X(BETH), KC_R, KC_S, X(INDICATOR), X(FOURIER), X(HAMILTON), X(LAPLACE), KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), KC_T, KC_O, KC_J, X(RIGHT_CEIL), X(LEFT_FLOOR), KC_0, KC_5, KC_A, KC_SPC),

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
	LAYOUT(
		KC_ESC, X(SUP1), X(SUP2), X(SUP3), X(SUP_MIN), S(KC_9), S(KC_5), S(KC_0), KC_RBRC, KC_DEL,
		KC_TAB, X(CURRENCY), S(KC_SCLN), X(DEGREE), X(MINUTE), KC_7, KC_8, KC_9, KC_SLSH, KC_ENT,
		MO(1), X(CENT), X(YEN), X(POUND), X(EURO), KC_4, KC_5, KC_6, KC_MINS, MO(1),
		TG(4), X(DIVISION), X(MICRO), X(OHM), X(BITCOIN), KC_1, KC_2, KC_3, S(KC_QUOT), KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, XXXXXXX, KC_COMM, MATH, SYMBOL, KC_DOT, MOUSE,
		MO(4), X(SECTION), S(KC_4), X(SECOND), X(ROOT), KC_LBRC, S(KC_8), S(KC_EQL), S(KC_6), KC_0),

/* -------------------------------------------------               -------------------------------------------------
 * |  Esc  |   ⊢   |   ⊧   |   ⃗   |   ̅   |   ͡   |               |   ≪   |   ≺   |   ↪   |   ≻   |   ≫   |  Del  |
 * -------------------------------------------------               -------------------------------------------------
 * |  Tab  |  XXX  |  XXX  |   △   |   □   |   ○   |               |   ⊙   |   ⊕   |   ⊖   |   ≈   |   ≅   | Enter |
 * -------------------------------------------------               -------------------------------------------------
 * |  L1   |   ⋉   |   ⋊   |   ⋈   |   ∡   |   ∠   |               |   ∘   |   ∗   |   ×   |   ±   |   ∓   |  L1   |
 * -------------------------------------------------               -------------------------------------------------
 * |  Gui  |   ⟕   |   ⟖   |   ⟗   |   ⊏   |   ⊑   |               |   ∝   |   ∥   |   ∦   |   ⊗   |   ∤   |BSpace |
 * -----------------------------------------------------------------------------------------------------------------
 *    NEO            GAME    GREEK |  L6   |  L4   |  Alt  | Ctrl  | Space |  L8   | MATH   SYMBOL           MOUSE
 *                                 -------------------------------------------------
 */
	LAYOUT(
		KC_ESC, X(RIGHT_TACK), X(MODELS), X(AB_VEC), X(AB_LINE), X(PRED), X(EMBED), X(SUCC), X(GREAT_GREAT), KC_DEL,
		KC_TAB, XXXXXXX, XXXXXXX, X(TRIANGLE), X(SQUARE), X(PLUS_OP), X(MINUS_OP), X(ROUGHLY), X(ISOMORPH), KC_ENT,
		MO(1), X(LTIMES), X(RTIMES), X(BOWTIE), X(M_ANGLE), X(AST_MID), X(TIMES), X(PLUS_MINUS), X(MINUS_PLUS), MO(1),
		KC_LGUI, X(LEFT_OUTER), X(RIGHT_OUTER), X(FULL_OUTER), X(SQ_LS), X(PARALLEL), X(NOT_PARA), X(TIMES_OP), X(NOT_DIV), KC_BSPC,
		TG(2), KC_LALT, GAME, GREEK, MO(6), MO(8), MATH, SYMBOL, KC_LCTRL, MOUSE,
		MO(4), X(SQ_LS_EQ), X(ANGLE), X(CIRCLE), X(AB_ARC), X(LESS_LESS), X(DOT_OP), X(CIRC_MID), X(PROP_TO), KC_SPC),

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
	LAYOUT(
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
	LAYOUT(
		KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
		KC_TAB, KC_MENU, LCTL(S(KC_TAB)), KC_UP, LCTL(KC_TAB), KC_BTN1, KC_MS_U, KC_BTN2, KC_SLCK, KC_ENT,
		KC_LSFT, KC_BSPC, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, KC_LSFT,
		KC_ENT, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_2, KC_3, KC_4, KC_5, KC_BSPC,
		TG(2), KC_LCTRL, GAME, GREEK, KC_LALT, KC_BTN2, MATH, SYMBOL, KC_BTN3, MOUSE,
		KC_SPC, KC_DEL, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, KC_1, KC_BTN1)
};

void matrix_init_user(void) {
	set_unicode_input_mode(UC_WINC);
}


void unicode_input_finish(void) {
  SEND_STRING("\n");
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
