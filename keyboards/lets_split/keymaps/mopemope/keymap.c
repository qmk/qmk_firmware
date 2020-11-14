#include QMK_KEYBOARD_H
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

#define QGMLWY  0
#define LOWER   1
#define RAISE   2
#define MISCL   3
#define MISCR   4
#define COMBR   5
#define COMBL   6
#define COMBE   7
#define COMBT   8
#define GAME1   9
#define GAME2  10
#define GAME3  11
#define GAME4  12
#define GAME5  13
#define GAME6  14
#define GAME7  15

#define _____ KC_TRNS
#define XXXXX KC_NO

#define WRKSP1 LALT(LCTL(KC_UP))
#define WRKSP2 LALT(LCTL(KC_DOWN))
#define UWRKSP LSFT(LALT(LCTL(KC_UP)))
#define DWRKSP LSFT(LALT(LCTL(KC_DOWN)))
#define PREVTB LSFT(LCTL(KC_UP))
#define NEXTTB LSFT(LCTL(KC_DOWN))
#define CAF2   LALT(LCTL(KC_F2))
#define CAF7   LALT(LCTL(KC_F7))
#define PREVW  LGUI(LCTL(KC_LEFT))
#define NEXTW  LGUI(LCTL(KC_RIGHT))

#define TAB    KC_TAB
#define MINS   JP_MINS
// #define MINS   ALT_T(JP_MINS)
#define SMINS  SFT_T(JP_MINS)
#define SBSLS  SFT_T(JP_BSLS)
#define BSP    KC_BSPC
#define DEL    KC_DEL
#define SDEL   SFT_T(KC_DEL)
#define PSCR   KC_PSCR
#define SPSCR  LSFT(KC_PSCR)
#define RJ     LT(RAISE,KC_J)
#define LK     LT(LOWER,KC_K)
#define AC     LT(COMBR,KC_A)
#define NC     LT(COMBL,KC_N)
#define EC     LT(COMBE,KC_E)
#define KC     LT(COMBE,KC_K)
#define TC     LT(COMBT,KC_T)
#define SPC    LT(RAISE,KC_SPC)
#define CSPC   LCTL(KC_SPC)
#define CRET   LCTL(KC_ENT)
#define ENT    LT(LOWER,KC_ENT)
#define CENT   CTL_T(KC_ENT)
#define BSPC   RCTL_T(KC_BSPC)
#define SBSPC  SFT_T(KC_BSPC)
#define ABSPC  ALT_T(KC_BSPC)
#define CBSPC  CTL_T(KC_BSPC)
#define D_M    LT(MISCL,KC_D)
#define D_C    CTL_T(KC_D)
#define Z_A    ALT_T(KC_Z)
#define Z_C    CTL_T(KC_Z)
#define Z_S    LSFT_T(KC_Z)
#define I_S    LSFT_T(KC_I)
#define X_CT   LCTL_T(KC_X)
#define P_AL   LALT_T(KC_P)
#define J_C    RCTL_T(KC_J)
#define P_C    RCTL_T(KC_P)
#define A_C    RCTL_T(KC_A)
#define H_M    LT(MISCR,KC_H)
#define S_C    CTL_T(JP_SLSH)
#define S_S    RSFT_T(JP_SLSH)
#define V_A    LALT_T(KC_V)
#define O_C    CTL_T(KC_O)
#define AT_A   ALT_T(JP_AT)
#define AT_C   CTL_T(JP_AT)
#define GL     LGUI(KC_LEFT)
#define GU     LGUI(KC_UP)
#define GD     LGUI(KC_DOWN)
#define GR     LGUI(KC_RIGHT)
#define CLEFT  LCTL(KC_LEFT)
#define CUP    LCTL(KC_UP)
#define CDOWN  LCTL(KC_DOWN)
#define CRIGHT LCTL(KC_RIGHT)
#define MLEFT  LALT(KC_LEFT)
#define MUP    LALT(KC_UP)
#define MDOWN  LALT(KC_DOWN)
#define MRIGHT LALT(KC_RIGHT)
#define MLT    LALT(KC_LT)
#define MGT    LALT(KC_GT)
#define GH     LGUI(KC_H)
#define GTAB   TD(G_TAB)
#define FG     TD(D_FG)
#define VB     TD(D_VB)
#define EXLM   JP_EXLM
#define DQT    JP_DQT
#define HASH   JP_HASH
#define DLR    JP_DLR
#define PERC   JP_PERC
#define AMPR   JP_AMPR
#define QUOT   JP_QUOT
#define GRV    JP_GRV
#define PIPE   JP_PIPE
#define YEN    JP_YEN
#define AT     JP_AT
#define LCBR   JP_LCBR
#define RCBR   JP_RCBR
#define UNDS   JP_UNDS
#define TILD   JP_TILD
#define EQL    JP_EQL
#define COLN   JP_COLN
#define SLSH   JP_SLSH
#define ASTR   JP_ASTR
#define LPRN   JP_LPRN
#define RPRN   JP_RPRN
#define BSLS   JP_BSLS
#define CIRC   CTL_T(JP_CIRC)
#define SCLN   JP_SCLN
#define COMM   JP_COMM
#define CCOM   LCTL(JP_COMM)
#define DOT    JP_DOT
#define CDOT   LCTL(JP_DOT)
#define MCOM   LALT(JP_COMM)
#define MDOT   LALT(JP_DOT)
#define PLUS   JP_PLUS
#define LBRC   JP_LBRC
#define RBRC   ALT_T(JP_RBRC)
#define GUI    KC_LGUI
#define ZHTG   JP_ZHTG
#define C_S    SFT_T(KC_C)
#define ESC    KC_ESC
#define DQG    DF(QGMLWY)
#define DG1    DF(GAME1)
#define DG2    DF(GAME2)
#define DG3    DF(GAME3)
#define DG4    DF(GAME4)
#define DG5    DF(GAME5)
#define DG6    DF(GAME6)
#define DG7    DF(GAME7)
#define SELA   LCTL(KC_A)
#define COPY   LCTL(KC_C)
#define PASTE  LCTL(KC_V)
#define CZ     LCTL(KC_Z)
#define CSL    LCTL(JP_SLSH)
#define CF     LCTL(KC_F)
#define CMN    LALT(LCTL(KC_N))
#define CMP    LALT(LCTL(KC_P))
#define CMM    LALT(LCTL(KC_M))
#define CMD    LALT(LCTL(JP_DOT))
#define CMY    LALT(LCTL(JP_YEN))
#define CG     LCTL(KC_G)
#define CQ     LCTL(KC_Q)
#define CT     LCTL(KC_T)
#define CC     LCTL(KC_C)
#define CS     LCTL(KC_S)
#define CX     LCTL(KC_X)
#define CL     LCTL(KC_L)
#define CK     LCTL(KC_K)
#define CE     LCTL(KC_E)
#define CP     LCTL(KC_P)
#define CN     LCTL(KC_N)
#define CAT    LCTL(JP_AT)
#define MX     LALT(KC_X)
#undef  MD
#define MD     LALT(KC_D)
#define MSCLN  LALT(JP_SCLN)
#define APERC  LALT(JP_PERC)
#define CPIPE  LCTL(JP_PIPE)

