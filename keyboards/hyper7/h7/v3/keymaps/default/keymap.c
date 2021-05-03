#include QMK_KEYBOARD_H

// Brevity defines
#define FT KC_TRNS

// modifier masks used for determining modifier actuation within macros
#define MODS_SHIFT_MASK   (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))

// Clear mods, perform action, restore mods
#define CLEAN_MODS(action) {       \
        uint8_t mods = get_mods(); \
        clear_mods();              \
        action;                    \
        set_mods(mods);            \
    }

// UNICODEMAP_ENABLE
enum unicode_names {
    AT_SYMBOL,
    GBP,
    JPY,
    EURO,
    PLUS_MINUS,
    QUOTATION_MARK,
    TILDE_OPERATOR,
    SINGLE_RIGHT_POINTING_ANGLE_QUOTATION_MARK,
    SINGLE_LEFT_POINTING_ANGLE_QUOTATION_MARK,
    BACKTICK,
    DQUOTE_OPEN,
    DQUOTE_CLOSE,
    PRIME,
    PIPE,

// APL
    N_ARY_LOGICAL_AND,
    N_ARY_LOGICAL_OR,
    N_ARY_INTERSECT,
    N_ARY_UNION,
    SUBSET_OF,
    SUPERSET_OF,
    FORALL,
    LEMNISCATE,
    THERE_EXISTS,
    PARTIAL_DIFFERENTIAL,
    UP_TACK,
    DOWN_TACK,
    RIGHT_TACK,
    LEFT_TACK,
    UPWARDS_ARROW,
    DOWNARDS_ARROW,
    LEFTWARDS_ARROW,
    RIGHTWARDS_ARROW,
    LEFTRIGHT_ARROW,
    LEFT_FLOOR,
    LEFT_CEILING,
    NOT_EQUAL_TO,
    ASYMPTOTICALLY_EQUAL_TO,
    NOT_ASYMPTOTICALLY_EQUAL_TO,
    LESS_THAN_OR_EQUAL,
    GREATER_THAN_OR_EQUAL,

// [main board] row 0
    CONTOUR_INTEGRAL,
    COPTIC_LC_DEI,
    DOUBLE_DAGGER,
    NABLA,
    CENT,
    DEGREE,
    APL_QUAD,
    DIVISION,
    MULTIPLICATION,
    PILCROW,
    LARGE_CIRCLE,
    HORIZONTAL_BAR,
    APPROXIMATELY_EQUAL_TO,
    DOUBLE_VERTICAL_LINE,
    SQUARE_IMAGE_OF,
    SQUARE_ORIGINAL_OF,


// Greek
// [main board] row 1
    GREEK_LC_THETA,
    GREEK_UC_THETA,
    GREEK_LC_OMEGA,
    GREEK_UC_OMEGA,
    GREEK_LC_EPSILON,
    GREEK_UC_EPSILON,
    GREEK_LC_RHO,
    GREEK_UC_RHO,
    GREEK_UC_TAU,
    GREEK_LC_TAU,
    GREEK_UC_PSI,
    GREEK_LC_PSI,
    GREEK_LC_UPSILON,
    GREEK_UC_UPSILON,
    GREEK_LC_IOTA,
    GREEK_UC_IOTA,
    GREEK_LC_OMICRON,
    GREEK_UC_OMICRON,
    GREEK_LC_PI,
    GREEK_UC_PI,
    MATHEMATICAL_LEFT_WHITE_SQUARE_BRACKET,
    MATHEMATICAL_RIGHT_WHITE_SQUARE_BRACKET,

// [main board] row 2
    GREEK_LC_ALPHA,
    GREEK_UC_ALPHA,
    GREEK_LC_SIGMA,
    GREEK_UC_SIGMA,
    GREEK_LC_DELTA,
    GREEK_UC_DELTA,
    GREEK_LC_PHI,
    GREEK_UC_PHI,
    GREEK_LC_GAMMA,
    GREEK_UC_GAMMA,
    GREEK_LC_ETA,
    GREEK_UC_ETA,
    GREEK_LC_YOT,
    GREEK_UC_YOT,
    GREEK_LC_KAPPA,
    GREEK_UC_KAPPA,
    GREEK_LC_LAMDA,
    GREEK_UC_LAMDA,
    TWO_DOT_LEADER,
    BULLET,

// [main board] row 3
    GREEK_LC_ZETA,
    GREEK_UC_ZETA,
    GREEK_LC_XI,
    GREEK_UC_XI,
    GREEK_LC_CHI,
    GREEK_UC_CHI,
    GREEK_LC_FINAL_SIGMA,
    // GREEK_UC_SIGMA, // Final sigma doesn't differentiate the capitalised form
    GREEK_LC_BETA,
    GREEK_UC_BETA,
    GREEK_LC_NU,
    GREEK_UC_NU,
    GREEK_LC_MU,
    GREEK_UC_MU,
    MUCH_LESS_THAN,
    MUCH_GREATER_THAN,
    INTEGRAL,
};

