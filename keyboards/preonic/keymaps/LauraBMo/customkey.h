
/* My alias to make a more readable keymap */

/* Control on hold and *** on tap */
#define CTL_LBR LCTL_T(KC_LBRC)
#define CTL_SPC RCTL_T(KC_SPC)
#define CTL_BSLS RCTL_T(KC_BSLS)

/* Shift on hold, (***) on tap */
#define SFT_QUOT RSFT_T(KC_QUOT)
/* #define SFT_CCED RSFT_T(ES_CCED) */
/* #define SFT_GRV LSFT_T(ES_GRV) */
#define ES_SLCB LSFT_T(ES_LCBR)
#define ES_SQUT RSFT_T(ES_QUOT)
#define ES_GCOL LGUI_T(ES_COLN)
#define CTL_CCED RCTL_T(ES_CCED)

/* Long keycodes to print screen */
#define KC_CPTW LGUI(LSFT(LCTL(KC_3)))  // Capture window
#define KC_CPTP LGUI(LSFT(LCTL(KC_4)))  // Capture portion of screen


/* Greek alphabet, see unicodes.h */
#define GK_ALPH XP(ALPHA, CALPHA)
#define GK_BETA XP(BETA, CBETA)
#define GK_GMMA XP(GAMMA, CGAMMA)
#define GK_DLTA XP(DELTA, CDELTA)
#define GK_EPS XP(EPSILON, CEPSILON)
#define GK_ZETA XP(ZETA, CZETA)
#define GK_ETA XP(ETA, CETA)
#define GK_THTA XP(THETA, CTHETA)
#define GK_IOTA XP(IOTA, CIOTA)
#define GK_KPPA XP(KAPPA, CKAPPA)
#define GK_LMBD XP(LAMBDA, CLAMBDA)
#define GK_MU XP(MU, CMU)
#define GK_NU XP(NU, CNU)
#define GK_XI XP(XI, CXI)
#define GK_OMI XP(OMICRON, COMICRON)
#define GK_PI XP(PI, CPI)
#define GK_RHO XP(RHO, CRHO)
#define GK_SGMA XP(SIGMA, CSIGMA)
#define GK_TAU XP(TAU, CTAU)
#define GK_UPS XP(UPSILON, CUPSILON)
#define GK_PHI XP(PHI, CPHI)
#define GK_CHI XP(CHI, CCHI)
#define GK_PSI XP(PSI, CPSI)
#define GK_OMGA XP(OMEGA, COMEGA)

/* Math symbols, for julia */
#define MTH_IN XP(MATHIN, MATHNI)
