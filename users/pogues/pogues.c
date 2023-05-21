#include "pogues.h"

/******************************************************************************
 * combo keys
 ******************************************************************************/
enum combo_keys {
    // naming is combo _ hand _ fingers (r=ring, m=middle, i=index) _ row (t=top, b=bottom) _ key
    // left hand only
    WF_ESC,
    CD_TAB,
    ZX_Q,           // trial on zx for q - skeletyl

    RESET_COMBO,

    // right hand only
    UY_DEL,
    HCOM_ENT,
    JY_CTLBSP,
    DOTSLSH_COMPOSE,  // trial compose on right lower ring/pinkie for skeletyl

    // both hands, not using pl / fu any more due to typing mishits
    WY_LMSE,

    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_esc[] = {CTL_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_reset[] = {KC_ESC, KC_TAB, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_U, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_J, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_q[] = {SFT_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_compose[] = {KC_DOT, SFT_SLS, COMBO_END};
const uint16_t PROGMEM combo_mouse[] = {CTL_W, CTL_Y, COMBO_END};

combo_t key_combos[] = {
    [WF_ESC] = COMBO(combo_esc, KC_ESC),
    [CD_TAB] = COMBO(combo_tab, KC_TAB),
    [ZX_Q] = COMBO(combo_q, KC_Q),

    [UY_DEL] = COMBO(combo_del, KC_DEL),
    [HCOM_ENT] = COMBO(combo_ent, KC_ENT),
    [JY_CTLBSP] = COMBO(combo_bspc, LCTL(KC_BSPC)),
    [DOTSLSH_COMPOSE] = COMBO(combo_compose, MY_COMP),
#ifdef MOUSEKEY_ENABLE
    [RESET_COMBO] = COMBO(combo_reset, QK_BOOTLOADER),
    [WY_LMSE] = COMBO(combo_mouse, TO(LMSE)),
#endif
};

/******************************************************************************
 * combo keys end
 ******************************************************************************/

/******************************************************************************
 * compose key mapping function
 ******************************************************************************/
uint8_t compose_mapping(uint16_t* sequence, uint8_t sequence_len) {
    // NOTE that the COMPOSE_MAPPING will return if there is a full or partial
    // match to the sequence.

    /**********************************************************************
     * general
     *********************************************************************/
    // caps word
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_C),
        { toggle_caps_word(); }
    )

    // quit dwm
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_Q),
        { SEND_STRING(SS_LGUI(SS_LSFT("q"))); }
    )

    /**********************************************************************
     * copy paste
     *********************************************************************/
    // copy all
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_C),
        { SEND_STRING(SS_LCTL("ac")); }
    )
    // cut all
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_X),
        { SEND_STRING(SS_LCTL("ax")); }
    )
    // paste
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_P),
        { SEND_STRING(SS_LCTL("v")); }
    )

    /**********************************************************************
     * qzdev
     *********************************************************************/
    // open a file
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_O),
        { SEND_STRING(SS_LCTL(SS_LSFT("o"))); }
    )

    /**********************************************************************
     * qzdev diff
     *********************************************************************/
    // diff current
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT("g"))); }
    )
    // diff approved
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_A),
        { SEND_STRING(SS_LCTL(SS_LSFT("v"))); }
    )
    // diff prod
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_P),
        { SEND_STRING(SS_LCTL(SS_LSFT("p"))); }
    )
    // diff head
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_H),
        { SEND_STRING(SS_LCTL(SS_LSFT("e"))); }
    )
    // diff against version
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_V),
        { SEND_STRING(SS_LCTL(SS_LSFT("d"))); }
    )

    /**********************************************************************
     * qzdev vc
     *********************************************************************/
    // vc blame
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_B),
        { SEND_STRING(SS_LCTL(SS_LSFT("b"))); }
    )

    // vc log
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_L),
        { SEND_STRING(SS_LCTL(SS_LSFT("l"))); }
    )

    // vc commit
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT("c"))); }
    )

    // vc request review
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_R),
        { SEND_STRING(SS_LCTL(SS_LSFT("w"))); }
    )

    // push to
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_P),
        { SEND_STRING(SS_LCTL(SS_LSFT("s"))); }
    )

    // vc update
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_U),
        { SEND_STRING(SS_LCTL(SS_LSFT("u"))); }
    )

    /**********************************************************************
     * qzdev run test
     *********************************************************************/
    // run test function
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_F),
        { SEND_STRING(SS_LCTL(SS_TAP(X_F10))); }
    )
    // run test class
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_F10)))); }
    )
    // run test module
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_S),
        { SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_F10)))); }
    )

    /**********************************************************************
     * qzdev run
     *********************************************************************/
    // run script
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_S),
        { tap_code(KC_F9); }
    )
    // run script with restart
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_R),
        { SEND_STRING(SS_LCTL(SS_TAP(X_F9))); }
    )
    // run selected text
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_T),
        { SEND_STRING(SS_LALT(SS_TAP(X_F9))); }
    )

    return COMPOSE_ERROR;
}


/******************************************************************************
 * compose end
 ******************************************************************************/