#define WH_D   KC_WH_D
#define WH_U   KC_WH_U
#define PGDN   KC_PGDN
#define PGUP   KC_PGUP
#define MS_L   KC_MS_L
#define MS_U   KC_MS_U
#define MS_D   KC_MS_D
#define MS_R   KC_MS_R
#define KLEFT  KC_LEFT
#define KUP    KC_UP
#define KDOWN  KC_DOWN
#define KRIGHT KC_RIGHT
#define MUTE   KC_MUTE
#define VOLD   KC_VOLD
#define VOLU   KC_VOLU
#define BTN2   KC_BTN2
#define BTN1   KC_BTN1
#define ASTG   KC_ASTG
#define RTOG   RGB_TOG
#define RMOD   RGB_MOD
#define RRMOD  RGB_RMOD
#define RHUI   RGB_HUI
#define RHUD   RGB_HUD
#define RSAI   RGB_SAI
#define RSAD   RGB_SAD
#define RVAI   RGB_VAI
#define RVAD   RGB_VAD
#define CTL    OSM(MOD_RCTL)

// COMB
// C-V
#define C_V LCTL(KC_V)
// M-V
#define M_V LALT(KC_V)
// C-<
#define C_LT LCTL(JP_LT)
// C->
#define C_GT LCTL(JP_GT)

