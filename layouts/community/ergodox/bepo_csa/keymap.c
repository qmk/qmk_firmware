/* TypeMatrix-2030-like keymap  */
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "led.h"
#include "keymap_extras/keymap_bepo.h"
#include "keymap_extras/keymap_canadian_multilingual.h"

enum layers {
    LR_BASE, // default layer
    LR_CSA, // BÉPO over Canadian Multilingual (CSA)
    LR_CSA_SFT, // shifted BÉPO over CSA
    LR_CSA_AGR, // altgr-ed BÉPO over CSA
    LR_CSA_AGR_SFT, // altgr-shifted BÉPO over CSA
    LR_NUMR, // numeric layer
    LR_FN, // fn layer
};

#define IS_CA_MULT_ENABLED()    (layer_state & (1 << LR_CSA))

enum macros {
    // Characters that do not exist in CSA and must be implemented based on unicode support
    // Note: these are intentionally declared first to be used as indexes in spec_chars below
    UC_NDSH, // –
    UC_MDSH, // —
    UC_ELPS, // …
    END_UC, // indicates the last unicode character macro
    // other macros
    M_CSA_SFT, // toggle shift on CSA
    M_CSA_AGR_SFT, // toggle shift on LR_CSA_AGR (goes to LR_CSA_AGR_SFT)
    M_CSA_SFT_AGR, // toggle AltGr on LR_CSA_SFT (goes to LR_CSA_AGR_SFT)
    // macros for characters that need to be un-shifted in LR_CA_MULT_SHIFT
    M_1,
    M_2,
    M_3,
    M_4,
    M_5,
    M_6,
    M_7,
    M_8,
    M_9,
    M_0,
    M_DEGR,
    M_SCLN,
    M_GRV,
    M_NBSP,
    // macros for characters that don't have a simple key combination in LR_CA_MULT_ALTGR
    M_CRC,
    // other layer macros
    M_DBL0, // double 0
    M_FNLR, // fn layer
    M_NMAL, // num+alt
};

#define CSA(name)   M(M_CSA_##name)     // calls a CSA macro

const uint16_t unicode_chars[] = {
        [UC_NDSH] = L'–',
        [UC_MDSH] = L'—',
        [UC_ELPS] = L'…',
};

