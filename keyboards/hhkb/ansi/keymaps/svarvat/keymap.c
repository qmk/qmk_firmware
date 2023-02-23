// Initialize variable holding the binary

// representation of active modifiers.
uint8_t mod_state;

/*  -*-  eval: (turn-on-orgtbl); -*-
 * default HHKB Layout
 */
#include QMK_KEYBOARD_H

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ² │ & │ é │ " │ ' │ ( │ - │ è │ _ │ ç │ à │ ) │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ A │ Z │ E │ R │ T │ Y │ U │ I │ O │ P │ ^ │ $ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Q │ S │ D │ F │ G │ H │ J │ K │ L │ M │ ù │ * │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ W │ X │ C │ V │ B │ N │ , │ ; │ : │ ! │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
#define FR_SUP2 KC_GRV  // ²
#define FR_AMPR KC_1    // &
#define FR_EACU KC_2    // é
#define FR_DQUO KC_3    // "
#define FR_QUOT KC_4    // '
#define FR_LPRN KC_5    // (
#define FR_MINS KC_6    // -
#define FR_EGRV KC_7    // è
#define FR_UNDS KC_8    // _
#define FR_CCED KC_9    // ç
#define FR_AGRV KC_0    // à
#define FR_RPRN KC_MINS // )
#define FR_EQL KC_EQL   // =
#define FR_A KC_Q       // A
#define FR_Z KC_W       // Z
#define FR_E KC_E       // E
#define FR_R KC_R       // R
#define FR_T KC_T       // T
#define FR_Y KC_Y       // Y
#define FR_U KC_U       // U
#define FR_I KC_I       // I
#define FR_O KC_O       // O
#define FR_P KC_P       // P
#define FR_CIRC KC_LBRC // ^ (dead)
#define FR_DLR KC_RBRC  // $
#define FR_Q KC_A       // Q
#define FR_S KC_S       // S
#define FR_D KC_D       // D
#define FR_F KC_F       // F
#define FR_G KC_G       // G
#define FR_H KC_H       // H
#define FR_J KC_J       // J
#define FR_K KC_K       // K
#define FR_L KC_L       // L
#define FR_M KC_SCLN    // M
#define FR_UGRV KC_QUOT // ù
#define FR_ASTR KC_NUHS // *
#define FR_LABK KC_NUBS // <
#define FR_W KC_Z       // W
#define FR_X KC_X       // X
#define FR_C KC_C       // C
#define FR_V KC_V       // V
#define FR_B KC_B       // B
#define FR_N KC_N       // N
#define FR_COMM KC_M    // ,
#define FR_SCLN KC_COMM // ;
#define FR_COLN KC_DOT  // :
#define FR_EXLM KC_SLSH // !
#define FR_1 S(FR_AMPR)   // 1
#define FR_2 S(FR_EACU)   // 2
#define FR_3 S(FR_DQUO)   // 3
#define FR_4 S(FR_QUOT)   // 4
#define FR_5 S(FR_LPRN)   // 5
#define FR_6 S(FR_MINS)   // 6
#define FR_7 S(FR_EGRV)   // 7
#define FR_8 S(FR_UNDS)   // 8
#define FR_9 S(FR_CCED)   // 9
#define FR_0 S(FR_AGRV)   // 0
#define FR_DEG S(FR_RPRN) // °
#define FR_PLUS S(FR_EQL) // +
#define FR_DIAE S(FR_CIRC) // ¨ (dead)
#define FR_PND S(FR_DLR)   // £
#define FR_PERC S(FR_UGRV) // %
#define FR_MICR S(FR_ASTR) // µ
#define FR_RABK S(FR_LABK) // >
#define FR_QUES S(FR_COMM) // ?
#define FR_DOT S(FR_SCLN)  // .
#define FR_SLSH S(FR_COLN) // /
#define FR_SECT S(FR_EXLM) // §
#define FR_TILD ALGR(FR_EACU) // ~ (dead)
#define FR_HASH ALGR(FR_DQUO) // #
#define FR_LCBR ALGR(FR_QUOT) // {
#define FR_LBRC ALGR(FR_LPRN) // [
#define FR_PIPE ALGR(FR_MINS) // |
#define FR_GRV ALGR(FR_EGRV)  // ` (dead)
#define FR_BSLS ALGR(FR_UNDS) // (backslash)
#define FR_AT ALGR(FR_AGRV)   // @
#define FR_RBRC ALGR(FR_RPRN) // ]
#define FR_RCBR ALGR(FR_EQL)  // }
#define FR_EURO ALGR(KC_E)   // €
#define FR_CURR ALGR(FR_DLR) // ¤