enum double_taps {
  G_TAB = 0,
  D_FG = 1,
  D_VB = 2,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [G_TAB] = ACTION_TAP_DANCE_DOUBLE (KC_TAB, KC_ESC),
  [D_FG] =  ACTION_TAP_DANCE_DOUBLE (KC_F, KC_G),
  [D_VB] =  ACTION_TAP_DANCE_DOUBLE (KC_V, KC_B),
};

enum custom_keycodes {
  CXCF = SAFE_RANGE,
  CXCB,
  CXCS,
  CXO,
  CXU,
  CCN,
  CCP
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QGMLWY
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  Q   |  G   |  M   |  L   |  W   |      | |      |  Y   |  F   |  U   |  B   |  BSP |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  D   |  S   |  T   |  N   |  R   |      | |      |  I   |  A   |  E   |  O   |  H   |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  Z   |  X   |  C   |  V   | SPC  |      | |      | ENT  |  J   |  K   |  P   |  /   |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [QGMLWY] = LAYOUT( \
    KC_Q,    KC_G,   KC_M,  KC_L,  KC_W,  XXXXX,  XXXXX,  KC_Y,  KC_F,  KC_U,  KC_B,   BSP,    \
    D_M,     KC_S,   TC,    NC,    KC_R,  XXXXX,  XXXXX,  KC_I,  AC,    EC,    KC_O,   H_M,    \
    Z_S ,    X_CT,   KC_C,  V_A,   SPC,   XXXXX,  XXXXX,  ENT,   J_C,   KC_K,  P_AL,   S_S,    \
    XXXXX,   XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX   \
  ),