/* shortcut for unicode character macros */
#define MUC(name)   M(UC_##name)    // calls a unicode macro

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   $    |   "  |   «  |   »  |   (  |   )  | Del  |           | Del  |   @  |   +  |   -  |   /  |   *  |   W    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   B  |   É  |   P  |   O  |   È  |Backsp|           |Backsp|   ^  |   V  |   D  |   L  |   J  |   Z    |
 * |--------+------+------+------+------+------|ace   |           |ace   |------+------+------+------+------+--------|
 * |   =    |   A  |   U  |   I  |   E  |   ,  |------|           |------|   C  |   T  |   S  |   R  |   N  |   M    |
 * |--------+------+------+------+------+------|Enter |           |Enter |------+------+------+------+------+--------|
 * | LShift |   À  |   Y  |   X  |   .  |   K  |      |           |      |   '  |   Q  |   G  |   H  |   F  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl |  fn  | LGui |numAlt| LAlt |                                       |Alt Gr|   %  |  App |   Ç  | RCtrl|
 *   `----------------------------------'                                       `----------------------------------'
 *                                       ,--------------.       ,-------------.
 *                                       |  Esc  | num  |       | Left |Right |
 *                                ,------+-------+------|       |------+------+------.
 *                                |      |       | PgUp |       |  Up  |      |      |
 *                                |Space | Home  |------|       |------| End  |Space |
 *                                |      |       | PgDn |       | Down |      |      |
 *                                `---------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[LR_BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        BP_DLR,     KC_1,      KC_2,    KC_3,      KC_4,     KC_5,    KC_DEL,
        KC_TAB,     BP_B,      BP_ECUT, BP_P,      BP_O,     BP_EGRV, KC_BSPC,
        BP_EQL,     BP_A,      BP_U,    BP_I,      BP_E,     BP_COMM,
        KC_LSFT,    BP_AGRV,   BP_Y,    BP_X,      BP_DOT,   BP_K,    KC_ENT,
        KC_LCTL,    M(M_FNLR), KC_LGUI, M(M_NMAL), KC_LALT,

                                                   KC_ESC,   TG(LR_NUMR),
                                                             KC_PGUP,
                                          KC_SPC,  KC_HOME,  KC_PGDN,

        // right hand
        KC_DEL,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     BP_W,
        KC_BSPC,   BP_DCRC,  BP_V,    BP_D,    BP_L,    BP_J,     BP_Z,
                   BP_C,     BP_T,    BP_S,    BP_R,    BP_N,     BP_M,
        KC_ENT,    BP_APOS,  BP_Q,    BP_G,    BP_H,    BP_F,     KC_RSFT,
                             KC_ALGR, BP_PERC, KC_APP,  BP_CCED,  KC_RCTL,

        KC_LEFT, KC_RGHT,
        KC_UP,
        KC_DOWN, KC_END,   KC_SPC
    ),
/**
 * Same as default but for use with Canadian Multilingual on OS side
 */
[LR_CSA] = LAYOUT_ergodox(
        // left hand
        KC_DLR,      CSA_DQOT,   CSA_LGIL,  CSA_RGIL,  KC_LPRN,  KC_RPRN,   KC_TRNS,
        KC_TRNS,     KC_B,       CSA_ECUT,  KC_P,      KC_O,     CSA_EGRV,  KC_TRNS,
        KC_EQL,      KC_A,       KC_U,      KC_I,      KC_E,     KC_COMM,
        CSA(SFT),    CSA_AGRV,   KC_Y,      KC_X,      KC_DOT,   KC_K,      KC_TRNS,
        KC_TRNS,     KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,

                                                       KC_TRNS,  KC_TRNS,
                                                                 KC_TRNS,
                                            KC_TRNS,   KC_TRNS,  KC_TRNS,

        // right hand
        KC_TRNS,  KC_AT,     KC_PLUS,  KC_MINS,  CSA_SLSH,  KC_ASTR,   KC_W,
        KC_TRNS,  CSA_DCRC,  KC_V,     KC_D,     KC_L,      KC_J,      KC_Z,
                  KC_C,      KC_T,     KC_S,     KC_R,      KC_N,      KC_M,
        KC_TRNS,  CSA_APOS,  KC_Q,     KC_G,     KC_H,      KC_F,      CSA(SFT),
                      MO(LR_CSA_AGR),  KC_PERC,  KC_TRNS,   CSA_CCED,  KC_LCTL, // RCTL has a special behaviour in CSA so use LCTL

        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
/* Shifted BÉPO over Canadian Multilingual
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   #    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |   !  |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   °    |      |      |      |      |   ;  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |   :  |      |      |           |      |   ?  |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |   `  |      |      |       |
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[LR_CSA_SFT] = LAYOUT_ergodox(
        // left hand
        KC_HASH,  M(M_1),   M(M_2),   M(M_3),  M(M_4),   M(M_5),   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
        M(M_DEGR),KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  M(M_SCLN),
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_COLN,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,

                                                      KC_TRNS,  KC_TRNS,
                                                                KC_TRNS,
                                          M(M_NBSP),  KC_TRNS,  KC_TRNS,

        // right hand
        KC_TRNS,  M(M_6),    M(M_7),   M(M_8),   M(M_9),   M(M_0),   KC_TRNS,
        KC_TRNS,  KC_EXLM,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  CSA_QEST,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                        CSA(SFT_AGR),  M(M_GRV), KC_TRNS,  KC_TRNS,  KC_TRNS,

        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_TRNS,  KC_TRNS,  M(M_NBSP)
    ),