enum custom_keycodes {
    MA_BACKTICK = SAFE_RANGE,
    MA_TILD,
    MA_DELLINE,
    MA_DELX2,
    MA_BSPCX2,
    MA_DOWN,
    MA_UP,
    MA_DOWNX2,
    MA_UPX2,
    MA_RIGHTX2,
    MA_LEFTX2,
    MA_ENTX2,
    MA_DELX4,
    MA_BSPCX4,
    MA_DOWNX4,
    MA_UPX4,
    MA_RIGHTX4,
    MA_LEFTX4,
    MA_ENTX4,
    MA_LTHUMB,
    MA_LTHUMBE,
    MA_LTHUMBD,
    MA_LTHUMB1,
    MA_LTHUMB2,
    MA_LTHUMB3,
    MA_LTHUMBQ,
    MA_LTHUMBW,
    MA_LTHUMBA,
    MA_LTHUMBS,
    MA_LTHUMBF,
    MA_LTHUMBG,
    MA_LTHUMBZ,
    MA_LTHUMBX,
    MA_LTHUMBC,
    MA_LTHUMBV,
    MA_LTHUMBB,
    MA_LTHUMBR,
    MA_LTHUMBT,
    MA_LTHUMBY,
    MA_LPINKY,
    MA_LOSLBISTRIG,
    MA_0,
    MA_1,
    MA_2,
    MA_3,
    MA_4,
    MA_5,
    MA_6,
    MA_7,
    MA_8,
    MA_9,
    MA_EQL,
    MA_ASTR,
    MA_DOT,
    MA_MINS,
    MA_PLUS,
    MA_ENT,
    MA_SLSH,
    MA_CIRC,
    MA_SIMPLEARROW,
    MA_DOUBLEARROW,
};

enum unicode_names {
    EGRAVE,
    EAIGU,
    ECIRC,
    ETREMA,
    AGRAVE,
    ACIRC,
    ATREMA,
    ICIRC,
    ITREMA,
    OCIRC,
    OTREMA,
    UCIRC,
    UTREMA,
};

const uint32_t unicode_map[] PROGMEM = {
    [EGRAVE] = 0x00C8, // È
    [EAIGU] = 0x00C9, // É
    [ECIRC] = 0x00CA, // Ê
    [ETREMA] = 0x00CB, // Ë
    [AGRAVE] = 0x00C0, // À
    [ACIRC] = 0x00C2, // Â
    [ATREMA] = 0x00C4, // Ä
    [ICIRC] = 0x00CE, // Î
    [ITREMA] = 0x00CF, // Ï
    [OCIRC] = 0x00D4, // Ô
    [OTREMA] = 0x00D6, // Ö
    [UAIGU] = 0x00D9, // Ù
    [UCIRC] = 0x00DB, // Û
    [UTREMA] = 0x00DC, // Ü
};

#define LA_BASE 0
#define LA_LTHUMB 1
#define LA_LTHUMBEMO 2
    // gui + shift + lettre côté gauche
    // LSG
#define LA_LTHUMBDMO 3
    // gui + alt + lettre côté gauche
    // RSG
#define LA_LTHUMBEOSL 4
    // ctl + shift + lettre côté gauche
    // LAG
#define LA_LTHUMBDOSL 5
    // ctl + alt + lettre côté gauche
    // RAG
#define LA_LTHUMBEOSLBIS 6
    // ctl + shift + alt + lettre côté gauche
    // LCA
#define LA_LTHUMBDOSLBIS 7
    // ctl + alt + gui + lettre côté gauche
    // RSA
#define LA_LTHUMB1MO 8
    // shift + alt + gui + lettre côté gauche
    // LCAG
#define LA_LTHUMB2MO 9
    // shift + alt + lettre côté gauche
    // MEH
#define LA_LTHUMB3MO 10
    // ctl + shift + alt + gui + lettre côté gauche
    // HYPR
#define LA_CAPSLOCK 11
#define LA_RTHUMB 12
#define LA_LPINKY 13
#define LA_LPINKYQ 14
#define LA_LPINKYW 15