const uint32_t PROGMEM unicode_map[] = {
// Unicode char definitions
    [AT_SYMBOL] = 0x0040,
    [GBP] = 0x00A3,
    [JPY] = 0x00A5,
    [EURO] = 0x20AC,
    [PLUS_MINUS] = 0x00B1,
    [QUOTATION_MARK] = 0x0022,
    [TILDE_OPERATOR] = 0x223C,
    [SINGLE_RIGHT_POINTING_ANGLE_QUOTATION_MARK] = 0x203A,
    [SINGLE_LEFT_POINTING_ANGLE_QUOTATION_MARK] = 0x2039,
    [BACKTICK] = 0x2018,
    [DQUOTE_OPEN] = 0x201C,
    [DQUOTE_CLOSE] = 0x201D,
    [PRIME] = 0x2019,
    [PIPE] = 0x2502,

// APL
    [N_ARY_LOGICAL_AND] = 0x22C0,
    [N_ARY_LOGICAL_OR] = 0x22C1,
    [N_ARY_INTERSECT] = 0x22C2,
    [N_ARY_UNION] = 0x22C3,
    [SUBSET_OF] = 0x2282,
    [SUPERSET_OF] = 0x2283,
    [FORALL] = 0x2200,
    [LEMNISCATE] = 0x221E, // ∞
    [THERE_EXISTS] = 0x2203,
    [PARTIAL_DIFFERENTIAL] = 0x2202,
    [UP_TACK] = 0x22A5,
    [DOWN_TACK] = 0x22A4,
    [RIGHT_TACK] = 0x22A2,
    [LEFT_TACK] = 0x22A3,
    [UPWARDS_ARROW] = 0x2191,
    [DOWNARDS_ARROW] = 0x2193,
    [LEFTWARDS_ARROW] = 0x2190,
    [RIGHTWARDS_ARROW] = 0x2192,
    [LEFTRIGHT_ARROW] = 0x2194,
    [LEFT_FLOOR] = 0x230A,
    [LEFT_CEILING] = 0x2308,
    [NOT_EQUAL_TO] = 0x2260,
    [ASYMPTOTICALLY_EQUAL_TO] = 0x2243,
    [NOT_ASYMPTOTICALLY_EQUAL_TO] = 0x2261,
    [LESS_THAN_OR_EQUAL] = 0x2264,
    [GREATER_THAN_OR_EQUAL] = 0x2265,

// Greek
// [main board] row 0
    [CONTOUR_INTEGRAL] = 0x222E,
    [COPTIC_LC_DEI] = 0x03EF,
    [DOUBLE_DAGGER] = 0x2021,
    [NABLA] = 0x2207,
    [CENT] = 0x00A2,
    [DEGREE] = 0x00B0,
    [APL_QUAD] = 0x2395,
    [DIVISION] = 0x00F7,
    [MULTIPLICATION] = 0x00D7,
    [PILCROW] = 0x00B6,
    [LARGE_CIRCLE] = 0x25EF,
//  [THREE_EM_DASH] = 0x2E3B,
    [HORIZONTAL_BAR] = 0x2015,
    [APPROXIMATELY_EQUAL_TO] = 0x2248,
    [DOUBLE_VERTICAL_LINE] = 0x2016,
    [SQUARE_IMAGE_OF] = 0x228F,
    [SQUARE_ORIGINAL_OF] = 0x2290,


// [main board] row 1
    [GREEK_LC_THETA] = 0x03B8,
    [GREEK_UC_THETA] = 0x0398,
    [GREEK_LC_OMEGA] = 0x03C9,
    [GREEK_UC_OMEGA] = 0x03A9,
    [GREEK_LC_EPSILON] = 0x03B5,
    [GREEK_UC_EPSILON] = 0x0395,
    [GREEK_LC_RHO] = 0x03C1,
    [GREEK_UC_RHO] = 0x03A1,
    [GREEK_LC_TAU] = 0x03C4,
    [GREEK_UC_TAU] = 0x03A4,
    [GREEK_LC_PSI] = 0x03C8,
    [GREEK_UC_PSI] = 0x03A8,
    [GREEK_LC_UPSILON] = 0x03C5,
    [GREEK_UC_UPSILON] = 0x03A5,
    [GREEK_LC_IOTA] = 0x03B9,
    [GREEK_UC_IOTA] = 0x0399,
    [GREEK_LC_OMICRON] = 0x03BF,
    [GREEK_UC_OMICRON] = 0x039F,
    [GREEK_LC_PI] = 0x03C0,
    [GREEK_UC_PI] = 0x03A0,
    [MATHEMATICAL_LEFT_WHITE_SQUARE_BRACKET] = 0x27E6,
    [MATHEMATICAL_RIGHT_WHITE_SQUARE_BRACKET] = 0x27E7,

// [main board] row 2
    [GREEK_LC_ALPHA] = 0x03B1,
    [GREEK_UC_ALPHA] = 0x0391,
    [GREEK_LC_SIGMA] = 0x03C3,
    [GREEK_UC_SIGMA] = 0x03A3,
    [GREEK_LC_DELTA] = 0x03B4,
    [GREEK_UC_DELTA] = 0x0394,
    [GREEK_LC_PHI] = 0x03C6,
    [GREEK_UC_PHI] = 0x03A6,
    [GREEK_LC_GAMMA] = 0x03B3,
    [GREEK_UC_GAMMA] = 0x0393,
    [GREEK_LC_ETA] = 0x03B7,
    [GREEK_UC_ETA] = 0x0397,
    [GREEK_LC_YOT] = 0x03F3,
    [GREEK_UC_YOT] = 0x037F,
    [GREEK_LC_KAPPA] = 0x03BA,
    [GREEK_UC_KAPPA] = 0x039A,
    [GREEK_LC_LAMDA] = 0x03BB,
    [GREEK_UC_LAMDA] = 0x039B,
    [TWO_DOT_LEADER] = 0x2025,
    [BULLET] = 0x2022,

// [main board] row 3
    [GREEK_LC_ZETA] = 0x03B6,
    [GREEK_UC_ZETA] = 0x0396,
    [GREEK_LC_XI] = 0x03BE,
    [GREEK_UC_XI] = 0x039E,
    [GREEK_LC_CHI] = 0x03C7,
    [GREEK_UC_CHI] = 0x03A7,
    [GREEK_LC_FINAL_SIGMA] = 0x03C2,
    // [GREEK_UC_SIGMA] = 0x03A3, // Final sigma doesn't differentiate the capitalised form
    [GREEK_LC_BETA] = 0x03B2,
    [GREEK_UC_BETA] = 0x0392,
    [GREEK_LC_NU] = 0x03BD,
    [GREEK_UC_NU] = 0x039D,
    [GREEK_LC_MU] = 0x03BC,
    [GREEK_UC_MU] = 0x039C,
    [MUCH_LESS_THAN] = 0x226A,
    [MUCH_GREATER_THAN] = 0x226B,
    [INTEGRAL] = 0x222B,
};

