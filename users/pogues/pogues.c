#include "pogues.h"


static bool vscode = false;
uint8_t vscode_compose_mapping(uint16_t* sequence, uint8_t sequence_len);
uint8_t qzdev_compose_mapping(uint16_t* sequence, uint8_t sequence_len);


void toggle_dev_env(void) {
    // TODO move out and look at lighting options?
    vscode = !vscode;
}

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

    // quit window manager
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_Q),
        { SEND_STRING(SS_LGUI(SS_LSFT("q"))); }
    )

    // start window manager menu (launcher)
    COMPOSE_MAPPING(
        COMPOSE_INPUT(MOV_SPC),
        { SEND_STRING(SS_LGUI(SS_LSFT("l"))); }
    )

    // set the mode to qzdev or vscode
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_M),
        { toggle_dev_env(); }
    )

    if (vscode) {
        return vscode_compose_mapping(sequence, sequence_len);
    } else {
        return qzdev_compose_mapping(sequence, sequence_len);
    }
}

uint8_t vscode_compose_mapping(uint16_t* sequence, uint8_t sequence_len) {
    // open file (quick open/goto file)
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_O),
        { SEND_STRING(SS_LCTL("p")); }
    )
    // command pallet
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_P),
        { SEND_STRING(SS_LCTL(SS_LSFT("p"))); }
    )

    // run script
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_S),
        { tap_code(KC_F7); }
    )
    // assume we are called last
    return COMPOSE_ERROR;
}

uint8_t qzdev_compose_mapping(uint16_t* sequence, uint8_t sequence_len) {
    // hold the mappings that apply to qzdev, must be called last
    // open a file
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_O),
        { SEND_STRING(SS_LCTL(SS_LSFT("o"))); }
    )

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

    // assume we are called last
    return COMPOSE_ERROR;
}




/******************************************************************************
 * compose end
 ******************************************************************************/