/* AltGr-ed BÉPO over Canadian Multilingual
 * "////" indicates that the key is disabled (unsupported bépo character)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    –   |   —  |   <  |   >  |   [  |   ]  |      |           |      |   ^  |   ±  | //// |   ÷  |   ×  | dead ˘ |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   |  |dead '|   &  |   œ  |dead `|      |           |      |   ¡  |dead ˇ|   ð  | //// |   ĳ  | ////// |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ////// |   æ  |   ù  |dead "|   €  |   ̛’  |------|           |------|   ©  |   þ  |   ß  |   ®  |dead ~| dead ¯ |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   \  |   {  |   }  |   …  |   ~  |      |           |      |   ¿  |dead °|   μ  | //// |dead ˛|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      | //// |      |dead ¸|       |
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |   _  |      |------|       |------|      |  _   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[LR_CSA_AGR] = LAYOUT_ergodox(
        // left hand
        MUC(NDSH),    MUC(MDSH),  CSA_LESS,  CSA_GRTR,  CSA_LBRC,   CSA_RBRC,  KC_TRNS,
        KC_TRNS,      CSA_PIPE,   CSA_DACT,  KC_AMPR,   CSA_OE,     CSA_DGRV,  KC_TRNS,
        KC_NO,        CSA_AE,     CSA_UGRV,  CSA_DTRM,  CSA_EURO,   CSA_RQOT,
        CSA(AGR_SFT), CSA_BSLS,   CSA_LCBR,  CSA_RCBR,  MUC(ELPS),  CSA_TILD,  KC_TRNS,
        KC_TRNS,      KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,

                                                      KC_TRNS,  KC_TRNS,
                                                                KC_TRNS,
                                        KC_UNDS, CSA(AGR_SFT),  KC_TRNS,

        // right hand
        KC_TRNS,  M(M_CRC),  CSA_PSMS,  KC_NO,     CSA_DVSN, CSA_TIMS,  CSA_DBRV,
        KC_TRNS,  CSA_IXLM,  CSA_DCAR,  CSA_ETH,   KC_NO,    CSA_IJ,    KC_NO,
                  CSA_CPRT,  CSA_THRN,  CSA_SRPS,  CSA_RTM,  CSA_DTLD,  CSA_DMCR,
        KC_TRNS,  CSA_IQST,  CSA_DRNG,  CSA_MU,    KC_NO,    CSA_DOGO,  CSA(AGR_SFT),
                             KC_TRNS,   KC_NO,     KC_TRNS,  CSA_DCED,  KC_TRNS,

        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_TRNS,  CSA(AGR_SFT),  KC_UNDS
    ),
/* AltGr-shifted BÉPO over Canadian Multilingual
 * "////" indicates that the key is disabled (unsupported bépo character or unused in bépo)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    ¶   | //// |   “  |   ”  | //// | //// |      |           |      | //// |   ¬  |   ¼  |   ½  |   ¾  | ////// |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   ¦  |   ˝  |   §  |   Œ  |   `  |      |           |      | //// | //// |   Ð  | //// |   Ĳ  | ////// |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ////// |   Æ  |   Ù  |dead-˙| //// | //// |------|           |------| //// |   Þ  |   ẞ   |   ™  | //// |   º    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | //// |   ‘  |   ’  | //// | //// |      |           |      | //// | //// | //// | //// |   ª  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[LR_CSA_AGR_SFT] = LAYOUT_ergodox(
        // left hand
        CSA_PARG,      KC_NO,     CSA_LDQT,    CSA_RDQT,  KC_NO,     KC_NO,     KC_TRNS,
        KC_TRNS,       CSA_BPIP,  CSA_DDCT,    CSA_SECT,  S(CSA_OE), M(M_GRV),  KC_TRNS,
        KC_NO,         S(CSA_AE), S(CSA_UGRV), CSA_DDTA,  KC_NO,     KC_NO,
        CSA(AGR_SFT),  KC_NO,     CSA_LQOT,    CSA_RQOT,  KC_NO,     KC_NO,     KC_TRNS,
        KC_TRNS,       KC_TRNS,   KC_TRNS,     KC_TRNS,   KC_TRNS,

        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_TRNS,  CSA(AGR_SFT),  KC_TRNS,

        // right hand
        KC_TRNS,  KC_NO,     CSA_NEGT,    CSA_1QRT,    CSA_1HLF,  CSA_3QRT,   KC_NO,
        KC_TRNS,  KC_NO,     KC_NO,       S(CSA_ETH),  KC_NO,     S(CSA_IJ),  KC_NO,
                  KC_NO,     S(CSA_THRN), S(CSA_SRPS), CSA_TM,    KC_NO,      CSA_ORDO,
        KC_TRNS,  KC_NO,     KC_NO,       KC_NO,       KC_NO,     CSA_ORDA,   CSA(AGR_SFT),
                        CSA(SFT_AGR),     KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_TRNS,

        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_TRNS,  CSA(AGR_SFT),  KC_TRNS
    ),
/* Numeric Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |      |      |  Tab |   /  |   *  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  F6  |  F7  |  F8  |  F9  |  F10 |      |           |      |      | Home |   7  |   8  |   9  |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F11 |  F12 |      |      |      |------|           |------|  Up  | End  |   4  |   5  |   6  |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           | Left | Down | Right|   1  |   2  |   3  |KpEnter |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |   0  |  00  |   .  |Etr/Ctl|
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |n.lock|c.lock|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[LR_NUMR] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                              KC_TRNS, KC_TRNS,KC_TRNS,

       // right hand
       KC_TRNS, KC_F6,   KC_F7,   KC_TAB,  KC_PSLS,  KC_PAST, KC_PMNS,
       KC_TRNS, KC_TRNS, KC_HOME, KC_P7,   KC_P8,    KC_P9,   KC_PPLS,
                KC_UP,   KC_END,  KC_P4,   KC_P5,    KC_P6,   KC_PPLS,
       KC_LEFT, KC_DOWN, KC_RGHT, KC_P1,   KC_P2,    KC_P3,   KC_PENT,
                         KC_TRNS, KC_P0,   M(M_DBL0),KC_PDOT, CTL_T(KC_PENT),

       KC_NLCK, KC_CAPS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* fn layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |~CA-mult|      |      |      |      |      |Insert|           |Insert|Eject |Power |Sleep | Wake |PrtScr|ScrollLk|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |VolUp |           |      |      |      |      |      |      | Pause  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  RESET |      |      | Calc | Mail |Browsr|------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | App  | cut  | copy |paste | Mute |VolDn |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Next |       |      |      |      |
 *                                 | Mute | play |------|       |------|      |      |
 *                                 |      |      | Prev |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[LR_FN] = LAYOUT_ergodox(
       TG(LR_CSA), KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,      KC_TRNS, KC_INS,
       KC_TRNS,    KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,      KC_TRNS, KC_VOLU,
       RESET,      KC_TRNS, KC_TRNS,      KC_CALC,     KC_MAIL,      KC_WHOM,
       KC_TRNS,    KC_APP,  S(KC_DEL),    LCTL(KC_INS),S(KC_INS),    KC_MUTE, KC_VOLD,
       KC_TRNS,    KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,

                                           KC_TRNS, KC_TRNS,
                                                    KC_MPRV,
                                  KC_MUTE, KC_MPLY, KC_MNXT,

    // right hand
       KC_INS,   KC_EJCT, KC_PWR,  KC_SLEP, KC_WAKE, KC_PSCR, KC_SLCK,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAUS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

void hold_shift(void) {
    register_code(KC_LSHIFT);
}

void release_shift(void) {
    unregister_code(KC_LSHIFT);
}

uint16_t hextokeycode(int hex) {
    if (hex == 0x0) {
        return KC_P0;
    } else if (hex < 0xA) {
        return KC_P1 + (hex - 0x1);
    } else {
        return KC_A + (hex - 0xA);
    }
}

void send_unicode(uint16_t unicode)
{
    // For more info on how this works per OS, see here: https://en.wikipedia.org/wiki/Unicode_input#Hexadecimal_code_input
    // Implemented for Windows:
    // Pressing ALT followed by + followed by the unicode code point in hex.
    // Requires registry key HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad set to String 1
    register_code(KC_LALT);
    register_code(KC_PPLS);
    unregister_code(KC_PPLS);

    for (int i = 12; i >= 0; i -= 4) {
        register_code(hextokeycode((unicode >> i) & 0xF));
        unregister_code(hextokeycode((unicode >> i) & 0xF));
    }

    unregister_code(KC_LALT);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
        case 0 ... END_UC:
            if (record->event.pressed) {
                send_unicode(unicode_chars[id]);
            }
            break;
        case M_CSA_SFT:
            // BÉPO over CSA: toggle shift layer
            layer_invert(LR_CSA_SFT);
            if (record->event.pressed) {
                hold_shift();
            } else {
                release_shift();
            }
            break;
        case M_CSA_SFT_AGR:
            // BÉPO over CSA: from shift layer, momentary altgr+shift layer
            layer_invert(LR_CSA_AGR);
            layer_invert(LR_CSA_AGR_SFT);
            if (record->event.pressed) {
                // shift not needed for LR_CSA_AGR_SFT
                release_shift();
            } else {
                // back to shift layer
                hold_shift();
            }
            break;
        case M_CSA_AGR_SFT:
            // BÉPO over CSA: from altgr layer, momentary altgr+shift layer
            layer_invert(LR_CSA_SFT);
            layer_invert(LR_CSA_AGR_SFT);
            break;
        case M_1 ... M_0:
        case M_DEGR:
        case M_SCLN:
        case M_GRV:
        case M_NBSP:
            // macros of the shift layer that require to release shift
            if (record->event.pressed) {
                release_shift();
                switch (id) {
                    case M_1 ... M_0:
                        register_code(KC_1 + (id - M_1));
                        break;
                    case M_DEGR:
                        return MACRO(DOWN(KC_ALGR), D(SCLN), END);
                    case M_SCLN:
                        return MACRO(D(SCLN), END);
                    case M_GRV:
                        return MACRO(I(75), DOWN(KC_ALGR), TYPE(CSA_DCRC), UP(KC_ALGR), T(SPACE), END);
                    case M_NBSP:
                        // use weak mod such that pressing another key will not be affected
                        add_weak_mods(MOD_BIT(KC_ALGR));
                        return MACRO(D(SPACE), END);
                }
            } else {
                hold_shift();
                switch (id) {
                    case M_1 ... M_0:
                        unregister_code(KC_1 + (id - M_1));
                        break;
                    case M_DEGR:
                        return MACRO(UP(KC_ALGR), U(SCLN), END);
                    case M_SCLN:
                        return MACRO(U(SCLN), END);
                    case M_NBSP:
                        del_weak_mods(MOD_BIT(KC_ALGR));
                        return MACRO(U(SPACE), END);
                }
            }
            break;
        case M_CRC:
            if (record->event.pressed) {
                return MACRO(I(75), TYPE(CSA_DCRC), T(SPACE), END);
            }
            break;
        case M_DBL0:
            if (record->event.pressed) {
                return MACRO( I(25), T(P0), T(P0), END );
            }
        break;
        case M_FNLR:
            layer_invert(LR_NUMR);
            layer_invert(LR_FN);
            break;
        case M_NMAL:
            layer_invert(LR_NUMR);
            if (record->event.pressed) {
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
            }
            break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    // led 1: numeric layer
    if (layer_state & (1 << LR_NUMR)) {
        ergodox_right_led_1_on();
    }
    // led 2: BÉPO over Canadian Multilingual
    if (IS_CA_MULT_ENABLED()) {
        ergodox_right_led_2_on();
    }
    // led 3: caps lock
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
      ergodox_right_led_3_on();
    }
};