/*
 * Layer definitions.
 */
#define _BASE 0   // Base layer
#define _APL 1    // APL symbols
#define _GREEK 2  // Greek symbols
#define _FN 3     // FN & media keys

enum custom_keycodes {
    // daughter board R1
    H_HELP = SAFE_RANGE,
    H_MACRO,
    H_TERMINAL,
    H_QUOTE,
    H_OVERSTRIKE,
    H_CLEAR_INPUT,
    H_CLEAR_SCREEN,
    H_HOLD_OUTPUT,
    H_STOP_OUTPUT,
    H_ABORT,
    H_BREAK,
    H_RESUME,
    H_CALL,

    // daughter board R2
    H_LOCAL,
    H_NETWORK,
    H_SYSTEM,
    H_REFRESH,
    H_BUFFER,
    H_SQUARE,
    H_CIRCLE,
    H_TRIANGLE,
    H_DIAMOND,
    H_REPEAT,
    H_TRANSMIT,
    H_STATUS,
    H_SUSPEND,

    // daughter board r3
    H_CLOSE,
    H_OPEN,
    H_COMPLETE,

    // main board r1
    H_WRITE,
    H_DOUBLE_QUOTE__PLUS_MINUS,
    H_COLON__TILDE,
    H_L_BRACE__L_CHEVRON,
    H_R_BRACE__R_CHEVRON,

    // main board r2
    H_MARK,
    H_LEFT_PAREN__LEFT_BRACKET,
    H_RIGHT_PAREN__RIGHT_BRACKET,

    // main board r3
    H_SELECT,
    H_DEBUG,
    H_SEMI_COLON__BACK_TICK,
    H_TICK__QUOTE,
    H_LINE,
    H_PAGE,

    // main board r4
    H_TTY,
    H_LOCK, // lock machine? a little close to other used keys on a single keypress?

