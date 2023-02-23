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
};

#define LA_BASE 0
#define LA_LTHUMB 1
#define LA_LTHUMBEMO 2
#define LA_LTHUMBEOSL 3
#define LA_LTHUMBDMO 4
#define LA_LTHUMBDOSL 5
#define LA_LTHUMB1MO 6
#define LA_LTHUMB2MO 7
#define LA_LTHUMB3MO 8
#define LA_CAPSLOCK 9
#define LA_RTHUMB 10
#define LA_LPINKY 11
#define LA_LPINKYQ 12
#define LA_LPINKYW 13
#define LA_LPINKYR 14
#define LA_LPINKYF 15

bool isLeftThumbEMoStarted = false;
bool isLeftThumbDMoStarted = false;



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
        KC_ESC, KC_1, X(EAIGU), KC_3, KC_4, KC_5, KC_6, X(EGRAVE), KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_LGUI,
        KC_TAB, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), KC_LBRC, KC_RBRC, TG(LA_CAPSLOCK),
        MO(LA_LPINKY), S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), S(KC_SCLN), KC_QUOT, KC_ENT,
        KC_LSFT, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(LA_LPINKY),
        KC_LALT, MA_LTHUMB, KC_SPC, MO(LA_RTHUMB), KC_RALT
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
        KC_TRNS, MO(LA_LPINKYQ), MO(LA_LPINKYW), KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, MA_UP, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_ESC, KC_UP, KC_ENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, MA_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_PENT,
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
        MA_LPINKY, MA_LTHUMBA, MA_LTHUMBS,  MA_LTHUMBD, MA_LTHUMBF, MA_LTHUMBG, MA_DOT, MA_4, MA_5, MA_6, MA_MINS, MA_PLUS, MA_ENT,
        KC_TRNS, MA_LTHUMBZ, MA_LTHUMBX, MA_LTHUMBC, MA_LTHUMBV, MA_LTHUMBB, MA_0, MA_1, MA_2, MA_3, MA_SLSH, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_SPC, MO(LA_RTHUMB), KC_TRNS
    ),
    [LA_LTHUMBEMO] = LAYOUT(
        KC_TRNS, KC_TRNS, MA_DELLINE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMBEOSL] = LAYOUT(
        KC_TRNS, C(KC_Q), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMBDMO] = LAYOUT(
        KC_TRNS, KC_TRNS, MA_DELLINE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMBDOSL] = LAYOUT(
        KC_TRNS, C(KC_Q), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMB1MO] = LAYOUT(
        KC_TRNS, MA_DELLINE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMB2MO] = LAYOUT(
        KC_TRNS, MA_DELLINE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LA_LTHUMB3MO] = LAYOUT(
        KC_TRNS, MA_DELLINE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
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
bool processKeycodeIfLThumb(uint16_t keycode, keyrecord_t* record) {
    unregister_mods(MOD_MASK_CTRL);
    switch (keycode) {
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                layer_off(LA_LTHUMB);
            }
            return false;
        case MA_LTHUMBE:
            if (record->event.pressed) {
                layer_on(LA_LTHUMBEMO);
            }
            return false;
        case MA_LTHUMBD:
            if (record->event.pressed) {
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
        case MA_LPINKY:
            if (record->event.pressed) {
                layer_off(LA_LTHUMB);
                layer_on(LA_LPINKY);
                register_code16(KC_LCTL);
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
        case MA_LTHUMB:
            if (!(record->event.pressed)) {
                unregister_code16(KC_LCTL);
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
        } else if (IS_LAYER_ON(LA_LTHUMBEMO)) {
            return processKeycodeIfLThumbEMo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBDOSL)) {
            return processKeycodeIfLThumbDOsl(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBDMO)) {
            return processKeycodeIfLThumbDMo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMB1MO)) {
            return processKeycodeIfLThumb1Mo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMB2MO)) {
            return processKeycodeIfLThumb2Mo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMB3MO)) {
            return processKeycodeIfLThumb3Mo(keycode, record);
        } else {
            return processKeycodeIfLThumb(keycode, record);
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
    if (IS_LAYER_ON(LA_BASE)) {return processKeycodeIfLBase(keycode, record);}


    return true;
}