bool isLeftThumbEMoStarted = false;
bool isLeftThumbDMoStarted = false;
bool isDeadKeyCircStarted = false;
bool isDeadKeyTremaStarted = false;



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LA_BASE Level: Default Layer
    |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
    | Esc   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | -     | =   | \     |Win|
    |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
    | Tab   | Q | W | E | R | T | Y | U | I | O | P | [     | ]   | Backs | x |
    |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
    | LGUI  | A | S | D | F | G | H | J | K | L | ; | '     | Ent |   x   | x |
    |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
    | Shift | Z | X | C | V | B | N | M | , | . | / | Shift | Fn0 |   x   | x |
    |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|

        |------+------+-----------------------+------+------|
        | LAlt | Cont | ******* Space ******* | RGUI | RAlt |
        |------+------+-----------------------+------+------|
    */
    [LA_BASE] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_LGUI,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, TG(LA_CAPSLOCK),
        MA_LPINKY, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_RALT,
        KC_LALT, MA_LTHUMB, KC_SPC, MO(LA_RTHUMB), KC_RALT
    ),
    [LA_CAPSLOCK] = LAYOUT(
        KC_TRNS, KC_TRNS, X(EAIGU), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, X(EGRAVE), KC_TRNS, KC_TRNS, X(AGRAVE), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), MA_CIRC, KC_TRNS, KC_TRNS,
        KC_TRNS, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), S(KC_SCLN), X(UAIGU), KC_TRNS,
        KC_TRNS, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LA_RTHUMB] = LAYOUT(
        KC_PWR, FR_EURO, MA_TILD, FR_HASH, MA_BACKTICK, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, QK_REBOOT, QK_BOOTLOADER,
        KC_CAPS, FR_LBRC, FR_RBRC, FR_LCBR, FR_RCBR, FR_AT, FR_MICR, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP, KC_TRNS, KC_BSPC,
        KC_TRNS, FR_LABK, FR_RABK, FR_LPRN, FR_RPRN, FR_PIPE, FR_SECT, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
        KC_TRNS, FR_DEG, FR_SUP2, FR_DLR, FR_PERC, FR_PND, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LA_LPINKY] = LAYOUT(
        KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS,
        KC_TRNS, MO(LA_LPINKYQ), MO(LA_LPINKYW), KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, MA_UP, KC_END, MA_DOUBLEARROW, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_ESC, KC_UP, KC_ENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, MA_DOWN, KC_RGHT, MA_SIMPLEARROW, KC_TRNS, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LCTL, KC_BSPC, KC_TRNS, KC_TRNS
    ),
    [LA_LPINKYQ] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, MA_DELX2, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, MA_UPX2, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_ESC, MA_UPX2, MA_ENTX2, KC_TRNS, KC_TRNS, KC_TRNS, MA_LEFTX2, MA_DOWNX2, MA_RIGHTX2, KC_TRNS, KC_TRNS, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LCTL, MA_BSPCX2, KC_TRNS, KC_TRNS
    ),
    [LA_LPINKYW] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, MA_DELX4, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, MA_UPX4, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_ESC, MA_UPX4, MA_ENTX4, KC_TRNS, KC_TRNS, KC_TRNS, MA_LEFTX4, MA_DOWNX4, MA_RIGHTX4, KC_TRNS, KC_TRNS, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LCTL, MA_BSPCX4, KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMB] = LAYOUT(
        KC_TRNS, MA_LTHUMB1, MA_LTHUMB2, MA_LTHUMB3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, MA_LTHUMBQ, MA_LTHUMBW, MA_LTHUMBE, MA_LTHUMBR, MA_LTHUMBT, MA_LTHUMBY, MA_7, MA_8, MA_9, MA_EQL, MA_ASTR, KC_TRNS, KC_TRNS,
        KC_TRNS, MA_LTHUMBA, MA_LTHUMBS,  MA_LTHUMBD, MA_LTHUMBF, MA_LTHUMBG, MA_DOT, MA_4, MA_5, MA_6, MA_MINS, MA_PLUS, MA_ENT,
        KC_LSFT, MA_LTHUMBZ, MA_LTHUMBX, MA_LTHUMBC, MA_LTHUMBV, MA_LTHUMBB, MA_0, MA_1, MA_2, MA_3, MA_SLSH, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_SPC, MO(LA_RTHUMB), KC_TRNS
    ),
    [LA_LTHUMBEMO] = LAYOUT(
        LSG(KC_ESC), LSG(KC_1), LSG(KC_2), LSG(KC_3), LSG(KC_4), LSG(KC_5), LSG(KC_6), LSG(KC_7), LSG(KC_8), LSG(KC_9), LSG(KC_0), LSG(KC_MINS), LSG(KC_EQL), LSG(KC_BSLS), KC_TRNS,
        LSG(KC_TAB), LSG(KC_Q), LSG(KC_W), LSG(KC_E), LSG(KC_R), LSG(KC_T), LSG(KC_Y), LSG(KC_U), LSG(KC_I), LSG(KC_O), LSG(KC_P), LSG(KC_LBRC), LSG(KC_RBRC), KC_TRNS,
        KC_TRNS, LSG(KC_A), LSG(KC_S), LSG(KC_D), LSG(KC_F), LSG(KC_G), LSG(KC_H), LSG(KC_J), LSG(KC_K), LSG(KC_L), LSG(KC_SCLN), LSG(KC_QUOT), LSG(KC_ENT),
        KC_TRNS, LSG(KC_Z), LSG(KC_X), LSG(KC_C), LSG(KC_V), LSG(KC_B), LSG(KC_N), LSG(KC_M), LSG(KC_COMM), LSG(KC_DOT), LSG(KC_SLSH), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, LSG(KC_SPC), KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMBEOSL] = LAYOUT(
        LAG(KC_ESC), LAG(KC_1), LAG(KC_2), LAG(KC_3), LAG(KC_4), LAG(KC_5), LAG(KC_6), LAG(KC_7), LAG(KC_8), LAG(KC_9), LAG(KC_0), LAG(KC_MINS), LAG(KC_EQL), LAG(KC_BSLS), KC_TRNS,
        LAG(KC_TAB), LAG(KC_Q), LAG(KC_W), LAG(KC_E), LAG(KC_R), LAG(KC_T), LAG(KC_Y), LAG(KC_U), LAG(KC_I), LAG(KC_O), LAG(KC_P), LAG(KC_LBRC), LAG(KC_RBRC), KC_TRNS,
        KC_TRNS, LAG(KC_A), LAG(KC_S), LAG(KC_D), LAG(KC_F), LAG(KC_G), LAG(KC_H), LAG(KC_J), LAG(KC_K), LAG(KC_L), LAG(KC_SCLN), LAG(KC_QUOT), LAG(KC_ENT),
        KC_TRNS, LAG(KC_Z), LAG(KC_X), LAG(KC_C), LAG(KC_V), LAG(KC_B), LAG(KC_N), LAG(KC_M), LAG(KC_COMM), LAG(KC_DOT), LAG(KC_SLSH), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, LAG(KC_SPC), KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMBEOSLBIS] = LAYOUT(
        LCA(KC_ESC), LCA(KC_1), LCA(KC_2), LCA(KC_3), LCA(KC_4), LCA(KC_5), LCA(KC_6), LCA(KC_7), LCA(KC_8), LCA(KC_9), LCA(KC_0), LCA(KC_MINS), LCA(KC_EQL), LCA(KC_BSLS), KC_TRNS,
        LCA(KC_TAB), LCA(KC_Q), LCA(KC_W), LCA(KC_E), LCA(KC_R), LCA(KC_T), LCA(KC_Y), LCA(KC_U), LCA(KC_I), LCA(KC_O), LCA(KC_P), LCA(KC_LBRC), LCA(KC_RBRC), KC_TRNS,
        KC_TRNS, LCA(KC_A), LCA(KC_S), LCA(KC_D), LCA(KC_F), LCA(KC_G), LCA(KC_H), LCA(KC_J), LCA(KC_K), LCA(KC_L), LCA(KC_SCLN), LCA(KC_QUOT), LCA(KC_ENT),
        KC_TRNS, LCA(KC_Z), LCA(KC_X), LCA(KC_C), LCA(KC_V), LCA(KC_B), LCA(KC_N), LCA(KC_M), LCA(KC_COMM), LCA(KC_DOT), LCA(KC_SLSH), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, LCA(KC_SPC), KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMBDMO] = LAYOUT(
        RSG(KC_ESC), RSG(KC_1), RSG(KC_2), RSG(KC_3), RSG(KC_4), RSG(KC_5), RSG(KC_6), RSG(KC_7), RSG(KC_8), RSG(KC_9), RSG(KC_0), RSG(KC_MINS), RSG(KC_EQL), RSG(KC_BSLS), KC_TRNS,
        RSG(KC_TAB), RSG(KC_Q), RSG(KC_W), RSG(KC_E), RSG(KC_R), RSG(KC_T), RSG(KC_Y), RSG(KC_U), RSG(KC_I), RSG(KC_O), RSG(KC_P), RSG(KC_LBRC), RSG(KC_RBRC), KC_TRNS,
        KC_TRNS, RSG(KC_A), RSG(KC_S), RSG(KC_D), RSG(KC_F), RSG(KC_G), RSG(KC_H), RSG(KC_J), RSG(KC_K), RSG(KC_L), RSG(KC_SCLN), RSG(KC_QUOT), RSG(KC_ENT),
        KC_TRNS, RSG(KC_Z), RSG(KC_X), RSG(KC_C), RSG(KC_V), RSG(KC_B), RSG(KC_N), RSG(KC_M), RSG(KC_COMM), RSG(KC_DOT), RSG(KC_SLSH), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, RSG(KC_SPC), KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMBDOSL] = LAYOUT(
        RAG(KC_ESC), RAG(KC_1), RAG(KC_2), RAG(KC_3), RAG(KC_4), RAG(KC_5), RAG(KC_6), RAG(KC_7), RAG(KC_8), RAG(KC_9), RAG(KC_0), RAG(KC_MINS), RAG(KC_EQL), RAG(KC_BSLS), KC_TRNS,
        RAG(KC_TAB), RAG(KC_Q), RAG(KC_W), RAG(KC_E), RAG(KC_R), RAG(KC_T), RAG(KC_Y), RAG(KC_U), RAG(KC_I), RAG(KC_O), RAG(KC_P), RAG(KC_LBRC), RAG(KC_RBRC), KC_TRNS,
        KC_TRNS, RAG(KC_A), RAG(KC_S), RAG(KC_D), RAG(KC_F), RAG(KC_G), RAG(KC_H), RAG(KC_J), RAG(KC_K), RAG(KC_L), RAG(KC_SCLN), RAG(KC_QUOT), RAG(KC_ENT),
        KC_TRNS, RAG(KC_Z), RAG(KC_X), RAG(KC_C), RAG(KC_V), RAG(KC_B), RAG(KC_N), RAG(KC_M), RAG(KC_COMM), RAG(KC_DOT), RAG(KC_SLSH), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, RAG(KC_SPC), KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMBDOSLBIS] = LAYOUT(
        RSA(KC_ESC), RSA(KC_1), RSA(KC_2), RSA(KC_3), RSA(KC_4), RSA(KC_5), RSA(KC_6), RSA(KC_7), RSA(KC_8), RSA(KC_9), RSA(KC_0), RSA(KC_MINS), RSA(KC_EQL), RSA(KC_BSLS), KC_TRNS,
        RSA(KC_TAB), RSA(KC_Q), RSA(KC_W), RSA(KC_E), RSA(KC_R), RSA(KC_T), RSA(KC_Y), RSA(KC_U), RSA(KC_I), RSA(KC_O), RSA(KC_P), RSA(KC_LBRC), RSA(KC_RBRC), KC_TRNS,
        KC_TRNS, RSA(KC_A), RSA(KC_S), RSA(KC_D), RSA(KC_F), RSA(KC_G), RSA(KC_H), RSA(KC_J), RSA(KC_K), RSA(KC_L), RSA(KC_SCLN), RSA(KC_QUOT), RSA(KC_ENT),
        KC_TRNS, RSA(KC_Z), RSA(KC_X), RSA(KC_C), RSA(KC_V), RSA(KC_B), RSA(KC_N), RSA(KC_M), RSA(KC_COMM), RSA(KC_DOT), RSA(KC_SLSH), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, RSA(KC_SPC), KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMB1MO] = LAYOUT(
        LCAG(KC_ESC), LCAG(KC_1), LCAG(KC_2), LCAG(KC_3), LCAG(KC_4), LCAG(KC_5), LCAG(KC_6), LCAG(KC_7), LCAG(KC_8), LCAG(KC_9), LCAG(KC_0), LCAG(KC_MINS), LCAG(KC_EQL), LCAG(KC_BSLS), KC_TRNS,
        LCAG(KC_TAB), LCAG(KC_Q), LCAG(KC_W), LCAG(KC_E), LCAG(KC_R), LCAG(KC_T), LCAG(KC_Y), LCAG(KC_U), LCAG(KC_I), LCAG(KC_O), LCAG(KC_P), LCAG(KC_LBRC), LCAG(KC_RBRC), KC_TRNS,
        KC_TRNS, LCAG(KC_A), LCAG(KC_S), LCAG(KC_D), LCAG(KC_F), LCAG(KC_G), LCAG(KC_H), LCAG(KC_J), LCAG(KC_K), LCAG(KC_L), LCAG(KC_SCLN), LCAG(KC_QUOT), LCAG(KC_ENT),
        KC_TRNS, LCAG(KC_Z), LCAG(KC_X), LCAG(KC_C), LCAG(KC_V), LCAG(KC_B), LCAG(KC_N), LCAG(KC_M), LCAG(KC_COMM), LCAG(KC_DOT), LCAG(KC_SLSH), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, LCAG(KC_SPC), KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMB2MO] = LAYOUT(
        MEH(KC_ESC), MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), MEH(KC_5), MEH(KC_6), MEH(KC_7), MEH(KC_8), MEH(KC_9), MEH(KC_0), MEH(KC_MINS), MEH(KC_EQL), MEH(KC_BSLS), KC_TRNS,
        MEH(KC_TAB), MEH(KC_Q), MEH(KC_W), MEH(KC_E), MEH(KC_R), MEH(KC_T), MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), MEH(KC_LBRC), MEH(KC_RBRC), KC_TRNS,
        KC_TRNS, MEH(KC_A), MEH(KC_S), MEH(KC_D), MEH(KC_F), MEH(KC_G), MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_SCLN), MEH(KC_QUOT), MEH(KC_ENT),
        KC_TRNS, MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B), MEH(KC_N), MEH(KC_M), MEH(KC_COMM), MEH(KC_DOT), MEH(KC_SLSH), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, MEH(KC_SPC), KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMB3MO] = LAYOUT(
        HYPR(KC_ESC), HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5), HYPR(KC_6), HYPR(KC_7), HYPR(KC_8), HYPR(KC_9), HYPR(KC_0), HYPR(KC_MINS), HYPR(KC_EQL), HYPR(KC_BSLS), KC_TRNS,
        HYPR(KC_TAB), HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T), HYPR(KC_Y), HYPR(KC_U), HYPR(KC_I), HYPR(KC_O), HYPR(KC_P), HYPR(KC_LBRC), HYPR(KC_RBRC), KC_TRNS,
        KC_TRNS, HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G), HYPR(KC_H), HYPR(KC_J), HYPR(KC_K), HYPR(KC_L), HYPR(KC_SCLN), HYPR(KC_QUOT), HYPR(KC_ENT),
        KC_TRNS, HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B), HYPR(KC_N), HYPR(KC_M), HYPR(KC_COMM), HYPR(KC_DOT), HYPR(KC_SLSH), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, HYPR(KC_SPC), KC_TRNS, KC_TRNS
    ),
};