    // main board r5
    H_EOF,
    H_7BIT,
    H_CIRCLE_SM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* _BASE: Base Layer(Default)
     * ,-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
     * |   Help    |   Macro   |#| Terminal  |   Quote   | OverStrike| ClearInput|ClearScreen|HoldOutput | StopOutput|   Abort   |   Break   |  Resume   |#|   Call    |   RESET   |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |   Local   |  Network  |#|  System   |  Refresh  |   Buffer  |   Square  |   Circle  | Triangle  |  Diamond  |   Repeat  |  Transmit |  Status   |#|  Suspend  |  CapsLock |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F1  | F2  |Close|Open |#|   Esc     |  ?  |  !  |  @  |  £  |  €  |  ¥  |  '  |  “  |  ”  |  '  |  _  |  <  |  >  |  |  |  {  |  }  | Complete  |#|  ^  |  %  |  #  |  $  |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |###############################################################################################################################################################################|
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F3  | F4  |Find |Write|#|Compose | "/± | :/~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  |  | {/‹  | }/›  | Undo   |#|  ~  |  /  |  *  |  -  |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F5  | F6  |Mark |Undo |#|Paste|  Cut   |Tab     |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  (  |  )  | Bspace | Clear  |Begin|#|  7  |  8  |  9  |  +  |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F7  | F8  |Selec|Debug|#|Function|  Mode  |  Top   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  | Return |  Line  |  Page  |#|  4  |  5  |  6  |  &  |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F9  | F10 | TTY |LOCK |#|Begin| End | Symbol | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Shift  | Symbol |  Up | End |#|  1  |  2  |  3  |  =  |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F11 | F12 |Home | EOF |#|Prev |Next |7bit | Alt | Hyper  | Spr |  Ctrl  | Space |TRNS |  Del   |  Ctrl  | Spr  | Hyper  |Meta |Left |Down |Right|#| Del |  0  |  .  | Run |
     * `-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
     *  Incomplete mappings
     *  r1: H_MACRO, H_TERMINAL, H_OVERSTRIKE, H_HOLD_OUTPUT, H_STOP_OUTPUT, H_CALL
     *  r2: H_LOCAL, H_NETWORK, H_SYSTEM, H_REFRESH, H_BUFFER, H_SQUARE, H_CIRCLE, H_TRIANGLE, H_DIAMOND, H_REPEAT, H_TRANSMIT, H_STATUS
     *  r3: H_COMPLETE
     *
     *  r1: H_FIND, H_WRITE
     *  r2: H_MARK
     *  r3: H_SELECT, H_DEBUG, H_LINE
     *  r4: H_TTY
     *  r2: H_7BIT, H_CIRCLE_SM
     */
    [_BASE] = LAYOUT_h7v3_183(
        H_HELP,            H_MACRO,           H_TERMINAL,           H_QUOTE,             H_OVERSTRIKE,            H_CLEAR_INPUT,           H_CLEAR_SCREEN,                 H_HOLD_OUTPUT,             H_STOP_OUTPUT,          H_ABORT,           H_BREAK,              H_RESUME,            H_CALL,              KC_NLCK,           //14
        H_LOCAL,           H_NETWORK,         H_SYSTEM,             H_REFRESH,           H_BUFFER,                H_SQUARE,                H_CIRCLE,                       H_TRIANGLE,                H_DIAMOND,              H_REPEAT,          H_TRANSMIT,           H_STATUS,            H_SUSPEND,           KC_CLCK,           //14
        KC_F1,   KC_F2,    H_CLOSE,  H_OPEN,  KC_ESC,               KC_QUES,    KC_EXLM, X(AT_SYMBOL),    X(GBP), X(EURO),        X(JPY),  X(BACKTICK),    X(DQUOTE_OPEN), X(DQUOTE_CLOSE), X(PRIME), KC_UNDS,       KC_LABK, KC_RABK,  X(PIPE), KC_LCBR,    KC_RCBR,  H_COMPLETE,          KC_CIRC,   KC_PERC,  KC_HASH,  KC_DLR,  //26

        KC_F3,   KC_F4,    KC_FIND,  H_WRITE, KC_LEAD,  H_DOUBLE_QUOTE__PLUS_MINUS, H_COLON__TILDE,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,    KC_6,     KC_7,    KC_8,     KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_NUBS, H_L_BRACE__L_CHEVRON,  H_R_BRACE__R_CHEVRON,  KC_UNDO,    KC_TILD,   KC_SLSH,  KC_PAST,  KC_PMNS, //27
        KC_F5,   KC_F6,    KC_EXLM,  KC_UNDO, KC_PASTE, KC_CUT ,  KC_TAB ,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,    KC_Y,     KC_U,    KC_I,     KC_O,    KC_P,     KC_LPRN,  KC_RPRN, KC_BSPC, KC_CLEAR, KC_HOME,                                                                 KC_P7,     KC_P8,    KC_P9,    KC_PPLS, //26
        KC_F7,   KC_F8,    KC_SELECT,H_DEBUG, MO(_FN), KC_NO,       MO(_APL), KC_A,     KC_S,     KC_D,     KC_F,     KC_G,    KC_H,     KC_J,    KC_K,     KC_L,    H_SEMI_COLON__BACK_TICK,  KC_QUOT,  KC_ENT , H_LINE, H_PAGE,                                                           KC_P4,     KC_P5,    KC_P6,    KC_AMPR, //25
        KC_F9,   KC_F10,   H_TTY,    KC_LOCK, KC_HOME,  KC_END ,  MO(_GREEK), KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,     KC_N,    KC_M,     KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT, MO(_GREEK),KC_UP,    KC_END,                                                              KC_P1,     KC_P2,    KC_P3,    KC_EQL,  //26
        KC_F11,  KC_F12,   KC_HOME,  H_EOF,   KC_MPRV,  KC_MNXT,  H_7BIT,  KC_LALT,  KC_HYPR,  KC_LGUI,  KC_LCTL,  KC_SPC,  H_CIRCLE_SM,  KC_DEL,  KC_RCTL,  KC_RGUI, KC_HYPR,  KC_RGUI,  KC_LEFT, KC_DOWN, KC_RGHT,                                                                        KC_DEL,    KC_P0,    KC_PDOT,  KC_ENTER //25
    ),
    /* _APL: Cadet Symbol Layer (Default)
     * ,-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
     * |           |           |#|           |           |           |           |           |           |           |           |           |           |#|           |           |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |           |           |#|           |           |           |           |           |           |           |           |           |           |#|           |           |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|           |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |           |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |###############################################################################################################################################################################|
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|        |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |        |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|     |        |        |  ⋀  |  ⋁  |  ⋂  |  ⋃  |  ⊂  |  ⊃  |  ∀  |  ∞  |  ∎  |  ∂  |     |     |        |        |     |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|        |        |        |  ⊥  |  ⊤  |  ⊢  |  ⊣  |  ↑  |  ↓  |  ←  |  →  |  ↔  |  ;  |  '  |        |        |        |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|     |     |        |        |  ⌊  |  ⌈  |  ≠  |  ≃  |  ≡  |  ≤  |  ≥  |     |     |     |        |        |     |     |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|     |     |     |     |        |     |        |        |     |        |        |     |        |     |     |     |     |#|     |     |     |     |
     * `-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_APL] = LAYOUT_h7v3_183(
        FT,               FT,                 FT,                 FT,                 FT,                 FT,                FT,                FT,                 FT,                FT,               FT,                 FT,                  FT,                FT,
        FT,               FT,                 FT,                 FT,                 FT,                 FT,                FT,                FT,                 FT,                FT,               FT,                 FT,                  FT,                FT,
        FT,      FT,      FT,       FT,       FT,                 FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,       FT,      FT,      FT,       FT,       FT,                  FT,      FT,       FT,      FT,

        FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,       FT,       FT,                  FT,      FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       FT,       FT,  X(N_ARY_LOGICAL_AND), X(N_ARY_LOGICAL_OR), X(N_ARY_INTERSECT), X(N_ARY_UNION), X(SUBSET_OF),X(SUPERSET_OF), X(FORALL),X(LEMNISCATE), X(THERE_EXISTS),X(PARTIAL_DIFFERENTIAL),      FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       FT,       FT,  X(UP_TACK), X(DOWN_TACK), X(RIGHT_TACK), X(LEFT_TACK), X(UPWARDS_ARROW),X(DOWNARDS_ARROW), X(LEFTWARDS_ARROW),X(RIGHTWARDS_ARROW), X(LEFTRIGHT_ARROW),     FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,  X(LEFT_FLOOR), X(LEFT_CEILING), X(NOT_EQUAL_TO), X(ASYMPTOTICALLY_EQUAL_TO),X(NOT_ASYMPTOTICALLY_EQUAL_TO), X(LESS_THAN_OR_EQUAL),X(GREATER_THAN_OR_EQUAL),      FT,      FT,       FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT
    ),

    /* _GREEK: lower/upper case greek (needs shift modifier application for upper case chars) from codepage U0370.pdf \
     * ,-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
     * |           |           |#|           |           |           |           |           |           |           |           |           |           |#|           |           |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |           |           |#|           |           |           |           |           |           |           |           |           |           |#|           |           |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|           |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |           |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |###############################################################################################################################################################################|
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|        |  ∮  |     |  ϯ  |  ‡  |  ∇  |  ¢  |  °  |  ⎕  |  ÷  |  ×  |  ¶  |  ◯  |  ―  |  ≈  |  ‖  |  ⊏  |  ⊐  |        |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|     |        |        | θ/Θ | ω/Ω | ε/Ε | ρ/Ρ | τ/Τ | ψ/Ψ | υ/Υ | ι/Ι | ο/Ο | π/Π |  ⟦  |  ⟧  |        |        |      |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|        |        |        | α/Α | σ/Σ | δ/Δ | φ/Φ | γ/Γ | η/Η  | ϳ/Ϳ | κ/Κ | λ/Λ |  ‥  |  •  |        |        |        |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|     |     |         | SHIFT | ζ/Ζ  | ξ/Ξ | χ/Χ | ς/Σ | β/Β | ν/Ν | μ/Μ |  ≪  |  ≫  |  ∫  |        |        |     |     |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|     |     |     |     |        |     |        |        |     |        |        |     |        |     |     |     |     |#|     |     |     |     |
     * `-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_GREEK] = LAYOUT_h7v3_183(
        FT,               FT,                 FT,                 FT,                 FT,                 FT,                FT,                FT,                 FT,                FT,               FT,                 FT,                  FT,                FT,
        FT,               FT,                 FT,                 FT,                 FT,                 FT,                FT,                FT,                 FT,                FT,               FT,                 FT,                  FT,                FT,
        FT,      FT,      FT,       FT,       FT,                 FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,       FT,       FT,      FT,      FT,      FT,       FT,       FT,                  FT,      FT,       FT,      FT,

        FT,      FT,      FT,       FT,       FT, X(CONTOUR_INTEGRAL),  FT,  X(COPTIC_LC_DEI), X(DOUBLE_DAGGER), X(NABLA), X(CENT), X(DEGREE), X(APL_QUAD), X(DIVISION), X(MULTIPLICATION), X(PILCROW), X(LARGE_CIRCLE), X(HORIZONTAL_BAR), X(APPROXIMATELY_EQUAL_TO), X(DOUBLE_VERTICAL_LINE), X(SQUARE_IMAGE_OF), X(SQUARE_ORIGINAL_OF),       FT,       FT,                 FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       FT,       FT,  XP(GREEK_LC_THETA, GREEK_UC_THETA), XP(GREEK_LC_OMEGA, GREEK_UC_OMEGA), XP(GREEK_LC_EPSILON, GREEK_UC_EPSILON), XP(GREEK_LC_RHO, GREEK_UC_RHO), XP(GREEK_LC_TAU, GREEK_UC_TAU),XP(GREEK_LC_PSI, GREEK_UC_PSI), XP(GREEK_LC_UPSILON, GREEK_UC_UPSILON),XP(GREEK_LC_IOTA, GREEK_UC_IOTA), XP(GREEK_LC_OMICRON, GREEK_UC_OMICRON),XP(GREEK_LC_PI, GREEK_UC_PI), X(MATHEMATICAL_LEFT_WHITE_SQUARE_BRACKET), X(MATHEMATICAL_RIGHT_WHITE_SQUARE_BRACKET),     FT,      FT,      FT,                            FT,      FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       FT,       FT,  XP(GREEK_LC_ALPHA, GREEK_UC_ALPHA), XP(GREEK_LC_SIGMA, GREEK_UC_SIGMA), XP(GREEK_LC_DELTA, GREEK_UC_DELTA), XP(GREEK_LC_PHI, GREEK_UC_PHI), XP(GREEK_LC_GAMMA, GREEK_UC_GAMMA),XP(GREEK_LC_ETA, GREEK_UC_ETA), XP(GREEK_LC_YOT, GREEK_UC_YOT),XP(GREEK_LC_KAPPA, GREEK_UC_KAPPA), XP(GREEK_LC_LAMDA, GREEK_UC_LAMDA), X(TWO_DOT_LEADER), X(BULLET),      FT,      FT,      FT,                                     FT,      FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       FT,       FT,  FT,  XP(GREEK_LC_ZETA, GREEK_UC_ZETA), XP(GREEK_LC_XI, GREEK_UC_XI), XP(GREEK_LC_CHI, GREEK_UC_CHI), XP(GREEK_LC_FINAL_SIGMA, GREEK_UC_SIGMA),XP(GREEK_LC_BETA, GREEK_UC_BETA), XP(GREEK_LC_NU, GREEK_UC_NU),XP(GREEK_LC_MU, GREEK_UC_MU), X(MUCH_LESS_THAN),X(MUCH_GREATER_THAN), X(INTEGRAL),      FT,      FT,      FT,      FT,                            FT,      FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,                                     FT,      FT,       FT,      FT
    ),

    /* _FN: Function layer, media & LED mods
     * ,-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
     * |           |           |#|           |           |           |           |           |           |           |           |           |           |#|           |   Reset   |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |           |           |#|           |           |           |           |           |           |           |           |           |           |#|           |           |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|           |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |           |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |###############################################################################################################################################################################|
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|        |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |        |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|     |        |        |     |UC_M_WI|     |     |     |     |     |     |     |     |     |     |        |        |      |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|        |UC_MOD|        |     |     |     |     |     |     |     |     |UC_M_LN|     |     |        |        |        |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |H_LOCK|#|     |     |         |       |     |     |UC_M_WC|     |     |     |UC_M_MA|     |     |     |        |        |     |     |#|     |     |     |     |
     * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |     |     |     |     |#|     |     |     |     |        |     |        |        |     |        |        |     |        |     |     |     |     |#|     |     |     |     |
     * `-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [_FN] = LAYOUT_h7v3_183(
        FT,               FT,                 FT,                 FT,                 FT,                 FT,                 FT,                 FT,                 FT,                 FT,               FT,                 FT,                  FT,                RESET,
        FT,               FT,                 FT,                 FT,                 FT,                 FT,                 FT,                 FT,                 FT,                 FT,               FT,                 FT,                  FT,                FT,
        FT,      FT,      FT,       FT,       FT,                 FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,       FT,       FT,                  FT,      FT,       FT,      FT,

        FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,       FT,       FT,                  FT,      FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       UC_M_WI,  FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       UC_MOD,   FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       UC_M_LN,  FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT,
        FT,      FT,      FT,       H_LOCK,   FT,       FT,       FT,       FT,       FT,       FT,       UC_M_WC,  FT,       FT,       FT,       UC_M_MA,  FT,       FT,       FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
        FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT
    )
};

// activate leader functionality
LEADER_EXTERNS();

void matrix_scan_keymap(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // slash :: find
    SEQ_ONE_KEY(KC_SLASH) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_F)));
    }

    // Copy word
    SEQ_TWO_KEYS(KC_W, KC_C) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_LEFT))SS_LSFT(SS_LCTRL(SS_TAP(X_RIGHT)))SS_LCTRL(SS_TAP(X_C)));
    }
    // Copy line
    SEQ_TWO_KEYS(KC_L, KC_C) {
      SEND_STRING(SS_TAP(X_HOME)SS_LSFT(SS_TAP(X_END))SS_LCTRL(SS_TAP(X_C)));
    }
    // Copy all
    SEQ_TWO_KEYS(KC_A, KC_C) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_A)SS_TAP(X_C)));
    }
  }

}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      // [daughter board] row 1 POS key macros
      case H_HELP:
        send_string("[HELP] key");
        return false;
      case H_MACRO:
        send_string("[MACRO] key");
        return false;
      case H_TERMINAL:
        send_string("[TERMINAL] key");
        return false;
      case H_QUOTE:
        // wraps selected (editable) text in quotation marks
        send_string(SS_LCTL(SS_TAP(X_X))SS_TAP(X_QUOTE)SS_LCTL(SS_TAP(X_V))SS_TAP(X_QUOTE));
        return false;
      case H_OVERSTRIKE:
        // toggles insert/overstrike
        send_string(SS_TAP(X_INSERT));
        return false;
      case H_CLEAR_INPUT:
        // terminal: clears from the cursor to the beginning of the current command
        send_string(SS_LCTL(SS_TAP(X_U)));
        return false;
      case H_CLEAR_SCREEN:
        send_string(SS_LCTL(SS_TAP(X_L)));
        // ^ linux/osx shell specific, for windows command replace with
        // send_string(SS_TAP(X_C)SS_TAP(X_L)SS_TAP(X_S)SS_TAP(KC_ENTER));
        return false;
      case H_HOLD_OUTPUT:
        send_string("[HOLD OUTPUT] key");
        return false;
      case H_STOP_OUTPUT:
        send_string("[STOP OUTPUT] key");
        return false;
      case H_ABORT:
        send_string(SS_LCTL(SS_TAP(X_C)));
        return false;
      case H_BREAK:
        send_string(SS_TAP(X_PAUSE));
        return false;
      case H_RESUME:
        send_string(SS_TAP(X_F)SS_TAP(X_G)SS_TAP(X_ENTER));
        return false;
      case H_CALL:
        send_string("[CALL] key");
        return false;

      // [daughter board] row 2 POS key macros
      case H_LOCAL:
        send_string("[LOCAL] key");
        return false;
      case H_NETWORK:
        send_string("[NETWORK] key");
        return false;
      case H_SYSTEM:
        send_string("[SYSTEM] key");
        return false;
      case H_REFRESH:
        send_string(SS_LCTL(SS_TAP(X_R)));
        return false;
      case H_BUFFER:
        send_string("[BUFFER] key");
        return false;
      case H_SQUARE:
        send_string("[SQUARE] key");
        return false;
      case H_CIRCLE:
        send_string("[CIRCLE] key");
        return false;
      case H_TRIANGLE:
        send_string("[TRIANGLE] key");
        return false;
      case H_DIAMOND:
        send_string("[DIAMOND] key");
        return false;
      case H_REPEAT:
        send_string("[REPEAT] key");
        return false;
      case H_TRANSMIT:
        send_string("[TRANSMIT] key");
        return false;
      case H_STATUS:
        send_string("[STATUS] key");
        return false;
      case H_SUSPEND:
        send_string(SS_LCTL(SS_TAP(X_Z)));
        return false;

      // [daughter board] row 3
      case H_CLOSE:
        // ctrl-w: closes a tab/panel within an application
        send_string(SS_LCTL(SS_TAP(X_W)));
        return false;
      case H_OPEN:
        // ctrl-n: opens a tab/panel
        send_string(SS_LCTL(SS_TAP(X_N)));
        return false;
      case H_COMPLETE:
        // tab tab: bash command line completion
        send_string(SS_TAP(X_TAB)SS_TAP(X_TAB));
        return false;

      // [main board] row 1
      case H_WRITE:
        send_string(SS_LCTL(SS_TAP(X_S)));
        return false;

      case H_DOUBLE_QUOTE__PLUS_MINUS:
        if (get_mods() & MODS_SHIFT_MASK) {
          send_unicode_string("±");
        } else {
          send_unicode_string("\"");
        }
        return false;

      case H_COLON__TILDE:
        if (get_mods() & MODS_SHIFT_MASK) {
          send_unicode_string("∼");
        } else {
          send_string(":");
        }
        return false;

      case H_L_BRACE__L_CHEVRON:
        if (get_mods() & MODS_SHIFT_MASK) {
          send_unicode_string("‹");
        } else {
          send_string("{");
        }
        return false;

      case H_R_BRACE__R_CHEVRON:
        if (get_mods() & MODS_SHIFT_MASK) {
          send_unicode_string("›");
        } else {
          send_string("}");
        }
        return false;

      // [main board] row 2
      case H_MARK:
        send_string("[MARK] key");
        return false;
      case H_LEFT_PAREN__LEFT_BRACKET:
        if (get_mods() & MODS_SHIFT_MASK) {
          CLEAN_MODS(
            send_string(SS_TAP(X_LBRACKET))
          );
        } else {
          send_string("(");
        }
        return false;

      case H_RIGHT_PAREN__RIGHT_BRACKET:
        if (get_mods() & MODS_SHIFT_MASK) {
          CLEAN_MODS(
            send_string(SS_TAP(X_RBRACKET))
          );
        } else {
          send_string(")");
        }
        return false;

      // [main board] row 3
      case H_SELECT:
        send_string("[SELECT] key");
        return false;
      case H_DEBUG:
        send_string("[DEBUG] key");
        return false;
      case H_SEMI_COLON__BACK_TICK:
        if (get_mods() & MODS_SHIFT_MASK) {
          CLEAN_MODS(
            send_string("`");
          );
        } else {
          send_string(";");
        }
        return false;
      case H_TICK__QUOTE:
        if (get_mods() & MODS_SHIFT_MASK) {
          // host configured for uk layout, for ansi, switch to X_QUOT
          send_string(SS_TAP(X_2));
        } else {
          send_string("'");
        }
        return false;
      case H_LINE:
        send_string("[LINE] key");
        return false;
      case H_PAGE:
        if (get_mods() & MODS_SHIFT_MASK) {
          CLEAN_MODS(
            send_string(SS_TAP(X_PGUP));
          );
        } else {
          send_string(SS_TAP(X_PGDN));
        }
        return false;

      // [main board] row 4
      case H_TTY:
        send_string("[TTY] key");
        return false;
      case H_LOCK:
        send_string("[LOCK] key");
        return false;

      // [main board] row 5
      case H_EOF:
        send_string(SS_LCTL(SS_TAP(X_END)));
        return false;
      case H_7BIT:
        send_string("[7BIT] key");
        return false;
      case H_CIRCLE_SM:
        send_string("[CIRCLE_SM] key");
        return false;
    }
  }

  return true;
};

void led_set_keymap(uint8_t usb_led) {
  // stub
};
