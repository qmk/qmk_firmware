// Layer Keys
#define SPC_NAV LT(_NAV, KC_SPC)
#define BSP_SYM LT(_SYMBOL, KC_BSPC)
#define DEL_SYM LT(_SYMBOL, KC_DEL)
#define ESC_NUM LT(_NUMBER, KC_ESC)
#define TAB_SFT SFT_T(KC_TAB)
#define MIN_ARR LT(_ARRANGE, KC_MINS)
#define ENT_THU LT(_THUMB, KC_ENT)
#define EQL_THU LT(_THUMB, KC_EQL)

// magnet keycodes
#define M_LEFT LCA(KC_LEFT)
#define M_TOP LCA(KC_UP)
#define M_BOTT LCA(KC_DOWN)
#define M_RGHT LCA(KC_RGHT)

#define M_TOPL LCA(KC_U)
#define M_TOPR LCA(KC_I)
#define M_BOTL LCA(KC_J)
#define M_BOTR LCA(KC_K)

#define M_L13 LCA(KC_D)
#define M_L23 LCA(KC_E)
#define M_C13 LCA(KC_F)
#define M_R23 LCA(KC_T)
#define M_R13 LCA(KC_G)

#define M_1_6 LCA(KC_1)
#define M_2_6 LCA(KC_2)
#define M_3_6 LCA(KC_3)
#define M_4_6 LCA(KC_4)
#define M_5_6 LCA(KC_5)
#define M_6_6 LCA(KC_6)
#define M_L_56 LCA(KC_COMM)
#define M_R_56 LCA(KC_DOT)

#define M_NEXT LCAG(KC_RGHT)
#define M_PREV LCAG(KC_LEFT)

#define M_MAX LCA(KC_ENT)
#define M_CEN LCA(KC_C)
#define M_REST LCA(KC_BSPC)

// Modifier tapholds
#define T_SFT SFT_T(KC_T)
#define N_SFT SFT_T(KC_N)
#define Q_CTL CTL_T(KC_Q)
#define W_ALT ALT_T(KC_W)
#define F_GUI GUI_T(KC_F)
#define U_GUI GUI_T(KC_U)
#define Y_ALT ALT_T(KC_Y)
#define SCL_CTL CTL_T(KC_SCLN)

// Special characters
#define GBP A(KC_3)
#define EURO A(S(KC_2))

// Shortcuts
#define INPUT_L LCAG(KC_SPC)
#define TXT_PLS G(KC_PLUS)
#define TXT_MIN G(KC_MINS)
#define CUT G(KC_X)
#define COPY G(KC_C)
#define PASTE G(KC_V)
#define NXT_WIN G(KC_GRV)
#define EMOJI G(C(KC_SPC))  // brings up the emoji picker in OSX
#define VOLUP KC__VOLUP     // shorter naming for layout tidiness
#define VOLDOWN KC__VOLDOWN
#define MUTE KC_MUTE
#define LOCK G(C(KC_Q))        // Locks the screen on Mac OS
#define PREVTAB G(S(KC_LBRC))  // Previous Tab
#define NEXTTAB G(S(KC_RBRC))  // Next Tab
#define SCN_CAP G(S(KC_5))     // Screen capture
#define CHR_PRF G(S(KC_M))     // Switching Google Chrome profiles
#define MED_DSH S(A(KC_MINS))  // medium dash
#define POWERDN LCAG(KC_POWER)