bool processKeycodeIfLBase(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMB:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB);
                register_mods(MOD_MASK_CTRL);
            }
            return false;
        case MA_LPINKY:
            if (record->event.pressed) {
                layer_on(LA_LPINKY);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumb(uint16_t keycode, keyrecord_t* record, uint8_t mod_state) {
    unregister_mods(MOD_MASK_CTRL);
    switch (keycode) {
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMB);
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    layer_on(LA_LTHUMBEOSLBIS);
                } else {
                    layer_on(LA_LTHUMBEMO);
                }
             }
            return false;
        case MA_LTHUMBD:
            if (mod_state & MOD_MASK_SHIFT) {
                layer_on(LA_LTHUMBDOSLBIS);
            } else {
                layer_on(LA_LTHUMBDMO);
            }
            return false;
        case MA_LTHUMB1:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB1MO);
            }
            return false;
        case MA_LTHUMB2:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB2MO);
            }
            return false;
        case MA_LTHUMB3:
            if (record->event.pressed) {
                layer_on(LA_LTHUMB3MO);
            }
            return false;
        case MA_0:
            if (record->event.pressed) {
                tap_code16(FR_0);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_1:
            if (record->event.pressed) {
                tap_code16(FR_1);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_2:
            if (record->event.pressed) {
                tap_code16(FR_2);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_3:
            if (record->event.pressed) {
                tap_code16(FR_3);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_4:
            if (record->event.pressed) {
                tap_code16(FR_4);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_5:
            if (record->event.pressed) {
                tap_code16(FR_5);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_6:
            if (record->event.pressed) {
                tap_code16(FR_6);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_7:
            if (record->event.pressed) {
                tap_code16(FR_7);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_8:
            if (record->event.pressed) {
                tap_code16(FR_8);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_9:
            if (record->event.pressed) {
                tap_code16(FR_9);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_EQL:
            if (record->event.pressed) {
                tap_code16(FR_EQL);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_ASTR:
            if (record->event.pressed) {
                tap_code16(FR_ASTR);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_DOT:
            if (record->event.pressed) {
                tap_code16(FR_DOT);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_MINS:
            if (record->event.pressed) {
                tap_code16(FR_MINS);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_PLUS:
            if (record->event.pressed) {
                tap_code16(FR_PLUS);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_ENT:
            if (record->event.pressed) {
                tap_code16(KC_ENT);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
        case MA_SLSH:
            if (record->event.pressed) {
                tap_code16(FR_SLSH);
            }
            register_mods(MOD_MASK_CTRL);
            return false;
    }
    register_mods(MOD_MASK_CTRL);
    return true;
}
bool processKeycodeIfLThumbEMo(uint16_t keycode, keyrecord_t* record) {
    if ((keycode != MA_LTHUMB) & (keycode != MA_LTHUMBE)) {
        isLeftThumbEMoStarted = true;
    }
    switch (keycode) {
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMBEMO);
                if(!isLeftThumbEMoStarted) {
                    layer_on(LA_LTHUMBEOSL);
                } else {
                    isLeftThumbEMoStarted = false;
                    layer_off(LA_LTHUMB);
                }
            }
            return false;
        case MA_DELLINE:
            if (record->event.pressed) {
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                register_code16(KC_LSFT);
                tap_code16(KC_END);
                tap_code16(KC_RGHT);
                unregister_code16(KC_LSFT);
                tap_code16(KC_DEL);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbEOsl(uint16_t keycode, keyrecord_t* record) {
//    switch (keycode) {
//        case MA_LTHUMB:
//            return false;
//    }
    if (!(record->event.pressed)) {
        layer_off(LA_LTHUMB);
        layer_off(LA_LTHUMBEOSL);
    }
    return true;
}
bool processKeycodeIfLThumbEOslBis(uint16_t keycode, keyrecord_t* record) {
//    switch (keycode) {
//        case MA_LTHUMB:
//            return false;
//    }
    if (!(record->event.pressed)) {
        layer_off(LA_LTHUMB);
        layer_off(LA_LTHUMBEOSLBIS);
    }
    return true;
}
bool processKeycodeIfLThumbDMo(uint16_t keycode, keyrecord_t* record) {
    if ((keycode != MA_LTHUMB) & (keycode != MA_LTHUMBD)) {
        isLeftThumbDMoStarted = true;
    }
    switch (keycode) {
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMBDMO);
                if(!isLeftThumbDMoStarted) {
                    layer_on(LA_LTHUMBDOSL);
                } else {
                    isLeftThumbDMoStarted = false;
                    layer_off(LA_LTHUMB);
                }
            }
            return false;
        case MA_DELLINE:
            if (record->event.pressed) {
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                register_code16(KC_LSFT);
                tap_code16(KC_END);
                tap_code16(KC_RGHT);
                unregister_code16(KC_LSFT);
                tap_code16(KC_DEL);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLThumbDOsl(uint16_t keycode, keyrecord_t* record) {
//    switch (keycode) {
//        case MA_LTHUMB:
//            return false;
//    }
    if (!(record->event.pressed)) {
        layer_off(LA_LTHUMB);
        layer_off(LA_LTHUMBDOSL);
    }
    return true;
}
bool processKeycodeIfLThumbDOslBis(uint16_t keycode, keyrecord_t* record) {
//    switch (keycode) {
//        case MA_LTHUMB:
//            return false;
//    }
    if (!(record->event.pressed)) {
        layer_off(LA_LTHUMB);
        layer_off(LA_LTHUMBDOSLBIS);
    }
    return true;
}
bool processKeycodeIfLThumb1Mo(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMB1MO);
                layer_off(LA_LTHUMB);
            }
            return false;
//        case MA_DELLINE:
//            if (record->event.pressed) {
//                tap_code16(KC_HOME);
//                tap_code16(KC_HOME);
//                register_code16(KC_LSFT);
//                tap_code16(KC_END);
//                tap_code16(KC_RGHT);
//                unregister_code16(KC_LSFT);
//                tap_code16(KC_DEL);
//            }
//            return false;
    }
    return true;
}
bool processKeycodeIfLThumb2Mo(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMB2MO);
                layer_off(LA_LTHUMB);
            }
            return false;
//        case MA_DELLINE:
//            if (record->event.pressed) {
//                tap_code16(KC_HOME);
//                tap_code16(KC_HOME);
//                register_code16(KC_LSFT);
//                tap_code16(KC_END);
//                tap_code16(KC_RGHT);
//                unregister_code16(KC_LSFT);
//                tap_code16(KC_DEL);
//            }
//            return false;
    }
    return true;}
bool processKeycodeIfLThumb3Mo(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMB2MO);
                layer_off(LA_LTHUMB);
            }
            return false;
//        case MA_DELLINE:
//            if (record->event.pressed) {
//                tap_code16(KC_HOME);
//                tap_code16(KC_HOME);
//                register_code16(KC_LSFT);
//                tap_code16(KC_END);
//                tap_code16(KC_RGHT);
//                unregister_code16(KC_LSFT);
//                tap_code16(KC_DEL);
//            }
//            return false;
    }
    return true;}
bool processKeycodeIfRThumb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_BACKTICK:
            if (record->event.pressed) {
                tap_code16(FR_GRV);
                // timer = timer_read();
                tap_code16(KC_SPC);
            }
            return false;
        case MA_TILD:
            if (record->event.pressed) {
                tap_code16(FR_TILD);
                tap_code16(KC_SPC);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLPinky(uint16_t keycode, keyrecord_t* record, uint8_t mod_state) {
    switch (keycode) {
        case MA_LPINKY:
            if (!(record->event.pressed)) {
                layer_off(LA_LPINKY);
            }
            return false;
        case MA_UP:
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_CTRL) {
                    unregister_code16(KC_LCTL);
                    tap_code16(KC_UP);
                    register_code16(KC_LCTL);
                } else {
                    tap_code16(KC_UP);
                }
            }
            return false;
        case MA_DOWN:
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_CTRL) {
                    unregister_code16(KC_LCTL);
                    tap_code16(KC_DOWN);
                    register_code16(KC_LCTL);
                } else {
                    tap_code16(KC_DOWN);
                }
            }
            return false;
        case MA_DOUBLEARROW:
            if (record->event.pressed) {
                tap_code16(FR_EQL);
                tap_code16(FR_RABK);
                tap_code16(KC_SPC);
            }
            return false;
        case MA_SIMPLEARROW:
            if (record->event.pressed) {
                tap_code16(FR_MINS);
                tap_code16(FR_RABK);
                tap_code16(KC_SPC);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLPinkyQ(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_UPX2:
            if (record->event.pressed) {
                tap_code16(KC_UP);
                tap_code16(KC_UP);
            }
            return false;
        case MA_DOWNX2:
            if (record->event.pressed) {
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
            }
            return false;
        case MA_LEFTX2:
            if (record->event.pressed) {
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
            }
            return false;
        case MA_RIGHTX2:
            if (record->event.pressed) {
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
            }
            return false;
        case MA_DELX2:
            if (record->event.pressed) {
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
            }
            return false;
        case MA_ENTX2:
            if (record->event.pressed) {
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
            }
            return false;
        case MA_BSPCX2:
            if (record->event.pressed) {
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLPinkyZ(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MA_UPX4:
            if (record->event.pressed) {
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
                tap_code16(KC_UP);
            }
            return false;
        case MA_DOWNX4:
            if (record->event.pressed) {
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
                tap_code16(KC_DOWN);
            }
            return false;
        case MA_LEFTX4:
            if (record->event.pressed) {
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
            }
            return false;
        case MA_RIGHTX4:
            if (record->event.pressed) {
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
            }
            return false;
        case MA_DELX4:
            if (record->event.pressed) {
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
                tap_code16(KC_DEL);
            }
            return false;
        case MA_ENTX4:
            if (record->event.pressed) {
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
                tap_code16(KC_ENT);
            }
            return false;
        case MA_BSPCX4:
            if (record->event.pressed) {
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
                tap_code16(KC_BSPC);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfLCapslock(uint16_t keycode, keyrecord_t* record, uint8_t mod_state) {
    switch (keycode) {
        case MA_CIRC:
            if (record->event.pressed) {
                if (!isDeadKeyTremaStarted & mod_state & MOD_MASK_SHIFT) {isDeadKeyTremaStarted=true;}
                else if (!isDeadKeyCircStarted) {isDeadKeyCircStarted=true;}
            }
            return false;
        case S(KC_O):
            if (record->event.pressed) {
                if (isDeadKeyTremaStarted) {tap_code16(X(OTREMA));}
                else if (isDeadKeyCircStarted) {tap_code16(X(OCIRC));}
            }
            return false;
        case S(KC_A):
            if (record->event.pressed) {
                if (isDeadKeyTremaStarted) {tap_code16(X(ATREMA));}
                else if (isDeadKeyCircStarted) {tap_code16(X(ACIRC));}
            }
            return false;
        case S(KC_I):
            if (record->event.pressed) {
                if (isDeadKeyTremaStarted) {tap_code16(X(ITREMA));}
                else if (isDeadKeyCircStarted) {tap_code16(X(ICIRC));}
            }
            return false;
        case S(KC_U):
            if (record->event.pressed) {
                if (isDeadKeyTremaStarted) {tap_code16(X(UTREMA));}
                else if (isDeadKeyCircStarted) {tap_code16(X(UCIRC));}
            }
            return false;
    }
    if (isDeadKeyCircStarted) {isDeadKeyCircStarted=false;}
    if (isDeadKeyTremaStarted) {isDeadKeyTremaStarted=false;}
    return true;
}
bool processKeycodeIfShift(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_SLSH:
            if (record->event.pressed) {
                tap_code16(FR_BSLS);
            }
            return false;
    }
    return true;
}
bool processKeycodeIfCtl(uint16_t keycode, keyrecord_t* record) {return true;}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Store the current modifier state in the variable for later reference
    uint8_t mod_state = get_mods();

    if (IS_LAYER_ON(LA_LTHUMB)) {
        if (IS_LAYER_ON(LA_LTHUMBEOSL)) {
            return processKeycodeIfLThumbEOsl(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBEOSLBIS)) {
            return processKeycodeIfLThumbEOslBis(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBEMO)) {
            return processKeycodeIfLThumbEMo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBDOSL)) {
            return processKeycodeIfLThumbDOsl(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBDOSLBIS)) {
            return processKeycodeIfLThumbDOslBis(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBDMO)) {
            return processKeycodeIfLThumbDMo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMB1MO)) {
            return processKeycodeIfLThumb1Mo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMB2MO)) {
            return processKeycodeIfLThumb2Mo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMB3MO)) {
            return processKeycodeIfLThumb3Mo(keycode, record);
        } else {
            return processKeycodeIfLThumb(keycode, record, mod_state);
        }
    }
    if (IS_LAYER_ON(LA_LPINKY)) {
        if (IS_LAYER_ON(LA_LPINKYQ)) {
            return processKeycodeIfLPinkyQ(keycode, record);
        } else if (IS_LAYER_ON(LA_LPINKYW)) {
            return processKeycodeIfLPinkyZ(keycode, record);
        } else {
            return processKeycodeIfLPinky(keycode, record, mod_state);
        }
    }
    if (IS_LAYER_ON(LA_RTHUMB)) {return processKeycodeIfRThumb(keycode, record);}
    if (mod_state & MOD_MASK_SHIFT) {return processKeycodeIfShift(keycode, record);}
    if (mod_state & MOD_MASK_CTRL) {return processKeycodeIfCtl(keycode, record);}
    if (IS_LAYER_ON(LA_CAPSLOCK)) {return processKeycodeIfLCapslock(keycode, record, mod_state);}
    if (IS_LAYER_ON(LA_BASE)) {return processKeycodeIfLBase(keycode, record);}


    return true;
}