  /* LOWER (Symbol)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  !   |   "  |   #  |   $  |   %  |      | |      |   &  |  '   |  `   |  |   |  yen |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | ESC  |   (  |  )   |   {  |   }  |      | |      |   ~  |  .   |  /   |  =   |  @   |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  ^   |   [  |  ]   |   <  |   >  |      | |      |      |  ,   |      |      |  -   |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [LOWER] = LAYOUT( \
    EXLM,    DQT,    HASH,   DLR,   PERC,  XXXXX,  XXXXX, AMPR,   QUOT,  GRV,   PIPE,  YEN,  \
    ESC,     LPRN,   RPRN,   LCBR,  RCBR,  XXXXX,  XXXXX, TILD,   DOT,   SLSH,  EQL,   AT, \
    CIRC,    LBRC,   RBRC,   KC_LT, KC_GT, XXXXX,  XXXXX, _____,  COMM,  _____, _____, MINS, \
    XXXXX,   XXXXX,  XXXXX,  XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX \
  ),

  /* RAISE (Num + Fn + Others)
   * ,-----------------------------------------, ,-----------------------------------------.
   * |  1   |  2   |   3  |  4   |  5   |      | |      |   6  |   7  |   8  |   9  |   0  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | TAB  |  F1  |  F2  |  F3  |  F4  |      | |      |  F5  |  F12 |  F7  |  F8  |   @  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  _   |  F9  |  F10 |  F11 |      |      | |      |  DOT |  F6  |  <   |  >   |   -  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [RAISE] = LAYOUT( \
    KC_1,    KC_2,  KC_3,   KC_4,   KC_5,  XXXXX,  XXXXX, KC_6,  KC_7,   KC_8,  KC_9,  KC_0,   \
    TAB,     KC_F1, KC_F2,  KC_F3,  KC_F4, XXXXX,  XXXXX, KC_F5, KC_F12, KC_F7, KC_F8, AT,     \
    UNDS,    KC_F9, KC_F10, KC_F11, _____, XXXXX,  XXXXX, DOT,   KC_F6,  KC_LT, KC_GT, MINS,   \
    XXXXX,   XXXXX, XXXXX,  XXXXX,  XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX   \
  ),

  /* MISC Left
   * ,-----------------------------------------, ,-----------------------------------------.
   * |RESET |      |  UP  |      |WRKSP1|      | |      |UWRKSP| PGDN |  UP  | PGUP | DEL  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      | LEFT | DOWN | RIGHT|WRKSP2|      | |      |DWRKSP| LEFT | DOWN | RIGHT|      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      | COPY | PASTE| GUI  |      | |      | MLT  | MGT  | PSCR | HIDE |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [MISCL] = LAYOUT( \
    RESET, _____,  KUP,   _____, WRKSP1, XXXXX,  XXXXX,  UWRKSP, PGDN,  GU,    PGUP,  DEL,    \
    _____, KLEFT,  KDOWN, KRIGHT,WRKSP2, XXXXX,  XXXXX,  DWRKSP, GL,    GD,    GR,    _____,  \
    _____, _____,  COPY,  PASTE, GUI,    XXXXX,  XXXXX,  MLT,    MGT,  SPSCR, GH,    _____, \
    XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX   \
  ),

  /* MISC Right
   * ,-----------------------------------------, ,-----------------------------------------.
   * |RESET |      |      |      |PREVW |      | |      |PREVTB| MLT  |  UP  | MGT  | DEL  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | TAB  |      |      |      |NEXTW |      | |      |NEXTTB| LEFT | DOWN | RIGHT|      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      | BSP  |      | |      |      | BSP  |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [MISCR] = LAYOUT( \
    RESET,   _____, _____, _____, PREVW, XXXXX,  XXXXX, PREVTB, MLT,   KUP,   MGT,   DEL,    \
    TAB,     _____, _____, _____, NEXTW, XXXXX,  XXXXX, NEXTTB, KLEFT, KDOWN, KRIGHT, _____,  \
    _____,   _____, _____, _____, BSP,   XXXXX,  XXXXX, _____,  BSP,   _____, _____,  _____,  \
    XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX,  _____   \
  ),

  /* COMB Right (COMBA)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  C-Q |  C-G | C-M-M|  C-L | M-%  |      | |      |      | CXCF | CXU  | CXCB |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  M-D | CXCS |  C-T | C-M-N| M-X  |      | |      |      |      | C-Q  | CXO  |  C-@ |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  C-Z |  C-X |  C-C |      | ZHTG |      | |      |      |      | C-K  |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [COMBR] = LAYOUT( \
    CQ,      CG,     CMM,   CL,    APERC, XXXXX,   XXXXX, _____, CXCF,  CXU,   CXCB,  _____,  \
    MD,      CXCS,   CT,    CMN,   MX,    XXXXX,   XXXXX, _____, _____, CQ,    CXO,   CAT,    \
    CZ,      CX,     CC,    _____, ZHTG,  XXXXX,   XXXXX, _____, _____, CK,    _____, _____,  \
    XXXXX,   XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX   \
  ),

  /* COMB Left  (COMBN)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |      | C-G  |      | C-L  |      |      | |      | C-M-Y| CCP  |  UP  |  CCN |  M-D |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  TAB | C-S  | C-T  |      |      |      | |      |  M-; | LEFT |  DOWN| RIGHT|  C-@ |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      | C-X  | CRET | CSPC |      |      | |      |  M-, |  M-. |  C-, |  C-. |  CXU |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [COMBL] = LAYOUT( \
    _____,  CG,     XXXXX, CL,    _____, XXXXX,   XXXXX, CMY,   CCP,   CP,   CCN,    MD,   \
    TAB,    CS,     CT,    _____, _____, XXXXX,   XXXXX, MSCLN, CLEFT, CN,   CRIGHT, CAT,  \
    _____,  CX,     CRET,  CSPC,  _____, XXXXX,   XXXXX, MCOM,  MDOT,  CCOM, CDOT,   CXU,  \
    XXXXX,  XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX,XXXXX,  XXXXX \
  ),

  /* COMB Right2 (COMBE)
   * ,-----------------------------------------, ,-----------------------------------------,
   * | CAF7 |      |  CUP |      |      |      | |      | DQG  |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | CAF2 | CLEFT| CDOWN|CRIGHT|      |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | PSCR |      |      |      |      |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [COMBE] = LAYOUT( \
    CAF7,   _____, CUP,   _____,  _____, XXXXX,   XXXXX, DQG,   _____, _____, _____,  _____,  \
    CAF2,   CLEFT, CDOWN, CRIGHT, _____, XXXXX,   XXXXX, _____, _____, _____, _____,  _____, \
    PSCR,   _____, _____, _____,  BSP,   XXXXX,   XXXXX, _____, _____, _____, _____,  _____,  \
    XXXXX,  XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX   \
  ),

  /* COMB Left2 (COMBT)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  DG1 |  DG2 |  DG3 |  DG4 |  DG5 |      | |      |   "  |  !   |   +  |   *  |   |  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |   ~  |  =   |   :  |   ;  |   @  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      | BSP  |   ,  |   .  |   /  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [COMBT] = LAYOUT( \
    DG1,    DG2,    DG3,    DG4,   DG5,   XXXXX,  XXXXX, DQT,   EXLM,  PLUS,  ASTR,   PIPE,   \
    _____,  _____,  _____,  _____, _____, XXXXX,  XXXXX, TILD,  EQL,   COLN,  SCLN,   AT,     \
    _____,  _____,  _____,  _____, _____, XXXXX,  XXXXX, _____, BSP,   COMM,  DOT,    SLSH,   \
    XXXXX,  XXXXX,  XXXXX,  XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX   \
  ),

  /* GAME1(BL2)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  TAB |  G   |  W   |  E   |  R   |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | SHIFT|  A   |  S   |  D   |  F   |      | |      |      |  DQG |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  C   |  Q   |  M   |  V   |  SPC |      | |      |      |      |      |      |  DQG |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [GAME1] = LAYOUT( \
    GTAB,    KC_G,  KC_W,  KC_E,  KC_R,  XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    KC_LSFT, KC_A,  KC_S,  KC_D,  KC_F,  XXXXX,  XXXXX, XXXXX, DQG,   XXXXX, XXXXX, XXXXX,     \
    KC_C,    KC_Q,  KC_M,  KC_V,  KC_SPC,XXXXX,  XXXXX, _____, XXXXX, XXXXX, XXXXX, DQG,       \
    XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX      \
  ),

  /* GAME2(WoL)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  TAB |  Q   |  W   |  E   |  R   |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |  A   |  S   |  D   |  F   |      | |      |      |  DQG |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |  M   |      |  SPC |      | |      |      |      |      |      |  DQG |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [GAME2] = LAYOUT( \
    GTAB,    KC_Q,  KC_W,  KC_E,  KC_R,  XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX,   KC_A,  KC_S,  KC_D,  KC_F,  XXXXX,  XXXXX, XXXXX, DQG,   XXXXX, XXXXX, XXXXX,     \
    XXXXX,   XXXXX, KC_M,  XXXXX, KC_SPC,XXXXX,  XXXXX, _____, XXXXX, XXXXX, XXXXX, DQG,       \
    XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX      \
  ),

  /* GAME3(Diablo)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  F1  |  F2  |  F3  |  F4  |  F5  |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |   1  |   2  |   3  |   4  |   5  |      | |      |      |  DQG |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  ESC |   C  |   I  |   B  |   F  |      | |      |      |      |      |      |  DQG |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [GAME3] = LAYOUT( \
     KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
     KC_1,   KC_2,  KC_3,  KC_4,  KC_5,  XXXXX,  XXXXX, XXXXX, DQG,   XXXXX, XXXXX, XXXXX,     \
     KC_ESC, KC_C,  KC_I,  KC_B,  KC_F,  XXXXX,  XXXXX, _____, XXXXX, XXXXX, XXXXX, DQG,       \
     XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX      \
  ),

  /* GAME4(VAROLANT)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  ESC |  Q   |  W   |  E   |  R   |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  SFT |  A   |  S   |  D   |  X   |      | |      |      |  DQG |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  4   |  F   |  B   |  C   | SPC  |      | |      |      |      |      |      |  DQG |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [GAME4] = LAYOUT( \
     GTAB,   KC_Q,  KC_W,  KC_E,  KC_R,  XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
     KC_LSFT,KC_A,  KC_S,  KC_D,  KC_X,  XXXXX,  XXXXX, XXXXX, DQG,   XXXXX, XXXXX, XXXXX,     \
     KC_4,   FG,    VB,    KC_C,  KC_SPC,XXXXX,  XXXXX, _____, XXXXX, XXXXX, XXXXX, DQG,       \
     XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX      \
  ),

  /* GAME5(TLD)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  TAB |  Q   |  W   |  H   |  R   |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |   I  |  A   |  S   |  D   |  F   |      | |      |      |  DQG |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | CTRL |      |  M   |  J   |  SPC |      | |      |      |      |      |      |  DQG |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [GAME5] = LAYOUT( \
    GTAB,    KC_Q,  KC_W,  KC_H,  KC_R,  XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    I_S,     KC_A,  KC_S,  KC_D,  KC_F,  XXXXX,  XXXXX, XXXXX, DQG,   XXXXX, XXXXX, XXXXX,     \
    KC_LCTL, XXXXX, KC_M,  KC_J,  KC_SPC,XXXXX,  XXXXX, _____, XXXXX, XXXXX, XXXXX, DQG, \
    XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX      \
  ),

  /* GAME6(Moonlighter)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  TAB |  Q   |  W   |  E   |  M   |      | |      |      |  E   |   L  |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |   I  |  A   |  S   |  D   |  R   |      | |      |   I  |  J   |   K  |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |   Z  |  C   |      |      |  SPC |      | |      |      |      |      |      |  DQG |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [GAME6] = LAYOUT( \
    GTAB,    KC_Q,  KC_W,  KC_E,  KC_M,  XXXXX,  XXXXX, XXXXX, KC_E,  KC_L,  XXXXX, XXXXX,     \
    I_S,     KC_A,  KC_S,  KC_D,  KC_R,  XXXXX,  XXXXX, KC_I,  KC_J,  KC_K,  XXXXX, XXXXX,     \
    KC_Z,    KC_C,  XXXXX, XXXXX, KC_SPC,XXXXX,  XXXXX, _____, XXXXX, XXXXX, XXXXX, DQG,       \
    XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX      \
  ),

  /* GAME7(FO3)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  TAB |  Q   |  W   |  E   |  R   |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |   I  |  A   |  S   |  D   |  F   |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |   Z  |  T   |      |  V   |  SPC |      | |      |      |      |      |      |  DQG |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [GAME7] = LAYOUT( \
    GTAB,    KC_Q,  KC_W,  KC_E,  KC_R,  XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    I_S,     KC_A,  KC_S,  KC_D,  KC_F,  XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    Z_C,     KC_T,  XXXXX, KC_V,  KC_SPC,XXXXX,  XXXXX, _____, XXXXX, XXXXX, XXXXX, DQG,       \
    XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX      \
  ),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void keyboard_post_init_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case CXCF:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("xf"));
      }
    break;
  case CXCB:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("xb"));
    }
    break;
  case CXCS:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("xs"));
    }
    break;
  case CXO:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("x") "o");
    }
    break;
  case CXU:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("x") "u");
    }
    return false;
  case CCN:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("c") "n");
    }
    return false;
  case CCP:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("c") "p");
    }
    return false;
  }
  return true;
}
