/* TypeMatrix-2030-like keymap  */
#include "ergodox_ez.h"
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

#define IS_CA_MULT_ENABLED()    (default_layer_state & (1 << LR_CSA))

enum macros {
    // Characters that do not exist in CSA and must be implemented based on unicode support
    // Note: these are intentionally declared first to be used as indexes in spec_chars below
    UC_NDSH, // –
    UC_MDSH, // —
    UC_ELPS, // …
    END_UC, // indicates the last unicode character macro
    // other macros
    M_TGCM, // toggle CA-mult
    M_CMSFT, // toggle shift on CA-mult
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
    M_DBL0,
    M_FNLR,
};

const uint16_t unicode_chars[] = {
        [UC_NDSH] = L'–',
        [UC_MDSH] = L'—',
        [UC_ELPS] = L'…',
};

/* shortcut for unicod character macros */
#define MUC(name)   M(UC_##name)

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
 *   |LCtrl |  fn  | LGui | Play |App/Alt|                                      |Alt Gr|   %  | Home |   Ç  |End/Ctl|
 *   `-----------------------------------'                                      `-----------------------------------'
 *                                       ,--------------.       ,-------------.
 *                                       |Esc/Alt| num  |       | Left |Right |
 *                                ,------+-------+------|       |------+------+------.
 *                                |      |       | PgUp |       |  Up  |      |      |
 *                                |Space |LShift |------|       |------|RShift|Space |
 *                                |      |       | PgDn |       | Down |      |      |
 *                                `---------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[LR_BASE] = KEYMAP(  // layer 0 : default
        // left hand
        BP_DLR,     KC_1,      KC_2,    KC_3,    KC_4,          KC_5,    KC_DELT,
        KC_TAB,     BP_B,      BP_ECUT, BP_P,    BP_O,          BP_EGRV, KC_BSPC,
        BP_EQL,     BP_A,      BP_U,    BP_I,    BP_E,          BP_COMM,
        KC_LSFT,    BP_AGRV,   BP_Y,    BP_X,    BP_DOT,        BP_K,    KC_ENT,
        KC_LCTL,    M(M_FNLR), KC_LGUI, KC_MPLY, ALT_T(KC_APP),

                                              ALT_T(KC_ESC),  TG(LR_NUMR),
                                                              KC_PGUP,
                                            KC_SPC, KC_LSFT,  KC_PGDN,

        // right hand
        KC_DELT,   KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     BP_W,
        KC_BSPC,   BP_DCRC,  BP_V,    BP_D,    BP_L,    BP_J,     BP_Z,
                   BP_C,     BP_T,    BP_S,    BP_R,    BP_N,     BP_M,
        KC_ENT,    BP_APOS,  BP_Q,    BP_G,    BP_H,    BP_F,     KC_RSFT,
                             BP_ALGR, BP_PERC, KC_HOME, BP_CCED,  CTL_T(KC_END),

        KC_LEFT, KC_RGHT,
        KC_UP,
        KC_DOWN, KC_RSFT,  KC_SPC
    ),
/**
 * Same as default but for use with Canadian Multilingual on OS side
 */
[LR_CSA] = KEYMAP(
        // left hand
        KC_DLR,      CSA_DQOT,   CSA_LGIL,  CSA_RGIL,  KC_LPRN,       KC_RPRN,   KC_DELT,
        KC_TAB,      KC_B,       CSA_ECUT,  KC_P,      KC_O,          CSA_EGRV,  KC_BSPC,
        KC_EQL,      KC_A,       KC_U,      KC_I,      KC_E,          KC_COMM,
        M(M_CMSFT),  CSA_AGRV,   KC_Y,      KC_X,      KC_DOT,        KC_K,      KC_ENT,
        KC_LCTL,     M(M_FNLR),  KC_LGUI,   KC_MPLY,   ALT_T(KC_APP),

                                              ALT_T(KC_ESC),  TG(LR_NUMR),
                                                              KC_PGUP,
                                            KC_SPC, KC_LSFT,  KC_PGDN,

        // right hand
        KC_DELT,   KC_AT,     KC_PLUS,  KC_MINS,  CSA_SLSH,  KC_ASTR,   KC_W,
        KC_BSPC,   CSA_DCRC,  KC_V,     KC_D,     KC_L,      KC_J,      KC_Z,
                   KC_C,      KC_T,     KC_S,     KC_R,      KC_N,      KC_M,
        KC_ENT,    CSA_APOS,  KC_Q,     KC_G,     KC_H,      KC_F,      M(M_CMSFT),
                       MO(LR_CSA_AGR),  KC_PERC,  KC_HOME,   CSA_CCED,  CTL_T(KC_END),

        KC_LEFT, KC_RGHT,
        KC_UP,
        KC_DOWN, KC_RSFT,  KC_SPC
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
[LR_CSA_SFT] = KEYMAP(
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
                             KC_TRNS,  M(M_GRV), KC_TRNS,  KC_TRNS,  KC_TRNS,

        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_TRNS,  KC_TRNS,  M(M_NBSP)
    ),
/* AltGr-ed BÉPO over Canadian Multilingual
 * "////" indicates that the key is disabled (unsupported bépo character)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    –   |   —  |   <  |   >  |   [  |   ]  |      |           |      |   ^  |   ±  | //// | //// | //// | ////// |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   |  |dead '|   &  |   œ  |dead `|      |           |      | //// | //// |   ð  | //// |   ĳ  | ////// |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ////// |   æ  |   ù  |dead "|   €  |   ̛’  |------|           |------| //// |   þ  |   ß  | //// |dead ~| ////// |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   \  |   {  |   }  |   …  |   ~  |      |           |      | //// | //// |   μ  | //// | //// |        |
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
[LR_CSA_AGR] = KEYMAP(
        // left hand
        MUC(NDSH),  MUC(MDSH),  CSA_LESS,  CSA_GRTR,  CSA_LBRC,   CSA_RBRC,  KC_TRNS,
        KC_TRNS,    CSA_PIPE,   CSA_DACT,  KC_AMPR,   CSA_OE,     CSA_DGRV,  KC_TRNS,
        KC_NO,      CSA_AE,     CSA_UGRV,  CSA_DTRM,  CSA_EURO,   CSA_RQOT,
        KC_TRNS,    CSA_BSLS,   CSA_LCBR,  CSA_RCBR,  MUC(ELPS),  CSA_TILD,  KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,

                                                      KC_TRNS,  KC_TRNS,
                                                                KC_TRNS,
                                            KC_UNDS,  KC_TRNS,  KC_TRNS,

        // right hand
        KC_TRNS,  M(M_CRC), CSA_PSMS,  KC_NO,     KC_NO,    KC_NO,     KC_NO,
        KC_TRNS,  KC_NO,    KC_NO,     CSA_ETH,   KC_NO,    CSA_IJ,    KC_NO,
                  KC_NO,    CSA_THRN,  CSA_SRPS,  KC_NO,    CSA_DTLD,  KC_TRNS,
        KC_TRNS,  KC_NO,    KC_NO,     CSA_MU,    KC_NO,    KC_NO,     KC_NO,
                            KC_TRNS,   KC_NO,     KC_TRNS,  CSA_DCED,  KC_TRNS,

        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_UNDS
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
[LR_NUMR] = KEYMAP(
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
 * |        |      | cut  | copy |paste | Mute |VolDn |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | Next |      |      |
 *                                 | Mute |      |------|       |------|      |      |
 *                                 |      |      |      |       | Prev |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[LR_FN] = KEYMAP(
       M(M_TGCM), KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,      KC_TRNS, KC_INS,
       KC_TRNS,   KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,      KC_TRNS, KC_VOLU,
       RESET,     KC_TRNS, KC_TRNS,      KC_CALC,     KC_MAIL,      KC_WHOM,
       KC_TRNS,   KC_TRNS, LSFT(KC_DELT),LCTL(KC_INS),LSFT(KC_INS), KC_MUTE, KC_VOLD,
       KC_TRNS,   KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,

                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_MUTE, KC_TRNS, KC_TRNS,
    // right hand
       KC_INS,   KC_EJCT, KC_PWR,  KC_SLEP, KC_WAKE, KC_PSCR, KC_SLCK,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAUS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

       KC_TRNS, KC_TRNS,
       KC_MPRV,
       KC_MNXT, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
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
        case M_TGCM:
            if (record->event.pressed) {
                default_layer_xor(1 << LR_CSA);
            }
            break;
        case M_CMSFT:
            if (record->event.pressed) {
                layer_on(LR_CSA_SFT);
                hold_shift();
            } else {
                release_shift();
                layer_off(LR_CSA_SFT);
            }
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
                        return MACRO(DOWN(CSA_ALTGR), D(SCLN), END);
                    case M_SCLN:
                        return MACRO(D(SCLN), END);
                    case M_GRV:
                        return MACRO(DOWN(CSA_ALTGR), TYPE(CSA_DCRC), UP(CSA_ALTGR), T(SPACE), END);
                    case M_NBSP:
                        // use weak mod such that pressing another key will not be affected
                        add_weak_mods(MOD_BIT(CSA_ALTGR));
                        return MACRO(D(SPACE), END);
                }
            } else {
                hold_shift();
                switch (id) {
                    case M_1 ... M_0:
                        unregister_code(KC_1 + (id - M_1));
                        break;
                    case M_DEGR:
                        return MACRO(UP(CSA_ALTGR), D(LSFT), U(SCLN), END);
                    case M_SCLN:
                        return MACRO(D(LSFT), U(SCLN), END);
                    case M_NBSP:
                        del_weak_mods(MOD_BIT(CSA_ALTGR));
                        return MACRO(U(SPACE), END);
                }
            }
            break;
        case M_CRC:
            if (record->event.pressed) {
                return MACRO(TYPE(CSA_DCRC), T(SPACE), END);
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
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {
    return NULL;
};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

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
    return NULL;
};
